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
 
  //before cuts, just the ones that where already in the ntuple
  h_PossibleTrigger  = new TH1F("PossibleTrigger", "PossibleTrigger",30,0,30);

  h_mindRMuonJet = new TH1F("mindRMuonJet", "mindRMuonJet",100,0,5);
  h_mindRMuonJet_mPFIso = new TH2F("mindRMuonJet_mPFIso", "mindRMuonJet_mPFIso",200,0,10,100,0,5);
  h_ept= new TH1F("ept", "ept",200,0,1000);
  h_mpt= new TH1F("mpt", "mpt",200,0,1000);
  h_mPFIso= new TH1F("mPFIso", "mPFIso",200,0,10);
  //befor cuts
  h_MET = new TH1F("MET", "MET",200,0,1000);
  h_HT = new TH1F("HT", "HT",400,0,4000);
  h_nBJet35  = new TH1F("nBJet35", "nBJet35",20,0,20);
  h_nJet35  = new TH1F("nJet35", "nBJet35",20,0,20);
  h_Jet0= new TH1F("Jet0", "Jet0",200,0,1000);
  h_Jet1= new TH1F("Jet1", "Jet1",200,0,1000);
  h_Jet2= new TH1F("Jet2", "Jet2",200,0,1000);
  h_Jet3= new TH1F("Jet3", "Jet3",200,0,1000);
  h_Jet4= new TH1F("Jet4", "Jet4",200,0,1000);
  h_Jet5= new TH1F("Jet5", "Jet5",200,0,1000);
  h_Jet6= new TH1F("Jet6", "Jet6",200,0,1000);
  //after cuts
  h_MET_EvtSel = new TH1F("MET_EvtSel", "MET_EvtSel",200,0,1000);
  h_HT_EvtSel = new TH1F("HT_EvtSel", "HT_EvtSel",400,0,4000);
  h_nBJet35_EvtSel  = new TH1F("nBJet35_EvtSel", "nBJet35_EvtSel",20,0,20);
  h_nJet35_EvtSel  = new TH1F("nJet35_EvtSel", "nBJet35_EvtSel",20,0,20);
  h_Jet0_EvtSel= new TH1F("Jet0_EvtSel", "Jet0_EvtSel",200,0,1000);
  h_Jet1_EvtSel= new TH1F("Jet1_EvtSel", "Jet1_EvtSel",200,0,1000);
  h_Jet2_EvtSel= new TH1F("Jet2_EvtSel", "Jet2_EvtSel",200,0,1000);
  h_Jet3_EvtSel= new TH1F("Jet3_EvtSel", "Jet3_EvtSel",200,0,1000);
  h_Jet4_EvtSel= new TH1F("Jet4_EvtSel", "Jet4_EvtSel",200,0,1000);
  h_Jet5_EvtSel= new TH1F("Jet5_EvtSel", "Jet5_EvtSel",200,0,1000);
  h_Jet6_EvtSel= new TH1F("Jet6_EvtSel", "Jet6_EvtSel",200,0,1000);


  cout<<"before histos"<<endl;
  for(int b=0; b<5; b++){
  for (int i=0; i<7; i++){
    int iPt=30+i*10;
    Mjjj_sumpt_bjet_pt_njet.push_back(std::vector<std::vector<TH2F*> >());
    Mjjj_bjet_pt_njet_diag.push_back(std::vector<std::vector<std::vector<TH1F*> > >());
    for(int k=0; k<3; k++){
      int iNjet=k+6;

      Mjjj_sumpt_bjet_pt_njet[b].push_back(std::vector<TH2F*> ());
      sprintf(hNAME, "Mjjj_sumpt_bjet%i_pt%i_GE%ijet", b, iPt,iNjet);
      Mjjj_sumpt_bjet_pt_njet[b][i].push_back(new TH2F(hNAME,hNAME,200,0,2000,200,0,2000));
      Mjjj_bjet_pt_njet_diag[b].push_back(std::vector<std::vector<TH1F*> > ());

      for(int j=0; j<20; j++){
	
	int iDiag=j*10+40;
	
	Mjjj_bjet_pt_njet_diag[b][i].push_back(std::vector<TH1F*> ());
	sprintf(hNAME, "Mjjj_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);
	Mjjj_bjet_pt_njet_diag[b][i][k].push_back(new TH1F(hNAME,hNAME,200,0,2000));
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
   h_nBJet35->Write();
   h_nJet35->Write();
   h_HT->Write();
   h_Jet0->Write();
   h_Jet1->Write();
   h_Jet2->Write();
   h_Jet4->Write();
   h_Jet5->Write();
   h_Jet6->Write();


   TDirectory* triplets=fOutFile->mkdir("Triplets");
   fOutFile->cd("Triplets");
   h_MET_EvtSel->Write();
   h_nBJet35_EvtSel->Write();
   h_nJet35_EvtSel->Write();
   h_HT_EvtSel->Write();
   h_Jet0_EvtSel->Write();
   h_Jet1_EvtSel->Write();
   h_Jet2_EvtSel->Write();
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
	     //cout<<"Mjjj_pt"<<i*10+20<<"_njet"<<k+3<<"_diag"<<j*10+40<<"  "<<Mjjj_pt_njet_diag[i][k][j]->GetEntries()<<endl;
	     Mjjj_bjet_pt_njet_diag[b][i][k][j]->Write();  
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

      if (jet_PF_pt[i]>25.0 && fabs(jet_PF_eta[i])<2.5){
	nJet25=i+1;
	if(jet_PF_pt[i]>45.0){
	SumptAllJet=SumptAllJet+jet_PF_pt[i];
	fCleanJets.push_back(Jet);
	nJet35=i+1;
	if (bdiscCSV_PF[i] > 0.679)
	  {
	    nBJet35++;
	    fBJets.push_back(Jet);
	    fdummyCleanJets.push_back(dummyJet);
	  }
	if (bdiscCSV_PF[i] <= 0.679)
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
       if(fCleanJets[0].Pt() > 85 && fCleanJets[1].Pt() > 80 && fCleanJets[2].Pt() > 65 && fCleanJets[3].Pt() > 65 && fCleanJets[4].Pt() > 25 &&
	  fCleanJets[5].Pt() > 25){
	 h_PossibleTrigger->Fill(3);
       if(nBJet35 >= 1) h_PossibleTrigger->Fill(7);
       if(nBJet35 >= 2) h_PossibleTrigger->Fill(11);
       if(nBJet35 >= 3) h_PossibleTrigger->Fill(15);
       if(nBJet35 >= 4) h_PossibleTrigger->Fill(19);
       }
       }
     ////TRIGGER////////////
     //  if ( nJet35>=6 && nMuons>=1){
     //     if ( nJet35>=6 && SumptAllJet>800){
	   h_nBJet35->Fill(nBJet35);
	   h_nJet35->Fill(nJet35);
	   h_MET->Fill(pfMET);
	   h_HT->Fill(SumptAllJet);
	   h_Jet0->Fill(fCleanJets[0].Pt());
	   h_Jet1->Fill(fCleanJets[1].Pt());
	   h_Jet2->Fill(fCleanJets[2].Pt());
	   if(nJet35>=3) h_Jet3->Fill(fCleanJets[3].Pt());
	   if(nJet35>=4) h_Jet4->Fill(fCleanJets[4].Pt());
	   if(nJet35>=5) h_Jet5->Fill(fCleanJets[5].Pt());
	   if(nJet35>=6) h_Jet6->Fill(fCleanJets[6].Pt());


     if ( nJet35>=6){
       //if(fCleanJets[0].Pt() > 85 && fCleanJets[1].Pt() > 80 && fCleanJets[2].Pt() > 65 && fCleanJets[3].Pt() > 65 && fCleanJets[4].Pt() > 25 && fCleanJets[5].Pt() > 25){
       if(SumptAllJet>900){
	 if(1==1){//nBJet35 >= 3){

	   h_nBJet35_EvtSel->Fill(nBJet35);
	   h_nJet35_EvtSel->Fill(nJet35);
	   h_MET_EvtSel->Fill(pfMET);
	   h_HT_EvtSel->Fill(SumptAllJet);
	   h_Jet0_EvtSel->Fill(fCleanJets[0].Pt());
	   h_Jet1_EvtSel->Fill(fCleanJets[1].Pt());
	   h_Jet2_EvtSel->Fill(fCleanJets[2].Pt());
	   if(nJet35>=3) h_Jet3_EvtSel->Fill(fCleanJets[3].Pt());
	   if(nJet35>=4) h_Jet4_EvtSel->Fill(fCleanJets[4].Pt());
	   if(nJet35>=5) h_Jet5_EvtSel->Fill(fCleanJets[5].Pt());
	   if(nJet35>=6) h_Jet6_EvtSel->Fill(fCleanJets[6].Pt());
	   //all the jets make triplets
	   //	   int numJetForTriplet=fCleanJets.size();
	   //only the six leading jets make triplets
       unsigned int numJetForTriplet=6;
       int nTriplets=0;
       for (unsigned int i=0+0; i<numJetForTriplet-2; ++i) {
	 for (unsigned int j=i+1; j<numJetForTriplet-1; ++j) {
	   for (unsigned int k=j+1; k<numJetForTriplet-0; ++k) {
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
	 for(int b=0; b<5; b++){

	 for (int i=0; i<7; i++)
	   {
	     float iPt=30.0+i*10.0;
	     for(int k=0; k<3; k++)
	       { 
		 unsigned int iNjet=k+6;
		 //count njets with the pt cut -> gonna be slow
		 if(iNjet<=fCleanJets.size()){
		  
		   if(Triplet[q][2].Pt()>iPt && fCleanJets[iNjet-1].Pt()>iPt && nBJet35>=b)
		     {	
		        Mjjj_sumpt_bjet_pt_njet[b][i][k]->Fill(sumScalarPtTriplet[q],massTriplet[q]);
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
		     if(Triplet[q][2].Pt()>iPt && fCleanJets[njetsMin-1].Pt()>iPt && fCleanJets[iNjet-1].Pt()>iPt && nBJet35>=b)
		       {
			 //cout<<"after selection"<<endl;
			 //cout<<Triplet[q][2].pt()<<" "<<fCleanJets.size()<<" "<<fCleanJets[iNjet-1].pt()<<endl;
			 if(massTriplet[q]<(sumScalarPtTriplet[q]-iDiag))
			   {
			     float countT=0;
			     Mjjj_bjet_pt_njet_diag[b][i][k][j]->Fill(massTriplet[q]);
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
	 }//bjet loop
	   }//triplet loop
	 }//3 or more b jets
	 }//jetp
     }//minjet
     //lets see if the top branching ratios work
  }
  return;
}
