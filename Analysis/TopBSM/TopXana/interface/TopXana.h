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
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Photon.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include <fstream>

using namespace std;
using namespace edm;
using namespace pat;

class TopXana : public edm::EDAnalyzer {
 public:
  explicit TopXana(const edm::ParameterSet&);
  ~TopXana();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
 private:
  virtual void beginJob();
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  void UseJson( vector<int > GoodRuns, vector<int > GoodLumiStart,  vector<int > GoodLumiEnd,  Int_t nGoodRuns, int run, int lumis );
  void DoJetID(const edm::Event&);
  void DoVertexID(const edm::Event&);
  void DoElectronID(const edm::Event&);
  void DoMuonID(const edm::Event&);
  void DoPhotonID(const edm::Event&);
  void DoMETID(const edm::Event&);
  void DoCleanUp(vector<Muon >fGoodMuons,vector<Electron >fGoodElectrons,vector<Photon >fGoodPhotons,vector<Jet >fGoodJets);
  void GetMCTruth(const edm::Event&);
  void MakeTriplets(std::vector<pat::Jet >fCleanJets); 
  void getTriggerDecision(const edm::Event&, std::map<std::string, bool>&);
  
  
  // ----------member data ---------------------------
  ofstream run_evt_ee, run_evt_mm, run_evt_em;
  
  double _sumPtMin, _etacut, _jetptcut, _eeta,_ept,_meta,_mpt,_pheta,_phpt;
  bool _isData;
  bool _noTripletBtag;
  bool _debug;
  int _nbTagsMin; 
  int _nbTagsMax;      int _nTripletBtagsMin, _nTripletBtagsMax;
  bool _doBtagEff;
  std::string _outputFilename, _outputFilename2, corStep, corFlvr;   
  std::string _patJetType;
  int _njetsMin, _njetsMax;
  std::string _htTrigger;
  std::vector<std::string>          fTriggerNames;
  std::map<std::string, bool>       fTriggerMap;
  
  int countE;  
  
  TFile* outputFile; 
  TFile* outputFile2; 
  Int_t   entry;
  int  run;
  int   event;
  int   lumis;
  //varibales to test for the JSON file                                                                                            
  bool isdata;
  string JSONFilename;
  TFile* JSONFile;
  vector<int > GoodRuns;
  vector<int > GoodLumiStart;
  vector<int >  GoodLumiEnd;
  
  Int_t nGoodRuns;  
  Bool_t GoodRun;
  Int_t nGoodJets;
  Int_t nCleanJets;
  Int_t nBJets;
  Int_t nGoodElectrons;
  Int_t nCleanElectrons;
  
  Int_t nGoodMuons;
  Int_t nCleanMuons;
  
  Int_t nGoodPhotons;
  Int_t nCleanPhotons;
  
  Int_t IsVtxGood;
  Int_t nGoodVtx;
  TH1F* h_nGoodVtx;
  TH1F* h_zPosGoodVtx;
  TH1F* h_NumEvtCut;

  TH1F* h_nCleanJets;
  TH1F* h_nGoodJets;
  TH1F* h_nGoodElectrons;
  TH1F* h_nCleanElectrons;
  TH1F* h_nGoodMuons;
  TH1F* h_nCleanMuons;
  TH1F* h_nGoodPhotons;
  TH1F* h_nCleanPhotons;
  TH1F* h_MET;
  //some event check
  TH1F* h_DiElectronMass;
  TH1F* h_DiMuonMass;
  TH1F* h_ElectronMuonMass;
  
  TH1F* h_SumptSig4HighestPlus;
  TH1F* h_SumptSig4SecondHighestPlus;
  TH1F* h_TransMassLepMETPlus;
  TH1F* h_TransMassLepMET4JetPlus;

  TH1F* h_TransMassLepMET4SecondJetPlus;
  TH1F* h_SumptSig4HighestMinus;
  TH1F* h_SumptSig4SecondHighestMinus;
  TH1F* h_TransMassLepMETMinus;
  TH1F* h_TransMassLepMET4JetMinus;
  TH1F* h_TransMassLepMET4SecondJetMinus;

  TH1F* h_SumptSig4HighestPlus_5jet1b;
  TH1F* h_SumptSig4HighestPlus_4jet1b;
  TH1F* h_SumptSig4HighestPlus_5jet2b;
  TH1F* h_SumptSig4HighestPlus_4jet2b;

  TH1F* h_SumptSig4HighestMinus_5jet1b;
  TH1F* h_SumptSig4HighestMinus_4jet1b;
  TH1F* h_SumptSig4HighestMinus_5jet2b;
  TH1F* h_SumptSig4HighestMinus_4jet2b;

  TH1F* h_SumptSig4SecondHighestPlus_5jet1b;
  TH1F* h_SumptSig4SecondHighestPlus_5jet2b;
  TH1F* h_SumptSig4SecondHighestMinus_5jet1b;
  TH1F* h_SumptSig4SecondHighestMinus_5jet2b;



  TH1F* h_TransMassLepMET4JetPlus_5jet1b;
  TH1F* h_TransMassLepMET4JetPlus_4jet1b;
  TH1F* h_TransMassLepMET4JetPlus_5jet2b;
  TH1F* h_TransMassLepMET4JetPlus_4jet2b;

  TH1F* h_TransMassLepMET4JetMinus_5jet1b;
  TH1F* h_TransMassLepMET4JetMinus_4jet1b;
  TH1F* h_TransMassLepMET4JetMinus_5jet2b;
  TH1F* h_TransMassLepMET4JetMinus_4jet2b;

  //define variables that we need for the triplets
  std::vector <std::vector<pat::Jet > > Triplet;
  std::vector<double> nMCBtagTriplet;
  std::vector<double> sumScalarPtTriplet;
  std::vector<double> sumVectorPtTriplet;
  std::vector<double> massTriplet;
  std::vector<double> massQuad;
  pat::Jet AntiTripletHighestJet;
  pat::Jet Jet1; pat::Jet Jet2; pat::Jet Jet3; pat::Jet Jet4; 
  Int_t nTriplets;
  Int_t q;
  //define our own jet collection (just in case if we want to clean up also)
  std::vector<pat::Jet >      fGoodJets;
  std::vector<pat::Jet >      fCleanJets;
  
  //electron collection
  std::vector<pat::Electron> fGoodElectrons;
  std::vector<pat::Electron> fCleanElectrons;
  
  //muon collection
  std::vector<pat::Muon>     fGoodMuons;
  std::vector<pat::Muon>      fCleanMuons;
  std::vector<pat::Muon>      fFakeMuons;
  
  //photon collection
  std::vector<pat::Photon>     fGoodPhotons;
  std::vector<pat::Photon>      fCleanPhotons;
  
  //MET
  //TLorentzVector  fMET;
  pat::MET  fMET;
  //some plots for the 6 highest jets in the event
  std::vector<TH1F*> v_jet_pt;
  std::vector<TH1F*> v_jet_eta;
  std::vector<TH1F*> v_jet_phi;
  std::vector<TH1F*> v_jet_m;

  std::vector<TH1F*> v_e_pt;
  std::vector<TH1F*> v_e_eta;
  std::vector<TH1F*> v_e_phi;
  
  std::vector<TH1F*> v_m_pt;
  std::vector<TH1F*> v_m_eta;
  std::vector<TH1F*> v_m_phi;
  
  std::vector<TH1F*> v_ph_pt;
  std::vector<TH1F*> v_ph_eta;
  std::vector<TH1F*> v_ph_phi;
  //some other event variables
  
  //make some plots for the triplets
  std::vector <std::vector <std::vector<TH1F* > > > Mjjj_pt_njet_diag;
  std::vector <std::vector<TH2F* > >Mjjj_sumpt_pt_njet;
  std::vector <std::vector <std::vector<TH1F* > > > M4j_pt_njet_diag;
  std::vector <std::vector <std::vector<TH2F* > > > Mjjj_M4j_pt_njet_diag; 
  TH1F* h_LeptonPt;
  TH1F* h_ElectronPt;
  TH1F* h_MuonPt;
  
  //stuff for the tree
  TTree*  MyTree;
  int mcsize;
  int     pdgID[200];
  float   MCpx[200];
  float   MCpy[200];
  float   MCpz[200];
  float   MCe[200];
  // int MaxSize=500;
  int nJets; 
  float jetpx[500];
  //vector<float > jetpx;
  float  jetpy[500];
  float  jetpz[500];
  float  jete[500];
  float  jetpt[500];
  
  int nElectrons;
  float  epx[500];
  float  epy[500];
  float  epz[500];
  float  ee[500];
  float  ept[500];
  int nMuons;
  float  mpx[500];
  float  mpy[500];
  float  mpz[500];
  float  me[500];
  float  mpt[500];
  int nPhotons;
  float  phpx[500];
  float phpy[500];
  float  phpz[500];
  float  phe[500];
  float  phpt[500];
  //the triplets here could handle 30 jets  with combinaotriz
  
  float triplet_jet1pt[5000];
  float  triplet_jet1px[5000];
  float  triplet_jet1py[5000];
  float  triplet_jet1pz[5000];
  float  triplet_jet1e[5000];
  
  float triplet_jet2pt[5000];
  float triplet_jet2px[5000];
  float triplet_jet2py[5000];
  float triplet_jet2pz[5000];
  float triplet_jet2e[5000];
  
  float triplet_jet3pt[5000];
  float triplet_jet3px[5000];
  float triplet_jet3py[5000];
  float triplet_jet3pz[5000];
  float triplet_jet3e[5000];
  
  float triplet_mass[5000];
  float triplet_sumScalarPt[5000];
  float triplet_sumVectorPt[5000];
  
  
};

