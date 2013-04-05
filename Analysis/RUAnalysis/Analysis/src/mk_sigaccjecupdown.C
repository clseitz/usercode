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

void mk_sigaccjecupdown(string flavor = "112",  const string uncert = "jec")
{
	// gStyle->SetOptFit(1100); // chi2 and prob, not parameters
	// gStyle->SetOptFit(1); // chi2 and prob, not parameters
	// gStyle->SetOptStat("irme"); // integral, RMS, mean, # of entries
	// gStyle->SetStatFontSize(0.005);
	// gStyle->SetStatY(0.4);
	TLatex *   tex = new TLatex(0.678392,0.9283217,"CMS Preliminary 9.95 fb^{-1} at #sqrt{s}  =  8 TeV");
	tex->SetNDC();
	tex->SetTextAlign(22);
	tex->SetTextFont(42);
	// tex->SetTextSize(0.03846154);
	tex->SetLineWidth(2);
  cout<<"blabl"<<endl; 	
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

  // string uncert="btagup";
  // if(k==1) uncert="btagdown";
  // if(k==1) uncert="down";
  // if(k==2) uncert="";
  
  namelist.push_back("KinematicOptimization");
  // filelist_kin.push_back(TFile::Open(("Acc_Gluino_NoLumi_pt110_8TeVxsec_BtagMap_2500GeV"+uncert+".root").c_str()));
  // filelist_kin.push_back(TFile::Open("Acc_Gluino_NoLumi_pt60_pt110_8TeVxsec_BtagMap.root"));
  // filelist_kin.push_back(TFile::Open(("Acc_RPV112" + uncert + ".root").c_str()));
  filelist_kin.push_back(TFile::Open(("Acc_RPV" + flavor + "_Sph4.root").c_str()));
  filelist_kin.push_back(TFile::Open(("Acc_RPV" + flavor + uncert +  "up_Sph4.root").c_str()));
  filelist_kin.push_back(TFile::Open(("Acc_RPV" + flavor + uncert +  "down_Sph4.root").c_str()));
//   filelist_kin.push_back(TFile::Open(("Acc_Gluino_NoLumi_pt60_pt110_8TeVxsec_BtagMap" + uncert + ".root").c_str()));
  
  TFile f1(("RPV_" + flavor + "_accandwdith"+uncert+".root").c_str(), "recreate");
  f1.cd();
  
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
  
  for (int p = 0; p < 2; p++) {
    // ptcut="112";
    // if(p==1) ptcut="" + flavor;
     ptcut="60";
    if(p==1) ptcut="110";
     ///////////////////////////////////////////////////////////////////
      ///////////Plot nice Mjjj plots
      //////////////////////////////////////////////////////////////////
      // string histname = string("GausWidth_vs_Mass_112") + ptcut;
      string histname = string("GausWidth_vs_Mass_" + flavor) + "_" + ptcut;
      cout<< histname << endl;
      TGraphErrors *h_gauswidth = (TGraphErrors*) filelist_kin[0]->Get(histname.c_str())->Clone();
			TGraphErrors *h_gauswidthup = (TGraphErrors*) filelist_kin[1]->Get(histname.c_str())->Clone();
			TGraphErrors *h_gauswidthdown = (TGraphErrors*) filelist_kin[2]->Get(histname.c_str())->Clone();
			histname = string("GausAcceptance_vs_Mass_" + flavor) + "_" + ptcut;
      // histname = string("GausAcceptance_vs_Mass_112") + ptcut;
      cout<< histname << endl;
      TGraphErrors *h_gausacc = (TGraphErrors*) filelist_kin[0]->Get(histname.c_str())->Clone();
      TGraphErrors *h_gausaccup = (TGraphErrors*) filelist_kin[1]->Get(histname.c_str())->Clone();
      TGraphErrors *h_gausaccdown = (TGraphErrors*) filelist_kin[2]->Get(histname.c_str())->Clone();
         
      TCanvas * cGluinoFitsOpti = new TCanvas(("RPV_"+ptcut+"_"+cuts).c_str(), ("RPV_" + ptcut+"_"+cuts).c_str(), 800, 600);
      //h_gauswidth->SetFillColor(kOrange-2);
      // h_gauswidth->SetLineColor(kBlack);
		string title;
		string systematic = "pile-up";
		// title="Gaussian Width vs. Mass for Light-ptcut RPV";
		string tag = "Heavy", sphericity = " Sphericity Cut";
		if (flavor.compare("112") == 0)
			tag = "Light";
		else if (ptcut == "60")
			sphericity = "";
		string titlepart = tag + "-flavor RPV " + flavor + " p_{T} = " + ptcut + sphericity;
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
			TLegend *leg;
			leg = new TLegend(0.6,0.2,0.8994975,0.5,NULL,"brNDC");
			float linesiz = 2.0;
      h_gauswidthup->SetLineColor(kBlue);
			h_gauswidthup->SetLineWidth(linesiz);
			h_gauswidthup->SetMarkerColor(kBlue);
      TF1 *fitfunc = h_gauswidthup->GetFunction("GausWidth");
			if (fitfunc != NULL)
				fitfunc->SetLineColor(kBlue);
			leg->AddEntry(h_gauswidthup,"JES up", "L");
      h_gauswidthup->GetYaxis()->SetTitle("Width [GeV]");
      h_gauswidthup->GetYaxis()->SetTitleOffset(1.3);
      h_gauswidthup->GetXaxis()->SetTitle("RPV Mass [GeV]");
      h_gauswidthup->SetTitle(title.c_str());
      h_gauswidthup->Draw("A*");	
      fitfunc = h_gauswidth->GetFunction("GausWidth");
			if (fitfunc != NULL)
				fitfunc->SetLineColor(kBlack);
			else cout << "Bad func name\n";
			h_gauswidth->SetLineColor(kBlack);
			h_gauswidth->SetMarkerColor(kBlack);
			h_gauswidth->SetLineWidth(linesiz);
      // h_gauswidth->SetTitleSize(0.01);
      // h_gauswidth->Draw("AL");	
			leg->AddEntry(h_gauswidth,"Nominal JES", "L");
      h_gauswidth->Draw("same*");	
			h_gauswidthdown->SetLineWidth(linesiz);
			h_gauswidthdown->SetMarkerColor(kRed);
      h_gauswidthdown->SetLineColor(kRed);
      fitfunc = h_gauswidthdown->GetFunction("GausWidth");
			if (fitfunc != NULL)
				fitfunc->SetLineColor(kRed);
			leg->AddEntry(h_gauswidthdown,"JES down", "L");
      h_gauswidthdown->Draw("same*");	
			leg->Draw();
      cGluinoFitsOpti->Write();
      cGluinoFitsOpti->SaveAs((folder + "RPVwidthjesupdn" +flavor + ptcut+uncert+postfix).c_str());
      TCanvas * cGluinoFitsOpt2 = new TCanvas(("RPVacc_"+ptcut+"_"+cuts).c_str(), ("RPV_" + ptcut+"_"+cuts).c_str(), 800, 600);
			leg = new TLegend(0.6,0.2,0.8994975,0.5,NULL,"brNDC");
			title="Acceptance for " + titlepart;
      h_gausacc->SetTitle(title.c_str());
      h_gausacc->GetYaxis()->SetTitle("Acceptance");
      h_gausacc->GetYaxis()->SetTitleOffset(1.4);
      h_gausacc->GetXaxis()->SetTitle("RPV Mass [GeV]");
      // if (flavor.compare("113_223") == 0 && ptcut == "110") {
      	// gStyle->SetStatY(0.8);
				// h_gausacc->GetYaxis()->SetRangeUser(0.0, 0.035);
			//}

      fitfunc = h_gausacc->GetFunction("total");
			if (fitfunc != NULL)
				fitfunc->SetLineColor(kBlack);
			else cout << "Bad func name\n";
			h_gausacc->SetLineColor(kBlack);
			h_gausacc->SetMarkerColor(kBlack);
			h_gausacc->SetLineWidth(linesiz);
			leg->AddEntry(h_gausacc,"Nominal JES", "L");
      // h_gausacc->Draw("AL");	
      h_gausacc->Draw("A*");
      fitfunc = h_gausaccup->GetFunction("total");
			if (fitfunc != NULL)
				fitfunc->SetLineColor(kBlue);
			else cout << "Bad func name\n";
			h_gausaccup->SetLineColor(kBlue);
			h_gausaccup->SetMarkerColor(kBlue);
			h_gausaccup->SetLineWidth(linesiz);
			leg->AddEntry(h_gausaccup,"JES up", "L");
      h_gausaccup->Draw("same*");
      fitfunc = h_gausaccdown->GetFunction("total");
			if (fitfunc != NULL)
				fitfunc->SetLineColor(kRed);
			else cout << "Bad func name\n";
			h_gausaccdown->SetLineColor(kRed);
			h_gausaccdown->SetMarkerColor(kRed);
			h_gausaccdown->SetLineWidth(linesiz);
			leg->AddEntry(h_gausaccdown,"JES down", "L");
      h_gausaccdown->Draw("same*");
			leg->Draw();
      
      cGluinoFitsOpt2->Write();
      cGluinoFitsOpt2->SaveAs((folder + "RPVaccjesupdn" +flavor + ptcut+uncert+postfix).c_str());
      f1.cd();

		
		
		
		/////////////////Make some DataPlots///////////////////////
    }
  	
  }
	
	
}
