 // -*- C++ -*-
//
// Package:    TopXana
// Class:      TopXana
// 
/**\class TopXana TopXana.cc TopBSM/TopXana/src/TopXana.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Claudia Seitz
//         Created:  Fri Jun 17 12:26:54 EDT 2011
// $Id: TopXana.cc,v 1.4 2011/07/29 14:19:53 clseitz Exp $
//
//


// system include files
#include <memory>


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/PatCandidates/interface/Jet.h" // based on DataFormats/Candidate/interface/Particle.h
#include "DataFormats/PatCandidates/interface/JetCorrFactors.h"
#include "TTree.h"
#include "TopBSM/TopXana/interface/TopXana.h"

#include "DataFormats/PatCandidates/interface/Electron.h" 
#include "DataFormats/PatCandidates/interface/Muon.h" 
#include "DataFormats/PatCandidates/interface/MET.h" 
#include "DataFormats/PatCandidates/interface/Photon.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "TopBSM/TopXana/interface/EgammaTowerIsolation.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;


//
// class declaration


TopXana::TopXana(const edm::ParameterSet& iConfig)

{
  _sumPtMin        = iConfig.getUntrackedParameter<double>("sumPtMin",         300.0);
  _debug           = iConfig.getUntrackedParameter<bool>  ("debug",            false);
  _outputFilename  = iConfig.getUntrackedParameter<string>("outputFilename",  "PatJets_test.root");
  _outputFilename2 = iConfig.getUntrackedParameter<string>("outputFilename2", "PatJets_testTree.root");
  _patJetType      = iConfig.getUntrackedParameter<string>("PatJetType",      "selectedPatJets");
  _njetsMin        = iConfig.getUntrackedParameter<int>   ("NjetsMin",         4);
  _njetsMax        = iConfig.getUntrackedParameter<int>   ("NjetsMax",         4);
  _etacut          = iConfig.getUntrackedParameter<double>("etacut",           3.0); 
  _jetptcut        = iConfig.getUntrackedParameter<double>("jetptcut",         20.0);

  _eeta            = iConfig.getUntrackedParameter<double>("eeta",           2.1); 
  _ept             = iConfig.getUntrackedParameter<double>("ept",         20.0);
  
  _meta            = iConfig.getUntrackedParameter<double>("meta",           2.1); 
  _mpt             = iConfig.getUntrackedParameter<double>("mpt",         20.0);
  
  _pheta           = iConfig.getUntrackedParameter<double>("pheta",           1.45); 
  _phpt            = iConfig.getUntrackedParameter<double>("phpt",         30.0);
  
  _nbTagsMin       = iConfig.getUntrackedParameter<int>   ("nbTagsMin",        0);
  _nbTagsMax       = iConfig.getUntrackedParameter<int>   ("nbTagsMax",        1000);
  _isData          = iConfig.getUntrackedParameter<bool>  ("isData",           true);
  _noTripletBtag   = iConfig.getUntrackedParameter<bool>  ("noTripletBtag",    false);
  _nTripletBtagsMin= iConfig.getUntrackedParameter<int>   ("nTripletBtagsMin", 0);
  _nTripletBtagsMax= iConfig.getUntrackedParameter<int>   ("nTripletBtagsMax", 1000);
  _doBtagEff       = iConfig.getUntrackedParameter<bool>   ("doBtagEff", true);

  fTriggerNames = iConfig.getUntrackedParameter<std::vector<std::string> >("TriggerNames", std::vector<std::string>());
  for (std::vector<std::string>::iterator It = fTriggerNames.begin(); It != fTriggerNames.end(); ++It) {
    fTriggerMap[*It] = false;
  }


  JSONFilename  = iConfig.getUntrackedParameter<string>("JSONFilename","Cert_160404-166502_7TeV_PromptReco_Collisions11_JSON.txt");
   //now do what ever initialization is needed

}


TopXana::~TopXana()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TopXana::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
 /////////////////
   //GET EVT INFO
   ////////////////
   run   = iEvent.id().run();
   event = iEvent.id().event();
   lumis = iEvent.id().luminosityBlock();
  ////////////////////////
  ////CHECK JSON
  //////////////////////

  GoodRun=kFALSE;
  UseJson(GoodRuns,GoodLumiStart,GoodLumiEnd,nGoodRuns,run,lumis);

  //onlye keep events when they are in the good run list
  //std::cout<<"--------------run: "<<run<<"--event: "<<event<<"--lumi: "<<lumis<<"--entry: "<<entry<<"-----------"<<endl;
  
 
  if(GoodRun){

   //////////////////////
   ///// check triggers
   ///////////////// 
 // Look for one of the triggers we care about

   bool HasTrigger = false;
    if (_isData) {
      getTriggerDecision(iEvent, fTriggerMap);
      for (std::map<std::string, bool>::iterator It = fTriggerMap.begin(); It != fTriggerMap.end(); ++It) {
	if (It->second) {
	  HasTrigger = true;
	  break;
	}
      }
    }
    else {
      HasTrigger= true;
    }
   
   ///////////////////
   ////CLEAN UP VARIABLES   //////////////////
    if (HasTrigger){
  fGoodJets.clear(); fCleanJets.clear(); 
  nGoodJets=0; nCleanJets=0;
  fGoodElectrons.clear(); fCleanElectrons.clear();
  nGoodElectrons=0; nCleanElectrons=0; 
  fGoodMuons.clear(); fCleanMuons.clear(); 
  nGoodMuons=0; nCleanMuons=0;  
  fGoodPhotons.clear(); fCleanPhotons.clear();
  nGoodPhotons=0; nCleanPhotons=0;
  for (int i=0; i<200; ++i)
    {
      pdgID[i] = -99;
      MCpx[i] = -99;
      MCpy[i] = -99;
      MCpz[i] = -99;
      MCe[i] = -99;
    }
 
   Triplet.clear();   
   sumScalarPtTriplet.clear();
   sumVectorPtTriplet.clear();
   massTriplet.clear();
   nTriplets=0; q=0; //basically just triplet counting
   IsVtxGood = 0; nGoodVtx = 0;

  
  
   ///////////////////
   /////DO OBJECT ID
   //////////////////
   //Select all the objects int the event (vertex function makes some plots)
   DoJetID(iEvent);
   DoVertexID(iEvent);
   DoElectronID(iEvent);
   DoMuonID(iEvent);
   //DoPhotonID(iEvent);
   DoMETID(iEvent);

   //make some plots before cleanup 
   h_nGoodJets->Fill(nGoodJets);
   h_nGoodElectrons->Fill(nGoodElectrons);  
   h_nGoodMuons->Fill(nGoodMuons);
   h_nGoodPhotons->Fill(nGoodPhotons);

   //////////////////
   ///////REMOVE OVERLAP IN OCJECT COLLECTION
   ////////////////
   //lets clean our object collections
   DoCleanUp(fGoodMuons,fGoodElectrons,fGoodPhotons,fGoodJets);

   //make plots after the clean up
   h_nCleanElectrons->Fill(nCleanElectrons);
   h_nCleanMuons->Fill(nCleanMuons);
   h_nCleanPhotons->Fill(nCleanPhotons);
   h_nCleanJets->Fill(nCleanJets);

   /////////////////
   //////KINEMATIC PLOTS OF OBJECTS + STUFF FOR THE TREE
   ////////////////
   //make some kinematic plots and write out variables for the tree
   nJets=nCleanJets;
   for(int i=0; i<nCleanJets; i++){
     if(i<6){
       v_jet_pt[i]->Fill(fCleanJets[i].pt()); 
       v_jet_eta[i]->Fill(fCleanJets[i].eta()); 
       v_jet_phi[i]->Fill(fCleanJets[i].phi()); 
       v_jet_m[i]->Fill(fCleanJets[i].mass()); 
     }
     jetpt[i]=fCleanJets[i].pt();
     jetpx[i]=fCleanJets[i].px();
     jetpy[i]=fCleanJets[i].py();
     jetpz[i]=fCleanJets[i].pz();
     jete[i]=fCleanJets[i].energy();	 
     
     
   }
   nElectrons=nCleanElectrons;
   for(int i=0; i<nCleanElectrons; i++){
     if(i<6){
       v_e_pt[i]->Fill(fCleanElectrons[i].pt()); 
       v_e_eta[i]->Fill(fCleanElectrons[i].eta()); 
       v_e_phi[i]->Fill(fCleanElectrons[i].phi()); 
     }
     ept[i]=fCleanElectrons[i].pt();
     epx[i]=fCleanElectrons[i].px();
     epy[i]=fCleanElectrons[i].py();
     epz[i]=fCleanElectrons[i].pz();
     ee[i]=fCleanElectrons[i].energy();	 
     
     
   }
   nMuons=nCleanMuons;
   for(int i=0; i<nCleanMuons; i++){
     if(i<6){
       v_m_pt[i]->Fill(fCleanMuons[i].pt()); 
       v_m_eta[i]->Fill(fCleanMuons[i].eta()); 
       v_m_phi[i]->Fill(fCleanMuons[i].phi()); 
     }
     mpt[i]=fCleanMuons[i].pt();
     mpx[i]=fCleanMuons[i].px();
     mpy[i]=fCleanMuons[i].py();
     mpz[i]=fCleanMuons[i].pz();
     me[i]=fCleanMuons[i].energy();	 
     
     
   }
   nPhotons=nCleanPhotons;
   for(int i=0; i<nCleanPhotons; i++){
     if(i<6){
       v_ph_pt[i]->Fill(fCleanPhotons[i].pt()); 
       v_ph_eta[i]->Fill(fCleanPhotons[i].eta()); 
       v_ph_phi[i]->Fill(fCleanPhotons[i].phi()); 
     }
     phpt[i]=fCleanPhotons[i].pt();
     phpx[i]=fCleanPhotons[i].px();
     phpy[i]=fCleanPhotons[i].py();
     phpz[i]=fCleanPhotons[i].pz();
     phe[i]=fCleanPhotons[i].energy();	 
     
   }
   h_MET->Fill(fMET.et());
   ///////////////////////////
   ////////EVENT SELECTION FOR PLOTS -> TREE HAS EVERYTHING
   /////////////////////////
   //DI-LEPTON PLOTS
   if ((nCleanElectrons+ nCleanMuons) == 2){
     if (nCleanElectrons==2 && fCleanElectrons[1].pt()>45.0 && fCleanElectrons[0].pt()>45.0){
       h_DiElectronMass->Fill((fCleanElectrons[0].p4()+fCleanElectrons[1].p4()).mass());
     }
     if (nCleanMuons==2 && fCleanMuons[1].pt()>30.0 && fCleanMuons[0].pt()>30.0){
       h_DiMuonMass->Fill((fCleanMuons[0].p4()+fCleanMuons[1].p4()).mass());
     }
     if ((nCleanElectrons == 1 && fCleanElectrons[0].pt()>45.0) && (nCleanMuons==1 && fCleanMuons[0].pt()>30.0))
       {
	 h_ElectronMuonMass->Fill((fCleanElectrons[0].p4()+fCleanMuons[0].p4()).mass()); 
       }
   }

   //JET cuts
   bool enoughCleanJets=true;  
   if (_njetsMin  < 3) enoughCleanJets=false;
   //Need at leat N Jets                                                                       
   if (nCleanJets < _njetsMin) enoughCleanJets=false;
   //Need no more than N Jets ;)                                                          
   if (nCleanJets > _njetsMax) enoughCleanJets=false;
 

   //SINGLE LEPTON SELECTION 
   bool minCleanLeptons=false;
   bool enoughCleanLeptons=false;
   float fLeptonPt=0;
   //TLorentzVector fLepton;
   float fElectronPt=0;
   float fMuonPt=0;
   //checking how many jets pass the chosen pt cut
   int nJet35=0; int nBJet35=0;
   for (unsigned int i=0; i<fCleanJets.size(); i++){
     if (fCleanJets[i].pt()>35.0){
       nJet35=i+1;
       if (fCleanJets[i].bDiscriminator("simpleSecondaryVertexHighEffBJetTags") > 1.74) nBJet35++;
       
     }
   }
   //if (nJet35>=1) cout <<nJet35<<"  "<<nBJet35<<endl;
   
   
   h_NumEvtCut->Fill(0);
   if ((nCleanElectrons+ nCleanMuons) == 1){//asking for exactly one clean muon or electron > 20GeV
     h_NumEvtCut->Fill(1);
     if (nCleanElectrons==1 && fCleanElectrons[0].pt()>25.0){//one electron with pt > 45 GeV
       h_NumEvtCut->Fill(2); 
       if( fMET.et()>30.0){//MET above 30
	 h_NumEvtCut->Fill(3);
	 if(nJet35 >=1){//at least one jet with pt >35
	   h_NumEvtCut->Fill(4);
	   if(nJet35 >=2){//at least two jet with pt >35
	     h_NumEvtCut->Fill(5);
	     if(nJet35 >=1 && nBJet35>=1){
	       h_NumEvtCut->Fill(6);
	       if(nJet35 >=3){
		 h_NumEvtCut->Fill(7);
		 
		 if(nJet35 >=4){
		   pat::Electron fLepton=fCleanElectrons[0];
		   h_NumEvtCut->Fill(8);
		   TLorentzVector v_TransMassLepMET4Jet;
		   v_TransMassLepMET4Jet.SetPx(fLepton.px()+fMET.px()+fCleanJets[0].px()+fCleanJets[1].px()+fCleanJets[2].px()+fCleanJets[3].px());
		   v_TransMassLepMET4Jet.SetPy(fLepton.py()+fMET.py()+fCleanJets[0].py()+fCleanJets[1].py()+fCleanJets[2].py()+fCleanJets[3].py());
		   v_TransMassLepMET4Jet.SetPz(0);
		   v_TransMassLepMET4Jet.SetE(fLepton.et()+fMET.et()+fCleanJets[0].et()+fCleanJets[1].et()+fCleanJets[2].et()+fCleanJets[3].et());
		   float SumptSig4Highest=0;
		   SumptSig4Highest=((fCleanJets[0].p4()+fCleanJets[1].p4()+fCleanJets[2].p4()+fCleanJets[3].p4()+fLepton.p4()+fMET.p4()).pt())
		     /(fCleanJets[0].pt()+fCleanJets[1].pt()+fCleanJets[2].pt()+fCleanJets[3].pt()+fLepton.pt()+fMET.pt());

		   TLorentzVector v_TransMassLepMET;
		   v_TransMassLepMET.SetPx(fLepton.px()+fMET.px());
		   v_TransMassLepMET.SetPy(fLepton.py()+fMET.py());
		   v_TransMassLepMET.SetPz(0);
		   v_TransMassLepMET.SetE(fLepton.et()+fMET.et());
		   
		   if(fLepton.charge()==+1 && nBJet35>=1) h_TransMassLepMET4JetPlus_4jet1b->Fill(v_TransMassLepMET4Jet.Mag());
		   if(fLepton.charge()==+1 && nBJet35>=2) h_TransMassLepMET4JetPlus_4jet2b->Fill(v_TransMassLepMET4Jet.Mag());
		   if(fLepton.charge()==-1 && nBJet35>=1) h_TransMassLepMET4JetMinus_4jet1b->Fill(v_TransMassLepMET4Jet.Mag());
		   if(fLepton.charge()==-1 && nBJet35>=2) h_TransMassLepMET4JetMinus_4jet2b->Fill(v_TransMassLepMET4Jet.Mag());
		  
		   if(fLepton.charge()==+1 && nBJet35>=1) h_SumptSig4HighestPlus_4jet1b->Fill(SumptSig4Highest);
		   if(fLepton.charge()==+1 && nBJet35>=2) h_SumptSig4HighestPlus_4jet2b->Fill(SumptSig4Highest);
		   if(fLepton.charge()==-1 && nBJet35>=1) h_SumptSig4HighestMinus_4jet1b->Fill(SumptSig4Highest);
		   if(fLepton.charge()==-1 && nBJet35>=2) h_SumptSig4HighestMinus_4jet2b->Fill(SumptSig4Highest);
		   
		  		   
		   if(nJet35 >=5){

		     float SumptSig4SecondHighest=0;
		     SumptSig4SecondHighest=((fCleanJets[1].p4()+fCleanJets[2].p4()+fCleanJets[3].p4()+fCleanJets[4].p4()+fLepton.p4()+fMET.p4()).pt())
		       /(fCleanJets[1].pt()+fCleanJets[2].pt()+fCleanJets[3].pt()+fCleanJets[4].pt()+fLepton.pt()+fMET.pt());

		     h_NumEvtCut->Fill(9);
		     if(fLepton.charge()==+1 && nBJet35>=1) h_TransMassLepMET4JetPlus_5jet1b->Fill(v_TransMassLepMET4Jet.Mag());
		     if(fLepton.charge()==+1 && nBJet35>=2) h_TransMassLepMET4JetPlus_5jet2b->Fill(v_TransMassLepMET4Jet.Mag());
		     if(fLepton.charge()==-1 && nBJet35>=1) h_TransMassLepMET4JetMinus_5jet1b->Fill(v_TransMassLepMET4Jet.Mag());
		     if(fLepton.charge()==-1 && nBJet35>=2) h_TransMassLepMET4JetMinus_5jet2b->Fill(v_TransMassLepMET4Jet.Mag());

		     if(fLepton.charge()==+1 && nBJet35>=1) h_SumptSig4HighestPlus_5jet1b->Fill(SumptSig4Highest);
		     if(fLepton.charge()==+1 && nBJet35>=2) h_SumptSig4HighestPlus_5jet2b->Fill(SumptSig4Highest);
		     if(fLepton.charge()==-1 && nBJet35>=1) h_SumptSig4HighestMinus_5jet1b->Fill(SumptSig4Highest);
		     if(fLepton.charge()==-1 && nBJet35>=2) h_SumptSig4HighestMinus_5jet2b->Fill(SumptSig4Highest);

		     if(fLepton.charge()==+1 && nBJet35>=1) h_SumptSig4SecondHighestPlus_5jet1b->Fill(SumptSig4SecondHighest);
		     if(fLepton.charge()==+1 && nBJet35>=2) h_SumptSig4SecondHighestPlus_5jet2b->Fill(SumptSig4SecondHighest);
		     if(fLepton.charge()==-1 && nBJet35>=1) h_SumptSig4SecondHighestMinus_5jet1b->Fill(SumptSig4SecondHighest);
		     if(fLepton.charge()==-1 && nBJet35>=2) h_SumptSig4SecondHighestMinus_5jet2b->Fill(SumptSig4SecondHighest);
		   }
		   
		 }
	       }
	       
	     }
	     
	   }
	   
	 }
       }
     }
     
   }
   
      


   /* if(enoughCleanJets){
   if ((nCleanElectrons+ nCleanMuons) == 1 && fMET.et()>30.0 && fCleanJets[nCleanJets-1].pt()>35.0){
     minCleanLeptons=true;
     if (nCleanElectrons==1 && fCleanElectrons[0].pt()>45.0)
       {
	 enoughCleanLeptons=true;
	 fLeptonPt=fCleanElectrons[0].pt();
	 fElectronPt=fCleanElectrons[0].pt();
	 pat::Electron fLepton=fCleanElectrons[0];

	 if(nCleanJets>=5){
	   float SumptSig4Highest=0;
	   SumptSig4Highest=((fCleanJets[0].p4()+fCleanJets[1].p4()+fCleanJets[2].p4()+fCleanJets[3].p4()+fLepton.p4()+fMET.p4()).pt())
	     /(fCleanJets[0].pt()+fCleanJets[1].pt()+fCleanJets[2].pt()+fCleanJets[3].pt()+fLepton.pt()+fMET.pt());
	  
	   
	   float SumptSig4SecondHighest=0;
	   SumptSig4SecondHighest=((fCleanJets[1].p4()+fCleanJets[2].p4()+fCleanJets[3].p4()+fCleanJets[4].p4()+fLepton.p4()+fMET.p4()).pt())
	     /(fCleanJets[1].pt()+fCleanJets[2].pt()+fCleanJets[3].pt()+fCleanJets[4].pt()+fLepton.pt()+fMET.pt());
	   
	   TLorentzVector v_TransMassLepMET;
	   v_TransMassLepMET.SetPx(fLepton.px()+fMET.px());
	   v_TransMassLepMET.SetPy(fLepton.py()+fMET.py());
	   v_TransMassLepMET.SetPz(0);
	   v_TransMassLepMET.SetE(fLepton.et()+fMET.et());
	  

	   TLorentzVector v_TransMassLepMET4SecondJet;
	   v_TransMassLepMET4SecondJet.SetPx(fLepton.px()+fMET.px()+fCleanJets[4].px()+fCleanJets[1].px()+fCleanJets[2].px()+fCleanJets[3].px());
	   v_TransMassLepMET4SecondJet.SetPy(fLepton.py()+fMET.py()+fCleanJets[4].py()+fCleanJets[1].py()+fCleanJets[2].py()+fCleanJets[3].py());
	   v_TransMassLepMET4SecondJet.SetPz(0);
	   v_TransMassLepMET4SecondJet.SetE(fLepton.et()+fMET.et()+fCleanJets[4].et()+fCleanJets[1].et()+fCleanJets[2].et()+fCleanJets[3].et());
	   
	   if(fLepton.charge()==+1){
	     h_SumptSig4HighestPlus->Fill(SumptSig4Highest);
	     h_SumptSig4SecondHighestPlus->Fill(SumptSig4SecondHighest);
	     h_TransMassLepMETPlus->Fill(v_TransMassLepMET.Mag());
	     h_TransMassLepMET4SecondJetPlus->Fill(v_TransMassLepMET4SecondJet.Mag());
	   }
	   if(fLepton.charge()==-1){
	     h_SumptSig4HighestMinus->Fill(SumptSig4Highest);
	      h_SumptSig4SecondHighestMinus->Fill(SumptSig4SecondHighest);
	     h_TransMassLepMETMinus->Fill(v_TransMassLepMET.Mag());
	     h_TransMassLepMET4SecondJetMinus->Fill(v_TransMassLepMET4SecondJet.Mag());
	   }
	   
	 }
	 if(nCleanJets>=4){
	   TLorentzVector v_TransMassLepMET4Jet;
	   v_TransMassLepMET4Jet.SetPx(fLepton.px()+fMET.px()+fCleanJets[0].px()+fCleanJets[1].px()+fCleanJets[2].px()+fCleanJets[3].px());
	   v_TransMassLepMET4Jet.SetPy(fLepton.py()+fMET.py()+fCleanJets[0].py()+fCleanJets[1].py()+fCleanJets[2].py()+fCleanJets[3].py());
	   v_TransMassLepMET4Jet.SetPz(0);
	   v_TransMassLepMET4Jet.SetE(fLepton.et()+fMET.et()+fCleanJets[0].et()+fCleanJets[1].et()+fCleanJets[2].et()+fCleanJets[3].et());

	   if(fLepton.charge()==+1 && nBJets>=1 && nCleanJets>=4) h_TransMassLepMET4JetPlus_4jet1b->Fill(v_TransMassLepMET4Jet.Mag());
	   if(fLepton.charge()==+1 && nBJets>=2 && nCleanJets>=4) h_TransMassLepMET4JetPlus_4jet2b->Fill(v_TransMassLepMET4Jet.Mag());
	   if(fLepton.charge()==+1 && nBJets>=1 && nCleanJets>=5) h_TransMassLepMET4JetPlus_5jet1b->Fill(v_TransMassLepMET4Jet.Mag());
	   if(fLepton.charge()==+1 && nBJets>=2 && nCleanJets>=5) h_TransMassLepMET4JetPlus_5jet2b->Fill(v_TransMassLepMET4Jet.Mag());

	   if(fLepton.charge()==-1 && nBJets>=1 && nCleanJets>=4) h_TransMassLepMET4JetMinus_4jet1b->Fill(v_TransMassLepMET4Jet.Mag());
	   if(fLepton.charge()==-1 && nBJets>=2 && nCleanJets>=4) h_TransMassLepMET4JetMinus_4jet2b->Fill(v_TransMassLepMET4Jet.Mag());
	   if(fLepton.charge()==-1 && nBJets>=1 && nCleanJets>=5) h_TransMassLepMET4JetMinus_5jet1b->Fill(v_TransMassLepMET4Jet.Mag());
	   if(fLepton.charge()==-1 && nBJets>=2 && nCleanJets>=5) h_TransMassLepMET4JetMinus_5jet2b->Fill(v_TransMassLepMET4Jet.Mag());
	   if (v_TransMassLepMET4Jet.Mag()>1000.0) cout<<run<<" "<<event<<endl;
	   
	 }   
       }
   */
     /*if (nCleanMuons==1 && fCleanMuons[0].pt()>30.0){
	 enoughCleanLeptons=true;
	 fLeptonPt=fCleanMuons[0].pt();
	 fMuonPt=fCleanMuons[0].pt();
	 pat::Muon fLepton=fCleanMuons[0];

	 if(nCleanJets>=5){
	   float SumptSig4Highest=0;
	   SumptSig4Highest=((fCleanJets[0].p4()+fCleanJets[1].p4()+fCleanJets[2].p4()+fCleanJets[3].p4()+fLepton.p4()+fMET.p4()).pt())
	     /(fCleanJets[0].pt()+fCleanJets[1].pt()+fCleanJets[2].pt()+fCleanJets[3].pt()+fLepton.pt()+fMET.pt());
	  
	   
	   float SumptSig4SecondHighest=0;
	   SumptSig4SecondHighest=((fCleanJets[1].p4()+fCleanJets[2].p4()+fCleanJets[3].p4()+fCleanJets[4].p4()+fLepton.p4()+fMET.p4()).pt())
	     /(fCleanJets[1].pt()+fCleanJets[2].pt()+fCleanJets[3].pt()+fCleanJets[4].pt()+fLepton.pt()+fMET.pt());
	   
	   TLorentzVector v_TransMassLepMET;
	   v_TransMassLepMET.SetPx(fLepton.px()+fMET.px());
	   v_TransMassLepMET.SetPy(fLepton.py()+fMET.py());
	   v_TransMassLepMET.SetPz(0);
	   v_TransMassLepMET.SetE(fLepton.et()+fMET.et());
	  

	   TLorentzVector v_TransMassLepMET4SecondJet;
	   v_TransMassLepMET4SecondJet.SetPx(fLepton.px()+fMET.px()+fCleanJets[4].px()+fCleanJets[1].px()+fCleanJets[2].px()+fCleanJets[3].px());
	   v_TransMassLepMET4SecondJet.SetPy(fLepton.py()+fMET.py()+fCleanJets[4].py()+fCleanJets[1].py()+fCleanJets[2].py()+fCleanJets[3].py());
	   v_TransMassLepMET4SecondJet.SetPz(0);
	   v_TransMassLepMET4SecondJet.SetE(fLepton.et()+fMET.et()+fCleanJets[4].et()+fCleanJets[1].et()+fCleanJets[2].et()+fCleanJets[3].et());
	   
	   if(fLepton.charge()==+1){
	     h_SumptSig4HighestPlus->Fill(SumptSig4Highest);
	     h_SumptSig4SecondHighestPlus->Fill(SumptSig4SecondHighest);
	     h_TransMassLepMETPlus->Fill(v_TransMassLepMET.Mag());
	     h_TransMassLepMET4SecondJetPlus->Fill(v_TransMassLepMET4SecondJet.Mag());
	   }
	   if(fLepton.charge()==-1){
	     h_SumptSig4HighestMinus->Fill(SumptSig4Highest);
	      h_SumptSig4SecondHighestMinus->Fill(SumptSig4SecondHighest);
	     h_TransMassLepMETMinus->Fill(v_TransMassLepMET.Mag());
	     h_TransMassLepMET4SecondJetMinus->Fill(v_TransMassLepMET4SecondJet.Mag());
	   }
	   
	 }
	 if(nCleanJets>=4){
	   TLorentzVector v_TransMassLepMET4Jet;
	   v_TransMassLepMET4Jet.SetPx(fLepton.px()+fMET.px()+fCleanJets[0].px()+fCleanJets[1].px()+fCleanJets[2].px()+fCleanJets[3].px());
	   v_TransMassLepMET4Jet.SetPy(fLepton.py()+fMET.py()+fCleanJets[0].py()+fCleanJets[1].py()+fCleanJets[2].py()+fCleanJets[3].py());
	   v_TransMassLepMET4Jet.SetPz(0);
	   v_TransMassLepMET4Jet.SetE(fLepton.et()+fMET.et()+fCleanJets[0].et()+fCleanJets[1].et()+fCleanJets[2].et()+fCleanJets[3].et());

	   if(fLepton.charge()==+1 && nBJets>=1 && nCleanJets>=4) h_TransMassLepMET4JetPlus_4jet1b->Fill(v_TransMassLepMET4Jet.Mag());
	   if(fLepton.charge()==+1 && nBJets>=2 && nCleanJets>=4) h_TransMassLepMET4JetPlus_4jet2b->Fill(v_TransMassLepMET4Jet.Mag());
	   if(fLepton.charge()==+1 && nBJets>=1 && nCleanJets>=5) h_TransMassLepMET4JetPlus_5jet1b->Fill(v_TransMassLepMET4Jet.Mag());
	   if(fLepton.charge()==+1 && nBJets>=2 && nCleanJets>=5) h_TransMassLepMET4JetPlus_5jet2b->Fill(v_TransMassLepMET4Jet.Mag());

	   if(fLepton.charge()==-1 && nBJets>=1 && nCleanJets>=4) h_TransMassLepMET4JetMinus_4jet1b->Fill(v_TransMassLepMET4Jet.Mag());
	   if(fLepton.charge()==-1 && nBJets>=2 && nCleanJets>=4) h_TransMassLepMET4JetMinus_4jet2b->Fill(v_TransMassLepMET4Jet.Mag());
	   if(fLepton.charge()==-1 && nBJets>=1 && nCleanJets>=5) h_TransMassLepMET4JetMinus_5jet1b->Fill(v_TransMassLepMET4Jet.Mag());
	   if(fLepton.charge()==-1 && nBJets>=2 && nCleanJets>=5) h_TransMassLepMET4JetMinus_5jet2b->Fill(v_TransMassLepMET4Jet.Mag());
	   if (v_TransMassLepMET4Jet.Mag()>1000.0) cout<<run<<" "<<event<<endl;
	   
	 }   
	 }*/
     /*if (nCleanMuons==1 && fCleanMuons[0].pt()>30.0)
       {
	 enoughCleanLeptons=true;
	 fLeptonPt=fCleanMuons[0].pt();
	 fMuonPt=fCleanMuons[0].pt();
	 
	 pat::Muon fLepton=fCleanMuons[0];//(fCleanMuons[0].px(),fCleanMuons[0].py(),fCleanMuons[0].pz(),fCleanMuons[0].et());
	 if(nCleanJets>=5){
	   float SumptSig4Highest=0;
	   SumptSig4Highest=((fCleanJets[0].p4()+fCleanJets[1].p4()+fCleanJets[2].p4()+fCleanJets[3].p4()+fLepton.p4()+fMET.p4()).pt())
	     /(fCleanJets[0].pt()+fCleanJets[1].pt()+fCleanJets[2].pt()+fCleanJets[3].pt()+fLepton.pt()+fMET.pt());
	  
	   float SumptSig4SecondHighest=0;
	   SumptSig4SecondHighest=((fCleanJets[1].p4()+fCleanJets[2].p4()+fCleanJets[3].p4()+fCleanJets[4].p4()+fLepton.p4()+fMET.p4()).pt())
	     /(fCleanJets[1].pt()+fCleanJets[2].pt()+fCleanJets[3].pt()+fCleanJets[4].pt()+fLepton.pt()+fMET.pt());
	   
	   TLorentzVector v_TransMassLepMET;
	   v_TransMassLepMET.SetPx(fLepton.px()+fMET.px());
	   v_TransMassLepMET.SetPy(fLepton.py()+fMET.py());
	   v_TransMassLepMET.SetPz(0);
	   v_TransMassLepMET.SetE(fLepton.et()+fMET.et());
	  
	   TLorentzVector v_TransMassLepMET4SecondJet;
	   v_TransMassLepMET4SecondJet.SetPx(fLepton.px()+fMET.px()+fCleanJets[4].px()+fCleanJets[1].px()+fCleanJets[2].px()+fCleanJets[3].px());
	   v_TransMassLepMET4SecondJet.SetPy(fLepton.py()+fMET.py()+fCleanJets[4].py()+fCleanJets[1].py()+fCleanJets[2].py()+fCleanJets[3].py());
	   v_TransMassLepMET4SecondJet.SetPz(0);
	   v_TransMassLepMET4SecondJet.SetE(fLepton.et()+fMET.et()+fCleanJets[4].et()+fCleanJets[1].et()+fCleanJets[2].et()+fCleanJets[3].et());
	   
	 
	   
	   if(fLepton.charge()==+1){
	     h_SumptSig4HighestPlus->Fill(SumptSig4Highest);
	     h_SumptSig4SecondHighestPlus->Fill(SumptSig4SecondHighest);
	     h_TransMassLepMETPlus->Fill(v_TransMassLepMET.Mag());
	     h_TransMassLepMET4SecondJetPlus->Fill(v_TransMassLepMET4SecondJet.Mag());
	   }
	   if(fLepton.charge()==-1){
	     h_SumptSig4HighestMinus->Fill(SumptSig4Highest);
	     h_SumptSig4SecondHighestMinus->Fill(SumptSig4SecondHighest);
	     h_TransMassLepMETMinus->Fill(v_TransMassLepMET.Mag());
	     h_TransMassLepMET4SecondJetMinus->Fill(v_TransMassLepMET4SecondJet.Mag());
	   }
	   
	 }
	 if(nCleanJets>=4){
	   TLorentzVector v_TransMassLepMET4Jet;
	   v_TransMassLepMET4Jet.SetPx(fLepton.px()+fMET.px()+fCleanJets[0].px()+fCleanJets[1].px()+fCleanJets[2].px()+fCleanJets[3].px());
	   v_TransMassLepMET4Jet.SetPy(fLepton.py()+fMET.py()+fCleanJets[0].py()+fCleanJets[1].py()+fCleanJets[2].py()+fCleanJets[3].py());
	   v_TransMassLepMET4Jet.SetPz(0);
	   v_TransMassLepMET4Jet.SetE(fLepton.et()+fMET.et()+fCleanJets[0].et()+fCleanJets[1].et()+fCleanJets[2].et()+fCleanJets[3].et());
	   if(fLepton.charge()==+1){
	     h_TransMassLepMET4JetPlus->Fill(v_TransMassLepMET4Jet.Mag());
	   }
	   if(fLepton.charge()==-1){
	     h_TransMassLepMET4JetMinus->Fill(v_TransMassLepMET4Jet.Mag());
	   }
	   
	 }   
       }
   }
    }//enoughCleanJets
   //make some additional plots 
   */
   
   /////////////////////
   //////TRIPLETS
   ///////////////////
  
    
   //call function that makes the triplets for all events that pass the minimum lepton ID but enough good jets
   /*if(enoughCleanJets && minCleanLeptons){
  
  nTriplets=0;
  
  MakeTriplets(fCleanJets);  
  if(enoughCleanLeptons){
    h_LeptonPt->Fill(fLeptonPt);
    if (nCleanElectrons==1)    h_ElectronPt->Fill( fElectronPt);
     if (nCleanMuons==1)h_MuonPt->Fill(fMuonPt);
    countE++;
   //make some plots only for events with cuts applied
   
     
     //ok make now some plots
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
		   if(Triplet[q][2].pt()>iPt && fCleanJets[iNjet-1].pt()>iPt)
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
		     if(Triplet[q][2].pt()>iPt && fCleanJets[_njetsMin-1].pt()>iPt && fCleanJets[iNjet-1].pt()>iPt)
		       {
			 //cout<<"after selection"<<endl;
			 //cout<<Triplet[q][2].pt()<<" "<<fCleanJets.size()<<" "<<fCleanJets[iNjet-1].pt()<<endl;
			 if(massTriplet[q]<(sumScalarPtTriplet[q]-iDiag))
			   {
			     float countT=0;
			     Mjjj_pt_njet_diag[i][k][j]->Fill(massTriplet[q]);
			     //if(countT==0 && massTriplet[q]>160 && massTriplet[q]<190){
			     M4j_pt_njet_diag[i][k][j]->Fill(massQuad[q]);
			     countT++;
			     
			     Mjjj_M4j_pt_njet_diag[i][k][j]->Fill(massTriplet[q],massQuad[q]);
			     //}
			     //cout<<"!!!!!!!!!!!!!KEEP!!!!!!!!!!"<<endl;
			   }
		       }
		      }
		 }//diag cut loop
	       }//njetloop
	   }//pt loop
       }//triplet loop
     
   }
   }*/
   
   //fill the tree use golden JSON file
   //GetMCTruth(iEvent);
   MyTree->Fill();
   entry++;
   
    }
 }
}

// ------------ method called once each job just before starting event loop  ------------
void 
TopXana::beginJob() 
{ if (_isData) {
    char c;
    int n;
    
    ifstream JSONFile(JSONFilename.data());
    nGoodRuns=0;
    int run, lb, le;
    bool startlb = false;
    while(!JSONFile.eof()){
      c=JSONFile.peek();
      while(!JSONFile.eof() && !( (c >= '0') && (c <= '9'))) {
	c = JSONFile.get();
	c = JSONFile.peek();

      }
      JSONFile>>n;
      if(n>100000){
	run = n;
	//cout<<run<<endl;
      }
      else{
	if(!startlb){
	  lb = n;
	  startlb = true;
	}
	else{
	  le = n;
	  GoodRuns.push_back(run);
	  GoodLumiStart.push_back(lb);
	  GoodLumiEnd.push_back(le);
	  ++nGoodRuns;
	  startlb = false;
	}
      }
    }
    cout << "Got: " << nGoodRuns << " specified as good." << endl;
  }


  countE=0;
run_evt_ee.open ("/cms/data21/clseitz/CMS_leptons/Electrons/NewCode3/run_evt_ee.txt");
run_evt_em.open ("/cms/data21/clseitz/CMS_leptons/Electrons/NewCode3/run_evt_em.txt");
run_evt_mm.open ("/cms/data21/clseitz/CMS_leptons/Electrons/NewCode3/run_evt_mm.txt");
  //define the tree we want to write out
  outputFile2= new TFile(_outputFilename2.data(),"recreate"); 
  outputFile2->cd();
  MyTree = new TTree("Events","");
  MyTree->Branch("run", &run);
  MyTree->Branch("event", &event);
  MyTree->Branch("lumis", &lumis);
 MyTree->Branch("entry", &entry);
  if(!_isData){
  MyTree->Branch("pdgID",pdgID,"pdgID[200]/I");
  MyTree->Branch("MCpx", MCpx, "MCpx[200]/F");
  MyTree->Branch("MCpy", MCpy, "MCpy[200]/F");
  MyTree->Branch("MCpz", MCpz, "MCpz[200]/F");
  MyTree->Branch("MCe", MCe, "MCe[200]/F");
  }
  MyTree->Branch("nJets", &nJets);
  MyTree->Branch("nElectrons", &nElectrons);
  MyTree->Branch("nMuons", &nMuons);
  MyTree->Branch("nPhotons", &nPhotons);
  MyTree->Branch("nTriplets", &nTriplets);
 MyTree->Branch("nGoodVtx", &nGoodVtx);

  MyTree->Branch("jetpt[nJets]", jetpt);
  MyTree->Branch("jetpx[nJets]", jetpx);
  MyTree->Branch("jetpy[nJets]", jetpy);
  MyTree->Branch("jetpz[nJets]", jetpz);
  MyTree->Branch("jete[nJets]", jete);

 
  MyTree->Branch("ept[nElectrons]", ept);
  MyTree->Branch("epx[nElectrons]", epx);
  MyTree->Branch("epy[nElectrons]", epy);
  MyTree->Branch("epz[nElectrons]", epz);
  MyTree->Branch("ee[nElectrons]", ee);
  
 
  MyTree->Branch("mpt[nMuons]", mpt);
  MyTree->Branch("mpx[nMuons]", mpx);
  MyTree->Branch("mpy[nMuons]", mpy);
  MyTree->Branch("mpz[nMuons]", mpz);
  MyTree->Branch("me[nMuons]", me);
  
 
  MyTree->Branch("phpt[nPhotons]", phpt);
  MyTree->Branch("phpx[nPhotons]", phpx);
  MyTree->Branch("phpy[nPhotons]", phpy);
  MyTree->Branch("phpz[nPhotons]", phpz);
  MyTree->Branch("phe[nPhotons]", phe);
  
  MyTree->Branch("triplet_jet1pt[nTriplets]", triplet_jet1pt);
  MyTree->Branch("triplet_jet2pt[nTriplets]", triplet_jet2pt);
  MyTree->Branch("triplet_jet3pt[nTriplets]", triplet_jet3pt);
  MyTree->Branch("triplet_sumScalarPt[nTriplets]",triplet_sumScalarPt);
  MyTree->Branch("triplet_mass[nTriplets]",triplet_mass);
  MyTree->Branch("triplet_sumVectorPt[nTriplets]",triplet_sumVectorPt);
  
  MyTree->Branch("triplet_jet1px[nTriplets]", triplet_jet1px);
  MyTree->Branch("triplet_jet1py[nTriplets]", triplet_jet1py);
  MyTree->Branch("triplet_jet1pz[nTriplets]", triplet_jet1pz);
  MyTree->Branch("triplet_jet1e[nTriplets]", triplet_jet1e);

 
  MyTree->Branch("triplet_jet2px[nTriplets]", triplet_jet2px);
  MyTree->Branch("triplet_jet2py[nTriplets]", triplet_jet2py);
  MyTree->Branch("triplet_jet2pz[nTriplets]", triplet_jet2pz);
  MyTree->Branch("triplet_jet2e[nTriplets]", triplet_jet2e);

 
  MyTree->Branch("triplet_jet3px[nTriplets]", triplet_jet3px);
  MyTree->Branch("triplet_jet3py[nTriplets]", triplet_jet3py);
  MyTree->Branch("triplet_jet3pz[nTriplets]", triplet_jet3pz);
  MyTree->Branch("triplet_jet3e[nTriplets]", triplet_jet3e);
  
 

  char hTITLE[99];
  char hNAME[99];
  //create output file
  outputFile = new TFile(_outputFilename.data(),"recreate");
  //initialize event counter
  entry = 0;
  h_NumEvtCut = new TH1F("NumEvtCut", "NumEvtCut",20,0,20);
  h_DiElectronMass = new TH1F("DiElectronMass","DiElectronMass",200,0,400);
  h_DiMuonMass = new TH1F("DiMuonMass","DiMuonMass",200,0,400);
  h_ElectronMuonMass = new TH1F("ElectronMuonMass","ElectronMuonMass",200,0,400);


  sprintf(hTITLE, "Number of good Jet with Pt>%i and Eta<%i", (int) _jetptcut,(int) _etacut);
  h_nGoodJets = new TH1F("nJetsGood", hTITLE,20,0,20);
  
  sprintf(hTITLE, "Number of good Electrons with Pt>%i and Eta<%i", (int) _ept,(int) _eeta);
  h_nGoodElectrons = new TH1F("nElectronsGood", hTITLE,10,0,10);
  
  sprintf(hTITLE, "Number of good Muons with Pt>%i and Eta<%i", (int) _mpt,(int) _meta);
  h_nGoodMuons = new TH1F("nMuonsGood", hTITLE,10,0,10);
  
  sprintf(hTITLE, "Number of good Photons with Pt>%i and Eta<%i", (int) _phpt,(int) _pheta);
  h_nGoodPhotons = new TH1F("nPhotonsGood", hTITLE,10,0,10);
  
  sprintf(hTITLE, "Number of clean Jet with Pt>%i and Eta<%i", (int) _jetptcut,(int) _etacut);
  h_nCleanJets = new TH1F("nJetsClean", hTITLE,20,0,20);
  
  sprintf(hTITLE, "Number of clean Electrons with Pt>%i and Eta<%i", (int) _ept,(int) _eeta);
  h_nCleanElectrons = new TH1F("nElectronsClean", hTITLE,10,0,10);
  
  sprintf(hTITLE, "Number of clean Muons with Pt>%i and Eta<%i", (int) _mpt,(int) _meta);
  h_nCleanMuons = new TH1F("nMuonsClean", hTITLE,10,0,10);
  
  sprintf(hTITLE, "Number of clean Photons with Pt>%i and Eta<%i", (int) _phpt,(int) _pheta);
  h_nCleanPhotons = new TH1F("nPhotonsClean", hTITLE,10,0,10);
  
  h_nGoodVtx = new TH1F("nVtx","Number of Vertices",30,0,30);
  h_zPosGoodVtx = new TH1F("zPosCleanVtx","Z position of the vertices",600,-30,30);
  
  h_MET  = new TH1F("PFMet","PFMET",1000,0.,1000.);

  h_SumptSig4HighestPlus = new TH1F("SumptSig4HighestPlus","SumptSig4HighesPlus",200,0,2);
  h_SumptSig4SecondHighestPlus = new TH1F("SumptSig4SecondHighestPlus","SumptSig4SecondHighestPlus",200,0,2);
 h_TransMassLepMETPlus = new TH1F("TransMassLepMETPlus","TransMassLepMETPlus",200,0,2000);
  h_TransMassLepMET4JetPlus_5jet1b = new TH1F("TransMassLepMET4JetPlus_5jet1b","TransMassLepMET4JetPlus_5jet1b",200,0,2000);
  h_TransMassLepMET4JetPlus_5jet2b = new TH1F("TransMassLepMET4JetPlus_5jet2b","TransMassLepMET4JetPlus_5jet2b",200,0,2000);
  h_TransMassLepMET4JetPlus_4jet1b = new TH1F("TransMassLepMET4JetPlus_4jet1b","TransMassLepMET4JetPlus_4jet1b",200,0,2000);
  h_TransMassLepMET4JetPlus_4jet2b = new TH1F("TransMassLepMET4JetPlus_4jet2b","TransMassLepMET4JetPlus_4jet2b",200,0,2000);

  h_TransMassLepMET4JetPlus = new TH1F("TransMassLepMET4JetPlus","TransMassLepMET4JetPlus",400,0,4000);
  h_TransMassLepMET4SecondJetPlus = new TH1F("TransMassLepMET4SecondJetPlus","TransMassLepMET4SecondJetPlus",400,0,4000);

  h_SumptSig4HighestMinus = new TH1F("SumptSig4HighestMinus","SumptSig4HighesMinus",200,0,2);
  h_SumptSig4SecondHighestMinus = new TH1F("SumptSig4SecondHighestMinus","SumptSig4SecondHighestMinus",200,0,2);
  h_TransMassLepMETMinus = new TH1F("TransMassLepMETMinus","TransMassLepMETMinus",200,0,2000);

  h_TransMassLepMET4JetMinus_5jet1b = new TH1F("TransMassLepMET4JetMinus_5jet1b","TransMassLepMET4JetMinus_5jet1b",200,0,2000);
  h_TransMassLepMET4JetMinus_5jet2b = new TH1F("TransMassLepMET4JetMinus_5jet2b","TransMassLepMET4JetMinus_5jet2b",200,0,2000);
  h_TransMassLepMET4JetMinus_4jet1b = new TH1F("TransMassLepMET4JetMinus_4jet1b","TransMassLepMET4JetMinus_4jet1b",200,0,2000);
  h_TransMassLepMET4JetMinus_4jet2b = new TH1F("TransMassLepMET4JetMinus_4jet2b","TransMassLepMET4JetMinus_4jet2b",200,0,2000);
  h_TransMassLepMET4JetMinus = new TH1F("TransMassLepMET4JetMinus","TransMassLepMET4JetMinus",400,0,4000);
  h_TransMassLepMET4SecondJetMinus = new TH1F("TransMassLepMET4SecondJetMinus","TransMassLepMET4SecondJetMinus",400,0,4000);

  h_SumptSig4HighestPlus_5jet1b = new TH1F("SumptSig4HighestPlus_5jet1b","SumptSig4HighesPlus_5jet1b",200,0,2);
   h_SumptSig4HighestPlus_4jet1b = new TH1F("SumptSig4HighestPlus_4jet1b","SumptSig4HighesPlus_4jet1b",200,0,2);
   h_SumptSig4HighestPlus_5jet2b = new TH1F("SumptSig4HighestPlus_5jet2b","SumptSig4HighesPlus_5jet2b",200,0,2);
   h_SumptSig4HighestPlus_4jet2b = new TH1F("SumptSig4HighestPlus_4jet2b","SumptSig4HighesPlus_4jet2b",200,0,2);
   
   h_SumptSig4HighestMinus_5jet1b = new TH1F("SumptSig4HighestMinus_5jet1b","SumptSig4HighesMinus_5jet1b",200,0,2);
   h_SumptSig4HighestMinus_4jet1b = new TH1F("SumptSig4HighestMinus_4jet1b","SumptSig4HighesMinus_4jet1b",200,0,2);
   h_SumptSig4HighestMinus_5jet2b = new TH1F("SumptSig4HighestMinus_5jet2b","SumptSig4HighesMinus_5jet2b",200,0,2);
   h_SumptSig4HighestMinus_4jet2b = new TH1F("SumptSig4HighestMinus_4jet2b","SumptSig4HighesMinus_4jet2b",200,0,2);
   
   h_SumptSig4SecondHighestPlus_5jet1b = new TH1F("SumptSig4SecondHighestPlus_5jet1b","SumptSig4SecondHighesPlus_5jet1b",200,0,2);
   h_SumptSig4SecondHighestPlus_5jet2b = new TH1F("SumptSig4SecondHighestPlus_5jet2b","SumptSig4SecondHighesPlus_5jet2b",200,0,2);
   h_SumptSig4SecondHighestMinus_5jet1b = new TH1F("SumptSig4SecondHighestMinus_5jet1b","SumptSig4SecondHighesMinus_5jet1b",200,0,2);
   h_SumptSig4SecondHighestMinus_5jet2b = new TH1F("SumptSig4SecondHighestMinus_5jet2b","SumptSig4SecondHighesMinus_5jet2b",200,0,2);


  for(int i=0; i<6; i++)
    {
      sprintf(hNAME, "jet_%i_pt", i);
      sprintf(hTITLE, "JetPt of the %i st Jet with Pt>%i and Eta<%i", i,(int) _jetptcut,(int) _etacut);
      v_jet_pt.push_back(new TH1F(hNAME,hTITLE,200,0,1000));
      
      sprintf(hNAME, "jet_%i_eta", i);
      sprintf(hTITLE, "JetEta of the %i st Jet with Pt>%i and Eta<%i", i,(int) _jetptcut,(int) _etacut);
      v_jet_eta.push_back(new TH1F(hNAME,hTITLE,200,-5,5));
      
      sprintf(hNAME, "jet_%i_phi", i);
      sprintf(hTITLE, "JetPhi of the %i st Jet with Pt>%i and Eta<%i", i,(int) _jetptcut,(int) _etacut);
      v_jet_phi.push_back(new TH1F(hNAME,hTITLE,200,-5,5));
      
       sprintf(hNAME, "jet_%i_m", i);
      sprintf(hTITLE, "JetMass of the %i st Jet with Pt>%i and Eta<%i", i,(int) _jetptcut,(int) _etacut);
      v_jet_m.push_back(new TH1F(hNAME,hTITLE,200,0,1000));

      sprintf(hNAME, "electron_%i_pt", i);
      sprintf(hTITLE, "ElectronPt of the %i st Electron with Pt>%i and Eta<%i", i,(int) _ept,(int) _eeta);
      v_e_pt.push_back(new TH1F(hNAME,hTITLE,200,0,1000));
      
      sprintf(hNAME, "electron_%i_eta", i);
      sprintf(hTITLE, "ElectronEta of the %i st Electron with Pt>%i and Eta<%i", i,(int) _ept,(int) _eeta);
      v_e_eta.push_back(new TH1F(hNAME,hTITLE,200,-5,5));
      
      sprintf(hNAME, "electron_%i_phi", i);
      sprintf(hTITLE, "ElectronPhi of the %i st Electron with Pt>%i and Eta<%i", i,(int) _ept,(int) _eeta);
      v_e_phi.push_back(new TH1F(hNAME,hTITLE,200,-5,5));
      
      sprintf(hNAME, "muon_%i_pt", i);
      sprintf(hTITLE, "MuonPt of the %i st Muon with Pt>%i and Eta<%i", i,(int) _mpt,(int) _meta);
      v_m_pt.push_back(new TH1F(hNAME,hTITLE,200,0,1000));

      sprintf(hNAME, "muon_%i_eta", i);
      sprintf(hTITLE, "MuonEta of the %i st Muon with Pt>%i and Eta<%i", i,(int) _mpt,(int) _meta);
      v_m_eta.push_back(new TH1F(hNAME,hTITLE,200,-5,5));
      
      sprintf(hNAME, "muon_%i_phi", i);
      sprintf(hTITLE, "MuonPhi of the %i st Muon with Pt>%i and Eta<%i", i,(int) _mpt,(int) _meta);
      v_m_phi.push_back(new TH1F(hNAME,hTITLE,200,-5,5));
      
      sprintf(hNAME, "photon_%i_pt", i);
      sprintf(hTITLE, "PhotonPt of the %i st Photon with Pt>%i and Eta<%i", i,(int) _phpt,(int) _pheta);
      v_ph_pt.push_back(new TH1F(hNAME,hTITLE,200,0,1000));
      
      sprintf(hNAME, "photon_%i_eta", i);
      sprintf(hTITLE, "PhotonEta of the %i st Photon with Pt>%i and Eta<%i", i,(int) _phpt,(int) _pheta);
      v_ph_eta.push_back(new TH1F(hNAME,hTITLE,200,-5,5));
      
      sprintf(hNAME, "photon_%i_phi", i);
      sprintf(hTITLE, "PhotonPhi of the %i st Photon with Pt>%i and Eta<%i", i,(int) _phpt,(int) _pheta);
      v_ph_phi.push_back(new TH1F(hNAME,hTITLE,200,-5,5));
     
    }
  h_LeptonPt = new TH1F("LeptonPt","LeptonPt",200,0,1000);
  h_ElectronPt = new TH1F("ElectronPt", "LeptonPt",200,0,1000);
  h_MuonPt = new TH1F("MuonPt", "LeptonPt",200,0,1000);
  for (int i=0; i<7; i++){
    int iPt=20+i*10;

    for(int k=0; k<4; k++){
      int iNjet=k+3;

      Mjjj_sumpt_pt_njet.push_back(std::vector<TH2F*> ());
      sprintf(hNAME, "Mjjj_sumpt_pt%i_GE%ijet", iPt,iNjet);
      Mjjj_sumpt_pt_njet[i].push_back(new TH2F(hNAME,hNAME,100,0,1000,100,0,1000));
      Mjjj_pt_njet_diag.push_back(std::vector<std::vector<TH1F*> > ());


      
      M4j_pt_njet_diag.push_back(std::vector<std::vector<TH1F*> > ());
      Mjjj_M4j_pt_njet_diag.push_back(std::vector<std::vector<TH2F*> > ());

      for(int j=0; j<20; j++){
	
	int iDiag=j*10+40;
	
	Mjjj_pt_njet_diag[i].push_back(std::vector<TH1F*> ());
	sprintf(hNAME, "Mjjj_pt%i_diag%i_GE%ijet", iPt,iDiag,iNjet);
	Mjjj_pt_njet_diag[i][k].push_back(new TH1F(hNAME,hNAME,100,0,1000));

	M4j_pt_njet_diag[i].push_back(std::vector<TH1F*> ());
	sprintf(hNAME, "M4j_pt%i_diag%i_GE%ijet", iPt,iDiag,iNjet);
	M4j_pt_njet_diag[i][k].push_back(new TH1F(hNAME,hNAME,300,0,3000));
	
	Mjjj_M4j_pt_njet_diag[i].push_back(std::vector<TH2F*> ());
	sprintf(hNAME, "Mjjj_M4j_pt%i_diag%i_GE%ijet", iPt,iDiag,iNjet);
	Mjjj_M4j_pt_njet_diag[i][k].push_back(new TH2F(hNAME,hNAME,100,0,1000,300,0,3000));
      }
    }
  }


}

// ------------ method called once each job just after ending the event loop  ------------
void 
TopXana::endJob() 
{cout<<"Number of one lepton events "<<countE<<endl;
  run_evt_ee.close();
  run_evt_em.close();
  run_evt_mm.close();
  //first write the tree
 outputFile2->Write(); outputFile2->Close();
 //now write out some plots
  char FOLDER[100];
  outputFile->cd();
  outputFile->mkdir("Jets");
  outputFile->cd("Jets");
  h_nGoodJets->Write();
  h_nCleanJets->Write();
  for(int i=0; i<6; i++)
    { v_jet_m[i]->Write();
      v_jet_pt[i]->Write();
      v_jet_eta[i]->Write();
      v_jet_phi[i]->Write();
    }
  
  outputFile->cd();
  outputFile->mkdir("Electrons");
  outputFile->cd("Electrons");
  h_nGoodElectrons->Write();
  h_nCleanElectrons->Write();
  for(int i=0; i<6; i++)
    { 
      v_e_pt[i]->Write();
      v_e_eta[i]->Write();
      v_e_phi[i]->Write();
    }  
  outputFile->mkdir("Muons");
  outputFile->cd("Muons");
  h_nGoodMuons->Write();
  h_nCleanMuons->Write();
  for(int i=0; i<6; i++)
    { 
      v_m_pt[i]->Write();
      v_m_eta[i]->Write();
      v_m_phi[i]->Write();
    }  
  
  outputFile->mkdir("Photons");
  outputFile->cd("Photons");
  h_nGoodPhotons->Write();
  h_nCleanPhotons->Write();
  for(int i=0; i<6; i++)
    { 
      v_ph_pt[i]->Write();
      v_ph_eta[i]->Write();
      v_ph_phi[i]->Write();
    }  
  outputFile->cd();
  outputFile->mkdir("Event");
  outputFile->cd("Event");
  h_NumEvtCut->Write();
  h_DiMuonMass->Write();
  h_DiElectronMass->Write();
  h_ElectronMuonMass->Write();
  h_nGoodVtx->Write();
  h_zPosGoodVtx->Write();
  h_MET->Write();

  h_SumptSig4HighestPlus->Write();
  h_SumptSig4SecondHighestPlus->Write();
  h_TransMassLepMETPlus->Write();
  h_TransMassLepMET4JetPlus->Write();
  h_TransMassLepMET4SecondJetPlus->Write();

  h_SumptSig4HighestMinus->Write();
  h_SumptSig4SecondHighestMinus->Write();
  h_TransMassLepMETMinus->Write();
  h_TransMassLepMET4JetMinus->Write();
  h_TransMassLepMET4SecondJetMinus->Write();

 h_TransMassLepMET4JetPlus_5jet1b->Write();
   h_TransMassLepMET4JetPlus_4jet1b->Write();
   h_TransMassLepMET4JetPlus_5jet2b->Write();
   h_TransMassLepMET4JetPlus_4jet2b->Write();

   h_TransMassLepMET4JetMinus_5jet1b->Write();
   h_TransMassLepMET4JetMinus_4jet1b->Write();
   h_TransMassLepMET4JetMinus_5jet2b->Write();
   h_TransMassLepMET4JetMinus_4jet2b->Write();

   h_SumptSig4HighestPlus_5jet1b->Write();
   h_SumptSig4HighestPlus_4jet1b->Write();
   h_SumptSig4HighestPlus_5jet2b->Write();
   h_SumptSig4HighestPlus_4jet2b->Write();
   
   h_SumptSig4HighestMinus_5jet1b->Write();
   h_SumptSig4HighestMinus_4jet1b->Write();
   h_SumptSig4HighestMinus_5jet2b->Write();
   h_SumptSig4HighestMinus_4jet2b->Write();
   
   h_SumptSig4SecondHighestPlus_5jet1b->Write();
   h_SumptSig4SecondHighestPlus_5jet2b->Write();
   h_SumptSig4SecondHighestMinus_5jet1b->Write();
   h_SumptSig4SecondHighestMinus_5jet2b->Write();


   /*  outputFile->cd();
  TDirectory* now=outputFile->mkdir("Triplets");
  outputFile->cd("Triplets");
 h_LeptonPt->Write();
 h_ElectronPt->Write();
 h_MuonPt->Write();

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
TDirectory* now2=outputFile->mkdir("Quad");
  outputFile->cd("Quad");
for (int i=0; i<7; i++){
    sprintf(FOLDER, "jetpt_%i", i*10+20);
    now2->mkdir(FOLDER);
    now2->cd(FOLDER);
    for (int k=0; k<4; k++){
      for(int j=0; j<20; j++){ 
	M4j_pt_njet_diag[i][k][j]->Write();
	Mjjj_M4j_pt_njet_diag[i][k][j]->Write();
      }
    }
  }
   */

}

// ------------ method called when starting to processes a run  ------------
void 
TopXana::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
TopXana::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
TopXana::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
TopXana::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void 
TopXana::UseJson( vector<int > GoodRuns, vector<int > GoodLumiStart,  vector<int > GoodLumiEnd,  Int_t nGoodRuns , int run, int lumis){
 
  if (_isData) {
    GoodRun=kFALSE;
    for (int ii=0;ii<nGoodRuns;++ii){
      if (run == GoodRuns[ii]){
	if (lumis >= GoodLumiStart[ii]
	    && lumis <=GoodLumiEnd[ii])
	  GoodRun = kTRUE;
      }
    }
  } else {  
    GoodRun = kTRUE;
  }
  return;
}

void 
TopXana::getTriggerDecision(const edm::Event& iEvent, std::map<std::string, bool>& TriggerMap)
{
  edm::Handle<edm::TriggerResults> triggerResults;

  std::string menu = "HLT";
  iEvent.getByLabel(edm::InputTag("TriggerResults", "", menu), triggerResults);

  const edm::TriggerNames& triggerNames = iEvent.triggerNames(* triggerResults);

  for (std::map<std::string, bool>::iterator It = TriggerMap.begin(); It != TriggerMap.end(); ++It) {
    It->second = false;
    unsigned int triggerIndex = triggerNames.triggerIndex(It->first);

    if (triggerIndex < triggerResults->size()) {
      if (triggerResults->accept(triggerIndex)) {
        It->second = true;
      }
    }

  }
  return;
}


void 
TopXana::DoJetID(const edm::Event& iEvent){
   // Jet Handle  
  Handle< vector<Jet> > PatJets; 
  iEvent.getByLabel(_patJetType, PatJets); 
   //lets do some JetID
  
  for (unsigned int j=0; j<PatJets->size(); j++) {
     if (_debug && j==0){
       std::cout<<"--------------run: "<<run<<"--event: "<<event<<"--lumi: "<<lumis<<"--entry: "<<entry<<"-----------"<<endl;
       std::cout << "Number of PatJets: " << PatJets->size() << std::endl;
     }
     
     // Choose jets based on pt and abs(eta)
     if ((*PatJets)[j].pt()        > 20.0  &&
	 fabs((*PatJets)[j].eta()) < 3.0)
       {
	 if (_debug) std::cout << "Jet #" << j << " Passes pT cut of " << _jetptcut 
			       << " and eTa cut of " << _etacut << " with pT: " 
			       <<  (*PatJets)[j].pt() << ", and eTa: " 
			       << (*PatJets)[j].eta() << std::endl;
	 bool jetID = false;
	 if (_patJetType == "selectedPatJets"){
	   //CaloJet ID
	   jetID = 
	     (((*PatJets)[j].correctedJet("Uncorrected").emEnergyFraction() > 0.01 ||
	       fabs((*PatJets)[j].eta())                            > 2.4) &&
	      (*PatJets)[j].correctedJet("Uncorrected").jetID().n90Hits    > 1     &&
	      (*PatJets)[j].correctedJet("Uncorrected").jetID().fHPD       < 0.98);
	 }
	 if (_patJetType == "selectedPatJetsAK5PF" || _patJetType == "goodPatJetsPFlow"){
	   //ParticleFlow ID
	   jetID = 
	     ((*PatJets)[j].correctedJet("Uncorrected").neutralHadronEnergyFraction()   < 0.99 && 
	      (*PatJets)[j].correctedJet("Uncorrected").neutralEmEnergyFraction()       < 0.99 &&
	      (*PatJets)[j].correctedJet("Uncorrected").numberOfDaughters()             > 1    &&
	      (fabs((*PatJets)[j].eta())                    > 2.4  ||
	       ((*PatJets)[j].correctedJet("Uncorrected").chargedHadronEnergyFraction() > 0.   &&
		(*PatJets)[j].correctedJet("Uncorrected").chargedEmEnergyFraction()     < 0.99 &&
		(*PatJets)[j].correctedJet("Uncorrected").chargedMultiplicity()         > 0.))); 
	 }
	 
	 if(jetID){
	   if (_debug) std::cout<<"After JetID"
				<< "Jet #" << j << " Passes pT cut of " << _jetptcut 
				<< " and eTa cut of " << _etacut << " with pT: " 
				<<  (*PatJets)[j].pt() << ", and eTa: " 
				<< (*PatJets)[j].eta() << std::endl;
	   
	   
	 
	   fGoodJets.push_back((*PatJets)[j]);
	 
	   nGoodJets++; 
	  
	   
	 }//JetID
       }//JetKinematics
   }//JetLoop
 if (_debug) std::cout << "Found "<< nGoodJets << " Jets" << std::endl;
return;
}

void 
TopXana::DoVertexID(const edm::Event& iEvent){

  edm::Handle<reco::VertexCollection>  recVtxs;
  iEvent.getByLabel("goodOfflinePrimaryVertices", recVtxs);
  
 
  
  for (size_t i=0; i<recVtxs->size(); ++i)
    if (!((*recVtxs)[i].isFake())) {
      if ( ((*recVtxs)[i].ndof() > 4) &&
           (fabs( (*recVtxs)[i].z()) <= 24) &&
           ((*recVtxs)[i].position().rho() <= 2) ){
        nGoodVtx++;
	h_zPosGoodVtx->Fill((*recVtxs)[i].z());
      }
    }
  
  if (nGoodVtx > 0) IsVtxGood = 1;
  h_nGoodVtx->Fill(nGoodVtx);
  
  return;
}

void 
TopXana::DoElectronID(const edm::Event& iEvent){
  
  Handle< vector<Electron> > PatElectrons;
  iEvent.getByLabel("selectedPatElectrons", PatElectrons);

// begin electron loop                                                                                                                                   
  cout<<"------------new event --------------"<<endl;        
  for (unsigned int j=0; j<PatElectrons->size(); j++) {
    //Fill all electrons  
    //continue actually skips all the rest and moves on to the next loop entry
    //eta cuts
    if (fabs((*PatElectrons)[j].superCluster()->eta()) > 2.5) continue;
    if (fabs((*PatElectrons)[j].superCluster()->eta()) > 1.442 && fabs((*PatElectrons)[j].superCluster()->eta())< 1.566) continue;
    if (fabs((*PatElectrons)[j].superCluster()->eta()) < 1.442 && (*PatElectrons)[j].scSigmaIEtaIEta()<0.001) continue;
   
    // Spike clean: kTime || kWeird || kBad  
    if((*PatElectrons)[j].userInt("electronUserData:seedSeverityLevel")==3 || (*PatElectrons)[j].userInt("electronUserData:seedSeverityLevel")==4 
       || (*PatElectrons)[j].userInt("electronUserData:seedSeverityLevel")==5) continue;
   
    //coversion
    const reco::Track *eleTrk = (const reco::Track*)( (*PatElectrons)[j].gsfTrack().get());  
    const reco::HitPattern& p_inner = eleTrk->trackerExpectedHitsInner(); 
    int NumberOfExpectedInnerHits = p_inner.numberOfHits();
    //DOUBLE CHECK YURI HAS !=0 but twiki says
    //If NumberOfExpectedInnerHits is greater than 1, then the electron is 
    //vetoed as from a converted photon and should be rejected in an analysis looking for prompt photons.
    if (NumberOfExpectedInnerHits != 0) continue;
   
    // H2WW WP80 for barrel   
    edm::Handle<double> rhoH;
    iEvent.getByLabel(edm::InputTag("kt6PFJets","rho"),rhoH);
    double rho = *(rhoH.product());

    //NEED TO FIX ISOLATION -> RIGHT NOW LIK IN YURIS CODE
    //cout<<j<<" "<<(*PatElectrons)[j].userFloat("eleHcalTowerIsoPUDR03")<<endl;  
    /*edm::Handle<CaloTowerCollection> towerHandle;
      iEvent.getByLabel("towerMaker", towerHandle);
     const CaloTowerCollection* towers = towerHandle.product();
     EgammaTowerIsolation myHcalIsoDR03(0.3, 0., 0, -1, towers);
    */                                               
    //BARREL
    if (fabs((*PatElectrons)[j].superCluster()->eta()) < 1.4442 &&
	(max((float)0., (*PatElectrons)[j].dr03EcalRecHitSumEt() - 1) +  (*PatElectrons)[j].userFloat("eleHcalTowerIsoPUDR03") + 
	 (*PatElectrons)[j].dr03TkSumPt()  - rho*3.1415927*0.3*0.3)/(*PatElectrons)[j].pt() > 0.04) continue;
   
    
    if (fabs((*PatElectrons)[j].superCluster()->eta()) < 1.4442 &&  (*PatElectrons)[j].scSigmaIEtaIEta() > 0.01) continue;
    if (fabs((*PatElectrons)[j].superCluster()->eta()) < 1.4442 && fabs((*PatElectrons)[j].deltaPhiSuperClusterTrackAtVtx()) > 0.027) continue;
    if (fabs((*PatElectrons)[j].superCluster()->eta()) < 1.4442 && fabs((*PatElectrons)[j].deltaEtaSuperClusterTrackAtVtx()) > 0.005) continue;
    
    //ENDCAP
    if (fabs((*PatElectrons)[j].superCluster()->eta()) < 1.566 &&
	(max((float)0., (*PatElectrons)[j].dr03EcalRecHitSumEt() - 1) +  (*PatElectrons)[j].userFloat("eleHcalTowerIsoPUDR03") + 
	 (*PatElectrons)[j].dr03TkSumPt()  - rho*3.1415927*0.3*0.3)/(*PatElectrons)[j].pt() > 0.033) continue;
    
    if (fabs((*PatElectrons)[j].superCluster()->eta()) > 1.566 &&  (*PatElectrons)[j].scSigmaIEtaIEta() > 0.031) continue;
    if (fabs((*PatElectrons)[j].superCluster()->eta()) > 1.566 &&  fabs((*PatElectrons)[j].deltaPhiSuperClusterTrackAtVtx()) > 0.021) continue;
    if (fabs((*PatElectrons)[j].superCluster()->eta()) > 1.566 && fabs((*PatElectrons)[j].deltaEtaSuperClusterTrackAtVtx())  > 0.006) continue;



 if ((*PatElectrons)[j].pt()>20.0 && fabs((*PatElectrons)[j].eta())<2.1) {
        //passes electron Id                                                                                                                                           
          fGoodElectrons.push_back((*PatElectrons)[j]);
	  nGoodElectrons++;
 }


  } // pat electron loop     
 
  return;
}

void
TopXana::DoMuonID(const edm::Event& iEvent){

  Handle< vector<Muon> > PatMuons; 
  iEvent.getByLabel("selectedPatMuons", PatMuons);
  //also get the vertices for some cuts
   edm::Handle<reco::VertexCollection>  recVtxs;
  iEvent.getByLabel("goodOfflinePrimaryVertices", recVtxs);
  //Get rho for isolations 
  edm::Handle<double> rhoH;
  iEvent.getByLabel(edm::InputTag("kt6PFJets","rho"),rhoH);
  double rho = *(rhoH.product());
  for (unsigned int j=0; j<PatMuons->size(); j++) {
    
    double relIso = ((*PatMuons)[j].trackIso()  +
                     (*PatMuons)[j].ecalIso()   +
                     (*PatMuons)[j].hcalIso()- rho*3.1415927*0.3*0.3) / (*PatMuons)[j].pt();

    int    nValidHits        = -1;
    int    nValidTrackerHits = -1;
    int    nValidPixelHits   = -1;
    ////EVA ORIGINAL
    
    if ((*PatMuons)[j].globalTrack().isNonnull()) {
      nValidHits        = (*PatMuons)[j].globalTrack()->hitPattern().numberOfValidMuonHits();
      nValidTrackerHits = (*PatMuons)[j].globalTrack()->hitPattern().numberOfValidTrackerHits();
      nValidPixelHits   = (*PatMuons)[j].globalTrack()->hitPattern().numberOfValidPixelHits();
      }
    ///////DEAN
    /*if ((*PatMuons)[j].globalTrack().isNonnull()) {
      nValidHits = (*PatMuons)[j].globalTrack()->hitPattern().numberOfValidMuonHits();
    }

    if ((*PatMuons)[j].innerTrack().isNonnull()) {
      nValidTrackerHits = (*PatMuons)[j].innerTrack()->numberOfValidHits();
      nValidPixelHits   = (*PatMuons)[j].innerTrack()->hitPattern().pixelLayersWithMeasurement();
    }
    */
    int stations = 0;
    unsigned stationMask((*PatMuons)[j].stationMask());
    for(unsigned i=0; i < 8; ++i)
      if(stationMask & 1 << i) ++stations;

    if ((*PatMuons)[j].pt()>20.0 && fabs((*PatMuons)[j].eta())<2.1) {
     
       if((*PatMuons)[j].isGlobalMuon()  &&
	 (*PatMuons)[j].isTrackerMuon() && 
	 nValidHits                >  0 && 
	 nValidTrackerHits         > 10 &&
	 nValidPixelHits           >  0 &&
	 (*PatMuons)[j].globalTrack()->dxy((*recVtxs)[0].position())<0.02 &&
	 (*PatMuons)[j].globalTrack()->dz((*recVtxs)[0].position())<0.1 &&
	 //(*PatMuons)[j].dB()       <  0.02 &&
	 (*PatMuons)[j].globalTrack()->normalizedChi2() < 10 && 
	 stations                > 1) {

	if( relIso  <  0.1) { // is good muon
	  //fill cut muon for all good muons that pass reliso

	 fGoodMuons.push_back((*PatMuons)[j]);
	 nGoodMuons++;

	  
	} // reliso
	} // global, tracker muons
    } // eta pt of muon
  } // muon loop 
  
  return;
}
void
TopXana::DoPhotonID(const edm::Event& iEvent){
  Handle< vector<Photon> > PatPhotons;
  iEvent.getByLabel("selectedPatPhotons", PatPhotons);

  // Photon Selection
  for (size_t i = 0; i != PatPhotons->size(); ++i) {
    if ((*PatPhotons)[i].et()>20.0 && fabs((*PatPhotons)[i].superCluster()->position().eta())<1.45) {
        // tight photons
        if ( ((*PatPhotons)[i].ecalRecHitSumEtConeDR04()< 4.2+0.006*(*PatPhotons)[i].et()) &&
            ((*PatPhotons)[i].hcalTowerSumEtConeDR04()< 2.2+0.0025*(*PatPhotons)[i].et()) && 
            ((*PatPhotons)[i].hadronicOverEm() < 0.05) &&
            ((*PatPhotons)[i].trkSumPtHollowConeDR04() < 2+0.001*(*PatPhotons)[i].et()) &&
            ((*PatPhotons)[i].sigmaIetaIeta() <0.013) &&
            (!((*PatPhotons)[i].hasPixelSeed()))) { 
          fGoodPhotons.push_back((*PatPhotons)[i]);
	  nGoodPhotons++;
        }
      }
  }

  

  return;
}

void
TopXana::DoMETID(const edm::Event& iEvent){
  Handle< vector<MET> >      MetColl;
  iEvent.getByLabel("patMETsPFlow",  MetColl);
  fMET=(*MetColl)[0];
  
  
  return;
}
void
TopXana::DoCleanUp(vector<Muon >fGoodMuons,vector<Electron >fGoodElectrons,vector<Photon >fGoodPhotons,vector<Jet >fGoodJets){
   for (size_t im = 0; im != fGoodMuons.size(); ++im) {
    fCleanMuons.push_back(fGoodMuons[im] );
    nCleanMuons++;
  }
 // Keep non-overlapping electrons
  for (size_t ie = 0; ie != fGoodElectrons.size(); ++ie) {
    bool HasOverlap = false;
    TLorentzVector Electron(fGoodElectrons[ie].px(), fGoodElectrons[ie].py(), fGoodElectrons[ie].pz(), fGoodElectrons[ie].energy()); 
    for (size_t im = 0; im != fGoodMuons.size(); ++im) {
      TLorentzVector Muon(fGoodMuons[im].px(), fGoodMuons[im].py(), fGoodMuons[im].pz(), fGoodMuons[im].p()); 
      if (Muon.DeltaR( Electron ) < 0.4) {
        HasOverlap = true;
	if(_debug && HasOverlap) cout<<"Overlap Electron Muon with pt: "<<fGoodElectrons[ie].pt()<<" eta: "<<fGoodElectrons[ie].eta()<<endl;

      }
    }
    if (!HasOverlap) {
      fCleanElectrons.push_back( fGoodElectrons[ie]);
      nCleanElectrons++;
    }
  }

  // Keep non-overlapping photons
  for (size_t ip = 0; ip != fGoodPhotons.size(); ++ip) {
    bool HasOverlap = false;
    TLorentzVector Photon(fGoodPhotons[ip].px(), fGoodPhotons[ip].py(), fGoodPhotons[ip].pz(), fGoodPhotons[ip].energy()); 
    for (size_t ie = 0; ie != fGoodElectrons.size(); ++ie) {
      TLorentzVector Electron(fGoodElectrons[ie].px(), fGoodElectrons[ie].py(), fGoodElectrons[ie].pz(), fGoodElectrons[ie].energy());
      if (Electron.DeltaR(Photon) < 0.4) {
        HasOverlap = true;
      }
    }
    if (!HasOverlap) {
      fCleanPhotons.push_back( fGoodPhotons[ip] );
      nCleanPhotons++;
    }
  }
  // Keep non-overlapping jets
  nBJets=0;
  for (size_t ij = 0; ij != fGoodJets.size(); ++ij) {
    bool HasOverlap = false;
    TLorentzVector Jet(fGoodJets[ij].px(), fGoodJets[ij].py(), fGoodJets[ij].pz(), fGoodJets[ij].energy()); 
    for (size_t ie = 0; ie != fCleanElectrons.size(); ++ie) {
      TLorentzVector Electron(fCleanElectrons[ie].px(), fCleanElectrons[ie].py(), fCleanElectrons[ie].pz(), fCleanElectrons[ie].energy());
      if (Electron.DeltaR(Jet) < 0.4) {
        HasOverlap = true;
      }
    }
    for (size_t ip = 0; ip != fCleanPhotons.size(); ++ip) {
      TLorentzVector Photon(fCleanPhotons[ip].px(), fCleanPhotons[ip].py(), fCleanPhotons[ip].pz(), fCleanPhotons[ip].energy());
      if (Photon.DeltaR(Jet) < 0.4) {
        HasOverlap = true;
      }
    }
    for (size_t im = 0; im != fCleanMuons.size(); ++im) {
      TLorentzVector Muon(fCleanMuons[im].px(), fCleanMuons[im].py(), fCleanMuons[im].pz(), fCleanMuons[im].energy());
      if (Muon.DeltaR(Jet) < 0.4) {
        HasOverlap = true;
      }
    }

    if (!HasOverlap) {
      fCleanJets.push_back( fGoodJets[ij] );
      if (fGoodJets[ij].bDiscriminator("simpleSecondaryVertexHighEffBJetTags") > 1.74) nBJets++;
      nCleanJets++;
    }
  }

  return;
}
/*void 
TopXana::GetMCTruth(const edm::Event& iEvent){
  if(!_isData){
    
    Handle< vector<reco::GenParticle> > GenParticles; 
    iEvent.getByLabel("GenParticles", GenParticles);  
    for (unsigned int p=0; p<(*GenParticles).size(); p++) { 
      //cout<<p<<endl; 
      //use only that hard process
      if(p<200){
	pdgID[p]=(*GenParticles)[p].pdgId();
       
	MCpx[p]=(*GenParticles)[p].px();
	MCpy[p]=(*GenParticles)[p].py();
	MCpz[p]=(*GenParticles)[p].pz();
	MCe[p]=(*GenParticles)[p].energy();
	//cout<<MCpx[p]<<" "<<MCpy[p]<<" "<<MCpz[p]<<" "<<MCe[p]<<endl;
      }

     
    }
  }
  return;
}
*/
void
TopXana::MakeTriplets(vector<Jet >fCleanJets){
   const int nCombs = TMath::Factorial(nCleanJets)/(TMath::Factorial(nCleanJets - 3)*TMath::Factorial(3));
   for(int a=0; a<nCombs;a++){
 Triplet.push_back(std::vector<pat::Jet > ());
   }
     for (int i=0+0; i<nCleanJets-2; ++i) {
       for (int j=i+1; j<nCleanJets-1; ++j) {
	 for (int k=j+1; k<nCleanJets-0; ++k) {
	   TLorentzVector Jet1a; TLorentzVector Jet2a; TLorentzVector Jet3a;
	   //Jet1a.SetPxPyPzE(fCleanJets[i].px(),fCleanJets[i].py(), fCleanJets[i].pz(),  TMath::Sqrt( TMath::Power(fCleanJets[i].pt(), 2) + TMath::Power(fCleanJets[i].pz(), 2)+ TMath::Power(fCleanJets[i].mass(), 2))); 
	   //Jet2a.SetPxPyPzE(fCleanJets[j].px(),fCleanJets[j].py(), fCleanJets[j].pz(),  TMath::Sqrt( TMath::Power(fCleanJets[j].pt(), 2) + TMath::Power(fCleanJets[j].pz(), 2) + TMath::Power(fCleanJets[j].mass(), 2))); 
	   //Jet3a.SetPxPyPzE(fCleanJets[k].px(),fCleanJets[k].py(), fCleanJets[k].pz(),  TMath::Sqrt( TMath::Power(fCleanJets[k].pt(), 2) + TMath::Power(fCleanJets[k].pz(), 2) + TMath::Power(fCleanJets[k].mass(), 2))); 
	   
	   Jet1=fCleanJets[i]; Jet2=fCleanJets[j]; Jet3=fCleanJets[k];
	  //for the wprime find the highest pt jet that doesn't make it into the triplet
	   if (i!=0) AntiTripletHighestJet=fCleanJets[0];
	   if (i==0 && j!=1) AntiTripletHighestJet=fCleanJets[1];
	   if (i==0 && j==1 && k!=2) AntiTripletHighestJet=fCleanJets[2];
	   if (i==0 && j==1 && k==2) AntiTripletHighestJet=fCleanJets[3];
	   if(_debug){
	     cout <<nTriplets<<"  jet" << i <<" pt = "<< Jet1.pt() 
		  << ", jet" << j <<" pt = "<< Jet2.pt() 
		  << ", jet" << k <<" pt = "<< Jet3.pt()<<" pt4= "<<AntiTripletHighestJet.pt() << " tripletmass:" << (Jet1.p4()+Jet2.p4()+Jet3.p4()).mass()
		  <<" quad mass: "<<(Jet1.p4()+Jet2.p4()+Jet3.p4()+AntiTripletHighestJet.p4()).mass()<< endl;
	   }//debug
	   //save all the triplet infos and the jets -> eventually we might write this out in a tree
	  
	   Triplet[nTriplets].push_back(Jet1);
	   Triplet[nTriplets].push_back(Jet2);
	   Triplet[nTriplets].push_back(Jet3);

	   triplet_jet1pt[nTriplets]=Jet1.pt();
	   triplet_jet1px[nTriplets]=Jet1.px();
	   triplet_jet1py[nTriplets]=Jet1.py();
	   triplet_jet1pz[nTriplets]=Jet1.pz();
	   triplet_jet1e[nTriplets]=Jet1.energy();

	   triplet_jet2pt[nTriplets]=Jet2.pt();
	   triplet_jet2px[nTriplets]=Jet2.px();
	   triplet_jet2py[nTriplets]=Jet2.py();
	   triplet_jet2pz[nTriplets]=Jet2.pz();
	   triplet_jet2e[nTriplets]=Jet2.energy();

	   triplet_jet3pt[nTriplets]=Jet3.pt();
	   triplet_jet3px[nTriplets]=Jet3.px();
	   triplet_jet3py[nTriplets]=Jet3.py();
	   triplet_jet3pz[nTriplets]=Jet3.pz();
	   triplet_jet3e[nTriplets]=Jet3.energy();

	   

	   sumScalarPtTriplet.push_back(Jet1.pt()+Jet2.pt()+Jet3.pt());
	   massTriplet.push_back((Jet1.p4()+Jet2.p4()+Jet3.p4()).mass());
	   massQuad.push_back((Jet1.p4()+Jet2.p4()+Jet3.p4()+AntiTripletHighestJet.p4()).mass());
	   sumVectorPtTriplet.push_back((Jet1.p4()+Jet2.p4()+Jet3.p4()).pt());

	  
	   //massTriplet.push_back((Jet1a+Jet2a+Jet3a).M());
	   //sumScalarPtTriplet.push_back(Jet1a.Pt()+Jet2a.Pt()+Jet3a.Pt());



	   triplet_sumScalarPt[nTriplets]=Jet1.pt()+Jet2.pt()+Jet3.pt();
	   triplet_mass[nTriplets]=(Jet1.p4()+Jet2.p4()+Jet3.p4()).mass();
	   triplet_sumVectorPt[nTriplets]=(Jet1.p4()+Jet2.p4()+Jet3.p4()).pt();




	   nTriplets++;
	  
	   
	 }//k 
       }//j
     }//i
     return;
}

void
TopXana::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TopXana);
