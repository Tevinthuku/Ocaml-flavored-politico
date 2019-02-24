type http
module Response :
  sig type t external end_ : string -> t -> unit = "end" "BS-EXTERNAL" end
external createServer : (string -> Response.t -> unit) -> http = ""
  "BS-EXTERNAL"
external listen : int -> http -> unit = "" "BS-EXTERNAL"
