from bs4 import BeautifulSoup
import requests
import BBallRefID
import sys
import datetime

#this func. blatantly stolen from basketcrawler, along w/ idea to use BeautifulSoup
def getSoupFromURL(url, supressOutput=True):
    """
    This function grabs the url and returns and returns the BeautifulSoup object
    """
    if not supressOutput:
        print url
    
    try:
        r = requests.get(url)
    except:
        return None
    
    return BeautifulSoup(r.text)


def getDateLines(year, month, day):
  tempYear = year
  if month > 6: 
      tempYear -= 1

  print 'http://data.nowgoal.com/nba/oddsHistory.htm?Selday=%d-%d-%d' % (tempYear, month, day)
  bball = getSoupFromURL('http://data.nowgoal.com/nba/oddsHistory.htm?Selday=%d-%d-%d' % (tempYear, month, day), True)
  homeNum = -1
  awayNum = -1 
  OU = ""
  Odds = ""

  outFile = open('csvDir/%dLines.csv' % (year), 'a')

  counter = 0
  for thing in bball.findAll('tr'):
    if counter == 3:
      if str(thing.findAll('b')) != "[<b> National Basketball Association </b>]":
        print str(thing.findAll('b'))
        print "Not the NBA. Break."
        break

    if counter < 4:
      counter += 1
      continue

    if str(thing)[1:24] == 'tr class="Leaguestitle"':
      break

    counter2 = 0
    for thing2 in thing.findAll('td'):
      if counter2 > 1 and counter2 < 13:
        counter3 = 0
        for thing3 in thing2.findAll('a'):
          if counter2 != 2 or counter3 == 0 or counter3 == 3:
            start = str(thing3).index('>')
            end = str(thing3)[1:].index('<')
            if counter2 == 2:
              start += 1
              end -= 1
              if counter3 == 0:
                end -= 3
                homeNum = BBallRefID.teamsBook.index(str(thing3)[start+1:end+1])
              elif counter3 == 3:
                awayNum = BBallRefID.teamsBook.index(str(thing3)[start+1:end+1])
            elif counter2 == 3:
              Odds = str(thing3)[start+1:end+1]
            elif counter2 == 8:
              OU = str(thing3)[start+1:end+1]
          counter3 += 1
      counter2 += 1
    outFile.write(str((year - 2000)*100000000 + month*1000000 + day*10000 + 100*homeNum + 1*awayNum) + "," + OU + "," + Odds + "\n")
 
  outFile.close()


if(len(sys.argv) != 3):
  print "Usage: python BBallBookAPI.py <startYear> <endYear>"
  sys.exit()

startYear = int(sys.argv[1])
endYear = int(sys.argv[2])

if(startYear > endYear):
  print "Error: <startYear> must be less than <endYear>. Return."
  sys.exit()

years = range(startYear, endYear + 1)
months = [12]
#days = [21]
#months = [9, 10, 11, 12, 1, 2, 3, 4, 5, 6]
days = range(1, 32)

cutDay = datetime.date.today() + datetime.timedelta(days=1)

cutYear = cutDay.year
cutMonth = cutDay.month
cutDay = cutDay.day

if cutMonth > 6:
  cutYear += 1

for year in years:
  outFile = open('csvDir/%dlines.csv' % year, 'w')

for year in years:
  for month in months:
    for day in days:
      if year == cutYear and month == cutMonth and day == cutDay:
        print "Hit cut date. Exit."
        sys.exit()

      getDateLines(year, month, day)


#getDateLines(2014, 12, 17)

#print bball

#for thing in bball.findAll()
 # outFile.write()

#outFile.close()

#outFile.write(bball)
#outFile.close()
