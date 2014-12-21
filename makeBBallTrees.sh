#!/bin/bash

if [ $# -ne 3 ]
then 
  echo "Usage: ./makeBBallTrees.sh <inputList> <outName> <outDir>"
  exit 1
fi

echo | awk -v inputList=$1 -v outName=$2 '{print "./makeBBallTrees.exe \""inputList"\" \""outName"\""}' | bash

mv *.root $3
echo "job done successfully"
