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


#include <sstream>

template <class T>
inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

void make_ANplots()
{
	
	//Which plots to make
	int WhichPlot=0; //0 = normal all backgrounds+error bars and data, 1= include W' on top of the background for W' mass
	int bkgC=5;//38;
	//define input variables
	vector <string > namelist;
	vector <string > VarList;
	vector <TFile* > data;
	vector <TFile* > filelist;
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
	char dir[99];
	char AxisLabel[99];
	char dirout[99];
	float upRange=1100;
	float lumi=2420;
	float TriggerS = 1;
	int nRebin=10;
	

	
	filelist.push_back(TFile::Open("../MakeKinematicOpt/DATA_RPV_112_4th80_KinematicOptimization_geq0b.root"));
	namelist.push_back("KinematicOptimization");
	
	namelist.push_back("BtaggingOptimization");
	filelist.push_back(TFile::Open("../MakeBtagOpt/DATA_RPV_Btags_6th60_Diag110_CSVL_1GeVBin_test.root"));
	filelist.push_back(TFile::Open("../MakeBtagOpt/DATA_RPV_Btags_6th60_Diag110_CSVM_1GeVBin_test.root"));
	filelist.push_back(TFile::Open("../MakeBtagOpt/DATA_RPV_Btags_6th60_Diag110_CSVT_1GeVBin_test.root"));
	
	TFile f1("AN_Plots.root", "recreate");
	f1.cd();
	f1.mkdir(namelist[0].c_str());
	f1.mkdir(namelist[1].c_str());

	
	int masses[11] = {250,300,350,400,450,500,750,1000,1250,1500};
	string flavor="112";
	
	string nameIN;
	string cuts;
	string prefix;
	string postfix;
	string folder;
	folder="plots/";
	postfix=".png";
	/////////////Plots for each Mass separatly//////////////
	/////////////----------------------------------------/////////////
	prefix="SignalOverSigPlusBkg_RPV_M";
	for(int i=0; i<10; i++){
		nameIN=prefix+to_string(masses[i])+"_"+flavor;
		cout<<(nameIN).c_str()<<endl;
		TH2F* h_SignalOverSqrtSigPlusBkg = (TH2F*) filelist[0]->Get((nameIN).c_str())->Clone();
		TCanvas * cSignalOverSqrtSigPlusBkg = new TCanvas((nameIN).c_str(), (nameIN).c_str(), 800, 600);
		
		h_SignalOverSqrtSigPlusBkg->Draw("colztext");
		h_SignalOverSqrtSigPlusBkg->SetMarkerSize(1.6);
		h_SignalOverSqrtSigPlusBkg->SetMinimum(0);
		h_SignalOverSqrtSigPlusBkg->SetTitle(("N_{Sig} / #sqrt{N_{Sig}+N_{Bkg}}   for RPV gluino m="+to_string(masses[i])+" Gev").c_str());
		h_SignalOverSqrtSigPlusBkg->GetYaxis()->SetRangeUser(70,180);
		h_SignalOverSqrtSigPlusBkg->GetYaxis()->SetTitle("Diagonal Cut [GeV]");
		h_SignalOverSqrtSigPlusBkg->GetYaxis()->SetTitleOffset(1.3);
		
		h_SignalOverSqrtSigPlusBkg->GetXaxis()->SetRangeUser(40,90);
		h_SignalOverSqrtSigPlusBkg->GetXaxis()->SetTitle("6^{th} Jet p_{T} [GeV]");
		h_SignalOverSqrtSigPlusBkg->GetXaxis()->SetTitleOffset(1.2);
		
		cSignalOverSqrtSigPlusBkg->SetGrid();
		cSignalOverSqrtSigPlusBkg->SetMargin(0.1,0.16,0.1,0.12);
		cSignalOverSqrtSigPlusBkg->SaveAs((folder+nameIN+postfix).c_str());
		f1.cd(namelist[0].c_str());
		cSignalOverSqrtSigPlusBkg->Write();
		///////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////
		nameIN="RPV_M"+to_string(masses[i])+"_"+flavor+"/0bFits/";
		cuts="bjet0_pt60_diag110_GE6jet";
		cout<<(nameIN+"P4Gaus_Mjjj_"+cuts).c_str()<<endl;
		TH2F* h_GluinoHist_Fit = (TH2F*) filelist[0]->Get((nameIN+"P4Gaus_Mjjj_"+cuts).c_str())->Clone();
		cout<<((nameIN+"Mjjj_"+cuts+"MCcomb").c_str())<<endl;
		TH2F* h_GluinoHist_MCcomb = (TH2F*) filelist[0]->Get((nameIN+"Mjjj_"+cuts+"_MCcomb").c_str())->Clone();
		cout<<((nameIN+"P4_Mjjj_"+cuts).c_str())<<endl;
		TF1* f_GluinoP4 = (TF1*) filelist[0]->Get((nameIN+"P4_Mjjj_"+cuts).c_str())->Clone();
		cout<<((nameIN+"GaussP4_Mjjj_"+cuts).c_str())<<endl;
		TF1* f_GluinoGauss = (TF1*) filelist[0]->Get((nameIN+"GaussP4_Mjjj_"+cuts).c_str())->Clone();
		
		TCanvas * cGluinoFitsOpti = new TCanvas(("RPV_M"+to_string(masses[i])+cuts).c_str(), ("RPV_M"+to_string(masses[i])+cuts).c_str(), 800, 600);
		h_GluinoHist_Fit->SetFillColor(kOrange-2);
		h_GluinoHist_Fit->SetLineColor(kBlack);	
		h_GluinoHist_Fit->Draw("histe");	

		h_GluinoHist_MCcomb->SetFillColor(10);
			h_GluinoHist_MCcomb->SetLineColor(kBlack);
		h_GluinoHist_MCcomb->Draw("samehist");
		f_GluinoGauss->Draw("same");
		f_GluinoP4->Draw("same");
		
		f1.cd(namelist[0].c_str());
		cGluinoFitsOpti->Write();
		
	
	}
	
	
	
	///////Plots for normalized signal significance for different masses///////
	///////-------------------------------------------------------------//////
	prefix="GluinoMass_vs_6thpT";
	nameIN=prefix+"_"+flavor+"_normalized";
	TH2F* h_GluniMass_vs_6thpT= (TH2F*) filelist[0]->Get((nameIN).c_str())->Clone();
	TCanvas * cGluniMass_vs_6thpT = new TCanvas((nameIN).c_str(), (nameIN).c_str(), 800, 600);	
		
	h_GluniMass_vs_6thpT->Draw("colztext");
	
	h_GluniMass_vs_6thpT->SetMarkerSize(1.6);
	h_GluniMass_vs_6thpT->SetMinimum(0);
	h_GluniMass_vs_6thpT->SetTitle("Normalized Signal Significance, #Delta = 110 GeV");
	h_GluniMass_vs_6thpT->GetYaxis()->SetRangeUser(0,9);
	h_GluniMass_vs_6thpT->GetYaxis()->SetTitle("Gluino Mass [GeV]");
	h_GluniMass_vs_6thpT->GetYaxis()->SetTitleOffset(1.5);
	h_GluniMass_vs_6thpT->GetYaxis()->SetLabelSize(0.05);
	h_GluniMass_vs_6thpT->GetXaxis()->SetRangeUser(40,90);
	h_GluniMass_vs_6thpT->GetXaxis()->SetTitle("6^{th} Jet p_{T} [GeV]");
	h_GluniMass_vs_6thpT->GetXaxis()->SetTitleOffset(1.2);
	
	cGluniMass_vs_6thpT->SetGrid();
	cGluniMass_vs_6thpT->SetMargin(0.13,0.16,0.1,0.12);
	cGluniMass_vs_6thpT->SaveAs((folder+nameIN+postfix).c_str());
	f1.cd(namelist[0].c_str());
	cGluniMass_vs_6thpT->Write();
	//////////////////////////////////////////////////////////////////////////
	
	//////////Plots for gluino b-tagging optimization///////////////////////
	//////////---------------------------------------//////////////////////
	prefix="GluinoMass_vs_nBtags";
	flavor="113_223";
	nameIN=prefix+"_"+flavor+"_normalized";
	cout<<((nameIN).c_str())<<endl;
	TH2F* h_GluniMass_vs_Btag_CSVL_norm= (TH2F*) filelist[1]->Get((nameIN).c_str())->Clone();
	TH2F* h_GluniMass_vs_Btag_CSVM_norm= (TH2F*) filelist[2]->Get((nameIN).c_str())->Clone();
	TH2F* h_GluniMass_vs_Btag_CSVT_norm= (TH2F*) filelist[3]->Get((nameIN).c_str())->Clone();
	
	nameIN=prefix+"_"+flavor;
	TH2F* h_GluniMass_vs_Btag_CSVL= (TH2F*) filelist[1]->Get((nameIN).c_str())->Clone();
	TH2F* h_GluniMass_vs_Btag_CSVM= (TH2F*) filelist[2]->Get((nameIN).c_str())->Clone();
	TH2F* h_GluniMass_vs_Btag_CSVT= (TH2F*) filelist[3]->Get((nameIN).c_str())->Clone();
	TCanvas * cGluniMass_vs_Btag = new TCanvas((nameIN).c_str(), (nameIN).c_str(), 1200, 650);	
	cGluniMass_vs_Btag->Divide(3,2);

	
	cGluniMass_vs_Btag->cd(1);
	h_GluniMass_vs_Btag_CSVL->Draw("text");
	h_GluniMass_vs_Btag_CSVL->SetMinimum(0);
	h_GluniMass_vs_Btag_CSVL->SetMaximum(40);
	h_GluniMass_vs_Btag_CSVL->SetTitle("CSV Light, #Delta = 110 GeV, 6^{th} Jet p_{T} > 60 GeV");
	
	cGluniMass_vs_Btag->cd(2);
	h_GluniMass_vs_Btag_CSVM->Draw("text");
	h_GluniMass_vs_Btag_CSVM->SetMinimum(0);
	h_GluniMass_vs_Btag_CSVM->SetMaximum(40);
	h_GluniMass_vs_Btag_CSVM->SetTitle("CSV Medium, #Delta = 110 GeV, 6^{th} Jet p_{T} > 60 GeV");
																		
	
	cGluniMass_vs_Btag->cd(3);
	h_GluniMass_vs_Btag_CSVT->Draw("text");
	h_GluniMass_vs_Btag_CSVT->SetMinimum(0);
	h_GluniMass_vs_Btag_CSVT->SetMaximum(40);
	h_GluniMass_vs_Btag_CSVT->SetTitle("CSV Tight, #Delta = 110 GeV, 6^{th} Jet p_{T} > 60 GeV");
	
	cGluniMass_vs_Btag->cd(4);
	h_GluniMass_vs_Btag_CSVL_norm->Draw("colztext");
	h_GluniMass_vs_Btag_CSVL_norm->SetMinimum(0.2);
	h_GluniMass_vs_Btag_CSVL_norm->SetMaximum(1.2);
	h_GluniMass_vs_Btag_CSVL_norm->SetTitle("normalized CSV Light");	
	cGluniMass_vs_Btag->cd(5);
	h_GluniMass_vs_Btag_CSVM_norm->Draw("colztext");
	h_GluniMass_vs_Btag_CSVM_norm->SetMinimum(0.2);
	h_GluniMass_vs_Btag_CSVM_norm->SetMaximum(1.2);
	h_GluniMass_vs_Btag_CSVM_norm->SetTitle("normalized CSV Medium");
	
	cGluniMass_vs_Btag->cd(6);
	h_GluniMass_vs_Btag_CSVT_norm->Draw("colztext");
	h_GluniMass_vs_Btag_CSVT_norm->SetMinimum(0.2);
	h_GluniMass_vs_Btag_CSVT_norm->SetMaximum(1.2);
	h_GluniMass_vs_Btag_CSVT_norm->SetTitle("normalized CSV Tight");
	f1.cd(namelist[1].c_str());
	cGluniMass_vs_Btag->Write();
	
}

 



