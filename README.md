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

To run makeBBallStatTree.C:
   need root, figure it out

   First run:
      sh pmakeBBallStatTree.sh <inputCSVList> <outFileName> <outDir>
            will create directory to run in, and executable
   cd into created directory and run:
      sh makeBBallStatTree.sh <inputCSVList> <outFileName> <outDir>
      	 will create file <outFileName>.root containt statTree in <outDir>

   statTree structure documented in header file BBallStatTree.h