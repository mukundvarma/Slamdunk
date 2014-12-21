//=============================================                                 
// Author: Chris McGinn                                                         
//                                                                              
// BBall Trees Class                                                    
//                                                                              
//=============================================  

#ifndef BBallTrees_h
#define BBallTrees_h

#include <iostream>
#include <string>
#include "TFile.h"
#include "TTree.h"

#include "BBallTeamVar.h"

TTree* statTree_p = 0;
TTree* bookTree_p = 0;

const Int_t maxGames = 130;

std::string teamStr_;
Int_t teamNum_;
Int_t year_;

Int_t nGames_;
Int_t teamNumVs_[maxGames];
Int_t ptFor_[maxGames];
Int_t ptVs_[maxGames];
Int_t win_[maxGames];
Int_t loss_[maxGames];

Float_t ptForPer_[maxGames];
Float_t ptVsPer_[maxGames];

void SetBranches()
{
  //Set stat tree branches

  statTree_p->Branch("teamStr", &teamStr_);
  statTree_p->Branch("teamNum", &teamNum_, "teamNum/I");
  statTree_p->Branch("year", &year_, "year/I");

  statTree_p->Branch("nGames", &nGames_, "nGames/I");

  statTree_p->Branch("teamNumVs", teamNumVs_, "teamNumVs[nGames]/I");
  statTree_p->Branch("win", win_, "win[nGames]/I");
  statTree_p->Branch("loss", loss_, "loss[nGames]/I");
  statTree_p->Branch("ptFor", ptFor_, "ptFor[nGames]/I");
  statTree_p->Branch("ptVs", ptVs_, "ptVs[nGames]/I");

  statTree_p->Branch("ptForPer", ptForPer_, "ptForPer[nGames]/F");
  statTree_p->Branch("ptVsPer", ptVsPer_, "ptVsPer[nGames]/F");

  //Set book tree branches

  bookTree_p->Branch("nGames", &nGames_, "nGames/I");

  return;
}

void GetBranches()
{
  //Get stat tree branches

  statTree_p->SetBranchAddress("teamNum", &teamNum_);
  statTree_p->SetBranchAddress("year", &year_);

  statTree_p->SetBranchAddress("nGames", &nGames_);
  statTree_p->SetBranchAddress("teamNumVs", teamNumVs_);
  statTree_p->SetBranchAddress("win", win_);
  statTree_p->SetBranchAddress("loss", loss_);
  statTree_p->SetBranchAddress("ptFor", ptFor_);
  statTree_p->SetBranchAddress("ptVs", ptVs_);

  statTree_p->SetBranchAddress("ptForPer", ptForPer_);
  statTree_p->SetBranchAddress("ptVsPer", ptVsPer_);

  //Get book tree branches

  bookTree_p->Branch("nGames", &nGames_);

  return;
}

void InitTrees()
{
  std::cout << "Init Trees" << std::endl;

  statTree_p = new TTree("statTree_p", "statTree_p");
  bookTree_p = new TTree("bookTree_p", "bookTree_p");
  SetBranches();

  return;
}


void FillTrees()
{
  statTree_p->Fill();
  bookTree_p->Fill();
  return;
}


void WriteTrees(TFile* outFile_p)
{
  outFile_p->cd();
  statTree_p->Write("", TObject::kOverwrite);
  bookTree_p->Write("", TObject::kOverwrite);

  return;
}


void CleanupTrees()
{
  if(statTree_p != 0) delete statTree_p;
  if(bookTree_p != 0) delete bookTree_p;
  return;
}

void GetTrees(TFile* inFile_p)
{
  std::cout << "Get Trees" << std::endl;

  statTree_p = (TTree*)inFile_p->Get("statTree");
  bookTree_p = (TTree*)inFile_p->Get("bookTree");
  GetBranches();

  return;
}

void GetTreesEntry(Int_t entryNum)
{
  statTree_p->GetEntry(entryNum);
  bookTree_p->GetEntry(entryNum);
  return;
}


void InitVar()
{
  teamStr_ = "";
  teamNum_ = -1;
  year_ = -1;

  nGames_ = 0;

  return;
}

#endif
