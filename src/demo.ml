

let () = Js.log "Hello, There world

let sum lst = 
    let rec aux acc  = function
    | [] -> acc
    | x::tl -> aux (acc+x) tl in
    aux 0 lst