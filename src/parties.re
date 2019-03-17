open Http;

open Utils;

let parties = ref([]);

let isPartyUpdateRoute = route =>
  switch (Js.String.split("/", route)) {
  | n when Array.length(n) > 1 && n[Array.length(n) - 1] == "name" => true
  | _ => false
  };

let resolveAllParties = res =>
  Response.(res |> jsonify(200, {"status": 200, "data": parties^}));

let createParty = (req, res) => {
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
                Utils.getString(json, "hqAddress"),
              ) {
              | (Ok(name), Ok(hqAddress)) =>
                let newParty = Js.Dict.empty();
                Js.Dict.set(newParty, "name", name);
                Js.Dict.set(newParty, "hqAdress", hqAddress);
                Js.Dict.set(
                  newParty,
                  "id",
                  string_of_int(List.length(parties^)),
                );
                parties := List.append([newParty], parties^);

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
              | (_, Error(hqfailurereason)) =>
                Response.(
                  res
                  |> jsonify(
                       400,
                       {"status": 400, "message": hqfailurereason},
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

let getSingleParty = id => {
  let f = json =>
    switch (Js.Dict.get(json, "id"), id) {
    | (Some(id), dyn) when id == dyn => true
    | (_, _) => false
    };

  switch (List.find(f, parties^)) {
  | item => Some(item)
  | exception Not_found => None
  };
};

let resolveSingleParty = (res, dynamicpartiesroute) =>
  switch (getSingleParty(Utils.getParam(dynamicpartiesroute))) {
  | Some(item) =>
    Response.(res |> jsonify(200, {"status": 200, "data": [item]}))
  | None =>
    Response.(res |> jsonify(404, {"status": 404, "message": "Not found"}))
  };

let updateParty = (req, res, dynamicpartiesroute) => {
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
              switch (Utils.getString(json, "name")) {
              | Ok(newname) =>
                let partyId = Utils.getParam(dynamicpartiesroute);
                let updatefn = party =>
                  switch (Js.Dict.get(party, "id")) {
                  | Some(id) when id == partyId =>
                    Js.Dict.set(party, "name", newname);
                    party;
                  | _ => party
                  };
                switch (getSingleParty(partyId)) {
                | Some(item) =>
                  parties := List.map(updatefn, parties^);
                  Response.(
                    res
                    |> jsonify(
                         200,
                         {"status": 200, "updated": true, "data": [item]},
                       )
                  );
                | None =>
                  Response.(
                    res
                    |> jsonify(
                         404,
                         {"status": 404, "message": "Party Not found"},
                       )
                  )
                };
              | _ =>
                Response.(
                  res
                  |> jsonify(400, {"status": 400, "message": "Bad request"})
                )
              }
            | _ =>
              Response.(
                res
                |> jsonify(
                     400,
                     {"status": 400, "message": "Required an object"},
                   )
              )
            };
          },
        ),
      )
  );
};

let deleteParty = (res, dynamicpartiesroute) => {
  let partyId = Utils.getParam(dynamicpartiesroute);
  let f = json =>
    switch (Js.Dict.get(json, "id")) {
    | Some(id) when id != partyId => true
    | _ => false
    };
  switch (getSingleParty(partyId)) {
  | Some(_) =>
    parties := List.filter(f, parties^);
    Response.(
      res
      |> jsonify(200, {"status": 200, "message": "deleted item " ++ partyId})
    );
  | None =>
    Response.(res |> jsonify(404, {"status": 404, "message": "Not found"}))
  };
};