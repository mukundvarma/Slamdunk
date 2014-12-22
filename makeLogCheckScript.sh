#!/bin/bash

ls $1>logCheck.sh
perl -pi -e 's/csvDir/cat csvDir/g' logCheck.sh
perl -pi -e 's/\.csv/\.csv\nread -p "Press any key to continue... " -n1 -s/g' logCheck.sh