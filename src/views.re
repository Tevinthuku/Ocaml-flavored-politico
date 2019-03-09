open Http;

open Utils;

let offices = ref([]);

let views = ((req, res)) => {
  let path = Request.url(req)->Utils.replacepath;
  switch (path) {
  | "offices" when Request.isMethod(req, "GET") =>
    Response.(res |> jsonify(200, {"status": 200, "data": offices^}))
  | "offices" when Request.isMethod(req, "POST") =>
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
                  Js.Dict.set(newOffice, "name", name);
                  Js.Dict.set(newOffice, "type", type_);
                  Js.Dict.set(
                    newOffice,
                    "id",
                    string_of_int(List.length(offices^)),
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
  | dynamicofficepath
      when
        Request.isMethod(req, "GET")
        && Utils.isRouteDynamic(dynamicofficepath, "offices") =>
    let f = json =>
      switch (Js.Dict.get(json, "id"), Utils.getParam(dynamicofficepath)) {
      | (Some(id), dyn) when id == dyn => true
      | (_, _) => false
      };

    switch (List.find(f, offices^)) {
    | item =>
      Response.(res |> jsonify(200, {"status": 200, "data": [item]}))
    | exception Not_found =>
      Response.(res |> jsonify(404, {"status": 404, "message": "Not found"}))
    };

  | route => Response.(res |> end_(route))
  };
};