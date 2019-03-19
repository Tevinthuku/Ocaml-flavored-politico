open Http;

let views = ((req, res)) => {
  let path = Request.url(req)->Utils.replacepath;
  switch (path, Request.method(req)) {
  | ("offices", "GET") => Offices.resolveAllOffices(res)
  | ("offices", "POST") => Offices.createOffice(req, res)
  | (specificoffice, "GET")
      when Utils.isRouteDynamic(specificoffice, "offices") =>
    Offices.resolveSingleOffice(res, specificoffice)

  | ("parties", "GET") => Parties.resolveAllParties(res)

  | ("parties", "POST") => Parties.createParty(req, res)

  | (specificparty, "GET")
      when Utils.isRouteDynamic(specificparty, "parties") =>
    Parties.resolveSingleParty(res, specificparty)

  | (updateparty, "PATCH")
      when
        Utils.isRouteDynamic(updateparty, "parties")
        && Parties.isPartyUpdateRoute(updateparty) =>
    Parties.updateParty(req, res, updateparty)

  | (deleteparty, "DELETE") when Utils.isRouteDynamic(deleteparty, "parties") =>
    Parties.deleteParty(res, deleteparty)
  | route => Response.(res |> end_(route))
  };
};