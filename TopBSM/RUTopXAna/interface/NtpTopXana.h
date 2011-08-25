#ifndef GUARD_NtpRUTopXAna_h
#define GUARD_NtpRUTopXAna_h

#include "TopBSM/RUTopXAna/interface/NtpReader.h"

#include <iostream>
#include <vector>
#include <fstream>

#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"

class NtpTopXana : public NtpReader
{
  public:
    NtpTopXana (std::vector<TString>&, bool const, TString const);
    ~NtpTopXana ();

    void Loop ();
    void BookHistograms();
    void WriteHistograms();

    //some variables needed
    std::vector<TLorentzVector >      fBJets;
    std::vector<TLorentzVector >      fNoBJets;
    std::vector<TLorentzVector >      fCleanJets;
    
    TH1F* h_NumEvtCut;
    TH1F* h_MET;
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

    std::vector<TH1F*> vh_St;

    std::vector<TH2F*> vh_TransMassLepMET4Jet_vs_LeadingJetPt;
    std::vector<TH1F*> vh_TransMassLepMET1JetB;
    std::vector<TH1F*> vh_Mass3Jet1B;
    std::vector<TH2F*> vh_TransMassLepMET1JetB_vs_Mass3Jet1B;
    //////plots for optimization//////
    std::vector<TH1F*> vh_TransMassLepMET1JetB_pt;
    std::vector<TH1F*> vh_TransMassLepMET1JetB_delphi;
    std::vector<TH1F*> vh_TransMassLepMET1JetB_st;

    std::vector<TH1F*> vh_TransMassLepMET4Jet_pt;
    std::vector<TH1F*> vh_TransMassLepMET4Jet_delphi;
    std::vector<TH1F*> vh_TransMassLepMET4Jet_st;

    std::vector<std::vector<TH1F*> >  vh_TransMassLepMET4Jet_pt_st;
    std::vector<std::vector<TH1F*> >  vh_TransMassLepMET1JetB_pt_st;

    std::vector<TH1F*> vh_ChargeXeta;



    private:
    TFile* fOutFile;

};


















#endif
