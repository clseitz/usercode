 //Defines general ntuple objects
//object selection for leptons
#include "RUAnalysis/Ntupler/interface/NtpReader.h"


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
  fChain.SetName("EvTree");
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

  Tree->Branch("pdgID[200]",pdgID);
  Tree->Branch("MCpx[200]", MCpx);
  Tree->Branch("MCpy[200]", MCpy);
  Tree->Branch("MCpz[200]", MCpz);
  Tree->Branch("MCe[200]", MCe);
  
 
  Tree->Branch("nElectrons", &nElectrons);
  Tree->Branch("nMuons", &nMuons);
  Tree->Branch("nPhotons", &nPhotons);
  Tree->Branch("nTriplets", &nTriplets);
  Tree->Branch("nGoodVtx", &nGoodVtx);
  ///////////////////////////
  //JETS
  /////////////////////////////
  /////PF jets AK5
  Tree->Branch("nPFJets", &nPFJets);
  Tree->Branch("jet_PF_pt[nPFJets]", jet_PF_pt);

  Tree->Branch("jet_PF_et[nPFJets]", jet_PF_et);
  Tree->Branch("jet_PF_eta[nPFJets]", jet_PF_eta);
  Tree->Branch("jet_PF_phi[nPFJets]", jet_PF_phi);
  Tree->Branch("jet_PF_theta[nPFJets]", jet_PF_theta);
  Tree->Branch("jet_PF_mass[nPFJets]", jet_PF_mass);
  Tree->Branch("jet_PF_area[nPFJets]", jet_PF_area);
  Tree->Branch("jet_PF_nJetDaughters[nPFJets]", jet_PF_nJetDaughters);

  Tree->Branch("jet_PF_px[nPFJets]", jet_PF_px);
  Tree->Branch("jet_PF_py[nPFJets]", jet_PF_py);
  Tree->Branch("jet_PF_pz[nPFJets]", jet_PF_pz);
  Tree->Branch("jet_PF_e[nPFJets]", jet_PF_e);

  Tree->Branch("bdiscTCHE_PF[nPFJets]", bdiscTCHE_PF);
  Tree->Branch("bdiscTCHP_PF[nPFJets]", bdiscTCHP_PF);
  Tree->Branch("bdiscSSVHE_PF[nPFJets]", bdiscSSVHE_PF);
  Tree->Branch("bdiscSSSVHP_PF[nPFJets]", bdiscSSSVHP_PF);
  Tree->Branch("bdiscCSV_PF[nPFJets]", bdiscCSV_PF);
  Tree->Branch("bdiscJP_PF[nPFJets]", bdiscJP_PF);
  ///////////////////////////////////////////////////
  //CA8 jets
  ///////////////////////////////////////////////////
  Tree->Branch("nCA8PFJets", &nCA8PFJets);
  Tree->Branch("jet_CA8PF_pt[nCA8PFJets]", jet_CA8PF_pt);

  Tree->Branch("jet_CA8PF_et[nCA8PFJets]", jet_CA8PF_et);
  Tree->Branch("jet_CA8PF_eta[nCA8PFJets]", jet_CA8PF_eta);
  Tree->Branch("jet_CA8PF_phi[nCA8PFJets]", jet_CA8PF_phi);
  Tree->Branch("jet_CA8PF_theta[nCA8PFJets]", jet_CA8PF_theta);
  Tree->Branch("jet_CA8PF_mass[nCA8PFJets]", jet_CA8PF_mass);
  Tree->Branch("jet_CA8PF_area[nCA8PFJets]", jet_CA8PF_area);
  Tree->Branch("jet_CA8PF_nJetDaughters[nCA8PFJets]", jet_CA8PF_nJetDaughters);

  Tree->Branch("jet_CA8PF_px[nCA8PFJets]", jet_CA8PF_px);
  Tree->Branch("jet_CA8PF_py[nCA8PFJets]", jet_CA8PF_py);
  Tree->Branch("jet_CA8PF_pz[nCA8PFJets]", jet_CA8PF_pz);
  Tree->Branch("jet_CA8PF_e[nCA8PFJets]", jet_CA8PF_e);
  Tree->Branch("bdiscTCHE_CA8PF[nCA8PFJets]", bdiscTCHE_CA8PF);
  Tree->Branch("bdiscTCHP_CA8PF[nCA8PFJets]", bdiscTCHP_CA8PF);
  Tree->Branch("bdiscSSVHE_CA8PF[nCA8PFJets]", bdiscSSVHE_CA8PF);
  Tree->Branch("bdiscSSSVHP_CA8PF[nCA8PFJets]", bdiscSSSVHP_CA8PF);
  Tree->Branch("bdiscCSV_CA8PF[nCA8PFJets]", bdiscCSV_CA8PF);
  Tree->Branch("bdiscJP_CA8PF[nCA8PFJets]", bdiscJP_CA8PF);
  //////////////////////////////////////////////////////////
  //CA8 pruned Jet
  /////////////////////////////////////////////////////////
  Tree->Branch("nCA8PrunedPFJets", &nCA8PrunedPFJets);
  Tree->Branch("jet_CA8PrunedPF_pt[nCA8PrunedPFJets]", jet_CA8PrunedPF_pt);
  Tree->Branch("jet_CA8PrunedPF_et[nCA8PFJets]", jet_CA8PrunedPF_et);
  Tree->Branch("jet_CA8PrunedPF_eta[nCA8PrunedPFJets]", jet_CA8PrunedPF_eta);
  Tree->Branch("jet_CA8PrunedPF_phi[nCA8PrunedPFJets]", jet_CA8PrunedPF_phi);
  Tree->Branch("jet_CA8PrunedPF_theta[nCA8PrunedPFJets]", jet_CA8PrunedPF_theta);
  Tree->Branch("jet_CA8PrunedPF_mass[nCA8PrunedPFJets]", jet_CA8PrunedPF_mass);
  Tree->Branch("jet_CA8PrunedPF_area[nCA8PrunedPFJets]", jet_CA8PrunedPF_area);
  Tree->Branch("jet_CA8PrunedPF_nJetDaughters[nCA8PrunedPFJets]", jet_CA8PrunedPF_nJetDaughters);

  Tree->Branch("jet_CA8PrunedPF_subJet1_mass[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet1_mass);
  Tree->Branch("jet_CA8PrunedPF_subJet2_mass[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet2_mass);
  Tree->Branch("jet_CA8PrunedPF_subJet3_mass[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet3_mass);

  Tree->Branch("jet_CA8PrunedPF_subJet1_px[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet1_px);
  Tree->Branch("jet_CA8PrunedPF_subJet2_px[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet2_px);
  Tree->Branch("jet_CA8PrunedPF_subJet3_px[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet3_px);

  Tree->Branch("jet_CA8PrunedPF_subJet1_py[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet1_py);
  Tree->Branch("jet_CA8PrunedPF_subJet2_py[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet2_py);
  Tree->Branch("jet_CA8PrunedPF_subJet3_py[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet3_py);

  Tree->Branch("jet_CA8PrunedPF_subJet1_pz[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet1_pz);
  Tree->Branch("jet_CA8PrunedPF_subJet2_pz[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet2_pz);
  Tree->Branch("jet_CA8PrunedPF_subJet3_pz[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet3_pz);

  Tree->Branch("jet_CA8PrunedPF_subJet1_e[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet1_e);
  Tree->Branch("jet_CA8PrunedPF_subJet2_e[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet2_e);
  Tree->Branch("jet_CA8PrunedPF_subJet3_e[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet3_e);


  Tree->Branch("jet_CA8PrunedPF_px[nCA8PrunedPFJets]", jet_CA8PrunedPF_px);
  Tree->Branch("jet_CA8PrunedPF_py[nCA8PrunedPFJets]", jet_CA8PrunedPF_py);
  Tree->Branch("jet_CA8PrunedPF_pz[nCA8PrunedPFJets]", jet_CA8PrunedPF_pz);
  Tree->Branch("jet_CA8PrunedPF_e[nCA8PrunedPFJets]", jet_CA8PrunedPF_e);
  Tree->Branch("bdiscTCHE_CA8PrunedPF[nCA8PrunedPFJets]", bdiscTCHE_CA8PrunedPF);
  Tree->Branch("bdiscTCHP_CA8PrunedPF[nCA8PrunedPFJets]", bdiscTCHP_CA8PrunedPF);
  Tree->Branch("bdiscSSVHE_CA8PrunedPF[nCA8PrunedPFJets]", bdiscSSVHE_CA8PrunedPF);
  Tree->Branch("bdiscSSSVHP_CA8PrunedPF[nCA8PrunedPFJets]", bdiscSSSVHP_CA8PrunedPF);
   Tree->Branch("bdiscCSV_CA8PrunedPF[nCA8PrunedPFJets]", bdiscCSV_CA8PrunedPF);
  Tree->Branch("bdiscJP_CA8PrunedPF[nCA8PrunedPFJets]", bdiscJP_CA8PrunedPF);


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
  Tree->Branch("mPFIso[nMuons]", mPFIso);


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
 
    fChain.SetBranchAddress("pdgID[200]",pdgID);
    fChain.SetBranchAddress("MCpx[200]", MCpx);
    fChain.SetBranchAddress("MCpy[200]", MCpy);
    fChain.SetBranchAddress("MCpz[200]", MCpz);
    fChain.SetBranchAddress("MCe[200]", MCe);
 

  fChain.SetBranchAddress("nElectrons", &nElectrons);
  fChain.SetBranchAddress("nMuons", &nMuons);
  fChain.SetBranchAddress("nPhotons", &nPhotons);
  fChain.SetBranchAddress("nTriplets", &nTriplets);
  fChain.SetBranchAddress("nGoodVtx", &nGoodVtx);

  fChain.SetBranchAddress("nPFJets", &nPFJets);
  fChain.SetBranchAddress("jet_PF_pt[nPFJets]", jet_PF_pt);
   fChain.SetBranchAddress("jet_PF_et[nPFJets]", jet_PF_et);
   fChain.SetBranchAddress("jet_PF_eta[nPFJets]", jet_PF_eta);
   fChain.SetBranchAddress("jet_PF_phi[nPFJets]", jet_PF_phi);
   fChain.SetBranchAddress("jet_PF_theta[nPFJets]", jet_PF_theta);
   fChain.SetBranchAddress("jet_PF_mass[nPFJets]", jet_PF_mass);
   fChain.SetBranchAddress("jet_PF_area[nPFJets]", jet_PF_area);
   fChain.SetBranchAddress("jet_PF_mass[nPFJets]", jet_PF_nJetDaughters);

  fChain.SetBranchAddress("jet_PF_px[nPFJets]", jet_PF_px);
  fChain.SetBranchAddress("jet_PF_py[nPFJets]", jet_PF_py);
  fChain.SetBranchAddress("jet_PF_pz[nPFJets]", jet_PF_pz);
  fChain.SetBranchAddress("jet_PF_e[nPFJets]", jet_PF_e);
  fChain.SetBranchAddress("bdiscTCHE_PF[nPFJets]", bdiscTCHE_PF);
  fChain.SetBranchAddress("bdiscTCHP_PF[nPFJets]", bdiscTCHP_PF);
  fChain.SetBranchAddress("bdiscSSVHE_PF[nPFJets]", bdiscSSVHE_PF);
  fChain.SetBranchAddress("bdiscSSSVHP_PF[nPFJets]", bdiscSSSVHP_PF);
   fChain.SetBranchAddress("bdiscCSV_PF[nPFJets]", bdiscCSV_PF);
   fChain.SetBranchAddress("bdiscJP_PF[nPFJets]", bdiscJP_PF);

  fChain.SetBranchAddress("nCA8PFJets", &nCA8PFJets);
  fChain.SetBranchAddress("jet_CA8PF_pt[nCA8PFJets]", jet_CA8PF_pt);
   fChain.SetBranchAddress("jet_CA8PF_et[nCA8PFJets]", jet_CA8PF_et);
   fChain.SetBranchAddress("jet_CA8PF_eta[nCA8PFJets]", jet_CA8PF_eta);
   fChain.SetBranchAddress("jet_CA8PF_phi[nCA8PFJets]", jet_CA8PF_phi);
   fChain.SetBranchAddress("jet_CA8PF_theta[nCA8PFJets]", jet_CA8PF_theta);
   fChain.SetBranchAddress("jet_CA8PF_mass[nCA8PFJets]", jet_CA8PF_mass);
   fChain.SetBranchAddress("jet_CA8PF_area[nCA8PFJets]", jet_CA8PF_area);
   fChain.SetBranchAddress("jet_CA8PF_mass[nCA8PFJets]", jet_CA8PF_nJetDaughters);

  fChain.SetBranchAddress("jet_CA8PF_px[nCA8PFJets]", jet_CA8PF_px);
  fChain.SetBranchAddress("jet_CA8PF_py[nCA8PFJets]", jet_CA8PF_py);
  fChain.SetBranchAddress("jet_CA8PF_pz[nCA8PFJets]", jet_CA8PF_pz);
  fChain.SetBranchAddress("jet_CA8PF_e[nCA8PFJets]", jet_CA8PF_e);
  fChain.SetBranchAddress("bdiscTCHE_CA8PF[nCA8PFJets]", bdiscTCHE_CA8PF);
  fChain.SetBranchAddress("bdiscTCHP_CA8PF[nCA8PFJets]", bdiscTCHP_CA8PF);
  fChain.SetBranchAddress("bdiscSSVHE_CA8PF[nCA8PFJets]", bdiscSSVHE_CA8PF);
  fChain.SetBranchAddress("bdiscSSSVHP_CA8PF[nCA8PFJets]", bdiscSSSVHP_CA8PF);
   fChain.SetBranchAddress("bdiscCSV_CA8PF[nCA8PFJets]", bdiscCSV_CA8PF);
   fChain.SetBranchAddress("bdiscJP_CA8PF[nCA8PFJets]", bdiscJP_CA8PF);

  fChain.SetBranchAddress("nCA8PrunedPFJets", &nCA8PrunedPFJets);
  fChain.SetBranchAddress("jet_CA8PrunedPF_pt[nCA8PrunedPFJets]", jet_CA8PrunedPF_pt);
   fChain.SetBranchAddress("jet_CA8PrunedPF_pt[nCA8PrunedPFJets]", jet_CA8PrunedPF_pt);
   fChain.SetBranchAddress("jet_CA8PrunedPF_et[nCA8PFJets]", jet_CA8PrunedPF_et);
   fChain.SetBranchAddress("jet_CA8PrunedPF_eta[nCA8PrunedPFJets]", jet_CA8PrunedPF_eta);
   fChain.SetBranchAddress("jet_CA8PrunedPF_phi[nCA8PrunedPFJets]", jet_CA8PrunedPF_phi);
   fChain.SetBranchAddress("jet_CA8PrunedPF_theta[nCA8PrunedPFJets]", jet_CA8PrunedPF_theta);
   fChain.SetBranchAddress("jet_CA8PrunedPF_mass[nCA8PrunedPFJets]", jet_CA8PrunedPF_mass);
   fChain.SetBranchAddress("jet_CA8PrunedPF_area[nCA8PrunedPFJets]", jet_CA8PrunedPF_area);
   fChain.SetBranchAddress("jet_CA8PrunedPF_mass[nCA8PrunedPFJets]", jet_CA8PrunedPF_nJetDaughters);
   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet1_mass[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet1_mass);
   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet2_mass[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet2_mass);
   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet3_mass[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet3_mass);

   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet1_px[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet1_px);
   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet2_px[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet2_px);
   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet3_px[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet3_px);

   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet1_py[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet1_py);
   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet2_py[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet2_py);
   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet3_py[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet3_py);

   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet1_pz[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet1_pz);
   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet2_pz[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet2_pz);
   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet3_pz[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet3_pz);

   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet1_e[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet1_e);
   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet2_e[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet2_e);
   fChain.SetBranchAddress("jet_CA8PrunedPF_subJet3_e[nCA8PrunedPFJets]", jet_CA8PrunedPF_subJet3_e);


  fChain.SetBranchAddress("jet_CA8PrunedPF_px[nCA8PrunedPFJets]", jet_CA8PrunedPF_px);
  fChain.SetBranchAddress("jet_CA8PrunedPF_py[nCA8PrunedPFJets]", jet_CA8PrunedPF_py);
  fChain.SetBranchAddress("jet_CA8PrunedPF_pz[nCA8PrunedPFJets]", jet_CA8PrunedPF_pz);
  fChain.SetBranchAddress("jet_CA8PrunedPF_e[nCA8PrunedPFJets]", jet_CA8PrunedPF_e);
  fChain.SetBranchAddress("bdiscTCHE_CA8PrunedPF[nCA8PrunedPFJets]", bdiscTCHE_CA8PrunedPF);
  fChain.SetBranchAddress("bdiscTCHP_CA8PrunedPF[nCA8PrunedPFJets]", bdiscTCHP_CA8PrunedPF);
  fChain.SetBranchAddress("bdiscSSVHE_CA8PrunedPF[nCA8PrunedPFJets]", bdiscSSVHE_CA8PrunedPF);
  fChain.SetBranchAddress("bdiscSSSVHP_CA8PrunedPF[nCA8PrunedPFJets]", bdiscSSSVHP_CA8PrunedPF);
   fChain.SetBranchAddress("bdiscCSV_CA8PrunedPF[nCA8PrunedPFJets]", bdiscCSV_CA8PrunedPF);
   fChain.SetBranchAddress("bdiscJP_CA8PrunedPF[nCA8PrunedPFJets]", bdiscJP_CA8PrunedPF);

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
  fChain.SetBranchAddress("mPFIso[nMuons]", mPFIso);

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


