#ifndef GUARD_NtpDeanAna_h
#define GUARD_NtpDeanAna_h

#include "TopBSM/RUTopXAna/interface/NtpReader.h"

#include <iostream>
#include <vector>
#include <fstream>

#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"

class NtpDeanAna : public NtpReader
{
  public:
    NtpDeanAna (std::vector<TString>&, bool const, TString const);
    ~NtpDeanAna ();

    void Loop ();

    void DileptonEvents ();
    void LeptonPlusJetsEvents ();


  private:
    TFile* fOutFile;

};


















#endif
