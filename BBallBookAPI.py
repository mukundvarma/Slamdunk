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

#bball = getSoupFromURL('http://www.vegasinsider.com/nba/scoreboard/scores.cfm/game_date/12-20-2014', True)
bball = getSoupFromURL('http://www.basketball-reference.com/teams/ATL/2015_games.html', True)

print bball

#for thing in bball.findAll()
 # outFile.write()

#outFile.close()

#outFile.write(bball)
#outFile.close()
