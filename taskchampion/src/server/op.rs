use crate::operation::Operation;
use chrono::{DateTime, Utc};
use serde::{Deserialize, Serialize};
use uuid::Uuid;

/// A SyncOp defines a single change to the task database, that can be synchronized
/// via a server.
#[derive(PartialEq, Eq, Clone, Debug, Serialize, Deserialize)]
pub(crate) enum SyncOp {
    /// Create a new task.
    ///
    /// On application, if the task already exists, the operation does nothing.
    Create { uuid: Uuid },

    /// Delete an existing task.
    ///
    /// On application, if the task does not exist, the operation does nothing.
    Delete { uuid: Uuid },

    /// Update an existing task, setting the given property to the given value.  If the value is
    /// None, then the corresponding property is deleted.
    ///
    /// If the given task does not exist, the operation does nothing.
    Update {
        uuid: Uuid,
        property: String,
        value: Option<String>,
        timestamp: DateTime<Utc>,
    },
}

/// See [`SyncOp::transform`] for details.
#[derive(PartialEq, Eq, Debug)]
pub(crate) enum TransformResult {
    /// No conflict between op1 and op2; they are returned unchanged.
    NoConflict,
    /// Both op1 and op2 create the same state, no further operations are required.
    Redundant,
    /// Op1 "wins". WINNER INVARIANT implies that for all task states, applying op2 and then op1
    /// has the same effect as applying op2 alone.
    Op1Wins,
    /// Op2 "wins". WINNER INVARIANT implies that for all task states, applying op1 and then op2
    /// has the same efffect as applying op1 alone.
    Op2Wins,
}

use SyncOp::*;

impl SyncOp {
    pub(crate) fn uuid(&self) -> Uuid {
        *match self {
            Create { uuid, .. } => uuid,
            Delete { uuid, .. } => uuid,
            Update { uuid, .. } => uuid,
        }
    }

    /// Calculate the transform of the given operations.
    ///
    /// Transform takes two operations op1 and op2 that happened concurrently and produces two
    /// operations op1' and op2' such that `apply(apply(S, op1), op2') = apply(apply(S, op2),
    /// op1')` (the TRANSFORM INVARIANT).
    ///
    /// This function is used to serialize operations in a process similar to a Git
    /// "merge". Here op1 has been applied to state A to create state B, while op2 has been
    /// applied to state A to create state C.
    ///
    /// ```text
    ///        A
    ///       / \
    ///  op1 /   \ op2
    ///     /     \
    ///    B       C
    /// ```
    ///
    /// this function "completes the diamond:
    ///
    /// ```text
    ///    B       C
    ///     \     /
    /// op2' \   / op1'
    ///       \ /
    ///        D
    /// ```
    ///
    /// such that applying op2' to state B creates state D, and applying op1' to state C creates
    /// the same state D, resolving the state divergence. This allows two different systems which
    /// have already applied op1 and op2, respectively, and thus reached different states (B and
    /// C), to return to the same state (D) by applying op2' and op1', respectively.
    ///
    /// In most cases, the operations do not conflict, so op1' = op1 and op2' = op2.
    ///
    /// In some of the remaining cases, the two operations are redundant, and state B = C. In this
    /// case, op1' and op2' are both empty.
    ///
    /// Otherwise, the operations conflict and one operation "wins", in the sense that it is
    /// applied and erases the effect of the "losing" operation. For example, given two updates of
    /// the same property on the same task, the later update "wins" and the earlier update "loses".
    /// when op1 wins, op1' = op1, and op2' is empty; the reverse applies when op2 wins.
    ///
    /// WINNER INVARIANT: In all cases of conflict, applying the losing operation followed by the
    /// winning operation has the same effect as applying only the winning operation.
    ///
    /// For reasons of convenience in the caller ([`crate::taskdb::sync`]), this method returns an
    /// enum detailing how the two operations interact; the [`transform_ops`] method can translate
    /// this result into op1' and op2'.
    pub(crate) fn transform(op1: &SyncOp, op2: &SyncOp) -> TransformResult {
        // Operations on different UUIDs never conflict.
        if op1.uuid() != op2.uuid() {
            return TransformResult::NoConflict;
        }

        // Operations on the same task require further scruitiny.
        match (op1, op2) {
            // Two creations or deletions of the same uuid reach the same state, so there's no need
            // for any further operations to bring the state together.
            (&Create { .. }, &Create { .. }) => TransformResult::Redundant,
            (&Delete { .. }, &Delete { .. }) => TransformResult::Redundant,

            // Given a create and a delete of the same task, one of the operations is invalid: the
            // create implies the task does not exist, but the delete implies it exists. The the
            // delete must win, otherwise the WINNER INVARIANT would be violated.
            (&Delete { .. }, &Create { .. }) => TransformResult::Op1Wins,
            (&Create { .. }, &Delete { .. }) => TransformResult::Op2Wins,

            // And again from an Update and a Create, prefer the Update, as it implies the
            // creation, upholding the WINNER INVARIANT.
            (&Update { .. }, &Create { .. }) => TransformResult::Op1Wins,
            (&Create { .. }, &Update { .. }) => TransformResult::Op2Wins,

            // As with create vs. delete, a delete must win over an update.
            (&Update { .. }, &Delete { .. }) => TransformResult::Op2Wins,
            (&Delete { .. }, &Update { .. }) => TransformResult::Op1Wins,

            // Two updates to the same property of the same task might conflict.
            (
                Update {
                    property: property1,
                    value: value1,
                    timestamp: timestamp1,
                    ..
                },
                Update {
                    property: property2,
                    value: value2,
                    timestamp: timestamp2,
                    ..
                },
            ) if property1 == property2 => {
                // If everything is the same, they are redundant. If the value is the same, there's
                // no conflict. Otherwise, prefer the later modification, or (arbitrarily) the
                // lexically later value.
                if value1 == value2 {
                    if timestamp1 == timestamp2 {
                        TransformResult::Redundant
                    } else {
                        TransformResult::NoConflict
                    }
                } else if timestamp1 > timestamp2 || timestamp1 == timestamp2 && value1 > value2 {
                    TransformResult::Op1Wins
                } else {
                    TransformResult::Op2Wins
                }
            }

            // anything else is not a conflict of any sort, so return the operations unchanged
            (_, _) => TransformResult::NoConflict,
        }
    }

    /// Determine op1' and op2' as described for [`transform`].
    pub(crate) fn transformed_ops(
        op1: &SyncOp,
        op2: &SyncOp,
        res: TransformResult,
    ) -> (Option<SyncOp>, Option<SyncOp>) {
        match res {
            TransformResult::NoConflict => (Some(op1.clone()), Some(op2.clone())),
            TransformResult::Redundant => (None, None),
            TransformResult::Op1Wins => (Some(op1.clone()), None),
            TransformResult::Op2Wins => (None, Some(op2.clone())),
        }
    }

    /// Convert the public Operation type into a SyncOp. `UndoPoint` operations are converted to
    /// `None`.
    pub(crate) fn from_op(op: Operation) -> Option<Self> {
        match op {
            Operation::Create { uuid } => Some(SyncOp::Create { uuid }),
            Operation::Delete { uuid, .. } => Some(SyncOp::Delete { uuid }),
            Operation::Update {
                uuid,
                property,
                value,
                timestamp,
                ..
            } => Some(SyncOp::Update {
                uuid,
                property,
                value,
                timestamp,
            }),
            Operation::UndoPoint => None,
        }
    }
}

#[cfg(test)]
mod test {
    use super::*;
    use crate::errors::Result;
    use crate::storage::{InMemoryStorage, TaskMap};
    use crate::taskdb::TaskDb;
    use crate::Operations;
    use chrono::{Duration, Utc};
    use pretty_assertions::assert_eq;
    use proptest::prelude::*;

    // Tests of the SyncOp transform verify that the transform is correct by examining its effect
    // on a TaskDb. But TaskDb requires `Operation` values, so tests use a bit of glue code to
    // bridge the gap.
    impl SyncOp {
        pub(crate) fn into_op(self) -> Operation {
            match self {
                Create { uuid } => Operation::Create { uuid },
                Delete { uuid } => Operation::Delete {
                    uuid,
                    old_task: crate::storage::TaskMap::new(),
                },
                Update {
                    uuid,
                    property,
                    value,
                    timestamp,
                } => Operation::Update {
                    uuid,
                    property,
                    value,
                    timestamp,
                    old_value: None,
                },
            }
        }
    }

    #[test]
    fn test_json_create() -> Result<()> {
        let uuid = Uuid::new_v4();
        let op = Create { uuid };
        let json = serde_json::to_string(&op)?;
        assert_eq!(json, format!(r#"{{"Create":{{"uuid":"{}"}}}}"#, uuid));
        let deser: SyncOp = serde_json::from_str(&json)?;
        assert_eq!(deser, op);
        Ok(())
    }

    #[test]
    fn test_json_delete() -> Result<()> {
        let uuid = Uuid::new_v4();
        let op = Delete { uuid };
        let json = serde_json::to_string(&op)?;
        assert_eq!(json, format!(r#"{{"Delete":{{"uuid":"{}"}}}}"#, uuid));
        let deser: SyncOp = serde_json::from_str(&json)?;
        assert_eq!(deser, op);
        Ok(())
    }

    #[test]
    fn test_json_update() -> Result<()> {
        let uuid = Uuid::new_v4();
        let timestamp = Utc::now();

        let op = Update {
            uuid,
            property: "abc".into(),
            value: Some("false".into()),
            timestamp,
        };

        let json = serde_json::to_string(&op)?;
        assert_eq!(
            json,
            format!(
                r#"{{"Update":{{"uuid":"{}","property":"abc","value":"false","timestamp":"{:?}"}}}}"#,
                uuid, timestamp,
            )
        );
        let deser: SyncOp = serde_json::from_str(&json)?;
        assert_eq!(deser, op);
        Ok(())
    }

    #[test]
    fn test_json_update_none() -> Result<()> {
        let uuid = Uuid::new_v4();
        let timestamp = Utc::now();

        let op = Update {
            uuid,
            property: "abc".into(),
            value: None,
            timestamp,
        };

        let json = serde_json::to_string(&op)?;
        assert_eq!(
            json,
            format!(
                r#"{{"Update":{{"uuid":"{}","property":"abc","value":null,"timestamp":"{:?}"}}}}"#,
                uuid, timestamp,
            )
        );
        let deser: SyncOp = serde_json::from_str(&json)?;
        assert_eq!(deser, op);
        Ok(())
    }

    fn test_transform(setup: Option<SyncOp>, op1: SyncOp, op2: SyncOp, exp: TransformResult) {
        let res = SyncOp::transform(&op1, &op2);
        assert_eq!(res, exp);

        let (op1_prime, op2_prime) = SyncOp::transformed_ops(&op1, &op2, res);

        // check that the two operation sequences have the same effect, enforcing the invariant of
        // the transform function.
        let mut db1 = TaskDb::new_inmemory();
        let mut ops1 = Operations::new();
        if let Some(o) = setup.clone() {
            ops1.push(o.into_op());
        }
        ops1.push(op1.into_op());
        if let Some(o) = op2_prime {
            ops1.push(o.into_op());
        }
        db1.commit_operations(ops1, |_| false).unwrap();

        let mut db2 = TaskDb::new_inmemory();
        let mut ops2 = Operations::new();
        if let Some(o) = setup {
            ops2.push(o.into_op());
        }
        ops2.push(op2.into_op());
        if let Some(o) = op1_prime {
            ops2.push(o.into_op());
        }
        db2.commit_operations(ops2, |_| false).unwrap();

        assert_eq!(db1.sorted_tasks(), db2.sorted_tasks());
    }

    #[test]
    fn test_unrelated_create() {
        let uuid1 = Uuid::new_v4();
        let uuid2 = Uuid::new_v4();

        test_transform(
            None,
            Create { uuid: uuid1 },
            Create { uuid: uuid2 },
            TransformResult::NoConflict,
        );
    }

    #[test]
    fn test_related_updates_different_props() {
        let uuid = Uuid::new_v4();
        let timestamp = Utc::now();

        test_transform(
            Some(Create { uuid }),
            Update {
                uuid,
                property: "abc".into(),
                value: Some("true".into()),
                timestamp,
            },
            Update {
                uuid,
                property: "def".into(),
                value: Some("false".into()),
                timestamp,
            },
            TransformResult::NoConflict,
        );
    }

    #[test]
    fn test_related_updates_same_prop_1_wins() {
        let uuid = Uuid::new_v4();
        let timestamp1 = Utc::now();
        let timestamp2 = timestamp1 - Duration::seconds(10);

        test_transform(
            Some(Create { uuid }),
            Update {
                uuid,
                property: "abc".into(),
                value: Some("true".into()),
                timestamp: timestamp1,
            },
            Update {
                uuid,
                property: "abc".into(),
                value: Some("false".into()),
                timestamp: timestamp2,
            },
            TransformResult::Op1Wins,
        );
    }

    #[test]
    fn test_related_updates_same_prop_2_wins() {
        let uuid = Uuid::new_v4();
        let timestamp1 = Utc::now();
        let timestamp2 = timestamp1 + Duration::seconds(10);

        test_transform(
            Some(Create { uuid }),
            Update {
                uuid,
                property: "abc".into(),
                value: Some("true".into()),
                timestamp: timestamp1,
            },
            Update {
                uuid,
                property: "abc".into(),
                value: Some("false".into()),
                timestamp: timestamp2,
            },
            TransformResult::Op2Wins,
        );
    }

    #[test]
    fn test_related_updates_same_prop_same_value() {
        let uuid = Uuid::new_v4();
        let timestamp1 = Utc::now();
        let timestamp2 = timestamp1 - Duration::seconds(10);

        test_transform(
            Some(Create { uuid }),
            Update {
                uuid,
                property: "abc".into(),
                value: Some("v".into()),
                timestamp: timestamp1,
            },
            Update {
                uuid,
                property: "abc".into(),
                value: Some("v".into()),
                timestamp: timestamp2,
            },
            TransformResult::NoConflict,
        );
    }

    #[test]
    fn test_related_updates_same_prop_same_time() {
        let uuid = Uuid::new_v4();
        let timestamp = Utc::now();

        test_transform(
            Some(Create { uuid }),
            Update {
                uuid,
                property: "abc".into(),
                value: Some("true".into()),
                timestamp,
            },
            Update {
                uuid,
                property: "abc".into(),
                value: Some("false".into()),
                timestamp,
            },
            TransformResult::Op1Wins,
        );
    }

    #[test]
    fn test_related_updates_redundant() {
        let uuid = Uuid::new_v4();
        let timestamp = Utc::now();

        test_transform(
            Some(Create { uuid }),
            Update {
                uuid,
                property: "abc".into(),
                value: Some("v".into()),
                timestamp,
            },
            Update {
                uuid,
                property: "abc".into(),
                value: Some("v".into()),
                timestamp,
            },
            TransformResult::Redundant,
        );
    }

    fn uuid_strategy() -> impl Strategy<Value = Uuid> {
        prop_oneof![
            Just(Uuid::parse_str("83a2f9ef-f455-4195-b92e-a54c161eebfc").unwrap()),
            Just(Uuid::parse_str("56e0be07-c61f-494c-a54c-bdcfdd52d2a7").unwrap()),
            Just(Uuid::parse_str("4b7ed904-f7b0-4293-8a10-ad452422c7b3").unwrap()),
            Just(Uuid::parse_str("9bdd0546-07c8-4e1f-a9bc-9d6299f4773b").unwrap()),
        ]
    }

    fn operation_strategy() -> impl Strategy<Value = SyncOp> {
        prop_oneof![
            uuid_strategy().prop_map(|uuid| Create { uuid }),
            uuid_strategy().prop_map(|uuid| Delete { uuid }),
            (uuid_strategy(), "(title|project|status)").prop_map(|(uuid, property)| {
                Update {
                    uuid,
                    property,
                    value: Some("true".into()),
                    timestamp: Utc::now(),
                }
            }),
        ]
    }

    proptest! {
        #![proptest_config(ProptestConfig {
          cases: 1024, .. ProptestConfig::default()
        })]
        #[test]
        /// Check that, given two operations on a shared state, the TRANSFORM INVARIANT holds.
        fn transform_invariant_holds(preop1 in operation_strategy(),preop2 in operation_strategy(), op1 in operation_strategy(), op2 in operation_strategy()) {
            let res = SyncOp::transform(&op1, &op2);
            let (op1_prime, op2_prime) = SyncOp::transformed_ops(&op1, &op2, res);

            let mut ops1 = Operations::new();
            let mut ops2 = Operations::new();
            let mut db1 = TaskDb::new(Box::new(InMemoryStorage::new()));
            let mut db2 = TaskDb::new(Box::new(InMemoryStorage::new()));

            ops1.push(preop1.clone().into_op());
            ops1.push(preop2.clone().into_op());
            ops1.push(op1.into_op());
            if let Some(op2_prime) = op2_prime {
                ops1.push(op2_prime.into_op());
            }

            ops2.push(preop1.into_op());
            ops2.push(preop2.into_op());
            ops2.push(op2.into_op());
            if let Some(op1_prime) = op1_prime {
                ops2.push(op1_prime.into_op());
            }

            db1.commit_operations(ops1, |_| false).unwrap();
            db2.commit_operations(ops2, |_| false).unwrap();

            assert_eq!(db1.sorted_tasks(), db2.sorted_tasks());
        }
    }

    proptest! {
        #![proptest_config(ProptestConfig {
          cases: 1024, .. ProptestConfig::default()
        })]
        #[test]
        /// Check that, given two operations on a shared state, the WINNER INVARIANT holds.
        fn winner_invariant_holds(preop1 in operation_strategy(),preop2 in operation_strategy(), mut op1 in operation_strategy(), mut op2 in operation_strategy()) {
            let res = SyncOp::transform(&op1, &op2);

            match res {
            // The WINNER INVARIANT only applies when there is a conflict and one operation wins,
            // so if there is no conflict, there's not much to test.
                TransformResult::NoConflict => return Ok(()),
                TransformResult::Redundant => return Ok(()),
                // Swap the ops so that op1 always wins
                TransformResult::Op2Wins => {
                    (op1, op2) = (op2, op1);
                }
                _ => {},
            }
            
            // Apply just op1.
            let mut ops1 = Operations::new();
            let mut db1 = TaskDb::new(Box::new(InMemoryStorage::new()));
            ops1.push(preop1.clone().into_op());
            ops1.push(preop2.clone().into_op());
            ops1.push(op1.clone().into_op());

            // Apply op2 followed by the winning op1.
            let mut ops2 = Operations::new();
            let mut db2 = TaskDb::new(Box::new(InMemoryStorage::new()));
            ops2.push(preop1.into_op());
            ops2.push(preop2.into_op());
            ops2.push(op2.into_op());
            ops2.push(op1.into_op());

            db1.commit_operations(ops1, |_| false).unwrap();
            db2.commit_operations(ops2, |_| false).unwrap();

            assert_eq!(db1.sorted_tasks(), db2.sorted_tasks());
        }
    }

    #[test]
    fn test_from_op_create() {
        let uuid = Uuid::new_v4();
        assert_eq!(
            SyncOp::from_op(Operation::Create { uuid }),
            Some(SyncOp::Create { uuid })
        );
    }

    #[test]
    fn test_from_op_delete() {
        let uuid = Uuid::new_v4();
        assert_eq!(
            SyncOp::from_op(Operation::Delete {
                uuid,
                old_task: TaskMap::new()
            }),
            Some(SyncOp::Delete { uuid })
        );
    }

    #[test]
    fn test_from_op_update() {
        let uuid = Uuid::new_v4();
        let timestamp = Utc::now();
        assert_eq!(
            SyncOp::from_op(Operation::Update {
                uuid,
                property: "prop".into(),
                old_value: Some("foo".into()),
                value: Some("v".into()),
                timestamp,
            }),
            Some(SyncOp::Update {
                uuid,
                property: "prop".into(),
                value: Some("v".into()),
                timestamp,
            })
        );
    }

    #[test]
    fn test_from_op_undo_point() {
        assert_eq!(SyncOp::from_op(Operation::UndoPoint), None);
    }
}
