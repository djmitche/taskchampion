////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2006 - 2018, Paul Beckingham, Federico Hernandez.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// http://www.opensource.org/licenses/mit-license.php
//
////////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_STRINGS
#define INCLUDED_STRINGS

// columns/Col*
#define STRING_COLUMN_LABEL_DESC     "Description"
#define STRING_COLUMN_LABEL_DUE      "Due"
#define STRING_COLUMN_LABEL_END      "End"
#define STRING_COLUMN_LABEL_ENTERED  "Entered"
#define STRING_COLUMN_LABEL_COUNT    "Count"
#define STRING_COLUMN_LABEL_COMPLETE "Completed"
#define STRING_COLUMN_LABEL_MOD      "Modified"
#define STRING_COLUMN_LABEL_ADDED    "Added"
#define STRING_COLUMN_LABEL_AGE      "Age"
#define STRING_COLUMN_LABEL_PROJECT  "Project"
#define STRING_COLUMN_LABEL_UNTIL    "Until"
#define STRING_COLUMN_LABEL_WAIT     "Wait"
#define STRING_COLUMN_LABEL_WAITING  "Waiting until"
#define STRING_COLUMN_LABEL_RECUR    "Recur"
#define STRING_COLUMN_LABEL_RECUR_L  "Recurrence"
#define STRING_COLUMN_LABEL_START    "Start"
#define STRING_COLUMN_LABEL_STARTED  "Started"
#define STRING_COLUMN_LABEL_ACTIVE   "A"
#define STRING_COLUMN_LABEL_STATUS   "Status"
#define STRING_COLUMN_LABEL_STAT     "St"
#define STRING_COLUMN_LABEL_STAT_PE  "Pending"
#define STRING_COLUMN_LABEL_STAT_CO  "Completed"
#define STRING_COLUMN_LABEL_STAT_DE  "Deleted"
#define STRING_COLUMN_LABEL_STAT_WA  "Waiting"
#define STRING_COLUMN_LABEL_STAT_RE  "Recurring"
#define STRING_COLUMN_LABEL_STAT_P   "P"
#define STRING_COLUMN_LABEL_STAT_C   "C"
#define STRING_COLUMN_LABEL_STAT_D   "D"
#define STRING_COLUMN_LABEL_STAT_W   "W"
#define STRING_COLUMN_LABEL_STAT_R   "R"
#define STRING_COLUMN_LABEL_TAGS     "Tags"
#define STRING_COLUMN_LABEL_TAG      "Tag"
#define STRING_COLUMN_LABEL_UUID     "UUID"
#define STRING_COLUMN_LABEL_URGENCY  "Urgency"
#define STRING_COLUMN_LABEL_NAME     "Name"
#define STRING_COLUMN_LABEL_VALUE    "Value"
#define STRING_COLUMN_LABEL_DATE     "Date"
#define STRING_COLUMN_LABEL_COLUMN   "Columns"
#define STRING_COLUMN_LABEL_STYLES   "Supported Formats"
#define STRING_COLUMN_LABEL_EXAMPLES "Example"
#define STRING_COLUMN_LABEL_SCHED    "Scheduled"
#define STRING_COLUMN_LABEL_UDA      "Name"
#define STRING_COLUMN_LABEL_TYPE     "Type"
#define STRING_COLUMN_LABEL_MODIFY   "Modifiable"
#define STRING_COLUMN_LABEL_NOMODIFY "Read Only"
#define STRING_COLUMN_LABEL_LABEL    "Label"
#define STRING_COLUMN_LABEL_DEFAULT  "Default"
#define STRING_COLUMN_LABEL_VALUES   "Allowed Values"
#define STRING_COLUMN_LABEL_UDACOUNT "Usage Count"
#define STRING_COLUMN_LABEL_ORPHAN   "Orphan UDA"

#define STRING_COLUMN_LABEL_COMMAND  "Command"
#define STRING_COLUMN_LABEL_CATEGORY "Category"
#define STRING_COLUMN_LABEL_RO       "R/W"
#define STRING_COLUMN_LABEL_SHOWS_ID "ID"
#define STRING_COLUMN_LABEL_GC       "GC"
#define STRING_COLUMN_LABEL_CONTEXT  "Context"
#define STRING_COLUMN_LABEL_FILTER   "Filter"
#define STRING_COLUMN_LABEL_MODS     "Mods"
#define STRING_COLUMN_LABEL_MISC     "Misc"

// Column Examples
#define STRING_COLUMN_EXAMPLES_TAGS  "home @chore next"
#define STRING_COLUMN_EXAMPLES_PROJ  "home.garden"
#define STRING_COLUMN_EXAMPLES_PAR   "home"
#define STRING_COLUMN_EXAMPLES_IND   "  home.garden"
#define STRING_COLUMN_EXAMPLES_DESC  "Move your clothes down on to the lower peg"
#define STRING_COLUMN_EXAMPLES_ANNO1 "Immediately before your lunch"
#define STRING_COLUMN_EXAMPLES_ANNO2 "If you are playing in the match this afternoon"
#define STRING_COLUMN_EXAMPLES_ANNO3 "Before you write your letter home"
#define STRING_COLUMN_EXAMPLES_ANNO4 "If you're not getting your hair cut"

// commands/Cmd*
// USAGE strings are visible in 'task help'
#define STRING_CMD_VERSION_USAGE     "taskwarrior バージョン番号の表示"
#define STRING_CMD_VERSION_USAGE2    "taskwarrior バージョン番号のみの表示"
#define STRING_CMD_VERSION_DOCS      "taskwarrior のドキュメントは 'man task', 'man taskrc', 'man task-color', 'man task-sync' あるいは http://taskwarrior.org にあります。"
#define STRING_CMD_VERSION_UNKNOWN   "unknown"
#define STRING_CMD_EXEC_USAGE        "外部コマンドまたはスクリプトの実行"
#define STRING_CMD_URGENCY_USAGE     "Displays the urgency measure of a task"
#define STRING_CMD_URGENCY_RESULT    "task {1} urgency {2}"
#define STRING_CMD_ADD_USAGE         "新しいタスクの追加"
#define STRING_CMD_ADD_FEEDBACK      "タスク {1} が生成されました。"
#define STRING_CMD_ADD_RECUR         "Created task {1} (recurrence template)."
#define STRING_CMD_LOG_USAGE         "Adds a new task that is already completed"
#define STRING_CMD_LOG_NO_RECUR      "You cannot log recurring tasks."
#define STRING_CMD_LOG_NO_WAITING    "保留のタスクはログできません。"

//#define STRING_CMD_LOG_LOGGED        "Logged task {1}."
#define STRING_CMD_LOG_LOGGED        "Logged task {1}."

#define STRING_CMD_IDS_USAGE_RANGE   "Shows the IDs of matching tasks, as a range"
#define STRING_CMD_IDS_USAGE_LIST    "Shows the IDs of matching tasks, in the form of a list"
#define STRING_CMD_IDS_USAGE_ZSH     "Shows the IDs and descriptions of matching tasks"
#define STRING_CMD_UDAS_USAGE        "Shows all the defined UDA details"
#define STRING_CMD_UDAS_COMPL_USAGE  "Shows the defined UDAs for completion purposes"
#define STRING_CMD_UUIDS_USAGE_RANGE "Shows the UUIDs of matching tasks, as a comma-separated list"
#define STRING_CMD_UUIDS_USAGE_LIST  "Shows the UUIDs of matching tasks, as a list"
#define STRING_CMD_UUIDS_USAGE_ZSH   "Shows the UUIDs and descriptions of matching tasks"
#define STRING_CMD_INFO_USAGE        "すべてのデータとメタデータを表示"
#define STRING_CMD_INFO_BLOCKED      "This task blocked by"
#define STRING_CMD_INFO_BLOCKING     "This task is blocking"
#define STRING_CMD_INFO_UNTIL        "Until"
#define STRING_CMD_INFO_MODIFICATION "Modification"
#define STRING_CMD_INFO_MODIFIED     "Last modified"
#define STRING_CMD_INFO_VIRTUAL_TAGS "Virtual tags"
#define STRING_CMD_UNDO_USAGE        "Reverts the most recent change to a task"
#define STRING_CMD_STATS_USAGE       "タスク データベース情報を表示"
#define STRING_CMD_STATS_CATEGORY    "Category"
#define STRING_CMD_STATS_DATA        "Data"
#define STRING_CMD_STATS_TOTAL       "Total"
#define STRING_CMD_STATS_ANNOTATIONS "Annotations"
#define STRING_CMD_STATS_UNIQUE_TAGS "Unique tags"
#define STRING_CMD_STATS_PROJECTS    "Projects"
#define STRING_CMD_STATS_DATA_SIZE   "Data size"
#define STRING_CMD_STATS_UNDO_TXNS   "Undo transactions"
#define STRING_CMD_STATS_BACKLOG     "Sync backlog transactions"
#define STRING_CMD_STATS_TAGGED      "Tasks tagged"
#define STRING_CMD_STATS_OLDEST      "最古の タスク"
#define STRING_CMD_STATS_NEWEST      "最新の タスク"
#define STRING_CMD_STATS_USED_FOR    "Task used for"
#define STRING_CMD_STATS_ADD_EVERY   "Task added every"
#define STRING_CMD_STATS_COMP_EVERY  "Task completed every"
#define STRING_CMD_STATS_DEL_EVERY   "Task deleted every"
#define STRING_CMD_STATS_AVG_PEND    "Average time pending"
#define STRING_CMD_STATS_DESC_LEN    "Average desc length"
#define STRING_CMD_STATS_CHARS       "{1} 文字"
#define STRING_CMD_STATS_BLOCKED     "ブロックされたタスク"
#define STRING_CMD_STATS_BLOCKING    "Blocking tasks"
#define STRING_CMD_REPORTS_USAGE     "Lists all supported reports"
#define STRING_CMD_REPORTS_REPORT    "Report"
#define STRING_CMD_REPORTS_DESC      "Description"
#define STRING_CMD_REPORTS_SUMMARY   "{1} reports"
#define STRING_CMD_TAGS_USAGE        "使用されているすべてのタグを表示"
#define STRING_CMD_COMTAGS_USAGE     "Shows only a list of all tags used, for autocompletion purposes"
#define STRING_CMD_TAGS_SINGLE       "1 つのタグ"
#define STRING_CMD_TAGS_PLURAL       "{1} 個のタグ"
#define STRING_CMD_TAGS_NO_TAGS      "タグがない。"
#define STRING_CMD_HISTORY_USAGE_D   "Shows a report of task history, by day"
#define STRING_CMD_HISTORY_USAGE_W   "Shows a report of task history, by week"
#define STRING_CMD_HISTORY_DAY       "Day"
#define STRING_CMD_GHISTORY_USAGE_D  "Shows a graphical report of task history, by day"
#define STRING_CMD_GHISTORY_USAGE_W  "Shows a graphical report of task history, by week"
#define STRING_CMD_GHISTORY_USAGE_D  "Shows a graphical report of task history, by day"
#define STRING_CMD_GHISTORY_USAGE_W  "Shows a graphical report of task history, by week"
#define STRING_CMD_GHISTORY_DAY      "Day"
#define STRING_CMD_HISTORY_USAGE_M   "Shows a report of task history, by month"
#define STRING_CMD_HISTORY_YEAR      "Year"
#define STRING_CMD_HISTORY_MONTH     "Month"
#define STRING_CMD_HISTORY_ADDED     "Added"
#define STRING_CMD_HISTORY_COMP      "Completed"
#define STRING_CMD_HISTORY_DEL       "Deleted"
#define STRING_CMD_HISTORY_NET       "Net"
#define STRING_CMD_HISTORY_USAGE_A   "Shows a report of task history, by year"
#define STRING_CMD_HISTORY_AVERAGE   "Average"
#define STRING_CMD_HISTORY_LEGEND    "Legend: {1}, {2}, {3}"
#define STRING_CMD_HISTORY_LEGEND_A  "Legend: + Added, X Completed, - Deleted"
#define STRING_CMD_GHISTORY_USAGE_M  "Shows a graphical report of task history, by month"
#define STRING_CMD_GHISTORY_USAGE_A  "Shows a graphical report of task history, by year"
#define STRING_CMD_GHISTORY_YEAR     "Year"
#define STRING_CMD_GHISTORY_MONTH    "Month"
#define STRING_CMD_GHISTORY_NUMBER   "追加/完了/削除されたタスク数"
#define STRING_CMD_UNIQUE_USAGE      "Generates lists of unique attribute values"
#define STRING_CMD_UNIQUE_MISSING    "An attribute must be specified.  See 'task _columns'."
#define STRING_CMD_UNIQUE_VALID      "You must specify an attribute or UDA."

#define STRING_CMD_PROJECTS_USAGE    "Shows all project names used"
#define STRING_CMD_PROJECTS_USAGE_2  "Shows only a list of all project names used"
#define STRING_CMD_PROJECTS_NO       "プロジェクトがない。"
#define STRING_CMD_PROJECTS_NONE     "(none)"
#define STRING_CMD_PROJECTS_SUMMARY  "{1} プロジェクト"
#define STRING_CMD_PROJECTS_SUMMARY2 "{1} プロジェクト"
#define STRING_CMD_PROJECTS_TASK     "({1} タスク)"
#define STRING_CMD_PROJECTS_TASKS    "({1} タスク)"
#define STRING_CMD_COUNT_USAGE       "一致した タスク をカウント"

#define STRING_CMD_PURGE_USAGE       "Removes the specified tasks from the data files. Causes permanent loss of data."
#define STRING_CMD_PURGE_ABRT        "Purge operation aborted."
#define STRING_CMD_PURGE_1           "Purged {1} task."
#define STRING_CMD_PURGE_N           "Purged {1} tasks."
#define STRING_CMD_PURGE_CONFIRM     "Permanently remove task {1} '{2}'?"
#define STRING_CMD_PURGE_CONFIRM_R   "Task '{1}' is a recurrence template. All its {2} deleted children tasks will be purged as well. Continue?"
#define STRING_CMD_PURGE_NDEL_CHILD  "Task '{1}' is a recurrence template. Its child task {2} must be deleted before it can be purged."

#define STRING_CMD_APPEND_USAGE      "存在する task 説明文にテキストを追加"
#define STRING_CMD_APPEND_1          "{1} タスク を追加。"
#define STRING_CMD_APPEND_N          "{1} タスク を追加。"
#define STRING_CMD_APPEND_TASK       "タスク {1} '{2}' を追加中。"
#define STRING_CMD_APPEND_TASK_R     "Appending to recurring task {1} '{2}'."
#define STRING_CMD_APPEND_CONFIRM_R  "This is a recurring task.  Do you want to append to all pending recurrences of this same task?"
#define STRING_CMD_APPEND_CONFIRM    "タスク {1} '{2}' を追加?"
#define STRING_CMD_APPEND_NO         "タスク を追加できませんでした。"

#define STRING_CMD_PREPEND_USAGE     "Prepends text to an existing task description"
#define STRING_CMD_PREPEND_1         "Prepended {1} task."
#define STRING_CMD_PREPEND_N         "Prepended {1} tasks."
#define STRING_CMD_PREPEND_TASK      "Prepending to task {1} '{2}'."
#define STRING_CMD_PREPEND_TASK_R    "Prepending to recurring task {1} '{2}'."
#define STRING_CMD_PREPEND_CONFIRM_R "This is a recurring task.  Do you want to prepend to all pending recurrences of this same task?"
#define STRING_CMD_PREPEND_CONFIRM   "Prepend to task {1} '{2}'?"
#define STRING_CMD_PREPEND_NO        "Task not prepended."

#define STRING_CMD_ANNO_USAGE        "既存のタスクに注釈を追加"
#define STRING_CMD_ANNO_CONFIRM      "Annotate task {1} '{2}'?"
#define STRING_CMD_ANNO_TASK         "タスク{1} に注釈 '{2}' を追加"
#define STRING_CMD_ANNO_TASK_R       "Annotating recurring task {1} '{2}'."
#define STRING_CMD_ANNO_CONFIRM_R    "This is a recurring task.  Do you want to annotate all pending recurrences of this same task?"
#define STRING_CMD_ANNO_NO           "Task not annotated."
#define STRING_CMD_ANNO_1            "{1} task に注釈付加."
#define STRING_CMD_ANNO_N            "{1} task に注釈付加."

#define STRING_CMD_DENO_USAGE        "Deletes an annotation"
#define STRING_CMD_DENO_NONE         "指定されたtaskには注釈がないので削除できません。"
#define STRING_CMD_DENO_CONFIRM      "タスク {1} から注釈 '{2}' を削除しますか?"
#define STRING_CMD_DENO_FOUND        "注釈 '{1}' が見つかったので削除します。"
#define STRING_CMD_DENO_NOMATCH      "'{1}' に一致する注釈が見つからなかったので削除できません。"
#define STRING_CMD_DENO_NO           "Task not denotated."
#define STRING_CMD_DENO_1            "Denotated {1} task."
#define STRING_CMD_DENO_N            "Denotated {1} tasks."

#define STRING_CMD_IMPORT_USAGE      "JSON ファイルをインポート"
#define STRING_CMD_IMPORT_SUMMARY    "{1} task をインポートしました。"
#define STRING_CMD_IMPORT_FILE       "'{1}' をインポート中"
#define STRING_CMD_IMPORT_MISSING    "ファイル '{1}' が見つかりません。"
#define STRING_CMD_IMPORT_UUID_BAD   "Not a valid UUID '{1}'."
#define STRING_TASK_NO_DESC          "Annotation is missing a description: {1}"
#define STRING_TASK_NO_ENTRY         "Annotation is missing an entry date: {1}"

#define STRING_CMD_COMMANDS_USAGE    "Generates a list of all commands, with behavior details"
#define STRING_CMD_HCOMMANDS_USAGE   "Generates a list of all commands, for autocompletion purposes"
#define STRING_CMD_ZSHCOMMANDS_USAGE "Generates a list of all commands, for zsh autocompletion purposes"
#define STRING_CMD_ZSHATTS_USAGE     "Generates a list of all attributes, for zsh autocompletion purposes"
#define STRING_CMD_ALIASES_USAGE     "Generates a list of all aliases, for autocompletion purposes"

#define STRING_CMD_COLOR_USAGE       "All colors, a sample, or a legend"
#define STRING_CMD_COLOR_HERE        "Here are the colors currently in use:"
#define STRING_CMD_COLOR_COLOR       "Color"
#define STRING_CMD_COLOR_DEFINITION  "Definition"
#define STRING_CMD_COLOR_EXPLANATION "Use this command to see how colors are displayed by your terminal."
#define STRING_CMD_COLOR_16          "16-color usage (supports underline, bold text, bright background):"
#define STRING_CMD_COLOR_256         "256-color usage (supports underline):"
#define STRING_CMD_COLOR_YOURS       "Your sample:"
#define STRING_CMD_COLOR_BASIC       "Basic colors"
#define STRING_CMD_COLOR_EFFECTS     "Effects"
#define STRING_CMD_COLOR_CUBE        "Color cube rgb"
#define STRING_CMD_COLOR_RAMP        "Gray ramp"
#define STRING_CMD_COLOR_TRY         "Try running '{1}'."
#define STRING_CMD_COLOR_OFF         "Color is currently turned off in your .taskrc file.  To enable color, remove the line 'color=off', or change the 'off' to 'on'."
#define STRING_CMD_CONFIG_USAGE      "Change settings in the task configuration"
#define STRING_CMD_CONFIG_CONFIRM    "Are you sure you want to change the value of '{1}' from '{2}' to '{3}'?"
#define STRING_CMD_CONFIG_CONFIRM2   "Are you sure you want to add '{1}' with a value of '{2}'?"
#define STRING_CMD_CONFIG_CONFIRM3   "Are you sure you want to remove '{1}'?"
#define STRING_CMD_CONFIG_NO_ENTRY   "No entry named '{1}' found."
#define STRING_CMD_CONFIG_FILE_MOD   "Config file {1} modified."
#define STRING_CMD_CONFIG_NO_NAME    "Specify the name of a config variable to modify."
#define STRING_CMD_HCONFIG_USAGE     "Lists all supported configuration variables, for completion purposes"
#define STRING_CMD_CONTEXT_USAGE     "Set and define contexts (default filters)"
#define STRING_CMD_CONTEXT_DEF_SUCC  "Context '{1}' defined. Use 'task context {1}' to activate."
#define STRING_CMD_CONTEXT_DEF_FAIL  "Context '{1}' not defined."
#define STRING_CMD_CONTEXT_DEF_USAG  "Both context name and its definition must be provided."
#define STRING_CMD_CONTEXT_DEF_ABRT  "Context definiton aborted."
#define STRING_CMD_CONTEXT_DEF_ABRT2 "Filter validation failed: {1}"
#define STRING_CMD_CONTEXT_DEF_CONF  "The filter '{1}' matches 0 pending tasks. Do you wish to continue?"
#define STRING_CMD_CONTEXT_DEF_INVLD "The name '{1}' is reserved and not allowed to use as a context name."
#define STRING_CMD_CONTEXT_DEL_SUCC  "Context '{1}' deleted."
#define STRING_CMD_CONTEXT_DEL_FAIL  "Context '{1}' not deleted."
#define STRING_CMD_CONTEXT_DEL_USAG  "Context name needs to be specified."
#define STRING_CMD_CONTEXT_LIST_EMPT "No contexts defined."
#define STRING_CMD_CONTEXT_SET_NFOU  "Context '{1}' not found."
#define STRING_CMD_CONTEXT_SET_SUCC  "Context '{1}' set. Use 'task context none' to remove."
#define STRING_CMD_CONTEXT_SET_FAIL  "Context '{1}' not applied."
#define STRING_CMD_CONTEXT_SHOW_EMPT "No context is currently applied."
#define STRING_CMD_CONTEXT_SHOW      "Context '{1}' with filter '{2}' is currently applied."
#define STRING_CMD_CONTEXT_NON_SUCC  "Context unset."
#define STRING_CMD_CONTEXT_NON_FAIL  "Context not unset."
#define STRING_CMD_HCONTEXT_USAGE    "Lists all supported contexts, for completion purposes"
#define STRING_CMD_CUSTOM_MISMATCH   "There are different numbers of columns and labels for report '{1}'."
#define STRING_CMD_CUSTOM_SHOWN      "{1} shown"
#define STRING_CMD_CUSTOM_COUNT      "1 task"
#define STRING_CMD_CUSTOM_COUNTN     "{1} tasks"
#define STRING_CMD_CUSTOM_TRUNCATED  "truncated to {1} lines"
#define STRING_CMD_TIMESHEET_USAGE   "Summary of completed and started tasks"
#define STRING_CMD_TIMESHEET_STARTED "Started ({1} tasks)"
#define STRING_CMD_TIMESHEET_DONE    "Completed ({1} tasks)"
#define STRING_CMD_CAL_USAGE         "Shows a calendar, with due tasks marked"
#define STRING_CMD_CAL_BAD_MONTH     "引数 '{1}' は正しい月ではありません。"
#define STRING_CMD_CAL_BAD_ARG       "引数'{1}' を認識できません。"
#define STRING_CMD_CAL_LABEL_DATE    "Date"
#define STRING_CMD_CAL_LABEL_HOL     "Holiday"
#define STRING_CMD_CAL_SUN_MON       "'weekstart' 設定変数は 'Sunday' または 'Monday' のみが使えます。"
#define STRING_CMD_CALC_USAGE        "電卓"

// Feedback
#define STRING_FEEDBACK_NO_TASKS     "タスクがない。"
#define STRING_FEEDBACK_NO_TASKS_SP  "タスクが1つも指定されていません。"
#define STRING_FEEDBACK_NO_MATCH     "一致したものはありません。"
#define STRING_FEEDBACK_TASKS_SINGLE "(1 タスク)"
#define STRING_FEEDBACK_TASKS_PLURAL "({1} タスク)"
#define STRING_FEEDBACK_DELETED      "{1} will be deleted."
#define STRING_FEEDBACK_DEP_SET      "Dependencies will be set to '{1}'."
#define STRING_FEEDBACK_DEP_MOD      "Dependencies will be changed from '{1}' to '{2}'."
#define STRING_FEEDBACK_DEP_DEL      "Dependencies '{1}' deleted."
#define STRING_FEEDBACK_DEP_WAS_SET  "Dependencies set to '{1}'."
#define STRING_FEEDBACK_DEP_WAS_MOD  "Dependencies changed from '{1}' to '{2}'."
#define STRING_FEEDBACK_ATT_SET      "{1} will be set to '{2}'."
#define STRING_FEEDBACK_ATT_MOD      "{1} will be changed from '{2}' to '{3}'."
#define STRING_FEEDBACK_ATT_DEL      "{1} deleted."
#define STRING_FEEDBACK_ATT_DEL_DUR  "{1} deleted (duration: {2})."
#define STRING_FEEDBACK_ATT_WAS_SET  "{1} set to '{2}'."
#define STRING_FEEDBACK_ATT_WAS_MOD  "{1} changed from '{2}' to '{3}'."
#define STRING_FEEDBACK_ANN_ADD      "Annotation of '{1}' added."
#define STRING_FEEDBACK_ANN_DEL      "Annotation '{1}' deleted."
#define STRING_FEEDBACK_ANN_WAS_MOD  "Annotation changed to '{1}'."
#define STRING_FEEDBACK_NOP          "No changes will be made."
#define STRING_FEEDBACK_WAS_NOP      "No changes made."
#define STRING_FEEDBACK_TAG_NOCOLOR  "The 'nocolor' special tag will disable color rules for this task."
#define STRING_FEEDBACK_TAG_NONAG    "The 'nonag' special tag will prevent nagging when this task is modified."
#define STRING_FEEDBACK_TAG_NOCAL    "The 'nocal' special tag will keep this task off the 'calendar' report."
#define STRING_FEEDBACK_TAG_NEXT     "The 'next' special tag will boost the urgency of this task so it appears on the 'next' report."
#define STRING_FEEDBACK_TAG_VIRTUAL  "Virtual tags (including '{1}') are reserved and may not be added or removed."
#define STRING_FEEDBACK_UNBLOCKED    "Unblocked {1} '{2}'."
#define STRING_FEEDBACK_EXPIRED      "Task {1} '{2}' expired and was deleted."
#define STRING_FEEDBACK_BACKLOG_N    "There are {1} local changes.  Sync required."
#define STRING_FEEDBACK_BACKLOG      "There is {1} local change.  Sync required."

// Task
#define STRING_TASK_NO_FF1           "Taskwarrior no longer supports file format 1, originally used between 27 November 2006 and 31 December 2007."
#define STRING_TASK_NO_FF2           "Taskwarrior no longer supports file format 2, originally used between 1 January 2008 and 12 April 2009."
#define STRING_TASK_NO_FF3           "Taskwarrior no longer supports file format 3, originally used between 23 March 2009 and 16 May 2009."
#define STRING_TASK_PARSE_UNREC_FF   "Unrecognized Taskwarrior file format or blank line in data."
#define STRING_TASK_DEPEND_ITSELF    "A task cannot be dependent on itself."
#define STRING_TASK_DEPEND_MISS_CREA "Could not create a dependency on task {1} - not found."
#define STRING_TASK_DEPEND_MISS_DEL  "Could not delete a dependency on task {1} - not found."
#define STRING_TASK_DEPEND_DUP       "Task {1} already depends on task {2}."
#define STRING_TASK_DEPEND_CIRCULAR  "Circular dependency detected and disallowed."
#define STRING_TASK_VALID_BLANK      "Cannot add a task that is blank."
#define STRING_TASK_VALID_BEFORE     "Warning: You have specified that the '{1}' date is after the '{2}' date."
#define STRING_TASK_VALID_REC_DUE    "A recurring task must also have a 'due' date."
#define STRING_TASK_SAFETY_VALVE     "This command has no filter, and will modify all (including completed and deleted) tasks.  Are you sure?"
#define STRING_TASK_SAFETY_FAIL      "コマンドの実行は中止された。"
#define STRING_TASK_SAFETY_ALLOW     "You did not specify a filter, and with the 'allow.empty.filter' value, no action is taken."
#define STRING_TASK_INVALID_COL_TYPE "Unrecognized column type '{1}' for column '{2}'"

#endif
