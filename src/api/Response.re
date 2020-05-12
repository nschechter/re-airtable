open Lwt;
open Cohttp;

let parse = (~onSuccess=None, ~onError=None, response) =>
  response
  >>= (
    ((resp, body)) => {
      let code = resp |> Response.status |> Code.code_of_status;
      switch (code) {
      | 200 =>
        switch (onSuccess) {
        | Some(onSuccess) => body |> Cohttp_lwt.Body.to_string |> onSuccess
        | None => ignore()
        }
      | _ =>
        switch (onError) {
        | Some(onError) => onError(body)
        | None => ignore()
        }
      };

      Lwt.return(code |> string_of_int);
    }
  );