#ifndef GUARD_NtpRUTopXAna_h
#define GUARD_NtpRUTopXAna_h

//#include "TopBSM/RUTopXAna/interface/NtpReader.h"
#include "RUAnalysis/Analysis/interface/NtpReader.h"
#include <iostream>
#include <vector>
#include <fstream>

#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"

class NtpTriggerEff : public NtpReader
{
  public:
    NtpTriggerEff (std::vector<TString>&, bool const, TString const);
    ~NtpTriggerEff ();

    void Loop ();
    void BookHistograms();
    void WriteHistograms();

    TH1F* h_RunNumber_Base;
    TH1F* h_RunNumber_BaseSel;
    TH1F* h_RunNumber_Sel;
    TH1F*  h_MET_Base;
    TH1F* h_nBJet35_Base;
    TH1F* h_nJet35_Base;
    TH1F* h_Jet0_Base;
    TH1F* h_Jet1_Base;
    TH1F* h_Jet2_Base;
    TH1F* h_Jet3_Base;
    TH1F* h_Jet4_Base;
    TH1F* h_Jet5_Base;
    TH1F* h_Jet6_Base;
    TH1F* h_HT_Base;

    TH1F*  h_MET_BaseSel;
    TH1F* h_nBJet35_BaseSel;
    TH1F* h_nJet35_BaseSel;
    TH1F* h_Jet0_BaseSel;
    TH1F* h_Jet1_BaseSel;
    TH1F* h_Jet2_BaseSel;
    TH1F* h_Jet3_BaseSel;
    TH1F* h_Jet4_BaseSel;
    TH1F* h_Jet5_BaseSel;
    TH1F* h_Jet6_BaseSel;
    TH1F* h_HT_BaseSel;

    std::vector <std::vector<TH1F* > > h_Jet0_BaseSel_pt4_pt6;
    std::vector <std::vector<TH1F* > > h_Jet0_Base_pt4_pt6;

    std::vector <std::vector<TH1F* > > h_Jet4;
    std::vector <std::vector<TH1F* > > h_Jet6;
    
 private:
    TFile* fOutFile;

};






#endif
