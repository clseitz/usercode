#include <memory>
#include <iostream>
#include <TString.h> 
#include <TFile.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TH3D.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TProfile.h>
#include <TRandom.h>
#include <TROOT.h>
#include <TBranch.h>
#include <vector>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/JetCorrFactors.h"


using namespace std;
using namespace edm;
using namespace pat;

class BtagCode : public edm::EDAnalyzer {
   public:
      explicit BtagCode(const edm::ParameterSet&);
      ~BtagCode();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      void BtagEff(std::vector<pat::Jet >fCleanJets, int nCleanJets); 
      void MakeTriplets(std::vector<pat::Jet >fCleanJets); 
       void BtagEffTriplet(std::vector <std::vector<pat::Jet > > Triplet, std::vector<double> nMCBtagTriplet,std::vector<double> sumScalarPtTriplet, std::vector<double> sumVectorPtTriplet, std::vector<double> massTriplet);  
      void DoJetID(const edm::Event&);
      // ----------member data ---------------------------
      //define all the variables in the config file
      double _sumPtMin, _etacut, _jetptcut;
      bool _isData;
      bool _noTripletBtag;
      bool _debug;
      int _nbTagsMin; 
      int _nbTagsMax;
      int _nTripletBtagsMin, _nTripletBtagsMax;
      bool _doBtagEff;
      std::string _outputFilename, _outputFilename2, corStep, corFlvr;   
      std::string _patJetType;
      int _njetsMin, _njetsMax;
      std::string _htTrigger;
      
      
      TFile* outputFile; 
      Int_t   nEvents;
      Int_t   run;
      Int_t   event;
      Int_t   lumis;
      Int_t nGoodJets;
      Int_t nCleanJets;
      //define variables that we need for the triplets
      std::vector <std::vector<pat::Jet > > Triplet;
      std::vector<double> nMCBtagTriplet;
      std::vector<double> sumScalarPtTriplet;
      std::vector<double> sumVectorPtTriplet;
      std::vector<double> massTriplet;
      
      Int_t nTriplets;
      Int_t q;
      //define our own jet collection (just in case if we want to clean up also)
      std::vector<pat::Jet >      fGoodJets;
      std::vector<pat::Jet >      fCleanJets;
      //variables for btagging
      Int_t MCbcount;
      vector<double > operating_point; vector<string > op_name;
      vector<string > flavor_name;
      vector<string > tagger_name;
      
      //histograms for the different taggers and flavor
      std::vector<std::vector<TH1F*> > discriminator_tagalgo_flavor;
      std::vector<std::vector<TH1F*> > jet_pt_tagger_flavor;
      std::vector<std::vector<TH1F*> > jet_pt_1p2_2p4_tagger_flavor;
      std::vector<std::vector<TH1F*> > jet_pt_l1p2_tagger_flavor;

      std::vector<std::vector<TH1F*> > jet_eta_tagger_flavor;
       std::vector<std::vector<TH2F*> > jet_eta_pt_tagger_flavor;

      std::vector<std::vector<TH1F*> > triplet_jet_pt_tagger_flavor;
      std::vector<std::vector<TH1F*> > triplet_sumpt_tagger_flavor;
      std::vector<std::vector<TH1F*> > triplet_mass_tagger_flavor;

      TH1F* MCbTriplet;

      //define some stuff for the triplet making
    
};
