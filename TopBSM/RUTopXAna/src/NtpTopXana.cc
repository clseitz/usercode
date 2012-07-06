#include "TopBSM/RUTopXAna/interface/NtpTopXana.h"


NtpTopXana::NtpTopXana (std::vector<TString>& InFileNames, bool const IsData) : NtpReader(InFileNames, IsData)
{
}

NtpTopXana::~NtpTopXana ()
{
}



void NtpTopXana::Loop ()
{
  // Run over all entries and do what you like!

  for (int ientry = 0; GetEntry(ientry) > 0; ++ientry) {
    if (ientry % 1000 == 0) {
      printf("Processing entry: %i\n", ientry);
    }

    if (nElectrons == 2) {
      printf("2 Electrons Pt: %12.1f %12.1f\n", ept[0], ept[1]);
    }

  }

  return;
}
