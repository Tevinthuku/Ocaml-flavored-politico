[@bs.val] [@bs.scope "JSON"] external stringify: 'a => string = "";
[@bs.val] [@bs.scope "JSON"] external parse: 'a => string = "";

type decode;

[@bs.module "string_decoder"] [@bs.new]
external strDecode:
  ([@bs.string] [ | [@bs.as "utf-8"] `utf8 | [@bs.as "ascii"] `useAscii]) =>
  decode =
  "StringDecoder";

[@bs.send] external write: (decode, string) => string = "";

let newdecoder = strDecode(`utf8);

let replacepath: string => string = [%bs.raw
  {|
function (str) {
 return str.replace(/^\/+|\/+$/g, '');
}
|}
];

type result('a) =
  | Ok('a)
  | Error(string);

let getString = (a, prop) =>
  switch (Js.Dict.get(a, prop)) {
  | Some(value) =>
    switch (Js.Json.classify(value)) {
    | Js.Json.JSONString(value) => Ok(value)
    | _ => Error(prop ++ " is not a string")
    }
  | _ => Error("Please provide " ++ prop)
  };

let getInt = (a, prop) =>
  switch (Js.Dict.get(a, prop)) {
  | Some(value) =>
    switch (Js.Json.classify(value)) {
    | Js.Json.JSONNumber(value) => Ok(value)
    | _ => Error(prop ++ " is not a number")
    }
  | _ => Error("Please provide " ++ prop)
  };

let isRouteDynamic = (route, expect) =>
  switch (Js.String.split("/", route)) {
  | n when Array.length(n) > 1 && expect == n[0] => true
  | _ => false
  };

let getParam: string => string = [%bs.raw
  {|
    function (route) {
      return route.split("/")[1]
    }
  |}
];