/*************************************************************

Class Usage:

This class should only be used for upgrading and downgrading 
if a single operating point is used in an analysis. 

bool isBTagged = b-tag flag for jet
int pdgIdPart = parton id
float Btag_SF = MC/data scale factor for b/c-tagging efficiency
float Btag_eff = b/c-tagging efficiency in data
float Bmistag_SF = MC/data scale factor for mistag efficiency
float Bmistag_eff = mistag efficiency in data

Author: Michael Segala
Contact: michael.segala@gmail.com
Updated: Ulrich Heintz 12/23/2011

v 1.1

*************************************************************/


#ifndef BTagSFUtil_lite_h
#define BTagSFUtil_lite_h

#include <Riostream.h>
#include "TRandom3.h"
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "NtpThreeJet.h"

class BTagSFUtil{

 public:
    
  BTagSFUtil( int seed=0 );
  ~BTagSFUtil();
    
  void modifyBTagsWithSF( bool& isBTagged, int pdgIdPart, float Btag_SF = 0.98, float Btag_eff = 1.0,float Ctag_SF = 0.98, float Ctag_eff = 1.0, float UDSGtag_SF = 0.98, float UDSGtag_eff = 1.0);
 private:
  
  bool applySF(bool& isBTagged, float Btag_SF = 0.98, float Btag_eff = 1.0);
  
  TRandom3* rand_;

};


BTagSFUtil::BTagSFUtil( int seed ) {

  rand_ = new TRandom3(seed);

}

BTagSFUtil::~BTagSFUtil() {

  delete rand_;
  //delete CSVM_SFb_0to2p4;
  //delete CSVM_SFb_errors;

}


void BTagSFUtil::modifyBTagsWithSF(bool& isBTagged, int pdgIdPart, float Btag_SF, float Btag_eff, float Ctag_SF, float Ctag_eff,float UDSG_SF, float UDSG_eff){

  bool newBTag = isBTagged;

  // b quarks 
  if( abs( pdgIdPart ) == 5) { 

    newBTag = applySF(isBTagged, Btag_SF, Btag_eff);
  }
  if( abs( pdgIdPart ) == 4) { 

    newBTag = applySF(isBTagged, Ctag_SF, Ctag_eff);

    // light quarks:
  } else if( abs( pdgIdPart )>0 ) { //in data it is 0 (save computing time)

    newBTag = applySF(isBTagged, UDSG_SF, UDSG_eff);
    
  }

  isBTagged = newBTag;

}


bool BTagSFUtil::applySF(bool& isBTagged, float Btag_SF, float Btag_eff){
  
  bool newBTag = isBTagged;

  if (Btag_SF == 1) return newBTag; //no correction needed 

  //throw die
  float coin = rand_->Uniform(1.);    

  if(Btag_SF > 1){  // use this if SF>1

    if( !isBTagged ) {

      //fraction of jets that need to be upgraded
      //      float mistagPercent = (1.0 - Btag_SF) / (1.0 - (Btag_SF/Btag_eff) );
      float mistagPercent = (1.0 - Btag_SF) / (1.0 - (1.0/Btag_eff) );
      //upgrade to tagged
      if( coin < mistagPercent ) {newBTag = true;}
    }

  }else{  // use this if SF<1
      
    //downgrade tagged to untagged
    if( isBTagged && coin > Btag_SF ) {newBTag = false;}

  }

  return newBTag;
}


#endif

