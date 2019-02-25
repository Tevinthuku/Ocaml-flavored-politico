open Http
open Views


let _ = createServer (fun req -> fun res -> (
    
    views (req, res)
    
))
|> listen 3000