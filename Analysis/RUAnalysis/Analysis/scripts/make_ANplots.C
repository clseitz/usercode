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
#include "TGraphErrors.h"


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
  vector <TFile* > filelist_btag;
  vector <TFile* > filelist_kin;
  vector <TFile* > filelist_param;
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
  
  
  namelist.push_back("KinematicOptimization");
  filelist_kin.push_back(TFile::Open("../MakeKinematicOpt/DATA_RPV_112_4th80_KinematicOptimization_geq0b.root"));
  filelist_kin.push_back(TFile::Open("../MakeKinematicOpt/DATA_RPV_113_223_4th80_KinematicOptimization_geq0b.root"));
  
  
  namelist.push_back("BtaggingOptimization");
  filelist_btag.push_back(TFile::Open("../MakeBtagOpt/DATA_RPV_Btags_6th60_Diag110_CSVL_113_223_1GeVBin_TEST.root"));
  filelist_btag.push_back(TFile::Open("../MakeBtagOpt/DATA_RPV_Btags_6th60_Diag110_CSVM_113_223_1GeVBin_TEST.root"));
  filelist_btag.push_back(TFile::Open("../MakeBtagOpt/DATA_RPV_Btags_6th60_Diag110_CSVT_113_223_1GeVBin_TEST.root"));
  filelist_btag.push_back(TFile::Open("../MakeBtagOpt/DATA_RPV_Btags_6th60_Diag110_JPM_113_223_1GeVBin_TEST.root"));
  
  filelist_param.push_back(TFile::Open("../MakeBtagOpt/DATA_RPV_Btags_6th60_Diag110_CSVM_113_223_1GeVBin_TEST.root"));
  filelist_param.push_back(TFile::Open("../MakeBtagOpt/DATA_RPV_Btags_6th60_Diag110_CSVM_112_1GeVBin_TEST.root"));
  
  filelist_stealth.push_back(TFile::Open("../MakeBtagOpt/DATA_Stealth_Btags_6th60_Diag110_CSVM_1GeVBin_TEST.root"));
  
  TFile f1("AN_Plots.root", "recreate");
  f1.cd();
  f1.mkdir(namelist[0].c_str());
  f1.mkdir(namelist[1].c_str());
  
  
  int masses[11] = {250,300,350,400,450,500,750,1000,1250,1500};
  
  
  string nameIN;
  string cuts;
  string prefix;
  string postfix;
  string folder;
  string flavor;
  folder="plots/";
  postfix=".pdf";
  /////////////Plots for each Mass separatly//////////////
  /////////////----------------------------------------/////////////
  
  for (int p=0;p<2;p++){
    flavor="112";
    if(p==1) flavor="113_223";
    prefix="SignalOverSqrtSigPlusBkg_RPV_M";
    for(int i=0; i<10; i++){
      nameIN=prefix+to_string(masses[i])+"_"+flavor;
      cout<<(nameIN).c_str()<<endl;
      TH2F* h_SignalOverSqrtSigPlusBkg = (TH2F*) filelist_kin[p]->Get((nameIN).c_str())->Clone();
      TCanvas * cSignalOverSqrtSigPlusBkg = new TCanvas((nameIN).c_str(), (nameIN).c_str(), 800, 600);
      
      h_SignalOverSqrtSigPlusBkg->Draw("colztext");
      h_SignalOverSqrtSigPlusBkg->SetMarkerSize(1.6);
      h_SignalOverSqrtSigPlusBkg->SetMinimum(0);
      h_SignalOverSqrtSigPlusBkg->SetTitle(("N_{Sig} / #sqrt{N_{Sig}+N_{Bkg}}   for RPV gluino m="+to_string(masses[i])+" Gev, flavor = "+flavor).c_str());
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
      ///////////Plot nice Mjjj plots
      //////////////////////////////////////////////////////////////////
      nameIN="RPV_M"+to_string(masses[i])+"_"+flavor+"/0bFits/";
      cuts="bjet0_pt60_diag110_GE6jet";
      if (i>=5) cuts="bjet0_pt80_diag110_GE6jet";
      
      cout<<(nameIN+"P4Gaus_Mjjj_"+cuts).c_str()<<endl;
      TH2F* h_GluinoHist_Fit = (TH2F*) filelist_kin[p]->Get((nameIN+"P4Gaus_Mjjj_"+cuts).c_str())->Clone();
      cout<<((nameIN+"Mjjj_"+cuts+"MCcomb").c_str())<<endl;
      TH2F* h_GluinoHist_MCcomb = (TH2F*) filelist_kin[p]->Get((nameIN+"Mjjj_"+cuts+"_MCcomb").c_str())->Clone();
      cout<<((nameIN+"P4_Mjjj_"+cuts).c_str())<<endl;
      TF1* f_GluinoP4 = (TF1*) filelist_kin[p]->Get((nameIN+"P4_Mjjj_"+cuts).c_str())->Clone();
      cout<<((nameIN+"GaussP4_Mjjj_"+cuts).c_str())<<endl;
      TF1* f_GluinoGauss = (TF1*) filelist_kin[p]->Get((nameIN+"GaussP4_Mjjj_"+cuts).c_str())->Clone();
      
      TCanvas * cGluinoFitsOpti = new TCanvas(("RPV_M"+to_string(masses[i])+"_"+flavor+"_"+cuts).c_str(), ("RPV_M"+to_string(masses[i])+"_"+flavor+"_"+cuts).c_str(), 800, 600);
      h_GluinoHist_Fit->SetFillColor(kOrange-2);
      h_GluinoHist_Fit->SetLineColor(kBlack);
      string title="RPV gluino m="+to_string(masses[i])+", flavor = "+flavor+", #Delta = 110 GeV, #bf{6^{th} Jet p_{T} = 60 GeV}";
      if (i>=5) title="RPV gluino m="+to_string(masses[i])+", flavor = "+flavor+", #Delta = 110 GeV, #bf{6^{th} Jet p_{T} = 80 GeV}";
      
      h_GluinoHist_Fit->SetTitle(title.c_str());
      h_GluinoHist_Fit->GetYaxis()->SetTitle("Triplets / 10 GeV");
      h_GluinoHist_Fit->GetYaxis()->SetTitleOffset(1.3);
      h_GluinoHist_Fit->GetXaxis()->SetTitle("Triplet invariant Mass [GeV]");
      h_GluinoHist_Fit->Draw("histe");	
      
      h_GluinoHist_MCcomb->SetFillColor(10);
      h_GluinoHist_MCcomb->SetLineColor(kBlack);
      h_GluinoHist_MCcomb->Draw("samehist");
      f_GluinoGauss->SetLineColor(kRed);
      f_GluinoGauss->Draw("same");
      
      f_GluinoP4->Draw("same");
      
      f1.cd(namelist[0].c_str());
      cGluinoFitsOpti->Write();
      cGluinoFitsOpti->SaveAs((folder+"RPV_M"+to_string(masses[i])+"_"+flavor+"_"+cuts+postfix).c_str());
      
    }
    
    
    
    ///////Plots for normalized signal significance for different masses///////
    ///////-------------------------------------------------------------//////
    prefix="GluinoMass_vs_6thpT";
    nameIN=prefix+"_"+flavor+"_normalized";
    cout<<(nameIN).c_str()<<endl;
    TH2F* h_GluniMass_vs_6thpT= (TH2F*) filelist_kin[p]->Get((nameIN).c_str())->Clone();
    TCanvas * cGluniMass_vs_6thpT = new TCanvas((nameIN).c_str(), (nameIN).c_str(), 800, 600);	
    
    h_GluniMass_vs_6thpT->Draw("colztext");
    
    h_GluniMass_vs_6thpT->SetMarkerSize(1.6);
    h_GluniMass_vs_6thpT->SetMinimum(0);
    h_GluniMass_vs_6thpT->SetMaximum(1.7);
    h_GluniMass_vs_6thpT->SetTitle(("Normalized Signal Significance RPV flavor = "+flavor+", #Delta = 110 GeV").c_str());
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
  }
  
  
  
  
  //////////Plots for gluino b-tagging ONLY WITH 112_223 DIFFERENCES ARE EXPECTED optimization///////////////////////
  //////////---------------------------------------//////////////////////
  prefix="GluinoMass_vs_nBtags";
  flavor="113_223";
  string taggers[4]={"CSVLoose","CSVMedium","CSVTight","JPMedium"};
  for(int k=0; k<2;k++){
    if(k==0)nameIN=nameIN=prefix+"_"+flavor;
    if(k==1)nameIN=nameIN=prefix+"_"+flavor+"_pt80";
    TCanvas * cGluniMass_vs_Btag = new TCanvas((nameIN).c_str(), (nameIN).c_str(), 600, 750);	
    cGluniMass_vs_Btag->Divide(1,2);
    
    nameIN=nameIN=prefix+"_"+flavor;
    TH2F* h_GluniMass_vs_Tagger= (TH2F*) filelist_btag[0]->Get((nameIN).c_str())->Clone();
    
    //TH2F* h_GluniMass_vs_Tagger = new TH2F("GluniMass_vs_Tagger","h_GluniMass_vs_Tagger",9,0,9,10,0,10);
    
    //TH2F* h_GluniMass_vs_tagger= (TH2F*) filelist[2]->Get((nameIN).c_str())->Clone();
    for(int n=0; n<4;n++){
      if(k==0)nameIN=nameIN=prefix+"_"+flavor;
      if(k==1)nameIN=nameIN=prefix+"_"+flavor+"_pt80";
      
      TH2F* h_GluniMass_vs_Btag= (TH2F*) filelist_btag[n]->Get((nameIN).c_str())->Clone();
      
      for(int h=1; h<=10; h++){
	float newBin=h_GluniMass_vs_Btag->GetBinContent(3,h);
	h_GluniMass_vs_Tagger->SetBinContent(n+1,h,newBin);	
	
      }
      h_GluniMass_vs_Tagger->GetXaxis()->SetBinLabel(n+1,taggers[n].c_str());
      
      
      if(k==0)nameIN=nameIN=prefix+"_"+flavor+"_normalized";
      if(k==1)nameIN=nameIN=prefix+"_"+flavor+"_pt80_normalized";			
      TH2F* h_GluniMass_vs_Btag_norm= (TH2F*) filelist_btag[n]->Get((nameIN).c_str())->Clone();	
      
      cGluniMass_vs_Btag->cd(1);
      cGluniMass_vs_Btag->GetPad(1)->SetLeftMargin(0.17);
      cGluniMass_vs_Btag->GetPad(1)->SetGrid();
      h_GluniMass_vs_Btag->Draw("text");
      if(k==0){
	h_GluniMass_vs_Btag->SetTitle((taggers[n]+", #Delta = 110 GeV, 6^{th} Jet p_{T} > 60 GeV").c_str());
	h_GluniMass_vs_Btag->SetMinimum(0);
	h_GluniMass_vs_Btag->SetMaximum(40);}
      
      if(k==1){
	h_GluniMass_vs_Btag->SetTitle((taggers[n]+", #Delta = 110 GeV, 6^{th} Jet p_{T} > 80 GeV").c_str());
	h_GluniMass_vs_Btag->SetMinimum(0);
	h_GluniMass_vs_Btag->SetMaximum(5.5);
      }
      
      h_GluniMass_vs_Btag->GetYaxis()->SetLabelSize(0.06);
      h_GluniMass_vs_Btag->GetXaxis()->SetLabelSize(0.05);
      h_GluniMass_vs_Btag->GetXaxis()->SetRangeUser(1,5);
      
      cGluniMass_vs_Btag->cd(2);
      cGluniMass_vs_Btag->GetPad(2)->SetLeftMargin(0.17);
      cGluniMass_vs_Btag->GetPad(2)->SetGrid();
      h_GluniMass_vs_Btag_norm->Draw("colztext");
      
      if(k==0){
	h_GluniMass_vs_Btag_norm->SetMinimum(0.4);
	h_GluniMass_vs_Btag_norm->SetMaximum(1.2);
      }
      if(k==1){
	h_GluniMass_vs_Btag_norm->SetMinimum(0.2);
	h_GluniMass_vs_Btag_norm->SetMaximum(1.4);
      }
      
      h_GluniMass_vs_Btag_norm->GetYaxis()->SetLabelSize(0.06);
      h_GluniMass_vs_Btag_norm->GetXaxis()->SetLabelSize(0.05);
      h_GluniMass_vs_Btag_norm->GetXaxis()->SetRangeUser(1,5);
      h_GluniMass_vs_Btag_norm->SetTitle(taggers[n].c_str());
      
      f1.cd(namelist[1].c_str());
      cGluniMass_vs_Btag->Write();
      cGluniMass_vs_Btag->SaveAs((folder+taggers[n]+nameIN+postfix).c_str());
    }
    if(k==0)nameIN=nameIN=prefix+"_"+flavor;
    if(k==1)nameIN=nameIN=prefix+"_"+flavor+"_pt80";
    
    TCanvas * cGluniMass_vs_Tagger = new TCanvas((nameIN+"geq1bEvent").c_str(), (nameIN+"geq1bEvent").c_str(), 700, 550);
    h_GluniMass_vs_Tagger->Draw();
    h_GluniMass_vs_Tagger->SetTitle("N_{Sig} / #sqrt{N_{Sig}+N_{Bkg}}, >= 1b Event, #Delta = 110 GeV, 6^{th} Jet p_{T} > 60 GeV");
    if(k==1)h_GluniMass_vs_Tagger->SetTitle("N_{Sig} / #sqrt{N_{Sig}+N_{Bkg}}, >= 1b Event, #Delta = 110 GeV, 6^{th} Jet p_{T} > 80 GeV");
    h_GluniMass_vs_Tagger->Draw("text");
    h_GluniMass_vs_Tagger->GetXaxis()->SetRangeUser(0,3);
    h_GluniMass_vs_Tagger->GetYaxis()->SetRangeUser(0,4);
    if(k==1)h_GluniMass_vs_Tagger->GetYaxis()->SetRangeUser(5,9);
    cGluniMass_vs_Tagger->SetGrid();
    cGluniMass_vs_Tagger->Write();
    nameIN=nameIN+"geq1bEvent";
    cGluniMass_vs_Tagger->SaveAs((folder+nameIN+postfix).c_str());
  }
  
  
  
  
  
  //////////////////Make Plots for amplitude, width and integral////////////////
  string fitplots[3]={"GausMean","GausAmp","GausWidth"};
  string fitgraphs[5]={"geq0_Event","geq1_Event","geq1_Triplet","geq2_Event","geq2_Event_geq1_Triplet"};
  float up60[3]={500,1000,60};
  float down60[3]={200,10,10};
  float up80[3]={1600,40,130};
  float down80[3]={470,0.0001,20};
  
  float up[3]={1600,1000,130};
  float down[3]={200,0.0001,10};
  
  
  string namegraphs[5]={">= 0 b Event",">= 1 b Event",">= 1 b Triplet",">= 2 b Event","& >=1 b Triplet"};
  
  int colors[5]={1,2,4,6,8};
  int markers[5]={20,21,22,33,34};
  string pt;
  
  
  for(int l=0;l<2;l++){
    flavor="113_223";
    if(l==1) flavor="112";
    for(int p=0;p<2;p++){
      pt="60";
      if(p==1)pt="80";
      for(int k=0; k<3;k++){
	TCanvas * cGluino_vs_Mass= new TCanvas((fitplots[k]+"_"+pt).c_str(), (fitplots[k]+"_"+pt).c_str(), 800, 600);
	TLegend *leg;
	if(k==1) {
	  leg = new TLegend(0.6,0.2,0.8994975,0.5,NULL,"brNDC");
	  cGluino_vs_Mass->SetLogy();
	}
	else leg = new TLegend(0.1,0.7,0.48,0.9);
	
	for(int h=0; h<5;h++){
	  
	  nameIN=fitplots[k]+"_vs_Mass_"+flavor+"_"+pt+"_"+fitgraphs[h];
	  cout<<(nameIN).c_str()<<endl;
	  TGraphErrors* g_GausAmp_113_223=(TGraphErrors*) filelist_param[l]->Get((nameIN).c_str())->Clone();
	  g_GausAmp_113_223->SetLineColor(colors[h]);
	  g_GausAmp_113_223->SetMarkerColor(colors[h]);
	  g_GausAmp_113_223->SetMarkerStyle(markers[h]);
	  if(h==0)g_GausAmp_113_223->Draw("acPsame");
	  else g_GausAmp_113_223->Draw("cPsame");
	  g_GausAmp_113_223->GetYaxis()->SetTitle((fitplots[k]+" [GeV]").c_str());
	  g_GausAmp_113_223->GetYaxis()->SetTitleOffset(1.3);
	  g_GausAmp_113_223->GetYaxis()->SetRangeUser(down[k],up[k]);
	  //g_GausAmp_113_223->GetXaxis()->SetRangeUser(200,500);
	  //g_GausAmp_113_223->GetYaxis()->SetRangeUser(down60[k],up60[k]);
	  g_GausAmp_113_223->SetTitle((fitplots[k]+", flavor = "+flavor+", #Delta = 110 GeV, #bf{6^{th} Jet p_{T} > 60 GeV}").c_str());
	  
	  if(p==1){
	    //g_GausAmp_113_223->GetXaxis()->SetRangeUser(470,1600);
	    //	g_GausAmp_113_223->GetYaxis()->SetRangeUser(down80[k],up80[k]);
	    g_GausAmp_113_223->SetTitle((fitplots[k]+", flavor = "+flavor+", #Delta = 110 GeV, #bf{6^{th} Jet p_{T} > 80 GeV}").c_str());
	  }
	  g_GausAmp_113_223->GetXaxis()->SetTitle("Gluino Mass [GeV]");
	  
	  leg->AddEntry(g_GausAmp_113_223,namegraphs[h].c_str(),"lp");
	  
	}
	leg->Draw();
	
	cGluino_vs_Mass->Write();
	cGluino_vs_Mass->SaveAs((folder+fitplots[k]+"_"+flavor+"_"+pt+postfix).c_str());
      }
    }
  }
  
  
  
}





