open TestFramework;
open ReAirtable.Internals;

describe("API Tests", ({test, _}) => {
  test("Base URI to be constructed correctly", ({expect, _}) => {
    let uri =
      Base.make(~baseId="A8RV94E0yd3KCjTo", ~tableName="Base Test Table")
      |> Uri.to_string;

    expect.string(uri).toEqual(
      "https://api.airtable.com/v0/A8RV94E0yd3KCjTo/Base%20Test%20Table",
    );
  });

  test("Retrieve URI to be constructed correctly", ({expect, _}) => {
    let uri =
      "j49KiEUEage7ZIjw"
      |> RetrieveRecord.make(
           ~baseId="A8RV94E0yd3KCjTo",
           ~tableName="Retrieve Test Table",
         )
      |> Uri.to_string;
    expect.string(uri).toEqual(
      "https://api.airtable.com/v0/A8RV94E0yd3KCjTo/Retrieve%20Test%20Table/j49KiEUEage7ZIjw",
    );
  });

  test("List URI to be constructed correctly", ({expect, _}) => {
    let uri =
      {
        ...ListRecords.defaultConfig,
        maxRecords: Some("10"),
        fields: Some(["field 1", "field 2"]),
      }
      |> ListRecords.make(
           ~baseId="A8RV94E0yd3KCjTo",
           ~tableName="List Test Table",
         )
      |> Uri.to_string;
    expect.string(uri).toEqual(
      "https://api.airtable.com/v0/A8RV94E0yd3KCjTo/List%20Test%20Table?fields=field%201&fields=field%202&maxRecords=10",
    );
  });

  test("Delete URI to be constructed correctly", ({expect, _}) => {
    let uri =
      ["j49KiEUEage7ZIjw", "d12GMdqR9ew321O1"]
      |> DeleteRecords.makeMany(
           ~baseId="A8RV94E0yd3KCjTo",
           ~tableName="Delete Test Table",
         )
      |> Uri.to_string;
    expect.string(uri).toEqual(
      "https://api.airtable.com/v0/A8RV94E0yd3KCjTo/Delete%20Test%20Table?records%5B%5D=j49KiEUEage7ZIjw&records%5B%5D=d12GMdqR9ew321O1",
    );
  });
});