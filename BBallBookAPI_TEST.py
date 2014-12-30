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


bball = getSoupFromURL('http://data.nowgoal.com/nba/oddsHistory.htm?Selday=2013-12-3', True)

for thing in bball.findAll('tr'):
  print thing
