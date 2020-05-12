let make = (~baseId, ~tableName, recordId) => {
  let uri = Base.make(~baseId, ~tableName);
  Uri.with_path(uri, Uri.path(uri) ++ "/" ++ recordId);
};