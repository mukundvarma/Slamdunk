#include <fstream>
#include <vector>
#include "BBallTrees.h"
#include "getMean.h"

int makeBBallTrees(const std::string fList , const std::string outName);
Long64_t getGameID(const Int_t year, const Int_t month, const Int_t day, const Int_t teamNum, const Int_t teamNumVs, const Bool_t isHome);

int main(int argc, char* argv[])
{
  if(argc != 3){
    std::cout << "usage: makeBBallTrees <inputList> <outName>" << std::endl;
    return 1;
  }

  int jobStatus = -1;
  jobStatus = makeBBallTrees(argv[1], argv[2]);
  return jobStatus;
}

int makeBBallTrees(const std::string fList, const std::string outName)
{
  std::string buffer;
  std::vector<std::string> listOfFiles;
  std::ifstream inFile(fList.data());

  std::cout << "inList: " << fList << std::endl;

  if(!inFile.is_open()){
    std::cout << "Error opening file. Exiting." << std::endl;
    return 1;
  }
  else{
    while(true){
      inFile >> buffer;
      if(inFile.eof()) break;
      listOfFiles.push_back(buffer);
    }
  }

  std::cout << "FileList Loaded." << std::endl;

  TFile* outFile_p = new TFile(Form("%s.root", outName.c_str()), "UPDATE");
  InitBBallTrees();

  for(Int_t fileIter = 0; fileIter < (Int_t)(listOfFiles.size()); fileIter++){
    if(fileIter%1 == 0) std::cout << "File Number: " << fileIter << std::endl;
    InitBBallVar();

    std::string fileStr = listOfFiles[fileIter];
    const std::string cullString = "/";
    while(true){
      std::size_t strIndex = fileStr.find(cullString);
      if(strIndex == std::string::npos) break;
      fileStr.replace(0, strIndex + 1, "");
    }
    teamStr_ = fileStr.substr(0, 3);

    for(Int_t teamIter = 0; teamIter < nTeams; teamIter++){
      if(!strcmp(teamStr_.c_str(), teams[teamIter].c_str())){
	teamNum_ = teamIter;
	break;
      }
    }

    year_ = std::atoi(fileStr.substr(3, 7).c_str());

    std::ifstream csvFile(listOfFiles[fileIter].c_str());
    std::string outVal;

    while(true){
      std::getline(csvFile, outVal, ',');
      if(csvFile.eof()) break;
      month_[nGames_] = Int_t(std::atoi(outVal.c_str()));

      std::getline(csvFile, outVal, ',');
      day_[nGames_] = Int_t(std::atoi(outVal.c_str()));

      std::getline(csvFile, outVal, ',');
      isHome_[nGames_] = Bool_t(std::atoi(outVal.c_str()));

      std::getline(csvFile, outVal, ',');
      teamNumVs_[nGames_] = Int_t(std::atoi(outVal.c_str()));

      gameID_[nGames_] = getGameID(year_, month_[nGames_], day_[nGames_], teamNum_, teamNumVs_[nGames_], isHome_[nGames_]);

      std::getline(csvFile, outVal, ',');
      ptFor_[nGames_] = Int_t(std::atoi(outVal.c_str()));

      for(Int_t ptIter = 0; ptIter < nGames_+1; ptIter++){
	getMean(ptIter+1, ptFor_, ptForPer_[ptIter], ptForPerErr_[ptIter]);
      }

      std::getline(csvFile, outVal, ',');
      ptVs_[nGames_] = Int_t(std::atoi(outVal.c_str()));

      for(Int_t ptIter = 0; ptIter < nGames_+1; ptIter++){
	getMean(ptIter+1, ptVs_, ptVsPer_[ptIter], ptVsPerErr_[ptIter]);
      }

      if(nGames_ == 0){
	win_[nGames_] = 0;
	loss_[nGames_] = 0;
      }
      else{
	win_[nGames_] = win_[nGames_-1];
	loss_[nGames_] = loss_[nGames_-1];
      }
      if(ptFor_[nGames_] > ptVs_[nGames_]) win_[nGames_]++;
      else loss_[nGames_]++;

      ptDiff_[nGames_] = ptFor_[nGames_] - ptVs_[nGames_];
      ptDiffErr_[nGames_] = TMath::Sqrt(ptFor_[nGames_] + ptVs_[nGames_]);

      for(Int_t ptIter = 0; ptIter < nGames_+1; ptIter++){
        getMean(ptIter+1, ptDiff_, ptDiffPer_[ptIter], ptDiffPerErr_[ptIter]);
      }

      std::getline(csvFile, outVal);
      nGames_++;
    }

    FillBBallTrees();
  }

  WriteBBallTrees(outFile_p);
  CleanupBBallTrees();
  outFile_p->Close();
  delete outFile_p;

  return 0;
}


Long64_t getGameID(const Int_t year, const Int_t month, const Int_t day, const Int_t teamNum, const Int_t teamNumVs, const Bool_t isHome)
{
  Long_t gameID = (year - 2000)*100000000 + month*1000000 + day*10000;  

  if(isHome) gameID += teamNum*100 + teamNumVs*1;
  else gameID += teamNumVs*100 + teamNum*1;

  return gameID;
}
