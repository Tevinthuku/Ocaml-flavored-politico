open Http;

open Views;

createServer((req, res) => views((req, res))) |> listen(3000);