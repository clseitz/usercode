#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TObject.h"
#include <sstream>



void CountMjjj(TH1F *temp_diagcut,float diag, float i){
	 

}
void make_overlay()
{
  float lumi=1000.;
  vector <string > namelist;
  vector <string > plotlist;
  vector <TFile* > data;
  vector <TFile* > filelist;
  vector<float> nEvtTot;
  vector<float> McXsec;
  vector<float> DataLumi;
  //file 0-3 are the files to fit
  
  filelist.push_back(TFile::Open("/uscms_data/d3/clseitz/TTBarJets/TTbarJets_LeptonANA_e_vec_delphi_120.root"));
  namelist.push_back("TTbarJEts_e");
  //nEvtTot.push_back(216095.0);
  nEvtTot.push_back(3.6838e+06);
  McXsec.push_back(157.5);
  DataLumi.push_back(lumi);

filelist.push_back(TFile::Open("/uscms_data/d3/clseitz/TTBarJets/TTbarJets_LeptonANA_e_vec_delphi_120.root"));
  namelist.push_back("TTbarJEts_e");
  //nEvtTot.push_back(216095.0);
  nEvtTot.push_back(3.6838e+06);
  McXsec.push_back(0);
  DataLumi.push_back(lumi);

  /*filelist.push_back(TFile::Open("/uscms_data/d3/clseitz/WJets/WJets_LeptonANA_e_vec_delphi_120.root"));
  nEvtTot.push_back(4.5972e+07);
  namelist.push_back("WJets_muon");
  McXsec.push_back(31314.0);
  DataLumi.push_back(lumi);
  */

  filelist.push_back(TFile::Open("/uscms_data/d3/clseitz/WprimeHexcms/Wp600_CMS_LeptonANA_e_vec_delphi_120.root"));
  namelist.push_back("Wp600_e");
  nEvtTot.push_back(99987.0);
  McXsec.push_back(8.0);
  DataLumi.push_back(lumi);
  filelist.push_back(TFile::Open("/uscms_data/d3/clseitz/WprimeHexcms/Wp1000_CMS_LeptonANA_e_vec.root"));
  namelist.push_back("Wp1000_e");
  nEvtTot.push_back(99995.0);
  McXsec.push_back(0.72);
  DataLumi.push_back(lumi);
  
  
  //filelist.push_back(TFile::Open("/cms/data24/clseitz/MC_4_2_4/Sbottom/Sbottom750_neutralino150_LeptonAna_e25_met30_b12.root"));

filelist.push_back(TFile::Open("/home/clseitz/MyCMS/CMSSW_4_2_4/src/TopBSM/TopXana/submit/test.root"));
  namelist.push_back("Sbottom");
  nEvtTot.push_back(7800.0);
  McXsec.push_back(8.0);
  DataLumi.push_back(lumi);
  filelist.push_back(TFile::Open("/cms/data21/clseitz/CMS_leptons/Electrons/NewCode4/Electrons_full_900_emu_met50_b1.root"));
  namelist.push_back("electron");
  nEvtTot.push_back(1.0);
  McXsec.push_back(1.0);
  DataLumi.push_back(1.0);
  //plotlist.push_back("Event/SumptSig4HighestPlus");
  //plotlist.push_back("Event/SumptSig4SecondHighestPlus");
  //plotlist.push_back("Event/TransMassLepMET4JetPlus");
  //plotlist.push_back("Event/TransMassLepMET4SecondJetPlus");
  //plotlist.push_back("Event/SumptSig4HighestMinus");
  //plotlist.push_back("Event/SumptSig4SecondHighestMinus");
  //plotlist.push_back("Event/TransMassLepMET4JetMinus");
  //plotlist.push_back("Event/TransMassLepMET4SecondJetMinus");
  
 

plotlist.push_back("5Jet_1b_P/LeadingJetPt5Jet_1b_P");
  plotlist.push_back("5Jet_2b_P/LeadingJetPt5Jet_2b_P");
  plotlist.push_back("4Jet_1b_P/LeadingJetPt4Jet_1b_P");
  plotlist.push_back("4Jet_2b_P/LeadingJetPt4Jet_2b_P");
  plotlist.push_back("5Jet_1b_M/LeadingJetPt5Jet_1b_M");
  plotlist.push_back("5Jet_2b_M/LeadingJetPt5Jet_2b_M");
  plotlist.push_back("4Jet_1b_M/LeadingJetPt4Jet_1b_M");
  plotlist.push_back("4Jet_2b_M/LeadingJetPt4Jet_2b_M");
   /*
 plotlist.push_back("Event/TransMassLepMET5JetPlus_5jet1b");
  plotlist.push_back("Event/TransMassLepMET5JetPlus_5jet2b");  
  plotlist.push_back("Event/TransMassLepMET5JetMinus_5jet1b");
  plotlist.push_back("Event/TransMassLepMET5JetMinus_5jet2b");
  */
  TFile fnew1("overlay_plots.root", "recreate");
  
  
  
  for(int i=0; i<(plotlist.size()/2); i++){
    TCanvas* c1= new TCanvas((plotlist[i].c_str()),(plotlist[i].c_str()),800,600);
    TH1F* dummy;
 dummy = new TH1F("","",1000,0,2000);
    //if(i==0 || i==1 || i==4 || i==5) dummy = new TH1F("","",100,0,2);
    //if(i==2 || i==3 || i==6 || i ==7) dummy = new TH1F("","",1000,0,2000);
 //if(i==0 || i==1) dummy->GetYaxis()->SetRangeUser(0.1,200);
 //if(i==2 || i==3) dummy->GetYaxis()->SetRangeUser(0.1,500);
    //c1->SetLogy();
    //c1->SetGridx();
    //c1->SetGridy();
    dummy->SetTitle(plotlist[i].c_str());
    dummy->Draw();
    TLegend *leg = new TLegend(0.7060302,0.7692308,0.9761307,0.972028,NULL,"brNDC");


    for(int file=0; file<4; file++){
      std::stringstream dir;
      cout<<namelist[file]<<endl;
      dir<<namelist[file];
      TH1F* temp;
      TH1F* tempa;
      TH1F* tempb;

      tempa = (TH1F*) filelist[file]->Get(plotlist[i].c_str());
      temp =  (TH1F*) tempa->Rebin(10, "temp");
      TH1F* temp2;
      tempb = (TH1F*) filelist[file]->Get(plotlist[i+(plotlist.size()/2)].c_str());
      temp2 = (TH1F*) tempb->Rebin(10,"temp2");
      temp->Add(temp2);
      float scale = (1.0/nEvtTot[file])*DataLumi[file]*McXsec[file];
      
      temp->Scale(scale);
      float height;
     
     

      c1->cd();
      if(file==0)temp->Draw();
      if(file>0)temp->Draw("SAME");
      temp->SetLineColor(file+1);
      temp->SetLineWidth(2);
      if(file==4){
	temp->Sumw2();
	temp->SetMarkerStyle(23);
	temp->SetLineColor(12);
      }
      leg->AddEntry(temp, namelist[file].c_str(),"lep");

     
      
    }
    c1->cd();
    leg->Draw();
	fnew1.cd();
        c1->Write();
	std::stringstream gif;
	gif<<plotlist[i]<<".gif";

	c1->SaveAs((gif.str()).c_str());
        //      temp_Mjj->Wr
  }
  
} 


