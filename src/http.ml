type http

module Request = struct
    type t
    external url : t -> string = "" [@@bs.get ]
    external method_ : t -> string = "method" [@@bs.get ]
    end

module Response = struct
    type t
    external end_ : 'a -> unit = "end" [@@bs.send.pipe :t]
    external setHeader :  t -> string -> string -> unit = "" [@@bs.send ]

    let setHeader (header : string) (value : string) (response : t) =
        setHeader response header value;
        response

    end


external createServer : (Request.t -> Response.t -> unit) -> http = "" [@@bs.module "http"]

external listen: int -> unit = "" [@@bs.send.pipe :http]


