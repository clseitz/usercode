#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TObject.h"
#include "THStack.h"
#include <sstream>
#include "TH1F.h"
#include "TH2F.h"
#include "math.h"
#include "TF1.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"

#include <sstream>
template <class T>
inline std::string to_string (const T& t)
{
  std::stringstream ss;
  ss << t;
  return ss.str();
}
void make_Sys(string flavor = "112", int WhichCuts = 0,string Sys="PU")
{
  vector <TFile* > filelist;
  //explanation for WhichCuts variable:
  //for model 112 there is only one set of cuts so WhichCuts is ignored
  //otherwise WhichCuts==0 -> 6th jet pt = 60, no Sphericity cut
  //otherwise WhichCuts==1 -> 6th jet pt = 110, Sphericity > 0.4
  string Sph="";
  int pT6V=110;
  Sph="_Sph4";
  if (flavor=="112"){
    Sph="_Sph4";
    pT6V=110;
  }
  
  if (flavor=="113_223"){
    if (WhichCuts==0){
      // Sph="";
      pT6V=60;	
    }
    if (WhichCuts==1){
      Sph="_Sph4";
      pT6V=110;	
    }
    
  }
  
  filelist.push_back(TFile::Open(("Acc_RPV"+flavor+Sph+".root").c_str()));	
  filelist.push_back(TFile::Open(("Acc_RPV" + flavor + Sys + "up" + Sph + ".root").c_str()));	
  filelist.push_back(TFile::Open(("Acc_RPV" + flavor + Sys + "down" + Sph + ".root").c_str()));	
  
  
  TGraphErrors* g_Acc_norm = (TGraphErrors*) filelist[0]->Get(("GausAcceptance_vs_Mass_"+flavor+"_"+to_string(pT6V)).c_str())->Clone();
  TGraphErrors* g_Acc_up = (TGraphErrors*) filelist[1]->Get(("GausAcceptance_vs_Mass_"+flavor+"_"+to_string(pT6V)).c_str())->Clone();
  TGraphErrors* g_Acc_down = (TGraphErrors*) filelist[2]->Get(("GausAcceptance_vs_Mass_"+flavor+"_"+to_string(pT6V)).c_str())->Clone();
  
  
  TF1* f_Acc_norm = (TF1*)g_Acc_norm->GetFunction("total")->Clone();
  TF1* f_Acc_up = (TF1*)g_Acc_up->GetFunction("total")->Clone();
  TF1* f_Acc_down = (TF1*)g_Acc_down->GetFunction("total")->Clone();
  
  vector <float > masses;
  float OriginalMasses[11]={200,250,300,350,400,450,500,750,1000,1250,1500};
  if(flavor=="113_223"){
    if (WhichCuts==0){
      for (int iMass=0 ; iMass < 7; iMass++){
	masses.push_back(OriginalMasses[iMass]);	
      }
    }
    if (WhichCuts==1){
      for (int iMass=7 ; iMass < 11; iMass++){
	masses.push_back(OriginalMasses[iMass]);	
      }
    }
  }
  
  if(flavor=="112"){
    
    for (int iMass=4 ; iMass < 11; iMass++){
      masses.push_back(OriginalMasses[iMass]);	
    }
  }
  cout<<"Doing Systematic "+Sys+" for model RPV"+flavor+" with pt6="+to_string(pT6V);
  if (flavor=="113_223" && pT6V == 110)
  	cout << " and Sph="+Sph;
  cout <<endl;
  for( unsigned int i=0; i<masses.size(); i++){
    float norm=f_Acc_norm->Eval(masses[i]);
    float up= f_Acc_up->Eval(masses[i]);
    float down = f_Acc_down->Eval(masses[i]);
    cout<<setiosflags(ios::fixed) << setprecision(0)<<masses[i]<<" "<<setiosflags(ios::fixed) << setprecision(4)<<up<<" "<<norm<<" "<<down<<
      " "<<" % up: "<<(norm-up)/norm<<" % down: "<<(down-norm)/norm<<
      " MAX: "<<setiosflags(ios::fixed) << setprecision(0)<<max(fabs((norm-up)/norm),fabs((down-norm)/norm))*100<<" %"<<endl;
  }

}

 



