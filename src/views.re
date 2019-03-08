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
            _ => {
              let json =
                try (Js.Json.parseExn(data^)) {
                | _ => failwith("Error parsing JSON string")
                };

              switch (Js.Json.classify(json)) {
              | Js.Json.JSONObject(json) =>
                switch (
                  Utils.getString(json, "name"),
                  Utils.getString(json, "type"),
                ) {
                | (Ok(name), Ok(type_)) =>
                  let newOffice = Js.Dict.empty();
                  Js.Dict.set(newOffice, "name", Js.Json.string(name));
                  Js.Dict.set(newOffice, "type", Js.Json.string(type_));
                  Js.Dict.set(
                    newOffice,
                    "id",
                    Js.Json.number(float_of_int(List.length(offices^))),
                  );
                  offices := List.append([newOffice], offices^);

                  Response.(
                    res
                    |> jsonify(
                         200,
                         {"status": 200, "message": "Data received"},
                       )
                  );
                | (Error, _) =>
                  Response.(
                    res
                    |> jsonify(
                         400,
                         {"status": 400, "message": "Name is not provided"},
                       )
                  )
                | (_, Error) =>
                  Response.(
                    res
                    |> jsonify(
                         400,
                         {"status": 400, "message": "Type is not provided"},
                       )
                  )
                }
              | _ =>
                Response.(
                  res
                  |> jsonify(400, {"status": 400, "message": "Bad request"})
                )
              };
            },
          ),
        )
    );

  | route => Response.(res |> end_(route))
  };