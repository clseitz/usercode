#ifndef GUARD_NtpReader_h
#define GUARD_NtpReader_h

#include <iostream>
#include <vector>

#include "TChain.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"

class NtpReader
{
  public:
    NtpReader ();
    NtpReader (TTree*);
    NtpReader (std::vector<TString>&, bool);
    ~NtpReader ();

    bool IsData ();

    void SetBranches (TTree*);
    void SetBranchAddresses ();
    int  GetEntry (int const);


  private:
    TChain fChain;
    bool   fIsData;



  // These members are in the ntuple
  public:
    int   run;
    int   event;
    int   lumis;
    int   entry;
    int   nTriplets;
    int   nGoodVtx;

    int   mcsize;
    int   pdgID[500];
    float MCpx[500];
    float MCpy[500];
    float MCpz[500];
    float MCe[500];
    // int MaxSize=500;
    int   nJets; 
    float jetpx[200];
    float jetpy[200];
    float jetpz[200];
    float jete[200];
    float jetpt[200];
    float bdiscTCHE[200];
    float bdiscTCHP[200];
    float bdiscSSVHE[200];
    float bdiscSSSVHP[200];

    int   nElectrons;
    float epx[200];
    float epy[200];
    float epz[200];
    float ee[200];
    float ept[200];
    int   echarge[200];

    int   nMuons;
    float mpx[200];
    float mpy[200];
    float mpz[200];
    float me[200];
    float mpt[200];
    float mcharge[200];

    int   nPhotons;
    float phpx[200];
    float phpy[200];
    float phpz[200];
    float phe[200];
    float phpt[200];

    float pfMET;
    float pfMETphi;

    //the triplets here could handle 30 jets  with combinaotriz

    float triplet_jet1pt[5000];
    float triplet_jet1px[5000];
    float triplet_jet1py[5000];
    float triplet_jet1pz[5000];
    float triplet_jet1e[5000];

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






#endif
