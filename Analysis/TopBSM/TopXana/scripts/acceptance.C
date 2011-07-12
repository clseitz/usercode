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
void acceptance()
{
  float lumi=1000;
  vector <string > namelist;
   vector <TFile* > data;
 vector <TFile* > filelist;
 vector<float> nEvtTot;
 vector<float> McXsec;
 vector<float> DataLumi;
  //file 0-3 are the files to fit

		 filelist.push_back(TFile::Open("/cms/data24/clseitz/MC_4_2_4/TTbarJets_pileup/TTbarJets_LeptonANA_full.root"));
		 namelist.push_back("TTbarJEts");
		 nEvtTot.push_back(3701936);
		 McXsec.push_back(152);
		 DataLumi.push_back(lumi);

		 filelist.push_back(TFile::Open("/cms/data24/clseitz/MC_4_2_4/Wprime2/Wp1000_CMS_LeptonANA_2.root"));
		 namelist.push_back("Wp1000");
		 nEvtTot.push_back(99995);
		 McXsec.push_back(2);
		 DataLumi.push_back(lumi);
		 filelist.push_back(TFile::Open("/cms/data24/clseitz/MC_4_2_4/Wprime2/Wp600_CMS_LeptonANA_2.root"));
		 namelist.push_back("Wp600");
		 nEvtTot.push_back(99987);
		 McXsec.push_back(2);
		 DataLumi.push_back(lumi);

  TFile fnew1("acceptance_plots.root", "recreate");
  
  
  

  for(int file=0; file<3; file++){
    std::stringstream dir;
    cout<<endl;
    cout<<namelist[file]<<endl;;
    dir<<namelist[file];
    fnew1.cd();
    if(!fnew1.GetDirectory((dir.str()).c_str()))
      fnew1.mkdir((dir.str()).c_str());
    int plotcount=1;
    TCanvas* c1= new TCanvas("c1","c1",800,600);
    c1->Divide(3,3);
    //ptloop
    for(int i=20; i<=60; i=i+20){
      //diag_cut loop
      	for (int k=100; k<=180; k=k+40){

      // int i=23;
	  //int k=150;
      int diag=k;
	
	//defining the names to read in of historgrams
      std::stringstream sMjjj,sMjj;
      sMjjj<<"Triplets/jetpt_"<<i<<"/Mjjj_pt"<<i<<"_diag"<<diag<<"_GE4jet";
      sMjj<<"Triplets/Mjj_"<<i<<"_20_"<<diag;

	TH1F* temp_Mjjj = (TH1F*) filelist[file]->Get((sMjjj.str()).c_str());
	//	TH1F* temp_Mjj = (TH1F*) filelist[file]->Get((sMjj.str()).c_str());
	c1->cd(plotcount);
	temp_Mjjj->Draw();
	plotcount++;
	fnew1.cd();
	fnew1.cd((dir.str()).c_str());
	temp_Mjjj->Write();
	//	temp_Mjj->Write();
	float tot=0;
	float bg=0;
	float sig=0;
	tot=temp_Mjjj->GetBinContent(17)+temp_Mjjj->GetBinContent(18)+temp_Mjjj->GetBinContent(19)+temp_Mjjj->GetBinContent(20);
	bg=2*(temp_Mjjj->GetBinContent(16)+temp_Mjjj->GetBinContent(21));
	sig=tot-bg;
	float acc=0;
	acc=sig/nEvtTot[file];
	float Nexp=0;
	Nexp=acc*DataLumi[file]*McXsec[file];
		cout<<"Pt_cut: "<<i<<" Diag: "<<diag<<endl;
		//	if (file<1) cout<<"Ntot: "<<tot<<" Nbg: "<<bg<<" Nobserved: "<<Nexp<<endl;
	if (file==7) cout<<"Ntot: "<<tot<<" Nbg: "<<bg<<" Nsig: "<<sig<<" acceptance: "<<acc*100<<"% Nexpected: "<<Nexp<<endl;
	if (file>=0) cout<<"Ntot: "<<tot<<" Nbg: "<<bg<<" Nsig: "<<sig<<" acceptance: "<<acc*100<<"%"<<endl;
		}

	
	}
	fnew1.cd();
	fnew1.cd((dir.str()).c_str());
    c1->Write();
       
 } 
} 


