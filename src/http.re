type http;

open Utils;

module Request = {
  type t;
  [@bs.get] external url: t => string = "";
  [@bs.get] external method_: t => string = "method";

  [@bs.send]
  external on:
    (
      t,
      [@bs.string] [
        | [@bs.as "end"] `end_(unit => unit)
        | `data(string => unit)
      ]
    ) =>
    unit =
    "";
  let isMethod = (request, meth) => method(request) == meth;
};

module Response = {
  type t;
  [@bs.send.pipe: t] external end_: 'a => unit = "end";
  [@bs.send] external setHeader: (t, string, string) => unit = "";
  [@bs.send] external writeHead: (t, int) => unit = "";
  let setHeader = (header: string, value: string, response: t) => {
    setHeader(response, header, value);
    response;
  };

  let writeHead = (status: int, response: t) => {
    writeHead(response, status);
    response;
  };
  let jsonify = (status, value: 'a, response: t) =>
    response
    |> setHeader("Content-Type", "application/json")
    |> writeHead(status)
    |> end_(stringify(value));
};

[@bs.module "http"]
external createServer: ((Request.t, Response.t) => unit) => http = "";

[@bs.send.pipe: http] external listen: int => unit = "";

[@bs.module "url"] external parse: (string, bool) => string = "";