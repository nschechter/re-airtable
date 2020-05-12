let _BASE_URL = "https://api.airtable.com";
let _VERSION = "v0";

let make = (~baseId, ~tableName) =>
  Uri.of_string(
    _BASE_URL ++ "/" ++ _VERSION ++ "/" ++ baseId ++ "/" ++ tableName,
  );

let request = (~apiKey, uri) =>
  uri
  |> Cohttp_lwt_unix.Client.get(
       ~headers=Cohttp.Header.init_with("Authorization", "Bearer " ++ apiKey),
     );