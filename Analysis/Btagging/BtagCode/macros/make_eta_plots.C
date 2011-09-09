#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TObject.h"

void make_eta_plots()
{
  float lumi=189;
  vector <string> namelist;
   vector <TFile* > data;
 vector <TFile* > filelist;
 vector<float> nEvtTot;
 vector<float> McXsec;
 vector<float> DataLumi;
 vector <string > Btaggers;
vector <string > B_OP;
vector <string > flavors;
 vector<double > operating_point; vector<string > op_name;
 char hNAME[99];
 char dir[99];

  //file 0-3 are the files to fit
  
  
 
 filelist.push_back(TFile::Open("/cms/data24/clseitz/BtaggEff/RPV_MC_113_223_200GeV_424_2raw.root"));
 namelist.push_back("RPV_MC_113_223_200GeV");

 filelist.push_back(TFile::Open("/cms/data24/clseitz/BtaggEff/TTbarJets/TTbarJets_Btag_raw_full_no3.root"));
 namelist.push_back("TTbarJets");

 filelist.push_back(TFile::Open("/cms/data24/clseitz/BtaggEff/Zprime/Zprime_M1000_W100_424_raw.root"));
namelist.push_back("Zprime_M1000_W100");
 filelist.push_back(TFile::Open("/cms/data24/clseitz/BtaggEff/Zprime/Zprime_M1500_W15_424_raw.root"));
namelist.push_back("Zprime_M1500_W15");
 filelist.push_back(TFile::Open("/cms/data24/clseitz/BtaggEff/Zprime/Zprime_M500_W50_424_raw.root"));
namelist.push_back("Zprime_M500_W50");
 filelist.push_back(TFile::Open("/cms/data24/clseitz/BtaggEff/Zprime/Zprime_M500_W5_424_raw.root"));
namelist.push_back("Zprime_M500_W5");
		


		 Btaggers.push_back("discriminator_TCHE");
		 Btaggers.push_back("discriminator_TCHP");
		 Btaggers.push_back("discriminator_SSVHE");
		 Btaggers.push_back("discriminator_SSVHP");
		 flavors.push_back("b");
		 flavors.push_back("c");
		 flavors.push_back("udsg");


		 op_name.push_back("TCHEL"); operating_point.push_back(1.70);
		 op_name.push_back("TCHEM"); operating_point.push_back(3.30);
		 op_name.push_back("TCHPM"); operating_point.push_back(1.93);
		 op_name.push_back("TCHPT"); operating_point.push_back(3.41);
		 op_name.push_back("SSVHEM"); operating_point.push_back(1.74);
		 op_name.push_back("SSVHET"); operating_point.push_back(3.05);
		 op_name.push_back("SSVHPT"); operating_point.push_back(2.00);
		 op_name.push_back("none");
	
  TFile fnew1("eta_bins.root", "recreate");
  
  
  
  
  // Double_t xbins[27]={0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,250,300,400,500,600,1000};
   Double_t xbins[15]={0,20,30,40,50,60,70,80,100,120,240,380,520,660,1000};
   //making plots for btag efficiency and miss tag rate
    for(int file=0; file<6; file++){
      cout<<namelist[file]<<endl;;
      sprintf(dir, "%s",namelist[file].c_str());
      
      if(!fnew1.GetDirectory(dir))
	fnew1.mkdir(dir);
      
      //Loop for the different OP
      for(int i=0; i<7; i++){

	//TCanvas* c1 = new TCanvas((sOP1.str()).c_str(),(sOP1.str()).c_str(),800,600);
	

	for (int a=0; a<3; a++){
	  std::stringstream sOP1;
	  sOP1<<"BTagEff_jet_pt_bins_eta_"<<op_name[i]<<"_"<<flavors[a]<<"_"<<dir;

	  std::stringstream name1;
	  name1<<"B-tag Efficiency "<<op_name[i]<<" "<<flavors[a]<<" "<<dir;
	  std::stringstream name2;
	  name2<<"Mis-tag Efficiency "<<op_name[i]<<" "<<flavors[a]<<" "<<dir;
	  TCanvas* c1 = new TCanvas((sOP1.str()).c_str(),(sOP1.str()).c_str(),800,600);
	TH1F* dummy = new TH1F("zmass","",1000,0,1000);
	dummy->Draw();
	dummy->GetXaxis()->SetTitle("pt of the jets");
	dummy->GetXaxis()->SetTitleOffset(1.9);
	dummy->GetYaxis()->SetTitleOffset(2.2);
	if(a==2)
	  {dummy->SetTitle((name2.str()).c_str());
	    dummy->GetYaxis()->SetTitle("mis-tag efficiency");
	    dummy->GetYaxis()->SetRangeUser(0,0.1);
	  }
	if(a==0){
	  dummy->SetTitle((name1.str()).c_str());
	  dummy->GetYaxis()->SetTitle("b-tag efficiency");
	  dummy->GetYaxis()->SetRangeUser(0,1);
	}
	
	
	dummy->GetXaxis()->SetRangeUser(0,300);
	  std::stringstream sOP2,sOP3,sOP4;
	  sOP2<<"Btag/jet_pt_"<<op_name[i]<<"_"<<flavors[a];
	  sOP3<<"Btag/jet_pt_l1p2_"<<op_name[i]<<"_"<<flavors[a];
	  sOP4<<"Btag/jet_pt_1p2_2p4_"<<op_name[i]<<"_"<<flavors[a];
	   
	  
	  
	  std::stringstream sNoBtagl1p2,sNoBtag1p2_2p4,sNoBtag;
	  sNoBtag<<"Btag/jet_pt_none_"<<flavors[a];
	  sNoBtagl1p2<<"Btag/jet_pt_l1p2_none_"<<flavors[a];
	  sNoBtag1p2_2p4<<"Btag/jet_pt_1p2_2p4_none_"<<flavors[a];
	  
	  TH1F* tempBtag;
	  TH1F* tempBtagl1p2;
	  TH1F* tempBtag1p2_2p4;
	  TH1F* tempNoBtag;
	  TH1F* tempNoBtagl1p2;
	  TH1F* tempNoBtag1p2_2p4;
	  TH1F* hBtag;
	  TH1F* hBtagl1p2;
	  TH1F* hBtag1p2_2p4;
	  TH1F*  hNoBtag;
	  TH1F*  hNoBtagl1p2;
	  TH1F*  hNoBtag1p2_2p4;
       
	  //get histograms
	  tempBtag = (TH1F*) filelist[file]->Get((sOP2.str()).c_str());
	  tempBtagl1p2 = (TH1F*) filelist[file]->Get((sOP3.str()).c_str());
	  tempBtag1p2_2p4 = (TH1F*) filelist[file]->Get((sOP4.str()).c_str());

	   tempNoBtag = (TH1F*) filelist[file]->Get((sNoBtag.str()).c_str());
	  tempNoBtagl1p2 = (TH1F*) filelist[file]->Get((sNoBtagl1p2.str()).c_str());
	  tempNoBtag1p2_2p4 = (TH1F*) filelist[file]->Get((sNoBtag1p2_2p4.str()).c_str());

	  //define errors
	  tempBtag->Sumw2();
	  tempBtagl1p2->Sumw2();
	  tempBtag1p2_2p4->Sumw2();
	  tempNoBtag->Sumw2();
	  tempNoBtagl1p2->Sumw2();
	  tempNoBtag1p2_2p4->Sumw2();

	  //rebin and make new histos

	  hBtag=(TH1F*) tempBtag->Rebin(14,"hBtag",xbins);
	  hBtagl1p2=(TH1F*) tempBtagl1p2->Rebin(14,"hBtagl1p2",xbins);
	  hBtag1p2_2p4=(TH1F*) tempBtag1p2_2p4->Rebin(14,"hBtag1p2_2p4",xbins);
	  hNoBtag=(TH1F*) tempNoBtag->Rebin(14,"hNoBtag",xbins);
	  hNoBtagl1p2=(TH1F*) tempNoBtagl1p2->Rebin(14,"hNoBtagl1p",xbins);
	  hNoBtag1p2_2p4=(TH1F*) tempNoBtag1p2_2p4->Rebin(14,"hNoBtag1p2_2p4",xbins);

	  hBtag->SetName((sOP2.str()).c_str());
	  hBtagl1p2->SetName((sOP3.str()).c_str());
	  hBtag1p2_2p4->SetName((sOP4.str()).c_str());
	  hNoBtag->SetName((sNoBtag.str()).c_str());
	  hNoBtagl1p2->SetName((sNoBtagl1p2.str()).c_str());
	  hNoBtag1p2_2p4->SetName((sNoBtag1p2_2p4.str()).c_str());

	
	  fnew1.cd(dir);
	  //temp_Btag->Write();
	  //temp_NoBtag->Write();
	  std::stringstream seff;
	  seff<<"BTagEff_bins_of_eta"<<op_name[i]<<"_"<<flavors[a];
	  
	  TH1F* BTagEff; TH1F* BTagEffl1p2; TH1F* BTagEff1p2_2p4;
	  TH1F* BTagEffEta;
	  BTagEff=(TH1F*) hBtag->Clone();
	  BTagEff->Divide(hNoBtag);
	  BTagEff->SetMarkerStyle(6);
	  BTagEff->SetName((seff.str()).c_str());
	  BTagEff->SetTitle((seff.str()).c_str());

	  BTagEffl1p2=(TH1F*) hBtagl1p2->Clone();
	  BTagEffl1p2->Divide(hNoBtagl1p2);
	  BTagEffl1p2->SetName((seff.str()).c_str());
	  BTagEffl1p2->SetLineColor(2);
	  BTagEffl1p2->SetMarkerColor(2);
	  BTagEffl1p2->SetMarkerStyle(2);
	  BTagEffl1p2->SetTitle((seff.str()).c_str());

	  BTagEff1p2_2p4=(TH1F*) hBtag1p2_2p4->Clone();
	  BTagEff1p2_2p4->Divide(hNoBtag1p2_2p4);
	  BTagEff1p2_2p4->SetName((seff.str()).c_str());
	  BTagEff1p2_2p4->SetLineColor(3);
	  BTagEff1p2_2p4->SetMarkerColor(3);
	   BTagEff1p2_2p4->SetMarkerStyle(3);
	  BTagEff1p2_2p4->SetTitle((seff.str()).c_str());
	  c1->cd();
	 
	  BTagEff->Draw("SAME");
 BTagEff->SetTitle((sOP1.str()).c_str());
	  BTagEffl1p2->Draw("Same");
	 BTagEff1p2_2p4->Draw("Same");
	 TLegend *leg = new TLegend(0.7060302,0.7692308,0.9761307,0.972028,NULL,"brNDC");
	 leg->AddEntry(BTagEff,"|eta| < 2.4","lep");
	 leg->AddEntry(BTagEffl1p2,"|eta| < 1.2","lep");
	 leg->AddEntry(BTagEff1p2_2p4,"1.2 < |eta| < 2.4","lep");
	 leg->Draw();

	fnew1.cd(dir);
	sOP1<<".gif";
      c1->SaveAs((sOP1.str()).c_str());

        c1->Write();
	
	std::stringstream s2D,s2Dname, sNo2D;
	s2D<<"Btag/jet_2D_eta_pt_"<<op_name[i]<<"_"<<flavors[a];
	s2Dname<<"jet_2D_eta_pt_"<<op_name[i]<<"_"<<flavors[a]<<"_"<<dir;
	  sNo2D<<"Btag/jet_2D_eta_pt_none_"<<flavors[a];
	//now lets do the 2D stuff
	 TH2F*  temp2D;
	 TH2F*  tempNo2D;
	 TH2F*  h2D;
	 TH2F*  hNo2D;
	 //get histograms
	 temp2D = (TH2F*) filelist[file]->Get((s2D.str()).c_str());
	 tempNo2D = (TH2F*) filelist[file]->Get((sNo2D.str()).c_str());
	 cout<< temp2D->GetXaxis()->GetNbins()<<" "<<temp2D->GetYaxis()->GetNbins()<<endl;
	 TH2F* BTagEff2D= new TH2F((s2D.str()).c_str(),(s2D.str()).c_str(),200,0,4,500,0,1000);
	 h2D=(TH2F*)temp2D->Rebin2D(4,15,"h2D");
	 hNo2D=(TH2F*)tempNo2D->Rebin2D(4,15,"h2D");
	 BTagEff2D->Rebin2D(4,15);
	 for (int i=1; i< h2D->GetXaxis()->GetNbins(); i++)
	   {
	     for(int j=1; j<h2D->GetYaxis()->GetNbins(); j++)
	       { 
	 float eff=0;
		 //cout<<i<<" "<<j<<" "<< htempno2D->GetBinContent(i,j)<<" "<< h2D->GetBinContent(i,j)<<endl;
		 if (hNo2D->GetBinContent(i,j)==0) eff=0;
		 else eff= h2D->GetBinContent(i,j)/hNo2D->GetBinContent(i,j);
		 //cout<<eff<<endl;
		
		 BTagEff2D->SetBinContent(i,j,eff);
	       }
	   }
	 	fnew1.cd(dir);
		BTagEff2D->GetXaxis()->SetRangeUser(0,2.4);
		BTagEff2D->SetTitle((s2Dname.str()).c_str());
		BTagEff2D->Write();
		 TCanvas* c2 = new TCanvas((s2Dname.str()).c_str(),(s2Dname.str()).c_str(),800,600);
		 BTagEff2D->Draw("colz");
		s2Dname<<".gif";
		c2->SaveAs((s2Dname.str()).c_str());
	
	  
	}
	
	

      }
      
    }
   
    
      
      
} 


