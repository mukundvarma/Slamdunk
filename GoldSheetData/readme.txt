To extract data from goldsheet.com, you need
1. Autohotkey (AHK)
2. Dataminer plugin for Google Chrome
3. Python

Instructions
1. Create a list of links to be mined using the python script createlinklist.py which uses team IDs (as given in teamIDs.txt)
2. After you have installed Dataminer, edit the AHK script "goldSheetData.ahk" to reflect the locations where chrome downloads your files by default, and the location where you want to store the CSV files.
3. Run the AHK script 