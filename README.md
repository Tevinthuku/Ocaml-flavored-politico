## Ocaml-Flavored-Politico

This is the same Politico we built in bootcamp session at Andela Cycle 37
The original Version was built in python, but I will be building it in Ocaml.

### Reasons for the rebuild.

I have much respect for python and flask and I was amazed by what I could achieve with it, however
one issue that I was not comfortable with when working with python was it is a dynamically typed language
and this introduces its own class of errors that need a lot of effort to defend your app against.
A staticcally typed language such as Ocaml does help eleviate the type errors automatically for you and as
a result your program ends up being free of type errors.

The mantra for this repo is

```
    If types don't match don't compile
```

# Global Setup

[NodeJs Installation](https://nodejs.org/en/download/)

[Global ReasonML installation](https://reasonml.github.io/docs/en/installation)

## Setting up the repo.

### 1. Clone the repo

### 2. Install dependencies

Install the dependencies via `yarn` or `npm install`

### 3. Build

The build command compiles the code to JS

```
npm run build
```

or

```
yarn build
```

### 4. Watch

Watch compiles the code and listens for changes from the files.

```
npm run watch
```

or

```
yarn watch
```

### 5. Editor

If you use `vscode`, Press `Windows + Shift + B` it will build automatically

or install

[Jared Forsyth's VSCode extension](https://github.com/jaredly/reason-language-server)
