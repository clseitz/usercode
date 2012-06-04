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

class NtpThreeJet : public NtpReader
{
  public:
    NtpThreeJet (std::vector<TString>&, bool const, TString const);
    ~NtpThreeJet ();

    void Loop ();
    void BookHistograms();
    void WriteHistograms();

    //some variables needed
    /*   std::vector<TLorentzVector >      fBJets;
   std::vector<TLorentzVector >      fNoBJets;
    std::vector<TLorentzVector >      fCleanJets;
    std::vector<TLorentzVector >      fCleanJets20;
    */    
    TH1F* h_NumEvtCutMuon;
    TH1F* h_NumEvtCutElectron;
    TH1F* h_NumEvtCut;
    TH1F* h_PossibleTrigger;

    TH1F*  h_ept;
    TH1F* h_mpt;
    TH1F* h_mPFIso;
    TH1F*  h_mindRMuonJet;
    TH2F*  h_mindRMuonJet_mPFIso;
    TH1F*  h_MET;
    TH1F* h_nBJet35;
    TH1F* h_nJet35;
    TH1F* h_Jet0;
    TH1F* h_Jet1;
    TH1F* h_Jet2;
    TH1F* h_Jet3;
    TH1F* h_Jet4;
    TH1F* h_Jet5;
    TH1F* h_Jet6;
    TH1F* h_HT;

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
    
    
    TH1F* h_nBJet35_EvtSel;
    TH1F* h_nJet35_EvtSel;
    TH1F* h_HT_EvtSel;
    TH1F* h_MET_EvtSel;
    TH1F* h_Jet0_EvtSel;
    TH1F* h_Jet1_EvtSel;
    TH1F* h_Jet2_EvtSel;
    TH1F* h_Jet3_EvtSel;
    TH1F* h_Jet4_EvtSel;
    TH1F* h_Jet5_EvtSel;
    TH1F* h_Jet6_EvtSel;


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



    //make some plots for the triplets
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Mjjj_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector<TH2F* > > > Mjjj_sumpt_bjet_pt_njet;
    std::vector <std::vector <std::vector<TH1F* > > > M4j_pt_njet_diag;
    std::vector <std::vector <std::vector<TH2F* > > > Mjjj_M4j_pt_njet_diag; 

    
 private:
    TFile* fOutFile;

};






#endif
