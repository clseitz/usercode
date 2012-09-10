
//#Includetr "RUAnalysis/Ntupler/interface/Ntupler.h"
#include "RUAnalysis/Analysis/interface/NtpThreeJet.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "TLorentzVector.h"
#include "TFile.h"
#include "math.h"
#include "../interface/BTagSFUtil.h"
#include "RUAnalysis/Analysis/interface/LumiReweightingStandAlone.h"

using namespace std;

NtpThreeJet::NtpThreeJet (std::vector<TString>& InFileNames, bool const IsData, TString const OutFileName) : NtpReader(InFileNames, IsData)
{
  fOutFile = new TFile(OutFileName, "recreate");
  if (!fOutFile->IsOpen()) {
    std::cerr << "ERROR: cannot open output root file " << OutFileName << std::endl;
    throw;
  }
}

NtpThreeJet::~NtpThreeJet ()
{
  /*  if (fOutFile) {
    fOutFile->Write();
    fOutFile->Close();
    delete fOutFile;
    }*/
}


void NtpThreeJet::BookHistograms()
{


  char hNAME[99];
 
  //before cuts, just the ones that where already in the ntuple
  h_PossibleTrigger  = new TH1F("PossibleTrigger", "PossibleTrigger",30,0,30);   h_PossibleTrigger->Sumw2();

  h_mindRMuonJet = new TH1F("mindRMuonJet", "mindRMuonJet",100,0,5);   h_mindRMuonJet->Sumw2();
  h_mindRMuonJet_mPFIso = new TH2F("mindRMuonJet_mPFIso", "mindRMuonJet_mPFIso",200,0,10,100,0,5);  h_mindRMuonJet_mPFIso->Sumw2();
  h_ept= new TH1F("ept", "ept",200,0,1000); h_ept->Sumw2();
  h_mpt= new TH1F("mpt", "mpt",200,0,1000); h_mpt->Sumw2();
  h_mPFIso= new TH1F("mPFIso", "mPFIso",200,0,10); h_mPFIso->Sumw2();
  //befor cuts
  h_MET = new TH1F("MET", "MET",200,0,1000); h_MET->Sumw2();
  h_nTruePileUp = new TH1F("nTruePileUp", "nTruePileUp",100,0,100); h_nTruePileUp->Sumw2();
  h_nTruePileUp_NoWeight = new TH1F("nTruePileUp_NoWeight", "nTruePileUp_NoWeight",100,0,100); h_nTruePileUp_NoWeight->Sumw2();
  h_nVertex = new TH1F("nVertex", "nVertex",100,0,100); h_nVertex->Sumw2();
  h_HT = new TH1F("HT", "HT",400,0,4000); h_HT->Sumw2();
  h_nBJet35  = new TH1F("nBJet35", "nBJet35",20,0,20); h_nBJet35->Sumw2();
  h_nJet35  = new TH1F("nJet35", "nJet35",20,0,20); h_nJet35->Sumw2();
  h_Jet0= new TH1F("Jet0", "Jet0",200,0,1000); h_Jet0->Sumw2();
  h_Jet1= new TH1F("Jet1", "Jet1",200,0,1000); h_Jet1->Sumw2();
  h_Jet2= new TH1F("Jet2", "Jet2",200,0,1000); h_Jet2->Sumw2();
  h_Jet3= new TH1F("Jet3", "Jet3",200,0,1000); h_Jet3->Sumw2();
  h_Jet4= new TH1F("Jet4", "Jet4",200,0,1000); h_Jet4->Sumw2();
  h_Jet5= new TH1F("Jet5", "Jet5",200,0,1000); h_Jet5->Sumw2();
  h_Jet6= new TH1F("Jet6", "Jet6",200,0,1000); h_Jet6->Sumw2();
  h_NeutralHad_JetPt= new TH2F("NeutralHad_JetPt", "NeutralHad_JetPt",200,0,1000,100,0,1);  h_NeutralHad_JetPt->Sumw2();

  //after cuts
  h_MET_EvtSel = new TH1F("MET_EvtSel", "MET_EvtSel",200,0,1000); h_MET_EvtSel->Sumw2();
  h_HT_EvtSel = new TH1F("HT_EvtSel", "HT_EvtSel",400,0,4000); h_HT_EvtSel->Sumw2();
  h_nBJet35_EvtSel  = new TH1F("nBJet35_EvtSel", "nBJet35_EvtSel",20,0,20); h_nBJet35_EvtSel->Sumw2();
  h_nJet35_EvtSel  = new TH1F("nJet35_EvtSel", "nJet35_EvtSel",20,0,20); h_nJet35_EvtSel->Sumw2();
  h_Jet0_EvtSel= new TH1F("Jet0_EvtSel", "Jet0_EvtSel",200,0,1000); h_Jet0_EvtSel->Sumw2();
  h_Jet1_EvtSel= new TH1F("Jet1_EvtSel", "Jet1_EvtSel",200,0,1000); h_Jet1_EvtSel->Sumw2();
  h_Jet2_EvtSel= new TH1F("Jet2_EvtSel", "Jet2_EvtSel",200,0,1000); h_Jet2_EvtSel->Sumw2();
  h_Jet3_EvtSel= new TH1F("Jet3_EvtSel", "Jet3_EvtSel",200,0,1000); h_Jet3_EvtSel->Sumw2();
  h_Jet4_EvtSel= new TH1F("Jet4_EvtSel", "Jet4_EvtSel",200,0,1000); h_Jet4_EvtSel->Sumw2();
  h_Jet5_EvtSel= new TH1F("Jet5_EvtSel", "Jet5_EvtSel",200,0,1000); h_Jet5_EvtSel->Sumw2();
  h_Jet6_EvtSel= new TH1F("Jet6_EvtSel", "Jet6_EvtSel",200,0,1000); h_Jet6_EvtSel->Sumw2();
  //TriggerPlots
  
  h_MET_Base = new TH1F("MET_Base", "MET_Base",200,0,1000); h_MET_Base->Sumw2();
  h_HT_Base = new TH1F("HT_Base", "HT_Base",400,0,4000); h_HT_Base->Sumw2();
  h_nBJet35_Base   = new TH1F("nBJet35_Base", "nBJet35_Base",20,0,20); h_nBJet35_Base->Sumw2();
  h_nJet35_Base   = new TH1F("nJet20_Base", "nJet20_Base",20,0,20); h_nJet35_Base->Sumw2();
  h_Jet0_Base = new TH1F("Jet0_Base", "Jet0_Base",200,0,1000); h_Jet0_Base->Sumw2();
  h_Jet1_Base = new TH1F("Jet1_Base", "Jet1_Base",200,0,1000); h_Jet1_Base->Sumw2();
  h_Jet2_Base = new TH1F("Jet2_Base", "Jet2_Base",200,0,1000); h_Jet2_Base->Sumw2();
  h_Jet3_Base = new TH1F("Jet3_Base", "Jet3_Base",200,0,1000); h_Jet3_Base->Sumw2();
  h_Jet4_Base = new TH1F("Jet4_Base", "Jet4_Base",200,0,1000); h_Jet4_Base->Sumw2();
  h_Jet5_Base = new TH1F("Jet5_Base", "Jet5_Base",200,0,1000); h_Jet5_Base->Sumw2();
  h_Jet6_Base = new TH1F("Jet6_Base", "Jet6_Base",200,0,1000); h_Jet6_Base->Sumw2();

  h_MET_BaseSel = new TH1F("MET_BaseSel", "MET_BaseSel",200,0,1000); h_MET_BaseSel->Sumw2();
  h_HT_BaseSel = new TH1F("HT_BaseSel", "HT_BaseSel",400,0,4000); h_HT_BaseSel->Sumw2();
  h_nBJet35_BaseSel   = new TH1F("nBJet35_BaseSel", "nBJet35_BaseSel",20,0,20); h_nBJet35_BaseSel->Sumw2();
  h_nJet35_BaseSel   = new TH1F("nJet20_BaseSel", "nJet20_BaseSel",20,0,20); h_nJet35_BaseSel->Sumw2();
  h_Jet0_BaseSel = new TH1F("Jet0_BaseSel", "Jet0_BaseSel",200,0,1000); h_Jet0_BaseSel->Sumw2();
  h_Jet1_BaseSel = new TH1F("Jet1_BaseSel", "Jet1_BaseSel",200,0,1000); h_Jet1_BaseSel->Sumw2();
  h_Jet2_BaseSel = new TH1F("Jet2_BaseSel", "Jet2_BaseSel",200,0,1000); h_Jet2_BaseSel->Sumw2();
  h_Jet3_BaseSel = new TH1F("Jet3_BaseSel", "Jet3_BaseSel",200,0,1000); h_Jet3_BaseSel->Sumw2();
  h_Jet4_BaseSel = new TH1F("Jet4_BaseSel", "Jet4_BaseSel",200,0,1000); h_Jet4_BaseSel->Sumw2();
  h_Jet5_BaseSel = new TH1F("Jet5_BaseSel", "Jet5_BaseSel",200,0,1000); h_Jet5_BaseSel->Sumw2();
  h_Jet6_BaseSel = new TH1F("Jet6_BaseSel", "Jet6_BaseSel",200,0,1000); h_Jet6_BaseSel->Sumw2();
  

  cout<<"before histos"<<endl;
  for(int b=0; b<5; b++){
  for (int i=0; i<7; i++){
    int iPt=30+i*10;
    //Triplet mass plots
    Mjjj_sumpt_bjet_pt_njet.push_back(std::vector<std::vector<TH2F*> >());
    Mjjj_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    //Dalitz Plots
    MjjHigh_MjjMid_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH2F*> > >());
    MjjHigh_MjjLow_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH2F*> > >());
    MjjMid_MjjLow_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH2F*> > >());
    //Dijet mass plots
    M12_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    M13_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    M23_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    for(int k=0; k<3; k++){
      int iNjet=k+6;

      Mjjj_sumpt_bjet_pt_njet[b].push_back(std::vector<TH2F*> ());
      sprintf(hNAME, "Mjjj_sumpt_bjet%i_pt%i_GE%ijet", b, iPt,iNjet);
      Mjjj_sumpt_bjet_pt_njet[b][i].push_back(new TH2F(hNAME,hNAME,200,0,2000,200,0,2000));
      Mjjj_sumpt_bjet_pt_njet[b][i][k]->Sumw2();
      Mjjj_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());

      MjjHigh_MjjMid_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH2F*> > ());
      MjjHigh_MjjLow_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH2F*> > ());
      MjjMid_MjjLow_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH2F*> > ());

      M12_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      M13_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      M23_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      for(int j=0; j<20; j++){
	
	int iDiag=j*10+40;
	
	Mjjj_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
	sprintf(hNAME, "Mjjj_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);
	Mjjj_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,200,0,2000));
	Mjjj_bjet_pt_njet_diag[b][i][k][j]->Sumw2();
	
	MjjHigh_MjjMid_bjet_pt_njet_diag[b][i].push_back(std::vector<TH2F*> ());
	sprintf(hNAME, " MjjHigh_MjjMid_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);
	MjjHigh_MjjMid_bjet_pt_njet_diag[b][i][k].push_back(new TH2F(hNAME,hNAME,100,0,1,100,0,1));
	MjjHigh_MjjMid_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	MjjHigh_MjjLow_bjet_pt_njet_diag[b][i].push_back(std::vector<TH2F*> ());
	sprintf(hNAME, " MjjHigh_MjjLow__bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);
	MjjHigh_MjjLow_bjet_pt_njet_diag[b][i][k].push_back(new TH2F(hNAME,hNAME,100,0,1,100,0,1));
	MjjHigh_MjjLow_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	MjjMid_MjjLow_bjet_pt_njet_diag[b][i].push_back(std::vector<TH2F*> ());
	sprintf(hNAME, " MjjHigh_MjjLow_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);
	MjjMid_MjjLow_bjet_pt_njet_diag[b][i][k].push_back(new TH2F(hNAME,hNAME,100,0,1,100,0,1));
	MjjMid_MjjLow_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	M12_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
	sprintf(hNAME, "M12_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);
	M12_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,200,0,2000));
	M12_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	M13_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
	sprintf(hNAME, "M13_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);
	M13_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,200,0,2000));
	M13_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	M23_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
	sprintf(hNAME, "M23_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);
	M23_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,200,0,2000));
	M23_bjet_pt_njet_diag[b][i][k][j]->Sumw2();
      }
    }
  }
  }
  cout<<"after histos"<<endl;
 return;
}
 
void NtpThreeJet::WriteHistograms()
{cout<<"made it here"<<endl;
  char FOLDER[100];
  fOutFile->cd();

   fOutFile->mkdir("Events");
   fOutFile->cd("Events");
   h_PossibleTrigger->Write();

   h_ept->Write();
   h_mpt->Write();
   h_mPFIso->Write();
   h_mindRMuonJet->Write();
   h_mindRMuonJet_mPFIso->Write();
   h_MET->Write();
   h_nTruePileUp->Write();
   h_nTruePileUp_NoWeight->Write();
   h_nVertex->Write();
   h_nBJet35->Write();
   h_nJet35->Write();
   h_HT->Write();
   h_Jet0->Write();
   h_Jet1->Write();
   h_Jet2->Write();
   h_Jet3->Write();
   h_Jet4->Write();
   h_Jet5->Write();
   h_Jet6->Write();
   h_NeutralHad_JetPt->Write();
   fOutFile->mkdir("Trigger");
   fOutFile->cd("Trigger");

   h_MET_Base->Write();
   h_nBJet35_Base->Write();
   h_nJet35_Base->Write();
   h_HT_Base->Write();
   h_Jet0_Base->Write();
   h_Jet1_Base->Write();
   h_Jet2_Base->Write();
   h_Jet3_Base->Write();
   h_Jet4_Base->Write();
   h_Jet5_Base->Write();
   h_Jet6_Base->Write();

   h_MET_BaseSel->Write();
   h_nBJet35_BaseSel->Write();
   h_nJet35_BaseSel->Write();
   h_HT_BaseSel->Write();
   h_Jet0_BaseSel->Write();
   h_Jet1_BaseSel->Write();
   h_Jet2_BaseSel->Write();
   h_Jet3_BaseSel->Write();
   h_Jet4_BaseSel->Write();
   h_Jet5_BaseSel->Write();
   h_Jet6_BaseSel->Write();


   TDirectory* triplets=fOutFile->mkdir("Triplets");
   fOutFile->cd("Triplets");
   h_MET_EvtSel->Write();
   h_nBJet35_EvtSel->Write();
   h_nJet35_EvtSel->Write();
   h_HT_EvtSel->Write();
   h_Jet0_EvtSel->Write();
   h_Jet1_EvtSel->Write();
   h_Jet2_EvtSel->Write();
   h_Jet3_EvtSel->Write();
   h_Jet4_EvtSel->Write();
   h_Jet5_EvtSel->Write();
   h_Jet6_EvtSel->Write();
   for (int b=0; b<5; b++){
     sprintf(FOLDER, "bjet_%i", b);
     TDirectory* now=triplets->mkdir(FOLDER);
     triplets->cd(FOLDER);
       for (int i=0; i<7; i++){
	 sprintf(FOLDER, "jetpt_%i", i*10+30);
	 now->mkdir(FOLDER);
	 now->cd(FOLDER);
	 for (int k=0; k<3; k++){
	   Mjjj_sumpt_bjet_pt_njet[b][i][k]->Write();
	   for(int j=0; j<20; j++){ 
	   
	     Mjjj_bjet_pt_njet_diag[b][i][k][j]->Write();  
	     MjjHigh_MjjMid_bjet_pt_njet_diag[b][i][k][j]->Write();
	     MjjHigh_MjjLow_bjet_pt_njet_diag[b][i][k][j]->Write();
	     MjjMid_MjjLow_bjet_pt_njet_diag[b][i][k][j]->Write();

	     /*M12_bjet_pt_njet_diag[b][i][k][j]->Write();
	     M13_bjet_pt_njet_diag[b][i][k][j]->Write();
	     M23_bjet_pt_njet_diag[b][i][k][j]->Write();
	     */
	   }
	 }
       }
   }
   
  return;
}
  

void NtpThreeJet::Loop ()
{

  /////////////////IMPORTANT DEFINE SOME CUTS//////////////////
  /////////////////////////////////////////////////////////////
  //St cut
  float st_cut=700.0;
  //leadin jet pt cut
  float pt0_cut=180.0;
  float pt1_cut=90.0;
  int njetsMin=6;
  bool DoPileUpReweight=true;
  bool DoBtagSF=true;  
////////////////////////////////////////////////////////////

  // Run over all entries and do what you like!
  int countallhad=0;
  int countlep=0;
  int countsemilep=0;
  
  reweight::LumiReWeighting LumiWeights_;
  std::vector< float > DataJun01 ;
  std::vector< float > Summer2012;
  float Summer2012_f[60] = { 2.344E-05,    2.344E-05,    2.344E-05,    2.344E-05,    4.687E-04,    4.687E-04,    7.032E-04,    9.414E-04,
			     1.234E-03,    1.603E-03,    2.464E-03,    3.250E-03,    5.021E-03,    6.644E-03,    8.502E-03,    1.121E-02,
			     1.518E-02,    2.033E-02,       2.608E-02,    3.171E-02,    3.667E-02,    4.060E-02,    4.338E-02,    4.520E-02,
			     4.641E-02,    4.735E-02,    4.816E-02,    4.881E-02,    4.917E-02,      4.909E-02,    4.842E-02,    4.707E-02,
			     4.501E-02,    4.228E-02,    3.896E-02,    3.521E-02,    3.118E-02,    2.702E-02,    2.287E-02,      1.885E-02,
			     1.508E-02,    1.166E-02,    8.673E-03,    6.190E-03,    4.222E-03,    2.746E-03,    1.698E-03,    9.971E-04,
			     5.549E-04,    2.924E-04, 1.457E-04,    6.864E-05,    3.054E-05,    1.282E-05,    5.081E-06,    1.898E-06,
			     6.688E-07,    2.221E-07,    6.947E-08,    2.047E-08
  };
  float data_f[60]={0,8.66979e-07,1.99567e-06,7.0944e-06,0.00115866,0.00304481,9.37811e-05,0.000438788,0.00369376,
		    0.0132685,0.0250747,0.035147,0.0466437,0.0612746,0.0752654,0.0879549,0.0977272,0.0971447,
		    0.0854517,0.0699568,0.0561969,0.0454351,0.0372194,0.0307875,0.0256272,0.0213495,0.0176728,
		    0.014462,0.0116675,0.00926419,0.00722899,0.00553611,0.00415629,0.0030565,0.00220048,0.00155038,
		    0.00106882,0.00072095,0.000475842,0.000307359,0.000194338,0.000120318,7.29651e-05,4.33587e-05,
		    2.52569e-05,1.44273e-05,8.08416e-06,4.44472e-06,2.39826e-06,1.27011e-06,0.00018054};
  for( int z=0; z<50; ++z) {
    Summer2012.push_back(Summer2012_f[z]);
    DataJun01.push_back(data_f[z]);
  }
  
  LumiWeights_ = reweight::LumiReWeighting(Summer2012,DataJun01);
  
  for (int ientry = 0; GetEntry(ientry) > 0; ++ientry) {

    //do pile up reweighintg
	
    double MyWeight = LumiWeights_.weight(nTruePileUp);
    double weight=1;
    //    if(!DataIs) weight=MyWeight;
    //    cout<<nTruePileUp<<" "<<weight<<endl;
  ///////////////////Clear out variables/////////////////////
    std::vector<TLorentzVector* >      fBJets;
    std::vector<TLorentzVector* >      fNoBJets;
    std::vector<TLorentzVector* >      fCleanJets;
    std::vector<TLorentzVector* >      fTestJets;
    std::vector<TLorentzVector* >      fCleanJets20;  
    std::vector<float >   sumScalarPtTriplet;
    std::vector<float >   massTriplet;

    std::vector<float >   massDoublet12;
    std::vector<float >   massDoublet13;
    std::vector<float >   massDoublet23;

    std::vector<float >   massDoubletHigh;
    std::vector<float >   massDoubletMid;
    std::vector<float >   massDoubletLow;

    std::vector<float >   sumVectorPtTriplet;
    std::vector <std::vector<TLorentzVector* > > Triplet;

  Triplet.clear();    sumScalarPtTriplet.clear();  sumVectorPtTriplet.clear(); massTriplet.clear();
  fBJets.clear(); fNoBJets.clear();fCleanJets.clear();    fCleanJets20.clear(); fTestJets.clear(); 
  massDoublet12.clear();  massDoublet13.clear(); massDoublet23.clear();
  massDoubletHigh.clear();  massDoubletMid.clear();  massDoubletLow.clear();

  ////////////////////////////////////////////////////////////
    

    if (ientry % 1000 == 0) {
      printf("Processing entry: %i\n", ientry);
    }
    //cout<<HasSelTrigger<<" "<<HasBaseTrigger<<endl;
    if(1==1){//MSquark == 375 && MLSP ==75){

    //JETS///////
    //Count all the jets above 35 Gev, also calculated HT=SumptAllJet, count number of b-jets
    int nJet20=0; int nJet35=0; int nBJet35=0; int nNoBJet35=0; 

    float SumptAllJet=0;
    float SumptAllJet20=0;
    vector<TLorentzVector* > fdummyCleanJets;
    int dummycounter=0;     
    //    cout<<"Shouldn't be anyting "<<fCleanJets.size()<<" "<<nPFJets<<" "<<sizeof(jet_PF_pt)<<endl;
        for (int i=0; i<nPFJets; i++){
	  //cout<<i<<". th jet: "<<jet_PF_pt[i]<<" eta: "<< fabs(jet_PF_eta[i])<<endl;
      TLorentzVector* Jet= new TLorentzVector(jet_PF_px[i],jet_PF_py[i],jet_PF_pz[i],jet_PF_e[i]);
      TLorentzVector* dummyJet= new TLorentzVector (0,0,0,0);

      if (jet_PF_pt[i]>20.0 && fabs(jet_PF_eta[i])<2.5){
	nJet20++;
	fCleanJets20.push_back(Jet);
	SumptAllJet20=SumptAllJet20+jet_PF_pt[i];
	if(jet_PF_pt[i]>35.0){
	SumptAllJet=SumptAllJet+jet_PF_pt[i];
	fCleanJets.push_back(Jet);
	nJet35++;
	h_NeutralHad_JetPt->Fill(jet_PF_pt[i],jet_PF_NeutralHad[i],weight);
	dummycounter++;
	//implementing b-tagging scale factors
	int jet_flavor =jet_PF_PartonFlav[i];
	float jet_pt = jet_PF_pt[i];
	float jet_phi = jet_PF_phi[i];
        float jet_eta = jet_PF_eta[i];
	bool isTagged = false;
	if (bdiscCSV_PF[i] > 0.679) isTagged = true;
	//Add isData check here (need to add variable to the ntuple first)
	//set a unique seed                                                                                                                                                 
	//	cout<<"before function:"<<isTagged<<" CSV:"<<bdiscCSV_PF[i]<<endl;
	if(!DataIs){
        double phi = jet_phi;
        double sin_phi = sin(phi*1000000);
        double seed = abs(static_cast<int>(sin_phi*100000));
	//Initialize class                                                                                                                                                
        BTagSFUtil* btsfutil = new BTagSFUtil( seed );
        bool temp=isTagged;
	//modify tags                                                                                                                                                      
	double BTagSF =  btsfutil->GetBTagSF(jet_pt,jet_eta,0);
        double BTageff =  btsfutil->GetBTageff();
        double LightJetSF =  btsfutil->GetLightJetSF(jet_pt,jet_eta,0);
        double LightJeteff =  btsfutil->GetLightJeteff(jet_pt,jet_eta,0); //no uncertainties given                                                                           

	btsfutil->modifyBTagsWithSF(isTagged, jet_flavor, BTagSF, BTageff, LightJetSF, LightJeteff);
	if (temp != isTagged) cout<<"GOT ONE!!!!!!!!!!!: "<<temp<<"  "<<isTagged<<" "<<jet_flavor<<"  "<<bdiscCSV_PF[i]<<endl;
	}
	if (isTagged)
	  {
	    nBJet35++;
	    fBJets.push_back(Jet);
	    fdummyCleanJets.push_back(dummyJet);
	  }
	if (!isTagged)
	  {
	    nNoBJet35++;
	    fNoBJets.push_back(Jet);
	    fdummyCleanJets.push_back(Jet);

	  }
	}
      }
	}
	//cout<<nTruePileUp<<" "<<MyWeight<<" "<<weight<<endl;



     //MUON/////
     //make some plots for the muons
    vector<TLorentzVector* > fdummyCleanMuons;
    for (int i=0; i<nMuons; i++){
       TLorentzVector Muon(mpx[i],mpy[i],mpz[i],me[i]);
       //lets look at the leading muon for now
       if(i==0){
	 h_mPFIso->Fill(mPFIso[i],weight);
	 h_mpt->Fill(Muon.Pt(),weight);
       //calcualte the minimum dR to one of the jets
       float mindRMuonJet=9999;
       for (int j=0; j<nJet35; j++){
	 TLorentzVector Jet1(fCleanJets[j]->Px(),fCleanJets[j]->Py(),fCleanJets[j]->Pz(),fCleanJets[j]->E());
	 float dRMuonJet=Jet1.DeltaR(Muon);
	 if (dRMuonJet < mindRMuonJet) mindRMuonJet=dRMuonJet;
	 //	 cout<<"All: "<<dRMuonJet<<endl;

       }
       //cout<<mindRMuonJet<<endl;
       h_mindRMuonJet->Fill(mindRMuonJet,weight);

       h_mindRMuonJet_mPFIso->Fill(mPFIso[i],mindRMuonJet,weight);
       }
     }
    
     ////TRIGGER////////////
     if(nJet20>=4){
     if(HasBaseTrigger){
       h_MET_Base->Fill(pfMET,weight);
       h_HT_Base->Fill(SumptAllJet20,weight);
       h_Jet0_Base->Fill(fCleanJets20[0]->Pt(),weight);
       h_Jet1_Base->Fill(fCleanJets20[1]->Pt(),weight);
       h_Jet2_Base->Fill(fCleanJets20[2]->Pt(),weight);
       h_Jet3_Base->Fill(fCleanJets20[3]->Pt(),weight);
       if(nJet20>=5) h_Jet4_Base->Fill(fCleanJets20[4]->Pt(),weight);
       if(nJet20>=6) h_Jet5_Base->Fill(fCleanJets20[5]->Pt(),weight);
            if(HasSelTrigger){
	      h_MET_BaseSel->Fill(pfMET,weight);
	      h_HT_BaseSel->Fill(SumptAllJet20,weight);
	      h_Jet0_BaseSel->Fill(fCleanJets20[0]->Pt(),weight);
	      h_Jet1_BaseSel->Fill(fCleanJets20[1]->Pt(),weight);
	      h_Jet2_BaseSel->Fill(fCleanJets20[2]->Pt(),weight);
	      h_Jet3_BaseSel->Fill(fCleanJets20[3]->Pt(),weight);
	      if(nJet20>=5) h_Jet4_BaseSel->Fill(fCleanJets20[4]->Pt(),weight);
	      if(nJet20>=6) h_Jet5_BaseSel->Fill(fCleanJets20[5]->Pt(),weight);
	    }
     }

     }
     //Possible Triggers selections
	
    if (HasSelTrigger){     
     if (nJet35>=6 && nMuons>=1) {
       h_PossibleTrigger->Fill(1);
       if(nBJet35 >= 1) h_PossibleTrigger->Fill(5);
       if(nBJet35 >= 2) h_PossibleTrigger->Fill(9);
       if(nBJet35 >= 3) h_PossibleTrigger->Fill(13);
       if(nBJet35 >= 4) h_PossibleTrigger->Fill(17);
     }
     if (nJet35>=6 && SumptAllJet>900)
       { h_PossibleTrigger->Fill(2);
       if(nBJet35 >= 1) h_PossibleTrigger->Fill(6);
       if(nBJet35 >= 2) h_PossibleTrigger->Fill(10);
       if(nBJet35 >= 3) h_PossibleTrigger->Fill(14);
       if(nBJet35 >= 4) h_PossibleTrigger->Fill(18);
       }
     if (nJet35>=6){
       if(fCleanJets[0]->Pt() > 85 && fCleanJets[1]->Pt() > 80 && fCleanJets[2]->Pt() > 65 && fCleanJets[3]->Pt() > 65 && fCleanJets[4]->Pt() > 25 &&
	  fCleanJets[5]->Pt() > 25){
	 h_PossibleTrigger->Fill(3);
       if(nBJet35 >= 1) h_PossibleTrigger->Fill(7);
       if(nBJet35 >= 2) h_PossibleTrigger->Fill(11);
       if(nBJet35 >= 3) h_PossibleTrigger->Fill(15);
       if(nBJet35 >= 4) h_PossibleTrigger->Fill(19);
       }
       }



     //  if ( nJet35>=6 && nMuons>=1){
     //     if ( nJet35>=6 && SumptAllJet>800){
     h_nBJet35->Fill(nBJet35,weight);
     h_nJet35->Fill(nJet35,weight);
     h_MET->Fill(pfMET,weight);
     h_nTruePileUp->Fill(nTruePileUp,weight);
     h_nTruePileUp_NoWeight->Fill(nTruePileUp);
     h_nVertex->Fill(nGoodVtx,weight);
     h_HT->Fill(SumptAllJet,weight);
     if(nJet35>=1)h_Jet0->Fill(fCleanJets[0]->Pt(),weight);
     if(nJet35>=2)h_Jet1->Fill(fCleanJets[1]->Pt(),weight);
     if(nJet35>=3)h_Jet2->Fill(fCleanJets[2]->Pt(),weight);
     if(nJet35>=4)h_Jet3->Fill(fCleanJets[3]->Pt(),weight);
     if(nJet35>=5)h_Jet4->Fill(fCleanJets[4]->Pt(),weight);
     if(nJet35>=6)h_Jet5->Fill(fCleanJets[5]->Pt(),weight);
	   
	      
     if ( nJet35>=6){
       //cout<<nJet35<<" "<<fCleanJets.size()<<" s"<<fCleanJets[0]->Pt()<<" "<<fCleanJets[1]->Pt()<<" "<<fCleanJets[2]->Pt()<<" "<<fCleanJets[3]->Pt()<<" "<<fCleanJets[4]->Pt()<<" "<<fCleanJets[5]->Pt()<<endl;
       if(fCleanJets[0]->Pt() > 80.0 && fCleanJets[1]->Pt() > 80. && fCleanJets[2]->Pt() > 80.0 && fCleanJets[3]->Pt() > 80.0 && 
fCleanJets[4]->Pt() > 60.0 && fCleanJets[5]->Pt() > 60.0){
       //      if(SumptAllJet>900){
	 if(1==1){//nBJet35 >= 3){

	   h_nBJet35_EvtSel->Fill(nBJet35,weight);
	   h_nJet35_EvtSel->Fill(nJet35,weight);
	   h_MET_EvtSel->Fill(pfMET,weight);
	   h_HT_EvtSel->Fill(SumptAllJet,weight);
	   h_Jet0_EvtSel->Fill(fCleanJets[0]->Pt(),weight);
	   h_Jet1_EvtSel->Fill(fCleanJets[1]->Pt(),weight);
	   h_Jet2_EvtSel->Fill(fCleanJets[2]->Pt(),weight);
	   if(nJet35>=4) h_Jet3_EvtSel->Fill(fCleanJets[3]->Pt(),weight);
	   if(nJet35>=5) h_Jet4_EvtSel->Fill(fCleanJets[4]->Pt(),weight);
	   if(nJet35>=6) h_Jet5_EvtSel->Fill(fCleanJets[5]->Pt(),weight);
	   if(nJet35>=7) h_Jet6_EvtSel->Fill(fCleanJets[6]->Pt(),weight);
	   //all the jets make triplets
	   //	   int numJetForTriplet=fCleanJets.size();
	   //only the six leading jets make triplets
       unsigned int numJetForTriplet=6;
       int nTriplets=0;
       for (unsigned int i=0+0; i<numJetForTriplet-2; ++i) {
	 for (unsigned int j=i+1; j<numJetForTriplet-1; ++j) {
	   for (unsigned int k=j+1; k<numJetForTriplet-0; ++k) {
	     Triplet.push_back(std::vector<TLorentzVector* > ());
	     
	     TLorentzVector* Jet1; TLorentzVector* Jet2; TLorentzVector* Jet3;
	     Jet1=fCleanJets[i]; Jet2=fCleanJets[j]; Jet3=fCleanJets[k];
	     TLorentzVector Triplet123; Triplet123=(*Jet1+*Jet2+*Jet3);
	     TLorentzVector Doublet12; Doublet12=*Jet1+*Jet2;
	     TLorentzVector Doublet13; Doublet13=*Jet1+*Jet3;
	     TLorentzVector Doublet23; Doublet23=*Jet2+*Jet3;

	     sumScalarPtTriplet.push_back(Jet1->Pt()+Jet2->Pt()+Jet3->Pt());
	     massTriplet.push_back(Triplet123.M());
	     sumVectorPtTriplet.push_back(Triplet123.Pt());

	     massDoublet12.push_back(Doublet12.M());  
	     massDoublet13.push_back(Doublet13.M()); 
	     massDoublet23.push_back(Doublet23.M());
	     vector<float > dijetmass_3m;

	     dijetmass_3m.push_back(Doublet12.M()*Doublet12.M()/(Triplet123.M()*Triplet123.M()+Jet1->M()*Jet1->M()+Jet2->M()*Jet2->M()+Jet3->M()*Jet3->M()));
	     dijetmass_3m.push_back(Doublet13.M()*Doublet13.M()/(Triplet123.M()*Triplet123.M()+Jet1->M()*Jet1->M()+Jet2->M()*Jet2->M()+Jet3->M()*Jet3->M()));
	     dijetmass_3m.push_back(Doublet23.M()*Doublet23.M()/(Triplet123.M()*Triplet123.M()+Jet1->M()*Jet1->M()+Jet2->M()*Jet2->M()+Jet3->M()*Jet3->M()));
	     sort(dijetmass_3m.begin(),dijetmass_3m.end());



	     massDoubletHigh.push_back(dijetmass_3m[2]);  
	     massDoubletMid.push_back(dijetmass_3m[1]);  
	     massDoubletLow.push_back(dijetmass_3m[0]);

	     Triplet[nTriplets].push_back(Jet1);
	     Triplet[nTriplets].push_back(Jet2);
	     Triplet[nTriplets].push_back(Jet3);

	     nTriplets++;	     
	   }
	 }
       }
     
       
     for(unsigned int q=0; q<massTriplet.size(); q++)
       {
	 for(int b=0; b<5; b++){

	 for (int i=0; i<7; i++)
	   {
	     float iPt=30.0+(float)i*10.0;
	     for(int k=0; k<3; k++)
	       { 
		 unsigned int iNjet=k+6;
		 //count njets with the pt cut -> gonna be slow
		 if(iNjet<=fCleanJets.size()){
		  
		   if(Triplet[q][2]->Pt()>iPt && fCleanJets[iNjet-1]->Pt()>iPt && nBJet35>=b)
		     {	
		       Mjjj_sumpt_bjet_pt_njet[b][i][k]->Fill(sumScalarPtTriplet[q],massTriplet[q],weight);
		     }
		   for(int j=0; j<20; j++){
		        
		     float iDiag=(float)j*10.0+40.0;
		     //to implement the pt cut we only keep triplets where the lowest jet passes pt cut
		     //also we check if the njetsMin cut satisfies this pt cut
		     //std::cout<<"before selection"<<endl;
		     // std::cout<<Triplet[q][2].pt()<<" "<<fCleanJets.size()<<" "<<fCleanJets[iNjet-1].pt()<<endl;
		     //if(iNjet>fCleanJets.size()){
		     // cout<<Triplet[q][2].pt()<<endl;
		     // cout<<fCleanJets.size()<<endl;
		     // cout<<iNjet-1<<endl;
		     //}
		     if(Triplet[q][2]->Pt()>iPt && fCleanJets[njetsMin-1]->Pt()>iPt && fCleanJets[iNjet-1]->Pt()>iPt && nBJet35>=b)
		       {
			 //cout<<"after selection"<<endl;
			 //cout<<Triplet[q][2].pt()<<" "<<fCleanJets.size()<<" "<<fCleanJets[iNjet-1].pt()<<endl;
			 if(massTriplet[q]<(sumScalarPtTriplet[q]-iDiag))
			   {
			     float countT=0;
			     Mjjj_bjet_pt_njet_diag[b][i][k][j]->Fill(massTriplet[q],weight);
			     //cout<<iDiag<<" "<<iPt<<" "<<b<<" "<<iNjet<<endl;
			     //cout<<massTriplet[q]<<" "<<(*Triplet[q][2]+*Triplet[q][1]+*Triplet[q][0]).M()<<endl;
			     //if(countT==0 && massTriplet[q]>160 && massTriplet[q]<190){


			     if(massTriplet[q] > 150.0 && massTriplet[q] < 200.0){
			       MjjHigh_MjjMid_bjet_pt_njet_diag[b][i][k][j]->Fill(massDoubletMid[q], massDoubletHigh[q],weight);
			       MjjHigh_MjjLow_bjet_pt_njet_diag[b][i][k][j]->Fill(massDoubletLow[q], massDoubletHigh[q],weight);
			       MjjMid_MjjLow_bjet_pt_njet_diag[b][i][k][j]->Fill(massDoubletLow[q],massDoubletMid[q],weight);
			     }
			     countT++;
			          
			    
			     //}
			     //cout<<"!!!!!!!!!!!!!KEEP!!!!!!!!!!"<<endl;
			   }
		       }
		   }
		 }//diag cut loop
	       }//njetloop
	   }//pt loop
	 }//bjet loop
	   }//triplet loop
	 }//3 or more b jets
	 }//jetp
     }//minjet
     //lets see if the top branching ratios work
    
  }
 }//Msquqark
 }//get entrye
  return;
}
