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
    
    TH1F* h_NumEvtCutMuon;
    TH1F* h_NumEvtCutElectron;
    TH1F* h_NumEvtCut;

    TH1F*  h_ept;
    TH1F* h_mpt;
    TH1F*    h_MET;
    TH1F* h_Jet0;
    TH1F* h_Jet1;
    TH1F* h_Jet2;
    TH1F* h_Jet4;
    TH1F* h_Jet5;
    
    
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
    std::vector<TH1F*> vh_ChargeXeta;
    std::vector<TH1F*> vh_TransMass3Jet1B;
    std::vector<TH1F*> vh_DeltaPhiLep1Jet;
    //////plots for optimization//////
    std::vector<TH1F*> vh_TransMassLepMET1JetB_pt;
    std::vector<TH1F*> vh_TransMassLepMET1JetB_delphi;
    std::vector<TH1F*> vh_TransMassLepMET1JetB_st;

    std::vector<TH1F*> vh_TransMassLepMET4Jet_pt;
    std::vector<TH1F*> vh_TransMassLepMET4Jet_delphi;
    std::vector<TH1F*> vh_TransMassLepMET4Jet_st;

    std::vector<std::vector<TH1F*> >  vh_TransMassLepMET4Jet_pt_st;
    std::vector<std::vector<TH1F*> >  vh_TransMassLepMET1JetB_pt_st;

    //MC plots
    TH1F* h_MCwprimeMassPos;
    TH1F* h_MCwprimeMassNeg;
    TH1F* h_MCwprimeMETMassPos;
    TH1F* h_MCwprimeMETMassNeg;
    TH1F* h_MCminChi2Pos;
    TH1F* h_MCminChi2Neg;
    TH1F* h_MCPhidLepTopNeg;
    TH1F* h_MCPhidLepTopPos;
    TH1F* h_MCPhiWpTopNeg;
    TH1F* h_MCPhiWpTopPos;
    TH1F* h_MCPhiWpTop;
    TH1F* h_MCwprimeMassGood;
    TH1F* h_MCwprimeMassBad;

    //MC 4jet top asymmetry
    TH1F* h_MCdeltaEtaTopAntiTop;
    TH1F* h_MC_posneg_DeltaEta;

    //some plots with chi2 selection applied
    TH1F* h_minChi2Pos;
    TH1F* h_minChi2Neg;
    TH1F* h_TopLepJetMassPos;
    TH1F* h_TopLepJetMassNeg;
    TH1F* h_TopLepJetMassGood;
    TH1F* h_TopLepJetMassBad;
    TH2F* h_TopJetMass_Good_vs_Bad;
    TH1F*  h_dPhiTopLepJetPos;
    TH1F* h_dPhiTopLepJetNeg;
    
    TH2F* h_TopLepSumptPos;
    TH2F* h_TopLepSumptNeg;
    TH2F* h_TopHadSumptPos;
    TH2F* h_TopHadSumptNeg;

    TH1F* h_TopLepMass;
    TH1F* h_TopHadMass;


    
 private:
    TFile* fOutFile;

};






#endif
