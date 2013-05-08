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
#include "tdrstyle.C"

#include <sstream>

template <class T>
inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

void mk_sigaccanplots(string flavor = "112")
{
	setTDRStyle();
	// gStyle->SetOptFit(1100); // chi2 and prob, not parameters
	gStyle->SetOptFit(0); // chi2 and prob, not parameters
	// gStyle->SetOptStat("irme"); // integral, RMS, mean, # of entries
	gStyle->SetStatFontSize(0.005);
	gStyle->SetStatY(0.4);
	TLatex *   tex = new TLatex(0.2,0.78,"CMS Simulation Preliminary");
	tex->SetNDC();
	tex->SetTextAlign(12); // Left-adjusted
	tex->SetTextFont(42);
	float textsiz = 0.045;
	tex->SetTextSize(textsiz);
	tex->SetLineWidth(2);
  // for(int k=0; k<3; k++){	
  // for(int k=0; k<2; k++){	
  for(int k=2; k<3; k++){	
  //Which plots to make
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
  string uncert="up";
  if(k==1) uncert="down";
  if(k==2) uncert="";
  
  namelist.push_back("KinematicOptimization");
  // filelist_kin.push_back(TFile::Open(("Acc_Gluino_NoLumi_pt110_8TeVxsec_BtagMap_2500GeV"+uncert+".root").c_str()));
  // filelist_kin.push_back(TFile::Open("Acc_Gluino_NoLumi_pt60_pt110_8TeVxsec_BtagMap.root"));
  // filelist_kin.push_back(TFile::Open(("Acc_RPV112" + uncert + ".root").c_str()));
  filelist_kin.push_back(TFile::Open(("Acc_RPV" + flavor + uncert + "_Sph4.root").c_str()));
//   filelist_kin.push_back(TFile::Open(("Acc_Gluino_NoLumi_pt60_pt110_8TeVxsec_BtagMap" + uncert + ".root").c_str()));
  
  TFile f1(("RPV_" + flavor + "_accandwdithtest"+uncert+".root").c_str(), "recreate");
  f1.cd();
  
  
  
  string nameIN;
  string cuts;
  string prefix;
  string postfix;
  string folder;
  string ptcut;
  folder="plots_test/";
  postfix=".pdf";
  /////////////Plots for each Mass separatly//////////////
  /////////////----------------------------------------/////////////
  
  for (int p = 0; p < 2; p++) {
    // ptcut="112";
    // if(p==1) ptcut="" + flavor;
     ptcut="60";
    if(p==1) ptcut="110";
      // string histname = string("GausWidth_vs_Mass_112") + ptcut;
      string histname = string("GausWidth_vs_Mass_" + flavor) + "_" + ptcut;
      cout<< histname << endl;
      TGraphErrors *h_GluinoHist_Fit = (TGraphErrors*) filelist_kin[0]->Get(histname.c_str())->Clone();
      histname = string("GausAcceptance_vs_Mass_" + flavor) + "_" + ptcut;
      // histname = string("GausAcceptance_vs_Mass_112") + ptcut;
      cout<< histname << endl;
      TGraphErrors *h_GluinoHist_MCcomb = (TGraphErrors*) filelist_kin[0]->Get(histname.c_str())->Clone();
      
      // histname = string("FullAcceptance_vs_Mass_" + flavor) + "_" + ptcut;
      histname = string("GausMean_vs_Mass_" + flavor) + "_" + ptcut;
      // histname = string("GausAcceptance_vs_Mass_112") + ptcut;
      cout<< histname << endl;
      // TGraphErrors *h_FullAccept = (TGraphErrors*) filelist_kin[0]->Get(histname.c_str())->Clone();
      TGraph *h_FullAccept = (TGraph*) filelist_kin[0]->Get(histname.c_str())->Clone();
     
      TCanvas * cGluinoFitsOpti = new TCanvas(("RPV_"+ptcut+"_"+cuts).c_str(), ("RPV_" + ptcut+"_"+cuts).c_str(), 800, 600);
      //h_GluinoHist_Fit->SetFillColor(kOrange-2);
      // h_GluinoHist_Fit->SetLineColor(kBlack);
		string title;
		string systematic = "pile-up";
		// title="Gaussian Width vs. Mass for Light-ptcut RPV";
		string tag = "Heavy", sphericity = " Sphericity > 0.4";
		if (flavor.compare("112") == 0)
			tag = "Light";
		else if (ptcut == "60")
			sphericity = "";
		string titlepart = tag + "-flavor RPV Gluino";
		string titleln2 = "p_{T} > " + ptcut + " GeV " + sphericity;
		title = "Width for " + titlepart;
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
      float titpos = 0.2;
			TLatex *   tex2 = new TLatex(titpos, 0.89, title.c_str());
			tex2->SetNDC();
			tex2->SetTextAlign(12); // Left-adjusted
			tex2->SetTextFont(42);
			tex2->SetTextSize(textsiz);
			tex2->SetLineWidth(2);
			TLatex *   tex3 = new TLatex(titpos, 0.84, titleln2.c_str());
			tex3->SetNDC();
			tex3->SetTextAlign(12);
			tex3->SetTextFont(42);
			tex3->SetTextSize(textsiz);
			tex3->SetLineWidth(2);
			TLegend *leg;
			if (flavor.compare("113_223") == 0 && ptcut == "110")
				leg = new TLegend(0.592392,0.15,0.9518012,0.5,NULL,"brNDC");
			else leg = new TLegend(0.192392,0.6847589,0.48018012,0.83553,NULL,"brNDC");
			leg->SetBorderSize(1);
			leg->SetTextFont(62);
			leg->SetLineColor(0);
			leg->SetLineStyle(1);
			leg->SetLineWidth(1);
			leg->SetFillColor(0);
			leg->SetFillStyle(1001);
			string titlepart2 = "#splitline{#splitline{#Delta = 110 GeV, 6^{th}-jet p_{T} = "
			+ ptcut + " GeV}{";
			// leg->SetHeader("#splitline{#splitline{#Delta = 110 GeV, 6^{th} Jet p_{T} = 110 GeV}{No b-tagging requirement}}{Sphericity > 0.4}");
			if (flavor.compare("112") == 0)
				titlepart2 += "No b-tag requirement";
			else titlepart2 += ">= 1 b tag in triplet";
			titlepart2 += "}}{" + sphericity + "}";
			leg->SetHeader(titlepart2.c_str());


			// leg->AddEntry(h_GluinoHist_Fit, "#splitline{Acceptance as function}{of gluino mass}","l");	
      h_GluinoHist_Fit->SetMarkerStyle(1);
      h_GluinoHist_Fit->SetMarkerColor(kWhite);
      // h_GluinoHist_Fit->SetTitleSize(0.01);
      h_GluinoHist_Fit->GetYaxis()->SetTitle("Width [GeV]");
      h_GluinoHist_Fit->GetYaxis()->SetTitleOffset(1.3);
      h_GluinoHist_Fit->GetXaxis()->SetTitle("Gluino Mass [GeV]");
      // h_GluinoHist_Fit->Draw("AL");	
      // h_GluinoHist_Fit->Draw("A*");	
      h_GluinoHist_Fit->Draw("APX");	
			// leg->Draw();
      tex->Draw();
      tex2->Draw();
      tex3->Draw();
      cGluinoFitsOpti->Write();
      cGluinoFitsOpti->SaveAs((folder + "RPVwidth" +flavor + ptcut+uncert+postfix).c_str());
      TCanvas * cGluinoFitsOpt2 = new TCanvas(("RPVacc_"+ptcut+"_"+cuts).c_str(), ("RPV_" + ptcut+"_"+cuts).c_str(), 800, 600);
			title="Acceptance for " + titlepart;
			tex2->SetText(titpos, 0.89, title.c_str());
      h_GluinoHist_MCcomb->SetMarkerStyle(1);
      h_GluinoHist_MCcomb->SetMarkerColor(kWhite);
      h_GluinoHist_MCcomb->SetTitle(title.c_str());
      h_GluinoHist_MCcomb->GetYaxis()->SetTitle("Acceptance");
      h_GluinoHist_MCcomb->GetYaxis()->SetTitleOffset(1.4);
      h_GluinoHist_MCcomb->GetXaxis()->SetTitle("Gluino Mass [GeV]");
      if (false && flavor.compare("113_223") == 0 && ptcut == "110") {
      	gStyle->SetStatY(0.8);
				h_GluinoHist_MCcomb->GetYaxis()->SetRangeUser(0.0, 0.035);
			}

      // h_GluinoHist_MCcomb->Draw("AL");	
      h_GluinoHist_MCcomb->Draw("APX");
      // h_GluinoHist_MCcomb->Draw("A*");
      tex->Draw();
      tex2->Draw();
      tex3->Draw();
			// leg->Draw();
      
      cGluinoFitsOpt2->Write();
      cGluinoFitsOpt2->SaveAs((folder + "RPVacc" +flavor + ptcut+uncert+postfix).c_str());
      gStyle->SetStatY(0.4);
      TCanvas * cGluinoFitsOpt3 = new TCanvas(("RPVfullacc_"+ptcut+"_"+cuts).c_str(), ("RPVfull_" + ptcut+"_"+cuts).c_str(), 800, 600);
      float axsize = 0.035;
			title="Gaussian Mean for " + titlepart;
			tex2->SetText(titpos, 0.89, title.c_str());
			// title="Full Acceptance for " + titlepart;
      h_FullAccept->SetMarkerStyle(1);
      // h_FullAccept->SetMarkerColor(kWhite);
      h_FullAccept->SetLineColor(kRed);
      h_FullAccept->SetLineWidth(2.0);
      // h_FullAccept->SetTitle(title.c_str());
      // h_FullAccept->GetYaxis()->SetTitle("Acceptance");
      h_FullAccept->GetYaxis()->SetTitle("Gaussian Mean [GeV]");
      h_FullAccept->GetXaxis()->SetTitleOffset(1.3);
      h_FullAccept->GetXaxis()->SetTitle("Gluino Mass [GeV]");
      h_FullAccept->GetXaxis()->SetTitleSize(axsize);
      h_FullAccept->GetYaxis()->SetTitleSize(axsize);
      h_FullAccept->GetXaxis()->SetLabelSize(axsize);
      h_FullAccept->GetYaxis()->SetLabelSize(axsize);
      h_FullAccept->Draw("AL");	
      // h_FullAccept->Draw("APX");	
			// leg->Draw();
      
      // h_GluinoHist_MCcomb->SetFillColor(10);
      // h_GluinoHist_MCcomb->SetLineColor(kBlack);
      //   h_GluinoHist_MCcomb->Draw("samehist");
      // f_GluinoGauss->SetLineColor(kRed);
      //f_GluinoGauss->Draw("same");
      
      //f_GluinoP4->Draw("same");
      tex->Draw();
      tex2->Draw();
      tex3->Draw();
      f1.cd();

		
		
      cGluinoFitsOpt3->Write();
      cGluinoFitsOpt3->SaveAs((folder + "RPVmean" +flavor + ptcut+uncert+postfix).c_str());
		
		/////////////////Make some DataPlots///////////////////////
    }
  	
  }
	
	
}





