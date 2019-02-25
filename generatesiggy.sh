#!/bin/sh


filepath(){
  FILENAME=`echo $(basename $1)  | cut -d'-' -f 1`
  echo "src/$FILENAME.mli"
}

bsb -clean-world
bsb -make-world

for i in $(find lib/bs/src -name '*.cmi');do
   bsc "$(pwd)/$i" > "$(filepath $i)"
done