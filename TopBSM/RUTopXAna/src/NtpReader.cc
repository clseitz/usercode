#include "TopBSM/RUTopXAna/interface/NtpReader.h"


NtpReader::NtpReader ()
{
  // Construct
}

NtpReader::NtpReader (TTree* InTree)
{
  SetBranches(InTree);
}

NtpReader::NtpReader (std::vector<TString>& InFiles, bool const IsData)
{
  // Construct for reading an ntp

  // Is it data?
  fIsData = IsData;

  // Construct the chain
  fChain.SetName("Events");
  for (std::vector<TString>::iterator it = InFiles.begin(); it != InFiles.end(); ++it) {
    fChain.Add(*it);
  }

  SetBranchAddresses();
}


NtpReader::~NtpReader ()
{
}


bool NtpReader::IsData ()
{
  return fIsData;
}



void NtpReader::SetBranches (TTree* Tree)
{
  // Set the branches for writing

  Tree->Branch("run", &run);
  Tree->Branch("event", &event);
  Tree->Branch("lumis", &lumis);
  Tree->Branch("entry", &entry);
  if(!IsData()){
    Tree->Branch("pdgID",pdgID,"pdgID[200]/I");
    Tree->Branch("MCpx", MCpx, "MCpx[200]/F");
    Tree->Branch("MCpy", MCpy, "MCpy[200]/F");
    Tree->Branch("MCpz", MCpz, "MCpz[200]/F");
    Tree->Branch("MCe", MCe, "MCe[200]/F");
  }
  Tree->Branch("nJets", &nJets);
  Tree->Branch("nElectrons", &nElectrons);
  Tree->Branch("nMuons", &nMuons);
  Tree->Branch("nPhotons", &nPhotons);
  Tree->Branch("nTriplets", &nTriplets);
  Tree->Branch("nGoodVtx", &nGoodVtx);

  Tree->Branch("jetpt[nJets]", jetpt);
  Tree->Branch("jetpx[nJets]", jetpx);
  Tree->Branch("jetpy[nJets]", jetpy);
  Tree->Branch("jetpz[nJets]", jetpz);
  Tree->Branch("jete[nJets]", jete);
  Tree->Branch("bdiscTCHE[nJets]", bdiscTCHE);
  Tree->Branch("bdiscTCHP[nJets]", bdiscTCHP);
  Tree->Branch("bdiscSSVHE[nJets]", bdiscSSVHE);
  Tree->Branch("bdiscSSSVHP[nJets]", bdiscSSSVHP);


  Tree->Branch("epx[nElectrons]", epx);
  Tree->Branch("epy[nElectrons]", epy);
  Tree->Branch("epz[nElectrons]", epz);
  Tree->Branch("ee[nElectrons]", ee);
  Tree->Branch("ept[nElectrons]", ept);
  Tree->Branch("echarge[nElectrons]", echarge);


  Tree->Branch("mpx[nMuons]", mpx);
  Tree->Branch("mpy[nMuons]", mpy);
  Tree->Branch("mpz[nMuons]", mpz);
  Tree->Branch("me[nMuons]", me);
  Tree->Branch("mpt[nMuons]", mpt);
  Tree->Branch("mcharge[nMuons]", mcharge);


  Tree->Branch("phpt[nPhotons]", phpt);
  Tree->Branch("phpx[nPhotons]", phpx);
  Tree->Branch("phpy[nPhotons]", phpy);
  Tree->Branch("phpz[nPhotons]", phpz);
  Tree->Branch("phe[nPhotons]", phe);

  Tree->Branch("pfMET", &pfMET);
  Tree->Branch("pfMETphi", &pfMETphi);

  Tree->Branch("triplet_jet1pt[nTriplets]", triplet_jet1pt);
  Tree->Branch("triplet_jet2pt[nTriplets]", triplet_jet2pt);
  Tree->Branch("triplet_jet3pt[nTriplets]", triplet_jet3pt);
  Tree->Branch("triplet_sumScalarPt[nTriplets]",triplet_sumScalarPt);
  Tree->Branch("triplet_mass[nTriplets]",triplet_mass);
  Tree->Branch("triplet_sumVectorPt[nTriplets]",triplet_sumVectorPt);

  Tree->Branch("triplet_jet1px[nTriplets]", triplet_jet1px);
  Tree->Branch("triplet_jet1py[nTriplets]", triplet_jet1py);
  Tree->Branch("triplet_jet1pz[nTriplets]", triplet_jet1pz);
  Tree->Branch("triplet_jet1e[nTriplets]", triplet_jet1e);


  Tree->Branch("triplet_jet2px[nTriplets]", triplet_jet2px);
  Tree->Branch("triplet_jet2py[nTriplets]", triplet_jet2py);
  Tree->Branch("triplet_jet2pz[nTriplets]", triplet_jet2pz);
  Tree->Branch("triplet_jet2e[nTriplets]", triplet_jet2e);


  Tree->Branch("triplet_jet3px[nTriplets]", triplet_jet3px);
  Tree->Branch("triplet_jet3py[nTriplets]", triplet_jet3py);
  Tree->Branch("triplet_jet3pz[nTriplets]", triplet_jet3pz);
  Tree->Branch("triplet_jet3e[nTriplets]", triplet_jet3e);

 


  return;
}


void NtpReader::SetBranchAddresses ()
{
  // Set the branches for reading

  fChain.SetBranchAddress("run", &run);
  fChain.SetBranchAddress("event", &event);
  fChain.SetBranchAddress("lumis", &lumis);
  fChain.SetBranchAddress("entry", &entry);
  if(!IsData()){
    fChain.SetBranchAddress("pdgID[200]",pdgID);
    fChain.SetBranchAddress("MCpx[200]", MCpx);
    fChain.SetBranchAddress("MCpy[200]", MCpy);
    fChain.SetBranchAddress("MCpz[200]", MCpz);
    fChain.SetBranchAddress("MCe[200]", MCe);
  }
  fChain.SetBranchAddress("nJets", &nJets);
  fChain.SetBranchAddress("nElectrons", &nElectrons);
  fChain.SetBranchAddress("nMuons", &nMuons);
  fChain.SetBranchAddress("nPhotons", &nPhotons);
  fChain.SetBranchAddress("nTriplets", &nTriplets);
  fChain.SetBranchAddress("nGoodVtx", &nGoodVtx);

  fChain.SetBranchAddress("jetpt[nJets]", jetpt);
  fChain.SetBranchAddress("jetpx[nJets]", jetpx);
  fChain.SetBranchAddress("jetpy[nJets]", jetpy);
  fChain.SetBranchAddress("jetpz[nJets]", jetpz);
  fChain.SetBranchAddress("jete[nJets]", jete);
  fChain.SetBranchAddress("bdiscTCHE[nJets]", bdiscTCHE);
  fChain.SetBranchAddress("bdiscTCHP[nJets]", bdiscTCHP);
  fChain.SetBranchAddress("bdiscSSVHE[nJets]", bdiscSSVHE);
  fChain.SetBranchAddress("bdiscSSSVHP[nJets]", bdiscSSSVHP);


  fChain.SetBranchAddress("epx[nElectrons]", epx);
  fChain.SetBranchAddress("epy[nElectrons]", epy);
  fChain.SetBranchAddress("epz[nElectrons]", epz);
  fChain.SetBranchAddress("ee[nElectrons]", ee);
  fChain.SetBranchAddress("ept[nElectrons]", ept);
  fChain.SetBranchAddress("echarge[nElectrons]", echarge);


  fChain.SetBranchAddress("mpt[nMuons]", mpt);
  fChain.SetBranchAddress("mpx[nMuons]", mpx);
  fChain.SetBranchAddress("mpy[nMuons]", mpy);
  fChain.SetBranchAddress("mpz[nMuons]", mpz);
  fChain.SetBranchAddress("me[nMuons]", me);
  fChain.SetBranchAddress("mcharge[nMuons]", mcharge);


  fChain.SetBranchAddress("phpt[nPhotons]", phpt);
  fChain.SetBranchAddress("phpx[nPhotons]", phpx);
  fChain.SetBranchAddress("phpy[nPhotons]", phpy);
  fChain.SetBranchAddress("phpz[nPhotons]", phpz);
  fChain.SetBranchAddress("phe[nPhotons]", phe);

  fChain.SetBranchAddress("pfMET", &pfMET);
  fChain.SetBranchAddress("pfMETphi", &pfMETphi);

  fChain.SetBranchAddress("triplet_jet1pt[nTriplets]", triplet_jet1pt);
  fChain.SetBranchAddress("triplet_jet2pt[nTriplets]", triplet_jet2pt);
  fChain.SetBranchAddress("triplet_jet3pt[nTriplets]", triplet_jet3pt);
  fChain.SetBranchAddress("triplet_sumScalarPt[nTriplets]",triplet_sumScalarPt);
  fChain.SetBranchAddress("triplet_mass[nTriplets]",triplet_mass);
  fChain.SetBranchAddress("triplet_sumVectorPt[nTriplets]",triplet_sumVectorPt);

  fChain.SetBranchAddress("triplet_jet1px[nTriplets]", triplet_jet1px);
  fChain.SetBranchAddress("triplet_jet1py[nTriplets]", triplet_jet1py);
  fChain.SetBranchAddress("triplet_jet1pz[nTriplets]", triplet_jet1pz);
  fChain.SetBranchAddress("triplet_jet1e[nTriplets]", triplet_jet1e);


  fChain.SetBranchAddress("triplet_jet2px[nTriplets]", triplet_jet2px);
  fChain.SetBranchAddress("triplet_jet2py[nTriplets]", triplet_jet2py);
  fChain.SetBranchAddress("triplet_jet2pz[nTriplets]", triplet_jet2pz);
  fChain.SetBranchAddress("triplet_jet2e[nTriplets]", triplet_jet2e);


  fChain.SetBranchAddress("triplet_jet3px[nTriplets]", triplet_jet3px);
  fChain.SetBranchAddress("triplet_jet3py[nTriplets]", triplet_jet3py);
  fChain.SetBranchAddress("triplet_jet3pz[nTriplets]", triplet_jet3pz);
  fChain.SetBranchAddress("triplet_jet3e[nTriplets]", triplet_jet3e);

 


  return;
}


int NtpReader::GetEntry (int const ientry)
{
  return fChain.GetEntry(ientry);
}


