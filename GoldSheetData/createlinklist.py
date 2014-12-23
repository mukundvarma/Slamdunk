outfile = open('linklist.txt', 'w')
teamIdArray  = ["091", "092", "104", "152", "093", "094", "095", "096", "097", "098", "099", "100", "101", "102", "119", "115", "103", "116", "114", "105", "111", "117", "106", "107", "108", "109", "110", "118", "112", "113"]
yearArray = [2001,2002,2003,2004,2005,2006,2007,2008,2009,2010,2011,2012,2013,2014]

for team in teamIdArray:
    for year in yearArray:
        print 'http://scores.goldsheet.com/merge/tsnform.aspx?c=goldsheet2&page=nba/stats/ATS.aspx?id={},season={}'.format(team,year)
        
