#include "TopBSM/RUTopXAna/interface/NtpReader.h"


NtpReader::NtpReader ()
{
  // Construct
}

NtpReader::NtpReader (TString const OutFileName)
{
  fOutFile = new TFile(OutFileName, "recreate");

  if (!fOutFile->IsOpen()) {
    std::cerr << "ERROR: cannot open output file named: " << OutFileName << std::endl;
    throw;
  }

  fOutTree = new TTree("Events", "");
  fOutTree->SetDirectory(fOutFile);
  SetBranches();
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
  // destructor
  if (fOutTree) {
    fOutTree->GetCurrentFile()->Write();
    fOutTree->GetCurrentFile()->Close();
  }

  if (fOutFile) {
    delete fOutFile;
  }
}


bool NtpReader::IsData ()
{
  return fIsData;
}



void NtpReader::SetBranches ()
{
  // Set the branches for writing

  fOutTree->Branch("run", &run);
  fOutTree->Branch("event", &event);
  fOutTree->Branch("lumis", &lumis);
  fOutTree->Branch("entry", &entry);
  if(!IsData()){
    fOutTree->Branch("pdgID",pdgID,"pdgID[200]/I");
    fOutTree->Branch("MCpx", MCpx, "MCpx[200]/F");
    fOutTree->Branch("MCpy", MCpy, "MCpy[200]/F");
    fOutTree->Branch("MCpz", MCpz, "MCpz[200]/F");
    fOutTree->Branch("MCe", MCe, "MCe[200]/F");
  }
  fOutTree->Branch("nJets", &nJets);
  fOutTree->Branch("nElectrons", &nElectrons);
  fOutTree->Branch("nMuons", &nMuons);
  fOutTree->Branch("nPhotons", &nPhotons);
  fOutTree->Branch("nTriplets", &nTriplets);
  fOutTree->Branch("nGoodVtx", &nGoodVtx);

  fOutTree->Branch("jetpt[nJets]", jetpt);
  fOutTree->Branch("jetpx[nJets]", jetpx);
  fOutTree->Branch("jetpy[nJets]", jetpy);
  fOutTree->Branch("jetpz[nJets]", jetpz);
  fOutTree->Branch("jete[nJets]", jete);
  fOutTree->Branch("bdiscTCHE[nJets]", bdiscTCHE);
  fOutTree->Branch("bdiscTCHP[nJets]", bdiscTCHP);
  fOutTree->Branch("bdiscSSVHE[nJets]", bdiscSSVHE);
  fOutTree->Branch("bdiscSSSVHP[nJets]", bdiscSSSVHP);


  fOutTree->Branch("epx[nElectrons]", epx);
  fOutTree->Branch("epy[nElectrons]", epy);
  fOutTree->Branch("epz[nElectrons]", epz);
  fOutTree->Branch("ee[nElectrons]", ee);
  fOutTree->Branch("ept[nElectrons]", ept);
  fOutTree->Branch("echarge[nElectrons]", echarge);


  fOutTree->Branch("mpx[nMuons]", mpx);
  fOutTree->Branch("mpy[nMuons]", mpy);
  fOutTree->Branch("mpz[nMuons]", mpz);
  fOutTree->Branch("me[nMuons]", me);
  fOutTree->Branch("mpt[nMuons]", mpt);
  fOutTree->Branch("mcharge[nMuons]", mcharge);


  fOutTree->Branch("phpt[nPhotons]", phpt);
  fOutTree->Branch("phpx[nPhotons]", phpx);
  fOutTree->Branch("phpy[nPhotons]", phpy);
  fOutTree->Branch("phpz[nPhotons]", phpz);
  fOutTree->Branch("phe[nPhotons]", phe);

  fOutTree->Branch("pfMET", &pfMET);
  fOutTree->Branch("pfMETphi", &pfMETphi);

  fOutTree->Branch("triplet_jet1pt[nTriplets]", triplet_jet1pt);
  fOutTree->Branch("triplet_jet2pt[nTriplets]", triplet_jet2pt);
  fOutTree->Branch("triplet_jet3pt[nTriplets]", triplet_jet3pt);
  fOutTree->Branch("triplet_sumScalarPt[nTriplets]",triplet_sumScalarPt);
  fOutTree->Branch("triplet_mass[nTriplets]",triplet_mass);
  fOutTree->Branch("triplet_sumVectorPt[nTriplets]",triplet_sumVectorPt);

  fOutTree->Branch("triplet_jet1px[nTriplets]", triplet_jet1px);
  fOutTree->Branch("triplet_jet1py[nTriplets]", triplet_jet1py);
  fOutTree->Branch("triplet_jet1pz[nTriplets]", triplet_jet1pz);
  fOutTree->Branch("triplet_jet1e[nTriplets]", triplet_jet1e);


  fOutTree->Branch("triplet_jet2px[nTriplets]", triplet_jet2px);
  fOutTree->Branch("triplet_jet2py[nTriplets]", triplet_jet2py);
  fOutTree->Branch("triplet_jet2pz[nTriplets]", triplet_jet2pz);
  fOutTree->Branch("triplet_jet2e[nTriplets]", triplet_jet2e);


  fOutTree->Branch("triplet_jet3px[nTriplets]", triplet_jet3px);
  fOutTree->Branch("triplet_jet3py[nTriplets]", triplet_jet3py);
  fOutTree->Branch("triplet_jet3pz[nTriplets]", triplet_jet3pz);
  fOutTree->Branch("triplet_jet3e[nTriplets]", triplet_jet3e);

 


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


void NtpReader::FillTree ()
{
  fOutTree->Fill();
}
