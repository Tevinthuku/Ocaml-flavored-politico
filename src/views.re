open Http;

open Utils;

let offices = ref([]);

let views = ((req, res)) =>
  switch (Request.url(req)) {
  | "/offices" when Request.isMethod(req, "GET") =>
    Response.(res |> jsonify(200, {"status": 200, "data": offices^}))
  | "/offices" when Request.isMethod(req, "POST") =>
    let data = ref("");
    Request.(
      req->on(`data(value => data := data^ ++ write(newdecoder, value)))
    );
    Request.(
      req
      ->on(
          `end_(
            _ =>
              switch (Js.Json.parseExn(data^)) {
              | value =>
                offices := List.append([value], offices^);
                Response.(
                  res
                  |> jsonify(
                       200,
                       {"status": 200, "message": "Data received"},
                     )
                );
              | exception _ =>
                Response.(
                  res
                  |> jsonify(400, {"status": 400, "message": "Bad request"})
                )
              },
          ),
        )
    );

  | route => Response.(res |> end_(route))
  };