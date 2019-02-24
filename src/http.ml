type http

module Response = struct
    type t
    external end_ : string -> unit = "end" [@@bs.send.pipe :t] end

external createServer : (string -> Response.t -> unit) -> http = "" [@@bs.module "http"]

external listen: int -> unit = "" [@@bs.send.pipe :http]

