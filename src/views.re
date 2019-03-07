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
                let myMap = Js.Dict.empty();

                switch (Js.Json.classify(value)) {
                | Js.Json.JSONObject(a) =>
                  switch (Js.Dict.get(a, "name")) {
                  | Some(name) => Js.Dict.set(myMap, "name", name)
                  | _ =>
                    Response.(
                      res
                      |> jsonify(
                           400,
                           {"status": 400, "message": "Name is not provided"},
                         )
                    )
                  };

                  switch (Js.Dict.get(a, "type")) {
                  | Some(type_) => Js.Dict.set(myMap, "type", type_)
                  | _ =>
                    Response.(
                      res
                      |> jsonify(
                           400,
                           {"status": 400, "message": "Type is not provided"},
                         )
                    )
                  };
                | _ =>
                  Response.(
                    res
                    |> jsonify(
                         400,
                         {"status": 400, "message": "Not an object"},
                       )
                  )
                };
                Js.Dict.set(
                  myMap,
                  "id",
                  Js.Json.number(float_of_int(List.length(offices^))),
                );
                offices := List.append([myMap], offices^);
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