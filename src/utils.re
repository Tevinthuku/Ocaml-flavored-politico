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