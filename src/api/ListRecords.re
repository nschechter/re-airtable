let appendQueryParam = (~query, ~val_, uri) => {
  switch (val_) {
  | Some(val_) => Uri.add_query_param(uri, (query, [val_]))
  | None => uri
  };
};

let appendQueryParams = (~query, ~values, uri) => {
  switch (values) {
  | Some(values) =>
    values |> List.map(val_ => (query, [val_])) |> Uri.add_query_params(uri)
  | None => uri
  };
};

type config = {
  maxRecords: option(string),
  view: option(string),
  cellFormat: option(string),
  timeZone: option(string),
  pageSize: option(string),
  userLocale: option(string),
  filterByFormula: option(string),
  fields: option(list(string)),
};

let defaultConfig = {
  maxRecords: None,
  view: None,
  cellFormat: None,
  timeZone: None,
  pageSize: None,
  userLocale: None,
  filterByFormula: None,
  fields: None,
};

let make = (~baseId, ~tableName, config) => {
  Base.make(~baseId, ~tableName)
  |> appendQueryParam(~query="maxRecords", ~val_=config.maxRecords)
  |> appendQueryParam(~query="pageSize", ~val_=config.pageSize)
  |> appendQueryParam(~query="view", ~val_=config.view)
  |> appendQueryParam(~query="cellFormat", ~val_=config.cellFormat)
  |> appendQueryParam(~query="timeZone", ~val_=config.timeZone)
  |> appendQueryParam(~query="userLocale", ~val_=config.userLocale)
  |> appendQueryParam(~query="filterByFormula", ~val_=config.filterByFormula)
  |> appendQueryParams(~query="fields", ~values=config.fields);
};