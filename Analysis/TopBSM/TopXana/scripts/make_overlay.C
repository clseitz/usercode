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
  float lumi=1000;
  vector <string > namelist;
  vector <string > plotlist;
  vector <TFile* > data;
  vector <TFile* > filelist;
  vector<float> nEvtTot;
  vector<float> McXsec;
  vector<float> DataLumi;
  //file 0-3 are the files to fit
  
  filelist.push_back(TFile::Open("/cms/data24/clseitz/MC_4_2_4/TTbarJets_pileup/TTbarJets_LeptonANA_full_quad.root"));
  namelist.push_back("TTbarJEts");
  nEvtTot.push_back(3701936);
  McXsec.push_back(8);
  DataLumi.push_back(lumi);
  
  filelist.push_back(TFile::Open("/cms/data24/clseitz/MC_4_2_4/Wprime2/Wp1000_CMS_LeptonANA_quad.root"));
  namelist.push_back("Wp1000");
  nEvtTot.push_back(99995);
  McXsec.push_back(8.0);
  DataLumi.push_back(lumi);
  filelist.push_back(TFile::Open("/cms/data24/clseitz/MC_4_2_4/Wprime2/Wp600_CMS_LeptonANA_quad.root"));
  namelist.push_back("Wp600");
  nEvtTot.push_back(99987);
  McXsec.push_back(8.0);
  DataLumi.push_back(lumi);
  filelist.push_back(TFile::Open("/cms/data24/clseitz/MC_4_2_4/Sbottom/Sbottom750_neutralino150_LeptonAna.root"));
  namelist.push_back("Sbottom");
  nEvtTot.push_back(7800);
  McXsec.push_back(8.0);
  DataLumi.push_back(lumi);
  plotlist.push_back("Event/SumptSig4Highest");
  plotlist.push_back("Event/SumptSig4SecondHighest");
  plotlist.push_back("Event/h_TransMassLepMET4Jet");
  
  
  
  
  TFile fnew1("overlay_plots.root", "recreate");
  
  
  
  for(int i=0; i<plotlist.size(); i++){
    TCanvas* c1= new TCanvas((plotlist[i].c_str()),(plotlist[i].c_str()),800,600);
    TH1F* dummy;
    if(i==0 || i==1) dummy = new TH1F("","",100,0,2);
    if(i==2 ) dummy = new TH1F("","",1000,0,2000);
    dummy->GetYaxis()->SetRangeUser(0,100);
    dummy->Draw();
			     TLegend *leg = new TLegend(0.7060302,0.7692308,0.9761307,0.972028,NULL,"brNDC");


    for(int file=0; file<4; file++){
      std::stringstream dir;
      cout<<namelist[file]<<endl;;
      dir<<namelist[file];
      TH1F* temp;
      temp = (TH1F*) filelist[file]->Get(plotlist[i].c_str());
      float scale = (1/nEvtTot[file])*DataLumi[file]*McXsec[file];
      temp->Scale(scale);
      c1->cd();
      temp->Draw("SAME");
      temp->SetLineColor(file+1);
      leg->AddEntry(temp, namelist[file].c_str(),"lep");

     
      
    }
    c1->cd();
    leg->Draw();
	fnew1.cd();
        c1->Write();

        //      temp_Mjj->Wr
  }
  
} 


