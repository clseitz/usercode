#ifndef GUARD_NtpRUTopXAna_h
#define GUARD_NtpRUTopXAna_h

//#include "TopBSM/RUTopXAna/interface/NtpReader.h"
#include "RUAnalysis/Ntupler/interface/NtpReader.h"
#include <iostream>
#include <vector>
#include <fstream>

#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"

#include "math.h"
#include "TMath.h"
#include "Math/VectorUtil.h"
class NtpThreeJet : public NtpReader
{
  public:
    NtpThreeJet (std::vector<TString>&, bool const, TString const, const TString PUFile);
    ~NtpThreeJet ();

    void Loop ();
    void BookHistograms();
    void WriteHistograms();
    float GetBTagSF (float pt, float eta, int meanminmax);
    float GetLightJetSF (float pt, float eta, int meanminmax);
    //        std::vector<math::XYZVector> makeVecForEventShape(std::vector<JetLV*> jets);
    // std::vector<math::XYZVector> makeVecForEventShape(std::vector<JetLV*> jets, bool only6Jets, ROOT::Math::Boost boost);
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
    TH1F*  h_nTruePileUp;
    TH1F*  h_nTruePileUp_NoWeight;
    TH1F*  h_nVertex;
    TH1F* h_nBJet35;
    TH1F* h_nJet35;
    TH1F* h_Jet0;
    TH1F* h_Jet1;
    TH1F* h_Jet2;
    TH1F* h_Jet3;
    TH1F* h_Jet4;
    TH1F* h_Jet5;
    TH1F* h_Jet6;
    TH1F* h_BJet1;
    TH1F* h_BJet2;
    TH1F* h_BJet3;
    TH1F* h_HT;
    TH1F* h_HMT;

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
    TH1F* h_BJet1_Base;
    TH1F* h_BJet2_Base;
    TH1F* h_BJet3_Base;
    TH1F* h_HT_Base;
    TH1F* h_HMT_Base;
    TH2F* h_NeutralHad_JetPt;
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
    TH1F* h_BJet1_BaseSel;
    TH1F* h_BJet2_BaseSel;
    TH1F* h_BJet3_BaseSel;
    TH1F* h_HT_BaseSel;
    TH1F* h_HMT_BaseSel;
    
    TH1F* h_nBJet35_EvtSel;
    TH1F* h_nJet35_EvtSel;
    TH1F* h_HT_EvtSel;
    TH1F* h_MJ_EvtSel;
    TH1F* h_HMT_EvtSel;
    TH1F* h_MET_EvtSel;
    TH1F* h_Jet0_EvtSel;
    TH1F* h_Jet1_EvtSel;
    TH1F* h_Jet2_EvtSel;
    TH1F* h_Jet3_EvtSel;
    TH1F* h_Jet4_EvtSel;
    TH1F* h_Jet5_EvtSel;
    TH1F* h_Jet6_EvtSel;
    TH1F* h_BJet1_EvtSel;
    TH1F* h_BJet2_EvtSel;
    TH1F* h_BJet3_EvtSel;


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
    TF1  *CSVM_SFb_0to2p4;
    TH1D *CSVM_SFb_errors;

    TF1 *CSVM_SFl_0to2p4;
    TF1 *CSVM_SFl_0to0p8;
    TF1 *CSVM_SFl_0p8to1p6;
    TF1 *CSVM_SFl_1p6to2p4;

    TF1 *CSVM_SFl_0to2p4_min;
    TF1 *CSVM_SFl_0to0p8_min;
    TF1 *CSVM_SFl_0p8to1p6_min;
    TF1 *CSVM_SFl_1p6to2p4_min;

    TF1 *CSVM_SFl_0to2p4_max;
    TF1 *CSVM_SFl_0to0p8_max;
    TF1 *CSVM_SFl_0p8to1p6_max;
    TF1 *CSVM_SFl_1p6to2p4_max;

    double SFb_Unc_MultFactor;
    TF1 *CSVM_SFl_Corr;

    TFile *f_EffMap;

    TH2D *h2_EffMapB;
    TH2D *h2_EffMapC;
    TH2D *h2_EffMapUDSG;


    //make some plots for the triplets
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Mjjj_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Mjjj_Sph4_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >MjjjSym_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH2F* > > > >DeltaM_vs_AvM_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Mjjj_btag_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Mjjj_Sph4_btag_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Mjjj_1btag_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Mjjj_bjet_pt_njet_diag_MCmatch;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Mjjj_bjet_pt_njet_diag_MCcomb;

    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Ntrip_bjet_pt_njet_diag_MCmatch;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Ntrip_bjet_pt_njet_diag_MCcomb;

    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >MjjjSym_bjet_pt_njet_diag_MCmatch;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >MjjjSym_bjet_pt_njet_diag_MCcomb;

    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >P_bjet_pt_njet_diag_MCmatch;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >P_bjet_pt_njet_diag_MCcomb;

    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >h31_bjet_pt_njet_diag_MCmatch;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >h31_bjet_pt_njet_diag_MCcomb;

    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Maxtr_bjet_pt_njet_diag_MCmatch;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Maxtr_bjet_pt_njet_diag_MCcomb;

    std::vector <std::vector <std::vector <std::vector<TH2F* > > > >MjjHigh_MjjMid_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH2F* > > > >MjjHigh_MjjLow_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH2F* > > > >MjjMid_MjjLow_bjet_pt_njet_diag;

    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >M12_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >M13_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >M23_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector<TH2F* > > > Mjjj_sumpt_bjet_pt_njet;
    std::vector <std::vector <std::vector<TH2F* > > > Mjjj_vecpt_bjet_pt_njet;
    std::vector <std::vector <std::vector<TH2F* > > > Mjjj_P_bjet_pt_njet;
    std::vector <std::vector <std::vector<TH1F* > > > DeltaM_bjet_pt_njet;
    std::vector <std::vector <std::vector<TH2F* > > > Mjjj_sumpt_btag_pt_njet;
    std::vector <std::vector <std::vector<TH1F* > > > M4j_pt_njet_diag;
    std::vector <std::vector <std::vector<TH2F* > > > Mjjj_M4j_pt_njet_diag; 

    std::vector <std::vector <std::vector<TH1F* > > >    Aplanarity_bjet_pt_njet;
    std::vector <std::vector <std::vector<TH1F* > > >     Sphericity_bjet_pt_njet;
    std::vector <std::vector <std::vector<TH1F* > > >     Circularity_bjet_pt_njet;
    std::vector <std::vector <std::vector<TH1F* > > >     Isotropy_bjet_pt_njet;
    std::vector <std::vector <std::vector<TH1F* > > >     C_bjet_pt_njet;
    std::vector <std::vector <std::vector<TH1F* > > >     D_bjet_pt_njet;

    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >MET_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >HT_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >P_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >MET_over_HT_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >HMT_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >nBJet35_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >nJet35_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >nVertex_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Jet0_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Jet1_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Jet2_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Jet3_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Jet4_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Jet5_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >Jet6_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >BJet1_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >BJet2_bjet_pt_njet_diag;
    std::vector <std::vector <std::vector <std::vector<TH1F* > > > >BJet3_bjet_pt_njet_diag;
    


 private:
    TFile* fOutFile;
    TFile* fPUFile;

};


class JetLV : public TLorentzVector
{
public:
	JetLV(double x, double y, double z, double energy) :
		TLorentzVector(x, y, z, energy),
		btagged(hasBtag)
	{
		hasBtag = false;
	}
	
	~JetLV()
	{
	}
	
	const bool &btagged; // Read-only access to b tag status
	
	void setBtag(bool isBjet)
	{
		hasBtag = isBjet;
	}
	
protected:
	bool hasBtag;
};







#endif
