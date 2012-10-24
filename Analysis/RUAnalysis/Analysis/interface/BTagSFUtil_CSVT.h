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


class BTagSFUtil{

 public:
    
  BTagSFUtil( int seed=0 );
  ~BTagSFUtil();
    
  void modifyBTagsWithSF( bool& isBTagged, int pdgIdPart, float Btag_SF = 0.98, float Btag_eff = 1.0, float Bmistag_SF = 1.0, float  Bmistag_eff = 1.0);
  float GetLightJeteff (float pt = 40, float eta = 1.3, int meanminmax = 0);
  float GetBTagSF (float pt = 40, float eta = 1.3, int meanminmax = 0);
  float GetBTageff ();
  float GetLightJetSF (float pt = 40, float eta = 1.3, int meanminmax = 0);


 private:
  
  bool applySF(bool& isBTagged, float Btag_SF = 0.98, float Btag_eff = 1.0);
  
  TRandom3* rand_;

};


BTagSFUtil::BTagSFUtil( int seed ) {

  rand_ = new TRandom3(seed);

}

BTagSFUtil::~BTagSFUtil() {

  delete rand_;

}


void BTagSFUtil::modifyBTagsWithSF(bool& isBTagged, int pdgIdPart, float Btag_SF, float Btag_eff, float Bmistag_SF, float Bmistag_eff){

  bool newBTag = isBTagged;

  // b quarks and c quarks:
  if( abs( pdgIdPart ) == 5 ||  abs( pdgIdPart ) == 4) { 

    double bctag_eff = Btag_eff;
    if ( abs(pdgIdPart)==4 )  bctag_eff = Btag_eff; // take ctag eff = tag eff
    newBTag = applySF(isBTagged, Btag_SF, bctag_eff);

    // light quarks:
  } else if( abs( pdgIdPart )>0 ) { //in data it is 0 (save computing time)

    newBTag = applySF(isBTagged, Bmistag_SF, Bmistag_eff);
    
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
      float mistagPercent = (1.0 - Btag_SF) / (1.0 - (Btag_SF/Btag_eff) );

      //upgrade to tagged
      if( coin < mistagPercent ) {newBTag = true;}
    }

  }else{  // use this if SF<1
      
    //downgrade tagged to untagged
    if( isBTagged && coin > Btag_SF ) {newBTag = false;}

  }

  return newBTag;
}
float BTagSFUtil::GetBTagSF (float pt, float eta, int meanminmax){
  float x=pt;
  float ptmin[] = {30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500};
  float ptmax[] = {40, 50, 60, 70, 80,100, 120, 160, 210, 260, 320, 400, 500, 670};
  // Tagger: CSVT within 30 < pt < 670 GeV, abs(eta) < 2.4, x = pt

float  SFb_error[] = {   0.0364717,   0.0362281,   0.0232876,   0.0249618,   0.0261482,
		   0.0290466,   0.0300033,   0.0453252,   0.0685143,   0.0653621,
		   0.0712586,   0.094589,   0.0777011,   0.0866563 };
 float tmpSFbError=0;
  //inflate uncertainty by 1.5 fo 2012 for now -> still need higher uncertainty for c-tags (include parton flavor in function)
  float UncertFactor=1.5;
  for(unsigned int i= 0; i<15; i++){
    if(ptmin[i]<x && x<=ptmax[i])tmpSFbError=SFb_error[i]*UncertFactor;
  }
  //cout<<tmpSFbError<<endl;
  float tmpSFb = 1;
  
  if( meanminmax == 0 )  tmpSFb = 0.901615*((1.+(0.552628*x))/(1.+(0.547195*x)));
  if( meanminmax == -1 ) tmpSFb = 0.901615*((1.+(0.552628*x))/(1.+(0.547195*x)))- tmpSFbError;
  if( meanminmax == 1 ) tmpSFb = 0.901615*((1.+(0.552628*x))/(1.+(0.547195*x)))+ tmpSFbError;
  return tmpSFb;
}

float BTagSFUtil::GetBTageff (){
  float y=0.898;
  float effb=1;
  effb = -4.46932526854*y*y*y*y+7.32781975653*y*y*y-3.78459588569*y*y+0.221027515486*y+0.970299300468;
  //effb_err_max = -2.28719954194*y*y*y*y+1.80361455348*y*y*y+1.18308812929*y*y-1.58926423122*y+1.22173072594;


  
  return effb;
}

float BTagSFUtil::GetLightJetSF (float pt, float eta, int meanminmax){
  float x=pt; 
  float tmpSFl=1;
  if(fabs(eta)>=0.0 &&  fabs(eta) <=2.4){
    if( meanminmax == 0 ) tmpSFl = ((0.948463+(0.00288102*x))+(-7.98091e-06*(x*x)))+(5.50157e-09*(x*(x*x)));
    if( meanminmax == -1 ) tmpSFl = ((0.899715+(0.00102278*x))+(-2.46335e-06*(x*x)))+(9.71143e-10*(x*(x*x)));
    if( meanminmax == 1 ) tmpSFl = ((0.997077+(0.00473953*x))+(-1.34985e-05*(x*x)))+(1.0032e-08*(x*(x*x)));
  }
  
      return tmpSFl;

}

float BTagSFUtil::GetLightJeteff (float pt, float eta, int meanminmax){
  float x=pt;
  float tmpMistag=1;
  if(fabs(eta)>=0.0 &&  fabs(eta) <=2.4)
    
    {
      if( meanminmax == 0 ) tmpMistag = 0.00315116*(((1+(-0.00769281*x))+(2.58066e-05*(x*x)))+(-2.02149e-08*(x*(x*x))));

    }


    return tmpMistag;

}

#endif

