//=============================================                                 
// Author: Chris McGinn                                                         
//                                                                              
// BBall Hists Class                                                    
//                                                                              
//============================================= 

#ifndef BBallHists_h
#define BBallHists_h

#include "TFile.h"
#include "TH1I.h"
#include "TH1F.h"
#include "TMath.h"
#include "BBallTeamVar.h"

TH1I* ptFor_h[nTeams];
TH1F* ptForPer_h[nTeams];

void BookBBallHists(const Int_t year)
{
  for(Int_t iter = 0; iter < nTeams; iter++){
    ptFor_h[iter] = new TH1I(Form("ptFor_%s%d_h", teams[iter].c_str(), year), Form("ptFor_%s%d_h", teams[iter].c_str(), year), 82, -0.5, 81.5);
    ptForPer_h[iter] = new TH1F(Form("ptForPer_%s%d_h", teams[iter].c_str(), year), Form("ptForPer_%s%d_h", teams[iter].c_str(), year), 82, -0.5, 81.5);
  }

  return;
}

void FillBBallHists(const Int_t teamNum, const Int_t nGames, Int_t ptFor[], Float_t ptForPer[], Float_t ptForPerErr[])
{
  for(Int_t iter = 0; iter < nGames; iter++){
    ptFor_h[teamNum]->SetBinContent(iter+1, ptFor[iter]);
    ptFor_h[teamNum]->SetBinError(iter+1, TMath::Sqrt(ptFor[iter]));

    ptForPer_h[teamNum]->SetBinContent(iter+1, ptForPer[iter]);
    ptForPer_h[teamNum]->SetBinError(iter+1, ptForPerErr[iter]);
  }

  return;
}



void WriteBBallHists(const std::string outName)
{
  TFile* outFile_p = new TFile(outName.c_str(), "UPDATE");
  for(Int_t iter = 0; iter < nTeams; iter++){
    ptFor_h[iter]->Write("", TObject::kOverwrite);
    ptForPer_h[iter]->Write("", TObject::kOverwrite);
  }
  outFile_p->Close();
  delete outFile_p;

  return;
}

void CleanupBBallHists()
{
  for(Int_t iter = 0; iter < nTeams; iter++){
    delete ptFor_h[iter];
    delete ptForPer_h[iter];
  }

  return;
}

void GetBBallHists(TFile* histFile_p, const Int_t year)
{
  for(Int_t iter = 0; iter < nTeams; iter++){
    ptFor_h[iter] = (TH1I*)histFile_p->Get(Form("ptFor_%s%d_h", teams[iter].c_str(), year));
    ptForPer_h[iter] = (TH1F*)histFile_p->Get(Form("ptForPer_%s%d_h", teams[iter].c_str(), year));
  }

  return;
}

#endif
