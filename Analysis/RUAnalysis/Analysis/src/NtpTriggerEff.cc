\

//#Includetr "RUAnalysis/Ntupler/interface/Ntupler.h"
#include "RUAnalysis/Analysis/interface/NtpTriggerEff.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "TLorentzVector.h"
#include "TFile.h"
#include "math.h"

using namespace std;

NtpTriggerEff::NtpTriggerEff (std::vector<TString>& InFileNames, bool const IsData, TString const OutFileName) : NtpReader(InFileNames, IsData)
{
  fOutFile = new TFile(OutFileName, "recreate");
  if (!fOutFile->IsOpen()) {
    std::cerr << "ERROR: cannot open output root file " << OutFileName << std::endl;
    throw;
  }
}

NtpTriggerEff::~NtpTriggerEff ()
{

}


void NtpTriggerEff::BookHistograms()
{


  char hNAME[99];  
  h_RunNumber_Base = new TH1F("RunNumber_Base","RunNumber_Base",6000,190000,196000); h_RunNumber_Base->Sumw2();
  h_RunNumber_BaseSel = new TH1F("RunNumber_BaseSel","RunNumber_BaseSel",6000,190000,196000); h_RunNumber_BaseSel->Sumw2();
  h_RunNumber_Sel = new TH1F("RunNumber_Sel","RunNumber_Sel",6000,190000,196000); h_RunNumber_Sel->Sumw2();

 

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
  for(int i=0; i<20; i++){
    for (int j=0; j<20; j++){
      int iPt=20+i*5;
      int jPt=20+j*5;
      h_Jet0_BaseSel_pt4_pt6.push_back(std::vector<TH1F*> ());
      sprintf(hNAME, "h_Jet0_BaseSel_FourPt%i_SixPt%i", jPt, iPt);
      h_Jet0_BaseSel_pt4_pt6[i].push_back(new TH1F(hNAME,hNAME,20,0,20));
      h_Jet0_BaseSel_pt4_pt6[i][j]->Sumw2();

      h_Jet0_Base_pt4_pt6.push_back(std::vector<TH1F*> ());
      sprintf(hNAME, "h_Jet0_Base_FourPt%i_SixPt%i", jPt, iPt);
      h_Jet0_Base_pt4_pt6[i].push_back(new TH1F(hNAME,hNAME,20,0,20));
      h_Jet0_Base_pt4_pt6[i][j]->Sumw2();

      h_Jet4.push_back(std::vector<TH1F*> ());
      sprintf(hNAME, "h_Jet4_FourPt%i_SixPt%i", jPt, iPt);
      h_Jet4[i].push_back(new TH1F(hNAME,hNAME,200,0,1000));
      h_Jet4[i][j]->Sumw2();

      h_Jet6.push_back(std::vector<TH1F*> ());
      sprintf(hNAME, "h_Jet6_FourPt%i_SixPt%i", jPt, iPt);
      h_Jet6[i].push_back(new TH1F(hNAME,hNAME,200,0,1000));
      h_Jet6[i][j]->Sumw2();
    }
  }
  cout<<"after histos"<<endl;
  return;
}
 
void NtpTriggerEff::WriteHistograms()
{cout<<"made it here"<<endl;
  char FOLDER[100];
  fOutFile->cd();


  h_RunNumber_Base->Write();
  h_RunNumber_BaseSel->Write();
  h_RunNumber_Sel->Write();
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

   for(int i=0; i<20; i++){
     for (int j=0; j<20; j++){
       h_Jet0_BaseSel_pt4_pt6[i][j]->Write();
       h_Jet0_Base_pt4_pt6[i][j]->Write();
       h_Jet4[i][j]->Write();
       h_Jet6[i][j]->Write();
     }
   }
  return;
}
  

void NtpTriggerEff::Loop ()
{


  for (int ientry = 0; GetEntry(ientry) > 0; ++ientry) {

    
  ///////////////////Clear out variables/////////////////////

    std::vector<TLorentzVector* >      fCleanJets;
    std::vector<TLorentzVector* >      fCleanJets20;

    fCleanJets.clear();    fCleanJets20.clear(); 
  ////////////////////////////////////////////////////////////
   
    if (ientry % 500 == 0) {
      printf("Processing entry: %i\n", ientry);
    }
   int nJet20=0; int nJet35=0; 
   int nBJet20=0;
   for (int i=0; i<nPFJets; i++){
     TLorentzVector* Jet= new TLorentzVector(jet_PF_px[i],jet_PF_py[i],jet_PF_pz[i],jet_PF_e[i]);
     
     if (jet_PF_pt[i]>20.0 && fabs(jet_PF_eta[i])<2.5){
       nJet20++;
       fCleanJets20.push_back(Jet);
       if (bdiscCSV_PF[i] > 0.679)
	 {
	   nBJet20++;
	 }
       
       if(jet_PF_pt[i]>35.0){
	 fCleanJets.push_back(Jet);
	 nJet35++;
	 
       }
     }
   }
   
       
     ////TRIGGER////////////
   if(nJet20>=6){
     for(int i=0; i<20; i++){
       for (int j=0; j<20; j++){
	 int iPt=20+i*5;
	 int jPt=20+j*5;
	 if(fCleanJets20[3]->Pt()>jPt && fCleanJets20[5]->Pt()>iPt){
	   if(nBJet20 >= 2){
	     if(HasBaseTrigger){
	       h_Jet0_Base_pt4_pt6[i][j]->Fill(1);
	       h_Jet4[i][j]->Fill(fCleanJets20[3]->Pt());
	       h_Jet6[i][j]->Fill(fCleanJets20[5]->Pt());	     
	       if(HasSelTrigger) h_Jet0_BaseSel_pt4_pt6[i][j]->Fill(1);
	     }
	   }
	 }
       }
     }
     if(HasSelTrigger){
       h_RunNumber_Sel->Fill(run);
}
if(HasBaseTrigger){
       if(1==1){
	 //if(fCleanJets20[0]->Pt()>85 && fCleanJets20[1]->Pt()>85 && fCleanJets20[2]->Pt()>85 && fCleanJets20[3]->Pt()>85 && fCleanJets20[4]->Pt()>50 && fCleanJets20[5]->Pt()>50){
	 h_RunNumber_Base->Fill(run);
       h_MET_Base->Fill(pfMET);
       h_Jet0_Base->Fill(fCleanJets20[0]->Pt());
       h_Jet1_Base->Fill(fCleanJets20[1]->Pt());
       h_Jet2_Base->Fill(fCleanJets20[2]->Pt());
       h_Jet3_Base->Fill(fCleanJets20[3]->Pt());
       if(nJet20>=5) h_Jet4_Base->Fill(fCleanJets20[4]->Pt());
       if(nJet20>=6) h_Jet5_Base->Fill(fCleanJets20[5]->Pt());
            if(HasSelTrigger){
	      h_RunNumber_BaseSel->Fill(run);
	      h_MET_BaseSel->Fill(pfMET);
	      h_Jet0_BaseSel->Fill(fCleanJets20[0]->Pt());
	      h_Jet1_BaseSel->Fill(fCleanJets20[1]->Pt());
	      h_Jet2_BaseSel->Fill(fCleanJets20[2]->Pt());
	      h_Jet3_BaseSel->Fill(fCleanJets20[3]->Pt());
	      if(nJet20>=5) h_Jet4_BaseSel->Fill(fCleanJets20[4]->Pt());
	      if(nJet20>=6) h_Jet5_BaseSel->Fill(fCleanJets20[5]->Pt());
	    }
       }
     }

     }
  }   
  return;
}
