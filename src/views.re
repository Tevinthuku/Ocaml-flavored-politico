open Http;

let views = ((req, res)) => {
  let path = Request.url(req)->Utils.replacepath;
  switch (path) {
  | "offices" when Request.isMethod(req, "GET") =>
    Offices.resolveAllOffices(res)
  | "offices" when Request.isMethod(req, "POST") =>
    Offices.createOffice(req, res)
  | dynamicofficepath
      when
        Request.isMethod(req, "GET")
        && Utils.isRouteDynamic(dynamicofficepath, "offices") =>
    Offices.resolveSingleOffice(res, dynamicofficepath)
  | route => Response.(res |> end_(route))
  };
};