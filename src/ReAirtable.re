type t = {
  apiKey: string,
  baseId: string,
  tableName: string,
};

let make = (~apiKey, ~baseId, ~tableName) => {apiKey, baseId, tableName};

let defaultListConfig = ListRecords.defaultConfig;
let list = (~listConfig, ~onSuccess=None, ~onError=None, airtable) => {
  listConfig
  |> ListRecords.make(~baseId=airtable.baseId, ~tableName=airtable.tableName)
  |> Base.get(~apiKey=airtable.apiKey)
  |> Response.parse(~onSuccess, ~onError);
};

let retrieve = (~recordId, ~onSuccess=None, ~onError=None, airtable) => {
  recordId
  |> RetrieveRecord.make(
       ~baseId=airtable.baseId,
       ~tableName=airtable.tableName,
     )
  |> Base.get(~apiKey=airtable.apiKey)
  |> Response.parse(~onSuccess, ~onError);
};

let create = (~body, ~onSuccess=None, ~onError=None, airtable) => {
  Base.make(~baseId=airtable.baseId, ~tableName=airtable.tableName)
  |> Base.post(~body, ~apiKey=airtable.apiKey)
  |> Response.parse(~onSuccess, ~onError);
};

let update =
    (~body, ~destructive=false, ~onSuccess=None, ~onError=None, airtable) => {
  let table =
    Base.make(~baseId=airtable.baseId, ~tableName=airtable.tableName);
  destructive
    ? table
      |> Base.put(~body, ~apiKey=airtable.apiKey)
      |> Response.parse(~onSuccess, ~onError)
    : table
      |> Base.patch(~body, ~apiKey=airtable.apiKey)
      |> Response.parse(~onSuccess, ~onError);
};

let deleteOne = (~recordId, ~onSuccess=None, ~onError=None, airtable) => {
  recordId
  |> DeleteRecords.makeOne(
       ~baseId=airtable.baseId,
       ~tableName=airtable.tableName,
     )
  |> Base.delete(~apiKey=airtable.apiKey)
  |> Response.parse(~onSuccess, ~onError);
};

let deleteMany = (~recordIds, ~onSuccess=None, ~onError=None, airtable) => {
  recordIds
  |> DeleteRecords.makeMany(
       ~baseId=airtable.baseId,
       ~tableName=airtable.tableName,
     )
  |> Base.delete(~apiKey=airtable.apiKey)
  |> Response.parse(~onSuccess, ~onError);
};

module Internals = {
  module Base = Base;
  module DeleteRecords = DeleteRecords;
  module RetrieveRecord = RetrieveRecord;
  module ListRecords = ListRecords;
};