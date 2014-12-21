Slamdunk
========

To run bballRefAPI.py:
   need python 2.7, requests module, and BeautifulSoup

   requests:   
     http://docs.python-requests.org/en/latest/
   BeautifulSoup:
     http://www.crummy.com/software/BeautifulSoup/

   I used macports to grab both, then sudo easy_install BeautifulSoup(requests) in respective directories

   If modules properly installed, should be listed after calling:
     python -c "help('modules')"

   After properly installed, can grab all team game scores for listed number of years [2014 - (<num> - 1):2014] w/
     python bballRefAPI.py <num>