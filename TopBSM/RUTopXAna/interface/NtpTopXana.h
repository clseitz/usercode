#ifndef GUARD_NtpRUTopXAna_h
#define GUARD_NtpRUTopXAna_h

#include "TopBSM/RUTopXAna/interface/NtpReader.h"
#include "TLorentzVector.h"
#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include <vector>
#include <fstream>

class NtpTopXana : public NtpReader
{
  public:
    NtpTopXana (std::vector<TString>&, bool const);
    ~NtpTopXana ();

    void Loop ();
    void BookHistograms();
    void WriteHistograms();

    //some variables needed
    std::vector<TLorentzVector >      fBJets;
    std::vector<TLorentzVector >      fNoBJets;
    std::vector<TLorentzVector >      fCleanJets;
    TH1F* h_NumEvtCut;
    //lots of plots
    std::vector <std::string > VarList;
    std::vector <std::string > CutList;
    std::vector<TH1F*> vh_SumptSig4Highest;
    std::vector<TH1F*> vh_SumptSig4SecondHighest;
    std::vector<TH1F*> vh_TransMassLepMET4Jet;
    std::vector<TH1F*> vh_TransMassLepMET5Jet;
    std::vector<TH1F*> vh_TransMassLepMET4JetB;
    std::vector<TH1F*> vh_TransMassLepMET5JetB;
    
    std::vector<TH1F*> vh_Mass3Jet2B;
    std::vector<TH1F*> vh_MassLep1Jet;
    std::vector<TH1F*> vh_MassLep1B;
    std::vector<TH2F*> vh_MassLepB_vs_SumPt;
    std::vector<TH1F*> vh_DeltaPhiLepMET;
    
    std::vector<TH1F*> vh_LepBDiag50_Upper160_4Jet;
    std::vector<TH1F*> vh_LepBDiag50_Upper160_3Jet1B;
    std::vector<TH1F*> vh_LeadingJetPt;
    std::vector<TH2F*> vh_TransMassLepMET4Jet_vs_LeadingJetPt;

};


















#endif
