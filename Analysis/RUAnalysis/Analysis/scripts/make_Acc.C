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
#include "TGraphErrors.h"

#include <sstream>

void make_Acc()
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
	float lumi=1;
	float TriggerS = 1;
	
	
	float Ngluino=1;
	//filelist.push_back(TFile::Open("files/mcOffSummer2012_S10_RPV_M200_113_223_btagSF_6pt35_MCmatch.root"));
	filelist.push_back(TFile::Open("../files/mcOffSummer2012_S10_RPV_M200_113_223_4th80_MCmatch.root"));
	namelist.push_back("RPV_M200_113_223");
	EvtGen.push_back(Ngluino);
Xsec.push_back(1);
	//Xsec.push_back(495);
	GaussMeanIni.push_back(200);
	lumis.push_back(lumi*TriggerS);
	
	
//	filelist.push_back(TFile::Open("files/mcOffSummer2012_S10_RPV_M350_113_223_btagSF_6pt35_MCmatch.root"));
	filelist.push_back(TFile::Open("../files/mcOffSummer2012_S10_RPV_M350_113_223_4th80_MCmatch.root"));
	namelist.push_back("RPV_M350_113_223");
	EvtGen.push_back(Ngluino);
//	Xsec.push_back(48.7);
	Xsec.push_back(1);
	GaussMeanIni.push_back(350);
	lumis.push_back(lumi*TriggerS);


//	filelist.push_back(TFile::Open("files/mcOffSummer2012_S10_RPV_M400_113_223_btagSF_6pt35_MCmatch.root"));
	filelist.push_back(TFile::Open("../files/mcOffSummer2012_S10_RPV_M400_113_223_4th80_MCmatch.root"));
	namelist.push_back("RPV_M400_113_223");
	EvtGen.push_back(Ngluino);
	//Xsec.push_back(7.9);
	Xsec.push_back(1);
	GaussMeanIni.push_back(400);
	lumis.push_back(lumi*TriggerS);
	
//	filelist.push_back(TFile::Open("files/mcOffSummer2012_S10_RPV_M1250_113_223_btagSF_6pt35_MCmatch.root"));
	filelist.push_back(TFile::Open("../files/mcOffSummer2012_S10_RPV_M1250_113_223_4th80_MCmatch.root"));
	namelist.push_back("RPV_M1250_113_223");
	EvtGen.push_back(Ngluino);
	//Xsec.push_back(0.000777);
	Xsec.push_back(1);
	GaussMeanIni.push_back(1250);
	lumis.push_back(lumi*TriggerS);
	
	
	
	filelist.push_back(TFile::Open("../files/RPV_M250_112_4th80_Oct3_NormalNoBtagSF.root"));
	namelist.push_back("RPV_M250_112");
	EvtGen.push_back(Ngluino);
	//Xsec.push_back(140);
	Xsec.push_back(1);
	GaussMeanIni.push_back(250);
	lumis.push_back(lumi*TriggerS);
	
	filelist.push_back(TFile::Open("../files/RPV_M300_112_4th80_Oct3_NormalNoBtagSF.root"));
	namelist.push_back("RPV_M300_112");
	EvtGen.push_back(Ngluino);
	//Xsec.push_back(49);
	Xsec.push_back(1);
	GaussMeanIni.push_back(300);
	lumis.push_back(lumi*TriggerS);
	
	filelist.push_back(TFile::Open("../files/RPV_M400_112_4th80_Oct3_NormalNoBtagSF.root"));
	namelist.push_back("RPV_M400_112");
	EvtGen.push_back(Ngluino);
	//Xsec.push_back(7.9);
	Xsec.push_back(1);
	GaussMeanIni.push_back(400);
	lumis.push_back(lumi*TriggerS);
	
	filelist.push_back(TFile::Open("../files/RPV_M450_112_4th80_Oct3_NormalNoBtagSF.root"));
	namelist.push_back("RPV_M450_112");
	EvtGen.push_back(Ngluino);
	//Xsec.push_back(7.9);
	Xsec.push_back(1);
	GaussMeanIni.push_back(450);
	lumis.push_back(lumi*TriggerS);
	
	filelist.push_back(TFile::Open("../files/RPV_M500_112_4th80_Oct3_NormalNoBtagSF.root"));
	namelist.push_back("RPV_M500_112");
	EvtGen.push_back(Ngluino);
	//Xsec.push_back(1.8);
	Xsec.push_back(1);
	GaussMeanIni.push_back(500);
	lumis.push_back(lumi*TriggerS);
	
	filelist.push_back(TFile::Open("../files/RPV_M750_112_4th80_Oct3_NormalNoBtagSF.root"));
	namelist.push_back("RPV_M750_112");
	EvtGen.push_back(Ngluino);
	//Xsec.push_back(0.0821);
	Xsec.push_back(1);
	GaussMeanIni.push_back(750);
	lumis.push_back(lumi*TriggerS);
	
	filelist.push_back(TFile::Open("../files/RPV_M1000_112_4th80_Oct3_NormalNoBtagSF.root"));
	namelist.push_back("RPV_M1000_112");
	EvtGen.push_back(Ngluino);
	//Xsec.push_back(0.0821);
	Xsec.push_back(1);
	GaussMeanIni.push_back(1000);
	lumis.push_back(lumi*TriggerS);
	
	
	
	filelist.push_back(TFile::Open("../files/RPV_M1500_112_4th80_Oct3_NormalNoBtagSF.root"));
	namelist.push_back("RPV_M1500_112");
	EvtGen.push_back(Ngluino);
	//Xsec.push_back(0.0821);
	Xsec.push_back(1);
	GaussMeanIni.push_back(1500);
	lumis.push_back(lumi*TriggerS);

	
	vector <float > Mass_112;
	vector <float > GausMean_112;
	vector <float > GausAmp_112;
	vector <float > GausWidth_112;
	vector <float > GausIntegral_112;
	
	vector <float > Mass_Err_112;
	vector <float > GausMean_Err_112;
	vector <float > GausAmp_Err_112;
	vector <float > GausWidth_Err_112;
	vector <float > GausIntegral_Err_112;
	
	vector <float > Mass_113_223;
	vector <float > GausMean_113_223;
	vector <float > GausAmp_113_223;
	vector <float > GausWidth_113_223;
	vector <float > GausIntegral_113_223;
	
	vector <float > Mass_Err_113_223;
	vector <float > GausMean_Err_113_223;
	vector <float > GausAmp_Err_113_223;
	vector <float > GausWidth_Err_113_223;
	vector <float > GausIntegral_Err_113_223;
	
	
	
	

	std::vector<TH2F* > SignalOptmization;
	std::vector<TH2F* > SignalOverSqrtBkg;
	std::vector<TH2F* > SignalOverSqrtSigPlusBkg;
	std::vector<TH2F* > SignalOverSigPlusBkg;
	TFile fnew1("DATA_TTJets_TriggerS_sumw2_SoSqrtB_4Pt80_6pt35_0b.root", "recreate");
	TFile fnew2("DATA_SignalPreFit_4Pt80_6pt35_0b.root", "recreate");
	
	fnew1.cd();
	fnew1.mkdir("BkgScaled");
	fnew1.mkdir("0bFits");
	for(int n=0; n<namelist.size(); n++){

		TDirectory* MC=fnew1.mkdir(namelist[n].c_str());
		fnew1.cd(namelist[n].c_str());
		MC->mkdir("0bFits");
		string opti;
		opti="SignalOverSqrtBkg_";
		SignalOverSqrtBkg.push_back(new TH2F((opti+namelist[n]).c_str(),(opti+namelist[n]).c_str(),15,0,150,25,0,250));
		
		opti="SignalOverSqrtSigPlusBkg_";
		SignalOverSqrtSigPlusBkg.push_back(new TH2F((opti+namelist[n]).c_str(),(opti+namelist[n]).c_str(),15,0,150,25,0,250));
		
		opti="SignalOverSigPlusBkg_";
		SignalOverSigPlusBkg.push_back(new TH2F((opti+namelist[n]).c_str(),(opti+namelist[n]).c_str(),15,0,150,25,0,250));

						 }
	
	char hNAME[99];
	char hNScale[99];
	
	
	
	float first=1;
	if(WhichPlot==0){	
		for (int i=0; i<1; i++){
			int iPt=60+i*10;	
			for(int k=0; k<1; k++){
				int iNjet=k+6;
				for(int j=0; j<1; j++){
					int iDiag=j*10+110;
					int b=0;				
					for(int m=0; m<filelist.size(); m++){
						
					float scaleTTbar=1/(EvtGen[m])*Xsec[m]*lumis[m];
						TF1 *LandauGausFit = new TF1("LandauGausFit","landau(0)+gaus(3)", 0, 2000);
						TF1 *P4GausFit= new TF1("P4GausFit", "[0]*pow(1-x/8000.0,[1])/pow(x/8000.0,[2]+[3]*log(x/8000.))+gaus(4)",0,2000);
					
						//Prefit determine parameters for p4
						////////////////////////////////////
						TF1 *P4PreFit= new TF1("P4PreFit", "[0]*pow(1-x/8000.0,[1])/pow(x/8000.0,[2]+[3]*log(x/8000.))",0,2000);
						TF1 *GausPreFit= new TF1("GausPreFit", "gaus",0,2000);
						
						sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_bjet%i_pt%i_diag%i_GE%ijet_MCcomb", b,iPt,b,iPt,iDiag,iNjet);
						TH1F* h_PreFitP4 = (TH1F*) filelist[m]->Get(hNAME)->Clone();
						h_PreFitP4->Scale(scaleTTbar);
					 float FitStart=h_PreFitP4->GetMaximumBin()*10-20;
					  float	FitEnd=h_PreFitP4->GetMaximumBin()*10+800;

						cout<<"FITSTART: "<<FitStart<<endl;
						h_PreFitP4->Fit(P4PreFit,"RQ","",FitStart,1800);
						h_PreFitP4->Fit(P4PreFit,"RQ","",FitStart,1800);
					
						
						fnew2.cd();
						h_PreFitP4->Write();
							
							
						sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_bjet%i_pt%i_diag%i_GE%ijet_MCmatch", b,iPt,b,iPt,iDiag,iNjet);
						TH1F* h_PreFitGaus = (TH1F*) filelist[m]->Get(hNAME)->Clone();
						h_PreFitGaus->Scale(scaleTTbar);
						h_PreFitGaus->Fit(GausPreFit,"RQ","",GaussMeanIni[m]-40,GaussMeanIni[m]+40);
						fnew2.cd();
						h_PreFitGaus->Write();
						if(P4PreFit->GetParameter(0)==0 || P4PreFit->GetParameter(1)==0 || P4PreFit->GetParameter(2)==0 || P4PreFit->GetParameter(3)==0 || 	(P4PreFit->GetChisquare()/P4PreFit->GetNDF() > 3)){
						
							P4GausFit->SetParameter(1,-5);
							P4GausFit->SetParameter(2,15);
							P4GausFit->SetParameter(3,1.2);
							P4GausFit->SetParameter(4,GausPreFit->GetParameter(0));
							P4GausFit->SetParameter(5,GausPreFit->GetParameter(1));
							//P4GausFit->SetParLimits(5,GausPreFit->GetParameter(1)-20,GausPreFit->GetParameter(1)+20);
							P4GausFit->SetParameter(6,GausPreFit->GetParameter(2));
							//P4GausFit->SetParLimits(6,GausPreFit->GetParameter(2)-10,GausPreFit->GetParameter(2)+10);
							
						}
						else{
						P4GausFit->SetParameter(0,P4PreFit->GetParameter(0));				
						P4GausFit->SetParameter(1,P4PreFit->GetParameter(1));
						P4GausFit->SetParameter(2,P4PreFit->GetParameter(2));
						P4GausFit->SetParameter(3,P4PreFit->GetParameter(3));
						P4GausFit->SetParameter(4,GausPreFit->GetParameter(0));
						P4GausFit->SetParameter(5,GausPreFit->GetParameter(1));
						//P4GausFit->SetParLimits(5,GausPreFit->GetParameter(1)-20,GausPreFit->GetParameter(1)+20);
						P4GausFit->SetParameter(6,GausPreFit->GetParameter(2));
						//P4GausFit->SetParLimits(6,GausPreFit->GetParameter(2)-10,GausPreFit->GetParameter(2)+10);
						}
						
						//////////////////////////
						
						////REAL Fitting//////
						
						sprintf(hNAME, "Triplets/bjet_0/jetpt_%i/Mjjj_bjet0_pt%i_diag%i_GE%ijet", iPt,iPt,iDiag,iNjet);
						TH1F* h_TTbarFitP4 = (TH1F*) filelist[m]->Get(hNAME)->Clone();
						
						FitStart=GausPreFit->GetParameter(1)-190;
						//h_TTbarFitP4->Scale(scaleTTbar);
						h_TTbarFitP4->Fit(P4GausFit,"RQ","",FitStart,2000);
						h_TTbarFitP4->Fit(P4GausFit,"RQ","",FitStart,2000);
						sprintf(hNAME, "P4Gaus_Mjjj_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);
						h_TTbarFitP4->SetName(hNAME);
					
					
						TF1 *TTbarGausP4 = new TF1("TTbarGausP4","gaus", 0, 2000);
						TF1 *TTbarP4 = new TF1("TTbarP4","[0]*pow(1-x/8000.0,[1])/pow(x/8000.0,[2]+[3]*log(x/8000.))", 0, 2000);
					
						TTbarP4->SetParameter(0,P4GausFit->GetParameter(0));
						TTbarP4->SetParameter(1,P4GausFit->GetParameter(1));
						TTbarP4->SetParameter(2,P4GausFit->GetParameter(2));
						TTbarP4->SetParameter(3,P4GausFit->GetParameter(3));
					
						TTbarGausP4->SetParameter(0,P4GausFit->GetParameter(4));
						TTbarGausP4->SetParameter(1,P4GausFit->GetParameter(5));
						TTbarGausP4->SetParameter(2,P4GausFit->GetParameter(6));
						
						TTbarGausP4->SetParError(0,P4GausFit->GetParError(4));
						TTbarGausP4->SetParError(1,P4GausFit->GetParError(5));
						TTbarGausP4->SetParError(2,P4GausFit->GetParError(6));
					
						TTbarGausP4->SetLineColor(6);
						sprintf(hNAME, "GaussP4_Mjjj_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);
						TTbarGausP4->SetName(hNAME);
					
					
						TTbarP4->SetLineColor(1);
						sprintf(hNAME, "P4_Mjjj_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);
						TTbarP4->SetName(hNAME);
						string bfolder;
						
						float lowint=25;
						float highint=4000;

					
						bfolder="/0bFits";	
						fnew1.cd((namelist[m]+bfolder).c_str());
						h_TTbarFitP4->Write();
						TTbarGausP4->Write();
						TTbarP4->Write();
						
						float SigP4 = TTbarGausP4->Integral(0,2000);
						cout<<"Mass: "<<GaussMeanIni[m]<<" Integral: "<<SigP4/10/100000<<" "<<sqrt(2*3.14)*TTbarGausP4->GetParameter(2)*TTbarGausP4->GetParameter(0)/10/100000<<endl;
						
						//RPV113_223
						
						if(m<4){
							Mass_113_223.push_back(GaussMeanIni[m]);
							GausAmp_113_223.push_back(TTbarGausP4->GetParameter(0));
							GausMean_113_223.push_back(TTbarGausP4->GetParameter(1));
							GausWidth_113_223.push_back(TTbarGausP4->GetParameter(2));
							GausIntegral_113_223.push_back(SigP4/10/100000);
							
							GausAmp_Err_113_223.push_back(TTbarGausP4->GetParError(0));
							GausMean_Err_113_223.push_back(TTbarGausP4->GetParError(1));
							GausWidth_Err_113_223.push_back(TTbarGausP4->GetParError(2));
							GausIntegral_Err_113_223.push_back(SigP4/10/100000);
							
						}
						//RPV112
						if(m>=4){
							Mass_112.push_back(GaussMeanIni[m]);
							GausAmp_112.push_back(TTbarGausP4->GetParameter(0));
							GausMean_112.push_back(TTbarGausP4->GetParameter(1));
							GausWidth_112.push_back(TTbarGausP4->GetParameter(2));
							GausIntegral_112.push_back(SigP4/10/100000);
							
							GausAmp_Err_112.push_back(TTbarGausP4->GetParError(0));
							GausMean_Err_112.push_back(TTbarGausP4->GetParError(1));
							GausWidth_Err_112.push_back(TTbarGausP4->GetParError(2));

							cout<<TTbarGausP4->GetParameter(0)<<" "<<TTbarGausP4->GetParError(0)<<endl;
							cout<<TTbarGausP4->GetParError(2)<<endl;
							
						}
											

						
						}//file loop					
					
						
					}//idiag
					
					
					
										
					}//injet
					
					}//ipt
					
					
				
			}//whichplot
	TGraph* g_GausMean_112 = new TGraph((int)Mass_112.size(), &Mass_112[0],&GausMean_112[0]);
	g_GausMean_112->SetName("GausMean_vs_Mass_112");
	g_GausMean_112->SetTitle("GausMean_vs_Mass_112");
	
	TGraphErrors* g_GausAmp_112 = new TGraphErrors((int)Mass_112.size(), &Mass_112[0],&GausAmp_112[0],0,&GausAmp_Err_112[0]);
	g_GausAmp_112->SetName("GausAmp_vs_Mass_112");
	g_GausAmp_112->SetTitle("GausAmp_vs_Mass_112");
	
	TGraphErrors* g_GausWidth_112 = new TGraphErrors((int)Mass_112.size(),&Mass_112[0], &GausWidth_112[0],0,&GausWidth_Err_112[0]);
	g_GausWidth_112->SetName("GausWidth_vs_Mass_112");
	g_GausWidth_112->SetTitle("GausWidth_vs_Mass_112");
	
	TGraph* g_GausIntegral_112 = new TGraph((int)Mass_112.size(),&Mass_112[0], &GausIntegral_112[0]);
	g_GausIntegral_112->SetName("GausIntegral_vs_Mass_112");
	g_GausIntegral_112->SetTitle("GausIntegral_vs_Mass_112");
	
	TGraph* g_GausMean_113_223 = new TGraph((int)Mass_113_223.size(), &Mass_113_223[0],&GausMean_113_223[0]);
	g_GausMean_113_223->SetName("GausMean_vs_Mass_113_223");
	g_GausMean_113_223->SetTitle("GausMean_vs_Mass_113_223");
	
	TGraphErrors* g_GausAmp_113_223 = new TGraphErrors((int)Mass_113_223.size(), &Mass_113_223[0],&GausAmp_113_223[0],0,&GausAmp_Err_113_223[0]);
	g_GausAmp_113_223->SetName("GausAmp_vs_Mass_113_223");
	g_GausAmp_113_223->SetTitle("GausAmp_vs_Mass_113_223");
	
	TGraphErrors* g_GausWidth_113_223 = new TGraphErrors((int)Mass_113_223.size(),&Mass_113_223[0], &GausWidth_113_223[0],0,&GausWidth_Err_113_223[0]);
	g_GausWidth_113_223->SetName("GausWidth_vs_Mass_113_223");
	g_GausWidth_113_223->SetTitle("GausWidth_vs_Mass_113_223");

	TGraph* g_GausIntegral_113_223 = new TGraph((int)Mass_113_223.size(),&Mass_113_223[0], &GausIntegral_113_223[0]);
	g_GausIntegral_113_223->SetName("GausIntegral_vs_Mass_113_223");
	g_GausIntegral_113_223->SetTitle("GausIntegral_vs_Mass_113_223");
	
	
		fnew1.cd();
	
	g_GausMean_112->Write();
	g_GausAmp_112->Write();
	g_GausWidth_112->Write();
	g_GausIntegral_112->Write();
	
	g_GausMean_113_223->Write();
	g_GausAmp_113_223->Write();
	g_GausWidth_113_223->Write();

	g_GausIntegral_113_223->Write();
		//h_test->Write();


	
	
	}

 



