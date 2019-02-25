type http;

module Request = {
  type t;
  [@bs.get] external url: t => string = "";
  [@bs.get] external method_: t => string = "method";
};

module Response = {
  type t;
  [@bs.send.pipe: t] external end_: 'a => unit = "end";
  [@bs.send] external setHeader: (t, string, string) => unit = "";
  let setHeader = (header: string, value: string, response: t) => {
    setHeader(response, header, value);
    response;
  };
};

[@bs.module "http"]
external createServer: ((Request.t, Response.t) => unit) => http = "";

[@bs.send.pipe: http] external listen: int => unit = "";