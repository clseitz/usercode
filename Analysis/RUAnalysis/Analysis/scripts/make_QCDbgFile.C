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
#include "THStack.h"
#include "math.h"
#include "TF1.h"
#include "TLatex.h"

void make_QCDbgFile()
{
	
	//Which plots to make
	int WhichPlot=2; //0 = normal all backgrounds+error bars and data, 1= include W' on top of the background for W' mass
	//define input variables
	vector <string > namelist;
	vector <string > VarList;
	vector <TFile* > data;
	vector <TFile* > filelist;
	vector <float > EvtGen;
	vector <float > Xsec;

	vector<float> nEvtTot;
	vector<float> McXsec;
	vector<float> lumis;
	vector<float> DataLumi;
	vector <TH1F* > v_Asym;
	char dir[99];
	char dirout[99];
	float upRange=1100;
	float lumi=2420.0;
	float QCDk=1.28;
	
	/*float lumi=1;
	float QCDk=1;
	*/
	
	//QCD samples for geqB
	filelist.push_back(TFile::Open("files/mc2012_QCD_HT250-500_Summer12_52x_4th80_Sep25.root"));
	namelist.push_back("QCD_HT250-500");
	EvtGen.push_back(27057349);
	Xsec.push_back(276000.0);
	lumis.push_back(lumi*QCDk);
	filelist.push_back(TFile::Open("files/mc2012_QCD_HT500-1000_Summer12_52x_4th80_Sep25.root"));
	namelist.push_back("QCD_HT500-1000");
	EvtGen.push_back(31302905);
	Xsec.push_back(8426);
	lumis.push_back(lumi*QCDk);
	filelist.push_back(TFile::Open("files/mc2012_QCD_HT1000-Inf_Summer12_52x_4th80_Sep25.root"));
	namelist.push_back("QCD_HT1000");
	EvtGen.push_back(13879218);
	Xsec.push_back(204);
	lumis.push_back(lumi*QCDk);	
	TFile fnew1("mc2012_QCD_HT250-Inf_Summer12_8TeV_4pt80_6th35_geqB_RelXsec_2p4fb_k1p28_Sep25.root", "recreate");
	  //TFile fnew1("test5.root", "recreate");
	
	/*		
	//QCD samples for geqB
	filelist.push_back(TFile::Open("mc2012_QCD_HT250-500_Summer12_8TeV_4pt80_6pt60_exactB_Aug15.root"));
	namelist.push_back("QCD_HT250-500");
	EvtGen.push_back(27057349);
	Xsec.push_back(276000.0);
	lumis.push_back(lumi*QCDk);
	filelist.push_back(TFile::Open("mc2012_QCD_HT500-1000_Summer12_8TeV_4pt80_6pt60_exactB_Aug15.root"));
	namelist.push_back("QCD_HT500-1000");
	EvtGen.push_back(31302905);
	Xsec.push_back(8426);
	lumis.push_back(lumi*QCDk);
	filelist.push_back(TFile::Open("mc2012_QCD_HT1000-Inf_Summer12_8TeV_4pt80_6pt60_exactB_Aug15.root"));
	namelist.push_back("QCD_HT1000");
	EvtGen.push_back(13879218);
	Xsec.push_back(204);
	lumis.push_back(lumi*QCDk);	
	TFile fnew1("mc2012_QCD_HT250-Inf_Summer12_8TeV_4pt80_6pt60_exactB_RelXsec_2p4fb_k1p16_Aug15.root", "recreate");
	*/
  
    vector <string > plotlist;
	 vector <string > plotnames;
	vector <string > YaxisLabel;
	vector <string > XaxisLabel;
	char hNAME[99];
	char FOLDER[100];

if(WhichPlot==2){	
	TDirectory* triplets=fnew1.mkdir("Triplets");
	fnew1.cd("Triplets");

	for(int b=0; b<5; b++){
	  sprintf(FOLDER, "bjet_%i", b);
		TDirectory* now=triplets->mkdir(FOLDER);
		triplets->cd(FOLDER);

		for (int i=0; i<7; i++){
			int iPt=30+i*10;
			sprintf(FOLDER, "jetpt_%i", iPt);
			now->mkdir(FOLDER);
			now->cd(FOLDER);
			
			for(int k=0; k<3; k++){
				int iNjet=k+6;
				for(int j=0; j<20; j++){
					
					int iDiag=j*10+40;
					//int iDiag=j*10+160;

					sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,b,iPt,iDiag,iNjet);
					cout<<hNAME<<endl;
					/*plotlist.push_back(hNAME);
					sprintf(hNAME, "Mjjj_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);*/
					//					cout<<hNAME<<endl;
					plotnames.push_back(hNAME);
					 vector <TH1F* > histos;
					//loop to read in all the plots
					for(int file=0; file<filelist.size(); file++){
						sprintf(dir, namelist[file].c_str());
						//if(i==0 && k==0 && j==0) histos.push_back((TH1F*) filelist[file]->Get("Triplets/nBJet35_EvtSel"));
						//else 
						  histos.push_back((TH1F*) filelist[file]->Get(hNAME));
						
						//scale the histograms to their cross sections Nevt=xsec*BR*Nevt/Npass*Lumi
						//	float scaleF = Xsec[file]*lumis[file]/EvtGen[file];
						float scaleF=1;
						if(histos[file]->GetEntries()!=0)scaleF = 1/EvtGen[file]*Xsec[file]*lumis[file];
						else scaleF = 1;
						
						cout<<namelist[file]<<" before "<<histos[file]->Integral(0,5000)<<endl;
						histos[file]->Scale(scaleF);
						cout<<namelist[file]<<" after "<<histos[file]->Integral(0,5000)<<endl;
						//histos[file]->Rebin(2);
						
						
					}	
					TH1F* h_QCD_HT250_500 = (TH1F*) histos[0]->Clone();
					TH1F* h_QCD_HT500_1000 = (TH1F*) histos[1]->Clone();
					TH1F* h_QCD_HT1000 = (TH1F*) histos[2]->Clone();
					
					THStack* h_QCD_HTALL = new THStack("h_QCD_HTALL","test stacked histograms");
					
					
					h_QCD_HTALL->Add(h_QCD_HT500_1000);
					h_QCD_HTALL->Add(h_QCD_HT1000);
					h_QCD_HTALL->Add(h_QCD_HT250_500);
					
					TList * mylist = (TList*) h_QCD_HTALL->GetHists();
					TIter next(mylist);
					TH1 *h_data_div_QCD  = (TH1*) mylist -> First() ->Clone();
					h_data_div_QCD -> SetLineColor(kBlack);
					h_data_div_QCD -> SetFillStyle(0);
					TObject *obj;
					while ((obj = next()))
					{
						// cout<<obj->GetName()<<endl;
						//skip first object since it's used by creating the histogram                               
						if(obj == mylist->First()) continue;
						h_data_div_QCD -> Add((TH1*)obj);
					}
					
					//if (i==0 && k==0 && j==0) sprintf(hNAME, "nBJet35_EvtSel");
					//else 
					sprintf(hNAME, "Mjjj_bjet%i_pt%i_diag%i_GE%ijet",b,iPt,iDiag,iNjet);

					
					
					h_data_div_QCD->SetFillColor(5);
					h_data_div_QCD->SetName(hNAME);
					h_data_div_QCD->SetTitle(hNAME);
					/*if (i==0 && k==0 && j==0)
					  {
					    fnew1.cd();
					    fnew1.cd("Triplets");
					    h_data_div_QCD->Write();
					    }*/
					h_data_div_QCD->Write();
					
					
					
				}
			}
		}
	}
}
		//now for electrons and muosn specific
	
		
  	
  
}
 


