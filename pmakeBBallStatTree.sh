#!/bin/bash

if [ $# -ne 3 ]
then 
  echo "Usage: ./pmakeBBallStatTree.sh <inputList>  <outName> <outDir>"
  exit 1
fi

now="statTreeJob_$(date +"%m_%d_%Y__%H_%M_%S")"
mkdir $now
mkdir -p $3

cp makeBBallStatTree.sh $now
cp $1 $now

NAME="makeBBallStatTree.C"
g++ $NAME $(root-config --cflags --libs) -Werror -Wall -O2 -o "${NAME/%.C/}.exe" 
cp makeBBallStatTree.exe $now
