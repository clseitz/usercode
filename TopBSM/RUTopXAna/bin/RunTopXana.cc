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

int RunTopXana (std::vector<TString>& InFileNames, bool const IsData)
{
  NtpTopXana Ana(InFileNames, IsData);

  Ana.Loop();

  return 0;
}


int main (int argc, char* argv[])
{
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " [IsData] [FileName]s" << std::endl;
    return 1;
  }

  bool const IsData = atoi(argv[1]) == 1 ? true : false;

  std::vector<TString> InFileNames;
  for (int i = 2; i < argc; ++i) {
    InFileNames.push_back(argv[i]);
  }

  RunTopXana(InFileNames, IsData);

  return 0;
}
