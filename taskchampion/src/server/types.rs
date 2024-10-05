use crate::errors::Result;
use uuid::Uuid;

/// Versions are referred to with UUIDs.
pub type VersionId = Uuid;

/// The distinguished value for "no version"
pub const NIL_VERSION_ID: VersionId = Uuid::nil();

/// A segment in the history of this task database, in the form of a sequence of operations.  This
/// data is pre-encoded, and from the protocol level appears as a sequence of bytes.
pub type HistorySegment = Vec<u8>;

/// A snapshot of the state of the task database.  This is encoded by the taskdb implementation
/// and treated as a sequence of bytes by the server implementation.
pub type Snapshot = Vec<u8>;

/// AddVersionResult is the response type from [`crate::server::Server::add_version`].
#[derive(Debug, PartialEq, Eq)]
pub enum AddVersionResult {
    /// OK, version added with the given ID
    Ok(VersionId),
    /// Rejected; expected a version with the given parent version
    ExpectedParentVersion(VersionId),
}

/// SnapshotUrgency indicates how much the server would like this replica to send a snapshot.
#[derive(PartialEq, Debug, Clone, Copy, Eq, PartialOrd, Ord)]
pub enum SnapshotUrgency {
    /// Don't need a snapshot right now.
    None,
    /// A snapshot would be good, but can wait for other replicas to provide it.
    Low,
    /// A snapshot is needed right now.
    High,
}

/// A version as downloaded from the server
#[derive(Debug, PartialEq, Eq)]
pub enum GetVersionResult {
    /// No such version exists
    NoSuchVersion,

    /// The requested version
    Version {
        version_id: VersionId,
        parent_version_id: VersionId,
        history_segment: HistorySegment,
    },
}

/// A value implementing this trait can act as a server against which a replica can sync.
///
/// # Sealed
///
/// This trait is sealed, and cannot be ipmlemented outside of the `taskchampion` crate. This is to
/// allow development flexibility, and the decision may be reconsidered when the trait is more
/// stable.
pub trait Server: crate::private::Sealed {
    /// Add a new version.
    ///
    /// This must ensure that the new version is the only version with the given
    /// `parent_version_id`, and that all versions form a single parent-child chain. Inductively,
    /// this means that if there are any versions on the server, then `parent_version_id` must be
    /// the only version that does not already have a child.
    fn add_version(
        &mut self,
        parent_version_id: VersionId,
        history_segment: HistorySegment,
    ) -> Result<(AddVersionResult, SnapshotUrgency)>;

    /// Get the version with the given parent VersionId
    fn get_child_version(&mut self, parent_version_id: VersionId) -> Result<GetVersionResult>;

    /// Add a snapshot on the server
    fn add_snapshot(&mut self, version_id: VersionId, snapshot: Snapshot) -> Result<()>;

    fn get_snapshot(&mut self) -> Result<Option<(VersionId, Snapshot)>>;
}
