#include "TopBSM/RUTopXAna/interface/NtpTopXana.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "TLorentzVector.h"
#include "TFile.h"
#include "math.h"

using namespace std;

NtpTopXana::NtpTopXana (std::vector<TString>& InFileNames, bool const IsData, TString const OutFileName) : NtpReader(InFileNames, IsData)
{
  fOutFile = new TFile(OutFileName, "recreate");
  if (!fOutFile->IsOpen()) {
    std::cerr << "ERROR: cannot open output root file " << OutFileName << std::endl;
    throw;
  }
}

NtpTopXana::~NtpTopXana ()
{
  if (fOutFile) {
    fOutFile->Write();
    fOutFile->Close();
    delete fOutFile;
  }
}


void NtpTopXana::BookHistograms()
{
  char hNAME[99];
  
  h_NumEvtCut = new TH1F("NumEvtCut", "NumEvtCut",20,0,20);
  h_MET = new TH1F("MET", "MET",200,0,1000);
  //redefining everything with vectors
  //different cuts
  CutList.push_back("4Jet_1b_P");
  CutList.push_back("4Jet_2b_P");
   CutList.push_back("4Jet_1b_M");
   CutList.push_back("4Jet_2b_M");
   CutList.push_back("5Jet_1b_P");
   CutList.push_back("5Jet_2b_P");
   CutList.push_back("5Jet_1b_M");
   CutList.push_back("5Jet_2b_M");
   //different variables
   VarList.push_back("SumptSig4Highest_");
   VarList.push_back("SumptSig4SecondHighest_");
   VarList.push_back("TransMassLepMET4Jet_");
   VarList.push_back("TransMassLepMET5Jet_");
   VarList.push_back("TransMassLepMET4JetB_");
   VarList.push_back("TransMassLepMET5JetB_");
   VarList.push_back("Mass3Jet2B_");
   VarList.push_back("MassLep1Jet_");
   VarList.push_back("MassLep1B_");
   VarList.push_back("MassLepB_vs_SumPt_");
   VarList.push_back("DeltaPhiLepMET_");
   VarList.push_back("LepBJet_Diag50_Upper160_4Jet_");
   VarList.push_back("LepB_Diag50_Upper160_3Jet1B_");
   VarList.push_back("LeadingJetPt_");
   VarList.push_back("St_");
   VarList.push_back("TransMassLepMET4Jet_vs_LeadingJetPt_");
   VarList.push_back("TransMassLepMET1JetB_");
   VarList.push_back("Mass3Jet1B_");
   VarList.push_back("TransMassLepMET1JetB_vs_Mass3Jet1B_");
   VarList.push_back("vh_ChargeXeta");
    VarList.push_back("TransMass3Jet1B");
    VarList.push_back("DeltaPhiLep1Jet");

   //std::cout<<CutList[0]+VarList[0]<<std::endl;
   for (int f=0; f< (int) CutList.size(); f++){
     vh_SumptSig4Highest.push_back          (new TH1F((VarList[0]+CutList[f]).c_str(),(VarList[0]+CutList[f]).c_str(),200,0,2));
     vh_SumptSig4SecondHighest.push_back    (new TH1F((VarList[1]+CutList[f]).c_str(),(VarList[1]+CutList[f]).c_str(),200,0,2));
     vh_TransMassLepMET4Jet.push_back       (new TH1F((VarList[2]+CutList[f]).c_str(),(VarList[2]+CutList[f]).c_str(),200,0,2000));
     vh_TransMassLepMET5Jet.push_back       (new TH1F((VarList[3]+CutList[f]).c_str(),(VarList[3]+CutList[f]).c_str(),200,0,2000));

     vh_TransMassLepMET4JetB.push_back      (new TH1F((VarList[4]+CutList[f]).c_str(),(VarList[4]+CutList[f]).c_str(),200,0,2000));
     vh_TransMassLepMET5JetB.push_back      (new TH1F((VarList[5]+CutList[f]).c_str(),(VarList[5]+CutList[f]).c_str(),200,0,2000));

     vh_Mass3Jet2B.push_back                (new TH1F((VarList[6]+CutList[f]).c_str(),(VarList[6]+CutList[f]).c_str(),200,0,2000));
     vh_MassLep1Jet.push_back               (new TH1F((VarList[7]+CutList[f]).c_str(),(VarList[7]+CutList[f]).c_str(),200,0,1000));
     vh_MassLep1B.push_back                 (new TH1F((VarList[8]+CutList[f]).c_str(),(VarList[8]+CutList[f]).c_str(),200,0,2000));
     vh_MassLepB_vs_SumPt.push_back         (new TH2F((VarList[9]+CutList[f]).c_str(),(VarList[9]+CutList[f]).c_str(),200,0,1000,200,0,1000));
     vh_DeltaPhiLepMET.push_back            (new TH1F((VarList[10]+CutList[f]).c_str(),(VarList[10]+CutList[f]).c_str(),200,0,7));

     vh_LepBDiag50_Upper160_4Jet.push_back  (new TH1F((VarList[11]+CutList[f]).c_str(),(VarList[11]+CutList[f]).c_str(),200,0,2000));
     vh_LepBDiag50_Upper160_3Jet1B.push_back(new TH1F((VarList[12]+CutList[f]).c_str(),(VarList[12]+CutList[f]).c_str(),200,0,2000));

     vh_LeadingJetPt.push_back              (new TH1F((VarList[13]+CutList[f]).c_str(),(VarList[13]+CutList[f]).c_str(),200,0,600));
     vh_St.push_back                        (new TH1F((VarList[14]+CutList[f]).c_str(),(VarList[14]+CutList[f]).c_str(),200,0,2000));

     vh_TransMassLepMET4Jet_vs_LeadingJetPt.push_back(new TH2F((VarList[15]+CutList[f]).c_str(),(VarList[15]+CutList[f]).c_str(),200,0,2000,200,0,2000));
     vh_TransMassLepMET1JetB.push_back    (new TH1F((VarList[16]+CutList[f]).c_str(),(VarList[16]+CutList[f]).c_str(),200,0,2000));

     vh_Mass3Jet1B.push_back    (new TH1F((VarList[17]+CutList[f]).c_str(),(VarList[17]+CutList[f]).c_str(),200,0,2000));
     vh_TransMassLepMET1JetB_vs_Mass3Jet1B.push_back(new TH2F((VarList[18]+CutList[f]).c_str(),(VarList[18]+CutList[f]).c_str(),200,0,2000,200,0,2000));

     vh_ChargeXeta.push_back          (new TH1F((VarList[19]+CutList[f]).c_str(),(VarList[19]+CutList[f]).c_str(),200,-10,10));
     vh_TransMass3Jet1B.push_back                       (new TH1F((VarList[20]+CutList[f]).c_str(),(VarList[20]+CutList[f]).c_str(),200,0,2000));
     vh_DeltaPhiLep1Jet.push_back                       (new TH1F((VarList[21]+CutList[f]).c_str(),(VarList[21]+CutList[f]).c_str(),200,0,7));
   }

   ///////variables for optimization////////
   for(int i=0; i<35; i++){
     sprintf(hNAME, "TransMassLepMET1JetB_1jet_%i_pt", i*10+70);
     vh_TransMassLepMET1JetB_pt.push_back    (new TH1F(hNAME,hNAME,200,0,2000));
     sprintf(hNAME, "TransMassLepMET1JetB_delphi_%ip%i", i/2, ((int)((i*0.5+1)*10)) % 10);
     vh_TransMassLepMET1JetB_delphi.push_back    (new TH1F(hNAME,hNAME,200,0,2000));
     sprintf(hNAME, "TransMassLepMET1JetB_st_%i", i*50+200);
     vh_TransMassLepMET1JetB_st.push_back    (new TH1F(hNAME,hNAME,200,0,2000));

     sprintf(hNAME, "TransMassLepMET4Jet_1jet_%i_pt", i*10+70);
     vh_TransMassLepMET4Jet_pt.push_back    (new TH1F(hNAME,hNAME,200,0,2000));
     sprintf(hNAME, "TransMassLepMET4Jet_delphi_%ip%i", i/2, ((int)((i*0.5+1)*10)) % 10);
     vh_TransMassLepMET4Jet_delphi.push_back    (new TH1F(hNAME,hNAME,200,0,2000));
     sprintf(hNAME, "TransMassLepMET4Jet_st_%i", i*50+200);
     vh_TransMassLepMET4Jet_st.push_back    (new TH1F(hNAME,hNAME,200,0,2000));
     

      vh_TransMassLepMET4Jet_pt_st.push_back(std::vector<TH1F* >());
      vh_TransMassLepMET1JetB_pt_st.push_back(std::vector<TH1F* >());
     for(int j=0; j<35; j++){
      
       sprintf(hNAME, "TransMassLepMET4Jet_1jet_%i_st_%i", i*10+70,j*50+200);
        vh_TransMassLepMET4Jet_pt_st[i].push_back(new TH1F(hNAME,hNAME,200,0,2000));

	 
       sprintf(hNAME, "TransMassLepMET1JetB_1jet_%i_st_%i", i*10+70,j*50+200);
        vh_TransMassLepMET1JetB_pt_st[i].push_back(new TH1F(hNAME,hNAME,200,0,2000));
     }



   }
   //MC plots
 h_MCwprimeMassPos = new TH1F("MCwprimeMassPos", "MCwprimeMassPos",200,0,2000);
 h_MCwprimeMassNeg = new TH1F("MCwprimeMassNeg", "MCwprimeMassNeg",200,0,2000);
 h_MCwprimeMETMassPos = new TH1F("MCwprimeMETMassPos", "MCwprimeMETMassPos",200,0,2000);
 h_MCwprimeMETMassNeg = new TH1F("MCwprimeMETMassNeg", "MCwprimeMETMassNeg",200,0,2000);
 h_minChi2Pos = new TH1F("minChi2Pos", "minCh2Pos",1000,0,1000);
 h_minChi2Neg = new TH1F("minChi2Neg", "minCh2Neg",1000,0,1000);
 h_MCPhidLepTopPos = new TH1F("MCPhidLepTopPos", "MCPhidLepTopPos",200,0,4);
 h_MCPhidLepTopNeg = new TH1F("MCPhidLepTopNeg", "MCPhidLepTopNeg",200,0,4);
 h_MCPhiWpTopPos = new TH1F("MCPhiWpTopPos", "MCPhiWpTopPos",200,0,4);
 h_MCPhiWpTopNeg = new TH1F("MCPhiWpTopNeg", "MCPhiWpTopNeg",200,0,4);
 h_MCPhiWpTop = new TH1F("MCPhiWpTop", "MCPhiWpTop",200,0,4);
 return;
}
 
void NtpTopXana::WriteHistograms()
{
  fOutFile->cd();
  h_NumEvtCut->Write();
  h_MET->Write();
  for (int f=0; f< (int) CutList.size(); f++){
    fOutFile->cd();
    fOutFile->mkdir(CutList[f].c_str());
    fOutFile->cd(CutList[f].c_str());
    
    vh_SumptSig4Highest[f]->Write();
    vh_SumptSig4SecondHighest[f]->Write();
    vh_TransMassLepMET4Jet[f]->Write();
    vh_TransMassLepMET5Jet[f]->Write();
    vh_TransMassLepMET4JetB[f]->Write();
    vh_TransMassLepMET5JetB[f]->Write();
    vh_Mass3Jet2B[f]->Write();
    vh_MassLep1Jet[f]->Write();
    vh_MassLep1B[f]->Write();
    vh_MassLepB_vs_SumPt[f]->Write();
    vh_DeltaPhiLepMET[f]->Write();
    vh_LepBDiag50_Upper160_4Jet[f]->Write();
    vh_LepBDiag50_Upper160_3Jet1B[f]->Write();
    vh_LeadingJetPt[f]->Write();
    vh_St[f]->Write();
    vh_TransMassLepMET4Jet_vs_LeadingJetPt[f]->Write();
    vh_TransMassLepMET1JetB[f]->Write();
    vh_Mass3Jet1B[f]->Write();
    vh_TransMassLepMET1JetB_vs_Mass3Jet1B[f]->Write();
    vh_ChargeXeta[f]->Write();
    vh_TransMass3Jet1B[f]->Write();
    vh_DeltaPhiLep1Jet[f]->Write();
  }
  fOutFile->cd();
  fOutFile->mkdir("Optimization");
  fOutFile->cd("Optimization");
   for(int i=0; i<35; i++){
     vh_TransMassLepMET1JetB_pt[i]->Write();
     vh_TransMassLepMET1JetB_delphi[i]->Write();
     vh_TransMassLepMET1JetB_st[i]->Write();

     vh_TransMassLepMET4Jet_pt[i]->Write();
     vh_TransMassLepMET4Jet_delphi[i]->Write();
     vh_TransMassLepMET4Jet_st[i]->Write();
     
     for(int j=0; j<35; j++){
      
        vh_TransMassLepMET4Jet_pt_st[i][j]->Write();
	vh_TransMassLepMET1JetB_pt_st[i][j]->Write();
     }

   }
 fOutFile->cd();
 fOutFile->mkdir("MCwprime");
 fOutFile->cd("MCwprime");
 h_MCwprimeMassPos->Write();
 h_MCwprimeMassNeg->Write();
 h_MCwprimeMETMassPos->Write();
 h_MCwprimeMETMassNeg->Write();
 h_minChi2Neg->Write();
 h_minChi2Pos->Write();
 h_MCPhidLepTopNeg->Write();
 h_MCPhidLepTopPos->Write();
 h_MCPhiWpTopPos->Write();
 h_MCPhiWpTopNeg->Write();
 h_MCPhiWpTop->Write();
  return;
}
  

void NtpTopXana::Loop ()
{
  // Run over all entries and do what you like!
  int countallhad=0;
  int countlep=0;
  int countsemilep=0;

  for (int ientry = 0; GetEntry(ientry) > 0; ++ientry) {
    
    

    if (ientry % 1000 == 0) {
      printf("Processing entry: %i\n", ientry);
    }

    if (nElectrons == 2) {
      //printf("2 Electrons Pt: %12.1f %12.1f\n", ept[0], ept[1]);
      TLorentzVector Lep0(epx[0],epy[0],epz[0],ee[0]);
      TLorentzVector Lep1(epx[1],epy[1],epz[1],ee[1]);
      //std::cout<<(Lep0+Lep1).Mag()<<std::endl;

    }

    int nJet35=0; int nBJet35=0; int nNoBJet35=0; fBJets.clear(); fNoBJets.clear();fCleanJets.clear();
    float SumptAllJet=0;
     for (int i=0; i<nJets; i++){
      TLorentzVector Jet(jetpx[i],jetpy[i],jetpz[i],jete[i]);
      if (jetpt[i]>35.0){
	SumptAllJet=SumptAllJet+jetpt[i];
	fCleanJets.push_back(Jet);
	nJet35=i+1;
	if (bdiscSSVHE[i] > 1.74)
	  {
	    nBJet35++;
	    fBJets.push_back(Jet);
	  }
	if (bdiscSSVHE[i] <= 1.74)
	  {
	    nNoBJet35++;
	    fNoBJets.push_back(Jet);
	  }
      }
    }

     //////////OPTIMIZATION PLOTS////////////
     if ((nElectrons+ nMuons) == 1){
       if (nElectrons==1 && ept[0]>45.0){
	 if( pfMET>30.0){
	   if(nJet35 >=5 && nBJet35>=1){
	     for(int i=0; i<35; i++){
	       TLorentzVector fLepton(epx[0],epy[0],epz[0],ee[0]);
	       TLorentzVector fMET;
	       fMET.SetPtEtaPhiE(pfMET,0,pfMETphi,pfMET);
	       TLorentzVector v_TransMassLepMET1JetB;
	       v_TransMassLepMET1JetB.SetPx(fLepton.Px()+fMET.Px()+fNoBJets[0].Px()+fBJets[0].Px());
	       v_TransMassLepMET1JetB.SetPy(fLepton.Py()+fMET.Py()+fNoBJets[0].Py()+fBJets[0].Py());
	       v_TransMassLepMET1JetB.SetPz(0);
	       v_TransMassLepMET1JetB.SetE(fLepton.Et()+fMET.Et()+fNoBJets[0].Et()+fBJets[0].Et());
	   
	       TLorentzVector v_TransMassLepMET4Jet;
	       v_TransMassLepMET4Jet.SetPx(fLepton.Px()+fMET.Px()+fCleanJets[0].Px()+fCleanJets[1].Px()+fCleanJets[2].Px()+fCleanJets[3].Px());
	       v_TransMassLepMET4Jet.SetPy(fLepton.Py()+fMET.Py()+fCleanJets[0].Py()+fCleanJets[1].Py()+fCleanJets[2].Py()+fCleanJets[3].Py());
	       v_TransMassLepMET4Jet.SetPz(0);
	       v_TransMassLepMET4Jet.SetE(fLepton.Et()+fMET.Et()+fCleanJets[0].Et()+fCleanJets[1].Et()+fCleanJets[2].Et()+fCleanJets[3].Et());

	       float St=0;
	       St=SumptAllJet+ept[0]+pfMET;
	       
	       fMET.SetPtEtaPhiE(pfMET,0,pfMETphi,pfMET);
	       
	       if(fCleanJets[0].Pt()> i*10+70){
		 vh_TransMassLepMET1JetB_pt[i]->Fill(v_TransMassLepMET1JetB.Mag());
		 vh_TransMassLepMET4Jet_pt[i]->Fill(v_TransMassLepMET4Jet.Mag());
	       }
	       
	       if(fabs(pfMETphi-fLepton.Phi())<i*0.5+1){
		 vh_TransMassLepMET1JetB_delphi[i]->Fill(v_TransMassLepMET1JetB.Mag());
		 vh_TransMassLepMET4Jet_delphi[i]->Fill(v_TransMassLepMET4Jet.Mag());
	       }
		  
	       if(St> i*50+200){
		 vh_TransMassLepMET1JetB_st[i]->Fill(v_TransMassLepMET1JetB.Mag());
		 vh_TransMassLepMET4Jet_st[i]->Fill(v_TransMassLepMET4Jet.Mag());
	       }
	       
	       for(int j=0; j<35; j++){
		 
		 if(St> j*50+200 && fCleanJets[0].Pt()> i*10+70) vh_TransMassLepMET4Jet_pt_st[i][j]->Fill(v_TransMassLepMET4Jet.Mag());
		  if(St> j*50+200 && fCleanJets[0].Pt()> i*10+70) vh_TransMassLepMET1JetB_pt_st[i][j]->Fill(v_TransMassLepMET1JetB.Mag());
		 }

	     }
	   }
	 }
       }
     }
     
     //std::cout<<nJet35<<" "<<nNoBJet35<<std::endl; 
    h_NumEvtCut->Fill(0);
    if ((nElectrons+ nMuons) == 1){//asking for exactly one clean muon or electron > 20GeV
     h_NumEvtCut->Fill(1); //cout<<"1------------"<<endl;
     if (nElectrons==1 && ept[0]>45.0){//one electron with pt > 45 GeV
       h_NumEvtCut->Fill(2);
       h_MET->Fill(pfMET);// cout<<"2------------"<<endl;
       if( pfMET>30.0){//MET above 30
	 h_NumEvtCut->Fill(3); //cout<<"3------------"<<endl;
	 if(nJet35 >=1){//at least one jet with pt >35
	   h_NumEvtCut->Fill(4); //cout<<"4------------"<<endl;
	   if(nJet35 >=2){//at least two jet with pt >35
	     h_NumEvtCut->Fill(5); //cout<<"5------------"<<endl;
	     if(nJet35 >=1 && nBJet35>=1){ //cout<<"6------------"<<endl;
	       h_NumEvtCut->Fill(6);
	       if(nJet35 >=3){
		 h_NumEvtCut->Fill(7); //cout<<"7------------"<<endl;
		 
		     if(nJet35 >=4){ //cout<<"8------------"<<endl;
		        TLorentzVector fLepton(epx[0],epy[0],epz[0],ee[0]);
			TLorentzVector fMET;
			fMET.SetPtEtaPhiE(pfMET,0,pfMETphi,pfMET);
			float St=0;
			St=SumptAllJet+ept[0]+pfMET;
			if(1==1/*fabs(pfMETphi-fLepton.Phi())<2.0*/)
			 {
			  
			   h_NumEvtCut->Fill(8);
			   
			   TLorentzVector v_TransMassLepMET4Jet;
			   v_TransMassLepMET4Jet.SetPx(fLepton.Px()+fMET.Px()+fCleanJets[0].Px()+fCleanJets[1].Px()+fCleanJets[2].Px()+fCleanJets[3].Px());
			   v_TransMassLepMET4Jet.SetPy(fLepton.Py()+fMET.Py()+fCleanJets[0].Py()+fCleanJets[1].Py()+fCleanJets[2].Py()+fCleanJets[3].Py());
			   v_TransMassLepMET4Jet.SetPz(0);
			   v_TransMassLepMET4Jet.SetE(fLepton.Et()+fMET.Et()+fCleanJets[0].Et()+fCleanJets[1].Et()+fCleanJets[2].Et()+fCleanJets[3].Et());
			   TLorentzVector v_TransMassLepMET4Jet1B;
			   if(nBJet35>=1 && nNoBJet35>=3)
			     {
			       v_TransMassLepMET4Jet1B.SetPx(fLepton.Px()+fMET.Px()+fNoBJets[0].Px()+fNoBJets[1].Px()+fNoBJets[2].Px()+fBJets[0].Px());
			       v_TransMassLepMET4Jet1B.SetPy(fLepton.Py()+fMET.Py()+fNoBJets[0].Py()+fNoBJets[1].Py()+fNoBJets[2].Py()+fBJets[0].Py());
			       v_TransMassLepMET4Jet1B.SetPz(0);
			       v_TransMassLepMET4Jet1B.SetE(fLepton.Et()+fMET.Et()+fNoBJets[0].Et()+fNoBJets[1].Et()+fNoBJets[2].Et()+fBJets[0].Et());
			     }
			   TLorentzVector v_TransMassLepMET4Jet2B;
			   if(nBJet35>=2 && nNoBJet35>=2)
			     {
			       v_TransMassLepMET4Jet2B.SetPx(fLepton.Px()+fMET.Px()+fNoBJets[0].Px()+fNoBJets[1].Px()+fBJets[0].Px()+fBJets[1].Px());
			       v_TransMassLepMET4Jet2B.SetPy(fLepton.Py()+fMET.Py()+fNoBJets[0].Py()+fNoBJets[1].Py()+fBJets[0].Py()+fBJets[1].Py());
			       v_TransMassLepMET4Jet2B.SetPz(0);
			       v_TransMassLepMET4Jet2B.SetE(fLepton.Et()+fMET.Et()+fNoBJets[0].Et()+fNoBJets[1].Et()+fBJets[0].Et()+fBJets[1].Et());
			     }
			 
			   
			   float SumptSig4Highest=0;
			   SumptSig4Highest=((fCleanJets[0]+fCleanJets[1]+fCleanJets[2]+fCleanJets[3]+fLepton+fMET).Pt())
			     /(fCleanJets[0].Pt()+fCleanJets[1].Pt()+fCleanJets[2].Pt()+fCleanJets[3].Pt()+fLepton.Pt()+fMET.Pt());
			   
			   TLorentzVector v_TransMassLepMET;
			   v_TransMassLepMET.SetPx(fLepton.Px()+fMET.Px());
			   v_TransMassLepMET.SetPy(fLepton.Py()+fMET.Py());
			   v_TransMassLepMET.SetPz(0);
			   v_TransMassLepMET.SetE(fLepton.Et()+fMET.Et());
			   
			   TLorentzVector v_TransMassLepMET1JetB;
			   v_TransMassLepMET1JetB.SetPx(fLepton.Px()+fMET.Px()+fNoBJets[0].Px()+fBJets[0].Px());
			   v_TransMassLepMET1JetB.SetPy(fLepton.Py()+fMET.Py()+fNoBJets[0].Py()+fBJets[0].Py());
			   v_TransMassLepMET1JetB.SetPz(0);
			   v_TransMassLepMET1JetB.SetE(fLepton.Et()+fMET.Et()+fNoBJets[0].Et()+fBJets[0].Et());

			  
			     TLorentzVector v_TransMass3Jet1B;
			     if(nBJet35>=1 && nNoBJet35 >=3){
			   v_TransMass3Jet1B.SetPx(fNoBJets[0].Px()+fNoBJets[1].Px()+fNoBJets[2].Px()+fBJets[0].Px());
			   v_TransMass3Jet1B.SetPy(fNoBJets[0].Py()+fNoBJets[1].Py()+fNoBJets[2].Py()+fBJets[0].Py());
			   v_TransMass3Jet1B.SetPz(0);
			   v_TransMass3Jet1B.SetE(fNoBJets[0].Et()+fNoBJets[1].Et()+fNoBJets[2].Et()+fBJets[0].Et());
			     }
			     //std::cout<<v_TransMassLepMET1JetB.Mag()<<std::endl;
			 /////////Positives charges//////////
			   if(fCleanJets[0].Pt()>180 && St >700.0){
			   if(*echarge==+1)
			     {
			     //one or more btags
			       if(nBJet35>=1)
				 {
				   vh_TransMassLepMET4Jet                  [0]->Fill(v_TransMassLepMET4Jet.Mag());
				   vh_TransMassLepMET4Jet_vs_LeadingJetPt  [0]->Fill(fCleanJets[0].Pt(),v_TransMassLepMET4Jet.Mag());
				   vh_SumptSig4Highest                     [0]->Fill(SumptSig4Highest);
				   vh_MassLep1B                            [0]->Fill((fLepton+fBJets[0]).Mag());
				   vh_MassLepB_vs_SumPt                    [0]->Fill(fLepton.Pt()+fBJets[0].Pt(),(fLepton+fBJets[0]).Mag());
				   vh_DeltaPhiLepMET                       [0]->Fill(fabs(pfMETphi-fLepton.Phi()));
				   vh_LeadingJetPt                         [0]->Fill(fCleanJets[0].Pt());
				   vh_St                                   [0]->Fill(St);
				   vh_TransMassLepMET1JetB                 [0]->Fill(v_TransMassLepMET1JetB.Mag());
				   vh_ChargeXeta                           [0]->Fill(*echarge * fLepton.Eta());
				   
                                   
				   vh_DeltaPhiLep1Jet                      [0]->Fill(min(fabs(fLepton.Phi()-fCleanJets[0].Phi()), 2*3.14159265 - fabs(fLepton.Phi()-fCleanJets[0].Phi())));


				   if(nNoBJet35>=3){
				     vh_TransMassLepMET4JetB                [0]->Fill(v_TransMassLepMET4Jet1B.Mag());
				     vh_TransMass3Jet1B                     [0]->Fill(v_TransMass3Jet1B.Mag());
				     vh_MassLep1Jet                         [0]->Fill((fLepton+fNoBJets[0]).Mag());
				     vh_Mass3Jet1B                          [0]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fBJets[0]).Mag());
				     vh_TransMassLepMET1JetB_vs_Mass3Jet1B  [0]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fBJets[0]).Mag(),v_TransMassLepMET1JetB.Mag());
				   }
				   
				   
				 }
			       if(nBJet35>=2)
				 {
				   vh_TransMassLepMET4Jet                  [1]->Fill(v_TransMassLepMET4Jet.Mag());
				   vh_TransMassLepMET4Jet_vs_LeadingJetPt  [1]->Fill(fCleanJets[0].Pt(),v_TransMassLepMET4Jet.Mag());
				   vh_SumptSig4Highest                     [1]->Fill(SumptSig4Highest);
				   
				   
				   vh_DeltaPhiLepMET                       [1]->Fill(fabs(pfMETphi-fLepton.Phi()));
				   
				   vh_DeltaPhiLep1Jet                      [1]->Fill(min(fabs(fLepton.Phi()-fCleanJets[0].Phi()), 2*3.14159265 - fabs(fLepton.Phi()-fCleanJets[0].Phi())));
				   
				  

				   vh_LeadingJetPt                         [1]->Fill(fCleanJets[0].Pt());
				   vh_St                                 [1]->Fill(St);
				   vh_MassLep1B                            [1]->Fill((fLepton+fBJets[0]).Mag());
				   vh_MassLep1B                            [1]->Fill((fLepton+fBJets[1]).Mag());
				   vh_MassLepB_vs_SumPt                    [1]->Fill(fLepton.Pt()+fBJets[0].Pt(),(fLepton+fBJets[0]).Mag());
				   vh_MassLepB_vs_SumPt                    [1]->Fill(fLepton.Pt()+fBJets[1].Pt(),(fLepton+fBJets[1]).Mag());
				   vh_TransMassLepMET1JetB                  [1]->Fill(v_TransMassLepMET1JetB.Mag());
				    vh_ChargeXeta                           [1]->Fill(*echarge * fLepton.Eta());
				   if(nNoBJet35>=2)
				     {
				       vh_TransMassLepMET4JetB                [1]->Fill(v_TransMassLepMET4Jet2B.Mag());
				       vh_MassLep1Jet                         [1]->Fill((fLepton+fNoBJets[0]).Mag());
				     }
				 }
			       
			     }
			      
			   if(*echarge==-1)
			     {
			       //one or more btags
			       if(nBJet35>=1)
				 {
				   vh_TransMassLepMET4Jet                  [2]->Fill(v_TransMassLepMET4Jet.Mag());
				   vh_TransMassLepMET4Jet_vs_LeadingJetPt  [2]->Fill(fCleanJets[0].Pt(),v_TransMassLepMET4Jet.Mag());
				   vh_SumptSig4Highest                     [2]->Fill(SumptSig4Highest);
				   vh_MassLep1B                            [2]->Fill((fLepton+fBJets[0]).Mag());
				   vh_MassLepB_vs_SumPt                    [2]->Fill(fLepton.Pt()+fBJets[0].Pt(),(fLepton+fBJets[0]).Mag());
				   vh_DeltaPhiLepMET                       [2]->Fill(fabs(pfMETphi-fLepton.Phi()));
				   vh_DeltaPhiLep1Jet                      [2]->Fill(min(fabs(fLepton.Phi()-fCleanJets[0].Phi()), 2*3.14159265 - fabs(fLepton.Phi()-fCleanJets[0].Phi())));
				   
				   vh_LeadingJetPt                         [2] ->Fill(fCleanJets[0].Pt());
				   vh_St                                   [2]->Fill(St);
				   vh_TransMassLepMET1JetB                 [2]->Fill(v_TransMassLepMET1JetB.Mag());
				   vh_ChargeXeta                           [2]->Fill(*echarge * fLepton.Eta());
				   if(nNoBJet35>=3){
				     vh_TransMassLepMET4JetB                [2]->Fill(v_TransMassLepMET4Jet1B.Mag());
				     vh_MassLep1Jet                         [2]->Fill((fLepton+fNoBJets[0]).Mag());
				     vh_Mass3Jet1B                          [2]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fBJets[0]).Mag());
				     vh_TransMass3Jet1B                     [2]->Fill(v_TransMass3Jet1B.Mag());
				     vh_TransMassLepMET1JetB_vs_Mass3Jet1B  [2]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fBJets[0]).Mag(),v_TransMassLepMET1JetB.Mag());
				   }
				   
				 }
			       if(nBJet35>=2)
				 {
				   vh_TransMassLepMET4Jet                 [3]->Fill(v_TransMassLepMET4Jet.Mag());
				   vh_TransMassLepMET4Jet_vs_LeadingJetPt [3]->Fill(fCleanJets[0].Pt(),v_TransMassLepMET4Jet.Mag());
				   vh_SumptSig4Highest                    [3]->Fill(SumptSig4Highest);
				   
				   
				   vh_DeltaPhiLepMET                      [3]->Fill(fabs(pfMETphi-fLepton.Phi()));
				   vh_DeltaPhiLep1Jet                      [3]->Fill(min(fabs(fLepton.Phi()-fCleanJets[0].Phi()), 2*3.14159265 - fabs(fLepton.Phi()-fCleanJets[0].Phi())));
				   
				  

				   vh_LeadingJetPt                        [3]->Fill(fCleanJets[0].Pt());
				   vh_St                                  [3]->Fill(St);
				   vh_TransMassLepMET1JetB                [3]->Fill(v_TransMassLepMET1JetB.Mag());
				   vh_ChargeXeta                          [3]->Fill(*echarge * fLepton.Eta());
				   //double entries
				   vh_MassLep1B                           [3]->Fill((fLepton+fBJets[0]).Mag());
				   vh_MassLep1B                           [3]->Fill((fLepton+fBJets[1]).Mag());
				   vh_MassLepB_vs_SumPt                   [3]->Fill(fLepton.Pt()+fBJets[0].Pt(),(fLepton+fBJets[0]).Mag());
				   vh_MassLepB_vs_SumPt                   [3]->Fill(fLepton.Pt()+fBJets[1].Pt(),(fLepton+fBJets[1]).Mag());
				   
				   if(nNoBJet35>=2)
				     {
				       vh_TransMassLepMET4JetB               [3]->Fill(v_TransMassLepMET4Jet2B.Mag());
				       vh_MassLep1Jet                        [3]->Fill((fLepton+fNoBJets[0]).Mag());
				     }
				 }
			       
			     }
			   
			   
			   
			   
			      }
			   
			   if(nJet35 >=5)
			     {
			       //cout<<"9------------"<<endl;
			       //std::cout<<*echarge<<" "<<nJet35<<" "<<nBJet35<<" "<<nNoBJet35<<" "<<run<<" "<<lumis<<" "<<event<<std::endl;
			       float SumptSig4SecondHighest=0;
			       SumptSig4SecondHighest=((fCleanJets[1]+fCleanJets[2]+fCleanJets[3]+fCleanJets[4]+fLepton+fMET).Pt())
				 /(fCleanJets[1].Pt()+fCleanJets[2].Pt()+fCleanJets[3].Pt()+fCleanJets[4].Pt()+fLepton.Pt()+fMET.Pt());
			       TLorentzVector v_TransMassLepMET5Jet;
			       v_TransMassLepMET5Jet.SetPx(fLepton.Px()+fMET.Px()+fCleanJets[0].Px()+fCleanJets[1].Px()+fCleanJets[2].Px()+fCleanJets[3].Px()+fCleanJets[4].Px());
			       v_TransMassLepMET5Jet.SetPy(fLepton.Py()+fMET.Py()+fCleanJets[0].Py()+fCleanJets[1].Py()+fCleanJets[2].Py()+fCleanJets[3].Py()+fCleanJets[4].Py());
			       v_TransMassLepMET5Jet.SetPz(0);
			       v_TransMassLepMET5Jet.SetE(fLepton.Et()+fMET.Et()+fCleanJets[0].Et()+fCleanJets[1].Et()+fCleanJets[2].Et()+fCleanJets[3].Et()+fCleanJets[4].Et());
			       
			       
			       TLorentzVector v_TransMassLepMET5Jet1B;
			       if(nBJet35>=1 && nNoBJet35>=4)
				 {
				   v_TransMassLepMET4Jet1B.SetPx(fLepton.Px()+fMET.Px()+fNoBJets[0].Px()+fNoBJets[1].Px()+fNoBJets[2].Px()+fNoBJets[3].Px()+fBJets[0].Px());
				   v_TransMassLepMET4Jet1B.SetPy(fLepton.Py()+fMET.Py()+fNoBJets[0].Py()+fNoBJets[1].Py()+fNoBJets[2].Py()+fNoBJets[3].Py()+fBJets[0].Py());
				   v_TransMassLepMET4Jet1B.SetPz(0);
				   v_TransMassLepMET4Jet1B.SetE(fLepton.Et()+fMET.Et()+fNoBJets[0].Et()+fNoBJets[1].Et()+fNoBJets[2].Et()+fNoBJets[3].Et()+fBJets[0].Et());
				 }
			       TLorentzVector v_TransMassLepMET5Jet2B;
			       if(nBJet35>=2 && nNoBJet35>=3)
				 {
				   v_TransMassLepMET4Jet2B.SetPx(fLepton.Px()+fMET.Px()+fNoBJets[0].Px()+fNoBJets[1].Px()+fNoBJets[2].Px()+fBJets[0].Px()+fBJets[1].Px());
				   v_TransMassLepMET4Jet2B.SetPy(fLepton.Py()+fMET.Py()+fNoBJets[0].Py()+fNoBJets[1].Py()+fNoBJets[2].Py()+fBJets[0].Py()+fBJets[1].Py());
				   v_TransMassLepMET4Jet2B.SetPz(0);
				   v_TransMassLepMET4Jet2B.SetE(fLepton.Et()+fMET.Et()+fNoBJets[0].Et()+fNoBJets[1].Et()+fNoBJets[2].Et()+fBJets[0].Et()+fBJets[1].Et());
				 }
			       
			       h_NumEvtCut->Fill(9);
			       
			       //positive leptons
			        if(fCleanJets[0].Pt()>180 && St >700.0){
			       if(*echarge==+1)
				 {
				   if (nBJet35>=1)
				     { 
				       float f_MassLep1B=(fLepton+fBJets[0]).Mag();
				       float f_SumptLep1B=(fLepton.Pt()+fBJets[0].Pt());
				       
				       vh_TransMassLepMET4Jet                 [4]->Fill(v_TransMassLepMET4Jet.Mag());
				       vh_TransMassLepMET4Jet_vs_LeadingJetPt [4]->Fill(fCleanJets[0].Pt(),v_TransMassLepMET4Jet.Mag());
				       vh_TransMassLepMET5Jet                 [4]->Fill(v_TransMassLepMET5Jet.Mag());
				       vh_SumptSig4Highest                    [4]->Fill(SumptSig4Highest);
				       vh_SumptSig4SecondHighest              [4]->Fill(SumptSig4SecondHighest);
				       vh_MassLep1B                           [4]->Fill((fLepton+fBJets[0]).Mag());
				       vh_MassLepB_vs_SumPt                   [4]->Fill(fLepton.Pt()+fBJets[0].Pt(),(fLepton+fBJets[0]).Mag());
				       vh_DeltaPhiLepMET                      [4]->Fill(fabs(pfMETphi-fLepton.Phi()));

				       vh_DeltaPhiLep1Jet                      [4]->Fill(min(fabs(fLepton.Phi()-fCleanJets[0].Phi()), 2*3.14159265 - fabs(fLepton.Phi()-fCleanJets[0].Phi())));
				       
				       

				       vh_LeadingJetPt                        [4]->Fill(fCleanJets[0].Pt());
				       vh_St                                  [4]->Fill(St);
				       vh_TransMassLepMET1JetB                [4]->Fill(v_TransMassLepMET1JetB.Mag());
				       vh_ChargeXeta                          [4]->Fill(*echarge * fLepton.Eta());
				       if(nNoBJet35>=4)
					 {
					   vh_TransMassLepMET4JetB              [4]->Fill(v_TransMassLepMET4Jet1B.Mag());
					   vh_TransMassLepMET5JetB              [4]->Fill(v_TransMassLepMET5Jet1B.Mag());
					   vh_MassLep1Jet                       [4]->Fill((fLepton+fNoBJets[0]).Mag());
					   vh_Mass3Jet1B                          [4]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fBJets[0]).Mag());
					   vh_TransMass3Jet1B                     [4]->Fill(v_TransMass3Jet1B.Mag());
					   vh_TransMassLepMET1JetB_vs_Mass3Jet1B  [4]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fBJets[0]).Mag(),v_TransMassLepMET1JetB.Mag());
					   if((f_MassLep1B<f_SumptLep1B-50) /*&& f_MassLep1B < 160*/)
					     {
					       vh_LepBDiag50_Upper160_4Jet       [4]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fNoBJets[3]).Mag());
					     }
					 }
				     }

				   if (nBJet35>=2)
				     { 
				       float f_MassLep1Ba=(fLepton+fBJets[0]).Mag();
				       float f_SumptLep1Ba=(fLepton.Pt()+fBJets[0].Pt());
				       float f_MassLep1Bb=(fLepton+fBJets[1]).Mag();
				       float f_SumptLep1Bb=(fLepton.Pt()+fBJets[1].Pt());
				       
				       vh_TransMassLepMET4Jet                 [5]->Fill(v_TransMassLepMET4Jet.Mag());
				       vh_TransMassLepMET4Jet_vs_LeadingJetPt [5]->Fill(fCleanJets[0].Pt(),v_TransMassLepMET4Jet.Mag());
				       vh_TransMassLepMET5Jet                 [5]->Fill(v_TransMassLepMET5Jet.Mag());
				       vh_SumptSig4Highest                    [5]->Fill(SumptSig4Highest);
				       vh_SumptSig4SecondHighest              [5]->Fill(SumptSig4SecondHighest);
				       
				       vh_DeltaPhiLepMET                      [5]->Fill(fabs(pfMETphi-fLepton.Phi()));
				       vh_DeltaPhiLep1Jet                      [5]->Fill(min(fabs(fLepton.Phi()-fCleanJets[0].Phi()), 2*3.14159265 - fabs(fLepton.Phi()-fCleanJets[0].Phi())));

				      

				       vh_LeadingJetPt                        [5]->Fill(fCleanJets[0].Pt());
				       vh_St                                  [5]->Fill(St);
				       vh_TransMassLepMET1JetB                [5]->Fill(v_TransMassLepMET1JetB.Mag());
				       vh_ChargeXeta                          [5]->Fill(*echarge * fLepton.Eta());
				       vh_MassLep1B                           [5]->Fill((fLepton+fBJets[0]).Mag());
				       vh_MassLep1B                           [5]->Fill((fLepton+fBJets[1]).Mag());
				       vh_MassLepB_vs_SumPt                   [5]->Fill(fLepton.Pt()+fBJets[0].Pt(),(fLepton+fBJets[0]).Mag());
				       vh_MassLepB_vs_SumPt                   [5]->Fill(fLepton.Pt()+fBJets[1].Pt(),(fLepton+fBJets[1]).Mag());

				       if(nNoBJet35>=3)
					 {
					   vh_TransMassLepMET4JetB             [5]->Fill(v_TransMassLepMET4Jet2B.Mag());
					   vh_TransMassLepMET5JetB             [5]->Fill(v_TransMassLepMET5Jet1B.Mag());
					   vh_Mass3Jet2B                       [5]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fBJets[0]+fBJets[1]).Mag());
					   vh_MassLep1Jet                      [5]->Fill((fLepton+fNoBJets[0]).Mag());
					   vh_Mass3Jet1B                          [5]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fBJets[0]).Mag());
					   vh_TransMass3Jet1B                     [5]->Fill(v_TransMass3Jet1B.Mag());
					   vh_TransMassLepMET1JetB_vs_Mass3Jet1B  [5]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fBJets[0]).Mag(),v_TransMassLepMET1JetB.Mag());
					   if((f_MassLep1Ba<f_SumptLep1Ba-50) /*&& f_MassLep1Ba < 160*/)
					     {
					       vh_LepBDiag50_Upper160_3Jet1B      [5]->Fill((fBJets[1]+fNoBJets[0]+fNoBJets[1]+fNoBJets[2]).Mag());
					     }
					   if((f_MassLep1Bb<f_SumptLep1Bb-50) /*&& f_MassLep1Bb < 160*/)
					     {
					       vh_LepBDiag50_Upper160_3Jet1B      [5]->Fill((fBJets[0]+fNoBJets[0]+fNoBJets[1]+fNoBJets[2]).Mag());
					     }
					 }
				     }
				   
				 }
			       
			       if(*echarge==-1)
				 {
				   if (nBJet35>=1)
				     { 
				       float f_MassLep1B=(fLepton+fBJets[0]).Mag();
				       float f_SumptLep1B=(fLepton.Pt()+fBJets[0].Pt());
				       
				       vh_TransMassLepMET4Jet                 [6]->Fill(v_TransMassLepMET4Jet.Mag());
				       vh_TransMassLepMET4Jet_vs_LeadingJetPt [6]->Fill(fCleanJets[0].Pt(),v_TransMassLepMET4Jet.Mag());
				       vh_TransMassLepMET5Jet                 [6]->Fill(v_TransMassLepMET5Jet.Mag());
				       vh_SumptSig4Highest                    [6]->Fill(SumptSig4Highest);
				       vh_SumptSig4SecondHighest              [6]->Fill(SumptSig4SecondHighest);
				       vh_MassLep1B                           [6]->Fill((fLepton+fBJets[0]).Mag());
				       vh_MassLepB_vs_SumPt                   [6]->Fill(fLepton.Pt()+fBJets[0].Pt(),(fLepton+fBJets[0]).Mag());
				       vh_DeltaPhiLepMET                      [6]->Fill(fabs(pfMETphi-fLepton.Phi()));
				       vh_DeltaPhiLep1Jet                      [6]->Fill(min(fabs(fLepton.Phi()-fCleanJets[0].Phi()), 2*3.14159265 - fabs(fLepton.Phi()-fCleanJets[0].Phi())));
				       
				       vh_LeadingJetPt                        [6]->Fill(fCleanJets[0].Pt());
				       vh_St                                  [6]->Fill(St);
				       vh_TransMassLepMET1JetB                [6]->Fill(v_TransMassLepMET1JetB.Mag());
				       vh_ChargeXeta                          [6]->Fill(*echarge * fLepton.Eta());
				       if(nNoBJet35>=4)
					 {
					   vh_TransMassLepMET4JetB              [6]->Fill(v_TransMassLepMET4Jet1B.Mag());
					   vh_TransMassLepMET5JetB              [6]->Fill(v_TransMassLepMET5Jet1B.Mag());
					   vh_MassLep1Jet                       [6]->Fill((fLepton+fNoBJets[0]).Mag());
					   vh_Mass3Jet1B                          [6]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fBJets[0]).Mag());
					   vh_TransMass3Jet1B                     [6]->Fill(v_TransMass3Jet1B.Mag());
					   vh_TransMassLepMET1JetB_vs_Mass3Jet1B  [6]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fBJets[0]).Mag(),v_TransMassLepMET1JetB.Mag());
					   if((f_MassLep1B<f_SumptLep1B-50) /*&& f_MassLep1B < 160*/)
					     {
					       vh_LepBDiag50_Upper160_4Jet       [6]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fNoBJets[3]).Mag());
					     }
					 }
				     }

				   if (nBJet35>=2)
				     { 
				       float f_MassLep1Ba=(fLepton+fBJets[0]).Mag();
				       float f_SumptLep1Ba=(fLepton.Pt()+fBJets[0].Pt());
				       float f_MassLep1Bb=(fLepton+fBJets[1]).Mag();
				       float f_SumptLep1Bb=(fLepton.Pt()+fBJets[1].Pt());
				       
				       vh_TransMassLepMET4Jet                 [7]->Fill(v_TransMassLepMET4Jet.Mag());
				       vh_TransMassLepMET4Jet_vs_LeadingJetPt [7]->Fill(fCleanJets[0].Pt(),v_TransMassLepMET4Jet.Mag());
				       vh_TransMassLepMET5Jet                 [7]->Fill(v_TransMassLepMET5Jet.Mag());
				       vh_SumptSig4Highest                    [7]->Fill(SumptSig4Highest);
				       vh_SumptSig4SecondHighest              [7]->Fill(SumptSig4SecondHighest);
				      
				       vh_DeltaPhiLepMET                      [7]->Fill(fabs(pfMETphi-fLepton.Phi()));
				      
				       vh_DeltaPhiLep1Jet                      [7]->Fill(min(fabs(fLepton.Phi()-fCleanJets[0].Phi()), 2*3.14159265 - fabs(fLepton.Phi()-fCleanJets[0].Phi())));
				      
				       vh_LeadingJetPt                        [7]->Fill(fCleanJets[0].Pt());
				       vh_St                                  [7]->Fill(St);
				       vh_TransMassLepMET1JetB                [7]->Fill(v_TransMassLepMET1JetB.Mag());
				       vh_ChargeXeta                          [7]->Fill(*echarge * fLepton.Eta());
				       vh_MassLep1B                           [7]->Fill((fLepton+fBJets[0]).Mag());
				       vh_MassLep1B                           [7]->Fill((fLepton+fBJets[1]).Mag());
				       vh_MassLepB_vs_SumPt                   [7]->Fill(fLepton.Pt()+fBJets[0].Pt(),(fLepton+fBJets[0]).Mag());
				       vh_MassLepB_vs_SumPt                   [7]->Fill(fLepton.Pt()+fBJets[1].Pt(),(fLepton+fBJets[1]).Mag());

				       if(nNoBJet35>=3)
					 {
					   vh_TransMassLepMET4JetB             [7]->Fill(v_TransMassLepMET4Jet2B.Mag());
					   vh_TransMassLepMET5JetB             [7]->Fill(v_TransMassLepMET5Jet1B.Mag());
					   vh_Mass3Jet2B                       [7]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fBJets[0]+fBJets[1]).Mag());
					   vh_MassLep1Jet                      [7]->Fill((fLepton+fNoBJets[0]).Mag());
					   vh_Mass3Jet1B                          [7]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fBJets[0]).Mag());
					   vh_TransMass3Jet1B                     [7]->Fill(v_TransMass3Jet1B.Mag());
					   vh_TransMassLepMET1JetB_vs_Mass3Jet1B  [7]->Fill((fNoBJets[0]+fNoBJets[1]+fNoBJets[2]+fBJets[0]).Mag(),v_TransMassLepMET1JetB.Mag());
					  
					   if((f_MassLep1Ba<f_SumptLep1Ba-50) /*&& f_MassLep1Ba < 160*/)
					     {//std::cout<<(fBJets[1]+fNoBJets[0]+fNoBJets[1]+fNoBJets[2]).Mag()<<std::endl;
					       vh_LepBDiag50_Upper160_3Jet1B      [7]->Fill((fBJets[1]+fNoBJets[0]+fNoBJets[1]+fNoBJets[2]).Mag());
					     }
					   if((f_MassLep1Bb<f_SumptLep1Bb-50) && f_MassLep1Bb < 160)
					     {
					       vh_LepBDiag50_Upper160_3Jet1B      [7]->Fill((fBJets[0]+fNoBJets[0]+fNoBJets[1]+fNoBJets[2]).Mag());
					     }
					 
					
				     }
				   
				 }
			     } 
				   }		    
			 }
		     }
		     
		 }
	       }
	     }
	     
	   }
	   
	 }
       }
     }
     
    }
    
    
    //make some Generator level plots
    bool MCgen=true;

    if (MCgen){
      bool allhad=false;
      bool lep=false;
      bool semilep=false;
      if (fabs(pdgID[12])<5 && fabs(pdgID[13])<5 && fabs(pdgID[16])<5 && fabs(pdgID[17])<5) 
	{allhad=true;
	  countallhad++;
  }
      if( (fabs(pdgID[12])>=11 && fabs(pdgID[12])<=18) && (fabs(pdgID[13])>=11 && fabs(pdgID[13])<=18) && (fabs(pdgID[16])>=11 && fabs(pdgID[16])<=18) && (fabs(pdgID[17])>=11 && fabs(pdgID[17])<=18))
	{
	  lep=true;
	  countlep++;
  }
      if((fabs(pdgID[12])>=11 && fabs(pdgID[12])<=18) && (fabs(pdgID[13])>=11 && fabs(pdgID[13])<=18) &&fabs(pdgID[16])<5 &&fabs(pdgID[17])<5) 
	{semilep=true;
	  countsemilep++;
  }
      if((fabs(pdgID[16])>=11 && fabs(pdgID[16])<=18) && (fabs(pdgID[17])>=11 && fabs(pdgID[17])<=18) &&fabs(pdgID[12])<5 &&fabs(pdgID[13])<5)
	{
	  semilep=true;
	
	  countsemilep++;
  }

      //now only use the semileptonic events
      if(semilep){
	TLorentzVector MClep;
	TLorentzVector MCnu;
	TLorentzVector MC1b;
	TLorentzVector MC2b;
	TLorentzVector MCtb;
	TLorentzVector MCtbHad;
	TLorentzVector MCd;
	TLorentzVector MCrealWp;
	TLorentzVector MCrealt1;
	TLorentzVector MCrealt2;
	TLorentzVector MCMET;
	vector<TLorentzVector > Jets;
	vector<TLorentzVector > bjets;
	vector<TLorentzVector > Mets;
	vector<float > chi2;
	//find negative events
	int lepcharge;
	float bpt=0;
	float bcharge1=0;
	float bcharge2=0;
	for (int k=6; k<100; k++){
	  //find the lepton
	  if(fabs(pdgID[k])==11 || fabs(pdgID[k])==13 || fabs(pdgID[k])==15){
	    //leptons are defined with positive ID for negative charge 
	    if(pdgID[k] > 0 ) lepcharge=-1;
	    if (pdgID[k]<0) lepcharge=+1; 
	    MClep.SetPxPyPzE(MCpx[k],MCpy[k],MCpz[k],MCe[k]);
	  }
	  //find the neutrino
	  if(fabs(pdgID[k])==12 || fabs(pdgID[k])==14 || fabs(pdgID[k])==16)
	    {
	      MCnu.SetPxPyPzE(MCpx[k],MCpy[k],MCpz[k],MCe[k]);
	      MCMET.SetPxPyPzE(MCpx[k],MCpy[k],0,MCe[k]);

	    }
	    //find the hardest bjet (which might not be the right one but I don't have parent info)
	  if(fabs(pdgID[k])==5)
	    { 
	      TLorentzVector tempbjet;
	      tempbjet.SetPxPyPzE(MCpx[k],MCpy[k],MCpz[k],MCe[k]);
	      bjets.push_back(tempbjet);
	      if (bpt==0)
		{ MC1b.SetPxPyPzE(MCpx[k],MCpy[k],MCpz[k],MCe[k]);
		  if (pdgID[k]<0) bcharge1=-1;
		  if (pdgID[k]>0) bcharge1=+1;
		}
	      if (bpt!=0)
		{ MC2b.SetPxPyPzE(MCpx[k],MCpy[k],MCpz[k],MCe[k]);
		  if (pdgID[k]<0) bcharge2=-1;
		  if (pdgID[k]>0) bcharge2=+1;
		}
	      bpt=1;
	      
	    }
	  //Find all the jets in the event
	  if(fabs(pdgID[k])<=4 && fabs(pdgID[k])>=1)
	      {	
		//cout<<MCpz[k]<<endl;
		TLorentzVector tempJet;
		tempJet.SetPxPyPzE(MCpx[k],MCpy[k],MCpz[k],MCe[k]);
		Jets.push_back(tempJet);
	      }

	   

	}
	
	
	//the d-quark is always on position 8
	MCd.SetPxPyPzE(MCpx[8],MCpy[8],MCpz[8],MCe[8]);
	//double check the real wprime and two tops
	MCrealWp.SetPxPyPzE(MCpx[6],MCpy[6],MCpz[6],MCe[6]);
	MCrealt1.SetPxPyPzE(MCpx[7],MCpy[7],MCpz[7],MCe[7]);
	MCrealt2.SetPxPyPzE(MCpx[9],MCpy[9],MCpz[9],MCe[9]);

	h_MCPhiWpTop->Fill(min(fabs(MCrealWp.Phi()-MCrealt1.Phi()), 2*3.14159265 - fabs(MCrealWp.Phi()-MCrealt1.Phi())));
	//cout some stuff and see if it works
	//cout<<lepcharge<<endl;
	//cout<<entry<<" lep: "<<MClep.Px()<<" nu: "<<MCnu.Px()<<" 1b: "<<MC1b.Px()<<" "<<bcharge1<<" second b: "<<MC2b.Px()<<" "<<bcharge2<<endl;
	//associate the right b with the lepton
	if (lepcharge== bcharge1)
	  {MCtb=MC1b;
	    MCtbHad=MC2b;
	  }
	if (lepcharge==bcharge2)
	  { MCtb=MC2b;
	    MCtbHad=MC1b;
	  }
	//TOP RECO////////////
	/////////////////////////
	//find neutrino solution
	////////////////////////
	float nupz1; float nupz2; float Wmass=80.389; float nupz=0;
	float Disc=0;
	Disc=pow(Wmass,2) + pow(MClep.Pz(),2)+ pow((MClep.Px()+MCMET.Px()),2)+ pow((MClep.Py()+MCMET.Py()),2) -  pow((MClep.E()+MCMET.E()),2);
	//cout<<pow(MClep.Pz(),2)<<" "<<Disc<<endl;
	if (pow(MClep.Pz(),2)<= Disc){
	  nupz1=nupz2=-MClep.Pz();
	  TLorentzVector tempmet;
	  tempmet.SetPxPyPzE(MCMET.Px(),MCMET.Py(),nupz1,MCMET.E());
	  Mets.push_back(tempmet);
	  Mets.push_back(tempmet);
	}
	else{
	nupz1=-MClep.Pz()+sqrt(pow(MClep.Pz(),2)-Disc);
	nupz2=-MClep.Pz()-sqrt(pow(MClep.Pz(),2)-Disc);
	TLorentzVector tempmet;
	tempmet.SetPxPyPzE(MCMET.Px(),MCMET.Py(),nupz1,MCMET.E());
	Mets.push_back(tempmet);

	tempmet.SetPxPyPzE(MCMET.Px(),MCMET.Py(),nupz2,MCMET.E());
        Mets.push_back(tempmet);

	}
	//cout<<"Pz: "<<nupz1<<" "<<nupz2<<" "<<MCnu.Pz()<<endl;	
	//cout<<entry<<" "<<bjets.size()<<" "<<Mets.size()<<endl;
	//calculate top mass w
	TLorentzVector MCtopMET1((MCtb.Px()+MCMET.Px()+MClep.Px()),(MCtb.Py()+MCMET.Py()+MClep.Py())
				 ,(MCtb.Pz()+nupz1+MClep.Pz()),(MCtb.E()+MCMET.E()+MClep.E()));
	TLorentzVector MCtopMET2((MCtb.Px()+MCMET.Px()+MClep.Px()),(MCtb.Py()+MCMET.Py()+MClep.Py())
				 ,(MCtb.Pz()+nupz2+MClep.Pz()),(MCtb.E()+MCMET.E()+MClep.E()));
	//cout<<"Mtopreco: "<<MCtopMET1.M()<<" "<<MCtopMET2.M()<<endl;
	if (MCtopMET1.M()>0)nupz=nupz1;
	if (MCtopMET2.M()>0)nupz=nupz2;
	if(MCtopMET1.M() > 0 && MCtopMET2.M() >0){
	  if(fabs(nupz1-MClep.Pz()) < fabs(nupz2-MClep.Pz())) nupz=nupz1;
	  if(fabs(nupz1-MClep.Pz()) > fabs(nupz2-MClep.Pz())) nupz=nupz2;
	}
	//Reconstruct the top and Wprime from its decays products
	TLorentzVector MCtop;
	MCtop.SetPx(MCtb.Px()+MCnu.Px()+MClep.Px());
	MCtop.SetPy(MCtb.Py()+MCnu.Py()+MClep.Py());
	MCtop.SetPz(MCtb.Pz()+MCnu.Pz()+MClep.Pz());
	MCtop.SetE(MCtb.E()+MCnu.E()+MClep.E());
	//cout<<MCtop.M()<<" "<<MCrealt1.M()<<" "<<MCrealt2.M()<<endl;                                                                                        
	TLorentzVector MCwprime;
	MCwprime.SetPx(MCtop.Px()+MCd.Px());
	MCwprime.SetPy(MCtop.Py()+MCd.Py());
	MCwprime.SetPz(MCtop.Pz()+MCd.Pz());
	MCwprime.SetE(MCtop.E()+MCd.E());
	//cout<<MCwprime.M()<<" "<<MCrealWp.M()<<endl;  
	TLorentzVector MCtopMET((MCtb.Px()+MCMET.Px()+MClep.Px()),
				(MCtb.Py()+MCMET.Py()+MClep.Py()),(MCtb.Pz()+nupz+MClep.Pz()),(MCtb.E()+MCMET.E()+MClep.E()));
	TLorentzVector MCtopHad((MCtbHad.Px()+Jets[1].Px()+Jets[2].Px()),
				(MCtbHad.Py()+Jets[1].Py()+Jets[2].Py()),(MCtbHad.Pz()+Jets[1].Pz()+Jets[2].Pz()),(MCtbHad.E()+Jets[1].E()+Jets[2].E()));

	TLorentzVector MCwprimeMET((MCtopMET.Px()+MCd.Px()),(MCtopMET.Py()+MCd.Py()),(MCtopMET.Pz()+MCd.Pz()),(MCtopMET.E()+MCd.E()));
	cout<<MCtopMET.M()<<" "<<MCtopHad.M()<<" "<<MCwprimeMET.M()<<" "<<MCrealWp.M()<<endl;
			

	if (lepcharge==-1){
	  h_MCwprimeMassNeg->Fill(MCwprime.M());
	  h_MCwprimeMETMassNeg->Fill(MCwprimeMET.M());
	   h_MCPhidLepTopNeg->Fill(min(fabs(MCtopMET.Phi()-MCd.Phi()), 2*3.14159265 - fabs(MCtopMET.Phi()-MCd.Phi())));
	   //cout<<MCwprime.M()<<" "<<MCwprimeMET.M()<<endl;
	}
	if (lepcharge==+1){  
	  h_MCwprimeMassPos->Fill(MCwprime.M());
	  h_MCwprimeMETMassPos->Fill(MCwprimeMET.M());
	  h_MCPhidLepTopPos->Fill(min(fabs(MCtopMET.Phi()-MCd.Phi()), 2*3.14159265 - fabs(MCtopMET.Phi()-MCd.Phi())));
	}
	
	//CHI2 stuff
	//Now lets assume we don't know the b charge find the best match                                                                             
	//both leptonic tops with the neutrino solution
	//first define all the variabels


	//take only things that actually have b-jets
	if(bjets.size()==2){
	TLorentzVector LepTopMet0b0(bjets[0].Px()+Mets[0].Px()+MClep.Px()
				    ,bjets[0].Py()+Mets[0].Py()+MClep.Py(),bjets[0].Pz()+Mets[0].Pz()+MClep.Pz(),bjets[0].E()+Mets[0].E()+MClep.E());
	TLorentzVector LepTopMet0b1(bjets[1].Px()+Mets[0].Px()+MClep.Px()
                                    ,bjets[1].Py()+Mets[0].Py()+MClep.Py(),bjets[1].Pz()+Mets[0].Pz()+MClep.Pz(),bjets[1].E()+Mets[0].E()+MClep.E());
	TLorentzVector LepTopMet1b0(bjets[0].Px()+Mets[1].Px()+MClep.Px()
                                    ,bjets[0].Py()+Mets[1].Py()+MClep.Py(),bjets[0].Pz()+Mets[1].Pz()+MClep.Pz(),bjets[0].E()+Mets[1].E()+MClep.E());
	TLorentzVector LepTopMet1b1(bjets[1].Px()+Mets[1].Px()+MClep.Px()
                                    ,bjets[1].Py()+Mets[1].Py()+MClep.Py(),bjets[1].Pz()+Mets[1].Pz()+MClep.Pz(),bjets[1].E()+Mets[1].E()+MClep.E());

	TLorentzVector W01(Jets[0].Px()+Jets[1].Px(),Jets[0].Py()+Jets[1].Py(),Jets[0].Pz()+Jets[1].Pz(),Jets[0].E()+Jets[1].E());
	TLorentzVector HadTop01b0(W01.Px()+bjets[0].Px(),W01.Py()+bjets[0].Py(),W01.Pz()+bjets[0].Pz(),W01.E()+bjets[0].E());
	TLorentzVector HadTop01b1(W01.Px()+bjets[1].Px(),W01.Py()+bjets[1].Py(),W01.Pz()+bjets[1].Pz(),W01.E()+bjets[1].E());
	float dPhi2LepTopMet0b0 =(min(fabs(LepTopMet0b0.Phi()-Jets[2].Phi()), 2*3.14159265 - fabs(LepTopMet0b0.Phi()-Jets[2].Phi())));
	float dPhi2LepTopMet0b1 =(min(fabs(LepTopMet0b1.Phi()-Jets[2].Phi()), 2*3.14159265 - fabs(LepTopMet0b1.Phi()-Jets[2].Phi())));
	float dPhi2LepTopMet1b0 =(min(fabs(LepTopMet1b0.Phi()-Jets[2].Phi()), 2*3.14159265 - fabs(LepTopMet1b0.Phi()-Jets[2].Phi())));
	float dPhi2LepTopMet1b1 =(min(fabs(LepTopMet1b1.Phi()-Jets[2].Phi()), 2*3.14159265 - fabs(LepTopMet1b1.Phi()-Jets[2].Phi())));

	TLorentzVector W02(Jets[0].Px()+Jets[2].Px(),Jets[0].Py()+Jets[2].Py(),Jets[0].Pz()+Jets[2].Pz(),Jets[0].E()+Jets[2].E());
	TLorentzVector HadTop02b0(W02.Px()+bjets[0].Px(),W02.Py()+bjets[0].Py(),W02.Pz()+bjets[0].Pz(),W02.E()+bjets[0].E());
	TLorentzVector HadTop02b1(W02.Px()+bjets[1].Px(),W02.Py()+bjets[1].Py(),W02.Pz()+bjets[1].Pz(),W02.E()+bjets[1].E());
	float dPhi1LepTopMet0b0 =(min(fabs(LepTopMet0b0.Phi()-Jets[1].Phi()), 2*3.14159265 - fabs(LepTopMet0b0.Phi()-Jets[1].Phi())));
	float dPhi1LepTopMet0b1 =(min(fabs(LepTopMet0b1.Phi()-Jets[1].Phi()), 2*3.14159265 - fabs(LepTopMet0b1.Phi()-Jets[1].Phi())));
	float dPhi1LepTopMet1b0 =(min(fabs(LepTopMet1b0.Phi()-Jets[1].Phi()), 2*3.14159265 - fabs(LepTopMet1b0.Phi()-Jets[1].Phi())));
	float dPhi1LepTopMet1b1 =(min(fabs(LepTopMet1b1.Phi()-Jets[1].Phi()), 2*3.14159265 - fabs(LepTopMet1b1.Phi()-Jets[1].Phi())));

	TLorentzVector W12(Jets[1].Px()+Jets[2].Px(),Jets[1].Py()+Jets[2].Py(),Jets[1].Pz()+Jets[2].Pz(),Jets[1].E()+Jets[2].E());
	TLorentzVector HadTop12b0(W12.Px()+bjets[0].Px(),W12.Py()+bjets[0].Py(),W12.Pz()+bjets[0].Pz(),W12.E()+bjets[0].E());
	TLorentzVector HadTop12b1(W12.Px()+bjets[1].Px(),W12.Py()+bjets[1].Py(),W12.Pz()+bjets[1].Pz(),W12.E()+bjets[1].E());
	float dPhi0LepTopMet0b0 =(min(fabs(LepTopMet0b0.Phi()-Jets[0].Phi()), 2*3.14159265 - fabs(LepTopMet0b0.Phi()-Jets[0].Phi())));
	float dPhi0LepTopMet0b1 =(min(fabs(LepTopMet0b1.Phi()-Jets[0].Phi()), 2*3.14159265 - fabs(LepTopMet0b1.Phi()-Jets[0].Phi())));
	float dPhi0LepTopMet1b0 =(min(fabs(LepTopMet1b0.Phi()-Jets[0].Phi()), 2*3.14159265 - fabs(LepTopMet1b0.Phi()-Jets[0].Phi())));
	float dPhi0LepTopMet1b1 =(min(fabs(LepTopMet1b1.Phi()-Jets[0].Phi()), 2*3.14159265 - fabs(LepTopMet1b1.Phi()-Jets[0].Phi())));
	//	cout<<HadTop12b0.M()<<" "<<HadTop12b1.M()<<endl;
	//	cout<<dPhi0LepTopMet0b0<<" "<<dPhi0LepTopMet0b1<<" "<<dPhi0LepTopMet1b0<<" "<<dPhi0LepTopMet1b1<<endl;
	float mW=80.398; float mT=172.9; float wW=2; float wT=1.5; float Phi=3.14159; float wPhi=0.1;
	//cout<<pow((LepTopMet0b0.M()-mT)/wT,2)<<" "<<pow((W01.M()-mW)/wW,2)<<" "<<pow((HadTop01b1.M()-mT)/wT,2)<<" "<<pow((dPhi2LepTopMet0b0-Phi)/wPhi,2)<<endl;
	//cout<<(LepTopMet0b0.M()-mT)/wT<<" "<<(W01.M()-mW)/wW<<" "<<(HadTop01b1.M()-mT)/wT<<" "<<(dPhi2LepTopMet0b0-Phi)/wPhi<<endl;
	//

	//cout<<LepTopMet0b0.M()<<" "<<W01.M()<<" "<<HadTop01b1.M()<<" "<<dPhi2LepTopMet0b0<<endl;

	chi2.push_back(pow((LepTopMet0b0.M()-mT)/wT,2)+pow((W01.M()-mW)/wW,2)+pow((HadTop01b1.M()-mT)/wT,2)+pow((dPhi2LepTopMet0b0-Phi)/wPhi,2));
	chi2.push_back(pow((LepTopMet0b1.M()-mT)/wT,2)+pow((W01.M()-mW)/wW,2)+pow((HadTop01b0.M()-mT)/wT,2)+pow((dPhi2LepTopMet0b1-Phi)/wPhi,2));
	chi2.push_back(pow((LepTopMet1b0.M()-mT)/wT,2)+pow((W01.M()-mW)/wW,2)+pow((HadTop01b1.M()-mT)/wT,2)+pow((dPhi2LepTopMet1b0-Phi)/wPhi,2));
	chi2.push_back(pow((LepTopMet1b1.M()-mT)/wT,2)+pow((W01.M()-mW)/wW,2)+pow((HadTop01b0.M()-mT)/wT,2)+pow((dPhi2LepTopMet1b1-Phi)/wPhi,2));
	
	chi2.push_back(pow((LepTopMet0b0.M()-mT)/wT,2)+pow((W02.M()-mW)/wW,2)+pow((HadTop02b1.M()-mT)/wT,2)+pow((dPhi1LepTopMet0b0-Phi)/wPhi,2));
	chi2.push_back(pow((LepTopMet0b1.M()-mT)/wT,2)+pow((W02.M()-mW)/wW,2)+pow((HadTop02b0.M()-mT)/wT,2)+pow((dPhi1LepTopMet0b1-Phi)/wPhi,2));
	chi2.push_back(pow((LepTopMet1b0.M()-mT)/wT,2)+pow((W02.M()-mW)/wW,2)+pow((HadTop02b1.M()-mT)/wT,2)+pow((dPhi1LepTopMet1b0-Phi)/wPhi,2));
	chi2.push_back(pow((LepTopMet1b1.M()-mT)/wT,2)+pow((W02.M()-mW)/wW,2)+pow((HadTop02b0.M()-mT)/wT,2)+pow((dPhi1LepTopMet1b1-Phi)/wPhi,2));
	
	chi2.push_back(pow((LepTopMet0b0.M()-mT)/wT,2)+pow((W12.M()-mW)/wW,2)+pow((HadTop12b1.M()-mT)/wT,2)+pow((dPhi0LepTopMet0b0-Phi)/wPhi,2));
	chi2.push_back(pow((LepTopMet0b1.M()-mT)/wT,2)+pow((W12.M()-mW)/wW,2)+pow((HadTop12b0.M()-mT)/wT,2)+pow((dPhi0LepTopMet0b1-Phi)/wPhi,2));
	chi2.push_back(pow((LepTopMet1b0.M()-mT)/wT,2)+pow((W12.M()-mW)/wW,2)+pow((HadTop12b1.M()-mT)/wT,2)+pow((dPhi0LepTopMet1b0-Phi)/wPhi,2));
	chi2.push_back(pow((LepTopMet1b1.M()-mT)/wT,2)+pow((W12.M()-mW)/wW,2)+pow((HadTop12b0.M()-mT)/wT,2)+pow((dPhi0LepTopMet1b1-Phi)/wPhi,2));
cout<<"-------------------------------------"<<endl;

//cout<<pow((LepTopMet0b1.M()-mT)/wT,2)<<" "<<pow((W12.M()-mW)/wW,2)<<" "<<pow((HadTop12b0.M()-mT)/wT,2)<<" "<<pow((dPhi0LepTopMet0b1-Phi)/wPhi,2)<<endl;
	cout<<LepTopMet1b1.M()<<" "<<W12.M()<<" "<<HadTop12b0.M()<<" "<<dPhi0LepTopMet1b1<<endl;
	cout<<LepTopMet0b0.M()<<" "<<W12.M()<<" "<<HadTop12b1.M()<<" "<<dPhi0LepTopMet0b0<<endl;
	cout<<pow((LepTopMet0b0.M()-mT)/wT,2)<<" "<<pow((W12.M()-mW)/wW,2)<<" "<<pow((HadTop12b1.M()-mT)/wT,2)<<" "<<pow((dPhi0LepTopMet0b0-Phi)/wPhi,2)<<endl;
	//cout<<pow((LepTopMet0b1.M()-mT)/wT,2)+pow((W12.M()-mW)/wW,2)+pow((HadTop12b0.M()-mT)/wT,2)+pow((dPhi0LepTopMet0b1-Phi)/wPhi,2)<<endl;
	
	float minChi2=chi2[0];
	for(int m=0; m<chi2.size(); m++){
	  if (chi2[m]<=minChi2) minChi2=chi2[m];
	}
	cout<<entry<<" "<<minChi2<<endl;
	if (lepcharge==-1){
          	h_minChi2Neg->Fill(minChi2);

        }
        if (lepcharge==+1){
          	h_minChi2Pos->Fill(minChi2);

        }


	}
      }
     

      }
    
  }

  //lets see if the top branching ratios work
  cout<<"allhadronic: "<<countallhad<<" leptonic: "<<countlep<<" semilept: "<<countsemilep<<endl;
  float tot=countallhad+countlep+countsemilep;
  cout<<"BR: "<<(float) countallhad/tot<<" "<<(float) countlep/tot<<" "<<(float) countsemilep/tot<<endl;
  return;
}
