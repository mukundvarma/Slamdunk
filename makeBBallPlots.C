//=============================================
// Author: Chris McGinn
//
// BBall Plotter
//
//=============================================

#include "BBallHists.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TDatime.h"

int makeBBallPlots(const std::string inName, const Int_t year);
void makePerPlot(const std::string outName, const std::string plotName, TH1I* pt, TH1F* ptPer, TLine* mean, Bool_t isDiff);
void TwoFormat(TH1* inHist1_p, TH1* inHist2_p, Bool_t isDiff);
void niceTH1(TH1* uglyTH1, float max , float min, float ndivX, float ndivY, Int_t col = 1, Float_t size = 1, Int_t style = 20);
void handsomeTH1(TH1 *a = 0, Int_t col = 1, Float_t size = 1, Int_t markerstyle = 20);
void claverCanvasSaving(TCanvas* c, TString s,TString format = "gif");

int runMakeBBallPlots(const std::string inName)
{
  int rStatus = -1;

  const Int_t nYears = 11;
  const Int_t years[nYears] = {2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015};

  for(int iter = 0; iter < nYears; iter++){
    rStatus = makeBBallPlots(inName, years[iter]);
  }

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
    makePerPlot(outName, Form("%s%d_ptForPlot", teams[iter].c_str(), year), ptFor_h[iter], ptForPer_h[iter], meanTotPt_, false);
    makePerPlot(outName, Form("%s%d_ptVsPlot", teams[iter].c_str(), year), ptVs_h[iter], ptVsPer_h[iter], meanTotPt_, false);
    makePerPlot(outName, Form("%s%d_ptDiffPlot", teams[iter].c_str(), year), ptDiff_h[iter], ptDiffPer_h[iter], meanDiffPt_, true);
  }

  inFile_p->Close();
  delete inFile_p;

  return 0;
}


void makePerPlot(const std::string outName, const std::string plotName, TH1I* pt, TH1F* ptPer, TLine* mean, Bool_t isDiff)
{
  TwoFormat(pt, ptPer, isDiff);

  TCanvas* plotCanvas_p = new TCanvas(Form("%s_c", plotName.c_str()), Form("%s_c", plotName.c_str()), 1*300, 1*350);

  pt->DrawCopy("E1");
  ptPer->DrawCopy("E1 SAME");
  mean->Draw();

  TLegend* leg_p = new TLegend(0.20, 0.85, 0.50, 0.95);
  leg_p->SetFillColor(0);
  leg_p->SetFillStyle(0);
  leg_p->SetTextFont(43);
  leg_p->SetTextSizePixels(18);
  leg_p->SetBorderSize(0);

  leg_p->AddEntry(pt, "Pts.", "P L");
  leg_p->AddEntry(ptPer, "Pts./Game", "P L");
  leg_p->Draw("SAME");

  TFile* outFile_p = new TFile(outName.c_str(), "UPDATE");
  plotCanvas_p->Write("", TObject::kOverwrite);
  claverCanvasSaving(plotCanvas_p, Form("pdfDir/%s", plotName.c_str()), "pdf");
  outFile_p->Close();
  delete outFile_p;

  delete plotCanvas_p;

  return;
}

void TwoFormat(TH1* inHist1_p, TH1* inHist2_p, Bool_t isDiff)
{
  /*
  Float_t maxVal = inHist1_p->GetBinContent(inHist1_p->GetMaximumBin());
  if(maxVal < inHist2_p->GetBinContent(inHist2_p->GetMaximumBin())) maxVal = inHist2_p->GetBinContent(inHist2_p->GetMaximumBin());

  Float_t minVal = inHist1_p->GetBinContent(inHist1_p->GetMinimumBin());
  if(minVal > inHist2_p->GetBinContent(inHist2_p->GetMinimumBin())) minVal = inHist2_p->GetBinContent(inHist2_p->GetMinimumBin());
  */
  //  maxVal += TMath::Sqrt(maxVal) + 1;
  //  minVal -= TMath::Sqrt(minVal) + 1;
  //  if(minVal < 0) minVal = 0;

  Int_t base = 100;
  if(isDiff) base = 0;

  niceTH1(inHist1_p, base + 50, base - 50, 505, 505, kRed+2, 0.5, 20);
  niceTH1(inHist2_p, base + 50, base - 50, 505, 505, kBlue, 0.5, 21);

  return;
}

void niceTH1(TH1* uglyTH1, float max , float min, float ndivX, float ndivY, Int_t col, Float_t size, Int_t style)
{
  handsomeTH1(uglyTH1, col, size, style);
  uglyTH1->SetMaximum(max);
  uglyTH1->SetMinimum(min);
  uglyTH1->SetNdivisions(ndivX);
  uglyTH1->SetNdivisions(ndivY, "Y");

  return;
}

void handsomeTH1(TH1 *a, Int_t col, Float_t size, Int_t markerstyle)
{
  a->SetMarkerColor(col);
  a->SetMarkerSize(size);
  a->SetMarkerStyle(markerstyle);
  a->SetLineColor(col);
  a->GetYaxis()->SetTitleOffset(1.25);
  a->GetXaxis()->CenterTitle();
  a->GetYaxis()->CenterTitle();

  return;
}

void claverCanvasSaving(TCanvas* c, TString s,TString format)
{
  TDatime* date = new TDatime();
  c->SaveAs(Form("%s_%d.%s",s.Data(),date->GetDate(), format.Data()));

  return;
}
