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

static const float textsiz = 0.04;

template <class T>
inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}


void mkplot(const string &graphNam, const string &axisLabel, const string &ptcut,
	const string &flavor, const string &outfilenam, const vector <TFile* > &filelist_kin,
	TLatex *const tex)
{
      string histname = graphNam + "_" + flavor + "_" + ptcut;
      cout<< histname << endl;
      TGraph *h_GluinoHist_Fit = (TGraphErrors*) filelist_kin[0]->Get(histname.c_str())->Clone();
     
      string canvasNam = "RPV_"+flavor +ptcut + graphNam;
      TCanvas * cGluinoFitsOpti = new TCanvas(canvasNam.c_str(), canvasNam.c_str(), 800, 600);
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
		string titleln2 = "\\Delta = 110 GeV, 6^{th}-Jet p_{T} > " + ptcut + " GeV";
		title = axisLabel.substr(0, 2) + " for " + titlepart;
      h_GluinoHist_Fit->SetTitle(title.c_str());
      float titpos = 0.2, headpos = 0.64;
      if (graphNam[1] == '3')
      	titpos = 0.5;
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
      h_GluinoHist_Fit->SetMarkerStyle(1);
      h_GluinoHist_Fit->SetMarkerColor(kWhite);
      // h_GluinoHist_Fit->SetMarkerColor(kGreen + 3);
      // h_GluinoHist_Fit->SetMarkerSize(0.04);
     // h_GluinoHist_Fit->SetTitleSize(0.01);
      TF1 *fitfunc = h_GluinoHist_Fit->GetFunction("p3");
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
	string axisTitle = axisLabel + " [GeV]";
      h_GluinoHist_Fit->GetYaxis()->SetTitle(axisTitle.c_str());
      h_GluinoHist_Fit->GetYaxis()->SetTitleOffset(1.2);
      h_GluinoHist_Fit->GetXaxis()->SetTitle("Gluino Mass [GeV]");
      h_GluinoHist_Fit->GetXaxis()->SetTitleSize(labsiz);
      h_GluinoHist_Fit->GetYaxis()->SetTitleSize(labsiz);
       h_GluinoHist_Fit->Draw("APX");	// X eliminates error bars
       // h_GluinoHist_Fit->Draw("AP");	
      // TH1 *fithist = (TH1 *) fitfunccopy->GetHistogram()->Clone(fitnamew.c_str());
      TH1 *fithist = (TH1 *) fitfunccopy->GetHistogram()->Clone();
      fitfunccopy->Draw("CSAME");
      // h_GluinoHist_Fit->Draw("P");	// Draw points over fit line
		// leg->Draw();
      tex->SetX(headpos);
      tex->Draw();
      tex2->Draw();
      tex3->Draw();
      if (tex4 != NULL)
		tex4->Draw();
      cGluinoFitsOpti->Write();
      cGluinoFitsOpti->SaveAs(outfilenam.c_str());

}
      

void sigfiteffplots(string flavor = "112")
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
	tex->SetTextSize(textsiz);
	tex->SetLineWidth(2);
  // for(int k=0; k<3; k++){	
  // for(int k=0; k<2; k++){	
  for(int k=2; k<3; k++){	
		vector <TFile* > filelist_kin;
	
		// string uncert="btagup";
		// if(k==1) uncert="btagdown";
		string uncert="up";
		if(k==1) uncert="down";
		if(k==2) uncert="";
		
		filelist_kin.push_back(TFile::Open(("Acc_RPV" + flavor + uncert + "_Sph4f1f2f3.root").c_str()));
		
		TFile f1(("RPV_" + flavor + "_f1f2f3"+uncert+".root").c_str(), "recreate");
		f1.cd();
			
		string postfix;
		string folder;
		string ptcut;
		folder="plots_effic/";
		postfix=".pdf";
		/////////////Plots for each Mass separatly//////////////
		/////////////----------------------------------------/////////////
		
		for (int p = 0; p < 2; p++) {
			// ptcut="112";
			// if(p==1) ptcut="" + flavor;
			 ptcut="60";
			if(p==1) ptcut="110";
				// string histname = string("GausWidth_vs_Mass_112") + ptcut;
				
			string outfilenam = folder + "RPVeffic" +flavor + ptcut+uncert;
			string finalnam = outfilenam + "f1" +postfix;
			mkplot("f1_vs_Mass", "f1 (Event Selection Efficiency)", ptcut, flavor, finalnam, filelist_kin, tex);
			finalnam = outfilenam + "f2" +postfix;
			mkplot("f2_vs_Mass", "f2 (Number of Triplets per Event)", ptcut, flavor, finalnam, filelist_kin, tex);
			finalnam = outfilenam + "f3" +postfix;
			mkplot("f3_vs_Mass", "f3 (Proportion of Gaussian Triplets)", ptcut, flavor, finalnam, filelist_kin, tex);
		}
		
	}
}





