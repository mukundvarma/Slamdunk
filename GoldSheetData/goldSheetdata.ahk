Loop, read, C:\gslinklist.txt
{
	StringTrimLeft, year, A_LoopReadLine, 98; Get year id to rename the final csv file
	StringTrimRight, temp, A_LoopReadLine, 12
	StringTrimLeft, team, temp, 87; Get team id to rename the final csv file
	
	Run %A_LoopReadLine%; Read in URL from file
	sleep, 2000
	Click 1557, 52;Click plugin icon on chrome 
	sleep, 1000	
	Click 87, 52;Click preset (you have to make this preset beforehand)
	sleep, 1000
	Click 874, 791;Click the "download data" button 
	sleep, 500
	Send ^w
	Click 1150, 12
	Send ^w
	;Rename file 
	FileMove C:\Users\Mukund\Downloads\DataMiner.csv, C:\Users\Mukund\Documents\GSCsvs\GS_team%team%_year%year%.csv 
}