open Http
open Responses

open Utils

let views (req, res) = 
    match(Request.url req) with
    | "/offices" when (Request.method_ req) = "GET" -> Response.(
         res
         |> setHeader "Content-Type" "application/json"
         |> end_ (stringify (officesToJs { status = 200; data= [||] }))
    )
    | route -> Response.(
        res |> end_  route
    )

