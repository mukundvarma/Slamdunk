from bs4 import BeautifulSoup
import requests
import bballRefID
import sys

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


def getTagStr(inStr):
  start = inStr.index('>')
  end = inStr[1:].index('<')
  return inStr[start+1:end+1]

def writeCSVFile(teamName, year):
  bball = getSoupFromURL('http://www.basketball-reference.com/teams/%s/%d_games.html' % (teamName, year), True)
  outFile = open('csvDir/%s%d.csv' % (teamName, year), "w")

  for thing in bball.findAll('tr'):
    counter = 0
    for thing2 in thing.findAll('td'):
        if(counter == 7):
            if(getTagStr(str(thing2)) == ''):
                break
        if(counter == 9):
            outFile.write(getTagStr(str(thing2))+',')
        elif(counter == 10):
            outFile.write(getTagStr(str(thing2))+',\n')
            break
        counter += 1
        
  outFile.close()
  return

if(len(sys.argv) != 3):
    print "Usage: python bballRefAPI.py <startYear> <endYear>"
    sys.exit()

for team in bballRefID.teams:
  for num in range(int(sys.argv[1]),int(sys.argv[2])+1):
    writeCSVFile(team, num)


#for thing in bball.findAll()
 # outFile.write()

#outFile.close()

#outFile.write(bball)
#outFile.close()
