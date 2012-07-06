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
    NtpReader (TString const);
    NtpReader (std::vector<TString>&, bool);
    ~NtpReader ();

    bool IsData ();

    void SetBranches ();
    void SetBranchAddresses ();
    int  GetEntry (int const);

    void FillTree ();

  private:
    TChain fChain;
    bool   fIsData;
    TFile* fOutFile;
    TTree* fOutTree;



  // These members are in the ntuple
  protected:
    int   run;
    int   event;
    int   lumis;
    int   entry;
    int   nTriplets;
    int   nGoodVtx;

    int   mcsize;
    int   pdgID[200];
    float MCpx[200];
    float MCpy[200];
    float MCpz[200];
    float MCe[200];
    // int MaxSize=500;
    int   nJets; 
    float jetpx[500];
    float jetpy[500];
    float jetpz[500];
    float jete[500];
    float jetpt[500];
    float bdiscTCHE[500];
    float bdiscTCHP[500];
    float bdiscSSVHE[500];
    float bdiscSSSVHP[500];

    int   nElectrons;
    float epx[500];
    float epy[500];
    float epz[500];
    float ee[500];
    float ept[500];
    int   echarge[500];

    int   nMuons;
    float mpx[500];
    float mpy[500];
    float mpz[500];
    float me[500];
    float mpt[500];
    float mcharge[500];

    int   nPhotons;
    float phpx[500];
    float phpy[500];
    float phpz[500];
    float phe[500];
    float phpt[500];

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
