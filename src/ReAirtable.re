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
  |> Base.request(~apiKey=airtable.apiKey)
  |> Response.parse(~onSuccess, ~onError);
};

let retrieve = (~recordId, ~onSuccess=None, ~onError=None, airtable) => {
  recordId
  |> RetrieveRecord.make(
       ~baseId=airtable.baseId,
       ~tableName=airtable.tableName,
     )
  |> Base.request(~apiKey=airtable.apiKey)
  |> Response.parse(~onSuccess, ~onError);
};

module RetrieveRecord = RetrieveRecord;
module ListRecords = ListRecords;