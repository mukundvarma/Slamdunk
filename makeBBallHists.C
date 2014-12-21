//=============================================
// Author: Chris McGinn
//
// BBall Histogram Maker
//
//=============================================

#include "BBallTrees.h"
#include "BBallHists.h"


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

  for(Int_t jEntry = 0; jEntry < nEntries; jEntry++){
    GetBBallTreesEntry(jEntry);

    if(year_ != year) continue;

    if(nGames_ < 82) FillBBallHists(teamNum_, nGames_, ptFor_, ptForPer_, ptForPerErr_);
    else FillBBallHists(teamNum_, 82, ptFor_, ptForPer_, ptForPerErr_);
  }

  WriteBBallHists(outName);
  CleanupBBallHists();
  inFile_p->Close();
  delete inFile_p;

  return 0;
}
