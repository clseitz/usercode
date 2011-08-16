////////////////////////////////////////////////////////////////////
//
// Dean Andrew Hidas <Dean.Andrew.Hidas@cern.ch>
//
// Created on: Mon Jul 25 14:21:29 CEST 2011
//
////////////////////////////////////////////////////////////////////


#include <iostream>
#include <cstdlib>

#include "TString.h"

#include "TopBSM/RUTopXAna/interface/NtpTopXana.h"

int RunTopXana (std::vector<TString>& InFileNames, bool const IsData, TString const OutFileName)
{
  NtpTopXana Ana(InFileNames, IsData, OutFileName);
  //std::cout<<"Book Histograms"<<std::endl;

  Ana.BookHistograms();
  // std::cout<<"Loop through Events"<<std::endl;

  Ana.Loop();
  // std::cout<<"Write Histograms"<<std::endl;

  Ana.WriteHistograms();
  return 0;
}


int main (int argc, char* argv[])
{
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " [OutFileName] [FileName]s" << std::endl;
    return 1;
  }

  // currently default to false
  bool const IsData = false;

  // Output file name
  TString const OutFileName = argv[1];

  // Grab the filename itself for a quick check
  TString const JustFileName = OutFileName.Last('/') >= 0 ? OutFileName( OutFileName.Last('/') + 1, OutFileName.Length() - OutFileName.Last('/') - 1) : OutFileName;

  // Grab input file names
  std::vector<TString> InFileNames;
  for (int i = 2; i < argc; ++i) {
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


  RunTopXana(InFileNames, IsData, OutFileName);

  return 0;
}
