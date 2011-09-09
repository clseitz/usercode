#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TObject.h"

void btagging_plots()
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

 filelist.push_back(TFile::Open("/cms/data24/clseitz/BtaggEff/TTbarJets/TTbarJets_Btag_raw_full.root"));
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
	
  TFile fnew1("debug.root", "recreate");
  
  
  
  //fileloop
   cout<<"GE4Jet_GE1EventBTag_EQ1TripletBtag"<<endl;
   for(int file=0; file<6; file++){
  
    cout<<endl;
    cout<<namelist[file]<<endl;;
    sprintf(dir, "%s",namelist[file].c_str());
   
    if(!fnew1.GetDirectory(dir))
    fnew1.mkdir(dir);
    //cout<<"Btag"<<Btaggers[1]<<"_"<<flavors[1];
    //Make the plots for btag discrim
    for(int i=0; i<4; i++){
      std::stringstream sc;
      sc<<Btaggers[i];
      TCanvas* c1 = new TCanvas((sc.str()).c_str(),(sc.str()).c_str(),800,600);
      if (i<2)c1->SetLogy();

      for (int a=0; a<3; a++){
       std::stringstream sDis;
      sDis<<"Btag/"<<Btaggers[i]<<"_"<<flavors[a];
      TH1F* temp_Btag1 = (TH1F*) filelist[file]->Get((sDis.str()).c_str());
      fnew1.cd(dir);
      temp_Btag1->Write();
      float scalef=1;
     
      if (i>=2){
	scalef=temp_Btag1->Integral(0,500);
	//temp_Btag->GetXaxis()->SetRangeUser(0,6);
      }
      if (i<2){
	scalef=temp_Btag1->Integral(0,500);
	//temp_Btag->GetXaxis()->SetRangeUser(-5,30);
      }
      temp_Btag1->Scale(1/scalef);
      if (a==0){
	temp_Btag1->SetLineColor(3);
	temp_Btag1->Draw();
      }
      if (a==1){
	temp_Btag1->SetLineColor(4);
	temp_Btag1->Draw("same");
      }
      if (a==2){
	temp_Btag1->SetLineColor(2);
	temp_Btag1->Draw("same");
      }
      temp_Btag1->SetTitle((sc.str()).c_str());
      }
      TLegend *leg = new TLegend(0.6821608,0.6608392,0.9522613,0.8636364,NULL,"brNDC");
      std::stringstream sDb,sDc,sDudsg;
      sDb<<Btaggers[i]<<"_"<<flavors[0];
      sDc<<Btaggers[i]<<"_"<<flavors[1];
      sDudsg<<Btaggers[i]<<"_"<<flavors[2];
      leg->AddEntry((sDb.str()).c_str(),"MC b","lep");
      leg->AddEntry((sDc.str()).c_str(),"MC c","lep");
      leg->AddEntry((sDudsg.str()).c_str(),"MC udsg","lep");
      leg->Draw();

      fnew1.cd(dir);
      c1->Write();
    }
          
    }
    Double_t xbins[27]={0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,250,300,400,500,600,1000};
   //Double_t xbins[15]={0,20,30,40,50,60,70,80,100,120,240,380,520,660,1000};
   //making plots for btag efficiency and miss tag rate
      for(int file=0; file<6; file++){
  cout<<namelist[file]<<endl;;
    sprintf(dir, "%s",namelist[file].c_str());
   
    if(!fnew1.GetDirectory(dir))
    fnew1.mkdir(dir);
    
    //Loop for the different OP
    for(int i=0; i<7; i++){
      std::stringstream sOP1 ;
      sOP1<<"jet_pt_"<<op_name[i];
      //TCanvas* c1 = new TCanvas((sOP1.str()).c_str(),(sOP1.str()).c_str(),800,600);
      
      for (int a=0; a<3; a++){
	std::stringstream sOP2,sOP3;
	sOP2<<"Btag/jet_pt_"<<op_name[i]<<"_"<<flavors[a];
	sOP3<<"Btag/jet_eta_"<<op_name[i]<<"_"<<flavors[a];
	cout<<"Btag/jet_pt"<<op_name[i]<<"_"<<flavors[a]<<endl;
	std::stringstream sNoBtag,sNoBtagEta;
	sNoBtag<<"Btag/jet_pt_none_"<<flavors[a];
	sNoBtagEta<<"Btag/jet_eta_none_"<<flavors[a];
	TH1F* tempBtag;
	TH1F* tempNoBtag;
	TH1F *h_Btag;
	TH1F *h_NoBtag;
	
	TH1F* tempBtagEta;
	TH1F* tempNoBtagEta;
	TH1F *h_BtagEta;
	TH1F *h_NoBtagEta;

	tempBtag = (TH1F*) filelist[file]->Get((sOP2.str()).c_str());
	tempNoBtag = (TH1F*) filelist[file]->Get((sNoBtag.str()).c_str());
	tempBtagEta = (TH1F*) filelist[file]->Get((sOP3.str()).c_str());
	fnew1.cd(dir);
	
	cout<<(sNoBtagEta.str()).c_str()<<endl;
	tempNoBtagEta = (TH1F*) filelist[file]->Get((sNoBtagEta.str()).c_str());

	tempBtag->Sumw2();
	tempNoBtag->Sumw2();
	tempBtagEta->Sumw2();
	tempNoBtagEta->Sumw2();
	
		h_Btag =(TH1F*) tempBtag->Rebin(26,"h_Btag",xbins);
		h_NoBtag=(TH1F*) tempNoBtag->Rebin(26,"h_NoBtag",xbins);

		h_BtagEta =(TH1F*) tempBtagEta->Rebin(3,"h_Btag");
		h_NoBtagEta=(TH1F*) tempNoBtagEta->Rebin(3,"h_NoBtagEta");

		//h_Btag->SetName((sOP2.str()).c_str());
		//h_NoBtag->SetName((sOP2.str()).c_str());

		//h_BtagEta->SetName((sOP3.str()).c_str());
		//h_NoBtagEta->SetName((sOP3.str()).c_str());
	fnew1.cd(dir);
h_NoBtagEta->Write();
	//temp_Btag->Write();
	//temp_NoBtag->Write();
	std::stringstream seff;
	seff<<"BTagEff_"<<op_name[i]<<"_"<<flavors[a];
		std::stringstream seffEta;
	seffEta<<"BTagEffEta_"<<op_name[i]<<"_"<<flavors[a];
	//TH1F* BTagEff= new TH1F((seff.str()).c_str(),(seff.str()).c_str(),500,0,1000);
	TH1F* BTagEff;
	TH1F* BTagEffEta;
	BTagEff=(TH1F*) h_Btag->Clone();
	BTagEff->Divide(h_NoBtag);
	BTagEff->SetName((seff.str()).c_str());

	BTagEff->SetTitle((seff.str()).c_str());
	BTagEffEta=(TH1F*) h_BtagEta->Clone();
	BTagEffEta->Divide(h_NoBtagEta);
	BTagEffEta->SetName((seffEta.str()).c_str());
	BTagEffEta->SetTitle((seffEta.str()).c_str());
	fnew1.cd(dir);
	BTagEff->Write();
	BTagEffEta->Write();
	float scalef=1;

      }
      
      
      fnew1.cd(dir);
      // c1->Write();
    }
    
   }
  for(int file=0; file<6; file++){
 sprintf(dir, "%s",namelist[file].c_str());
 if(!fnew1.GetDirectory(dir))
    fnew1.mkdir(dir);
 for(float iTagger=0; iTagger<7; iTagger++)
   {
    
     for(int iFlavor=0; iFlavor<3; iFlavor++)
       {
	 std::stringstream sTagFlav_Tjetpt,sTagFlav_Tmass,sTagFlav_Tsumpt,sTagFlav_Tjetpt_none,sTagFlav_Tmass_none,sTagFlav_Tsumpt_none;
	 sTagFlav_Tjetpt<<"Btag/triplet_jet_pt_"<<op_name[iTagger]<<"_"<<flavors[iFlavor];
	 sTagFlav_Tsumpt<<"Btag/triplet_sumpt_"<<op_name[iTagger]<<"_"<<flavors[iFlavor];
	 sTagFlav_Tmass<<"Btag/triplet_mass_"<<op_name[iTagger]<<"_"<<flavors[iFlavor];
	 
	 sTagFlav_Tmass_none<<"Btag/triplet_mass_none_"<<flavors[iFlavor];
	 sTagFlav_Tsumpt_none<<"Btag/triplet_sumpt_none_"<<flavors[iFlavor];
	  sTagFlav_Tjetpt_none<<"Btag/triplet_jet_pt_none_"<<flavors[iFlavor];

	  //cout<<"debug"<<endl;
	 cout<<(sTagFlav_Tjetpt.str()).c_str()<<" "<<( sTagFlav_Tsumpt.str()).c_str()<<endl;

	 TH1F* h_tempTriplet_jetpt;
	 TH1F* h_tempTriplet_sumpt;
	 TH1F* h_tempTriplet_mass;

	 TH1F* h_tempTriplet_jetpt_none;
	 TH1F* h_tempTriplet_sumpt_none; 
	 TH1F* h_tempTriplet_mass_none; 
	  
	 TH1F* h_Triplet_jetpt;
	 TH1F* h_Triplet_sumpt;
	 TH1F* h_Triplet_mass;
	 
	 TH1F* h_Triplet_jetpt_none;
	 TH1F* h_Triplet_sumpt_none;
	 TH1F* h_Triplet_mass_none;
 
	 h_tempTriplet_jetpt = (TH1F*) filelist[file]->Get((sTagFlav_Tjetpt.str()).c_str());
	 h_tempTriplet_sumpt = (TH1F*) filelist[file]->Get(( sTagFlav_Tsumpt.str()).c_str());
	 h_tempTriplet_mass = (TH1F*) filelist[file]->Get(( sTagFlav_Tmass.str()).c_str());

	 h_tempTriplet_jetpt_none = (TH1F*) filelist[file]->Get((sTagFlav_Tjetpt_none.str()).c_str());
	 h_tempTriplet_sumpt_none = (TH1F*) filelist[file]->Get(( sTagFlav_Tsumpt_none.str()).c_str());
	 h_tempTriplet_mass_none = (TH1F*) filelist[file]->Get(( sTagFlav_Tmass_none.str()).c_str());
	  
	 h_Triplet_jetpt =  (TH1F*)h_tempTriplet_jetpt->Rebin(26,"temp_Btag",xbins);
	 h_Triplet_sumpt =  (TH1F*) h_tempTriplet_sumpt->Clone();
	 h_Triplet_mass =  (TH1F*)h_tempTriplet_mass->Clone();
	
	 h_Triplet_jetpt_none = (TH1F*) h_tempTriplet_jetpt_none->Rebin(26,"temp_Btag",xbins);
	 h_Triplet_sumpt_none = (TH1F*)  h_tempTriplet_sumpt_none->Clone();
	 h_Triplet_mass_none = (TH1F*) h_tempTriplet_mass_none->Clone();
	 //cout<<"debug"<<endl;

	 h_Triplet_jetpt->Sumw2();
	 h_Triplet_sumpt->Sumw2();
	 h_Triplet_mass->Sumw2();
	 //h_Triplet_jetpt->Rebin(20);
	 h_Triplet_sumpt->Rebin(20);
	 h_Triplet_mass->Rebin(20);

	  h_Triplet_jetpt_none->Sumw2();
	  h_Triplet_sumpt_none->Sumw2();
	  h_Triplet_mass_none->Sumw2();
	  //h_Triplet_jetpt_none->Rebin(20);
	  h_Triplet_sumpt_none->Rebin(20);
	  h_Triplet_mass_none->Rebin(20);
	  
	  std::stringstream seff_jetpt,seff_sumpt,seff_mass;
	    seff_jetpt<<"BTagEff_jetpt"<<op_name[iTagger]<<"_"<<flavors[iFlavor];
	    seff_sumpt<<"BTagEff_sumpt"<<op_name[iTagger]<<"_"<<flavors[iFlavor];
	    seff_mass<<"BTagEff_mass"<<op_name[iTagger]<<"_"<<flavors[iFlavor];
	    TH1F* BTagEff_jetpt;  TH1F* BTagEff_sumpt; TH1F* BTagEff_mass;
	    //TH1F* BTagEff= new TH1F((seff.str()).c_str(),(seff.str()).c_str(),500,0,1000);
	    BTagEff_jetpt=  (TH1F*)h_Triplet_jetpt->Clone();
	    BTagEff_jetpt->Divide(h_Triplet_jetpt_none);
	    BTagEff_jetpt->SetName((seff_jetpt.str()).c_str());
	    BTagEff_jetpt->SetTitle((seff_jetpt.str()).c_str());

	     BTagEff_sumpt=  (TH1F*)h_Triplet_sumpt->Clone();
	    BTagEff_sumpt->Divide(h_Triplet_sumpt_none);
	    BTagEff_sumpt->SetName((seff_sumpt.str()).c_str());
	    BTagEff_sumpt->SetTitle((seff_sumpt.str()).c_str());
	    
	    BTagEff_mass=  (TH1F*)h_Triplet_mass->Clone();
	    BTagEff_mass->Divide(h_Triplet_mass_none);
	    BTagEff_mass->SetName((seff_mass.str()).c_str());
	    BTagEff_mass->SetTitle((seff_mass.str()).c_str());
	   
	    fnew1.cd(dir);
	    BTagEff_jetpt->Write();
	    BTagEff_sumpt->Write();
	    BTagEff_mass->Write();

	
       }
   }
  }
    
      
      
} 


