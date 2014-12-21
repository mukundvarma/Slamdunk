//=============================================                                 
// Author: Chris McGinn                                                         
//                                                                              
// DiJet Initial Skim Class (MC)                                                    
//                                                                              
//=============================================  

#ifndef BBallStatTree_h
#define BBallStatTree_h

#include <iostream>
#include <string>
#include "TFile.h"
#include "TTree.h"

enum TeamNum{
  ATL,  //0
  BOS,  //1
  BRK,  //2
  CHA,  //3
  CHI,  //4
  CLE,  //5
  DAL,  //6
  DEN,  //7
  DET,  //8
  GSW,  //9
  HOU,  //10
  IND,  //11
  LAC,  //12
  LAL,  //13
  MEM,  //14
  MIA,  //15
  MIL,  //16
  MIN,  //17
  NOH,  //18
  NYK,  //19
  OKC,  //20
  ORL,  //21
  PHI,  //22
  PHO,  //23
  POR,  //24
  SAC,  //25
  SAS,  //26
  TOR,  //27
  UTA,  //28
  WAS   //29
};


TTree* statTree_p = 0;

const Int_t nTeams = 30;
const std::string teams[nTeams] = {"ATL", "BOS", "BRK", "CHA", "CHI", "CLE", "DAL", "DEN", "DET", "GSW", "HOU", "IND", "LAC", "LAL", "MEM", "MIA", "MIL", "MIN", "NOH", "NYK", "OKC", "ORL", "PHI", "PHO", "POR", "SAC", "SAS", "TOR", "UTA", "WAS"};

const Int_t maxGames = 130;

std::string teamStr_;
Int_t teamNum_;
Int_t year_;

Int_t nGames_;
Int_t ptFor_[maxGames];
Int_t ptAgst_[maxGames];

Float_t ptForPer_[maxGames];
Float_t ptAgstPer_[maxGames];

void SetBranches()
{
  statTree_p->Branch("teamStr", &teamStr_);
  statTree_p->Branch("teamNum", &teamNum_, "teamNum/I");
  statTree_p->Branch("year", &year_, "year/I");

  statTree_p->Branch("nGames", &nGames_, "nGames/I");
  statTree_p->Branch("ptFor", ptFor_, "ptFor[nGames]/I");
  statTree_p->Branch("ptAgst", ptAgst_, "ptAgst[nGames]/I");

  statTree_p->Branch("ptForPer", ptForPer_, "ptForPer[nGames]/F");
  statTree_p->Branch("ptAgstPer", ptAgstPer_, "ptAgstPer[nGames]/F");

  return;
}

void GetBranches()
{
  //  statTree_p->SetBranchAddress("teamStr", &teamStr_);
  statTree_p->SetBranchAddress("teamNum", &teamNum_);
  statTree_p->SetBranchAddress("year", &year_);

  statTree_p->SetBranchAddress("nGames", &nGames_);
  statTree_p->SetBranchAddress("ptFor", ptFor_);
  statTree_p->SetBranchAddress("ptAgst", ptAgst_);

  statTree_p->SetBranchAddress("ptForPer", ptForPer_);
  statTree_p->SetBranchAddress("ptAgstPer", ptAgstPer_);

  return;
}

void InitStatTree()
{
  std::cout << "Init Stat Tree" << std::endl;

  statTree_p = new TTree("statTree", "statTree");
  SetBranches();

  return;
}

void CleanupStatTree()
{
  if(statTree_p != 0) delete statTree_p;
  return;
}

void GetStatTree(TFile* inFile_p)
{
  std::cout << "Get Stat Tree" << std::endl;

  statTree_p = (TTree*)inFile_p->Get("statTree");
  GetBranches();

  return;
}

void InitStatVar()
{
  teamStr_ = "";
  teamNum_ = -1;
  year_ = -1;

  nGames_ = 0;

  return;
}

#endif
