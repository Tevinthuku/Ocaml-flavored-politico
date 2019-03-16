open Http;

open Utils;

let offices = ref([]);

let resolveAllOffices = res =>
  Response.(res |> jsonify(200, {"status": 200, "data": offices^}));

let createOffice = (req, res) => {
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
              | (Error(namefailurereason), _) =>
                Response.(
                  res
                  |> jsonify(
                       400,
                       {"status": 400, "message": namefailurereason},
                     )
                )
              | (_, Error(typefailurereason)) =>
                Response.(
                  res
                  |> jsonify(
                       400,
                       {"status": 400, "message": typefailurereason},
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
};

let resolveSingleOffice = (res, dynamicofficepath) => {
  let f = json =>
    switch (Js.Dict.get(json, "id"), Utils.getParam(dynamicofficepath)) {
    | (Some(id), dyn) when id == dyn => true
    | (_, _) => false
    };

  switch (List.find(f, offices^)) {
  | item => Response.(res |> jsonify(200, {"status": 200, "data": [item]}))
  | exception Not_found =>
    Response.(res |> jsonify(404, {"status": 404, "message": "Not found"}))
  };
};