type office = {
    name: string;
    type_: string [@bs.as "type"]
} [@@bs.deriving jsConverter]

type offices = {
    status: int;
    data: office array
} [@@bs.deriving jsConverter]