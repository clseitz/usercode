
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TObject.h"
#include "THStack.h"
#include "TGraph.h"
#include <sstream>



void CountMjjj(TH1F *temp_diagcut,float diag, float i){
	 

}
void make_optimization()
{ char hNAME[99];
  float lumi=1000.;
  vector <string > namelist;
  
  vector <string > VarList;
  vector <TFile* > data;
  vector <TFile* > filelist;
  vector<float> nEvtTot;
  vector<float> McXsec;
  vector<float> DataLumi;

  
  filelist.push_back(TFile::Open("../TTBar_plots_additionalCuts.root"));
  namelist.push_back("TTbarJEts_e");
  nEvtTot.push_back(3.6838e+06);
  McXsec.push_back(157.5);
  DataLumi.push_back(lumi);
 filelist.push_back(TFile::Open("../Wp1000_plots_additionalCuts.root"));
  namelist.push_back("Wp1000_e");
  nEvtTot.push_back(99995.0);
  McXsec.push_back(0.72);
  DataLumi.push_back(lumi);
 
filelist.push_back(TFile::Open("../Wp600_plots_additionalCuts.root"));
  namelist.push_back("Wp600_e");
  nEvtTot.push_back(99987.0);
  McXsec.push_back(8.0);
  DataLumi.push_back(lumi);
  
 
  
 
 

 
  filelist.push_back(TFile::Open("../Sbottom750_plots_additionalCuts.root"));
  namelist.push_back("Sbottom750_e");
  nEvtTot.push_back(57073.0);
  McXsec.push_back(8.0);
  DataLumi.push_back(lumi);
 filelist.push_back(TFile::Open("../Stop350_plots_additionalCuts.root"));
  namelist.push_back("Stop350_e");
  nEvtTot.push_back(10000.0);
  McXsec.push_back(1);
  DataLumi.push_back(lumi);
  

  TH1F* h_TransMassLepMET1JetB_pt_ttbar;
  TH1F* h_TransMassLepMET1JetB_delphi_ttbar;
  TH1F* h_TransMassLepMET1JetB_st_ttbar;

  TH1F* h_TransMassLepMET1JetB_pt_wp600;
  TH1F* h_TransMassLepMET1JetB_delphi_wp600;
  TH1F* h_TransMassLepMET1JetB_st_wp600;

  TH1F* h_pt_ttbar;
  TH1F* h_delphi_ttbar;
  TH1F* h_st_ttbar;
  
  TH1F* h_pt_wp600;
  TH1F* h_delphi_wp600;
  TH1F* h_st_wp600;

  TH1F* h_pt_st_ttbar;
  TH1F* h_pt_st_wp600;
  TH1F* h_TransMassLepMET1JetB_pt_st_ttbar;
   TH1F* h_TransMassLepMET1JetB_pt_st_wp600;
 TH2F* h_TransMassLepMET1JetB_pt_st= new TH2F("TransMassLepMET1JetB_pt_st","TransMassLepMET1JetB_pt_st",35,200,1950,35,70,420);
  vector<float> v_pt_y;
  vector<float> v_delphi_y;
  vector<float> v_st_y;

 vector<float> v_pt_x;
  vector<float> v_delphi_x;
  vector<float> v_st_x;

 TFile* fnew1=new TFile("optimization.root", "recreate");

 for(int i=0; i<35; i++){
     cout<<"do"<<endl;
     sprintf(hNAME, "TransMassLepMET4Jet_1jet_%i_pt", i*10+70);
     h_pt_ttbar = (TH1F*) filelist[0]->Get(hNAME);
     h_pt_wp600 = (TH1F*) filelist[1]->Get(hNAME);
     THStack sh_pt;
     TCanvas* c_pt= new TCanvas(hNAME,hNAME,800,600);
     cout<<"do"<<endl;
     sprintf(hNAME, "TransMassLepMET4Jet_delphi_%ip%i", i/2, ((int)((i*0.5+1)*10)) % 10);
     h_delphi_ttbar = (TH1F*) filelist[0]->Get(hNAME);
     h_delphi_wp600 = (TH1F*) filelist[1]->Get(hNAME);
     THStack sh_delphi;
     TCanvas* c_delphi= new TCanvas(hNAME,hNAME,800,600);
     sprintf(hNAME, "TransMassLepMET4Jet_st_%i", i*50+200);
     h_st_ttbar= (TH1F*) filelist[0]->Get(hNAME);
     h_st_wp600= (TH1F*) filelist[1]->Get(hNAME);
     THStack sh_st;
     TCanvas* c_st= new TCanvas(hNAME,hNAME,800,600);
     
     float scale_ttbar = (1.0/nEvtTot[0])*DataLumi[0]*McXsec[0];
     float scale_wp600 = (1.0/nEvtTot[1])*DataLumi[1]*McXsec[1];

   
     
     h_TransMassLepMET1JetB_pt_ttbar =  (TH1F*)  h_pt_ttbar->Rebin(5, "TransMassLepMET1JetB_pt_ttbar");
     h_TransMassLepMET1JetB_delphi_ttbar =  (TH1F*) h_delphi_ttbar->Rebin(5, "TransMassLepMET1JetB_delphi_ttbar");
     h_TransMassLepMET1JetB_st_ttbar =  (TH1F*) h_st_ttbar->Rebin(5, "h_TransMassLepMET1JetB_st_ttbar");
     
     h_TransMassLepMET1JetB_pt_wp600 =  (TH1F*) h_pt_wp600->Rebin(5, "h_TransMassLepMET1JetB_pt_wp600");
     h_TransMassLepMET1JetB_delphi_wp600 =  (TH1F*) h_delphi_wp600->Rebin(5, " h_TransMassLepMET1JetB_delphi_wp600");
     h_TransMassLepMET1JetB_st_wp600 =  (TH1F*) h_st_wp600->Rebin(5, "h_TransMassLepMET1JetB_st_wp600");

TLegend *leg = new TLegend(0.7060302,0.7692308,0.9761307,0.972028,NULL,"brNDC");
     leg->AddEntry(h_TransMassLepMET1JetB_pt_ttbar,"ttbar" ,"lep");
     leg->AddEntry(h_TransMassLepMET1JetB_pt_wp600, "wprime1000","lep");     

      h_TransMassLepMET1JetB_pt_ttbar->Scale(scale_ttbar);
     h_TransMassLepMET1JetB_delphi_ttbar->Scale(scale_ttbar);
     h_TransMassLepMET1JetB_st_ttbar->Scale(scale_ttbar);
     
     h_TransMassLepMET1JetB_pt_wp600->Scale(scale_wp600);
     h_TransMassLepMET1JetB_delphi_wp600->Scale(scale_wp600);
     h_TransMassLepMET1JetB_st_wp600->Scale(scale_wp600);

     h_TransMassLepMET1JetB_pt_wp600->SetLineColor(3);
     h_TransMassLepMET1JetB_delphi_wp600->SetLineColor(3);
     h_TransMassLepMET1JetB_st_wp600->SetLineColor(3);
     cout<<"do"<<endl;

     //make legend
     
     
    
     c_pt->cd();
     h_TransMassLepMET1JetB_pt_ttbar->Draw(); 
     h_TransMassLepMET1JetB_pt_wp600->Draw("same");
     leg->Draw();
     c_pt->Write();
     sh_pt.Add(h_TransMassLepMET1JetB_pt_ttbar); sh_pt.Add(h_TransMassLepMET1JetB_pt_wp600);
     leg->Draw();
     c_pt->cd();
     sprintf(hNAME, "TransMassLepMET1JetB_1jet_%i_pt_stack", i*10+70);
     c_pt->SetName(hNAME);
     sh_pt.Draw("hist");
     leg->Draw();
     c_pt->Write();

     c_delphi->cd();
     h_TransMassLepMET1JetB_delphi_ttbar->Draw(); 
     h_TransMassLepMET1JetB_delphi_wp600->Draw("same");
     leg->Draw();
      c_delphi->Write();
     sh_delphi.Add(h_TransMassLepMET1JetB_delphi_ttbar); sh_delphi.Add(h_TransMassLepMET1JetB_delphi_wp600);
     c_delphi->cd();
     sprintf(hNAME, "TransMassLepMET1JetB_delphi_%ip%i_stack", i/2, ((int)((i*0.5+1)*10)) % 10);
     c_delphi->SetName(hNAME);
     sh_delphi.Draw("hist");
     leg->Draw();
     c_delphi->Write();

     c_st->cd();
     h_TransMassLepMET1JetB_st_ttbar->Draw(); 
     h_TransMassLepMET1JetB_st_wp600->Draw("same");
     leg->Draw();
     c_st->Write();
     sh_st.Add(h_TransMassLepMET1JetB_st_ttbar); sh_st.Add(h_TransMassLepMET1JetB_st_wp600);
     c_st->cd();
     sprintf(hNAME, "TransMassLepMET1JetB_st_%i_stack", i*50+200);
     c_st->SetName(hNAME);
     sh_st.Draw("hist");
     leg->Draw();
     c_st->Write();

     float r_pt=h_TransMassLepMET1JetB_pt_wp600->Integral(0,h_TransMassLepMET1JetB_pt_wp600->GetNbinsX())/sqrt(h_TransMassLepMET1JetB_pt_ttbar->Integral(0,h_TransMassLepMET1JetB_pt_ttbar->GetNbinsX()));
     float r_delphi=h_TransMassLepMET1JetB_delphi_wp600->Integral(0,h_TransMassLepMET1JetB_delphi_wp600->GetNbinsX())/sqrt(h_TransMassLepMET1JetB_delphi_ttbar->Integral(0,h_TransMassLepMET1JetB_delphi_ttbar->GetNbinsX()));
     float r_st=h_TransMassLepMET1JetB_st_wp600->Integral(0,h_TransMassLepMET1JetB_st_wp600->GetNbinsX())/sqrt(h_TransMassLepMET1JetB_st_ttbar->Integral(0,h_TransMassLepMET1JetB_st_ttbar->GetNbinsX()));

     v_pt_y.push_back(r_pt);
     v_delphi_y.push_back(r_delphi);
     v_st_y.push_back(r_st);

     
     v_pt_x.push_back(i*10+70);
     v_delphi_x.push_back(i*0.5+1);
     v_st_x.push_back(i*50+200);

     cout<<h_TransMassLepMET1JetB_pt_ttbar->Integral(0,h_TransMassLepMET1JetB_pt_ttbar->GetNbinsX())<<endl;;

      for(int j=0; j<35; j++){
        
       sprintf(hNAME, "TransMassLepMET4Jet_1jet_%i_st_%i", i*10+70,j*50+200);
       TCanvas* c_pt_st= new TCanvas(hNAME,hNAME,800,600);
       THStack sh_pt_st;
       h_pt_st_ttbar = (TH1F*) filelist[0]->Get(hNAME);
       h_pt_st_wp600 = (TH1F*) filelist[1]->Get(hNAME);
       h_TransMassLepMET1JetB_pt_st_ttbar =  (TH1F*)  h_pt_st_ttbar->Rebin(5, "TransMassLepMET1JetB_pt_st_ttbar");
       h_TransMassLepMET1JetB_pt_st_wp600 =  (TH1F*)  h_pt_st_wp600->Rebin(5, "TransMassLepMET1JetB_pt_st_ttbar");
       h_TransMassLepMET1JetB_pt_st_ttbar->Scale(scale_ttbar);
       h_TransMassLepMET1JetB_pt_st_wp600->Scale(scale_wp600);
       h_TransMassLepMET1JetB_pt_st_wp600->SetLineColor(3);

        float r_pt_st=h_TransMassLepMET1JetB_pt_st_wp600->Integral(0,h_TransMassLepMET1JetB_pt_st_wp600->GetNbinsX())/sqrt(h_TransMassLepMET1JetB_pt_st_ttbar->Integral(0,h_TransMassLepMET1JetB_pt_st_ttbar->GetNbinsX()));
	h_TransMassLepMET1JetB_pt_st->Fill(j*50+200, i*10+70,r_pt_st);

	c_pt_st->cd();
	h_TransMassLepMET1JetB_pt_st_ttbar->Draw(); 
	h_TransMassLepMET1JetB_pt_st_wp600->Draw("same");
	leg->Draw();
	c_pt_st->Write();
	sh_pt_st.Add(h_TransMassLepMET1JetB_pt_st_ttbar); sh_pt_st.Add(h_TransMassLepMET1JetB_pt_st_wp600);
	leg->Draw();
	c_pt_st->cd();
	sprintf(hNAME, "TransMassLepMET1JetB_1jet_%i_st_%i_stack", i*10+70,j*50+200);
	c_pt_st->SetName(hNAME);
	sh_pt_st.Draw("hist");
	leg->Draw();
	c_pt_st->Write();

     }
     
 }
 
 
 TGraph* g_pt = new TGraph(v_pt_x.size(),&v_pt_x[0],&v_pt_y[0]);
 TGraph* g_delphi = new TGraph(v_delphi_x.size(),&v_delphi_x[0],&v_delphi_y[0]);
 TGraph* g_st = new TGraph(v_st_x.size(),&v_st_x[0],&v_st_y[0]);
 g_pt->SetTitle("Signal/Sqrt(Background) vs leading jet pt cut");
 g_delphi->SetTitle("Signal/Sqrt(Background) vs delphi(lep met) cut");
 g_st->SetTitle("Signal/Sqrt(Background) vs st cut");

 g_pt->SetName("g_pt");
 g_delphi->SetName("g_delphi");
 g_st->SetName("g_st");

 g_pt->GetXaxis()->SetTitle("leading jet pt cut");
 g_delphi->GetXaxis()->SetTitle("delphi(lep met) cut");
 g_st->GetXaxis()->SetTitle("st cut");

 g_pt->GetYaxis()->SetTitle("Signal/Sqrt(Background)");
 g_delphi->GetYaxis()->SetTitle("Signal/Sqrt(Background)");
 g_st->GetYaxis()->SetTitle("Signal/Sqrt(Background)");
 
 g_pt->GetXaxis()->SetTitleOffset(1.2);
 g_delphi->GetXaxis()->SetTitleOffset(1.2);
 g_st->GetYaxis()->SetTitleOffset(1.2);
 g_pt->GetYaxis()->SetTitleOffset(1.3);
 g_delphi->GetYaxis()->SetTitleOffset(1.3);
 g_st->GetXaxis()->SetTitleOffset(1.3);
 fnew1->cd();
 g_pt->Write(); 
 g_delphi->Write();
 g_st->Write();

 h_TransMassLepMET1JetB_pt_st->GetXaxis()->SetTitle("st cut");
 h_TransMassLepMET1JetB_pt_st->GetYaxis()->SetTitle("leading jet pt cut");
 h_TransMassLepMET1JetB_pt_st->GetXaxis()->SetTitleOffset(1.2);
h_TransMassLepMET1JetB_pt_st->GetYaxis()->SetTitleOffset(1.3);
 h_TransMassLepMET1JetB_pt_st->Write();
} 


