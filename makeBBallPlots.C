//=============================================
// Author: Chris McGinn
//
// BBall Plotter
//
//=============================================

#include "BBallHists.h"
#include "TCanvas.h"

int makeBBallPlots(const std::string inName, const Int_t year);
void makePerPlot(const std::string outName, const std::string plotName, TH1I* pt, TH1F* ptPer);
void TwoFormat(TH1* inHist1_p, TH1* inHist2_p);
void niceTH1(TH1* uglyTH1, float max , float min, float ndivX, float ndivY, Int_t col, Float_t size, Int_t style);

int runMakeBBallPlots(const std::string inName)
{
  int rStatus = -1;
  rStatus = makeBBallPlots(inName, 2014);
  return rStatus;
}

int makeBBallPlots(const std::string inName, const Int_t year)
{
  TH1::SetDefaultSumw2();

  std::string outName = inName;
  const std::string cutString = "Hists";
  const std::string repString = "Plots";

  std::size_t strIndex = outName.find(cutString);
  if(!(strIndex == std::string::npos)) outName.replace(strIndex, cutString.length(), repString);

  TFile* inFile_p = new TFile(inName.c_str(), "READ");
  GetBBallHists(inFile_p, year);

  for(Int_t iter = 0; iter < nTeams; iter++){
    makePerPlot(outName, Form("%s%d_ptForPlot", teams[iter], year), ptForPt_h[iter], ptForPtPer_h[iter]);
  }

  inFile_p->Close();
  delete inFile_p;

  return 0;
}


void makePerPlot(const std::string outName, const std::string plotName, TH1I* pt, TH1F* ptPer)
{
  TwoFormat(pt, ptPer);



  return;
}

void TwoFormat(TH1* inHist1_p, TH1* inHist2_p)
{
  Float_t maxVal = inHist1_p->GetBinContent(inHist1_p->GetMaximumBin());
  if(maxVal < inHist2_p->GetBinContent(inHist2_p->GetMaximumBin())) maxVal = inHist2_p->GetBinContent(inHist2_p->GetMaximumBin());

  Float_t minVal = inHist1_p->GetBinContent(inHist1_p->GetMinimumBin());
  if(minVal < inHist2_p->GetBinContent(inHist2_p->GetMinimumBin())) minVal = inHist2_p->GetBinContent(inHist2_p->GetMinimumBin());

  maxVal += TMath::Sqrt(maxVal);
  minVal -= TMath::Sqrt(minVal);
  if(minVal < 0) minVal = 0;

  niceTH1(inHist1_p, maxVal, minVal, 505, 505);
  niceTH1(inHist2_p, maxVal, minVal, 505, 505);

  return;
}

void niceTH1(TH1* uglyTH1, float max , float min, float ndivX, float ndivY, Int_t col = 1, Float_t size = 1, Int_t style = 20)
{
  handsomeTH1(uglyTH1, col, size, style);
  uglyTH1->SetMaximum(max);
  uglyTH1->SetMinimum(min);
  uglyTH1->SetNdivisions(ndivX);
  uglyTH1->SetNdivisions(ndivY, "Y");

  return;
}
