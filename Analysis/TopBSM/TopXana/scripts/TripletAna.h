//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul 12 15:12:53 2011 by ROOT version 5.27/06b
// from TTree Events/
// found on file: TTbarJets_1_LeptonANA_tree.root
//////////////////////////////////////////////////////////

#ifndef TripletAna_h
#define TripletAna_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class TripletAna {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run;
   Int_t           event;
   Int_t           lumis;
   Int_t           entry;
   Int_t           pdgID[200];
   Float_t         MCpx[200];
   Float_t         MCpy[200];
   Float_t         MCpz[200];
   Float_t         MCe[200];
   Int_t           nJets;
   Int_t           nElectrons;
   Int_t           nMuons;
   Int_t           nPhotons;
   Int_t           nTriplets;
   Int_t           nGoodVtx;
   Float_t         jetpt[15][nJets];   //[nJets]
   Float_t         jetpx[15][nJets];   //[nJets]
   Float_t         jetpy[15][nJets];   //[nJets]
   Float_t         jetpz[15][nJets];   //[nJets]
   Float_t         jete[15][nJets];   //[nJets]
   Float_t         ept[2][nElectrons];   //[nElectrons]
   Float_t         epx[2][nElectrons];   //[nElectrons]
   Float_t         epy[2][nElectrons];   //[nElectrons]
   Float_t         epz[2][nElectrons];   //[nElectrons]
   Float_t         ee[2][nElectrons];   //[nElectrons]
   Float_t         mpt[3][nMuons];   //[nMuons]
   Float_t         mpx[3][nMuons];   //[nMuons]
   Float_t         mpy[3][nMuons];   //[nMuons]
   Float_t         mpz[3][nMuons];   //[nMuons]
   Float_t         me[3][nMuons];   //[nMuons]
   Float_t         phpt[2][nPhotons];   //[nPhotons]
   Float_t         phpx[2][nPhotons];   //[nPhotons]
   Float_t         phpy[2][nPhotons];   //[nPhotons]
   Float_t         phpz[2][nPhotons];   //[nPhotons]
   Float_t         phe[2][nPhotons];   //[nPhotons]
   Float_t         triplet_jet1pt[220][nTriplets];   //[nTriplets]
   Float_t         triplet_jet2pt[220][nTriplets];   //[nTriplets]
   Float_t         triplet_jet3pt[220][nTriplets];   //[nTriplets]
   Float_t         triplet_sumScalarPt[220][nTriplets];   //[nTriplets]
   Float_t         triplet_mass[220][nTriplets];   //[nTriplets]
   Float_t         triplet_sumVectorPt[220][nTriplets];   //[nTriplets]
   Float_t         triplet_jet1px[220][nTriplets];   //[nTriplets]
   Float_t         triplet_jet1py[220][nTriplets];   //[nTriplets]
   Float_t         triplet_jet1pz[220][nTriplets];   //[nTriplets]
   Float_t         triplet_jet1e[220][nTriplets];   //[nTriplets]
   Float_t         triplet_jet2px[220][nTriplets];   //[nTriplets]
   Float_t         triplet_jet2py[220][nTriplets];   //[nTriplets]
   Float_t         triplet_jet2pz[220][nTriplets];   //[nTriplets]
   Float_t         triplet_jet2e[220][nTriplets];   //[nTriplets]
   Float_t         triplet_jet3px[220][nTriplets];   //[nTriplets]
   Float_t         triplet_jet3py[220][nTriplets];   //[nTriplets]
   Float_t         triplet_jet3pz[220][nTriplets];   //[nTriplets]
   Float_t         triplet_jet3e[220][nTriplets];   //[nTriplets]

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumis;   //!
   TBranch        *b_entry;   //!
   TBranch        *b_pdgID;   //!
   TBranch        *b_MCpx;   //!
   TBranch        *b_MCpy;   //!
   TBranch        *b_MCpz;   //!
   TBranch        *b_MCe;   //!
   TBranch        *b_nJets;   //!
   TBranch        *b_nElectrons;   //!
   TBranch        *b_nMuons;   //!
   TBranch        *b_nPhotons;   //!
   TBranch        *b_nTriplets;   //!
   TBranch        *b_nGoodVtx;   //!
   TBranch        *b_jetpt;   //!
   TBranch        *b_jetpx;   //!
   TBranch        *b_jetpy;   //!
   TBranch        *b_jetpz;   //!
   TBranch        *b_jete;   //!
   TBranch        *b_ept;   //!
   TBranch        *b_epx;   //!
   TBranch        *b_epy;   //!
   TBranch        *b_epz;   //!
   TBranch        *b_ee;   //!
   TBranch        *b_mpt;   //!
   TBranch        *b_mpx;   //!
   TBranch        *b_mpy;   //!
   TBranch        *b_mpz;   //!
   TBranch        *b_me;   //!
   TBranch        *b_phpt;   //!
   TBranch        *b_phpx;   //!
   TBranch        *b_phpy;   //!
   TBranch        *b_phpz;   //!
   TBranch        *b_phe;   //!
   TBranch        *b_triplet_jet1pt;   //!
   TBranch        *b_triplet_jet2pt;   //!
   TBranch        *b_triplet_jet3pt;   //!
   TBranch        *b_triplet_sumScalarPt;   //!
   TBranch        *b_triplet_mass;   //!
   TBranch        *b_triplet_sumVectorPt;   //!
   TBranch        *b_triplet_jet1px;   //!
   TBranch        *b_triplet_jet1py;   //!
   TBranch        *b_triplet_jet1pz;   //!
   TBranch        *b_triplet_jet1e;   //!
   TBranch        *b_triplet_jet2px;   //!
   TBranch        *b_triplet_jet2py;   //!
   TBranch        *b_triplet_jet2pz;   //!
   TBranch        *b_triplet_jet2e;   //!
   TBranch        *b_triplet_jet3px;   //!
   TBranch        *b_triplet_jet3py;   //!
   TBranch        *b_triplet_jet3pz;   //!
   TBranch        *b_triplet_jet3e;   //!

   TripletAna(TTree *tree=0);
   virtual ~TripletAna();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TripletAna_cxx
TripletAna::TripletAna(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("TTbarJets_1_LeptonANA_tree.root");
      if (!f) {
         f = new TFile("TTbarJets_1_LeptonANA_tree.root");
      }
      tree = (TTree*)gDirectory->Get("Events");

   }
   Init(tree);
}

TripletAna::~TripletAna()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TripletAna::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TripletAna::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TripletAna::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
   fChain->SetBranchAddress("entry", &entry, &b_entry);
   fChain->SetBranchAddress("pdgID", pdgID, &b_pdgID);
   fChain->SetBranchAddress("MCpx", MCpx, &b_MCpx);
   fChain->SetBranchAddress("MCpy", MCpy, &b_MCpy);
   fChain->SetBranchAddress("MCpz", MCpz, &b_MCpz);
   fChain->SetBranchAddress("MCe", MCe, &b_MCe);
   fChain->SetBranchAddress("nJets", &nJets, &b_nJets);
   fChain->SetBranchAddress("nElectrons", &nElectrons, &b_nElectrons);
   fChain->SetBranchAddress("nMuons", &nMuons, &b_nMuons);
   fChain->SetBranchAddress("nPhotons", &nPhotons, &b_nPhotons);
   fChain->SetBranchAddress("nTriplets", &nTriplets, &b_nTriplets);
   fChain->SetBranchAddress("nGoodVtx", &nGoodVtx, &b_nGoodVtx);
   fChain->SetBranchAddress("jetpt[nJets]", jetpt, &b_jetpt);
   fChain->SetBranchAddress("jetpx[nJets]", jetpx, &b_jetpx);
   fChain->SetBranchAddress("jetpy[nJets]", jetpy, &b_jetpy);
   fChain->SetBranchAddress("jetpz[nJets]", jetpz, &b_jetpz);
   fChain->SetBranchAddress("jete[nJets]", jete, &b_jete);
   fChain->SetBranchAddress("ept[nElectrons]", ept, &b_ept);
   fChain->SetBranchAddress("epx[nElectrons]", epx, &b_epx);
   fChain->SetBranchAddress("epy[nElectrons]", epy, &b_epy);
   fChain->SetBranchAddress("epz[nElectrons]", epz, &b_epz);
   fChain->SetBranchAddress("ee[nElectrons]", ee, &b_ee);
   fChain->SetBranchAddress("mpt[nMuons]", mpt, &b_mpt);
   fChain->SetBranchAddress("mpx[nMuons]", mpx, &b_mpx);
   fChain->SetBranchAddress("mpy[nMuons]", mpy, &b_mpy);
   fChain->SetBranchAddress("mpz[nMuons]", mpz, &b_mpz);
   fChain->SetBranchAddress("me[nMuons]", me, &b_me);
   fChain->SetBranchAddress("phpt[nPhotons]", phpt, &b_phpt);
   fChain->SetBranchAddress("phpx[nPhotons]", phpx, &b_phpx);
   fChain->SetBranchAddress("phpy[nPhotons]", phpy, &b_phpy);
   fChain->SetBranchAddress("phpz[nPhotons]", phpz, &b_phpz);
   fChain->SetBranchAddress("phe[nPhotons]", phe, &b_phe);
   fChain->SetBranchAddress("triplet_jet1pt[nTriplets]", triplet_jet1pt, &b_triplet_jet1pt);
   fChain->SetBranchAddress("triplet_jet2pt[nTriplets]", triplet_jet2pt, &b_triplet_jet2pt);
   fChain->SetBranchAddress("triplet_jet3pt[nTriplets]", triplet_jet3pt, &b_triplet_jet3pt);
   fChain->SetBranchAddress("triplet_sumScalarPt[nTriplets]", triplet_sumScalarPt, &b_triplet_sumScalarPt);
   fChain->SetBranchAddress("triplet_mass[nTriplets]", triplet_mass, &b_triplet_mass);
   fChain->SetBranchAddress("triplet_sumVectorPt[nTriplets]", triplet_sumVectorPt, &b_triplet_sumVectorPt);
   fChain->SetBranchAddress("triplet_jet1px[nTriplets]", triplet_jet1px, &b_triplet_jet1px);
   fChain->SetBranchAddress("triplet_jet1py[nTriplets]", triplet_jet1py, &b_triplet_jet1py);
   fChain->SetBranchAddress("triplet_jet1pz[nTriplets]", triplet_jet1pz, &b_triplet_jet1pz);
   fChain->SetBranchAddress("triplet_jet1e[nTriplets]", triplet_jet1e, &b_triplet_jet1e);
   fChain->SetBranchAddress("triplet_jet2px[nTriplets]", triplet_jet2px, &b_triplet_jet2px);
   fChain->SetBranchAddress("triplet_jet2py[nTriplets]", triplet_jet2py, &b_triplet_jet2py);
   fChain->SetBranchAddress("triplet_jet2pz[nTriplets]", triplet_jet2pz, &b_triplet_jet2pz);
   fChain->SetBranchAddress("triplet_jet2e[nTriplets]", triplet_jet2e, &b_triplet_jet2e);
   fChain->SetBranchAddress("triplet_jet3px[nTriplets]", triplet_jet3px, &b_triplet_jet3px);
   fChain->SetBranchAddress("triplet_jet3py[nTriplets]", triplet_jet3py, &b_triplet_jet3py);
   fChain->SetBranchAddress("triplet_jet3pz[nTriplets]", triplet_jet3pz, &b_triplet_jet3pz);
   fChain->SetBranchAddress("triplet_jet3e[nTriplets]", triplet_jet3e, &b_triplet_jet3e);
   Notify();
}

Bool_t TripletAna::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TripletAna::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TripletAna::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TripletAna_cxx
