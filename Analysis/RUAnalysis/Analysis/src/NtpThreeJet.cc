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
 
  h_NumEvtCutMuon = new TH1F("NumEvtCutMuon", "NumEvtCutMuon",20,0,20);
  h_NumEvtCutElectron = new TH1F("NumEvtCutElectron", "NumEvtCutElectron",20,0,20);
  h_NumEvtCut = new TH1F("NumEvtCut", "NumEvtCut",20,0,20);
  h_PossibleTrigger  = new TH1F("PossibleTrigger", "PossibleTrigger",20,0,20);
  h_MET = new TH1F("MET", "MET",200,0,1000);
  h_HT = new TH1F("HT", "HT",200,0,1000);
  h_mindRMuonJet = new TH1F("mindRMuonJet", "mindRMuonJet",100,0,5);
  h_mindRMuonJet_mPFIso = new TH2F("mindRMuonJet_mPFIso", "mindRMuonJet_mPFIso",200,0,10,100,0,5);
  h_ept= new TH1F("ept", "ept",200,0,1000);
  h_mpt= new TH1F("mpt", "mpt",200,0,1000);
  h_mPFIso= new TH1F("mPFIso", "mPFIso",200,0,10);
  
  h_Jet0= new TH1F("Jet0", "Jet0",200,0,1000);
  h_Jet1= new TH1F("Jet1", "Jet1",200,0,1000);
  h_Jet2= new TH1F("Jet2", "Jet2",200,0,1000);
  h_Jet4= new TH1F("Jet3", "Jet3",200,0,1000);
  h_Jet5= new TH1F("Jet4", "Jet4",200,0,1000);
  for (int i=0; i<7; i++){
    int iPt=20+i*10;

    for(int k=0; k<4; k++){
      int iNjet=k+3;

      Mjjj_sumpt_pt_njet.push_back(std::vector<TH2F*> ());
      sprintf(hNAME, "Mjjj_sumpt_pt%i_GE%ijet", iPt,iNjet);
      Mjjj_sumpt_pt_njet[i].push_back(new TH2F(hNAME,hNAME,100,0,1000,100,0,1000));
      Mjjj_pt_njet_diag.push_back(std::vector<std::vector<TH1F*> > ());

      for(int j=0; j<20; j++){
	
	int iDiag=j*10+40;
	
	Mjjj_pt_njet_diag[i].push_back(std::vector<TH1F*> ());
	sprintf(hNAME, "Mjjj_pt%i_diag%i_GE%ijet", iPt,iDiag,iNjet);
	Mjjj_pt_njet_diag[i][k].push_back(new TH1F(hNAME,hNAME,100,0,1000));
      }
    }
  }


 return;
}
 
void NtpThreeJet::WriteHistograms()
{cout<<"made it here"<<endl;
  char FOLDER[100];
  fOutFile->cd();

   fOutFile->mkdir("Events");
   fOutFile->cd("Events");

   h_NumEvtCutMuon->Write();
   h_NumEvtCutElectron->Write();
   h_NumEvtCut->Write();
   h_PossibleTrigger->Write();
   h_MET->Write();
   h_HT->Write();

   h_ept->Write();
   h_mpt->Write();
   h_mPFIso->Write();
   h_mindRMuonJet->Write();
   h_mindRMuonJet_mPFIso->Write();
   h_Jet0->Write();
   h_Jet1->Write();
   h_Jet2->Write();
   h_Jet4->Write();
   h_Jet5->Write();
   TDirectory* now=fOutFile->mkdir("Triplets");
   fOutFile->cd("Triplets");

   for (int i=0; i<7; i++){
     sprintf(FOLDER, "jetpt_%i", i*10+20);
     now->mkdir(FOLDER);
     now->cd(FOLDER);
     for (int k=0; k<4; k++){
       Mjjj_sumpt_pt_njet[i][k]->Write();
       for(int j=0; j<20; j++){ 
	 //cout<<"Mjjj_pt"<<i*10+20<<"_njet"<<k+3<<"_diag"<<j*10+40<<"  "<<Mjjj_pt_njet_diag[i][k][j]->GetEntries()<<endl;
	 Mjjj_pt_njet_diag[i][k][j]->Write();  
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
  ////////////////////////////////////////////////////////////

  // Run over all entries and do what you like!
  int countallhad=0;
  int countlep=0;
  int countsemilep=0;

  for (int ientry = 0; GetEntry(ientry) > 0; ++ientry) {
    
  ///////////////////Clear out variables/////////////////////
  Triplet.clear();  
  sumScalarPtTriplet.clear();
  sumVectorPtTriplet.clear();
  massTriplet.clear();
  
  ////////////////////////////////////////////////////////////
    

    if (ientry % 100 == 0) {
      printf("Processing entry: %i\n", ientry);
    }

    //JETS///////
    //Count all the jets above 35 Gev, also calculated HT=SumptAllJet, count number of b-jets
    int nJet25=0; int nJet35=0; int nBJet35=0; int nNoBJet35=0; fBJets.clear(); fNoBJets.clear();fCleanJets.clear();
    float SumptAllJet=0;
    vector<TLorentzVector > fdummyCleanJets;
     for (int i=0; i<nPFJets; i++){
      TLorentzVector Jet(jet_PF_px[i],jet_PF_py[i],jet_PF_pz[i],jet_PF_e[i]);
      TLorentzVector dummyJet(0,0,0,0);

      if (jet_PF_pt[i]>25.0){
	nJet25=i+1;
	if(jet_PF_pt[i]>35.0){
	SumptAllJet=SumptAllJet+jet_PF_pt[i];
	fCleanJets.push_back(Jet);
	nJet35=i+1;
	if (bdiscSSVHE_PF[i] > 1.74)
	  {
	    nBJet35++;
	    fBJets.push_back(Jet);
	    fdummyCleanJets.push_back(dummyJet);
	  }
	if (bdiscSSVHE_PF[i] <= 1.74)
	  {
	    nNoBJet35++;
	    fNoBJets.push_back(Jet);
	    fdummyCleanJets.push_back(Jet);

	  }
	}
      }
    }
     //MUON/////
     //make some plots for the muons
    vector<TLorentzVector > fdummyCleanMuons;
     for (int i=0; i<nMuons; i++){
       TLorentzVector Muon(mpx[i],mpy[i],mpz[i],me[i]);
       //lets look at the leading muon for now
       if(i==0){
       h_mPFIso->Fill(mPFIso[i]);
       h_mpt->Fill(Muon.Pt());
       //calcualte the minimum dR to one of the jets
       float mindRMuonJet=9999;
       for (int j=0; j<nJet35; j++){
	 TLorentzVector Jet(fCleanJets[j].Px(),fCleanJets[j].Py(),fCleanJets[j].Pz(),fCleanJets[j].E());
	 float dRMuonJet=Jet.DeltaR(Muon);
	 if (dRMuonJet < mindRMuonJet) mindRMuonJet=dRMuonJet;
	 //	 cout<<"All: "<<dRMuonJet<<endl;

       }
       //cout<<mindRMuonJet<<endl;
       h_mindRMuonJet->Fill(mindRMuonJet);

       h_mindRMuonJet_mPFIso->Fill(mPFIso[i],mindRMuonJet);
       }
     }

     //Possible Triggers selections

     if (nJet35>=6 && nMuons>=1) h_PossibleTrigger->Fill(1);
     if (nJet35>=6 && SumptAllJet>800) h_PossibleTrigger->Fill(2);
     if (nJet25>=6)
     if(fCleanJets[0].Pt() > 85 && fCleanJets[1].Pt() > 80 && fCleanJets[2].Pt() > 65 && fCleanJets[3].Pt() > 65 && fCleanJets[4].Pt() > 25 &&
	fCleanJets[5].Pt() > 25) h_PossibleTrigger->Fill(3);

     ////TRIGGER////////////
     //  if ( nJet35>=6 && nMuons>=1){
     //     if ( nJet35>=6 && SumptAllJet>800){

     if ( nJet25>=6){
       if(fCleanJets[0].Pt() > 85 && fCleanJets[1].Pt() > 80 && fCleanJets[2].Pt() > 65 && fCleanJets[3].Pt() > 65 && fCleanJets[4].Pt() > 25 &&
	  fCleanJets[5].Pt() > 25){
       h_MET->Fill(pfMET);
       h_Jet0->Fill(fCleanJets[0].Pt());
       h_Jet1->Fill(fCleanJets[1].Pt());
       h_Jet2->Fill(fCleanJets[2].Pt());
       h_HT->Fill(SumptAllJet);

       int nTriplets=0;
       for (unsigned int i=0+0; i<fCleanJets.size()-2; ++i) {
	 for (unsigned int j=i+1; j<fCleanJets.size()-1; ++j) {
	   for (unsigned int k=j+1; k<fCleanJets.size()-0; ++k) {
	     Triplet.push_back(std::vector<TLorentzVector > ());
	     
	     TLorentzVector Jet1; TLorentzVector Jet2; TLorentzVector Jet3;
	     Jet1=fCleanJets[i]; Jet2=fCleanJets[j]; Jet3=fCleanJets[k];
	     TLorentzVector Triplet123; Triplet123=Jet1+Jet2+Jet3;
	     TLorentzVector Doublet12; Doublet12=Jet1+Jet2;
	     TLorentzVector Doublet13; Doublet13=Jet1+Jet3;
	     TLorentzVector Doublet23; Doublet23=Jet2+Jet3;
	     
	     sumScalarPtTriplet.push_back(Jet1.Pt()+Jet2.Pt()+Jet3.Pt());
	     massTriplet.push_back(Triplet123.M());
	     sumVectorPtTriplet.push_back(Triplet123.Pt());

	     Triplet[nTriplets].push_back(Jet1);
	     Triplet[nTriplets].push_back(Jet2);
	     Triplet[nTriplets].push_back(Jet3);

	     nTriplets++;	     
	   }
	 }
       }
     

     for(unsigned int q=0; q<massTriplet.size(); q++)
       {
	 for (int i=0; i<7; i++)
	   {
	     float iPt=20.0+i*10.0;
	     for(int k=0; k<4; k++)
	       { 
		 unsigned int iNjet=k+3;
		 //count njets with the pt cut -> gonna be slow
		 if(iNjet<=fCleanJets.size()){
		  
		   if(Triplet[q][2].Pt()>iPt && fCleanJets[iNjet-1].Pt()>iPt)
		     {	
		        Mjjj_sumpt_pt_njet[i][k]->Fill(sumScalarPtTriplet[q],massTriplet[q]);
		     }
		   for(int j=0; j<20; j++){
		        
		     float iDiag=j*10.0+40.0;
		     //to implement the pt cut we only keep triplets where the lowest jet passes pt cut
		     //also we check if the njetsMin cut satisfies this pt cut
		     //std::cout<<"before selection"<<endl;
		     // std::cout<<Triplet[q][2].pt()<<" "<<fCleanJets.size()<<" "<<fCleanJets[iNjet-1].pt()<<endl;
		     //if(iNjet>fCleanJets.size()){
		     // cout<<Triplet[q][2].pt()<<endl;
		     // cout<<fCleanJets.size()<<endl;
		     // cout<<iNjet-1<<endl;
		     //}
		     if(Triplet[q][2].Pt()>iPt && fCleanJets[njetsMin-1].Pt()>iPt && fCleanJets[iNjet-1].Pt()>iPt)
		       {
			 //cout<<"after selection"<<endl;
			 //cout<<Triplet[q][2].pt()<<" "<<fCleanJets.size()<<" "<<fCleanJets[iNjet-1].pt()<<endl;
			 if(massTriplet[q]<(sumScalarPtTriplet[q]-iDiag))
			   {
			     float countT=0;
			     Mjjj_pt_njet_diag[i][k][j]->Fill(massTriplet[q]);
			     //if(countT==0 && massTriplet[q]>160 && massTriplet[q]<190){
			    
			     countT++;
			          
			    
			     //}
			     //cout<<"!!!!!!!!!!!!!KEEP!!!!!!!!!!"<<endl;
			   }
		       }
		   }
		 }//diag cut loop
	       }//njetloop
	   }//pt loop
       }//triplet loop
       }//jetp
     }//minjet
     //lets see if the top branching ratios work
  }
  return;
}
