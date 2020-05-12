let _BASE_URL = "https://api.airtable.com";
let _VERSION = "v0";

let make = (~baseId, ~tableName) =>
  Uri.of_string(
    _BASE_URL ++ "/" ++ _VERSION ++ "/" ++ baseId ++ "/" ++ tableName,
  );

let get = (~apiKey, uri) =>
  uri
  |> Cohttp_lwt_unix.Client.get(
       ~headers=Cohttp.Header.init_with("Authorization", "Bearer " ++ apiKey),
     );

let post = (~apiKey, ~body="", uri) =>
  uri
  |> Cohttp_lwt_unix.Client.post(
       ~headers=
         Cohttp.Header.of_list([
           ("Authorization", "Bearer " ++ apiKey),
           ("Content-Type", "application/json"),
         ]),
       ~body=body |> Cohttp_lwt.Body.of_string,
     );

let put = (~apiKey, ~body="", uri) =>
  uri
  |> Cohttp_lwt_unix.Client.put(
       ~headers=
         Cohttp.Header.of_list([
           ("Authorization", "Bearer " ++ apiKey),
           ("Content-Type", "application/json"),
         ]),
       ~body=body |> Cohttp_lwt.Body.of_string,
     );

let patch = (~apiKey, ~body="", uri) =>
  uri
  |> Cohttp_lwt_unix.Client.patch(
       ~headers=
         Cohttp.Header.of_list([
           ("Authorization", "Bearer " ++ apiKey),
           ("Content-Type", "application/json"),
         ]),
       ~body=body |> Cohttp_lwt.Body.of_string,
     );

let delete = (~apiKey, uri) =>
  uri
  |> Cohttp_lwt_unix.Client.delete(
       ~headers=Cohttp.Header.init_with("Authorization", "Bearer " ++ apiKey),
     );