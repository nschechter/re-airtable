let makeOne = (~baseId, ~tableName, recordId) => {
  let uri = Base.make(~baseId, ~tableName);
  Uri.with_path(uri, Uri.path(uri) ++ "/" ++ recordId);
};

let makeMany = (~baseId, ~tableName, recordIds) => {
  let uri = Base.make(~baseId, ~tableName);
  recordIds
  |> List.map(val_ => ("records[]", [val_]))
  |> Uri.add_query_params(uri);
};