[@bs.deriving jsConverter]
type office = {
  name: string,
  type_: string,
};

[@bs.deriving jsConverter]
type offices = {
  status: int,
  data: array(office),
};