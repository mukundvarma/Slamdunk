from bs4 import BeautifulSoup
import requests
import bballRefID
import sys

#this func. blatantly stolen from basketcrawler
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


def writeCSVFile(teamName, year):
  bball = getSoupFromURL('http://www.basketball-reference.com/teams/%s/%d_games.html' % (teamName, year), True)
  outFile = open('csvDir/%s%d.csv' % (teamName, year), "w")

  for thing in bball.findAll('tr'):
    counter = 0
    for thing2 in thing.findAll('td'):
        if(counter == 9):
            start = str(thing2).index('>')
            end = str(thing2)[1:].index('<')
            outFile.write(str(thing2)[start+1:end+1]+',')
        elif(counter == 10):
            start = str(thing2).index('>')
            end = str(thing2)[1:].index('<')
            outFile.write(str(thing2)[start+1:end+1]+',\n')
            break
        counter += 1

        
  outFile.close()
  return

if(len(sys.argv) == 1):
    print "Usage: python bballRefAPI.py <num>"
    sys.exit()

for team in bballRefID.teams:
    for num in range(0,int(sys.argv[1])):
        writeCSVFile(team, 2014-num)


#for thing in bball.findAll()
 # outFile.write()

#outFile.close()

#outFile.write(bball)
#outFile.close()
