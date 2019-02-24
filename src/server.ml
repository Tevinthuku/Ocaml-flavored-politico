open Http

let _ = createServer (fun _req -> fun res -> (
    Response.(
        res |> end_ "Hello world"
    )
))
|> listen 3000