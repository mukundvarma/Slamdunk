//=============================================
// Author: Chris McGinn
//
// BBall Histogram Maker
//
//=============================================

#include "BBallTrees.h"
#include "BBallHists.h"

int makeBBallHists(const std::string inName, const Int_t year);

int runMakeBBallHists(const std::string inName)
{
  Int_t jobStatus = -1;

  const Int_t nYears = 11;
  const Int_t years[nYears] = {2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015};

  for(int iter = 0; iter < nYears; iter++){
    jobStatus = makeBBallHists(inName, years[iter]);
    if(jobStatus != 0) break;
  }

  return jobStatus;
}

int makeBBallHists(const std::string inName, const Int_t year)
{
  TH1::SetDefaultSumw2();

  std::string outName = inName;
  const std::string cutString = "Tree";
  const std::string repString = "Hist";

  std::size_t strIndex = outName.find(cutString);
  if(!(strIndex == std::string::npos)) outName.replace(strIndex, cutString.length(), repString);

  TFile* inFile_p = new TFile(inName.c_str(), "READ");
  GetBBallTrees(inFile_p);

  Int_t nEntries = statTree_p->GetEntries();

  BookBBallHists(year);
  Float_t totPt = 0;
  Float_t totNum = 0;

  for(Int_t jEntry = 0; jEntry < nEntries; jEntry++){
    GetBBallTreesEntry(jEntry);
    if(year_ != year) continue;

    for(Int_t iter = 0; iter < 82; iter++){
      totPt+= ptFor_[iter];
      totNum++;
    }

    if(nGames_ < 82) FillBBallHists(teamNum_, nGames_, ptFor_, ptForPer_, ptForPerErr_, ptVs_, ptVsPer_, ptVsPerErr_);
    else FillBBallHists(teamNum_, 82, ptFor_, ptForPer_, ptForPerErr_, ptVs_, ptVsPer_, ptVsPerErr_);
  }
  totPt/=totNum;
  meanPt_ = new TLine(-0.5, totPt, 81.5, totPt);

  WriteBBallHists(outName, year);
  CleanupBBallHists();
  inFile_p->Close();
  delete inFile_p;

  return 0;
}
