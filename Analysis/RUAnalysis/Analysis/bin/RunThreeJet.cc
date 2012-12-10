////////////////////////////////////////////////////////////////////
//
// Dean Andrew Hidas <Dean.Andrew.Hidas@cern.ch>
//
// Created on: Mon Jul 25 14:21:29 CEST 2011
//
////////////////////////////////////////////////////////////////////


#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include "TString.h"

#include "RUAnalysis/Analysis/interface/NtpThreeJet.h"

int RunThreeJet (std::vector<TString>& InFileNames, bool const IsData, TString const OutFileName,
const TString PUFile)
{
  NtpThreeJet Ana(InFileNames, IsData, OutFileName, PUFile);
  //std::cout<<"Book Histograms"<<std::endl;

  Ana.BookHistograms();
  // std::cout<<"Loop through Events"<<std::endl;

  Ana.Loop();
  std::cout<<"Write Histograms"<<std::endl;

  Ana.WriteHistograms();
  std::cout<<"After Write Histograms, returning"<<std::endl;
  return 0;
}


int main (int argc, char* argv[])
{

  if (argc < 4) {
    std::cerr << "Usage: " << argv[0] << "[Pileup] [OutFileName] [FileName]s" << std::endl;
    return 1;
  }


  // currently default to false
  bool const IsData = false;

  // Output file name

TString const PUFile = argv[1];
  if (PUFile.SubString("PUHisto").IsNull()){
    std::cout<<"I think you are not including a pile up file, this will cause damage to input ntuples"<<std::endl;
    std::cout<<"even if you don't have a real PUHistos.root file just write PUHistos.root as first argument"<<std::endl;
    std::cout<<"until I fix the problem"<<std::endl;
    throw;
    }
  TString const OutFileName = argv[2];

  // Grab the filename itself for a quick check
  TString const JustFileName = OutFileName.Last('/') >= 0 ? OutFileName( OutFileName.Last('/') + 1, OutFileName.Length() - OutFileName.Last('/') - 1) : OutFileName;

  // Grab input file names
  std::vector<TString> InFileNames;
  for (int i = 3; i < argc; ++i) {
    InFileNames.push_back(argv[i]);
  }

  for (size_t i = 0; i != InFileNames.size(); ++i) {
    if (InFileNames[i].Contains(JustFileName)) {
      std::cerr << "OH NO, it looks like the output file you specified might be one of the input files... ";
      std::cerr << "are you sure you want to do this: " << OutFileName << std::endl;
      std::cerr << "If so.. you have to disable this message.  sorry -- dean" << std::endl;
      throw;
    }
  }


  RunThreeJet(InFileNames, IsData, OutFileName, PUFile);

  std::cout<<"About to return from main"<<std::endl;

  return 0;
}
