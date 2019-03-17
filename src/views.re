open Http;

let views = ((req, res)) => {
  let path = Request.url(req)->Utils.replacepath;
  switch (path) {
  | "offices" when Request.isMethod(req, "GET") =>
    Offices.resolveAllOffices(res)
  | "offices" when Request.isMethod(req, "POST") =>
    Offices.createOffice(req, res)
  | specificoffice
      when
        Request.isMethod(req, "GET")
        && Utils.isRouteDynamic(specificoffice, "offices") =>
    Offices.resolveSingleOffice(res, specificoffice)

  | "parties" when Request.isMethod(req, "GET") =>
    Parties.resolveAllParties(res)

  | "parties" when Request.isMethod(req, "POST") =>
    Parties.createParty(req, res)

  | specificparty
      when
        Request.isMethod(req, "GET")
        && Utils.isRouteDynamic(specificparty, "parties") =>
    Parties.resolveSingleParty(res, specificparty)

  | updateparty
      when
        Request.isMethod(req, "PATCH")
        && Utils.isRouteDynamic(updateparty, "parties")
        && Parties.isPartyUpdateRoute(updateparty) =>
    Parties.updateParty(req, res, updateparty)

  | deleteparty
      when
        Request.isMethod(req, "DELETE")
        && Utils.isRouteDynamic(deleteparty, "parties") =>
    Parties.deleteParty(res, deleteparty)
  | route => Response.(res |> end_(route))
  };
};