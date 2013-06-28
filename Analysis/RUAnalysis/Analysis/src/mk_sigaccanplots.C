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
	TLatex *tex = new TLatex(0.9,0.97,"CMS Simulation Preliminary");
	tex->SetNDC();
	tex->SetTextAlign(12); // Left-adjusted
	tex->SetTextFont(42);
	float textsiz = 0.04;
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
  folder="plots_band/";
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
     
      histname = string("GausMeanOffset_vs_Mass_" + flavor) + "_" + ptcut;
      cout<< histname << endl;
      TGraph *h_MeanOffset = (TGraph*) filelist_kin[0]->Get(histname.c_str())->Clone();
     
      TCanvas * cGluinoFitsOpti = new TCanvas(("RPV_"+flavor +ptcut).c_str(), ("RPV_" + ptcut+"_"+cuts).c_str(), 800, 600);
      //h_GluinoHist_Fit->SetFillColor(kOrange-2);
      // h_GluinoHist_Fit->SetLineColor(kBlack);
		string title;
		string systematic = "pile-up";
		// title="Gaussian Width vs. Mass for Light-ptcut RPV";
		string tag = "Heavy", sphericity = " Sphericity > 0.4";
		if (flavor.compare("112") == 0)
			tag = "Light";
		else if (ptcut.compare("60") == 0)
			sphericity = "";
		string titlepart = tag + "-flavor RPV Gluino";
		string titleln2 = "\\Delta = 110 GeV, 6^{th}-Jet p_{T} > " + ptcut + " GeV";
		title = titlepart;
		// title = "Width for " + titlepart;
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
      float titpos = 0.2, headpos = 0.64;
			TLatex *tex2 = new TLatex(titpos, 0.89, title.c_str());
			tex2->SetNDC();
			tex2->SetTextAlign(12); // Left-adjusted
			tex2->SetTextFont(42);
			tex2->SetTextSize(textsiz);
			tex2->SetLineWidth(2);
			TLatex *tex3 = new TLatex(titpos, 0.84, titleln2.c_str());
			tex3->SetNDC();
			tex3->SetTextAlign(12);
			tex3->SetTextFont(42);
			tex3->SetTextSize(textsiz);
			tex3->SetLineWidth(2);
			TLatex *tex4 = NULL;
			if (sphericity.size() > 0) {
				tex4 = new TLatex(titpos - 0.01, 0.79, sphericity.c_str());
				tex4->SetNDC();
				tex4->SetTextAlign(12);
				tex4->SetTextFont(42);
				tex4->SetTextSize(textsiz);
				tex4->SetLineWidth(2);
			}
			TLegend *leg = new TLegend(0.65, 0.2, 0.95, 0.4);
			leg->SetBorderSize(1);
			leg->SetTextFont(62);
			leg->SetLineColor(kBlack);
			leg->SetLineStyle(1);
			leg->SetLineWidth(1);
			leg->SetFillColor(0);
			leg->SetFillStyle(1001);
			//leg->SetHeader();


			// leg->AddEntry(h_GluinoHist_Fit, "#splitline{Acceptance as function}{of gluino mass}","l");	
      h_GluinoHist_Fit->SetMarkerStyle(1);
      h_GluinoHist_Fit->SetMarkerColor(kWhite);
      // h_GluinoHist_Fit->SetMarkerColor(kGreen + 3);
      h_GluinoHist_Fit->SetMarkerSize(0.004);
     // h_GluinoHist_Fit->SetTitleSize(0.01);
      TF1 *fitfunc = h_GluinoHist_Fit->GetFunction("GausWidth");
      string fitnamew = "fitcopy" + ptcut;
      TF1* fitfunccopy = (TF1 *) fitfunc->Clone(fitnamew.c_str());
      if (fitfunc == NULL)
     	 cout << "Can't get fit func\n";
      else {
      	fitfunc->Delete();
      	fitfunccopy->SetLineWidth(3);
      	fitfunccopy->SetLineColor(kGreen + 3);
		// fitfunc->SetLineStyle(3); // Dotted
      }
	float labsiz = 0.045;
      h_GluinoHist_Fit->GetYaxis()->SetTitle("Gaussian Width [GeV]");
      h_GluinoHist_Fit->GetYaxis()->SetTitleOffset(1.2);
      h_GluinoHist_Fit->GetXaxis()->SetTitle("Gluino Mass [GeV]");
      h_GluinoHist_Fit->GetXaxis()->SetTitleSize(labsiz);
      h_GluinoHist_Fit->GetYaxis()->SetTitleSize(labsiz);
       h_GluinoHist_Fit->Draw("APX");	// X eliminates error bars
       // h_GluinoHist_Fit->Draw("AP");	
      // TH1 *fithist = (TH1 *) fitfunccopy->GetHistogram()->Clone(fitnamew.c_str());
      TH1 *fithist = (TH1 *) fitfunccopy->GetHistogram()->Clone();
      int fillcolor = kGreen + 2;
      int fillstyle = 3013;
      if (fithist != NULL) {
      	int numBins = fithist->GetNbinsX();
      	for (int cnt = 1; cnt <= numBins; ++cnt) {
      		double mass = fithist->GetBinCenter(cnt);
      		double width =  fithist->GetBinContent(cnt);
      		double wuncert = 0.1281;
      		if (mass < 700)
      			wuncert = 0.1562;
      		else if (mass < 950)
      			wuncert = 0.1414;
      		else if (mass < 1000)
      			wuncert = 0.1345;
      		double err = width * wuncert;
      		fithist->SetBinError(cnt, err);
      	}
      	fithist->SetFillColor(fillcolor);
      	fithist->SetFillStyle(fillstyle);
      	fithist->Draw("CE3SAME");
      }
      fitfunccopy->Draw("CSAME");
      // h_GluinoHist_Fit->Draw("P");	// Draw points over fit line
      leg->AddEntry(fitfunccopy, "Gaussian Width", "L");
      leg->AddEntry(fithist, "Uncertainty", "F");
	 leg->Draw();
      tex->SetX(headpos);
      tex->Draw();
      tex2->Draw();
      tex3->Draw();
      if (tex4 != NULL)
		tex4->Draw();
      cGluinoFitsOpti->Write();
      cGluinoFitsOpti->SaveAs((folder + "RPVwidth" +flavor + ptcut+uncert+postfix).c_str());

      TCanvas * cGluinoFitsOpt2 = new TCanvas(("RPVacc_"+flavor +ptcut).c_str(), ("RPV_" + ptcut+"_"+cuts).c_str(), 800, 600);
	 // title="Acc. x Eff. for " + titlepart;
	 title= titlepart;
	 tex2->SetText(titpos, 0.89, title.c_str());
	 TLegend *leg2 = new TLegend(0.65, 0.2, 0.95, 0.4);
	 leg2->SetBorderSize(1);
	 leg2->SetTextFont(62);
	 leg2->SetTextSize(0.04);
	 leg2->SetLineColor(kBlack);
	 leg2->SetLineStyle(1);
	 leg2->SetLineWidth(1);
	 leg2->SetFillColor(0);
	 leg2->SetFillStyle(1001);

      TF1 *fitfuncA = h_GluinoHist_MCcomb->GetFunction("total");
      string fitname = "fitcopyA" + ptcut;
      TF1* fitfunccopyA = (TF1 *) fitfuncA->Clone(fitname.c_str());
      if (fitfuncA == NULL)
     	 cout << "Can't get fit func\n";
      else {
      	fitfuncA->Delete();
      	fitfunccopyA->SetLineWidth(3);
      	fitfunccopyA->SetLineColor(kGreen + 3);
		// fitfunc->SetLineStyle(3); // Dotted
      }
      h_GluinoHist_MCcomb->SetMarkerStyle(1);
      // h_GluinoHist_MCcomb->SetMarkerColor(kBlack);
      h_GluinoHist_MCcomb->SetMarkerColor(kWhite);
      h_GluinoHist_MCcomb->SetTitle(title.c_str());
      h_GluinoHist_MCcomb->GetYaxis()->SetTitle("Acceptance x Efficiency");
      h_GluinoHist_MCcomb->GetYaxis()->SetTitleOffset(1.4);
      h_GluinoHist_MCcomb->GetXaxis()->SetTitle("Gluino Mass [GeV]");
      h_GluinoHist_MCcomb->GetXaxis()->SetTitleSize(labsiz);
      h_GluinoHist_MCcomb->GetYaxis()->SetTitleSize(labsiz);
      if (false && flavor.compare("113_223") == 0 && ptcut == "110") {
      	gStyle->SetStatY(0.8);
				h_GluinoHist_MCcomb->GetYaxis()->SetRangeUser(0.0, 0.035);
			}

      // h_GluinoHist_MCcomb->Draw("AL");	
      h_GluinoHist_MCcomb->Draw("APX");
      // fitfunccopyA->Draw("C same");
      // TH1 *fithistA = (TH1 *) fitfunccopyA->GetHistogram()->Clone(fitname.c_str());
      TH1 *fithistA = (TH1 *) fitfunccopyA->GetHistogram()->Clone();
      if (fithistA != NULL) {
      	int numBins = fithistA->GetNbinsX();
      	for (int cnt = 1; cnt <= numBins; ++cnt) {
      		double mass = fithistA->GetBinCenter(cnt);
      		double accpt =  fithistA->GetBinContent(cnt);
      		double wuncert = 0.0917;
      		if (mass < 400)
      			wuncert = 0.1261;
      		else if (mass < 450)
      			wuncert = 0.1208;
      		else if (mass < 500)
      			wuncert = 0.1269;
      		else if (mass < 525)
      			wuncert = 0.1192;
      		else if (mass < 600)
      			wuncert = 0.1145;
      		else if (mass < 650)
      			wuncert = 0.1114;
      		else if (mass < 700)
      			wuncert = 0.1034;
       		else if (mass < 750)
      			wuncert = 0.0933;
      		else if (mass < 950)
      			wuncert = 0.086;
      		else if (mass < 1350)
      			wuncert = 0.0889;
      		else if (mass < 1400)
      			wuncert = 0.086;
      		else if (mass < 1450)
      			wuncert = 0.0933;
     		double err = accpt * wuncert;
      		fithistA->SetBinError(cnt, err);
      	}
      	fithistA->SetFillColor(fillcolor);
      	fithistA->SetFillStyle(fillstyle);
      	fithistA->Draw("CE3SAME");
      }
      fitfunccopyA->Draw("CSAME");
      // h_GluinoHist_MCcomb->Draw("P");	// Draw points over fit line
      tex->SetX(headpos);
      tex->Draw();
      tex2->Draw();
      tex3->Draw();
      leg2->AddEntry(fitfunccopyA, "Acc. x Eff.", "L");
      leg2->AddEntry(fithistA, "Uncertainty", "F");
	 leg2->Draw();
       if (tex4 != NULL)
		tex4->Draw();
 
      cGluinoFitsOpt2->Write();
      cGluinoFitsOpt2->SaveAs((folder + "RPVacc" +flavor + ptcut+uncert+postfix).c_str());

      gStyle->SetStatY(0.4);
      TCanvas * cGluinoFitsOpt3 = new TCanvas(("RPVfullacc_"+flavor +ptcut).c_str(), ("RPVfull_" + ptcut+"_"+cuts).c_str(), 800, 600);
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
      h_FullAccept->GetXaxis()->SetTitleSize(labsiz);
      h_FullAccept->GetYaxis()->SetTitleSize(labsiz);
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
      tex->SetX(titpos);
      tex->Draw();
      tex2->Draw();
      tex3->Draw();
      if (tex4 != NULL)
		tex4->Draw();
      f1.cd();
      cGluinoFitsOpt3->Write();
      cGluinoFitsOpt3->SaveAs((folder + "RPVmean" +flavor + ptcut+uncert+postfix).c_str());

      gStyle->SetStatY(0.4);
      TCanvas *cMeanOffset = new TCanvas(("RPVMeanOffset_"+flavor +ptcut).c_str(),
      	("RPVMeanOffset_" + ptcut + "_" + cuts).c_str(), 800, 600);
      axsize = 0.035;
			title="Mass Deviation for " + titlepart;
			titpos = 0.35;
			tex2->SetText(titpos, 0.89, title.c_str());
      h_MeanOffset->SetMarkerStyle(1);
      h_MeanOffset->SetLineColor(kRed);
      h_MeanOffset->SetLineWidth(2.0);
      h_MeanOffset->GetYaxis()->SetTitleOffset(1.3);
      h_MeanOffset->GetYaxis()->SetTitle("Fractional Mass Deviation");
      h_MeanOffset->GetXaxis()->SetTitleOffset(1.3);
      h_MeanOffset->GetXaxis()->SetTitle("Gluino Mass [GeV]");
      h_MeanOffset->GetXaxis()->SetTitleSize(labsiz);
      h_MeanOffset->GetYaxis()->SetTitleSize(labsiz);
      h_MeanOffset->GetXaxis()->SetLabelSize(axsize);
      h_MeanOffset->GetYaxis()->SetLabelSize(axsize);
      TLine *max = new TLine(0.5, 0.1, 0.5, 0.9);
			max->SetLineColor(kGreen + 2);
			max->SetLineWidth(3);
      h_MeanOffset->Draw("AL");	
			max->DrawLineNDC(0.16, 0.49, 0.98, 0.49);
      tex->SetX(titpos);
      tex->Draw();
      tex2->Draw();
      tex3->SetX(titpos);
      tex3->Draw();
      if (tex4 != NULL) {
      	tex4->SetX(titpos);
		tex4->Draw();
	 }
      f1.cd();
      cMeanOffset->Write();
      cMeanOffset->SaveAs((folder + "RPVmassdev" +flavor + ptcut+uncert+postfix).c_str());
      }
  	
  }
	
	
}





