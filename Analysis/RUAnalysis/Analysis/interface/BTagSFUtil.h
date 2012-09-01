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
  // Tagger: CSVM within 30 < pt < 670 GeV, abs(eta) < 2.4, x = pt

float  SFb_error[] = {    0.0295675,    0.0295095,    0.0210867,    0.0219349,    0.0227033,
		     0.0204062,    0.0185857,    0.0256242,    0.0383341,    0.0409675,
		     0.0420284,    0.0541299,    0.0578761,    0.0655432 };
  float tmpSFbError=0;
  //inflate uncertainty by 1.5 fo 2012 for now -> still need higher uncertainty for c-tags (include parton flavor in function)
  float UncertFactor=1.5;
  for(unsigned int i= 0; i<15; i++){
    if(ptmin[i]<x && x<=ptmax[i])tmpSFbError=SFb_error[i]*UncertFactor;
  }
  //cout<<tmpSFbError<<endl;
  float tmpSFb = 1;
  
    if( meanminmax == 0 )  tmpSFb = 0.6981*((1.+(0.414063*x))/(1.+(0.300155*x)));
  if( meanminmax == -1 ) tmpSFb = 0.6981*((1.+(0.414063*x))/(1.+(0.300155*x)))- tmpSFbError;
  if( meanminmax == 1 ) tmpSFb = 0.6981*((1.+(0.414063*x))/(1.+(0.300155*x)))+ tmpSFbError;
  return tmpSFb;
}

float BTagSFUtil::GetBTageff (){
  float x=0.679;
  float effb=1;
  effb = -1.73338329789*x*x*x*x +  1.26161794785*x*x*x +  0.784721653518*x*x +  -1.03328577451*x +  1.04305075822;
  
  return effb;
}

float BTagSFUtil::GetLightJetSF (float pt, float eta, int meanminmax){
  float x=pt; 
  float tmpSFl=1;

  if(fabs(eta)>=0.0 &&  fabs(eta) <=0.8)
    {
      if( meanminmax == 0 ) tmpSFl = ((1.06182+(0.000617034*x))+(-1.5732e-06*(x*x)))+(3.02909e-10*(x*(x*x)));
      if( meanminmax == -1 ) tmpSFl = ((0.972455+(7.51396e-06*x))+(4.91857e-07*(x*x)))+(-1.47661e-09*(x*(x*x)));
      if( meanminmax == 1 ) tmpSFl = ((1.15116+(0.00122657*x))+(-3.63826e-06*(x*x)))+(2.08242e-09*(x*(x*x)));
    }
  if(fabs(eta)>=0.8 &&  fabs(eta) <=1.6)

    {
      if( meanminmax == 0 ) tmpSFl = ((1.111+(-9.64191e-06*x))+(1.80811e-07*(x*x)))+(-5.44868e-10*(x*(x*x)));
      if( meanminmax == -1 ) tmpSFl = ((1.02055+(-0.000378856*x))+(1.49029e-06*(x*x)))+(-1.74966e-09*(x*(x*x)));
      if( meanminmax == 1 ) tmpSFl = ((1.20146+(0.000359543*x))+(-1.12866e-06*(x*x)))+(6.59918e-10*(x*(x*x)));
    }
  if(fabs(eta)>=1.6 &&  fabs(eta) <=2.4)
    {
      if( meanminmax == 0 ) tmpSFl = ((1.08498+(-0.000701422*x))+(3.43612e-06*(x*x)))+(-4.11794e-09*(x*(x*x)));
      if( meanminmax == -1 ) tmpSFl = ((0.983476+(-0.000607242*x))+(3.17997e-06*(x*x)))+(-4.01242e-09*(x*(x*x)));
      if( meanminmax == 1 ) tmpSFl = ((1.18654+(-0.000795808*x))+(3.69226e-06*(x*x)))+(-4.22347e-09*(x*(x*x)));
    }
  
      return tmpSFl;

}

float BTagSFUtil::GetLightJeteff (float pt, float eta, int meanminmax){
  float x=pt;
  float tmpMistag=1;
  if(fabs(eta)>=0.0 &&  fabs(eta) <=0.8)
    
    {
      if( meanminmax == 0 ) tmpMistag = (0.00967751+(2.54564e-05*x))+(-6.92256e-10*(x*x));
    }
  if(fabs(eta)>=0.8 &&  fabs(eta) <=1.6)
    
    {
      if( meanminmax == 0 ) tmpMistag = (0.00974141+(5.09503e-05*x))+(2.0641e-08*(x*x));
    }
  if(fabs(eta)>=1.6 &&  fabs(eta) <=2.4)
    {
      if( meanminmax == 0 ) tmpMistag = (0.013595+(0.000104538*x))+(-1.36087e-08*(x*x));
    }  


    return tmpMistag;

}

#endif

