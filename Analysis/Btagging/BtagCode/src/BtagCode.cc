  // -*- cs++ -*-
//
// Package:    BtagCode
// Class:      BtagCode
// 
/**\class BtagCode BtagCode.cc Btagging/BtagCode/src/BtagCode.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Claudia Seitz
//         Created:  Wed Jun 15 13:36:24 EDT 2011
// $Id: BtagCode.cc,v 1.3 2012/05/08 12:18:21 clseitz Exp $
//
//


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
#include "Btagging/BtagCode/interface/BtagCode.h"

#include "DataFormats/PatCandidates/interface/Electron.h" 
#include "DataFormats/PatCandidates/interface/Muon.h" 
#include "DataFormats/PatCandidates/interface/MET.h" 

#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include <iostream>
#include <algorithm>
#include <vector>

//
// class declaration
//


BtagCode::BtagCode(const edm::ParameterSet& iConfig)

{ _sumPtMin        = iConfig.getUntrackedParameter<double>("sumPtMin",         300.0);
  _debug           = iConfig.getUntrackedParameter<bool>  ("debug",            false);
  _outputFilename  = iConfig.getUntrackedParameter<string>("outputFilename",  "PatJets_test.root");
  _outputFilename2 = iConfig.getUntrackedParameter<string>("outputFilename2", "PatJets_testTree.root");
  _patJetType      = iConfig.getUntrackedParameter<string>("PatJetType",      "selectedPatJets");
  _njetsMin        = iConfig.getUntrackedParameter<int>   ("NjetsMin",         4);
  _njetsMax        = iConfig.getUntrackedParameter<int>   ("NjetsMax",         4);
  _etacut          = iConfig.getUntrackedParameter<double>("etacut",           3.0); 
  _jetptcut        = iConfig.getUntrackedParameter<double>("jetptcut",         20.0);
  _nbTagsMin       = iConfig.getUntrackedParameter<int>   ("nbTagsMin",        0);
  _nbTagsMax       = iConfig.getUntrackedParameter<int>   ("nbTagsMax",        1000);
  _isData          = iConfig.getUntrackedParameter<bool>  ("isData",           true);
  _noTripletBtag   = iConfig.getUntrackedParameter<bool>  ("noTripletBtag",    false);
  _nTripletBtagsMin= iConfig.getUntrackedParameter<int>   ("nTripletBtagsMin", 0);
  _nTripletBtagsMax= iConfig.getUntrackedParameter<int>   ("nTripletBtagsMax", 1000);
  _doBtagEff       = iConfig.getUntrackedParameter<bool>   ("doBtagEff", true);
   //now do what ever initialization is needed

}


BtagCode::~BtagCode()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//
// ------------ method called once each job just before starting event loop  ------------
void 
BtagCode::beginJob()
{
  //create output file
  outputFile = new TFile(_outputFilename.data(),"recreate");
  //initialize event counter
  nEvents = 0;
  //define btagging algos
  tagger_name.push_back("TCHE");
  tagger_name.push_back("TCHP");
  tagger_name.push_back("SSVHE");
  tagger_name.push_back("SSVHP");
    tagger_name.push_back("JP");
  tagger_name.push_back("CSV");
  
  //define btagging algos and working points
  op_name.push_back("TCHEL"); operating_point.push_back(1.70);
  op_name.push_back("TCHEM"); operating_point.push_back(3.30);
  op_name.push_back("TCHPM"); operating_point.push_back(1.93);
  op_name.push_back("TCHPT"); operating_point.push_back(3.41);
  op_name.push_back("SSVHEM"); operating_point.push_back(1.74);
  op_name.push_back("SSVHET"); operating_point.push_back(3.05);
  op_name.push_back("SSVHPT"); operating_point.push_back(2.00);
  op_name.push_back("JPL"); operating_point.push_back(0.275);
  op_name.push_back("JPM"); operating_point.push_back(0.545);
  op_name.push_back("JPT"); operating_point.push_back(0.790);
  op_name.push_back("CSVL"); operating_point.push_back(0.244);
  op_name.push_back("CSVM"); operating_point.push_back(0.679);
  op_name.push_back("CSVT"); operating_point.push_back(0.898);
  op_name.push_back("none");
  //define flavors for the btagging
  flavor_name.push_back("b");
  flavor_name.push_back("c");
  flavor_name.push_back("udsg");
  //to figure out if the bjet in the triplet is usually the hardest
 MCbTriplet= new TH1F("MCbTriplet","MCbTriplet",3,0,3);
  //histograms for the btagging discriminants
  for(float iTagger=0; iTagger<tagger_name.size(); iTagger++)
   {
    for(int iFlavor=0; iFlavor<3; iFlavor++)
       { 
	  discriminator_tagalgo_flavor.push_back(std::vector<TH1F*> ());
	 std::stringstream sdisc;
	 sdisc<<"discriminator_"<<tagger_name[iTagger]<<"_"<<flavor_name[iFlavor];

       	 if(iTagger==0 || iTagger==1) discriminator_tagalgo_flavor[iTagger].push_back(new TH1F((sdisc.str()).c_str(),(sdisc.str()).c_str(), 300, -30, 30));
	 if(iTagger==2 || iTagger==3) discriminator_tagalgo_flavor[iTagger].push_back(new TH1F((sdisc.str()).c_str(),(sdisc.str()).c_str(), 300, -6, 6));
	 if(iTagger==4) discriminator_tagalgo_flavor[iTagger].push_back(new TH1F((sdisc.str()).c_str(),(sdisc.str()).c_str(), 300, -6, 6));
	 if(iTagger==5) discriminator_tagalgo_flavor[iTagger].push_back(new TH1F((sdisc.str()).c_str(),(sdisc.str()).c_str(), 300, -6, 6));
       }
   }
  //define stuff for the different operating points
 
  for(float iOP=0; iOP<op_name.size(); iOP++)
    {
      jet_pt_tagger_flavor.push_back(std::vector<TH1F*> ());
      jet_pt_1p2_2p4_tagger_flavor.push_back(std::vector<TH1F*> ());
      jet_pt_l1p2_tagger_flavor.push_back(std::vector<TH1F*> ());
      jet_eta_tagger_flavor.push_back(std::vector<TH1F*> ());
      
      jet_eta_pt_tagger_flavor.push_back(std::vector<TH2F*> ());
      
      triplet_jet_pt_tagger_flavor.push_back(std::vector<TH1F*> ());
      triplet_sumpt_tagger_flavor.push_back(std::vector<TH1F*> ());
      triplet_mass_tagger_flavor.push_back(std::vector<TH1F*> ());
      
      for(int iFlavor=0; iFlavor<3; iFlavor++)
	{
	  std::stringstream sjetpt,sjetpt_1p2_2p4,sjetpt_l1p2,sjeteta,sjetetapt,sTagFlav_Tjetpt,sTagFlav_Tmass,sTagFlav_Tsumpt;
	  sjetpt<<"jet_pt_"<<op_name[iOP]<<"_"<<flavor_name[iFlavor];
	  sjetpt_1p2_2p4<<"jet_pt_1p2_2p4_"<<op_name[iOP]<<"_"<<flavor_name[iFlavor];
	  sjetpt_l1p2<<"jet_pt_l1p2_"<<op_name[iOP]<<"_"<<flavor_name[iFlavor];
	  sjeteta<<"jet_eta_"<<op_name[iOP]<<"_"<<flavor_name[iFlavor];
	  sjetetapt<<"jet_2D_eta_pt_"<<op_name[iOP]<<"_"<<flavor_name[iFlavor];
	  sTagFlav_Tjetpt<<"triplet_jet_pt_"<<op_name[iOP]<<"_"<<flavor_name[iFlavor];
	  sTagFlav_Tsumpt<<"triplet_sumpt_"<<op_name[iOP]<<"_"<<flavor_name[iFlavor];
	  sTagFlav_Tmass<<"triplet_mass_"<<op_name[iOP]<<"_"<<flavor_name[iFlavor];
	  
	  jet_pt_tagger_flavor[iOP].push_back(new TH1F(( sjetpt.str()).c_str(),(sjetpt.str()).c_str(), 500, 0, 1000));
	  jet_pt_1p2_2p4_tagger_flavor[iOP].push_back(new TH1F(( sjetpt_1p2_2p4.str()).c_str(),(sjetpt_1p2_2p4.str()).c_str(), 500, 0, 1000));
	  jet_pt_l1p2_tagger_flavor[iOP].push_back(new TH1F(( sjetpt_l1p2.str()).c_str(),(sjetpt_l1p2.str()).c_str(), 500, 0, 1000));
	  jet_eta_tagger_flavor[iOP].push_back(new TH1F(( sjeteta.str()).c_str(),(sjeteta.str()).c_str(), 200, 0, 4));

	  jet_eta_pt_tagger_flavor[iOP].push_back(new TH2F(( sjetetapt.str()).c_str(),(sjetetapt.str()).c_str(), 200, 0, 4,500, 0, 1000));
	  triplet_jet_pt_tagger_flavor[iOP].push_back(new TH1F((sTagFlav_Tjetpt.str()).c_str(),(sTagFlav_Tjetpt.str()).c_str(), 500, 0, 1000));
	  triplet_sumpt_tagger_flavor[iOP].push_back(new TH1F((sTagFlav_Tsumpt.str()).c_str(),(sTagFlav_Tsumpt.str()).c_str(), 500, 0, 1000));
	  triplet_mass_tagger_flavor[iOP].push_back(new TH1F((sTagFlav_Tmass.str()).c_str(),(sTagFlav_Tmass.str()).c_str(), 500, 0, 1000));
	  
	  
	  jet_pt_tagger_flavor[iOP][iFlavor]->Sumw2();
	  jet_pt_1p2_2p4_tagger_flavor[iOP][iFlavor]->Sumw2();
	  jet_pt_l1p2_tagger_flavor[iOP][iFlavor]->Sumw2();
	  jet_eta_tagger_flavor[iOP][iFlavor]->Sumw2();
	  jet_eta_pt_tagger_flavor[iOP][iFlavor]->Sumw2();
	  triplet_jet_pt_tagger_flavor[iOP][iFlavor]->Sumw2();
	  triplet_sumpt_tagger_flavor[iOP][iFlavor]->Sumw2();
	  triplet_mass_tagger_flavor[iOP][iFlavor]->Sumw2();
	}
    }

  
}


// ------------ method called for each event  ------------
void
BtagCode::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
   //clear out our own jet collection
   fGoodJets.clear(); fCleanJets.clear(); //use this if we decide to do clean up
   nGoodJets=0; nCleanJets=0;
   //clear the mcbcount
   MCbcount=0;
   //clear the triplet variables
   Triplet.clear();
   nMCBtagTriplet.clear();
   sumScalarPtTriplet.clear();
   sumVectorPtTriplet.clear();
   massTriplet.clear();
   //that doesn't work for pat jets so no clearing and hope it doesn do anything
   //Jet1.clear(); Jet2.clear(); Jet3.clear();
   nTriplets=0; q=0; //basically just triplet counting
  
   //get event info
   run   = iEvent.id().run();
   event = iEvent.id().event();
   lumis = iEvent.id().luminosityBlock();
  
   
  
   //this does the JetID -> see my function below
   DoJetID(iEvent);
  
   //call the btageff function which makes plots and counts the number of b jets in the event
   BtagEff(fCleanJets, nCleanJets);
  

   //put some more checks in 
   bool enoughGoodJets=true; 
   //We want to know efficiencys in MC so select events with at least one original bjet
   if(MCbcount<1) enoughGoodJets=false;
   if (_njetsMin  < 3) enoughGoodJets=false;
   //Need at leat N Jets                                                                       
   if (nGoodJets < _njetsMin) enoughGoodJets=false;
   //Need no more than N Jets ;)                                                          
   if (nGoodJets > _njetsMax) enoughGoodJets=false;
   //find sumPt from jet data                                                             
   if (enoughGoodJets) nGoodJets = nGoodJets;
   

   //go into the triplet making 
   if(enoughGoodJets){
     //call function that makes the triplets
     MakeTriplets(fCleanJets);

     BtagEffTriplet(Triplet,nMCBtagTriplet,sumScalarPtTriplet,sumVectorPtTriplet,massTriplet);
     //now lets make some btag efficiencys within the triplets
    
   }
}



// ------------ method called once each job just after ending the event loop  ------------
void 
BtagCode::endJob() 
{
  outputFile->cd();
  outputFile->mkdir("Btag");
  outputFile->cd("Btag");
  MCbTriplet->Write();
  cout<<"1"<<endl;
      for(float iTagger=0; iTagger<tagger_name.size();iTagger++)
	{
	  for(int iFlavor=0; iFlavor<3; iFlavor++)
	    {
	      discriminator_tagalgo_flavor[iTagger][iFlavor]->Write();
	      
 	    }
	}
      //write out the different op points
  cout<<"2"<<endl;
      for(float iOP=0; iOP<op_name.size();iOP++)
	{
	  for(int iFlavor=0; iFlavor<3; iFlavor++)
	    {
	      jet_pt_tagger_flavor[iOP][iFlavor]->Write();
	      jet_pt_1p2_2p4_tagger_flavor[iOP][iFlavor]->Write();
	      jet_pt_l1p2_tagger_flavor[iOP][iFlavor]->Write();
	       jet_eta_tagger_flavor[iOP][iFlavor]->Write();
	       jet_eta_pt_tagger_flavor[iOP][iFlavor]->Write();
	       triplet_jet_pt_tagger_flavor[iOP][iFlavor]->Write();
	       triplet_sumpt_tagger_flavor[iOP][iFlavor]->Write();
	       triplet_mass_tagger_flavor[iOP][iFlavor]->Write();

	    }
	}
      /*     for(float iTagger=0; iTagger<tagger_name.size();iTagger++)
   {
     for(int iFlavor=0; iFlavor<3; iFlavor++)
       {
         triplet_jet_pt_tagger_flavor[iTagger][iFlavor]->Write();
         triplet_sumpt_tagger_flavor[iTagger][iFlavor]->Write();
         triplet_mass_tagger_flavor[iTagger][iFlavor]->Write();
       }
       }*/

}

// ------------ method called when starting to processes a run  ------------
void 
BtagCode::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
BtagCode::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
BtagCode::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
BtagCode::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BtagCode::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
void BtagCode::MakeTriplets(std::vector<pat::Jet >fCleanJets){
 const int nCombs = TMath::Factorial(nGoodJets)/(TMath::Factorial(nGoodJets - 3)*TMath::Factorial(3));
     for (int i=0+0; i<nGoodJets-2; i++) {
       for (int j=i+1; j<nGoodJets-1; j++) {
	 for (int k=j+1; k<nGoodJets-0; k++) {
	   Jet Jet1; Jet Jet2; Jet Jet3;
	   Jet1=fCleanJets[i]; Jet2=fCleanJets[j]; Jet3=fCleanJets[k];
	  
	   if(_debug){
	     cout <<nTriplets<<"  jet" << i <<" pt = "<< Jet1.pt() 
		  << ", jet" << j <<" pt = "<< Jet2.pt() 
		  << ", jet" << k <<" pt = "<< Jet3.pt() << endl;
	   }//debug
	   //save all the triplet infos and the jets -> eventually we might write this out in a tree
	   Triplet.push_back(vector<Jet > ());
	   Triplet[nTriplets].push_back(Jet1);
	   Triplet[nTriplets].push_back(Jet2);
	   Triplet[nTriplets].push_back(Jet3);
	   sumScalarPtTriplet.push_back(Jet1.pt()+Jet2.pt()+Jet3.pt());
	   massTriplet.push_back((Jet1.p4()+Jet2.p4()+Jet3.p4()).mass());
	   sumVectorPtTriplet.push_back((Jet1.p4()+Jet2.p4()+Jet3.p4()).mass());
	   nTriplets++;
	   int MCbcountTriplet=0;
	   if (_doBtagEff){
	     if(fabs(Jet1.partonFlavour())==5) {
	       MCbcountTriplet++;
	       MCbTriplet->Fill(0);
	     }
	     if(fabs( Jet2.partonFlavour())==5){
	       MCbcountTriplet++;
	       MCbTriplet->Fill(1);
	     }
	     if(fabs(Jet3.partonFlavour())==5){
	       MCbcountTriplet++;
	       MCbTriplet->Fill(2);
	     }
	     nMCBtagTriplet.push_back(MCbcountTriplet);
	     }
	   
	 }//k 
       }//j
     }//i
     return;
}


void BtagCode::BtagEffTriplet(std::vector <std::vector<pat::Jet > > Triplet, std::vector<double> nMCBtagTriplet,std::vector<double> sumScalarPtTriplet, std::vector<double> sumVectorPtTriplet, std::vector<double> massTriplet)
{ for(int iT=0; iT<nTriplets; iT++){
	if(nMCBtagTriplet[iT]==1){
	  //only go through the triplet if we had exactly one b-jet in there
	  for(int iJ=0; iJ<3; iJ++){  
	    //Triplets are pt ordered starting with the highest jet at 0
	    //get b  discriminators from all the jets and the pt
	    double flavor_Triplet;
	    double d_bDis_TCHE_Triplet, d_bDis_TCHP_Triplet, d_bDis_SSVHE_Triplet,d_bDis_SSVHP_Triplet, d_pt_Triplet;
	    double  d_bDis_JP_Triplet, d_bDis_CSV_Triplet;

	    flavor_Triplet = fabs( Triplet[iT][iJ].partonFlavour() );
	    d_bDis_TCHP_Triplet=Triplet[iT][iJ].bDiscriminator("trackCountingHighPurBJetTags");
	    d_bDis_TCHE_Triplet=Triplet[iT][iJ].bDiscriminator("trackCountingHighEffBJetTags");
	    d_bDis_SSVHE_Triplet = Triplet[iT][iJ].bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
	    d_bDis_SSVHP_Triplet = Triplet[iT][iJ].bDiscriminator("simpleSecondaryVertexHighPurBJetTags");
	    d_bDis_JP_Triplet = Triplet[iT][iJ].bDiscriminator("jetProbabilityBJetTags");
	    d_bDis_CSV_Triplet = Triplet[iT][iJ].bDiscriminator("combinedSecondaryVertexBJetTags");
	    d_pt_Triplet=Triplet[iT][iJ].pt();
	    
	    
	    //do btag eff -> require a btag in the triplet
	    
	    if (flavor_Triplet==5){
	      triplet_jet_pt_tagger_flavor[13][0]->Fill(d_pt_Triplet);
	      triplet_sumpt_tagger_flavor[13][0]->Fill(sumScalarPtTriplet[iT]);
	      triplet_mass_tagger_flavor[13][0]->Fill(massTriplet[iT]);
	    }
	    if (flavor_Triplet==4){
	      triplet_jet_pt_tagger_flavor[13][1]->Fill(d_pt_Triplet);
	      triplet_sumpt_tagger_flavor[13][1]->Fill(sumScalarPtTriplet[iT]);
	      triplet_mass_tagger_flavor[13][1]->Fill(massTriplet[iT]);
	    }
	    
	    if (flavor_Triplet==21 || (flavor_Triplet >0 && flavor_Triplet<4))
	      {
		triplet_jet_pt_tagger_flavor[13][2]->Fill(d_pt_Triplet); 
		triplet_sumpt_tagger_flavor[13][2]->Fill(sumScalarPtTriplet[iT]); 
		triplet_mass_tagger_flavor[13][2]->Fill(massTriplet[iT]);
	      }
	    
		
		//TCHEL
		if (d_bDis_TCHE_Triplet>operating_point[0]){
		  if (flavor_Triplet==5){
		    triplet_jet_pt_tagger_flavor[0][0]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[0][0]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[0][0]->Fill(massTriplet[iT]);
		  }
		  if (flavor_Triplet==4){
		    triplet_jet_pt_tagger_flavor[0][1]->Fill(d_pt_Triplet);
		     triplet_sumpt_tagger_flavor[0][1]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[0][1]->Fill(massTriplet[iT]);
		  }
		  if (flavor_Triplet==21 || (flavor_Triplet >0 && flavor_Triplet<4)){
		    triplet_jet_pt_tagger_flavor[0][2]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[0][2]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[0][2]->Fill(massTriplet[iT]);
		  }
		}
		//TCHEM
		if (d_bDis_TCHE_Triplet>operating_point[1]){
		  if (flavor_Triplet==5){
		    triplet_jet_pt_tagger_flavor[1][0]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[1][0]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[1][0]->Fill(massTriplet[iT]);
		  }
		  if (flavor_Triplet==4){
		    triplet_jet_pt_tagger_flavor[1][1]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[1][1]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[1][1]->Fill(massTriplet[iT]);
		  }
		  if (flavor_Triplet==21 || (flavor_Triplet >0 && flavor_Triplet<4)){
		    triplet_jet_pt_tagger_flavor[1][2]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[1][2]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[1][2]->Fill(massTriplet[iT]);
		  }
		}
		//TCHPM
		if (d_bDis_TCHP_Triplet>operating_point[2]){
		  if (flavor_Triplet==5){
		    triplet_jet_pt_tagger_flavor[2][0]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[2][0]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[2][0]->Fill(massTriplet[iT]);
		  }
		  if (flavor_Triplet==4){
		    triplet_jet_pt_tagger_flavor[2][1]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[2][1]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[2][1]->Fill(massTriplet[iT]);
		  }
		  if (flavor_Triplet==21 || (flavor_Triplet >0 && flavor_Triplet<4)){
		    triplet_jet_pt_tagger_flavor[2][2]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[2][2]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[2][2]->Fill(massTriplet[iT]);
		  }
		}
		
		//TCHPT
		if (d_bDis_TCHP_Triplet>operating_point[3]){
		  if (flavor_Triplet==5){
		    triplet_jet_pt_tagger_flavor[3][0]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[3][0]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[3][0]->Fill(massTriplet[iT]);
		  }
		  if (flavor_Triplet==4){
		    triplet_jet_pt_tagger_flavor[3][1]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[3][1]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[3][1]->Fill(massTriplet[iT]);
		  }
		  if (flavor_Triplet==21 || (flavor_Triplet >0 && flavor_Triplet<4)){
		    triplet_jet_pt_tagger_flavor[3][2]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[3][2]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[3][2]->Fill(massTriplet[iT]);
		  }
		}
		
		//SSVHEM
		if (d_bDis_SSVHE_Triplet>operating_point[4]){
		  if (flavor_Triplet==5){
		    triplet_jet_pt_tagger_flavor[4][0]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[4][0]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[4][0]->Fill(massTriplet[iT]);
		  }
		  if (flavor_Triplet==4){
		    triplet_jet_pt_tagger_flavor[4][1]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[4][1]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[4][1]->Fill(massTriplet[iT]);
		  }
		  if (flavor_Triplet==21 || (flavor_Triplet >0 && flavor_Triplet<4)){
		    triplet_jet_pt_tagger_flavor[4][2]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[4][2]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[4][2]->Fill(massTriplet[iT]);
		  }
		}
		
		//SSVHET
		if (d_bDis_SSVHE_Triplet>operating_point[5]){
		  if (flavor_Triplet==5){
		    triplet_jet_pt_tagger_flavor[5][0]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[5][0]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[5][0]->Fill(massTriplet[iT]);
		  }
		  if (flavor_Triplet==4){
		    triplet_jet_pt_tagger_flavor[5][1]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[5][1]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[5][1]->Fill(massTriplet[iT]);
		  }
		  if (flavor_Triplet==21 || (flavor_Triplet >0 && flavor_Triplet<4)){
		    triplet_jet_pt_tagger_flavor[5][2]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[5][2]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[5][2]->Fill(massTriplet[iT]);
		  }
		}
		
		//SSVHPT
		if (d_bDis_SSVHP_Triplet>operating_point[6]){
		  if (flavor_Triplet==5){
		    triplet_jet_pt_tagger_flavor[6][0]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[6][0]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[6][0]->Fill(massTriplet[iT]);
		  }
		  if (flavor_Triplet==4){
		    triplet_jet_pt_tagger_flavor[6][1]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[6][1]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[6][1]->Fill(massTriplet[iT]);
		  }
		  if (flavor_Triplet==21 || (flavor_Triplet >0 && flavor_Triplet<4)){
		    triplet_jet_pt_tagger_flavor[6][2]->Fill(d_pt_Triplet);
		    triplet_sumpt_tagger_flavor[6][2]->Fill(sumScalarPtTriplet[iT]);
		    triplet_mass_tagger_flavor[6][2]->Fill(massTriplet[iT]);
		  }
		}
		//JPL
		if (d_bDis_JP_Triplet>operating_point[7]){
                  if (flavor_Triplet==5){
                    triplet_jet_pt_tagger_flavor[7][0]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[7][0]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[7][0]->Fill(massTriplet[iT]);
                  }
                  if (flavor_Triplet==4){
                    triplet_jet_pt_tagger_flavor[7][1]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[7][1]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[7][1]->Fill(massTriplet[iT]);
                  }
                  if (flavor_Triplet==21 || (flavor_Triplet >0 && flavor_Triplet<4)){
                    triplet_jet_pt_tagger_flavor[7][2]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[7][2]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[7][2]->Fill(massTriplet[iT]);
                  }
                }

		//JPM                                                                                                                                             
		if (d_bDis_JP_Triplet>operating_point[8]){
                  if (flavor_Triplet==5){
                    triplet_jet_pt_tagger_flavor[8][0]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[8][0]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[8][0]->Fill(massTriplet[iT]);
                  }
                  if (flavor_Triplet==4){
                    triplet_jet_pt_tagger_flavor[8][1]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[8][1]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[8][1]->Fill(massTriplet[iT]);
                  }
                  if (flavor_Triplet==21 || (flavor_Triplet >0 && flavor_Triplet<4)){
                    triplet_jet_pt_tagger_flavor[8][2]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[8][2]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[8][2]->Fill(massTriplet[iT]);
                  }
                }
		//JPL                                                                                                                                 
		if (d_bDis_JP_Triplet>operating_point[9]){
                  if (flavor_Triplet==5){
                    triplet_jet_pt_tagger_flavor[9][0]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[9][0]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[9][0]->Fill(massTriplet[iT]);
                  }
                  if (flavor_Triplet==4){
                    triplet_jet_pt_tagger_flavor[9][1]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[9][1]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[9][1]->Fill(massTriplet[iT]);
                  }
                  if (flavor_Triplet==21 || (flavor_Triplet >0 && flavor_Triplet<4)){
                    triplet_jet_pt_tagger_flavor[9][2]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[9][2]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[9][2]->Fill(massTriplet[iT]);
                  }
                }

 

		//CSVL                                                                                                                                         
		if (d_bDis_CSV_Triplet>operating_point[10]){
                  if (flavor_Triplet==5){
                    triplet_jet_pt_tagger_flavor[10][0]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[10][0]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[10][0]->Fill(massTriplet[iT]);
                  }
                  if (flavor_Triplet==4){
                    triplet_jet_pt_tagger_flavor[10][1]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[10][1]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[10][1]->Fill(massTriplet[iT]);
                  }
                  if (flavor_Triplet==21 || (flavor_Triplet >0 && flavor_Triplet<4)){
                    triplet_jet_pt_tagger_flavor[10][2]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[10][2]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[10][2]->Fill(massTriplet[iT]);
                  }
                }
		//CSVM                                                                                                                                         
                if (d_bDis_CSV_Triplet>operating_point[11]){
                  if (flavor_Triplet==5){
                    triplet_jet_pt_tagger_flavor[11][0]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[11][0]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[11][0]->Fill(massTriplet[iT]);
                  }
                  if (flavor_Triplet==4){
                    triplet_jet_pt_tagger_flavor[11][1]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[11][1]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[11][1]->Fill(massTriplet[iT]);
                  }
                  if (flavor_Triplet==21 || (flavor_Triplet >0 && flavor_Triplet<4)){
                    triplet_jet_pt_tagger_flavor[11][2]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[11][2]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[11][2]->Fill(massTriplet[iT]);
                  }
                }

		//CSVT                                                                                                               
                if (d_bDis_CSV_Triplet>operating_point[12]){
                  if (flavor_Triplet==5){
                    triplet_jet_pt_tagger_flavor[12][0]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[12][0]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[12][0]->Fill(massTriplet[iT]);
                  }
                  if (flavor_Triplet==4){
                    triplet_jet_pt_tagger_flavor[12][1]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[12][1]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[12][1]->Fill(massTriplet[iT]);
                  }
                  if (flavor_Triplet==21 || (flavor_Triplet >0 && flavor_Triplet<4)){
                    triplet_jet_pt_tagger_flavor[12][2]->Fill(d_pt_Triplet);
                    triplet_sumpt_tagger_flavor[12][2]->Fill(sumScalarPtTriplet[iT]);
                    triplet_mass_tagger_flavor[12][2]->Fill(massTriplet[iT]);
                  }
                }

	    }
	    }
	    }
  return;

}

void BtagCode::DoJetID(const edm::Event& iEvent){
   // Jet Handle  
  Handle< vector<Jet> > PatJets; 
  iEvent.getByLabel(_patJetType, PatJets); 
   //lets do some JetID
  
  for (unsigned int j=0; j<PatJets->size(); j++) {
     if (_debug && j==0){
       std::cout<<"--------------run: "<<run<<"--event: "<<event<<"--lumi: "<<lumis<<"---------------"<<endl;
       std::cout << "Number of PatJets: " << PatJets->size() << std::endl;
     }
     
     // Choose jets based on pt and abs(eta)
     if ((*PatJets)[j].pt()        > float(_jetptcut)  &&
	 fabs((*PatJets)[j].eta()) < float(_etacut))
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
	   fCleanJets.push_back((*PatJets)[j]);//for now good and clean jets are the same

	   nGoodJets++; 
	   nCleanJets++; 
	   
	 }//JetID
       }//JetKinematics
   }//JetLoop
 if (_debug) std::cout << "Found "<< nGoodJets << " Jets" << std::endl;
return;
}


//does the MC btag efficiencys as function of jet pt and jet eta
void BtagCode::BtagEff(std::vector<pat::Jet >fCleanJets, int nCleanJets){
  for (int j=0; j<nCleanJets; j++){
    double flavor;
    double d_bDis_TCHE, d_bDis_TCHP, d_bDis_SSVHE,d_bDis_SSVHP, d_pt, d_eta;
    double  d_bDis_JP, d_bDis_CSV;
    flavor = fabs(fCleanJets[j].partonFlavour() );
    d_bDis_TCHE=fCleanJets[j].bDiscriminator("trackCountingHighEffBJetTags");
    d_bDis_TCHP=fCleanJets[j].bDiscriminator("trackCountingHighPurBJetTags");
    d_bDis_SSVHE = fCleanJets[j].bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
    d_bDis_SSVHP = fCleanJets[j].bDiscriminator("simpleSecondaryVertexHighPurBJetTags");
    d_bDis_JP = fCleanJets[j].bDiscriminator("jetProbabilityBJetTags");
    d_bDis_CSV = fCleanJets[j].bDiscriminator("combinedSecondaryVertexBJetTags");

    d_pt=fCleanJets[j].pt();
    d_eta=fabs(fCleanJets[j].eta());
    //    cout<<d_bDis_TCHP<<" "<< d_bDis_TCHE<<" "<<d_bDis_SSVHE<<" "<<d_bDis_SSVHP<<" "<<d_pt<<" "<<d_bDis_CSV<<" "<<d_bDis_JP <<endl;
    //cout<<MCbcount<<endl;
    if (flavor==5){
      //count number of bjets in the event
      jet_pt_tagger_flavor[13][0]->Fill(d_pt);
      if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[13][0]->Fill(d_pt);
      if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[13][0]->Fill(d_pt);
      jet_eta_tagger_flavor[13][0]->Fill(d_eta);
      jet_eta_pt_tagger_flavor[13][0]->Fill(d_eta,d_pt);
      MCbcount++;
      discriminator_tagalgo_flavor[0][0]->Fill(d_bDis_TCHE);
      discriminator_tagalgo_flavor[1][0]->Fill(d_bDis_TCHP);
      discriminator_tagalgo_flavor[2][0]->Fill(d_bDis_SSVHE);
      discriminator_tagalgo_flavor[3][0]->Fill(d_bDis_SSVHP);
      discriminator_tagalgo_flavor[4][0]->Fill(d_bDis_JP);
      discriminator_tagalgo_flavor[5][0]->Fill(d_bDis_CSV);
    }
    if (flavor==4){
      jet_pt_tagger_flavor[13][1]->Fill(d_pt);
      if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[13][1]->Fill(d_pt);
      if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[13][1]->Fill(d_pt);
      jet_eta_tagger_flavor[13][1]->Fill(d_eta);
jet_eta_pt_tagger_flavor[13][1]->Fill(d_eta,d_pt);
      discriminator_tagalgo_flavor[0][1]->Fill(d_bDis_TCHE);
      discriminator_tagalgo_flavor[1][1]->Fill(d_bDis_TCHP);
      discriminator_tagalgo_flavor[2][1]->Fill(d_bDis_SSVHE);
      discriminator_tagalgo_flavor[3][1]->Fill(d_bDis_SSVHP);
      discriminator_tagalgo_flavor[4][1]->Fill(d_bDis_JP);
      discriminator_tagalgo_flavor[5][1]->Fill(d_bDis_CSV);

    }
    if (flavor==21 || (flavor >0 && flavor<4)){
      if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[13][2]->Fill(d_pt);
      if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[13][2]->Fill(d_pt);
      jet_pt_tagger_flavor[13][2]->Fill(d_pt);
      jet_eta_tagger_flavor[13][2]->Fill(d_eta);
jet_eta_pt_tagger_flavor[13][2]->Fill(d_eta,d_pt);
      discriminator_tagalgo_flavor[0][2]->Fill(d_bDis_TCHE);
      discriminator_tagalgo_flavor[1][2]->Fill(d_bDis_TCHP);
      discriminator_tagalgo_flavor[2][2]->Fill(d_bDis_SSVHE);
      discriminator_tagalgo_flavor[3][2]->Fill(d_bDis_SSVHP);
      discriminator_tagalgo_flavor[4][2]->Fill(d_bDis_JP);
      discriminator_tagalgo_flavor[5][2]->Fill(d_bDis_CSV);

    }
    
    //differen operating points
    //TCHEL
    if (d_bDis_TCHE>operating_point[0]){
      if (flavor==5){
	jet_pt_tagger_flavor[0][0]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[0][0]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[0][0]->Fill(d_pt);
	jet_eta_tagger_flavor[0][0]->Fill(d_eta);
jet_eta_pt_tagger_flavor[0][0]->Fill(d_eta,d_pt);
      }
      if (flavor==4){
	jet_pt_tagger_flavor[0][1]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[0][1]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[0][1]->Fill(d_pt);
	jet_eta_tagger_flavor[0][1]->Fill(d_eta);
jet_eta_pt_tagger_flavor[0][1]->Fill(d_eta,d_pt);
      }
      if (flavor==21 || (flavor >0 && flavor<4)){
	jet_pt_tagger_flavor[0][2]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[0][2]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[0][2]->Fill(d_pt);
	jet_eta_tagger_flavor[0][2]->Fill(d_eta); 
	jet_eta_pt_tagger_flavor[0][2]->Fill(d_eta,d_pt);
      }
    }
    //TCHEM
    if (d_bDis_TCHE>operating_point[1]){
      if (flavor==5){
	jet_pt_tagger_flavor[1][0]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[1][0]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[1][0]->Fill(d_pt);
	jet_eta_tagger_flavor[1][0]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[1][0]->Fill(d_eta,d_pt);
      }
      if (flavor==4){
	jet_pt_tagger_flavor[1][1]->Fill(d_pt);
if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[1][1]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[1][1]->Fill(d_pt);
	jet_eta_tagger_flavor[1][1]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[1][1]->Fill(d_eta,d_pt);
      }
      if (flavor==21 || (flavor >0 && flavor<4)){
	jet_pt_tagger_flavor[1][2]->Fill(d_pt);
if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[1][2]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[1][2]->Fill(d_pt);
	jet_eta_tagger_flavor[1][2]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[1][2]->Fill(d_eta,d_pt);
      }
    }
    //TCHPM
    if (d_bDis_TCHP>operating_point[2]){
      if (flavor==5){
	jet_pt_tagger_flavor[2][0]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[2][0]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[2][0]->Fill(d_pt);
	jet_eta_tagger_flavor[2][0]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[2][0]->Fill(d_eta,d_pt);
      }
      if (flavor==4){
	jet_pt_tagger_flavor[2][1]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[2][1]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[2][1]->Fill(d_pt);
	jet_eta_tagger_flavor[2][1]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[2][1]->Fill(d_eta,d_pt);
      }
      if (flavor==21 || (flavor >0 && flavor<4)){
	jet_pt_tagger_flavor[2][2]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[2][2]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[2][2]->Fill(d_pt);
	jet_eta_tagger_flavor[2][2]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[2][2]->Fill(d_eta,d_pt);
	
      }
    }
    //TCHPT
    if (d_bDis_TCHP>operating_point[3]){
      if (flavor==5){
	jet_pt_tagger_flavor[3][0]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[3][0]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[3][0]->Fill(d_pt);
	jet_eta_tagger_flavor[3][0]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[3][0]->Fill(d_eta,d_pt);
      }
      if (flavor==4){
	jet_pt_tagger_flavor[3][1]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[3][1]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[3][1]->Fill(d_pt);
	jet_eta_tagger_flavor[3][1]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[3][1]->Fill(d_eta,d_pt);
      }
      if (flavor==21 || (flavor >0 && flavor<4)){
	jet_pt_tagger_flavor[3][2]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[3][2]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[3][2]->Fill(d_pt);
	jet_eta_tagger_flavor[3][2]->Fill(d_eta); 
	jet_eta_pt_tagger_flavor[3][2]->Fill(d_eta,d_pt);
      }
    }
    //SSVHEM
    if (d_bDis_SSVHE>operating_point[4]){
      if (flavor==5){
	jet_pt_tagger_flavor[4][0]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[4][0]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[4][0]->Fill(d_pt);
	jet_eta_tagger_flavor[4][0]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[4][0]->Fill(d_eta,d_pt);
      }
      if (flavor==4){
	jet_pt_tagger_flavor[4][1]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[4][1]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[4][1]->Fill(d_pt);
	jet_eta_tagger_flavor[4][1]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[4][1]->Fill(d_eta,d_pt);
      }		  
      if (flavor==21 || (flavor >0 && flavor<4)){
	jet_pt_tagger_flavor[4][2]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[4][2]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[4][2]->Fill(d_pt);
	jet_eta_tagger_flavor[4][2]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[4][2]->Fill(d_eta,d_pt);
      }
    }
    //SSVHEM
    if (d_bDis_SSVHE>operating_point[5]){
      if (flavor==5){
	jet_pt_tagger_flavor[5][0]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[5][0]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[5][0]->Fill(d_pt);
	jet_eta_tagger_flavor[5][0]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[5][0]->Fill(d_eta,d_pt);
      }
      if (flavor==4){
	jet_pt_tagger_flavor[5][1]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[5][1]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[5][1]->Fill(d_pt);
	jet_eta_tagger_flavor[5][1]->Fill(d_eta);
jet_eta_pt_tagger_flavor[5][1]->Fill(d_eta,d_pt);
      }
      if (flavor==21 || (flavor >0 && flavor<4)){
	jet_pt_tagger_flavor[5][2]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[5][2]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[5][2]->Fill(d_pt);
	jet_eta_tagger_flavor[5][2]->Fill(d_eta);
jet_eta_pt_tagger_flavor[5][2]->Fill(d_eta,d_pt);
      }
    }
    //SSVHPT
    if (d_bDis_SSVHP>operating_point[6]){
      if (flavor==5){
	jet_pt_tagger_flavor[6][0]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[6][0]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[6][0]->Fill(d_pt);
	jet_eta_tagger_flavor[6][0]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[6][0]->Fill(d_eta,d_pt);
      }
      if (flavor==4){
	jet_pt_tagger_flavor[6][1]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[6][1]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[6][1]->Fill(d_pt);
	jet_eta_tagger_flavor[6][1]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[6][1]->Fill(d_eta,d_pt);
	
      }
      if (flavor==21 || (flavor >0 && flavor<4)){
	jet_pt_tagger_flavor[6][2]->Fill(d_pt);
	if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[6][2]->Fill(d_pt);
	if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[6][2]->Fill(d_pt);
	jet_eta_tagger_flavor[6][2]->Fill(d_eta);
	jet_eta_pt_tagger_flavor[6][2]->Fill(d_eta,d_pt);
      }
    }

    //JPL   
    if (d_bDis_JP>operating_point[7]){
      if (flavor==5){
        jet_pt_tagger_flavor[7][0]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[7][0]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[7][0]->Fill(d_pt);
        jet_eta_tagger_flavor[7][0]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[7][0]->Fill(d_eta,d_pt);
      }
      if (flavor==4){
        jet_pt_tagger_flavor[7][1]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[7][1]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[7][1]->Fill(d_pt);
        jet_eta_tagger_flavor[7][1]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[7][1]->Fill(d_eta,d_pt);

      }
      if (flavor==21 || (flavor >0 && flavor<4)){
        jet_pt_tagger_flavor[7][2]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[7][2]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[7][2]->Fill(d_pt);
        jet_eta_tagger_flavor[7][2]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[7][2]->Fill(d_eta,d_pt);
      }
    }

   //JPM                                                                                                                                                         
    if (d_bDis_JP>operating_point[8]){
      if (flavor==5){
        jet_pt_tagger_flavor[8][0]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[8][0]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[8][0]->Fill(d_pt);
        jet_eta_tagger_flavor[8][0]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[8][0]->Fill(d_eta,d_pt);
      }
      if (flavor==4){
        jet_pt_tagger_flavor[8][1]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[8][1]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[8][1]->Fill(d_pt);
        jet_eta_tagger_flavor[8][1]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[8][1]->Fill(d_eta,d_pt);

      }
      if (flavor==21 || (flavor >0 && flavor<4)){
        jet_pt_tagger_flavor[8][2]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[8][2]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[8][2]->Fill(d_pt);
        jet_eta_tagger_flavor[8][2]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[8][2]->Fill(d_eta,d_pt);
      }
    }
    //JPT                                                                                                                                                        
    if (d_bDis_JP>operating_point[9]){
      if (flavor==5){
        jet_pt_tagger_flavor[9][0]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[9][0]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[9][0]->Fill(d_pt);
        jet_eta_tagger_flavor[9][0]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[9][0]->Fill(d_eta,d_pt);
      }
      if (flavor==4){
        jet_pt_tagger_flavor[9][1]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[9][1]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[9][1]->Fill(d_pt);
        jet_eta_tagger_flavor[9][1]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[9][1]->Fill(d_eta,d_pt);

      }
      if (flavor==21 || (flavor >0 && flavor<4)){
        jet_pt_tagger_flavor[9][2]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[9][2]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[9][2]->Fill(d_pt);
        jet_eta_tagger_flavor[9][2]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[9][2]->Fill(d_eta,d_pt);
      }
    }
    //CSVL                                                                                                                            
    if (d_bDis_CSV>operating_point[10]){
      if (flavor==5){
        jet_pt_tagger_flavor[10][0]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[10][0]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[10][0]->Fill(d_pt);
        jet_eta_tagger_flavor[10][0]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[10][0]->Fill(d_eta,d_pt);
      }
      if (flavor==4){
        jet_pt_tagger_flavor[10][1]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[10][1]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[10][1]->Fill(d_pt);
        jet_eta_tagger_flavor[10][1]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[10][1]->Fill(d_eta,d_pt);

      }
      if (flavor==21 || (flavor >0 && flavor<4)){
        jet_pt_tagger_flavor[10][2]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[10][2]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[10][2]->Fill(d_pt);
        jet_eta_tagger_flavor[10][2]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[10][2]->Fill(d_eta,d_pt);
      }
    }

    //CSVM                                                                                                                                                        
    if (d_bDis_CSV>operating_point[11]){
      if (flavor==5){
        jet_pt_tagger_flavor[11][0]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[11][0]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[11][0]->Fill(d_pt);
        jet_eta_tagger_flavor[11][0]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[11][0]->Fill(d_eta,d_pt);
      }
      if (flavor==4){
        jet_pt_tagger_flavor[11][1]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[11][1]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[11][1]->Fill(d_pt);
        jet_eta_tagger_flavor[11][1]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[11][1]->Fill(d_eta,d_pt);

      }
      if (flavor==21 || (flavor >0 && flavor<4)){
        jet_pt_tagger_flavor[11][2]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[11][2]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[11][2]->Fill(d_pt);
        jet_eta_tagger_flavor[11][2]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[11][2]->Fill(d_eta,d_pt);
      }
    }

    //CSVT                                                                                                                                                        
    if (d_bDis_CSV>operating_point[12]){
      if (flavor==5){
        jet_pt_tagger_flavor[12][0]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[12][0]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[12][0]->Fill(d_pt);
        jet_eta_tagger_flavor[12][0]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[12][0]->Fill(d_eta,d_pt);
      }
      if (flavor==4){
        jet_pt_tagger_flavor[12][1]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[12][1]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[12][1]->Fill(d_pt);
        jet_eta_tagger_flavor[12][1]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[12][1]->Fill(d_eta,d_pt);

      }
      if (flavor==21 || (flavor >0 && flavor<4)){
        jet_pt_tagger_flavor[12][2]->Fill(d_pt);
        if(d_eta<1.2) jet_pt_l1p2_tagger_flavor[12][2]->Fill(d_pt);
        if(d_eta>=1.2 && d_eta<=2.4) jet_pt_1p2_2p4_tagger_flavor[12][2]->Fill(d_pt);
        jet_eta_tagger_flavor[12][2]->Fill(d_eta);
        jet_eta_pt_tagger_flavor[12][2]->Fill(d_eta,d_pt);
      }
    }

  }

  
  return;
}
//define this as a plug-in
DEFINE_FWK_MODULE(BtagCode);
