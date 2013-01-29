
//#Includetr "RUAnalysis/Ntupler/interface/Ntupler.h"
#include "RUAnalysis/Analysis/interface/NtpThreeJet.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "TLorentzVector.h"
#include "TFile.h"
#include "math.h"
//#include "../interface/BTagSFUtil.h"
#include "../interface/BTagSFUtil_CSVM_BtagMap.h"
//#include "../interface/BTagSFUtil_Loose.h"
//#include "../interface/BTagSFUtil_CSVT.h"
//#include "../interface/BTagSFUtil_JPTM.h"
#include "RUAnalysis/Analysis/interface/LumiReweightingStandAlone.h"

using namespace std;

NtpThreeJet::NtpThreeJet (std::vector<TString>& InFileNames, bool const IsData,
TString const OutFileName, TString const PUFile) : NtpReader(InFileNames, IsData)
{
  fOutFile = new TFile(OutFileName, "recreate");
  cout<<"OutPut file: "<<OutFileName<<endl;
  stringstream ss;
  ss<<OutFileName;
  string NameFile= ss.str();
  string::size_type found = NameFile.find("BtagMap");
  string::size_type found0 = NameFile.find("mc_");
  int length=abs(int(found0 + 3) - int(found - 1));
  //Should be TTjets for now its the RPV sample
    string BtagMap = "TTJets_MassiveB_AK5PF_CSVM_bTaggingEfficiencyMap.root";

   if (found!=string::npos && found0!=string::npos)
    {
      BtagMap = NameFile.substr(found0 + 3, length) + "_AK5PF_CSVM_bTaggingEfficiencyMap.root";
    }
  
  cout<<"BtagMap: data/"<<BtagMap<<" as map for Btagging efficiencies"<<endl;
  
  

  f_EffMap = new TFile(("data/"+BtagMap).c_str());
  if (!f_EffMap->IsOpen()) {
    std::cerr << "ERROR: cannot open Efficiency map file " << "data/"<<BtagMap << std::endl;
    f_EffMap = new TFile("data/TTJets_MassiveB_AK5PF_CSVM_bTaggingEfficiencyMap.root");
   std::cerr << "BtagMap: TTbar instead"<< std::endl;
  if (!f_EffMap->IsOpen()) {
    std::cerr << "ERROR: cannot open Second  Efficiency map file data/TTJets_MassiveB_AK5PF_CSVM_bTaggingEfficiencyMap.root" << std::endl;
    throw;
  }
    }

  if (!fOutFile->IsOpen()) {
    std::cerr << "ERROR: cannot open output root file " << OutFileName << std::endl;
    throw;
  }
  fPUFile = new TFile("data/"+PUFile);
  if (fPUFile->IsOpen()) {
    std::cout << "Found PU file " << PUFile << std::endl;
	} else {
    std::cerr << "Did not find PU file " << PUFile << " -- using default" << std::endl;
  }
}

NtpThreeJet::~NtpThreeJet ()
{
    std::cout << "Starting NtpThreeJet destructor " << std::endl;
    if (fOutFile) {
			// fOutFile->Write(); // Writes another copy of all objects
			fOutFile->Close();
			std::cout << "Closed file, now deleting pointer" << std::endl;
			delete fOutFile;
    }
    if (fPUFile) {
			fPUFile->Close();
			delete fPUFile;
    }
    /*    if (f_EffMap) {
			f_EffMap->Close();
			delete fPUFile;
			}*/
    
    std::cout << "Done with NtpThreeJet destructor " << std::endl;
    std::cout << "Done with NtpThreeJet destructor " << std::endl;
}


void NtpThreeJet::BookHistograms()
{

  h2_EffMapB    = (TH2D*)f_EffMap->Get("efficiency_b");
  h2_EffMapC    = (TH2D*)f_EffMap->Get("efficiency_c");
  h2_EffMapUDSG = (TH2D*)f_EffMap->Get("efficiency_udsg");
  double PtBins[] = {20,30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600, 800};

  CSVM_SFb_0to2p4 = new TF1("CSVM_SFb_0to2p4","0.726981*((1.+(0.253238*x))/(1.+(0.188389*x)))", 30.,670.);

  // Tagger: CSVM within 30 < pt < 670 GeV, abs(eta) < 2.4, x = pt
  CSVM_SFb_errors = new TH1D("CSVM_SFb_errors", "CSVM_SFb_errors", 16, PtBins);  

  CSVM_SFb_errors->SetBinContent( 0,0.0554504);
  CSVM_SFb_errors->SetBinContent( 1,0.0209663);
  CSVM_SFb_errors->SetBinContent( 2,0.0207019);
  CSVM_SFb_errors->SetBinContent( 3,0.0230073);
  CSVM_SFb_errors->SetBinContent( 4,0.0208719);
  CSVM_SFb_errors->SetBinContent( 5,0.0200453);
  CSVM_SFb_errors->SetBinContent( 6,0.0264232);
  CSVM_SFb_errors->SetBinContent( 7,0.0240102);
  CSVM_SFb_errors->SetBinContent( 8,0.0229375);
  CSVM_SFb_errors->SetBinContent( 9,0.0184615);
  CSVM_SFb_errors->SetBinContent(10,0.0216242);
  CSVM_SFb_errors->SetBinContent(11,0.0248119);
  CSVM_SFb_errors->SetBinContent(12,0.0465748);
  CSVM_SFb_errors->SetBinContent(13,0.0474666);
  CSVM_SFb_errors->SetBinContent(14,0.0718173);
  CSVM_SFb_errors->SetBinContent(15,0.0717567);
  CSVM_SFb_errors->SetBinContent(16,(2*0.0717567));

  float ptmax=800;


  CSVM_SFl_0to2p4 = new TF1("CSVM_SFl_0to2p4","((1.07585+(0.00119553*x))+(-3.00163e-06*(x*x)))+(2.10724e-09*(x*(x*x)))", 20.,ptmax);
  CSVM_SFl_0to2p4_min= new TF1("CSVM_SFl_0to2p4_min","((0.987005+(0.000726254*x))+(-1.73476e-06*(x*x)))+(1.20406e-09*(x*(x*x)))", 20.,ptmax);
  CSVM_SFl_0to2p4_max = new TF1("CSVM_SFl_0to2p4_max","((1.1647+(0.00166318*x))+(-4.26493e-06*(x*x)))+(3.01017e-09*(x*(x*x)))", 20.,ptmax);
  

     CSVM_SFl_0to0p8 = new TF1("CSVM_SFl_0to0p8","((1.06238+(0.00198635*x))+(-4.89082e-06*(x*x)))+(3.29312e-09*(x*(x*x)))", 20.,ptmax);
     CSVM_SFl_0to0p8_min = new TF1("CSVM_SFl_0to0p8_min","((0.972746+(0.00104424*x))+(-2.36081e-06*(x*x)))+(1.53438e-09*(x*(x*x)))", 20.,ptmax);
      CSVM_SFl_0to0p8_max= new TF1("CSVM_SFl_0to0p8_max","((1.15201+(0.00292575*x))+(-7.41497e-06*(x*x)))+(5.0512e-09*(x*(x*x)))", 20.,ptmax);


	 CSVM_SFl_0p8to1p6= new TF1("CSVM_SFl_0p8to1p6","((1.08048+(0.00110831*x))+(-2.96189e-06*(x*x)))+(2.16266e-09*(x*(x*x)))", 20.,ptmax);
	  CSVM_SFl_0p8to1p6_min = new TF1("CSVM_SFl_0p8to1p6_min","((0.9836+(0.000649761*x))+(-1.59773e-06*(x*x)))+(1.14324e-09*(x*(x*x)))", 20.,ptmax);
	 CSVM_SFl_0p8to1p6_max = new TF1("CSVM_SFl_0p8to1p6_max","((1.17735+(0.00156533*x))+(-4.32257e-06*(x*x)))+(3.18197e-09*(x*(x*x)))", 20.,ptmax);

  
  CSVM_SFl_Corr = new TF1("CSVM_SFl_Corr","(1.10422 + (-0.000523856*x) + (1.14251e-06*(x*x)))", 0.,670.);

  CSVM_SFl_0to2p4 =   new TF1("CSVM_SFl_0to2p4","((1.04318+(0.000848162*x))+(-2.5795e-06*(x*x)))+(1.64156e-09*(x*(x*x)))", 20.,800.);
  CSVM_SFl_0to0p8 =   new TF1("CSVM_SFl_0to0p8","((1.06182+(0.000617034*x))+(-1.5732e-06*(x*x)))+(3.02909e-10*(x*(x*x)))", 20.,800.);
  CSVM_SFl_0p8to1p6 = new TF1("CSVM_SFl_0p8to1p6","((1.111+(-9.64191e-06*x))+(1.80811e-07*(x*x)))+(-5.44868e-10*(x*(x*x)))", 20.,6.);
  CSVM_SFl_1p6to2p4 = new TF1("CSVM_SFl_1p6to2p4","((1.08498+(-0.000701422*x))+(3.43612e-06*(x*x)))+(-4.11794e-09*(x*(x*x)))", 20.,670.);


     CSVM_SFl_1p6to2p4 = new TF1("CSVM_SFl_1p6to2p4","((1.09145+(0.000687171*x))+(-2.45054e-06*(x*x)))+(1.7844e-09*(x*(x*x)))", 20.,ptmax);
     CSVM_SFl_1p6to2p4_min = new TF1("CSVM_SFl_1p6to2p4_min","((1.00616+(0.000358884*x))+(-1.23768e-06*(x*x)))+(6.86678e-10*(x*(x*x)))", 20.,ptmax);
     CSVM_SFl_1p6to2p4_max = new TF1("CSVM_SFl_1p6to2p4_max","((1.17671+(0.0010147*x))+(-3.66269e-06*(x*x)))+(2.88425e-09*(x*(x*x)))", 20.,ptmax);




  char hNAME[99];
 
  //before cuts, just the ones that where already in the ntuple
  h_PossibleTrigger  = new TH1F("PossibleTrigger", "PossibleTrigger",30,0,30);   h_PossibleTrigger->Sumw2();

  h_mindRMuonJet = new TH1F("mindRMuonJet", "mindRMuonJet",100,0,5);   h_mindRMuonJet->Sumw2();
  h_mindRMuonJet_mPFIso = new TH2F("mindRMuonJet_mPFIso", "mindRMuonJet_mPFIso",200,0,10,100,0,5);  h_mindRMuonJet_mPFIso->Sumw2();
  h_ept= new TH1F("ept", "ept",200,0,1000); h_ept->Sumw2();
  h_mpt= new TH1F("mpt", "mpt",200,0,1000); h_mpt->Sumw2();
  h_mPFIso= new TH1F("mPFIso", "mPFIso",200,0,10); h_mPFIso->Sumw2();
  //befor cuts
  h_MET = new TH1F("MET", "MET",200,0,800); h_MET->Sumw2();
  h_nTruePileUp = new TH1F("nTruePileUp", "nTruePileUp",100,0,100); h_nTruePileUp->Sumw2();
  h_nTruePileUp_NoWeight = new TH1F("nTruePileUp_NoWeight", "nTruePileUp_NoWeight",100,0,100); h_nTruePileUp_NoWeight->Sumw2();
  h_nVertex = new TH1F("nVertex", "nVertex",100,0,100); h_nVertex->Sumw2();
  h_HT = new TH1F("HT", "HT",300,0,3000); h_HT->Sumw2();
  h_HMT = new TH1F("HMT", "HMT", 300,0,6000); h_HMT->Sumw2();
  h_nBJet35  = new TH1F("nBJet35", "nBJet35",20,0,20); h_nBJet35->Sumw2();
  h_nJet35  = new TH1F("nJet35", "nJet35",20,0,20); h_nJet35->Sumw2();
  h_Jet0= new TH1F("Jet0", "Jet0",400,0,2000); h_Jet0->Sumw2();
  h_Jet1= new TH1F("Jet1", "Jet1",400,0,2000); h_Jet1->Sumw2();
  h_Jet2= new TH1F("Jet2", "Jet2",200,0,1000); h_Jet2->Sumw2();
  h_Jet3= new TH1F("Jet3", "Jet3",200,0,1000); h_Jet3->Sumw2();
  h_Jet4= new TH1F("Jet4", "Jet4",200,0,1000); h_Jet4->Sumw2();
  h_Jet5= new TH1F("Jet5", "Jet5",200,0,1000); h_Jet5->Sumw2();
  h_Jet6= new TH1F("Jet6", "Jet6",200,0,1000); h_Jet6->Sumw2();
  h_BJet1= new TH1F("BJet1", "BJet1",200,0,1000); h_BJet1->Sumw2();
  h_BJet2= new TH1F("BJet2", "BJet2",200,0,1000); h_BJet2->Sumw2();
  h_BJet3= new TH1F("BJet3", "BJet3",200,0,1000); h_BJet3->Sumw2();
  h_NeutralHad_JetPt= new TH2F("NeutralHad_JetPt", "NeutralHad_JetPt",200,0,1000,100,0,1);  h_NeutralHad_JetPt->Sumw2();

  //after cuts
  h_MET_EvtSel = new TH1F("MET_EvtSel", "MET_EvtSel",200,0,1000); h_MET_EvtSel->Sumw2();
  h_HT_EvtSel = new TH1F("HT_EvtSel", "HT_EvtSel",400,0,4000); h_HT_EvtSel->Sumw2();
  h_HMT_EvtSel = new TH1F("HMT_EvtSel", "HMT_EvtSel",400,0,4000); h_HMT_EvtSel->Sumw2();
  h_nBJet35_EvtSel  = new TH1F("nBJet35_EvtSel", "nBJet35_EvtSel",20,0,20); h_nBJet35_EvtSel->Sumw2();
  h_nJet35_EvtSel  = new TH1F("nJet35_EvtSel", "nJet35_EvtSel",20,0,20); h_nJet35_EvtSel->Sumw2();
  h_Jet0_EvtSel= new TH1F("Jet0_EvtSel", "Jet0_EvtSel",400,0,2000); h_Jet0_EvtSel->Sumw2();
  h_Jet1_EvtSel= new TH1F("Jet1_EvtSel", "Jet1_EvtSel",400,0,2000); h_Jet1_EvtSel->Sumw2();
  h_Jet2_EvtSel= new TH1F("Jet2_EvtSel", "Jet2_EvtSel",200,0,1000); h_Jet2_EvtSel->Sumw2();
  h_Jet3_EvtSel= new TH1F("Jet3_EvtSel", "Jet3_EvtSel",200,0,1000); h_Jet3_EvtSel->Sumw2();
  h_Jet4_EvtSel= new TH1F("Jet4_EvtSel", "Jet4_EvtSel",200,0,1000); h_Jet4_EvtSel->Sumw2();
  h_Jet5_EvtSel= new TH1F("Jet5_EvtSel", "Jet5_EvtSel",200,0,1000); h_Jet5_EvtSel->Sumw2();
  h_Jet6_EvtSel= new TH1F("Jet6_EvtSel", "Jet6_EvtSel",200,0,1000); h_Jet6_EvtSel->Sumw2();
  h_BJet1_EvtSel= new TH1F("BJet1_EvtSel", "BJet1_EvtSel",200,0,1000); h_BJet1_EvtSel->Sumw2();
  h_BJet2_EvtSel= new TH1F("BJet2_EvtSel", "BJet2_EvtSel",200,0,1000); h_BJet2_EvtSel->Sumw2();
  h_BJet3_EvtSel= new TH1F("BJet3_EvtSel", "BJet3_EvtSel",200,0,1000); h_BJet3_EvtSel->Sumw2();
  //TriggerPlots
  
  h_MET_Base = new TH1F("MET_Base", "MET_Base",200,0,1000); h_MET_Base->Sumw2();
  h_HT_Base = new TH1F("HT_Base", "HT_Base",400,0,4000); h_HT_Base->Sumw2();
  h_HMT_Base = new TH1F("HMT_Base", "HMT_Base",400,0,4000); h_HMT_Base->Sumw2();
  h_nBJet35_Base   = new TH1F("nBJet35_Base", "nBJet35_Base",20,0,20); h_nBJet35_Base->Sumw2();
  h_nJet35_Base   = new TH1F("nJet20_Base", "nJet20_Base",20,0,20); h_nJet35_Base->Sumw2();
  h_Jet0_Base = new TH1F("Jet0_Base", "Jet0_Base",200,0,1000); h_Jet0_Base->Sumw2();
  h_Jet1_Base = new TH1F("Jet1_Base", "Jet1_Base",200,0,1000); h_Jet1_Base->Sumw2();
  h_Jet2_Base = new TH1F("Jet2_Base", "Jet2_Base",200,0,1000); h_Jet2_Base->Sumw2();
  h_Jet3_Base = new TH1F("Jet3_Base", "Jet3_Base",200,0,1000); h_Jet3_Base->Sumw2();
  h_Jet4_Base = new TH1F("Jet4_Base", "Jet4_Base",200,0,1000); h_Jet4_Base->Sumw2();
  h_Jet5_Base = new TH1F("Jet5_Base", "Jet5_Base",200,0,1000); h_Jet5_Base->Sumw2();
  h_Jet6_Base = new TH1F("Jet6_Base", "Jet6_Base",200,0,1000); h_Jet6_Base->Sumw2();
  h_BJet1_Base= new TH1F("BJet1_Base", "BJet1_Base",200,0,1000); h_BJet1_Base->Sumw2();
  h_BJet2_Base= new TH1F("BJet2_Base", "BJet2_Base",200,0,1000); h_BJet2_Base->Sumw2();
  h_BJet3_Base= new TH1F("BJet3_Base", "BJet3_Base",200,0,1000); h_BJet3_Base->Sumw2();

  h_MET_BaseSel = new TH1F("MET_BaseSel", "MET_BaseSel",200,0,1000); h_MET_BaseSel->Sumw2();
  h_HT_BaseSel = new TH1F("HT_BaseSel", "HT_BaseSel",400,0,4000); h_HT_BaseSel->Sumw2();
  h_HMT_BaseSel = new TH1F("HMT_BaseSel", "HMT_BaseSel",400,0,4000); h_HMT_BaseSel->Sumw2();
  h_nBJet35_BaseSel   = new TH1F("nBJet35_BaseSel", "nBJet35_BaseSel",20,0,20); h_nBJet35_BaseSel->Sumw2();
  h_nJet35_BaseSel   = new TH1F("nJet20_BaseSel", "nJet20_BaseSel",20,0,20); h_nJet35_BaseSel->Sumw2();
  h_Jet0_BaseSel = new TH1F("Jet0_BaseSel", "Jet0_BaseSel",200,0,1000); h_Jet0_BaseSel->Sumw2();
  h_Jet1_BaseSel = new TH1F("Jet1_BaseSel", "Jet1_BaseSel",200,0,1000); h_Jet1_BaseSel->Sumw2();
  h_Jet2_BaseSel = new TH1F("Jet2_BaseSel", "Jet2_BaseSel",200,0,1000); h_Jet2_BaseSel->Sumw2();
  h_Jet3_BaseSel = new TH1F("Jet3_BaseSel", "Jet3_BaseSel",200,0,1000); h_Jet3_BaseSel->Sumw2();
  h_Jet4_BaseSel = new TH1F("Jet4_BaseSel", "Jet4_BaseSel",200,0,1000); h_Jet4_BaseSel->Sumw2();
  h_Jet5_BaseSel = new TH1F("Jet5_BaseSel", "Jet5_BaseSel",200,0,1000); h_Jet5_BaseSel->Sumw2();
  h_Jet6_BaseSel = new TH1F("Jet6_BaseSel", "Jet6_BaseSel",200,0,1000); h_Jet6_BaseSel->Sumw2();
  h_BJet1_BaseSel = new TH1F("BJet1_BaseSel", "BJet1_BaseSel",200,0,1000); h_BJet1_BaseSel->Sumw2();
  h_BJet2_BaseSel = new TH1F("BJet2_BaseSel", "BJet2_BaseSel",200,0,1000); h_BJet2_BaseSel->Sumw2();
  h_BJet3_BaseSel = new TH1F("BJet3_BaseSel", "BJet3_BaseSel",200,0,1000); h_BJet3_BaseSel->Sumw2();
  

  cout<<"before histos"<<endl;
  /*  Double_t tbins[68]={0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,86,92,99,106,114,122,131,141,151,
		      162,174,187,201,216,232,249,267,286,307,329,353,379,406,435,466,500,536,575,617,
		      662,710,761,816,875,938,1006,1079,1157,1241,1331,1427,1530,1641,1760,1887,2024,2170,2327,2495,2677,3000};*/
  Double_t tbins[59]={0,10,20,30,40,50,60,70,80,90,
		      100,110,121,131,141,151,162,174,187,201,
		      216,232,249,267,286,307,329,353,379,406,
		      435,466,500,536,575,617,662,710,761,816,
		      875,938,1006,1079,1157,1241,1331,1427,1530,1641,
		      1760,1887,2024,2170,2327,2495,2677,3000,3400};

  for(int b=0; b<5; b++){
  for (int i=0; i<10; i++){
    int iPt=30+i*10;
    //Triplet mass plots
    Mjjj_sumpt_bjet_pt_njet.push_back(std::vector<std::vector<TH2F*> >());
    Mjjj_sumpt_btag_pt_njet.push_back(std::vector<std::vector<TH2F*> >());
    Mjjj_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
     Mjjj_btag_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    Mjjj_1btag_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    Mjjj_bjet_pt_njet_diag_MCmatch.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    Mjjj_bjet_pt_njet_diag_MCcomb.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    MET_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    HT_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    MET_over_HT_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());

    HMT_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    nJet35_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    nBJet35_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    nVertex_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    Jet0_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    Jet1_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    Jet2_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    Jet3_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    Jet4_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    Jet5_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    Jet6_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    BJet1_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    BJet2_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    BJet3_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());

    //Dalitz Plots
    MjjHigh_MjjMid_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH2F*> > >());
    MjjHigh_MjjLow_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH2F*> > >());
    Mjjj_btag_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    Mjjj_1btag_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    MjjMid_MjjLow_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH2F*> > >());
    //Dijet mass plots
    M12_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    M13_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    M23_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    for(int k=0; k<3; k++){
      int iNjet=k+6;

      Mjjj_sumpt_bjet_pt_njet[b].push_back(std::vector<TH2F*> ());
      Mjjj_sumpt_btag_pt_njet[b].push_back(std::vector<TH2F*> ());
      sprintf(hNAME, "Mjjj_sumpt_bjet%i_pt%i_GE%ijet", b, iPt,iNjet);
      Mjjj_sumpt_bjet_pt_njet[b][i].push_back(new TH2F(hNAME,hNAME,200,0,2000,200,0,2000));
      Mjjj_sumpt_bjet_pt_njet[b][i][k]->Sumw2();
      sprintf(hNAME, "Mjjjbtag_sumpt_bjet%i_pt%i_GE%ijet", b, iPt,iNjet);
      Mjjj_sumpt_btag_pt_njet[b][i].push_back(new TH2F(hNAME,hNAME,200,0,2000,200,0,2000));
      Mjjj_sumpt_btag_pt_njet[b][i][k]->Sumw2();
      Mjjj_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      Mjjj_btag_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      Mjjj_1btag_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      Mjjj_bjet_pt_njet_diag_MCmatch[b].push_back(std::vector<std::vector<TH1F*> > ());
      Mjjj_bjet_pt_njet_diag_MCcomb[b].push_back(std::vector<std::vector<TH1F*> > ());
      MET_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      HT_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      MET_over_HT_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      HMT_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      nBJet35_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      nJet35_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      nVertex_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      Jet0_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      Jet1_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      Jet2_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      Jet3_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      Jet4_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      Jet5_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      Jet6_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      BJet1_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      BJet2_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      BJet3_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());

      MjjHigh_MjjMid_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH2F*> > ());
      MjjHigh_MjjLow_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH2F*> > ());
      MjjMid_MjjLow_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH2F*> > ());

      M12_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      M13_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      M23_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());
      for(int j=0; j<25; j++){
	
	int iDiag=j*10+40;
	
	Mjjj_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
	sprintf(hNAME, "Mjjj_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);
	Mjjj_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,2500,0,2500));
	//Mjjj_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,58,tbins));
	Mjjj_bjet_pt_njet_diag[b][i][k][j]->Sumw2();
	
	Mjjj_btag_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
	if(b<1) sprintf(hNAME, "Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", b,b,iPt,iDiag,iNjet);
	if(b>=1) sprintf(hNAME, "Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 1,b,iPt,iDiag,iNjet);
	
	Mjjj_btag_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,2500,0,2500));
	//Mjjj_btag_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,58,tbins));

	Mjjj_btag_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	Mjjj_1btag_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
	sprintf(hNAME, "Mjjj_1btag_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);
	Mjjj_1btag_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,2500,0,2500));
	//Mjjj_1btag_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,58,tbins));

	Mjjj_1btag_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	Mjjj_bjet_pt_njet_diag_MCmatch[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "Mjjj_bjet%i_pt%i_diag%i_GE%ijet_MCmatch", b,iPt,iDiag,iNjet);
	Mjjj_bjet_pt_njet_diag_MCmatch[b][i][k].push_back(new TH1F(hNAME,hNAME,2500,0,2500));
	//Mjjj_bjet_pt_njet_diag_MCmatch[b][i][k].push_back(new TH1F(hNAME,hNAME,58,tbins));
        Mjjj_bjet_pt_njet_diag_MCmatch[b][i][k][j]->Sumw2();

	Mjjj_bjet_pt_njet_diag_MCcomb[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "Mjjj_bjet%i_pt%i_diag%i_GE%ijet_MCcomb", b,iPt,iDiag,iNjet);
	Mjjj_bjet_pt_njet_diag_MCcomb[b][i][k].push_back(new TH1F(hNAME,hNAME,2500,0,2500));
	//Mjjj_bjet_pt_njet_diag_MCcomb[b][i][k].push_back(new TH1F(hNAME,hNAME,58,tbins));
        Mjjj_bjet_pt_njet_diag_MCcomb[b][i][k][j]->Sumw2();

	MET_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "MET_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        MET_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,500,0,1000));
        MET_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	HT_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "HT_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        HT_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,500,0,4000));
        HT_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	MET_over_HT_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "MET_over_HT_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        MET_over_HT_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,500,0,1));
        MET_over_HT_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	HMT_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "HMT_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        HMT_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,500,0,4000));
        HMT_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	nJet35_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "nJet35_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        nJet35_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,30,0,30));
        nJet35_bjet_pt_njet_diag[b][i][k][j]->Sumw2();
	
	nBJet35_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "nBJet35_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        nBJet35_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,30,0,30));
        nBJet35_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	nVertex_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "nVertex_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        nVertex_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,50,0,50));
        nVertex_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	Jet0_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "Jet0_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        Jet0_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,1500,0,2000));
        Jet0_bjet_pt_njet_diag[b][i][k][j]->Sumw2();
	
	Jet1_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "Jet1_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        Jet1_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,1500,0,2000));
        Jet1_bjet_pt_njet_diag[b][i][k][j]->Sumw2();
	
	Jet2_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "Jet2_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        Jet2_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,1500,0,2000));
        Jet2_bjet_pt_njet_diag[b][i][k][j]->Sumw2();
	
	Jet3_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "Jet3_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        Jet3_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,1500,0,2000));
        Jet3_bjet_pt_njet_diag[b][i][k][j]->Sumw2();
	
	Jet4_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "Jet4_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        Jet4_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,1500,0,2000));
        Jet4_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	Jet5_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "Jet5_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        Jet5_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,1500,0,2000));
        Jet5_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	Jet6_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "Jet6_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        Jet6_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,1500,0,2000));
        Jet6_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	BJet1_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "BJet1_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        BJet1_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,1500,0,2000));
        BJet1_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	BJet2_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "BJet2_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        BJet2_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,1500,0,2000));
        BJet2_bjet_pt_njet_diag[b][i][k][j]->Sumw2();

	BJet3_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
        sprintf(hNAME, "BJet3_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag, iNjet);
	        BJet3_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,1500,0,2000));
        BJet3_bjet_pt_njet_diag[b][i][k][j]->Sumw2();


	/*	MjjHigh_MjjMid_bjet_pt_njet_diag[b][i].push_back(std::vector<TH2F*> ());
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
	M23_bjet_pt_njet_diag[b][i][k][j]->Sumw2();*/
      }
    }
  }
  }
  cout<<"after histos"<<endl;
 return;
}
 
void NtpThreeJet::WriteHistograms()
{
	cout<<"made it here"<<endl;
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
   h_HMT->Write();
   h_Jet0->Write();
   h_Jet1->Write();
   h_Jet2->Write();
   h_Jet3->Write();
   h_Jet4->Write();
   h_Jet5->Write();
   h_Jet6->Write();
   h_BJet1->Write();
   h_BJet2->Write();
   h_BJet3->Write();
   h_NeutralHad_JetPt->Write();
   fOutFile->mkdir("Trigger");
   fOutFile->cd("Trigger");

   h_MET_Base->Write();
   h_nBJet35_Base->Write();
   h_nJet35_Base->Write();
   h_HT_Base->Write();
   h_HMT_Base->Write();
   h_Jet0_Base->Write();
   h_Jet1_Base->Write();
   h_Jet2_Base->Write();
   h_Jet3_Base->Write();
   h_Jet4_Base->Write();
   h_Jet5_Base->Write();
   h_Jet6_Base->Write();
   h_BJet1_Base->Write();
   h_BJet2_Base->Write();
   h_BJet3_Base->Write();

   h_MET_BaseSel->Write();
   h_nBJet35_BaseSel->Write();
   h_nJet35_BaseSel->Write();
   h_HT_BaseSel->Write();
   h_HMT_BaseSel->Write();
   h_Jet0_BaseSel->Write();
   h_Jet1_BaseSel->Write();
   h_Jet2_BaseSel->Write();
   h_Jet3_BaseSel->Write();
   h_Jet4_BaseSel->Write();
   h_Jet5_BaseSel->Write();
   h_Jet6_BaseSel->Write();
   h_BJet1_BaseSel->Write();
   h_BJet2_BaseSel->Write();
   h_BJet3_BaseSel->Write();


   TDirectory* triplets=fOutFile->mkdir("Triplets");
   fOutFile->cd("Triplets");
   h_MET_EvtSel->Write();
   h_nBJet35_EvtSel->Write();
   h_nJet35_EvtSel->Write();
   h_HT_EvtSel->Write();
   h_HMT_EvtSel->Write();
   h_Jet0_EvtSel->Write();
   h_Jet1_EvtSel->Write();
   h_Jet2_EvtSel->Write();
   h_Jet3_EvtSel->Write();
   h_Jet4_EvtSel->Write();
   h_Jet5_EvtSel->Write();
   h_Jet6_EvtSel->Write();
   h_BJet1_EvtSel->Write();
   h_BJet2_EvtSel->Write();
   h_BJet3_EvtSel->Write();
   for (int b=0; b<5; b++){
     sprintf(FOLDER, "bjet_%i", b);
     TDirectory* now=triplets->mkdir(FOLDER);
     triplets->cd(FOLDER);
       for (int i=0; i<10; i++){
	 sprintf(FOLDER, "jetpt_%i", i*10+30);
	 TDirectory* now2=now->mkdir(FOLDER);
	 now->cd(FOLDER);
	 for (int k=0; k<3; k++){
	   Mjjj_sumpt_bjet_pt_njet[b][i][k]->Write();
	   Mjjj_sumpt_btag_pt_njet[b][i][k]->Write();
	   for(int j=0; j<25; j++){ 
	     /*	     sprintf(FOLDER, "diagcut_%i_%i",k,j*10+40);
	     now2->mkdir(FOLDER);
	     now2->cd(FOLDER);*/
	     Mjjj_bjet_pt_njet_diag[b][i][k][j]->Write();  
	     Mjjj_btag_bjet_pt_njet_diag[b][i][k][j]->Write();  
	     
	     Mjjj_bjet_pt_njet_diag_MCmatch[b][i][k][j]->Write();  
	     Mjjj_bjet_pt_njet_diag_MCcomb[b][i][k][j]->Write();  
	     
	     bool WriteFull=false;
	     if(WriteFull){
	     MET_bjet_pt_njet_diag[b][i][k][j]->Write();
	     HT_bjet_pt_njet_diag[b][i][k][j]->Write();
	     MET_over_HT_bjet_pt_njet_diag[b][i][k][j]->Write();
	     HMT_bjet_pt_njet_diag[b][i][k][j]->Write();
	     nJet35_bjet_pt_njet_diag[b][i][k][j]->Write();
	     nBJet35_bjet_pt_njet_diag[b][i][k][j]->Write();
	     nVertex_bjet_pt_njet_diag[b][i][k][j]->Write();
	     Jet0_bjet_pt_njet_diag[b][i][k][j]->Write();
	     Jet1_bjet_pt_njet_diag[b][i][k][j]->Write();
	     Jet2_bjet_pt_njet_diag[b][i][k][j]->Write();
	     Jet3_bjet_pt_njet_diag[b][i][k][j]->Write();
	     Jet4_bjet_pt_njet_diag[b][i][k][j]->Write();
	     Jet5_bjet_pt_njet_diag[b][i][k][j]->Write();
	     Jet6_bjet_pt_njet_diag[b][i][k][j]->Write();
	     BJet1_bjet_pt_njet_diag[b][i][k][j]->Write();
	     BJet2_bjet_pt_njet_diag[b][i][k][j]->Write();
	     BJet3_bjet_pt_njet_diag[b][i][k][j]->Write();
	     }
	   }
	 }
       }
   }
   
  cout << "end of writing\n";
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
      
	// Distribution used for S10 Summer2012 MC.
 float Summer2012_f [60] = {2.560E-06, 5.239E-06, 1.420E-05, 
			     5.005E-05, 1.001E-04, 2.705E-04, 1.999E-03, 
			     6.097E-03, 1.046E-02, 1.383E-02, 1.685E-02, 
			     2.055E-02, 2.572E-02, 3.262E-02, 4.121E-02, 
			     4.977E-02, 5.539E-02, 5.725E-02, 5.607E-02, 
			     5.312E-02, 5.008E-02, 4.763E-02, 4.558E-02, 
			     4.363E-02, 4.159E-02, 3.933E-02, 3.681E-02, 
			     3.406E-02, 3.116E-02, 2.818E-02, 2.519E-02, 
			     2.226E-02, 1.946E-02, 1.682E-02, 1.437E-02, 
			     1.215E-02, 1.016E-02, 8.400E-03, 6.873E-03, 
			     5.564E-03, 4.457E-03, 3.533E-03, 2.772E-03, 
			     2.154E-03, 1.656E-03, 1.261E-03, 9.513E-04, 
			     7.107E-04, 5.259E-04, 3.856E-04, 2.801E-04, 
			     2.017E-04, 1.439E-04, 1.017E-04, 7.126E-05, 
			     4.948E-05, 3.405E-05, 2.322E-05, 1.570E-05, 
			     5.005E-06};

  float data_f[60]={0,8.66979e-07,1.99567e-06,7.0944e-06,0.00115866,0.00304481,9.37811e-05,0.000438788,0.00369376,
		    0.0132685,0.0250747,0.035147,0.0466437,0.0612746,0.0752654,0.0879549,0.0977272,0.0971447,
		    0.0854517,0.0699568,0.0561969,0.0454351,0.0372194,0.0307875,0.0256272,0.0213495,0.0176728,
		    0.014462,0.0116675,0.00926419,0.00722899,0.00553611,0.00415629,0.0030565,0.00220048,0.00155038,
		    0.00106882,0.00072095,0.000475842,0.000307359,0.000194338,0.000120318,7.29651e-05,4.33587e-05,
		    2.52569e-05,1.44273e-05,8.08416e-06,4.44472e-06,2.39826e-06,1.27011e-06,0.00018054};

	TH1D *puhist = (TH1D *) gDirectory->Get("pileup");
	if (puhist) {
		double numEvts = puhist->Integral();
		if (numEvts > 0)
			puhist->Scale(1.0/numEvts);
	}
  for( int z=0; z<50; ++z) {
    Summer2012.push_back(Summer2012_f[z]);
    double dataVal = data_f[z];
		if (puhist)
			dataVal =  puhist->GetBinContent(z + 1);
    DataJun01.push_back(dataVal);
  }
	cout << endl;
  
  LumiWeights_ = reweight::LumiReWeighting(Summer2012,DataJun01);
    std::vector<TLorentzVector* >      fBJets;
    std::vector<TLorentzVector* >      fNoBJets;
    std::vector<JetLV* >      				 fCleanJets;
    std::vector<TLorentzVector* >      fTestJets;
    std::vector<TLorentzVector* >      fCleanJets20;  
    vector<TLorentzVector* > fdummyCleanJets;  

    std::vector<int >   JetMoms;
    std::vector<int >   TripletMoms;
    std::vector<float >   sumScalarPtTriplet;
    std::vector<float >   massTriplet;

    std::vector<float >   massDoublet12;
    std::vector<float >   massDoublet13;
    std::vector<float >   massDoublet23;

    std::vector<float >   massDoubletHigh;
    std::vector<float >   massDoubletMid;
    std::vector<float >   massDoubletLow;

    std::vector<float >   sumVectorPtTriplet;
    std::vector <std::vector<JetLV* > > Triplet;

      TLorentzVector* dummyJet= new TLorentzVector (0,0,0,0);
	int notrig = 0;
  for (int ientry = 0; GetEntry(ientry) > 0; ++ientry) {

    //do pile up reweighintg
	
    double MyWeight = LumiWeights_.weight(nTruePileUp);
    double weight=1;
        if(!DataIs)
	  weight = MyWeight;
    //cout << " nTruePileUp " << nTruePileUp << ", assigned weight " << weight << " ";
  ///////////////////Clear out variables/////////////////////

  Triplet.clear();    sumScalarPtTriplet.clear();  sumVectorPtTriplet.clear(); massTriplet.clear();
  fBJets.clear(); fNoBJets.clear();fCleanJets.clear();    fCleanJets20.clear(); fTestJets.clear(); 
  fdummyCleanJets.clear();
  massDoublet12.clear();  massDoublet13.clear(); massDoublet23.clear();
  massDoubletHigh.clear();  massDoubletMid.clear();  massDoubletLow.clear();
  JetMoms.clear(); TripletMoms.clear();
  ////////////////////////////////////////////////////////////
    

    if (ientry % 100 == 0) {
      printf("\n=================Processing entry: %i\n", ientry);
    }
    //cout<<HasSelTrigger<<" "<<HasBaseTrigger<<endl;
    if(1==1){//MSquark == 375 && MLSP ==75)
      
      //JETS///////
      //Count all the jets above 35 Gev, also calculated HT=SumptAllJet, count number of b-jets
      int nJet20=0; int nJet35=0; int nBJet35=0; int nNoBJet35=0; 
      
      float SumptAllJet=0;
      float SumptAllJet20=0;
      float SumMetPtAllJet=0;
      float SumMetPtAllJet20=0;
      
      int dummycounter=0;     
      //    cout<<"Shouldn't be anyting "<<fCleanJets.size()<<" "<<nPFJets<<" "<<sizeof(jet_PF_pt)<<endl;
      for (int i=0; i<nPFJets; i++){
	//cout<<i<<". th jet: "<<jet_PF_pt[i]<<" eta: "<< fabs(jet_PF_eta[i])<<endl;
	JetLV* Jet=new JetLV(jet_PF_px[i],jet_PF_py[i],jet_PF_pz[i],jet_PF_e[i]);
	
	if (jet_PF_pt[i]>20.0 && fabs(jet_PF_eta[i])<2.5){
	  bool isTagged = false;
	  //CSVL > 0.244, CSVM > 0.679, CSVT > 0.898
	  if (bdiscCSV_PF[i] >  0.679)
	    isTagged = true;
	  //Add isData check here (need to add variable to the ntuple first)
	  //set a unique seed                                                                                                                                                
	  //implementing b-tagging scale factors
	  int jet_flavor =jet_PF_PartonFlav[i];
	  float jet_pt = jet_PF_pt[i];
	  float jet_phi = jet_PF_phi[i];
	  float jet_eta = jet_PF_eta[i];
	  
	  if(!DataIs){
	    double phi = jet_phi;
	    double sin_phi = sin(phi*1000000);
	    double seed = abs(static_cast<int>(sin_phi*100000));
	    //Initialize class                                                                                                                                                
	    BTagSFUtil* btsfutil = new BTagSFUtil( seed );
	    bool temp=isTagged;
	    //modify tags                                                                                                                                                      
	    int BtagSys =0;
	    //modify tags  
	    //For uncertainties use BtagSys=-1,1                                                                                                                                  
	    float Btag_SF =  GetBTagSF(jet_pt,jet_eta,BtagSys*1);
	    float Btag_eff =  h2_EffMapB->GetBinContent( h2_EffMapB->GetXaxis()->FindBin(jet_pt), h2_EffMapB->GetYaxis()->FindBin(fabs(jet_eta)) );
	    
	    //For uncertainties use BtagSys=-2,2 double uncertainties for c jets                                         
	    float Ctag_SF =  GetBTagSF(jet_pt,jet_eta,BtagSys*2);
	    float Ctag_eff = h2_EffMapC->GetBinContent( h2_EffMapC->GetXaxis()->FindBin(jet_pt), h2_EffMapC->GetYaxis()->FindBin(fabs(jet_eta)) );
	    
	    float UDSGtag_SF = GetLightJetSF(jet_pt,jet_eta,BtagSys*1);
	    float UDSGtag_eff = h2_EffMapUDSG->GetBinContent( h2_EffMapUDSG->GetXaxis()->FindBin(jet_pt), h2_EffMapUDSG->GetYaxis()->FindBin(fabs(jet_eta)) );
	    
	    btsfutil->modifyBTagsWithSF(isTagged, jet_flavor, Btag_SF,Btag_eff,Ctag_SF,Ctag_eff,UDSGtag_SF,UDSGtag_eff);
	    //if (temp != isTagged)
	    // cout<< endl << "GOT ONE!!!!!!!!!!!: "<<temp<<"  "<<isTagged<<" "<<jet_flavor<<"  "<<bdiscCSV_PF[i]<<endl;
	    delete btsfutil;
	  }
	  
	  Jet->setBtag(isTagged);
	  nJet20++;
	  fCleanJets20.push_back(Jet);
	  SumptAllJet20=SumptAllJet20+jet_PF_pt[i];
	  if(jet_PF_pt[i]>35.0){
	    SumptAllJet=SumptAllJet+jet_PF_pt[i];
	    fCleanJets.push_back(Jet);
	    h_NeutralHad_JetPt->Fill(jet_PF_pt[i],jet_PF_NeutralHad[i],weight);
	    JetMoms.push_back(jet_PF_JetMom[i]);
	    //	cout<<"JetMomFromTree: "<<jet_PF_JetMom[i]<<endl;
	    //cout<<"JetMomFromTree_InArray: "<<JetMoms[nJet35]<<endl;
	    
	    nJet35++;
	    dummycounter++;
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
      

        SumMetPtAllJet = pfMET + SumptAllJet;
	SumMetPtAllJet20 = pfMET + SumptAllJet20;
	//cout<<nTruePileUp<<" "<<MyWeight<<" "<<weight<<endl;



	//MUON/////
	//make some plots for the muons
	  
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
       h_HMT_Base->Fill(SumMetPtAllJet20,weight);
       h_Jet0_Base->Fill(fCleanJets20[0]->Pt(),weight);
       h_Jet1_Base->Fill(fCleanJets20[1]->Pt(),weight);
       h_Jet2_Base->Fill(fCleanJets20[2]->Pt(),weight);
       h_Jet3_Base->Fill(fCleanJets20[3]->Pt(),weight);
       if(nBJet35>2){
	 h_BJet1_Base->Fill(fBJets[0]->Pt(),weight);
	 h_BJet2_Base->Fill(fBJets[1]->Pt(),weight);
	 h_BJet3_Base->Fill(fBJets[2]->Pt(),weight);
	} 
       if(nJet20>=5) h_Jet4_Base->Fill(fCleanJets20[4]->Pt(),weight);
       if(nJet20>=6) h_Jet5_Base->Fill(fCleanJets20[5]->Pt(),weight);
            if(HasSelTrigger){
	      h_MET_BaseSel->Fill(pfMET,weight);
	      h_HT_BaseSel->Fill(SumptAllJet20,weight);
	      h_HMT_BaseSel->Fill(SumMetPtAllJet20,weight);
	      h_Jet0_BaseSel->Fill(fCleanJets20[0]->Pt(),weight);
	      h_Jet1_BaseSel->Fill(fCleanJets20[1]->Pt(),weight);
	      h_Jet2_BaseSel->Fill(fCleanJets20[2]->Pt(),weight);
	      h_Jet3_BaseSel->Fill(fCleanJets20[3]->Pt(),weight);
	      if(nBJet35>2){           
                  h_BJet1_BaseSel->Fill(fBJets[0]->Pt(),weight);
		  h_BJet2_BaseSel->Fill(fBJets[1]->Pt(),weight);
                  h_BJet3_BaseSel->Fill(fBJets[2]->Pt(),weight);
	      }
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



     //  if ( nJet35>=6 && nMuons>=1)
     //     if ( nJet35>=6 && SumptAllJet>800)
     h_nBJet35->Fill(nBJet35,weight);
     h_nJet35->Fill(nJet35,weight);
     h_MET->Fill(pfMET,weight);
     h_nTruePileUp->Fill(nTruePileUp,weight);
     h_nTruePileUp_NoWeight->Fill(nTruePileUp);
     h_nVertex->Fill(nGoodVtx,weight);
     h_HT->Fill(SumptAllJet,weight);
     h_HMT->Fill(SumMetPtAllJet,weight);
     if(nBJet35>2){           
         h_BJet1->Fill(fBJets[0]->Pt(),weight);
         h_BJet2->Fill(fBJets[1]->Pt(),weight);
         h_BJet3->Fill(fBJets[2]->Pt(),weight);
      }
     if(nJet35>=1)h_Jet0->Fill(fCleanJets[0]->Pt(),weight);
     if(nJet35>=2)h_Jet1->Fill(fCleanJets[1]->Pt(),weight);
     if(nJet35>=3)h_Jet2->Fill(fCleanJets[2]->Pt(),weight);
     if(nJet35>=4)h_Jet3->Fill(fCleanJets[3]->Pt(),weight);
     if(nJet35>=5)h_Jet4->Fill(fCleanJets[4]->Pt(),weight);
     if(nJet35>=6)h_Jet5->Fill(fCleanJets[5]->Pt(),weight);
        
     	      
     if ( nJet35>=6){
       //cout<<nJet35<<" "<<fCleanJets.size()<<" s"<<fCleanJets[0]->Pt()<<" "<<fCleanJets[1]->Pt()<<" "<<fCleanJets[2]->Pt()<<" "<<fCleanJets[3]->Pt()<<" "<<fCleanJets[4]->Pt()<<" "<<fCleanJets[5]->Pt()<<endl;
       //       if(fCleanJets[0]->Pt() > 80.0 && fCleanJets[1]->Pt() > 80. && fCleanJets[2]->Pt() > 80.0 && fCleanJets[3]->Pt() > 80.0 && 
       //fCleanJets[4]->Pt() > 60.0 && fCleanJets[5]->Pt() > 60.0)

       if(fCleanJets[3]->Pt() > 80 ){
       //      if(SumptAllJet>900)
	 if(1==1){//nBJet35 >= 3)

	   h_nBJet35_EvtSel->Fill(nBJet35,weight);
	   h_nJet35_EvtSel->Fill(nJet35,weight);
	   h_MET_EvtSel->Fill(pfMET,weight);
	   h_HT_EvtSel->Fill(SumptAllJet,weight);
	   h_HMT_EvtSel->Fill(SumMetPtAllJet,weight);
	   h_Jet0_EvtSel->Fill(fCleanJets[0]->Pt(),weight);
	   h_Jet1_EvtSel->Fill(fCleanJets[1]->Pt(),weight);
	   h_Jet2_EvtSel->Fill(fCleanJets[2]->Pt(),weight);
	   if(nBJet35>2){           
                  h_BJet1_EvtSel->Fill(fBJets[0]->Pt(),weight);
		  h_BJet2_EvtSel->Fill(fBJets[1]->Pt(),weight);
                  h_BJet3_EvtSel->Fill(fBJets[2]->Pt(),weight);
	      }
	   if(nJet35>=4) h_Jet3_EvtSel->Fill(fCleanJets[3]->Pt(),weight);
	   if(nJet35>=5) h_Jet4_EvtSel->Fill(fCleanJets[4]->Pt(),weight);
	   if(nJet35>=6) h_Jet5_EvtSel->Fill(fCleanJets[5]->Pt(),weight);
	   if(nJet35>=7) h_Jet6_EvtSel->Fill(fCleanJets[6]->Pt(),weight);
	   //all the jets make triplets
	   //  	   int numJetForTriplet=fCleanJets.size();
	   //only the six leading jets make triplets
	   unsigned int numJetForTriplet=6;
       int nTriplets=0;
       for (unsigned int i=0+0; i<numJetForTriplet-2; ++i) {
	 for (unsigned int j=i+1; j<numJetForTriplet-1; ++j) {
	   for (unsigned int k=j+1; k<numJetForTriplet-0; ++k) {
	     Triplet.push_back(std::vector<JetLV* > ());
	     
	     JetLV* Jet1; JetLV* Jet2; JetLV* Jet3;
	     Jet1=fCleanJets[i]; Jet2=fCleanJets[j]; Jet3=fCleanJets[k];
	     TLorentzVector Triplet123; Triplet123=(*Jet1+*Jet2+*Jet3);
	     TLorentzVector Doublet12; Doublet12=*Jet1+*Jet2;
	     TLorentzVector Doublet13; Doublet13=*Jet1+*Jet3;
	     TLorentzVector Doublet23; Doublet23=*Jet2+*Jet3;

	     sumScalarPtTriplet.push_back(Jet1->Pt()+Jet2->Pt()+Jet3->Pt());
	     massTriplet.push_back(Triplet123.M());
	     sumVectorPtTriplet.push_back(Triplet123.Pt());
	     int TripletMomGood=-1;
	     if(JetMoms[i]==-1 || JetMoms[j]==-1 || JetMoms[k]==-1) TripletMomGood=-1;
	     if((JetMoms[i]!=-1 && JetMoms[j]!=-1 && JetMoms[k]!=-1) && (JetMoms[i]==JetMoms[j] && JetMoms[i]==JetMoms[k] && JetMoms[j]==JetMoms[k])) TripletMomGood=JetMoms[i];
	    

	     TripletMoms.push_back(TripletMomGood);
	     //	     cout<<"Combo: "<<i<<" "<<j<<" "<<k<<" JetMoms: "<<JetMoms[i]<<" "<<JetMoms[j]<<" "<<JetMoms[k]<<" TripleMoms: "<<TripletMoms[nTriplets]<<endl;
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
     
       

	 for(int b=0; b<5; b++){

	 for (int i=0; i<10; i++)
	   {
	     float iPt=30.0+(float)i*10.0;
	     for(int k=0; k<3; k++)
	       { 
		 unsigned int iNjet=k+6;
		 //count njets with the pt cut -> gonna be slow
	       for(unsigned int q=0; q<massTriplet.size(); q++){
		  
       
		 if(iNjet<=fCleanJets.size()){
		  
		   if(Triplet[q][2]->Pt()>iPt && fCleanJets[iNjet-1]->Pt()>iPt && nBJet35==b)
		     {	
		       Mjjj_sumpt_bjet_pt_njet[b][i][k]->Fill(sumScalarPtTriplet[q],massTriplet[q],weight);
		     }
		   if(Triplet[q][2]->Pt()>iPt && fCleanJets[iNjet-1]->Pt()>iPt &&
		   	 nBJet35>=b && (Triplet[q][0]->btagged ||
		   	 	 Triplet[q][1]->btagged || Triplet[q][2]->btagged))
		     {	
		       Mjjj_sumpt_btag_pt_njet[b][i][k]->Fill(sumScalarPtTriplet[q],massTriplet[q],weight);
		     }
		   for(int j=0; j<25; j++){
		        
		     float iDiag=(float)j*10.0+40.0;
		     //to implement the pt cut we only keep triplets where the lowest jet passes pt cut
		     //also we check if the njetsMin cut satisfies this pt cut
		     //std::cout<<"before selection"<<endl;
		     // std::cout<<Triplet[q][2].pt()<<" "<<fCleanJets.size()<<" "<<fCleanJets[iNjet-1].pt()<<endl;
		     //if(iNjet>fCleanJets.size())
		     // cout<<Triplet[q][2].pt()<<endl;
		     // cout<<fCleanJets.size()<<endl;
		     // cout<<iNjet-1<<endl;
		     if(Triplet[q][2]->Pt()>iPt && fCleanJets[njetsMin-1]->Pt()>iPt && fCleanJets[iNjet-1]->Pt()>iPt && nBJet35==b)
		       {
			 //cout<<"after selection"<<endl;
			 //cout<<Triplet[q][2].pt()<<" "<<fCleanJets.size()<<" "<<fCleanJets[iNjet-1].pt()<<endl;
			 if(massTriplet[q]<(sumScalarPtTriplet[q]-iDiag))
			   {
			     float countT=0;
			     Mjjj_bjet_pt_njet_diag[b][i][k][j]->Fill(massTriplet[q],weight);
			    
			     if(TripletMoms[q]==0 || TripletMoms[q]==1)
			       Mjjj_bjet_pt_njet_diag_MCmatch[b][i][k][j]->Fill(massTriplet[q],weight);
			     if(TripletMoms[q]!=0 && TripletMoms[q]!=1)
			       Mjjj_bjet_pt_njet_diag_MCcomb[b][i][k][j]->Fill(massTriplet[q],weight);
			     
			     if(b==0)
			       {Mjjj_btag_bjet_pt_njet_diag[b][i][k][j]->Fill(massTriplet[q],weight);
				  MET_bjet_pt_njet_diag[b][i][k][j]->Fill(pfMET, weight);
			     HT_bjet_pt_njet_diag[b][i][k][j]->Fill(SumptAllJet, weight);
			     MET_over_HT_bjet_pt_njet_diag[b][i][k][j]->Fill(pfMET/SumptAllJet, weight);
			     HMT_bjet_pt_njet_diag[b][i][k][j]->Fill(SumMetPtAllJet20, weight);
			     nJet35_bjet_pt_njet_diag[b][i][k][j]->Fill(nJet35, weight);
			     nBJet35_bjet_pt_njet_diag[b][i][k][j]->Fill(nBJet35, weight);
			     nVertex_bjet_pt_njet_diag[b][i][k][j]->Fill(nGoodVtx,weight);
			     Jet0_bjet_pt_njet_diag[b][i][k][j]->Fill(fCleanJets[0]->Pt(), weight);
			     Jet1_bjet_pt_njet_diag[b][i][k][j]->Fill(fCleanJets[1]->Pt(), weight);
			     Jet2_bjet_pt_njet_diag[b][i][k][j]->Fill(fCleanJets[2]->Pt(), weight);
			     if(nJet35>=4)Jet3_bjet_pt_njet_diag[b][i][k][j]->Fill(fCleanJets[3]->Pt(), weight);
			     if(nJet35>=5)Jet4_bjet_pt_njet_diag[b][i][k][j]->Fill(fCleanJets[4]->Pt(), weight);
			     if(nJet35>=6)Jet5_bjet_pt_njet_diag[b][i][k][j]->Fill(fCleanJets[5]->Pt(), weight);
			     if(nJet35>=7)Jet5_bjet_pt_njet_diag[b][i][k][j]->Fill(fCleanJets[5]->Pt(), weight);
			     if(nBJet35>2){ 
			       BJet1_bjet_pt_njet_diag[b][i][k][j]->Fill(fBJets[0]->Pt(), weight);
			       BJet2_bjet_pt_njet_diag[b][i][k][j]->Fill(fBJets[1]->Pt(), weight);
			       BJet3_bjet_pt_njet_diag[b][i][k][j]->Fill(fBJets[2]->Pt(), weight);
			       }

			       }
			     if (b>=1){
			       if (Triplet[q][0]->btagged || Triplet[q][1]->btagged || Triplet[q][2]->btagged)
				 {
				   Mjjj_btag_bjet_pt_njet_diag[b][i][k][j]->Fill(massTriplet[q],weight);
				   MET_bjet_pt_njet_diag[b][i][k][j]->Fill(pfMET, weight);
			     HT_bjet_pt_njet_diag[b][i][k][j]->Fill(SumptAllJet, weight);
			     MET_over_HT_bjet_pt_njet_diag[b][i][k][j]->Fill(pfMET/SumptAllJet, weight);
			     HMT_bjet_pt_njet_diag[b][i][k][j]->Fill(SumMetPtAllJet20, weight);
			     nJet35_bjet_pt_njet_diag[b][i][k][j]->Fill(nJet35, weight);
			     nBJet35_bjet_pt_njet_diag[b][i][k][j]->Fill(nBJet35, weight);
			     nVertex_bjet_pt_njet_diag[b][i][k][j]->Fill(nGoodVtx,weight);
			     Jet0_bjet_pt_njet_diag[b][i][k][j]->Fill(fCleanJets[0]->Pt(), weight);
			     Jet1_bjet_pt_njet_diag[b][i][k][j]->Fill(fCleanJets[1]->Pt(), weight);
			     Jet2_bjet_pt_njet_diag[b][i][k][j]->Fill(fCleanJets[2]->Pt(), weight);
			     if(nJet35>=4)Jet3_bjet_pt_njet_diag[b][i][k][j]->Fill(fCleanJets[3]->Pt(), weight);
			     if(nJet35>=5)Jet4_bjet_pt_njet_diag[b][i][k][j]->Fill(fCleanJets[4]->Pt(), weight);
			     if(nJet35>=6)Jet5_bjet_pt_njet_diag[b][i][k][j]->Fill(fCleanJets[5]->Pt(), weight);
			     if(nJet35>=7)Jet5_bjet_pt_njet_diag[b][i][k][j]->Fill(fCleanJets[5]->Pt(), weight);
			     if(nBJet35>2){ 
			       BJet1_bjet_pt_njet_diag[b][i][k][j]->Fill(fBJets[0]->Pt(), weight);
			       BJet2_bjet_pt_njet_diag[b][i][k][j]->Fill(fBJets[1]->Pt(), weight);
			       BJet3_bjet_pt_njet_diag[b][i][k][j]->Fill(fBJets[2]->Pt(), weight);
			       } 
				 }
			     }
			     
			     countT++;
			          
			    
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
	 } //minjet
     //lets see if the top branching ratios work
    
  } else notrig++;
 }//Msquqark

  //delete Triplet; 
    //delete &sumScalarPtTriplet; delete  &sumVectorPtTriplet; delete &massTriplet;
    /*delete &fBJets; delete &fNoBJets; delete &fCleanJets;  delete  &fCleanJets20; delete &fTestJets;
    delete  &massDoublet12; delete &massDoublet13; delete &massDoublet23;
    delete  &massDoubletHigh; delete &massDoubletMid; delete  &massDoubletLow;
    */
 }//get entrye
 cout << "\n events w/o trigger " << notrig << endl;

  /*  fBJets.clear(); fNoBJets.clear();fCleanJets.clear();    fCleanJets20.clear(); fTestJets.clear();
  massDoublet12.clear();  massDoublet13.clear(); massDoublet23.clear();
  massDoubletHigh.clear();  massDoubletMid.clear();  massDoubletLow.clear();
  */
}

float NtpThreeJet::GetBTagSF (float pt, float eta, int meanminmax){
  float jetPt=pt;

  float SFb_Unc_MultFactor =1.0;

  if (jetPt>800.0) jetPt= 800.0;
  if (jetPt<20.0) jetPt = 20.0;




  float  ScaleFactor     = CSVM_SFb_0to2p4->Eval(jetPt);
  float  ScaleFactor_unc = CSVM_SFb_errors->GetBinContent(CSVM_SFb_errors->GetXaxis()->FindBin(jetPt));
  
  float ScaleFactor_up   = ScaleFactor + abs(meanminmax)*SFb_Unc_MultFactor*ScaleFactor_unc;
  float ScaleFactor_down = ScaleFactor - abs(meanminmax)*SFb_Unc_MultFactor*ScaleFactor_unc;

  
  if(meanminmax==0) return ScaleFactor;
  if(meanminmax==-1 || meanminmax == -2) return ScaleFactor_down;
  if(meanminmax==1 || meanminmax == 2) return ScaleFactor_up;
  return ScaleFactor;
}



float NtpThreeJet::GetLightJetSF (float pt, float eta, int meanminmax){
  float jetPt=pt; 
  float jetAbsEta = fabs(eta);
  if (jetPt>800.0) jetPt= 800.0;
  if (jetPt<20.0) jetPt = 20.0;
  float  ScaleFactor     = 1;
  float ScaleFactor_up   = 1;
  float ScaleFactor_down = 1;

  if( pt>800 )
    {
      ScaleFactor      = CSVM_SFl_0to2p4->Eval(800);
      ScaleFactor_up   = ScaleFactor + 2*( (CSVM_SFl_0to2p4_max->Eval(800) - CSVM_SFl_0to2p4->Eval(800))/CSVM_SFl_0to2p4->Eval(800) )*ScaleFactor;
      ScaleFactor_down = ScaleFactor + 2*( (CSVM_SFl_0to2p4_min->Eval(800) - CSVM_SFl_0to2p4->Eval(800))/CSVM_SFl_0to2p4->Eval(800) )*ScaleFactor;
    }
  else
    {
      if(jetAbsEta<0.8)
	{
	  ScaleFactor      = CSVM_SFl_0to0p8->Eval(jetPt);
	  ScaleFactor_up   = ScaleFactor + ( (CSVM_SFl_0to0p8_max->Eval(jetPt) - CSVM_SFl_0to0p8->Eval(jetPt))/CSVM_SFl_0to0p8->Eval(jetPt) )*ScaleFactor;
	  ScaleFactor_down = ScaleFactor + ( (CSVM_SFl_0to0p8_min->Eval(jetPt) - CSVM_SFl_0to0p8->Eval(jetPt))/CSVM_SFl_0to0p8->Eval(jetPt) )*ScaleFactor;
	}
      else if(jetAbsEta>=0.8 && jetAbsEta<1.6)
	{
	  ScaleFactor      = CSVM_SFl_0p8to1p6->Eval(jetPt);
	  ScaleFactor_up   = ScaleFactor + ( (CSVM_SFl_0p8to1p6_max->Eval(jetPt) - CSVM_SFl_0p8to1p6->Eval(jetPt))/CSVM_SFl_0p8to1p6->Eval(jetPt) )*ScaleFactor;
	  ScaleFactor_down = ScaleFactor + ( (CSVM_SFl_0p8to1p6_min->Eval(jetPt) - CSVM_SFl_0p8to1p6->Eval(jetPt))/CSVM_SFl_0p8to1p6->Eval(jetPt) )*ScaleFactor;
	}
      else
	{
	  ScaleFactor      = CSVM_SFl_1p6to2p4->Eval(jetPt);
	  ScaleFactor_up   = ScaleFactor + ( (CSVM_SFl_1p6to2p4_max->Eval(jetPt) - CSVM_SFl_1p6to2p4->Eval(jetPt))/CSVM_SFl_1p6to2p4->Eval(jetPt) )*ScaleFactor;
	  ScaleFactor_down = ScaleFactor + ( (CSVM_SFl_1p6to2p4_min->Eval(jetPt) - CSVM_SFl_1p6to2p4->Eval(jetPt))/CSVM_SFl_1p6to2p4->Eval(jetPt) )*ScaleFactor;
	}
    }
  if(meanminmax==0) return ScaleFactor;
  if(meanminmax==-1) return ScaleFactor_down;
  if(meanminmax==1) return ScaleFactor_up;
  return ScaleFactor;
}
