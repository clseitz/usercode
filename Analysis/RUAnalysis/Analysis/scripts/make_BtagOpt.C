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

void make_BtagOpt()
{
	
	//Which plots to make/cms/clseitz/ThreeJet/TLBSM/Analysis/Oct24_WBtagSF
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
	float lumi=2420;
	float TriggerS = 1;
	int nRebin=10;
	
	///////DIFFF//////
	//WBtag_1GeVBin
	//JPM_1GeVBin
	filelist.push_back(TFile::Open("/cms/clseitz/ThreeJet/TLBSM/Analysis/Oct24_WBtagSF/data2012_MultiJet_Quad50_Quad60_Di20_Json0601_2400pb_4th80_Oct24_JPM_1GeVBin.root"));
	namelist.push_back("MultiJetQuad60Di20_2400pb");
	EvtGen.push_back(1);
	Xsec.push_back(1);
	lumis.push_back(1);
	GaussMeanIni.push_back(10);

	
	float Ngluino=100000;

	/*filelist.push_back(TFile::Open("/cms/clseitz/ThreeJet/TLBSM/Analysis/Oct24_WBtagSF/RPV_M200_113_223_4th80_Oct24_JPM_1GeVBin.root"));
	namelist.push_back("RPV_M200_113_223");
	EvtGen.push_back(Ngluino);
	Xsec.push_back(686);
	GaussMeanIni.push_back(200);
	lumis.push_back(lumi*TriggerS);
	*/
	
	filelist.push_back(TFile::Open("/cms/clseitz/ThreeJet/TLBSM/Analysis/Oct24_WBtagSF/RPV_M250_113_223_4th80_Oct24_JPM_1GeVBin.root"));
	namelist.push_back("RPV_M250_113_223");
	EvtGen.push_back(Ngluino);
	Xsec.push_back(197.2);
	//Xsec.push_back(1);
	GaussMeanIni.push_back(250);
	lumis.push_back(lumi*TriggerS);
	
	filelist.push_back(TFile::Open("/cms/clseitz/ThreeJet/TLBSM/Analysis/Oct24_WBtagSF/RPV_M300_113_223_4th80_Oct24_JPM_1GeVBin.root"));
	namelist.push_back("RPV_M300_113_223");
	EvtGen.push_back(Ngluino);
	Xsec.push_back(67.7727);
	GaussMeanIni.push_back(300);
	lumis.push_back(lumi*TriggerS);
	
	
	filelist.push_back(TFile::Open("/cms/clseitz/ThreeJet/TLBSM/Analysis/Oct24_WBtagSF/RPV_M350_113_223_4th80_Oct24_JPM_1GeVBin.root"));
	namelist.push_back("RPV_M350_113_223");
	EvtGen.push_back(Ngluino);
	Xsec.push_back(26.4);
	GaussMeanIni.push_back(350);
	lumis.push_back(lumi*TriggerS);

	filelist.push_back(TFile::Open("/cms/clseitz/ThreeJet/TLBSM/Analysis/Oct24_WBtagSF/RPV_M400_113_223_4th80_Oct24_JPM_1GeVBin.root"));
	namelist.push_back("RPV_M400_113_223");
	EvtGen.push_back(Ngluino);
	Xsec.push_back(11.3);
	GaussMeanIni.push_back(400);
	lumis.push_back(lumi*TriggerS);
	
	
	filelist.push_back(TFile::Open("/cms/clseitz/ThreeJet/TLBSM/Analysis/Oct24_WBtagSF/RPV_M450_113_223_4th80_Oct24_JPM_1GeVBin.root"));
	namelist.push_back("RPV_M450_113_223");
	EvtGen.push_back(Ngluino);
	Xsec.push_back(5.2);
	GaussMeanIni.push_back(450);
	lumis.push_back(lumi*TriggerS);
	
	
	filelist.push_back(TFile::Open("/cms/clseitz/ThreeJet/TLBSM/Analysis/Oct24_WBtagSF/RPV_M500_113_223_4th80_Oct24_JPM_1GeVBin.root"));
	namelist.push_back("RPV_M500_113_223");
	EvtGen.push_back(Ngluino);
	Xsec.push_back(2.6);
	GaussMeanIni.push_back(500);
	lumis.push_back(lumi*TriggerS);
	
	
	filelist.push_back(TFile::Open("/cms/clseitz/ThreeJet/TLBSM/Analysis/Oct24_WBtagSF/RPV_M750_113_223_4th80_Oct24_JPM_1GeVBin.root"));
	namelist.push_back("RPV_M750_113_223");
	EvtGen.push_back(Ngluino);
	Xsec.push_back(0.127);
	GaussMeanIni.push_back(750);
	lumis.push_back(lumi*TriggerS);
	
	filelist.push_back(TFile::Open("/cms/clseitz/ThreeJet/TLBSM/Analysis/Oct24_WBtagSF/RPV_M1000_113_223_4th80_Oct24_JPM_1GeVBin.root"));
	namelist.push_back("RPV_M1000_113_223");
	EvtGen.push_back(Ngluino);
	Xsec.push_back(0.010005);
	GaussMeanIni.push_back(1000);
	lumis.push_back(lumi*TriggerS);
	
	filelist.push_back(TFile::Open("/cms/clseitz/ThreeJet/TLBSM/Analysis/Oct24_WBtagSF/RPV_M1250_113_223_4th80_Oct24_JPM_1GeVBin.root"));
	namelist.push_back("RPV_M1250_113_223");
	EvtGen.push_back(Ngluino);
	Xsec.push_back(0.000984752);
	GaussMeanIni.push_back(1250);
	lumis.push_back(lumi*TriggerS);
	
	filelist.push_back(TFile::Open("/cms/clseitz/ThreeJet/TLBSM/Analysis/Oct24_WBtagSF/RPV_M1500_113_223_4th80_Oct24_JPM_1GeVBin.root"));
	namelist.push_back("RPV_M1500_113_223");
	EvtGen.push_back(Ngluino);
	Xsec.push_back(0.000104);
	
	GaussMeanIni.push_back(1500);
	lumis.push_back(lumi*TriggerS);
	
	
	

	
	
	

	std::vector<TH2F* > SignalOptmization;
	std::vector<TH2F* > SignalOverSqrtBkg;
	std::vector<TH2F* > SignalOverSqrtSigPlusBkg;
	std::vector<TH2F* > SignalOverSigPlusBkg;
	TFile fnew1("DATA_RPV_Btags_6th60_Diag110_JPM_113_223_1GeVBin_TEST.root", "recreate");
	TFile fnew2("DATA_SignalPreFit_RPV_Btags_6th60_Diag110_JPM_113_223_1GeVBin_TEST.root", "recreate");
	
	fnew1.cd();
	fnew1.mkdir("BkgScaled");
	fnew1.mkdir("0bFits");
	for(int n=0; n<namelist.size(); n++){

		TDirectory* MC=fnew1.mkdir(namelist[n].c_str());
		fnew1.cd(namelist[n].c_str());
		MC->mkdir("0bFits");
		string opti;
		opti="SignalOverSqrtBkg_";
		SignalOverSqrtBkg.push_back(new TH2F((opti+namelist[n]).c_str(),(opti+namelist[n]).c_str(),7,0,7,25,0,25));
		
		opti="SignalOverSqrtSigPlusBkg_";
		SignalOverSqrtSigPlusBkg.push_back(new TH2F((opti+namelist[n]).c_str(),(opti+namelist[n]).c_str(),7,0,7,25,0,25));
		
		opti="SignalOverSigPlusBkg_";
		SignalOverSigPlusBkg.push_back(new TH2F((opti+namelist[n]).c_str(),(opti+namelist[n]).c_str(),7,0,7,25,0,25));

						 }
	
	TH1F* h_dummy = new TH1F("","",100,0,2000);
	h_dummy->Draw();
	h_dummy->GetXaxis()->SetTitle("Three Jet Mass [Gev]");
	h_dummy->GetYaxis()->SetTitle("Triplets / 10 GeV");
	h_dummy->GetYaxis()->SetTitleOffset(1.3);
	char hNAME[99];
	char hIN[99];
	char hNScale[99];
	
	TH2F* h_GluinoMass_vs_nBtags_113_223 = new TH2F("GluinoMass_vs_nBtags_113_223","GluinoMass_vs_nBtags_113_223",7,0,7,10,0,10);
	TH2F* h_GluinoMass_vs_nBtags_113_223_normalized = new TH2F("GluinoMass_vs_nBtags_113_223_normalized","GluinoMass_vs_nBtags_113_223_normalized",7,0,7,10,0,10);
	
	TH2F* h_GluinoMass_vs_nBtags_113_223_pt80 = new TH2F("GluinoMass_vs_nBtags_113_223_pt80","GluinoMass_vs_nBtags_113_223_pt80",7,0,7,10,0,10);
	TH2F* h_GluinoMass_vs_nBtags_113_223_pt80_normalized = new TH2F("GluinoMass_vs_nBtags_113_223_pt80_normalized","GluinoMass_vs_nBtags_113_223_pt80_normalized",7,0,7,10,0,10);
	
	char *masses[11] = {"200","250","300","350","400","450","500","750","1000","1250","1500"};
	
	float first=1;
	if(WhichPlot==0){	
		for (int i=0; i<3; i++){

			
			int iPt=60+i*10;	
			for(int k=0; k<5; k++){
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
				int iNjet=6;
				//k is used for the different plot options with btagging
				
				for(int j=0; j<1; j++){
					
					int iDiag=j*10+110;
					
					///////DATA Fit for >= 0 b	
					int b=k;
					//TF1 *P4DataFit= new TF1("P4PreFit", "[0]*pow(1-x/8000.0,[1])/pow(x/8000.0,[2]+[3]*log(x/8000.)+([4]*log(x/8000.)*log(x/8000.))+([5]*log(x/8000.)*log(x/8000.)*log(x/8000.0)))",0,2000);
					TF1 *P4DataFit= new TF1("P4PreFit", "[0]*pow(1-x/8000.0,[1])/pow(x/8000.0,[2]+[3]*log(x/8000.))",0,2000);
					cout<<hNAME<<endl;

					if(k==0) sprintf(hIN, "Triplets/bjet_%i/jetpt_%i/Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 0,iPt,0,0,iPt,iDiag,iNjet);
					if(k==1) sprintf(hIN, "Triplets/bjet_%i/jetpt_%i/Mjjj_bjet%i_pt%i_diag%i_GE%ijet", 1,iPt,1,iPt,iDiag,iNjet);
					if(k==2) sprintf(hIN, "Triplets/bjet_%i/jetpt_%i/Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 1,iPt,1,1,iPt,iDiag,iNjet);
					if(k==3) sprintf(hIN, "Triplets/bjet_%i/jetpt_%i/Mjjj_bjet%i_pt%i_diag%i_GE%ijet", 2,iPt,2,iPt,iDiag,iNjet);
					if(k==4) sprintf(hIN, "Triplets/bjet_%i/jetpt_%i/Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 2,iPt,1,2,iPt,iDiag,iNjet);
				
					
					cout<<hNAME<<endl;
					TH1F* h_DataFitP4 = (TH1F*) filelist[0]->Get(hIN)->Clone();
					h_DataFitP4->Rebin(nRebin);

					P4DataFit->SetParameter(0,0.2806);
					P4DataFit->SetParameter(1,33.3);
					
					P4DataFit->SetParameter(2,6.211);
					P4DataFit->SetParameter(3,0.9536);
					
					
					float FitStart=210;//h_DataFitP4->GetMaximumBin()*10-10;
					if(k==0) FitStart=190;
					h_DataFitP4->Fit(P4DataFit,"RL","",FitStart,2000);
					
					if(k==0) sprintf(hNAME, "Data_Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 0,0,iPt,iDiag,iNjet);
					if(k==1) sprintf(hNAME, "Data_Mjjj_bjet%i_pt%i_diag%i_GE%ijet", 1,iPt,iDiag,iNjet);
					if(k==2) sprintf(hNAME, "Data_Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 1,1,iPt,iDiag,iNjet);
					if(k==3) sprintf(hNAME, "Data_Mjjj_bjet%i_pt%i_diag%i_GE%ijet", 2,iPt,iDiag,iNjet);
					if(k==4) sprintf(hNAME, "Data_Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 1,2,iPt,iDiag,iNjet);

					
					fnew2.cd();
					h_DataFitP4->SetName(hNAME);
					h_DataFitP4->SetTitle(hNAME);
					h_DataFitP4->Write();
					
					cout<<hNAME<<endl;
					//sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,b,iPt,iDiag,iNjet);
				/*	if(k==0) sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,b,b,iPt,iDiag,iNjet);
					if(k==1) sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,b,iPt,iDiag,iNjet);
					if(k==2) sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 1,iPt,1,1,iPt,iDiag,iNjet);
				*/	
				
					TH1F* h_DataResidual = (TH1F*) h_DataFitP4->Clone();
					TH1F* h_DataOverFit = (TH1F*) h_DataFitP4->Clone();
					TH1F* h_DataMinusFit = (TH1F*) h_DataFitP4->Clone();
					TH1F* h_DataMinusFitOverFit = (TH1F*) h_DataFitP4->Clone();
					TH1F* h_DataMinusFitOverError = (TH1F*) h_DataFitP4->Clone();
					TAxis *xaxisData = h_DataResidual->GetXaxis();	
					for(int p=1; p<h_DataResidual->GetNbinsX(); p++){
						float binCenter = xaxisData->GetBinCenter(p);
					float fitVal = P4DataFit->Eval(binCenter);
						float oldBin=h_DataResidual->GetBinContent(p);
						float oldErr=h_DataResidual->GetBinError(p);
						if (oldErr==0) oldErr=1;

						float newBin=oldBin/fitVal;
						h_DataOverFit->SetBinContent(p,newBin);
						h_DataOverFit->SetBinError(p,(oldErr/oldBin)*newBin);
						
						newBin=oldBin-fitVal;
						h_DataMinusFit->SetBinContent(p,newBin);
						h_DataMinusFit->SetBinError(p,oldErr);

						newBin=(oldBin-fitVal)/fitVal;
						h_DataMinusFitOverFit->SetBinContent(p,newBin);
						h_DataMinusFitOverFit->SetBinError(p,oldErr*(oldBin*fitVal-oldBin+fitVal)/(fitVal*fitVal));
						//cout<<fitVal<<" "<<oldErr<<" "<<oldBin<<endl;
						newBin=(oldBin-fitVal)/oldErr;
						float newErr=1;
						if (oldBin==0)
						{
							newBin=0;
							newErr=0;
						}
						h_DataMinusFitOverError->SetBinContent(p,newBin);
						h_DataMinusFitOverError->SetBinError(p,newErr);
					}
					sprintf(hNAME, "Data_Mjjj_bjet%i_pt%i_diag%i_GE%ijet_DataOverFit", b,iPt,iDiag,iNjet);
					h_DataOverFit->SetName(hNAME);
					h_DataOverFit->SetTitle(hNAME);
					h_DataOverFit->GetXaxis()->SetRangeUser(200,2000);
					
					sprintf(hNAME, "Data_Mjjj_bjet%i_pt%i_diag%i_GE%ijet_DataMinusFit", b,iPt,iDiag,iNjet);
					h_DataMinusFit->SetName(hNAME);
					h_DataMinusFit->SetTitle(hNAME);
					h_DataMinusFit->GetXaxis()->SetRangeUser(200,2000);
					
					sprintf(hNAME, "Data_Mjjj_bjet%i_pt%i_diag%i_GE%ijet_DataMinusFitOverFit", b,iPt,iDiag,iNjet);
					h_DataMinusFitOverFit->SetName(hNAME);
					h_DataMinusFitOverFit->SetTitle(hNAME);
					h_DataMinusFitOverFit->GetXaxis()->SetRangeUser(200,2000);
					
										sprintf(hNAME, "Data_Mjjj_bjet%i_pt%i_diag%i_GE%ijet_DataMinusFitOverError", b,iPt,iDiag,iNjet);
					h_DataMinusFitOverError->SetName(hNAME);
					h_DataMinusFitOverError->SetTitle(hNAME);
					h_DataMinusFitOverError->GetXaxis()->SetRangeUser(200,2000);
					
					h_DataMinusFit->Write();
					h_DataOverFit->Write();
					h_DataMinusFitOverFit->Write();
					h_DataMinusFitOverError->Write();
					for(int m=1; m<filelist.size(); m++){
						cout<<"helo"<<endl;
					float scaleTTbar=1/(EvtGen[m])*Xsec[m]*lumis[m];
						TF1 *LandauGausFit = new TF1("LandauGausFit","landau(0)+gaus(3)", 0, 2000);
						TF1 *P4GausFit= new TF1("P4GausFit", "[0]*pow(1-x/8000.0,[1])/pow(x/8000.0,[2]+[3]*log(x/8000.))+gaus(4)",0,2000);
					
						//Prefit determine parameters for p4
						////////////////////////////////////
						TF1 *P4PreFit= new TF1("P4PreFit", "[0]*pow(1-x/8000.0,[1])/pow(x/8000.0,[2]+[3]*log(x/8000.))",0,2000);
						TF1 *GausPreFit= new TF1("GausPreFit", "gaus",0,2000);
						
						sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_bjet%i_pt%i_diag%i_GE%ijet_MCcomb", 0,iPt,0,iPt,iDiag,iNjet);
						
						TH1F* h_PreFitP4 = (TH1F*) filelist[m]->Get(hNAME)->Clone();
						h_PreFitP4->Rebin(nRebin);
						h_PreFitP4->Scale(scaleTTbar);
						/*P4PreFit->SetParameter(1,-30);
						P4PreFit->SetParameter(2,15);
						P4PreFit->SetParameter(3,5);*/
						// FitStart=h_PreFitP4->GetMaximumBin()*nRebin-20;
					float	FitEnd=h_PreFitP4->GetMaximumBin()*nRebin+800;
						
						if (m==1)
						{FitStart=GaussMeanIni[m]-102;
						    FitEnd=GaussMeanIni[m]+100;
						}
						if (m==2)
						{FitStart=GaussMeanIni[m]-115;
						    FitEnd=GaussMeanIni[m]+100;
						}
						if (m==3)
						{FitStart=GaussMeanIni[m]-100;
						    FitEnd=GaussMeanIni[m]+100;
						}
						if(m>3 && m<=7){
							FitStart=GaussMeanIni[m]-170;
							FitEnd=GaussMeanIni[m]+200;
						}
						if (m>=8){
							FitStart=GaussMeanIni[m]-450;
							FitEnd=GaussMeanIni[m]+200;
						}
						cout<<"FITSTART: "<<FitStart<<endl;
						h_PreFitP4->Fit(P4PreFit,"RQ","",FitStart,2000);
						h_PreFitP4->Fit(P4PreFit,"RQ","",FitStart,2000);
					
						
						fnew2.cd();
						h_PreFitP4->Write();
							
						
						sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_bjet%i_pt%i_diag%i_GE%ijet_MCmatch", 0,iPt,0,iPt,iDiag,iNjet);
						TH1F* h_PreFitGaus = (TH1F*) filelist[m]->Get(hNAME)->Clone();
						h_PreFitGaus->Rebin(nRebin);
						h_PreFitGaus->Scale(scaleTTbar);
						h_PreFitGaus->Fit(GausPreFit,"RQ","",GaussMeanIni[m]-50,GaussMeanIni[m]+60);
						fnew2.cd();
						h_PreFitGaus->Write();
						if(P4PreFit->GetParameter(0)==0 || P4PreFit->GetParameter(1)==0 || P4PreFit->GetParameter(2)==0 || P4PreFit->GetParameter(3)==0 || 	(P4PreFit->GetChisquare()/P4PreFit->GetNDF() > 3)){
						
							P4GausFit->SetParameter(1,-5);
							P4GausFit->SetParameter(2,15);
							P4GausFit->SetParameter(3,1.2);
							P4GausFit->SetParameter(4,GausPreFit->GetParameter(0));
							P4GausFit->SetParameter(5,GausPreFit->GetParameter(1));
							P4GausFit->SetParLimits(5,GausPreFit->GetParameter(1)-20,GausPreFit->GetParameter(1)+20);
							P4GausFit->SetParameter(6,GausPreFit->GetParameter(2));
							P4GausFit->SetParLimits(6,GausPreFit->GetParameter(2)-10,GausPreFit->GetParameter(2)+10);
							
						}
						else{
						P4GausFit->SetParameter(0,P4PreFit->GetParameter(0));				
						P4GausFit->SetParameter(1,P4PreFit->GetParameter(1));
						P4GausFit->SetParameter(2,P4PreFit->GetParameter(2));
						P4GausFit->SetParameter(3,P4PreFit->GetParameter(3));
						P4GausFit->SetParameter(4,GausPreFit->GetParameter(0));
						P4GausFit->SetParameter(5,GausPreFit->GetParameter(1));
						P4GausFit->SetParLimits(5,GausPreFit->GetParameter(1)-20,GausPreFit->GetParameter(1)+20);
						P4GausFit->SetParameter(6,GausPreFit->GetParameter(2));
						P4GausFit->SetParLimits(6,GausPreFit->GetParameter(2)-10,GausPreFit->GetParameter(2)+10);
						}
						
						//////////////////////////
						
						////REAL Fitting//////
						
						//sprintf(hNAME, "Triplets/bjet_0/jetpt_%i/Mjjj_bjet0_pt%i_diag%i_GE%ijet", iPt,iPt,iDiag,iNjet);
					
						
					/*	if(k==0) sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,b,b,iPt,iDiag,iNjet);
						if(k==1) sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,b,iPt,iDiag,iNjet);
						if(k==2) sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 1,iPt,1,1,iPt,iDiag,iNjet);*/
						
						TH1F* h_TTbarFitP4 = (TH1F*) filelist[m]->Get(hIN)->Clone();
						h_TTbarFitP4->Rebin(nRebin);
					//	FitStart=GausPreFit->GetParameter(1)-130;
						h_TTbarFitP4->Scale(scaleTTbar);
						h_TTbarFitP4->Fit(P4GausFit,"RQ","",FitStart,2000);
						h_TTbarFitP4->Fit(P4GausFit,"RQ","",FitStart,2000);
					//	sprintf(hNAME, "P4Gaus_Mjjj_bjet%i_pt%i_diag%i_GE%ijet", b,iPt,iDiag,iNjet);
						
						if(k==0) sprintf(hNAME, "P4Gaus_Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 0,0,iPt,iDiag,iNjet);
						if(k==1) sprintf(hNAME, "P4Gaus_Mjjj_bjet%i_pt%i_diag%i_GE%ijet", 1,iPt,iDiag,iNjet);
						if(k==2) sprintf(hNAME, "P4Gaus_Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 1,1,iPt,iDiag,iNjet);
						if(k==3) sprintf(hNAME, "P4Gaus_Mjjj_bjet%i_pt%i_diag%i_GE%ijet", 2,iPt,iDiag,iNjet);
						if(k==4) sprintf(hNAME, "P4Gaus_Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 1,2,iPt,iDiag,iNjet);
						
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
						//sprintf(hNAME, "GaussP4_Mjjj_bjet%i_pt%i_diag%i_GE%ijet", 0,iPt,iDiag,iNjet);
						
						if(k==0) sprintf(hNAME, "GausP4_Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 0,0,iPt,iDiag,iNjet);
						if(k==1) sprintf(hNAME, "GausP4_Mjjj_bjet%i_pt%i_diag%i_GE%ijet", 1,iPt,iDiag,iNjet);
						if(k==2) sprintf(hNAME, "GausP4_Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 1,1,iPt,iDiag,iNjet);
						if(k==3) sprintf(hNAME, "GausP4_Mjjj_bjet%i_pt%i_diag%i_GE%ijet", 2,iPt,iDiag,iNjet);
						if(k==4) sprintf(hNAME, "GausP4_Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 1,2,iPt,iDiag,iNjet);
						TTbarGausP4->SetName(hNAME);
					
					
						TTbarP4->SetLineColor(1);
						//sprintf(hNAME, "P4_Mjjj_bjet%i_pt%i_diag%i_GE%ijet", 0,iPt,iDiag,iNjet);
						if(k==0) sprintf(hNAME, "P4_Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 0,0,iPt,iDiag,iNjet);
						if(k==1) sprintf(hNAME, "P4_Mjjj_bjet%i_pt%i_diag%i_GE%ijet", 1,iPt,iDiag,iNjet);
						if(k==2) sprintf(hNAME, "P4_Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 1,1,iPt,iDiag,iNjet);
						if(k==3) sprintf(hNAME, "P4_Mjjj_bjet%i_pt%i_diag%i_GE%ijet", 2,iPt,iDiag,iNjet);
						if(k==4) sprintf(hNAME, "P4_Mjjj_btag%i_bjet%i_pt%i_diag%i_GE%ijet", 1,2,iPt,iDiag,iNjet);
						TTbarP4->SetName(hNAME);
						string bfolder;
						
						float lowint=1;
						float highint=4000;

					
						bfolder="/0bFits";	
						fnew1.cd((namelist[m]+bfolder).c_str());
						h_TTbarFitP4->Write();
						TTbarGausP4->Write();
						TTbarP4->Write();
						
						h_DataFitP4->Write();
				
						float LowIntGausP4=TTbarGausP4->GetParameter(1)-2*TTbarGausP4->GetParameter(2);
						float HighIntGausP4=TTbarGausP4->GetParameter(1)+2*TTbarGausP4->GetParameter(2);
							
						float BkgP4 = P4DataFit->Integral(LowIntGausP4,HighIntGausP4)/nRebin;
						float SigP4 = TTbarGausP4->Integral(LowIntGausP4,HighIntGausP4)/nRebin;
							
						cout<<hNAME<<endl;
							cout<<k<<" "<<iPt<<" "<<iDiag<<endl;
							cout<<"P4 ------------"<<endl;
							cout<<"P4: "<<BkgP4<<" "<<SigP4<<"      "<<SigP4/(SigP4+BkgP4)<<"  GaussMean: "<<TTbarGausP4->GetParameter(1)<<" IntRange: "<<LowIntGausP4<<" "<<HighIntGausP4<<endl;
							cout<<"SigP4/(SigP4+BkgP4): "<<SigP4/(SigP4+BkgP4)<<endl;
							cout<<"SigP4/sqrt(SigP4+BkgP4): "<<SigP4/sqrt(SigP4+BkgP4)<<endl;
							cout<<"SigP4/sqrt(BkgP4): "<<SigP4/sqrt(BkgP4)<<endl;
		
							//SignalOptmization[m]->SetBinContent(iPt/10+1,iDiag/10+1,SigP4/sqrt(SigP4+BkgP4));
						
						SignalOverSqrtBkg[m]->SetBinContent(k+2,iPt/10+1,SigP4/sqrt(BkgP4));
						SignalOverSqrtSigPlusBkg[m]->SetBinContent(k+2,iPt/10+1,SigP4/sqrt(SigP4+BkgP4));
						SignalOverSigPlusBkg[m]->SetBinContent(k+2,iPt/10+1,SigP4/(SigP4+BkgP4));
						first=1;
						//if (i==0 && j==0) first=SigP4/sqrt(SigP4+BkgP4);
						//if(m<=4) h_GluinoMass_vs_nBtags_113_223->SetBinContent(iPt/10+1,GaussMeanIni[m]/50+1,SigP4/sqrt(SigP4+BkgP4)/first);
						//if(m>4) h_GluinoMass_vs_nBtags_113_223->SetBinContent(iPt/10+1,GaussMeanIni[m]/50+1,SigP4/sqrt(SigP4+BkgP4)/first);

						
						
							Mass_113_223.push_back(GaussMeanIni[m]);
							GausAmp_113_223.push_back(TTbarGausP4->GetParameter(0));
							GausMean_113_223.push_back(TTbarGausP4->GetParameter(1));
							GausWidth_113_223.push_back(TTbarGausP4->GetParameter(2));
							GausIntegral_113_223.push_back(SigP4/nRebin);
							
							GausAmp_Err_113_223.push_back(TTbarGausP4->GetParError(0));
							GausMean_Err_113_223.push_back(TTbarGausP4->GetParError(1));
							GausWidth_Err_113_223.push_back(TTbarGausP4->GetParError(2));
							GausIntegral_Err_113_223.push_back(SigP4/nRebin);
							cout<<"!!!!!!!!!!!!!!!! "<<TTbarGausP4->GetParameter(0)<<" "<<TTbarGausP4->GetParError(0)<<endl;
							cout<<"!!!!!!!!!!!!!!!! "<<TTbarGausP4->GetParameter(2)<<" "<<TTbarGausP4->GetParError(2)<<endl;
						
						}//file loop					
					
					
					if(k==0) sprintf(hNAME,"geq0_Event", 0,0,iPt,iDiag,iNjet);
					if(k==1) sprintf(hNAME,"geq1_Event", 1,iPt,iDiag,iNjet);
					if(k==2) sprintf(hNAME,"geq1_Triplet", 1,1,iPt,iDiag,iNjet);
					if(k==3) sprintf(hNAME,"geq2_Event", 2,iPt,iDiag,iNjet);
					if(k==4) sprintf(hNAME,"geq2_Event_geq1_Triplet", 1,2,iPt,iDiag,iNjet);
					
					h_GluinoMass_vs_nBtags_113_223_pt80->GetXaxis()->SetBinLabel(2,">= 0 b Event");
					h_GluinoMass_vs_nBtags_113_223_pt80->GetXaxis()->SetBinLabel(3,">= 1 b Event");
					h_GluinoMass_vs_nBtags_113_223_pt80->GetXaxis()->SetBinLabel(4,">= 1 b Triplet");
					h_GluinoMass_vs_nBtags_113_223_pt80->GetXaxis()->SetBinLabel(5,">= 2 b Event");
					h_GluinoMass_vs_nBtags_113_223_pt80->GetXaxis()->SetBinLabel(6,"& >=1 b Triplet");
					
					
					TGraphErrors* g_GausMean_113_223 = new TGraphErrors((int)Mass_113_223.size(), &Mass_113_223[0],&GausMean_113_223[0],0,&GausMean_Err_113_223[0]);
					g_GausMean_113_223->SetName(("GausMean_vs_Mass_113_223_"+ to_string(iPt)+"_"+hNAME).c_str());
					g_GausMean_113_223->SetTitle(("GausMean_vs_Mass_113_223_"+ to_string(iPt)+"_"+hNAME).c_str());
					
					TGraphErrors* g_GausAmp_113_223 = new TGraphErrors((int)Mass_113_223.size(), &Mass_113_223[0],&GausAmp_113_223[0],0,&GausAmp_Err_113_223[0]);
					g_GausAmp_113_223->SetName(("GausAmp_vs_Mass_113_223_"+ to_string(iPt)+"_"+hNAME).c_str());
					g_GausAmp_113_223->SetTitle(("GausAmp_vs_Mass_113_223_"+ to_string(iPt)+"_"+hNAME).c_str());
					
					TGraphErrors* g_GausWidth_113_223 = new TGraphErrors((int)Mass_113_223.size(),&Mass_113_223[0], &GausWidth_113_223[0],0,&GausWidth_Err_113_223[0]);
					g_GausWidth_113_223->SetName(("GausWidth_vs_Mass_113_223_"+ to_string(iPt)+"_"+hNAME).c_str());
					g_GausWidth_113_223->SetTitle(("GausWidth_vs_Mass_113_223_"+ to_string(iPt)+"_"+hNAME).c_str());
					
					TGraph* g_GausIntegral_113_223 = new TGraph((int)Mass_113_223.size(),&Mass_113_223[0], &GausIntegral_113_223[0]);
					g_GausIntegral_113_223->SetName(("GausIntegral_vs_Mass_113_223_"+ to_string(iPt)+"_"+hNAME).c_str());
					g_GausIntegral_113_223->SetTitle(("GausIntegral_vs_Mass_113_223_"+ to_string(iPt)+"_"+hNAME).c_str());
					
					
					fnew1.cd();
					
					
					g_GausMean_113_223->Write();
					g_GausAmp_113_223->Write();
					g_GausWidth_113_223->Write();
					
					g_GausIntegral_113_223->Write();	
					}//idiag
					
				
										
					}//injet
			
			
					
					}//ipt
					
					
				
			}//whichplot
	
	
		
		
		fnew1.cd();
		//h_test->Write();


	
	
	for(int n=1; n<namelist.size(); n++){

		
		SignalOverSqrtBkg[n]->Write();
		SignalOverSqrtSigPlusBkg[n]->Write();
		SignalOverSigPlusBkg[n]->Write();
		float sum=0;
		float sum80=0;
		float numSum=0;


			for (int binBtag=2; binBtag<7; binBtag++){
				
			sum=sum+SignalOverSqrtSigPlusBkg[n]->GetBinContent(binBtag,7);
			sum80=sum80+SignalOverSqrtSigPlusBkg[n]->GetBinContent(binBtag,9);

			numSum++;
			}
			float average=sum/numSum;
		float average80=sum80/numSum;
			for (int binBtag=2; binBtag<7; binBtag++){
				
				h_GluinoMass_vs_nBtags_113_223_normalized->SetBinContent(binBtag,n,SignalOverSqrtSigPlusBkg[n]->GetBinContent(binBtag,7)/average);
				h_GluinoMass_vs_nBtags_113_223->SetBinContent(binBtag,n,SignalOverSqrtSigPlusBkg[n]->GetBinContent(binBtag,7));
				
				h_GluinoMass_vs_nBtags_113_223_pt80_normalized->SetBinContent(binBtag,n,SignalOverSqrtSigPlusBkg[n]->GetBinContent(binBtag,9)/average);
				h_GluinoMass_vs_nBtags_113_223_pt80->SetBinContent(binBtag,n,SignalOverSqrtSigPlusBkg[n]->GetBinContent(binBtag,9));
				
			}
			sprintf(AxisLabel, "Mass%4.0f", GaussMeanIni[n]);
		
		h_GluinoMass_vs_nBtags_113_223->GetYaxis()->SetBinLabel(n,AxisLabel);
		h_GluinoMass_vs_nBtags_113_223->SetMarkerSize(2);
		h_GluinoMass_vs_nBtags_113_223_normalized->GetYaxis()->SetBinLabel(n,AxisLabel);
		h_GluinoMass_vs_nBtags_113_223_normalized->SetMarkerSize(2);
		cout<<"sum : " <<sum<<" average: "<<sum/numSum<<endl;
		
		h_GluinoMass_vs_nBtags_113_223->GetXaxis()->SetBinLabel(2,">= 0 b Event");
		h_GluinoMass_vs_nBtags_113_223->GetXaxis()->SetBinLabel(3,">= 1 b Event");
		h_GluinoMass_vs_nBtags_113_223->GetXaxis()->SetBinLabel(4,">= 1 b Triplet");
		h_GluinoMass_vs_nBtags_113_223->GetXaxis()->SetBinLabel(5,">= 2 b Event");
		h_GluinoMass_vs_nBtags_113_223->GetXaxis()->SetBinLabel(6,"& >=1 b Triplet");
		
		h_GluinoMass_vs_nBtags_113_223_normalized->GetXaxis()->SetBinLabel(2,">= 0 b Event");
		h_GluinoMass_vs_nBtags_113_223_normalized->GetXaxis()->SetBinLabel(3,">= 1 b Event");
		h_GluinoMass_vs_nBtags_113_223_normalized->GetXaxis()->SetBinLabel(4,">= 1 b Triplet");
		h_GluinoMass_vs_nBtags_113_223_normalized->GetXaxis()->SetBinLabel(5,">= 2 b Event");
		h_GluinoMass_vs_nBtags_113_223_normalized->GetXaxis()->SetBinLabel(6,"& >=1 b Triplet");
		
		////////80/////
		h_GluinoMass_vs_nBtags_113_223_pt80->GetYaxis()->SetBinLabel(n,AxisLabel);
		h_GluinoMass_vs_nBtags_113_223_pt80->SetMarkerSize(2);
		h_GluinoMass_vs_nBtags_113_223_pt80_normalized->GetYaxis()->SetBinLabel(n,AxisLabel);
		h_GluinoMass_vs_nBtags_113_223_pt80_normalized->SetMarkerSize(2);
		cout<<"sum : " <<sum<<" average: "<<sum/numSum<<endl;
		
		h_GluinoMass_vs_nBtags_113_223_pt80->GetXaxis()->SetBinLabel(2,">= 0 b Event");
		h_GluinoMass_vs_nBtags_113_223_pt80->GetXaxis()->SetBinLabel(3,">= 1 b Event");
		h_GluinoMass_vs_nBtags_113_223_pt80->GetXaxis()->SetBinLabel(4,">= 1 b Triplet");
		h_GluinoMass_vs_nBtags_113_223_pt80->GetXaxis()->SetBinLabel(5,">= 2 b Event");
		h_GluinoMass_vs_nBtags_113_223_pt80->GetXaxis()->SetBinLabel(6,"& >=1 b Triplet");
		
		h_GluinoMass_vs_nBtags_113_223_pt80_normalized->GetXaxis()->SetBinLabel(2,">= 0 b Event");
		h_GluinoMass_vs_nBtags_113_223_pt80_normalized->GetXaxis()->SetBinLabel(3,">= 1 b Event");
		h_GluinoMass_vs_nBtags_113_223_pt80_normalized->GetXaxis()->SetBinLabel(4,">= 1 b Triplet");
		h_GluinoMass_vs_nBtags_113_223_pt80_normalized->GetXaxis()->SetBinLabel(5,">= 2 b Event");
		h_GluinoMass_vs_nBtags_113_223_pt80_normalized->GetXaxis()->SetBinLabel(6,"& >= 1 b Triplet");
		
		
		
	}
	h_GluinoMass_vs_nBtags_113_223_normalized->GetYaxis()->SetRangeUser(0,4);
	h_GluinoMass_vs_nBtags_113_223->GetYaxis()->SetRangeUser(0,4);
	
	h_GluinoMass_vs_nBtags_113_223_normalized->Write();
	h_GluinoMass_vs_nBtags_113_223->Write();
	

	h_GluinoMass_vs_nBtags_113_223_pt80_normalized->GetYaxis()->SetRangeUser(5,10);
	h_GluinoMass_vs_nBtags_113_223_pt80->GetYaxis()->SetRangeUser(5,10);
	
	h_GluinoMass_vs_nBtags_113_223_pt80_normalized->Write();
	h_GluinoMass_vs_nBtags_113_223_pt80->Write();
}

 



