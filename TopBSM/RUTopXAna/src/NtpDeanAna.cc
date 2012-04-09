#include "TopBSM/RUTopXAna/interface/NtpDeanAna.h"
#include "TopBSM/RUTopXAna/interface/TAnaHist.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "TLorentzVector.h"
#include "TFile.h"


NtpDeanAna::NtpDeanAna (std::vector<TString>& InFileNames, bool const IsData, TString const OutFileName) : NtpReader(InFileNames, IsData)
{
  fOutFile = new TFile(OutFileName, "recreate");
  if (!fOutFile->IsOpen()) {
    std::cerr << "ERROR: cannot open output root file " << OutFileName << std::endl;
    throw;
  }
}


NtpDeanAna::~NtpDeanAna ()
{
  if (fOutFile) {
    fOutFile->Write();
    fOutFile->Close();
    delete fOutFile;
  }
}


 

void NtpDeanAna::Loop ()
{
  // Run over all entries and do what you like!

  for (int ientry = 0; GetEntry(ientry) > 0; ++ientry) {
    if (ientry % 1000 == 0) {
      printf("Processing entry: %i\n", ientry);
    }
    std::cout<<"should be 4000023 "<<MCpz[0]<<" should 24 "<<pdgID[10]<<" should be 6 "<<pdgID[9]<<std::endl;
    // Analysis code call here
    DileptonEvents();
    LeptonPlusJetsEvents();


  }

  return;
}





void NtpDeanAna::LeptonPlusJetsEvents ()
{
  // Plot a few fun things related to a single lepton plus some jets

  // Get a histogramming object
  static TAnaHist Hist(fOutFile, "LeptonPlusJetsEvents");

  // Check for two leptons
  if (nElectrons + nMuons != 1) {
    return;
  }

  // Set the lepton TLorV
  TLorentzVector Lep;
  if (nElectrons) {
    Lep.SetPxPyPzE(epx[0], epy[0], epz[0], ee[0]);
  } else {
    Lep.SetPxPyPzE(mpx[0], mpy[0], mpz[0], me[0]);
  }

  // Set the Jet 4-vectors
  std::vector<TLorentzVector> Jet;
  std::vector<TLorentzVector> BTagJet;
  std::vector<bool> JetBTag;

  // Keep track of the number of BTags
  int NBtags = 0;
  for (int i = 0; i != nJets; ++i) {
    Jet.push_back( TLorentzVector(jetpx[i], jetpy[i], jetpz[i], jete[i]) );
    if (bdiscSSVHE[i] > 1.74) {
      BTagJet.push_back(Jet[i]);
      JetBTag.push_back(true);
      ++NBtags;
    } else {
      JetBTag.push_back(false);
    }
  }

  // Get the charge of the lepton and the type
  int const Charge = nElectrons ? echarge[0] : mcharge[0];
  TString const Type = nElectrons ? "e" : "m";

  // Plot Pt of lepton
  Hist.FillTH1F("LeptonPt",       "Lepton P_{T}",      "P_{T} [GeV]", "Events", 100, 0, 200, Lep.Pt());
  Hist.FillTH1F("LeptonPt_"+Type, "Lepton P_{T}"+Type, "P_{T} [GeV]", "Events", 100, 0, 200, Lep.Pt());

  Hist.FillTH1F("LeptonPtQ",       "Lepton P_{T}Q",      "P_{T}Q", "Events", 100, -200, 200, Lep.Pt() * Charge);
  Hist.FillTH1F("LeptonPtQ_"+Type, "Lepton P_{T}Q"+Type, "P_{T}Q", "Events", 100, -200, 200, Lep.Pt() * Charge);

  // if there is one btag
  if (NBtags == 1) {
    // deltaR between lepton and btagjet
    Hist.FillTH1F("DeltaR_1BTagLep",       "#Delta R_{lb}",       "#Delta R_{lb}", "Events", 50, 0, 4, Lep.DeltaR(BTagJet[0]));
    Hist.FillTH1F("DeltaR_1BTagLep_"+Type, "#Delta R_{lb} "+Type, "#Delta R_{lb}", "Events", 50, 0, 4, Lep.DeltaR(BTagJet[0]));
  }

  // If there are 2 btags
  if (NBtags == 2) {
    // deltaR betweeb btagjets
    Hist.FillTH1F("DeltaR_BB",       "#Delta R_{bb}",       "#Delta R_{bb}", "Events", 50, 0, 4, Lep.DeltaR(BTagJet[0]));
    Hist.FillTH1F("DeltaR_BB_"+Type, "#Delta R_{bb} "+Type, "#Delta R_{bb}", "Events", 50, 0, 4, Lep.DeltaR(BTagJet[0]));
  }


  // search for closest jet pair to wmass
  if (Jet.size() - NBtags >= 2) {
    std::pair<size_t, size_t> Wjets;
    float SmallestDifference = 9999;
    for (size_t i = 0; i < Jet.size() - 1; ++i) {
      if (JetBTag[i]) {
        continue;
      }
      for (size_t j = i + 1; j < Jet.size(); ++j) {
        if (JetBTag[j]) {
          continue;
        }
        float const Mass = (Jet[i]+Jet[j]).M();
        if ( fabs(Mass - 80.4) < SmallestDifference ) {
          Wjets.first = i;
          Wjets.second = j;
          SmallestDifference = fabs(Mass - 80.4);
        }
      }
    }
    if (SmallestDifference != 9999) {
      std::cout << "ClosestMass = " << (Jet[Wjets.first]+Jet[Wjets.second]).M() << std::endl;
      Hist.FillTH1F("W_JJMass", "Closest JJ to WMass", "Mass [GeV]", "Events", 50, 0, 150, (Jet[Wjets.first]+Jet[Wjets.second]).M());
    }
  }


  return;
}






void NtpDeanAna::DileptonEvents ()
{
  // Plot a few things for dilepton events

  // Get a histogramming object
  static TAnaHist Hist(fOutFile, "DileptonEvents");

  // Check for two leptons
  if (nElectrons + nMuons != 2) {
    return;
  }

  // Vector of leptons
  std::vector<TLorentzVector> Lep;

  // Get the dilepton type
  TString const DilType = nElectrons - nMuons < 0 ? "mm" :
                          nElectrons == nMuons ? "em" : "ee";

  // Let's keep track of the charge:
  int ChargeSum = 0;

  // Fill vector
  for (int i = 0; i != nElectrons; ++i) {
    Lep.push_back( TLorentzVector(epx[i], epy[i], epz[i], ee[i]) );
    ChargeSum += echarge[i];
  }
  for (int i = 0; i != nMuons; ++i) {
    Lep.push_back( TLorentzVector(mpx[i], mpy[i], mpz[i], me[i]) );
    ChargeSum += mcharge[i];
  }

  // Fill a plot of dilepton mass
  Hist.FillTH1F("DileptonMass_"+DilType, "Dilepton Mass for "+DilType, "m_{ll} [GeV]", "Events", 100, 0, 200, (Lep[0] + Lep[1]).M());



  return;
}
