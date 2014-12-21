#include <fstream>
#include <vector>
#include "BBallStatTree.h"

int makeBBallStatTree(const std::string fList , const std::string outName);

int main(int argc, char* argv[])
{
  if(argc != 3){
    std::cout << "usage: makeBBallStatTree <inputList> <outName>" << std::endl;
    return 1;
  }

  int jobStatus = -1;
  jobStatus = makeBBallStatTree(argv[1], argv[2]);
  return jobStatus;
}

int makeBBallStatTree(const std::string fList, const std::string outName)
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
  InitStatTree();

  for(Int_t fileIter = 0; fileIter < (Int_t)(listOfFiles.size()); fileIter++){
    if(fileIter%10 == 0) std::cout << "File Number: " << fileIter << std::endl;
    InitStatVar();

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

      ptFor_[nGames_] = Int_t(std::atoi(outVal.c_str()));

      ptForPer_[nGames_] = 0;
      for(Int_t ptIter = 0; ptIter < nGames_+1; ptIter++){
	ptForPer_[nGames_] += ptFor_[ptIter];
      }
      ptForPer_[nGames_]/=(nGames_+1);

      std::getline(csvFile, outVal, ',');

      ptAgst_[nGames_] = Int_t(std::atoi(outVal.c_str()));

      ptAgstPer_[nGames_] = 0;
      for(Int_t ptIter = 0; ptIter < nGames_+1; ptIter++){
	ptAgstPer_[nGames_] += ptAgst_[ptIter];
      }
      ptAgstPer_[nGames_]/=(nGames_+1);

      std::getline(csvFile, outVal);
      nGames_++;
    }

    statTree_p->Fill();
  }

  statTree_p->Write("", TObject::kOverwrite);
  CleanupStatTree();
  outFile_p->Close();
  delete outFile_p;

  return 0;
}
