from bs4 import BeautifulSoup
import requests
import BBallRefID
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

bball = getSoupFromURL('http://www.vegasinsider.com/nba/scoreboard/scores.cfm/game_date/12-20-2014', True)

for thing in bball.findAll('tr'):
  counter = 0
  if str(thing)[11:16] == 'tanBg':
    for thing2 in thing.findAll('td'):
      if counter == 2:
        start = str(thing2).index('>')  
        end = str(thing2)[1:].index('<')

        if str(thing2)[start+3:start+4] == '-':
          print "Odds: " + str(thing2)[start+3:end-1]
        else:
          print "Over/Under: " + str(thing2)[start+3:end-1]

      elif counter > 2:
        break
      counter += 1

#print bball

#for thing in bball.findAll()
 # outFile.write()

#outFile.close()

#outFile.write(bball)
#outFile.close()
