open Http;

open Responses;

let views = ((req, res)) =>
  switch (Request.url(req)) {
  | "/offices" when Request.isMethod(req, "GET") =>
    Response.(res |> jsonify(officesToJs({status: 200, data: [||]})))
  | "/offices" when Request.isMethod(req, "POST") =>
    let data = ref("");
    Request.(req->on(`data(value => data := data^ ++ value)));

    Request.(req->on(`end_(_ => print_string(data^))));

    Response.(res |> jsonify({"status": 200, "message": "Data received"}));

  | route => Response.(res |> end_(route))
  };