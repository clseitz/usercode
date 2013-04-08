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
#include "TLine.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TStyle.h"

#include <sstream>

template <class T>
inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

void make_ANplots(const string flavor = "112")
{
	gStyle->SetOptFit(1100); // chi2 and prob, not parameters
	gStyle->SetOptStat("irme"); // integral, RMS, mean, # of entries
	gStyle->SetStatFontSize(0.02);
	gStyle->SetStatY(0.8);
	TLatex *   tex = new TLatex(0.678392,0.9283217,"CMS Preliminary 9.95 fb^{-1} at #sqrt{s}  =  8 TeV");
	tex->SetNDC();
	tex->SetTextAlign(22);
	tex->SetTextFont(42);
	// tex->SetTextSize(0.03846154);
	tex->SetLineWidth(2);
  cout<<"blabl"<<endl; 	
  // for(int k=0; k<3; k++){	
  for(int k=0; k<2; k++){	
  // for(int k=2; k<3; k++){	
  //define input variables
  vector <string > namelist;
  vector <string > VarList;
  vector <TFile* > data;
  vector <TFile* > filelist;
  vector <TFile* > filelist_btag;
	vector <TFile* > filelist_2D;
  vector <TFile* > filelist_kin;
  vector <TFile* > filelist_param;
	  vector <TFile* > filelist_diag;
	vector <TFile* > filelist_stealth;
  vector <TFile* > filelist0b;
  vector <float > EvtGen;
  vector <float > Xsec;
  vector <float > GlunioMass;
  
  vector<float> nEvtTot;
  vector<float> McXsec;
  vector<float> lumis;
  vector<float> DataLumi;
  vector<float> GaussMeanIni;
  vector<float> LeftEdge;
  vector<float> RightEdge;
  vector<vector<float  > > MassBins;
  vector <TH1F* > v_Asym;

  // string uncert="btagup";
  // if(k==1) uncert="btagdown";
  string uncert="jecup";
  if(k==1) uncert="jecdown";
  if(k==2) uncert="";
  
  namelist.push_back("KinematicOptimization");
  // filelist_kin.push_back(TFile::Open(("Acc_Gluino_NoLumi_pt110_8TeVxsec_BtagMap_2500GeV"+uncert+".root").c_str()));
  // filelist_kin.push_back(TFile::Open("Acc_Gluino_NoLumi_pt60_pt110_8TeVxsec_BtagMap.root"));
  filelist_kin.push_back(TFile::Open(("Acc_RPV" + flavor + uncert + "_Sph4.root").c_str()));
//   filelist_kin.push_back(TFile::Open(("Acc_Gluino_NoLumi_pt60_pt110_8TeVxsec_BtagMap" + uncert + ".root").c_str()));
  
  TFile f1(("RPV_" + flavor + "_SignalPlots_"+uncert+".root").c_str(), "recreate");
  f1.cd();

  
  
  
  
  int masses[11] = {200,250,300,350,400,450,500,750,1000,1250,1500};
    //int masses[11] = {350,400,450,500,750,1000,1250};
  
  
  string nameIN;
  string cuts;
  string prefix;
  string postfix;
  string folder;
  string ptcut;
  folder="plots/";
  postfix=".pdf";
  /////////////Plots for each Mass separatly//////////////
  /////////////----------------------------------------/////////////
  
  // for (int p = 0; p < 2; p++) {
  int startInd = 0;
	if (flavor.compare("112") == 0)
		startInd = 1;
  for (int p = startInd; p < 2; p++) {
    ptcut="60";
    if(p==1) ptcut="110";
      ///////////////////////////////////////////////////////////////////
      ///////////Plot nice Mjjj plots
      //////////////////////////////////////////////////////////////////
    int Start=0, End = 6;
    if(p==1) {
    	Start = 7;
    	End = 10;
			if (flavor.compare("112") == 0)
  	    Start = 4;
    }
    for(int i=Start; i <= End; i++){
      cout<<("P4Gaus_RealFit"+to_string(masses[i])+"_"+ptcut).c_str()<<endl;
      TH1F* h_GluinoHist_Fit = (TH1F*) filelist_kin[0]->Get(("P4Gaus_RealFit"+to_string(masses[i])+"_"+ptcut).c_str())->Clone();
      cout<<("P4Pre"+to_string(masses[i])+"_"+ptcut).c_str()<<endl;
      TH1F* h_GluinoHist_MCcomb = (TH1F*) filelist_kin[0]->Get(("P4Pre"+to_string(masses[i])+"_"+ptcut).c_str())->Clone();
      // cout<<(("P4Pre"+to_string(masses[i])+"_"+ptcut).c_str())<<endl;
      // TF1* f_GluinoP4 = (TF1*) filelist_kin[0]->Get(("P4_"+to_string(masses[i])+"_"+ptcut).c_str())->Clone();
      cout<<(("Gaus_P4"+to_string(masses[i])+"_"+ptcut).c_str())<<endl;
      TF1* f_GluinoGauss = (TF1*) filelist_kin[0]->Get(("Gaus_P4"+to_string(masses[i])+"_"+ptcut).c_str())->Clone();
      
      TCanvas * cGluinoFitsOpti = new TCanvas(("RPV_M"+to_string(masses[i])+"_"+ptcut+"_"+cuts).c_str(), ("RPV_M"+to_string(masses[i])+"_"+ptcut+"_"+cuts).c_str(), 800, 600);
      //h_GluinoHist_Fit->SetFillColor(kOrange-2);
      h_GluinoHist_Fit->SetLineColor(kBlack);
		string title;
		// string systematic = "pile-up";
		string tag = "Heavy", sphericity = " Sphericity Cut";
		if (flavor.compare("112") == 0)
			tag = "Light";
		else if (ptcut == "60")
			sphericity = "";
		string uncertTitle = "";
		if (uncert.compare("jecup") == 0)
			uncertTitle = " JES up";
		else if (uncert.compare("jecdown") == 0)
			uncertTitle = " JES down";
		title= tag + "-flavor RPV " + flavor + " " + to_string(masses[i]) +
			" GeV p_{T} = " + ptcut + " " + sphericity + uncertTitle;
		/*
		if(k==0){
		title="RPV gluino #bf{" + systematic + " up} m="+to_string(masses[i])+", ptcut = "+ptcut+", #Delta = 110 GeV, #bf{6^{th} Jet p_{T} = 60 GeV}";
      if (i>=5 || p==0) title="RPV gluino #bf{" + systematic + " up} m="+to_string(masses[i])+", ptcut = "+ptcut+", #Delta = 110 GeV, #bf{6^{th} Jet p_{T} = 110 GeV}";
		}
		
				if(k==1){
		title="RPV gluino #bf{" + systematic + " down} m="+to_string(masses[i])+", ptcut = "+ptcut+", #Delta = 110 GeV, #bf{6^{th} Jet p_{T} = 60 GeV}";
      if (i>=5 || p==0) title="RPV gluino #bf{" + systematic + " down} m="+to_string(masses[i])+", ptcut = "+ptcut+", #Delta = 110 GeV, #bf{6^{th} Jet p_{T} = 110 GeV}";
				}
		
						if(k==2){
		title="RPV gluino m="+to_string(masses[i])+", ptcut = "+ptcut+", #Delta = 110 GeV, #bf{6^{th} Jet p_{T} = 60 GeV}";
      if (i>=5 || p==0) title="RPV gluino m="+to_string(masses[i])+", ptcut = "+ptcut+", #Delta = 110 GeV, #bf{6^{th} Jet p_{T} = 110 GeV}";
						}
						*/
      h_GluinoHist_Fit->SetTitle(title.c_str());
      // h_GluinoHist_Fit->SetTitleSize(0.01);
      h_GluinoHist_Fit->GetYaxis()->SetTitle("Triplets / 10 GeV");
      h_GluinoHist_Fit->GetYaxis()->SetTitleOffset(1.3);
      h_GluinoHist_Fit->GetXaxis()->SetTitle("Triplet Invariant Mass [GeV]");
      h_GluinoHist_Fit->Draw("");	
      
      h_GluinoHist_MCcomb->SetFillColor(10);
      h_GluinoHist_MCcomb->SetLineColor(kBlack);
      //   h_GluinoHist_MCcomb->Draw("samehist");
      f_GluinoGauss->SetLineColor(kRed);
      //f_GluinoGauss->Draw("same");
      
      //f_GluinoP4->Draw("same");
      //tex->Draw();
      f1.cd();

		
		
      cGluinoFitsOpti->Write();
      cGluinoFitsOpti->SaveAs((folder+ "RPV" + flavor + "_M" + to_string(masses[i]) + "_"+ptcut+uncert+postfix).c_str());
		
		/////////////////Make some DataPlots///////////////////////
    }
    }
  	
  }
	
	
}





