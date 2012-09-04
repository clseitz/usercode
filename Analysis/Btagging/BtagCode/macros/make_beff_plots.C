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

void make_beff_plots()
{
  float lumi=189;
  vector <string > namelist;
  vector <TFile* > data;
  vector <TFile* > filelist;
  vector<float> nEvtTot;
  vector<float> McXsec;
  vector<float> DataLumi;
  vector <string > Btaggers;
  vector <string > B_OP;
  vector <string > flavors;
  vector<double > operating_point; vector<string > op_name;
  vector<string > eff_name;
  vector<string > v_eff; 
  //file 0-3 are the files to fit
  char hNAME[999];
  char dir[99];
  char picname[99];
  
  filelist.push_back(TFile::Open("debug.root"));
  /*filelist.push_back(TFile::Open("debug.root"));
 filelist.push_back(TFile::Open("debug.root"));
  filelist.push_back(TFile::Open("debug.root"));
 filelist.push_back(TFile::Open("debug.root"));
 filelist.push_back(TFile::Open("debug.root"));*/

  namelist.push_back("test3b");
  /*namelist.push_back("RPV_MC_113_223_200GeV");
    namelist.push_back("TTbarJets");
    namelist.push_back("Zprime_M1000_W100");
 namelist.push_back("Zprime_M1500_W15");
 namelist.push_back("Zprime_M500_W50");
 namelist.push_back("Zprime_M500_W5");
  */
  Btaggers.push_back("discriminator_TCHE");
  Btaggers.push_back("discriminator_TCHP");
  Btaggers.push_back("discriminator_SSVHE");
  Btaggers.push_back("discriminator_SSVHP");
  Btaggers.push_back("discriminator_JP");
  Btaggers.push_back("discriminator_CSV");

  flavors.push_back("udsg");
  flavors.push_back("c");
  flavors.push_back("b");
  
  
  op_name.push_back("TCHEL"); operating_point.push_back(1.70);
  op_name.push_back("TCHEM"); operating_point.push_back(3.30);
  op_name.push_back("TCHPM"); operating_point.push_back(1.93);
  op_name.push_back("TCHPT"); operating_point.push_back(3.41);
  op_name.push_back("SSVHEM"); operating_point.push_back(1.74);
  op_name.push_back("SSVHET"); operating_point.push_back(3.05);
  op_name.push_back("SSVHPT"); operating_point.push_back(2.00);
  op_name.push_back("JPL"); operating_point.push_back(0.275);
  op_name.push_back("JPM"); operating_point.push_back(0.545);
  op_name.push_back("JPT"); operating_point.push_back(0.790);
  op_name.push_back("CSVL"); operating_point.push_back(0.244);
  op_name.push_back("CSVM"); operating_point.push_back(0.679);
  op_name.push_back("CSVT"); operating_point.push_back(0.898);

  eff_name.push_back("TCH");
  eff_name.push_back("SSVH");
  eff_name.push_back("JP");
  eff_name.push_back("CSV");

  eff_name.push_back("TCH");
  eff_name.push_back("SSVH");
  eff_name.push_back("JP");
  eff_name.push_back("CSV");

  v_eff.push_back("tag");
  v_eff.push_back("tag");
  v_eff.push_back("tag");
  v_eff.push_back("tag");
  v_eff.push_back("mistag");
  v_eff.push_back("mistag");
  v_eff.push_back("mistag");
  v_eff.push_back("mistag");
  TFile fnew1("debug2.root", "recreate");
  
  
  
  for(int file=0; file<filelist.size(); file++){
    sprintf(dir, "%s",namelist[file].c_str());
    if(!fnew1.GetDirectory(dir))
      fnew1.mkdir(dir);
    for (int b=0; b<eff_name.size();b++){
      cout<<"can't cd into directory"<<endl;
      cout<<dir<<endl;
      fnew1.cd(dir);
      cout<<" cd into directory"<<endl;
      std::stringstream sOP1 ;
      sOP1<<"B-"<<v_eff[b] <<"_efficiency_"<<eff_name[b];
      TCanvas* c1 = new TCanvas((sOP1.str()).c_str(),(sOP1.str()).c_str(),800,600);
      TH1F* dummy = new TH1F("zmass","",1000,0,1000);
      dummy->Draw();
      dummy->GetXaxis()->SetTitle("pt of the jets");
      dummy->GetXaxis()->SetTitleOffset(1.9);
      dummy->GetYaxis()->SetTitleOffset(2.2);

      dummy->GetXaxis()->SetRangeUser(0,300);
      cout<<b<<" "<<eff_name.size()/2<<endl;
      if(b<eff_name.size()/2){
	cout<<"lower"<<endl;
	dummy->GetYaxis()->SetTitle("b-tag efficiency");
	sprintf(hNAME, "B-tag efficiency %s ",namelist[file].c_str());
	dummy->SetTitle(hNAME);
	dummy->GetYaxis()->SetRangeUser(0,1);
      }
      if(b>=eff_name.size()/2){
	cout<<"higher"<<endl;
	dummy->GetYaxis()->SetTitle("mis (udsg) b-tag efficiency");
	sprintf(hNAME, "Mis (udsg) B-tag efficiency %s ",namelist[file].c_str());
	dummy->SetTitle(hNAME);
	if(b==2)dummy->GetYaxis()->SetRangeUser(0,0.6);
	if(b==3)dummy->GetYaxis()->SetRangeUser(0,0.6);
      }
      TLegend *leg = new TLegend(0.7060302,0.7692308,0.9761307,0.972028,NULL,"brNDC");
      
      //Loop for the different OP
      for(int i=0; i<op_name.size(); i++){
	
	for (int a=0; a<flavors.size(); a++){
	  std::stringstream sOP2, sOP3;
	  sOP2<<dir<<"/BTagEff_"<<op_name[i]<<"_"<<flavors[a];
	  sOP3<<"BTagEff_"<<op_name[i]<<"_"<<flavors[a];
	  
	  cout<<(sOP2.str()).c_str()<<endl;
	  cout<<a<<" "<<i<<" "<<b<<endl;
	  TH1F* tBtag_eff = (TH1F*) filelist[file]->Get((sOP2.str()).c_str());
	  c1->cd();
	  if(a==2){
	    //selecting only bjets
	    if (i<4 && b==0){
	      tBtag_eff->Draw("same");
	      tBtag_eff->SetMarkerStyle(4);
	      tBtag_eff->SetMarkerStyle(i+4);
	      tBtag_eff->SetMarkerColor(i+1);
	      tBtag_eff->SetLineColor(i+1);
              
	      leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep"); 
	      leg->Draw();
	      
	      
	    }
	    
	    //selecting only bjets
	    if ((i>=4 && i<7) && b==1){
	      
	      tBtag_eff->Draw("same");
	      tBtag_eff->SetMarkerStyle(i);
	      tBtag_eff->SetMarkerColor(i-3);
	      tBtag_eff->SetLineColor(i-3);
	      leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep"); 
	      leg->Draw();
	      
	    }
	    if (i>=7 && i<10 && b==2){

              tBtag_eff->Draw("same");
              tBtag_eff->SetMarkerStyle(i);
              tBtag_eff->SetMarkerColor(i-3);
              tBtag_eff->SetLineColor(i-3);
              leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep");
              leg->Draw();

            }
	    if (i>=10 && i<13 && b==3){

              tBtag_eff->Draw("same");
              tBtag_eff->SetMarkerStyle(i);
              tBtag_eff->SetMarkerColor(i-3);
              tBtag_eff->SetLineColor(i-3);
              leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep");
              leg->Draw();

            }


	    
	  }
	  if(a==0){
	    
	    //selecting udsg jets
	    if (i<4 && b==4){
	      tBtag_eff->Draw("same");
	      tBtag_eff->SetMarkerStyle(4);
	      tBtag_eff->SetMarkerStyle(i+4);
	      tBtag_eff->SetMarkerColor(i+1);
	      tBtag_eff->SetLineColor(i+1);
	      
	      leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep"); 
	      leg->Draw();
	      
	      
	    }
	    
	    //selecting only bjets
	    if (i>=4 && i<7 && b==5){

              tBtag_eff->Draw("same");
              tBtag_eff->SetMarkerStyle(i);
              tBtag_eff->SetMarkerColor(i-3);
              tBtag_eff->SetLineColor(i-3);
              leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep");
              leg->Draw();

            }
            if (i>=7 && i<10 && b==6){

              tBtag_eff->Draw("same");
              tBtag_eff->SetMarkerStyle(i);
              tBtag_eff->SetMarkerColor(i-3);
              tBtag_eff->SetLineColor(i-3);
              leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep");
              leg->Draw();

            }
            if (i>=10 && i<13 && b==7){

              tBtag_eff->Draw("same");
              tBtag_eff->SetMarkerStyle(i);
              tBtag_eff->SetMarkerColor(i-3);
              tBtag_eff->SetLineColor(i-3);
              leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep");
              leg->Draw();

            }

	    cout<<"debug"<<endl;
	    
	    
	  }
	}
	
	
	
      }
      fnew1.cd(dir);
      c1->Write();
      sOP1<<dir<<".gif";
      c1->SaveAs((sOP1.str()).c_str());
     
	 
    }
    cout<<"done with the first part"<<endl;
    for (int b=0; b<eff_name.size();b++){
      fnew1.cd(dir);
      std::stringstream sOP1 ;
      sOP1<<"B-"<<v_eff[b] <<"_efficiency_eta_"<<eff_name[b];
      TCanvas* c1 = new TCanvas((sOP1.str()).c_str(),(sOP1.str()).c_str(),800,600);
      TH1F* dummy = new TH1F("zmass","",100,0,4);
      dummy->Draw();
      dummy->GetXaxis()->SetTitle("eta of the jets");
      dummy->GetXaxis()->SetTitleOffset(1.9);
      dummy->GetYaxis()->SetTitleOffset(2.2);
      cout<<b<<" "<<eff_name.size()/2<<endl;
      if(b<eff_name.size()/2){
	cout<<"lower"<<endl;
	dummy->GetYaxis()->SetTitle("b-tag efficiency");
	sprintf(hNAME, "B-tag efficiency %s ",namelist[file].c_str());
	dummy->SetTitle(hNAME);
	dummy->GetYaxis()->SetRangeUser(0,1);
      }
      if(b>=eff_name.size()/2){
	cout<<"hgiher"<<endl;
	dummy->GetYaxis()->SetTitle("mis (udsg) b-tag efficiency");
	sprintf(hNAME, "Mis (udsg) B-tag efficiency %s ",namelist[file].c_str());
	dummy->SetTitle(hNAME);
	if(b==2)dummy->GetYaxis()->SetRangeUser(0,0.6);
	if(b==3)dummy->GetYaxis()->SetRangeUser(0,0.6);
      }
      TLegend *leg = new TLegend(0.7060302,0.7692308,0.9761307,0.972028,NULL,"brNDC");
      
      //Loop for the different OP
      for(int i=0; i<op_name.size(); i++){
	
	for (int a=0; a<flavors.size(); a++){
	  std::stringstream sOP2, sOP3;
	  sOP2<<dir<<"/BTagEffEta_"<<op_name[i]<<"_"<<flavors[a];
	  sOP3<<"BTagEffEta_"<<op_name[i]<<"_"<<flavors[a];
	  
	  cout<<(sOP2.str()).c_str()<<endl;
	  TH1F* tBtag_eff = (TH1F*) filelist[file]->Get((sOP2.str()).c_str());
	  c1->cd();
	  if(a==2){
	    //selecting only bjets
	    if (i<4 && b==0){
	      tBtag_eff->Draw("same");
	      tBtag_eff->SetMarkerStyle(4);
	      tBtag_eff->SetMarkerStyle(i+4);
	      tBtag_eff->SetMarkerColor(i+1);
	      tBtag_eff->SetLineColor(i+1);
              
	      leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep"); 
	      leg->Draw();
	      
	      
	    }
	    if (i>=4 && i<7 && b==1){

              tBtag_eff->Draw("same");
              tBtag_eff->SetMarkerStyle(i);
              tBtag_eff->SetMarkerColor(i-3);
              tBtag_eff->SetLineColor(i-3);
              leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep");
              leg->Draw();

            }
            if (i>=7 && i<10 && b==2){

              tBtag_eff->Draw("same");
              tBtag_eff->SetMarkerStyle(i);
              tBtag_eff->SetMarkerColor(i-3);
              tBtag_eff->SetLineColor(i-3);
              leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep");
              leg->Draw();

            }
            if (i>=10 && i<13 && b==3){

              tBtag_eff->Draw("same");
	      tBtag_eff->SetMarkerStyle(i);
              tBtag_eff->SetMarkerColor(i-3);
              tBtag_eff->SetLineColor(i-3);
              leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep");
              leg->Draw();

            }

	    
	  }
	  if(a==0){
	    
	    //selecting udsg jets
	    if (i<4 && b==4){
	      tBtag_eff->Draw("same");
	      tBtag_eff->SetMarkerStyle(4);
	      tBtag_eff->SetMarkerStyle(i+4);
	      tBtag_eff->SetMarkerColor(i+1);
	      tBtag_eff->SetLineColor(i+1);
	      
	      leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep"); 
	      leg->Draw();
	      
	      
	    }
	    
	    if (i>=4 && i<7 && b==5){

              tBtag_eff->Draw("same");
              tBtag_eff->SetMarkerStyle(i);
              tBtag_eff->SetMarkerColor(i-3);
              tBtag_eff->SetLineColor(i-3);
              leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep");
              leg->Draw();

            }
            if (i>=7 && i<10 && b==6){

              tBtag_eff->Draw("same");
              tBtag_eff->SetMarkerStyle(i);
              tBtag_eff->SetMarkerColor(i-3);
              tBtag_eff->SetLineColor(i-3);
              leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep");
              leg->Draw();

            }
            if (i>=10 && i<13 && b==7){

              tBtag_eff->Draw("same");
              tBtag_eff->SetMarkerStyle(i);
              tBtag_eff->SetMarkerColor(i-3);
              tBtag_eff->SetLineColor(i-3);
              leg->AddEntry((sOP3.str()).c_str(),(sOP3.str()).c_str(),"lep");
              leg->Draw();

            }


	    //cout<<"debug"<<endl;
	    
	    
	  }
	}
	
	
	
      }
      fnew1.cd(dir);
      c1->Write();
      sOP1<<dir<<".gif";
      c1->SaveAs((sOP1.str()).c_str());

	 
    }




}


  for(int file=0; file<filelist.size(); file++){
    sprintf(dir, "%s",namelist[file].c_str());
    if(!fnew1.GetDirectory(dir))
      fnew1.mkdir(dir);
    for (int b=0; b<eff_name.size();b++){
      fnew1.cd(dir);
      std::stringstream sOP1a,sOP1b, sOP1c;
      
      sOP1a<<"B-"<<v_eff[b] <<"_efficiency_Triplet_mass"<<eff_name[b];
      sOP1b<<"B-"<<v_eff[b] <<"_efficiency_Triplet_sumpt"<<eff_name[b];
      sOP1c<<"B-"<<v_eff[b] <<"_efficiency_Triplet_jetpt"<<eff_name[b];
      
      TCanvas* c1a = new TCanvas((sOP1a.str()).c_str(),(sOP1a.str()).c_str(),800,600);
      TCanvas* c1b = new TCanvas((sOP1b.str()).c_str(),(sOP1b.str()).c_str(),800,600);
      TCanvas* c1c = new TCanvas((sOP1c.str()).c_str(),(sOP1c.str()).c_str(),800,600);
      
      TH1F* dummya = new TH1F("dummya","",1000,0,1000);
      TH1F* dummyb = new TH1F("dummyb","",1000,0,1000);
      TH1F* dummyc = new TH1F("dummyc","",1000,0,1000);
      c1a->cd();
      dummya->Draw();
      c1b->cd();
      dummyb->Draw();
      c1c->cd();
      dummyc->Draw();
      
      dummya->GetXaxis()->SetTitleOffset(1.9);
      dummya->GetYaxis()->SetTitleOffset(2.2); 
      dummyb->GetXaxis()->SetTitleOffset(1.9);
      dummyb->GetYaxis()->SetTitleOffset(2.2); 
      dummyc->GetXaxis()->SetTitleOffset(1.9);
      dummyc->GetYaxis()->SetTitleOffset(2.2); 
      dummya->GetXaxis()->SetTitle("3-jet invariant mass");
      dummyb->GetXaxis()->SetTitle("3-jet sumpt");
      dummyc->GetXaxis()->SetTitle("single jet pt within triplet");
      if(b<eff_name.size()/2){
	dummya->GetYaxis()->SetTitle("b-tag efficiency");
	sprintf(hNAME, "B-tag efficiency %s ",namelist[file].c_str());
	dummya->SetTitle(hNAME);
	dummya->GetYaxis()->SetRangeUser(0,1);
	dummyb->GetYaxis()->SetTitle("b-tag efficiency");
	dummyb->SetTitle(hNAME);
	dummyb->GetYaxis()->SetRangeUser(0,1);
	dummyc->GetYaxis()->SetTitle("b-tag efficiency");
	dummyc->SetTitle(hNAME);
	dummyc->GetYaxis()->SetRangeUser(0,1);
      }
      if(b>=eff_name.size()/2){
	dummya->GetYaxis()->SetTitle("mis (udsg) b-tag efficiency");
	sprintf(hNAME, "Mis (udsg) B-tag efficiency %s ",namelist[file].c_str());
	dummya->SetTitle(hNAME);
	if(b==2)dummya->GetYaxis()->SetRangeUser(0,0.6);
	if(b==3)dummya->GetYaxis()->SetRangeUser(0,0.6);
	dummyb->GetYaxis()->SetTitle("mis (udsg) b-tag efficiency");
	dummyb->SetTitle(hNAME);
	if(b==2)dummyb->GetYaxis()->SetRangeUser(0,0.6);
	if(b==3)dummyb->GetYaxis()->SetRangeUser(0,0.6);
	dummyc->GetYaxis()->SetTitle("mis (udsg) b-tag efficiency");
	dummyc->SetTitle(hNAME);
	if(b==2)dummyc->GetYaxis()->SetRangeUser(0,0.6);
	if(b==3)dummyc->GetYaxis()->SetRangeUser(0,0.6);
      }
      
      TLegend *lega = new TLegend(0.7060302,0.7692308,0.9761307,0.972028,NULL,"brNDC");
      TLegend *legb = new TLegend(0.7060302,0.7692308,0.9761307,0.972028,NULL,"brNDC");
      TLegend *legc = new TLegend(0.7060302,0.7692308,0.9761307,0.972028,NULL,"brNDC");
      
      //Loop for the different OP
      for(int i=0; i<op_name.size(); i++){
	 
	for (int a=0; a<flavors.size(); a++){
	  
	 
	  std::stringstream OPmass, OPsumpt, OPjetpt, OPmassA, OPsumptA, OPjetptA;
	  OPmass<<dir<<"/BTagEff_mass"<<op_name[i]<<"_"<<flavors[a];
	  OPsumpt<<dir<<"/BTagEff_sumpt"<<op_name[i]<<"_"<<flavors[a];
	  OPjetpt<<dir<<"/BTagEff_jetpt"<<op_name[i]<<"_"<<flavors[a];
	  
	  OPmassA<<"BTagEff_mass"<<op_name[i]<<"_"<<flavors[a];
	  OPsumptA<<"BTagEff_sumpt"<<op_name[i]<<"_"<<flavors[a];
	  OPjetptA<<"BTagEff_jetpt"<<op_name[i]<<"_"<<flavors[a];
	  
	 TH1F* tBtag_eff_mass = (TH1F*) filelist[file]->Get((OPmass.str()).c_str());
	 TH1F* tBtag_eff_sumpt = (TH1F*) filelist[file]->Get((OPsumpt.str()).c_str());
	 TH1F* tBtag_eff_jetpt = (TH1F*) filelist[file]->Get((OPjetpt.str()).c_str());
	 //cout<<"debug"<<endl;
	 if(a==2){
	   //selecting only bjets
	   if (i<4 && b==0){
	     c1a->cd();
	     tBtag_eff_mass->Draw("same");
	     tBtag_eff_mass->SetMarkerStyle(i+4);
	      //tBtag_eff_mass->SetMarkerStyle(i-3);
	     tBtag_eff_mass->SetMarkerColor(i+1);
	     tBtag_eff_mass->SetLineColor(i+1);
	     lega->AddEntry((OPmass.str()).c_str(),(OPmass.str()).c_str(),"lep"); 
	     lega->Draw();
	     
	     c1b->cd();
	     tBtag_eff_sumpt->Draw("same");
	     tBtag_eff_sumpt->SetMarkerStyle(i+4);
	     tBtag_eff_sumpt->SetMarkerStyle(i+4);
	     tBtag_eff_sumpt->SetMarkerColor(i+1);
	     tBtag_eff_sumpt->SetLineColor(i+1);
	     legb->AddEntry((OPsumptA.str()).c_str(),(OPsumptA.str()).c_str(),"lep"); 
	     legb->Draw();
	     
	     c1c->cd();
	     tBtag_eff_jetpt->Draw("same");
	     tBtag_eff_jetpt->SetMarkerStyle(i+4);
	     tBtag_eff_jetpt->SetMarkerStyle(i+4);
	     tBtag_eff_jetpt->SetMarkerColor(i+1);
	     tBtag_eff_jetpt->SetLineColor(i+1);
	     legc->AddEntry((OPjetptA.str()).c_str(),(OPjetptA.str()).c_str(),"lep"); 
	     legc->Draw();
	     
	     
	   }
	   
	   //selecting only bjets
	   if (i>=4 && i<7 && b==1){
	     c1a->cd(); 
	     tBtag_eff_mass->Draw("same");
	     tBtag_eff_mass->SetMarkerStyle(i);
	     tBtag_eff_mass->SetMarkerColor(i-3);
	     tBtag_eff_mass->SetLineColor(i-3);
	     lega->AddEntry((OPmassA.str()).c_str(),(OPmassA.str()).c_str(),"lep"); 
	     lega->Draw();
	     
	     c1b->cd();
	     tBtag_eff_sumpt->Draw("same");
	     tBtag_eff_sumpt->SetMarkerStyle(i);
	     tBtag_eff_sumpt->SetMarkerStyle(i);
	     tBtag_eff_sumpt->SetMarkerColor(i-3);
	     tBtag_eff_sumpt->SetLineColor(i-3);
	     legb->AddEntry((OPsumptA.str()).c_str(),(OPsumptA.str()).c_str(),"lep"); 
	     legb->Draw();
	     
	     c1c->cd();
	     tBtag_eff_jetpt->Draw("same");
	     tBtag_eff_jetpt->SetMarkerStyle(i);
	     tBtag_eff_jetpt->SetMarkerStyle(i);
	     tBtag_eff_jetpt->SetMarkerColor(i-3);
	     tBtag_eff_jetpt->SetLineColor(i-3);
	     legc->AddEntry((OPjetptA.str()).c_str(),(OPjetptA.str()).c_str(),"lep"); 
	     legc->Draw();
	     
	     
	   }
	   if (i>=7 && i<10 && b==2){
             c1a->cd();
             tBtag_eff_mass->Draw("same");
             tBtag_eff_mass->SetMarkerStyle(i);
             tBtag_eff_mass->SetMarkerColor(i-3);
             tBtag_eff_mass->SetLineColor(i-3);
             lega->AddEntry((OPmassA.str()).c_str(),(OPmassA.str()).c_str(),"lep");
             lega->Draw();

             c1b->cd();
             tBtag_eff_sumpt->Draw("same");
             tBtag_eff_sumpt->SetMarkerStyle(i);
             tBtag_eff_sumpt->SetMarkerStyle(i);
             tBtag_eff_sumpt->SetMarkerColor(i-3);
             tBtag_eff_sumpt->SetLineColor(i-3);
             legb->AddEntry((OPsumptA.str()).c_str(),(OPsumptA.str()).c_str(),"lep");
             legb->Draw();

             c1c->cd();
             tBtag_eff_jetpt->Draw("same");
             tBtag_eff_jetpt->SetMarkerStyle(i);
             tBtag_eff_jetpt->SetMarkerStyle(i);
             tBtag_eff_jetpt->SetMarkerColor(i-3);
             tBtag_eff_jetpt->SetLineColor(i-3);
             legc->AddEntry((OPjetptA.str()).c_str(),(OPjetptA.str()).c_str(),"lep");
             legc->Draw();


           }

	   if (i>=10 && i<13 && b==3){

             c1a->cd();
             tBtag_eff_mass->Draw("same");
             tBtag_eff_mass->SetMarkerStyle(i);
             tBtag_eff_mass->SetMarkerColor(i-3);
             tBtag_eff_mass->SetLineColor(i-3);
             lega->AddEntry((OPmassA.str()).c_str(),(OPmassA.str()).c_str(),"lep");
             lega->Draw();

             c1b->cd();
             tBtag_eff_sumpt->Draw("same");
             tBtag_eff_sumpt->SetMarkerStyle(i);
             tBtag_eff_sumpt->SetMarkerStyle(i);
             tBtag_eff_sumpt->SetMarkerColor(i-3);
             tBtag_eff_sumpt->SetLineColor(i-3);
             legb->AddEntry((OPsumptA.str()).c_str(),(OPsumptA.str()).c_str(),"lep");
             legb->Draw();

             c1c->cd();
	     tBtag_eff_jetpt->Draw("same");
             tBtag_eff_jetpt->SetMarkerStyle(i);
             tBtag_eff_jetpt->SetMarkerStyle(i);
             tBtag_eff_jetpt->SetMarkerColor(i-3);
             tBtag_eff_jetpt->SetLineColor(i-3);
             legc->AddEntry((OPjetptA.str()).c_str(),(OPjetptA.str()).c_str(),"lep");
             legc->Draw();


	   }

	 }
	 
	 if(a==0){
	    
	    //selecting udsg jets
	    if (i<4 && b==4){
	      c1a->cd();
	      tBtag_eff_mass->Draw("same");
	      tBtag_eff_mass->SetMarkerStyle(4);
	      tBtag_eff_mass->SetMarkerStyle(i+4);
	      tBtag_eff_mass->SetMarkerColor(i+1);
	      tBtag_eff_mass->SetLineColor(i+1);
		  
	      lega->AddEntry((OPmassA.str()).c_str(),(OPmassA.str()).c_str(),"lep"); 
	      lega->Draw();

	        c1b->cd();
	      tBtag_eff_sumpt->Draw("same");
	      tBtag_eff_sumpt->SetMarkerStyle(4);
	      tBtag_eff_sumpt->SetMarkerStyle(i+4);
	      tBtag_eff_sumpt->SetMarkerColor(i+1);
	      tBtag_eff_sumpt->SetLineColor(i+1);
	      legb->AddEntry((OPsumptA.str()).c_str(),(OPsumptA.str()).c_str(),"lep"); 
	      legb->Draw();

	      c1c->cd();
	      tBtag_eff_jetpt->Draw("same");
	      tBtag_eff_jetpt->SetMarkerStyle(4);
	      tBtag_eff_jetpt->SetMarkerStyle(i+4);
	      tBtag_eff_jetpt->SetMarkerColor(i+1);
	      tBtag_eff_jetpt->SetLineColor(i+1);
	      legc->AddEntry((OPjetptA.str()).c_str(),(OPjetptA.str()).c_str(),"lep"); 
	      legc->Draw();

	      
	    }
	    
	  
	    if (i>=4 && i<7 && b==5){
	      c1a->cd(); 
	      tBtag_eff_mass->Draw("same");
	      tBtag_eff_mass->SetMarkerStyle(i);
	      tBtag_eff_mass->SetMarkerColor(i-3);
	      tBtag_eff_mass->SetLineColor(i-3);
	      lega->AddEntry((OPmassA.str()).c_str(),(OPmassA.str()).c_str(),"lep"); 
	      lega->Draw();
	           
	      c1b->cd();
	      tBtag_eff_sumpt->Draw("same");
	      tBtag_eff_sumpt->SetMarkerStyle(i);
	      tBtag_eff_sumpt->SetMarkerStyle(i);
	      tBtag_eff_sumpt->SetMarkerColor(i-3);
	      tBtag_eff_sumpt->SetLineColor(i-3);
	      legb->AddEntry((OPsumptA.str()).c_str(),(OPsumptA.str()).c_str(),"lep"); 
	      legb->Draw();
	           
	      c1c->cd();
	      tBtag_eff_jetpt->Draw("same");
	      tBtag_eff_jetpt->SetMarkerStyle(i);
	      tBtag_eff_jetpt->SetMarkerStyle(i);
	      tBtag_eff_jetpt->SetMarkerColor(i-3);
	      tBtag_eff_jetpt->SetLineColor(i-3);
	      legc->AddEntry((OPjetptA.str()).c_str(),(OPjetptA.str()).c_str(),"lep"); 
	      legc->Draw();
	           
	           
	    }
	    if (i>=7 && i<10 && b==6){
	      c1a->cd();
	      tBtag_eff_mass->Draw("same");
	      tBtag_eff_mass->SetMarkerStyle(i);
	      tBtag_eff_mass->SetMarkerColor(i-3);
	      tBtag_eff_mass->SetLineColor(i-3);
	      lega->AddEntry((OPmassA.str()).c_str(),(OPmassA.str()).c_str(),"lep");
	      lega->Draw();

	      c1b->cd();
	      tBtag_eff_sumpt->Draw("same");
	      tBtag_eff_sumpt->SetMarkerStyle(i);
	      tBtag_eff_sumpt->SetMarkerStyle(i);
	      tBtag_eff_sumpt->SetMarkerColor(i-3);
	      tBtag_eff_sumpt->SetLineColor(i-3);
	      legb->AddEntry((OPsumptA.str()).c_str(),(OPsumptA.str()).c_str(),"lep");
	      legb->Draw();

	      c1c->cd();
	      tBtag_eff_jetpt->Draw("same");
	      tBtag_eff_jetpt->SetMarkerStyle(i);
	      tBtag_eff_jetpt->SetMarkerStyle(i);
	      tBtag_eff_jetpt->SetMarkerColor(i-3);
	      tBtag_eff_jetpt->SetLineColor(i-3);
	      legc->AddEntry((OPjetptA.str()).c_str(),(OPjetptA.str()).c_str(),"lep");
	      legc->Draw();


	    }
	    if (i>=10 && i<13 && b==7){

	      c1a->cd();
	      tBtag_eff_mass->Draw("same");
	      tBtag_eff_mass->SetMarkerStyle(i);
	      tBtag_eff_mass->SetMarkerColor(i-3);
	      tBtag_eff_mass->SetLineColor(i-3);
	      lega->AddEntry((OPmassA.str()).c_str(),(OPmassA.str()).c_str(),"lep");
	      lega->Draw();

	      c1b->cd();
	      tBtag_eff_sumpt->Draw("same");
	      tBtag_eff_sumpt->SetMarkerStyle(i);
	      tBtag_eff_sumpt->SetMarkerStyle(i);
	      tBtag_eff_sumpt->SetMarkerColor(i-3);
	      tBtag_eff_sumpt->SetLineColor(i-3);
	      legb->AddEntry((OPsumptA.str()).c_str(),(OPsumptA.str()).c_str(),"lep");
	      legb->Draw();

	      c1c->cd();
	      tBtag_eff_jetpt->Draw("same");
	      tBtag_eff_jetpt->SetMarkerStyle(i);
	      tBtag_eff_jetpt->SetMarkerStyle(i);
	      tBtag_eff_jetpt->SetMarkerColor(i-3);
	      tBtag_eff_jetpt->SetLineColor(i-3);
	      legc->AddEntry((OPjetptA.str()).c_str(),(OPjetptA.str()).c_str(),"lep");
	      legc->Draw();


	    }

	     }
	}}
      fnew1.cd(dir);
      sOP1a<<dir<<".gif";
      sOP1b<<dir<<".gif";
      sOP1c<<dir<<".gif";
      c1a->Write();
      c1b->Write();
      c1c->Write();
      c1a->SaveAs((sOP1a.str()).c_str());
      c1b->SaveAs((sOP1b.str()).c_str());
      c1c->SaveAs((sOP1c.str()).c_str());
 
 
    }
}
   
} 


