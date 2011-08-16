#include "TopBSM/RUTopXAna/interface/NtpTopXana.h"
#include "TLorentzVector.h"
#include "TFile.h"

#include <iostream>
#include <fstream>
#include <vector>

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
   h_NumEvtCut = new TH1F("NumEvtCut", "NumEvtCut",20,0,20);
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
   VarList.push_back("TransMassLepMET4Jet_vs_LeadingJetPt_");
   
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
     vh_TransMassLepMET4Jet_vs_LeadingJetPt.push_back(new TH2F((VarList[14]+CutList[f]).c_str(),(VarList[14]+CutList[f]).c_str(),200,0,2000,200,0,2000));
        
   }
   return;
}
 
void NtpTopXana::WriteHistograms()
{
  fOutFile->cd();
  h_NumEvtCut->Write();
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
    vh_TransMassLepMET4Jet_vs_LeadingJetPt[f]->Write();
  }
  return;
}
  

void NtpTopXana::Loop ()
{
  // Run over all entries and do what you like!

  for (int ientry = 0; GetEntry(ientry) > 0; ++ientry) {
    if (ientry % 1000 == 0) {
      printf("Processing entry: %i\n", ientry);
    }

    if (nElectrons == 2) {
      printf("2 Electrons Pt: %12.1f %12.1f\n", ept[0], ept[1]);
      TLorentzVector Lep0(epx[0],epy[0],epz[0],ee[0]);
      TLorentzVector Lep1(epx[1],epy[1],epz[1],ee[1]);
      std::cout<<(Lep0+Lep1).Mag()<<std::endl;

    }

    int nJet35=0; int nBJet35=0; int nNoBJet35=0; fBJets.clear(); fNoBJets.clear();fCleanJets.clear();
     for (int i=0; i<nJets; i++){
      TLorentzVector Jet(jetpx[i],jetpy[i],jetpz[i],jete[i]);
      if (jetpt[i]>35.0){
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
     //std::cout<<nJet35<<" "<<nNoBJet35<<std::endl; 
    h_NumEvtCut->Fill(0);
    if ((nElectrons+ nMuons) == 1){//asking for exactly one clean muon or electron > 20GeV
     h_NumEvtCut->Fill(1); //cout<<"1------------"<<endl;
     if (nElectrons==1 && ept[0]>45.0){//one electron with pt > 45 GeV
       h_NumEvtCut->Fill(2); // cout<<"2------------"<<endl;
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
		 
		 if(1==1/*fCleanJets[0].pt()>120*/){
		     if(nJet35 >=4){ //cout<<"8------------"<<endl;
		        TLorentzVector fLepton(epx[0],epy[0],epz[0],ee[0]);
			TLorentzVector fMET;
			fMET.SetPtEtaPhiE(pfMET,0,pfMETphi,pfMET);
		       if(2==2/*fabs(pfMETphi-fLepton.phi())<2.1*/)
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
			   
			  
			 /////////Positives charges//////////
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
				   if(nNoBJet35>=3){
				     vh_TransMassLepMET4JetB                [0]->Fill(v_TransMassLepMET4Jet1B.Mag());
				     vh_MassLep1Jet                         [0]->Fill((fLepton+fNoBJets[0]).Mag());
				   }
				   
				   
				 }
			       if(nBJet35>=2)
				 {
				   vh_TransMassLepMET4Jet                  [1]->Fill(v_TransMassLepMET4Jet.Mag());
				   vh_TransMassLepMET4Jet_vs_LeadingJetPt  [1]->Fill(fCleanJets[0].Pt(),v_TransMassLepMET4Jet.Mag());
				   vh_SumptSig4Highest                     [1]->Fill(SumptSig4Highest);
				   
				   
				   vh_DeltaPhiLepMET                       [1]->Fill(fabs(pfMETphi-fLepton.Phi()));
				   vh_LeadingJetPt                         [1]->Fill(fCleanJets[0].Pt());
				   
				   vh_MassLep1B                            [1]->Fill((fLepton+fBJets[0]).Mag());
				   vh_MassLep1B                            [1]->Fill((fLepton+fBJets[1]).Mag());
				   vh_MassLepB_vs_SumPt                    [1]->Fill(fLepton.Pt()+fBJets[0].Pt(),(fLepton+fBJets[0]).Mag());
				   vh_MassLepB_vs_SumPt                    [1]->Fill(fLepton.Pt()+fBJets[1].Pt(),(fLepton+fBJets[1]).Mag());
				   
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
				   vh_LeadingJetPt                         [2] ->Fill(fCleanJets[0].Pt());
				   if(nNoBJet35>=3){
				     vh_TransMassLepMET4JetB                [2]->Fill(v_TransMassLepMET4Jet1B.Mag());
				     vh_MassLep1Jet                         [2]->Fill((fLepton+fNoBJets[0]).Mag());
				   }
				   
				 }
			       if(nBJet35>=2)
				 {
				   vh_TransMassLepMET4Jet                 [3]->Fill(v_TransMassLepMET4Jet.Mag());
				   vh_TransMassLepMET4Jet_vs_LeadingJetPt [3]->Fill(fCleanJets[0].Pt(),v_TransMassLepMET4Jet.Mag());
				   vh_SumptSig4Highest                    [3]->Fill(SumptSig4Highest);
				   
				   
				   vh_DeltaPhiLepMET                      [3]->Fill(fabs(pfMETphi-fLepton.Phi()));
				   vh_LeadingJetPt                        [3]->Fill(fCleanJets[0].Pt());
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
			   
			   
			   
			   
			   
			   
			   if(nJet35 >=5)
			     {
			       //cout<<"9------------"<<endl;
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
				       vh_LeadingJetPt                        [4]->Fill(fCleanJets[0].Pt());
				       if(nNoBJet35>=4)
					 {
					   vh_TransMassLepMET4JetB              [4]->Fill(v_TransMassLepMET4Jet1B.Mag());
					   vh_TransMassLepMET5JetB              [4]->Fill(v_TransMassLepMET5Jet1B.Mag());
					   vh_MassLep1Jet                       [4]->Fill((fLepton+fNoBJets[0]).Mag());
					   if((f_MassLep1B<f_SumptLep1B-50) && f_MassLep1B < 160)
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
				       vh_LeadingJetPt                        [5]->Fill(fCleanJets[0].Pt());

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
					  
					   if((f_MassLep1Ba<f_SumptLep1Ba-50) && f_MassLep1Ba < 160)
					     {
					       vh_LepBDiag50_Upper160_3Jet1B      [5]->Fill((fBJets[1]+fNoBJets[0]+fNoBJets[1]+fNoBJets[2]).Mag());
					     }
					   if((f_MassLep1Bb<f_SumptLep1Bb-50) && f_MassLep1Bb < 160)
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
				       vh_LeadingJetPt                        [6]->Fill(fCleanJets[0].Pt());
				       if(nNoBJet35>=4)
					 {
					   vh_TransMassLepMET4JetB              [6]->Fill(v_TransMassLepMET4Jet1B.Mag());
					   vh_TransMassLepMET5JetB              [6]->Fill(v_TransMassLepMET5Jet1B.Mag());
					   vh_MassLep1Jet                       [6]->Fill((fLepton+fNoBJets[0]).Mag());
					   if((f_MassLep1B<f_SumptLep1B-50) && f_MassLep1B < 160)
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
				       vh_LeadingJetPt                        [7]->Fill(fCleanJets[0].Pt());

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
					  
					   if((f_MassLep1Ba<f_SumptLep1Ba-50) && f_MassLep1Ba < 160)
					     {std::cout<<(fBJets[1]+fNoBJets[0]+fNoBJets[1]+fNoBJets[2]).Mag()<<std::endl;
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
    
    
    
    
  }
  return;
}
