open TestFramework;
open ReAirtable.Internals;

let createResponse = statusCode => {
  let response =
    Cohttp.Response.make(~status=Cohttp.Code.status_of_code(statusCode), ());
  let body = Cohttp_lwt.Body.of_string("");
  Lwt.return((response, body));
};

describe("Response Tests", ({test, _}) => {
  test("Response w/ a 200 code calls onSuccess correctly", ({expect, _}) => {
    let mockOnSuccess = Mock.mock1(_ => ignore());

    createResponse(200)
    |> Response.parse(~onSuccess=Some(Mock.fn(mockOnSuccess)))
    |> ignore;

    expect.mock(mockOnSuccess).toBeCalled();
  });

  test("Response w/ a 4XX code calls onError correctly", ({expect, _}) => {
    let mockOnError = Mock.mock1(_ => ignore());

    createResponse(404)
    |> Response.parse(~onError=Some(Mock.fn(mockOnError)))
    |> ignore;

    expect.mock(mockOnError).toBeCalled();
  });

  test("Response w/ a 4XX code does not call onSuccess", ({expect, _}) => {
    let mockOnError = Mock.mock1(_ => ignore());
    let mockOnSuccess = Mock.mock1(_ => ignore());

    createResponse(404)
    |> Response.parse(
         ~onError=Some(Mock.fn(mockOnError)),
         ~onSuccess=Some(Mock.fn(mockOnSuccess)),
       )
    |> ignore;

    expect.mock(mockOnSuccess).toBeCalledTimes(0);
  });

  test("Response w/ a 200 code does not call onError", ({expect, _}) => {
    let mockOnError = Mock.mock1(_ => ignore());
    let mockOnSuccess = Mock.mock1(_ => ignore());

    createResponse(200)
    |> Response.parse(
         ~onError=Some(Mock.fn(mockOnError)),
         ~onSuccess=Some(Mock.fn(mockOnSuccess)),
       )
    |> ignore;

    expect.mock(mockOnError).toBeCalledTimes(0);
  });
});