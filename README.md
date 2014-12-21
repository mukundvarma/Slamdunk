Slamdunk
========

To run BBallRefAPI.py:

   need python 2.7, requests module, and BeautifulSoup

   requests:   

     http://docs.python-requests.org/en/latest/

   BeautifulSoup:

     http://www.crummy.com/software/BeautifulSoup/

   I used macports to grab both, then sudo easy_install BeautifulSoup(requests) in respective directories

   If modules properly installed, should be listed after calling:

     python -c "help('modules')"

   After properly installed, can grab all team game scores for year arguments w/:

     python BBallRefAPI.py <yearStart> <yearEnd>

To run makeBBallTrees.C:

   need root, figure it out

   First run:

      sh pmakeBBallTrees.sh <inputCSVList> <outFileName> <outDir>

            will create directory to run in, and executable

   cd into created directory and run:

      sh makeBBallTrees.sh <inputCSVList> <outFileName> <outDir>

      	 will create file <outFileName>.root containing Trees in <outDir>

   Trees structure documented in header file BBallTrees.h