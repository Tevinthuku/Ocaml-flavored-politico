open Http;

open Responses;

open Utils;

let views = ((req, res)) =>
  switch (Request.url(req)) {
  | "/offices" when Request.method(req) == "GET" =>
    Response.(
      res
      |> setHeader("Content-Type", "application/json")
      |> end_(stringify(officesToJs({status: 200, data: [||]})))
    )
  | route => Response.(res |> end_(route))
  };