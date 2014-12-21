#!/bin/bash

if [ $# -ne 3 ]
then 
  echo "Usage: ./pmakeBBallTrees.sh <inputList>  <outName> <outDir>"
  exit 1
fi

now="bballTreeJob_$(date +"%m_%d_%Y__%H_%M_%S")"
mkdir $now
mkdir -p $3

cp makeBBallTrees.sh $now
cp $1 $now

NAME="makeBBallTrees.C"
g++ $NAME $(root-config --cflags --libs) -Werror -Wall -O2 -o "${NAME/%.C/}.exe" 
cp makeBBallTrees.exe $now
