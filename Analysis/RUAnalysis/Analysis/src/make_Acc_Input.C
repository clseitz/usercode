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
template <class T>
inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}
void make_Acc_Input(string filename = "RPV112")
{
	
	TFile fnew1(("Acc_"+filename+"_Sph4.root").c_str(), "recreate");
	int nRebin=10;
	
	
	std::vector<vector<string> > table;
	// Load table from file                                                                                              
	std::ifstream file((filename+".txt").c_str());
	while (file){
		std::string line;
		std::getline(file, line);
		std::istringstream is(line);
		std::vector<string> row;
		while (is){
			string data;
			is >> data;
			//cout<<data;
			row.push_back(data);
		}
		table.push_back(row);
	}
	
	cout<<table.size()<<endl;
	//cout<<table[0][0]<<" "<<table[0][1]<<" "<<table[0][2]<<" "<<table[0][3]<<" "<<table[0][4]<<endl;
	vector <float > mass;
	vector <string > files;
	vector <string > model;
	vector <float > nEvent;
	vector <float > xsec;
	vector <string > prefitfiles;
	
	for (unsigned m=0; m<table.size()-1;m++){
		//cout<<m<<endl;
		
		// double temp = ::atof(table[m][0].c_str());
		//cout<<temp<<endl;
		mass.push_back(::atof(table[m][0].c_str()));
		model.push_back(table[m][1]);
		files.push_back(table[m][2]);
		nEvent.push_back(::atof(table[m][3].c_str()));
		xsec.push_back(::atof(table[m][4].c_str()));
		prefitfiles.push_back(table[m][5]);
		//cout<<table[m][0]<<" "<<table[m][1]<<" "<<table[m][2]<<" "<<table[m][3]<<" "<<table[m][4]<<endl;
		
	}
	cout<<mass.size()<<endl;
	for(int pT6V=60;pT6V<=110; pT6V=pT6V+50){
	for (unsigned int k=0; k<mass.size();k++){
	cout<<mass[k]<<" "<<model[k]<<" "<<files[k]<<" "<<nEvent[k]<<" "<<xsec[k]<<endl;
	}
	vector <float > Mass;
	vector <float > GausMean;
	vector <float > GausAmp;
	vector <float > GausWidth;
	vector <float > GausIntegral;
	vector <float > FullIntegral;
	
	vector <float > Mass_Err;
	vector <float > GausMean_Err;
	vector <float > GausAmp_Err;
	vector <float > GausWidth_Err;
	vector <float > GausIntegral_Err;
	vector <float > FullIntegral_Err;
	
	string nameIN, name, namePre;
	string flavor=model[0];
		float MassStart=200;
		float MassEnd=750;
		if(pT6V> 60){
			MassStart=400;
			MassEnd=1500;
		}
			
	for(unsigned int m=0; m<mass.size(); m++){
		if(mass[m] >= MassStart && mass[m]<= MassEnd){
			TFile* InFile = TFile::Open(files[m].c_str());
			TFile* PreInFile = TFile::Open(prefitfiles[m].c_str());
		
		if(model[m]=="112"){
			nameIN="Triplets/bjet_0/jetpt_"+to_string(pT6V)+"/Mjjj_Sph4_btag0_bjet0_pt"+to_string(pT6V)+"_diag110_GE6jet";
			namePre="Triplets/bjet_0/jetpt_"+to_string(pT6V)+"/Mjjj_bjet0_pt"+to_string(pT6V)+"_diag110_GE6jet";
		}
		if(model[m]=="113_223"){
			if (pT6V > 60)
			  nameIN="Triplets/bjet_1/jetpt_"+to_string(pT6V)+"/Mjjj_Sph4_btag1_bjet1_pt"+to_string(pT6V)+"_diag110_GE6jet";
			else nameIN="Triplets/bjet_1/jetpt_"+to_string(pT6V)+"/Mjjj_btag1_bjet1_pt"+to_string(pT6V)+"_diag110_GE6jet";
			namePre="Triplets/bjet_1/jetpt_"+to_string(pT6V)+"/Mjjj_bjet1_pt"+to_string(pT6V)+"_diag110_GE6jet";
		}
			
				if(model[m]=="Stealth"){
				nameIN="Triplets/bjet_1/jetpt_"+to_string(pT6V)+"/Mjjj_btag1_bjet1_pt"+to_string(pT6V)+"_diag110_GE6jet";
				namePre="Triplets/bjet_1/jetpt_"+to_string(pT6V)+"/Mjjj_bjet1_pt"+to_string(pT6V)+"_diag110_GE6jet";
				name="Mjjj_btag1_bjet1_pt"+to_string(pT6V)+"_diag110_GE6jet";
			}
		float scaleMC=1;
		
		TF1 *P4GausFit= new TF1("P4GausFit", "[0]*pow(1-x/8000.0,[1])/pow(x/8000.0,[2]+[3]*log(x/8000.))+gaus(4)",0,2000);
		
		//Prefit determine parameters for p4
		////////////////////////////////////
		TF1 *P4PreFit= new TF1("P4PreFit", "[0]*pow(1-x/8000.0,[1])/pow(x/8000.0,[2]+[3]*log(x/8000.))",0,2000);
		TF1 *GausPreFit= new TF1("GausPreFit", "gaus",0,2000);
		cout<<(namePre+"_MCcomb").c_str()<<endl;
		
		TH1F* h_PreFitP4 = (TH1F*) PreInFile->Get((namePre+"_MCcomb").c_str())->Clone();
		h_PreFitP4->Scale(scaleMC);

		float FitStart=h_PreFitP4->GetMaximumBin()*nRebin-50;
		float	FitEnd=h_PreFitP4->GetMaximumBin()*nRebin+800;
		if ((int)mass[m] == 400) // Tweak to allow fit to work for JEC down
			FitEnd = 1500;

		cout<<"FITSTART: "<<FitStart<<endl;
		P4PreFit->SetParameter(1,20);
		P4PreFit->SetParameter(1,8);
		P4PreFit->SetParameter(1,2);
		h_PreFitP4->Fit(P4PreFit,"RQ","",FitStart,FitEnd);
		h_PreFitP4->Fit(P4PreFit,"RQ","",FitStart,FitEnd);
		h_PreFitP4->SetName(("P4Pre"+to_string(mass[m])+"_"+to_string(pT6V)).c_str());
		fnew1.cd();
		h_PreFitP4->Write();
		cout<<"here"<<endl;
		TH1F* h_PreFitGaus = (TH1F*) PreInFile->Get((namePre+"_MCmatch").c_str())->Clone();
		h_PreFitGaus->Scale(scaleMC);
		
		if(m<7)	h_PreFitGaus->Fit(GausPreFit,"RQ","",mass[m]-45,mass[m]+45);
		if(m>=7)	h_PreFitGaus->Fit(GausPreFit,"RQ","",mass[m]-80,mass[m]+80);
		h_PreFitGaus->SetName(("GausPre"+to_string(mass[m])+"_"+to_string(pT6V)).c_str());
		fnew1.cd();
		h_PreFitGaus->Write();
		if(P4PreFit->GetParameter(0)==0 || P4PreFit->GetParameter(1)==0 || P4PreFit->GetParameter(2)==0 || P4PreFit->GetParameter(3)==0 || 	(P4PreFit->GetChisquare()/P4PreFit->GetNDF() > 3)){
			P4GausFit->SetParameter(1,-5);
			P4GausFit->SetParameter(2,15);
			P4GausFit->SetParameter(3,1.2);
			P4GausFit->SetParameter(4,GausPreFit->GetParameter(0));
			//P4GausFit->SetParameter(5,GausPreFit->GetParameter(1));
			//P4GausFit->SetParLimits(5,GausPreFit->GetParameter(1)-40,GausPreFit->GetParameter(1)+40);
			P4GausFit->SetParameter(5,mass[m]);
			P4GausFit->SetParLimits(5,mass[m]-60,mass[m]+20);
			P4GausFit->SetParameter(6,GausPreFit->GetParameter(2));
			P4GausFit->SetParLimits(6,GausPreFit->GetParameter(2)-20,GausPreFit->GetParameter(2)+20);
		}	
		else{
			P4GausFit->SetParameter(0,P4PreFit->GetParameter(0));				
			P4GausFit->SetParameter(1,P4PreFit->GetParameter(1));
			P4GausFit->SetParameter(2,P4PreFit->GetParameter(2));
			P4GausFit->SetParameter(3,P4PreFit->GetParameter(3));
			P4GausFit->SetParameter(4,GausPreFit->GetParameter(0));
//			P4GausFit->SetParameter(5,GausPreFit->GetParameter(1));
//			P4GausFit->SetParLimits(5,GausPreFit->GetParameter(1)-40,GausPreFit->GetParameter(1)+40);
						P4GausFit->SetParameter(5,mass[m]);
			P4GausFit->SetParLimits(5,mass[m]-60,mass[m]+30);
			P4GausFit->SetParameter(6,GausPreFit->GetParameter(2));
			P4GausFit->SetParLimits(6,GausPreFit->GetParameter(2)-20,GausPreFit->GetParameter(2)+20);
		}
		/////////////////////////////////////////////////////////////////
		////REAL Fitting//////
		
						//P4GausFit->SetParLimits(5,mass[m]*0.1-20,mass[m]*0.1+20);
		TH1F* h_TTbarFitP4 = (TH1F*) InFile->Get((nameIN).c_str())->Clone();
		h_TTbarFitP4->Scale(scaleMC);

		
		switch ((int)mass[m]) {
			case 175: FitStart = 100;	// 200 GeV
				break;	
			case 200: FitStart = 110;	// 200 GeV
				break;	
			case 250: FitStart = 148;	// 250 GeV
				break;	
			case 300: FitStart = 185;	// 300 GeV
				break;	
			case 350: FitStart = 220;	// 350 GeV
				break;	
			case 400: FitStart = 230;	// 400 GeV
				break;	
			case 450: FitStart = 280;	// 450 GeV
				break;	
			case 500: FitStart = 300;	// 500 GeV
				break;	
			case 750: FitStart = 580;	// 750 GeV
				break;	
			case 1000: FitStart = 550;	// 1000 GeV
				break;	
			case 1250: FitStart = 800;	// 1250 GeV
				break;	
			case 1500: FitStart = 1050;	// 1500 GeV
				break;	
		}
		FitEnd=h_PreFitP4->GetMaximumBin()*nRebin + 800;
		if (FitEnd > 1900 || m > 8)
			FitEnd = 1900;

		
		h_TTbarFitP4->Fit(P4GausFit,"RQ","",FitStart,FitEnd);
		h_TTbarFitP4->Fit(P4GausFit,"RQ","",FitStart,FitEnd);
		h_TTbarFitP4->SetName(("P4Gaus_RealFit"+to_string(mass[m])+"_"+to_string(pT6V)).c_str());
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
		
		TTbarGausP4->SetName(("Gaus_P4"+to_string(mass[m])+"_"+to_string(pT6V)).c_str());
		
		
		TTbarP4->SetLineColor(1);
		
		TTbarP4->SetName(("P4_"+to_string(mass[m])+"_"+to_string(pT6V)).c_str());
		string bfolder;
		
		fnew1.cd();
		h_TTbarFitP4->Write();
		TTbarGausP4->Write();
		TTbarP4->Write();
		
		float SigP4 = TTbarGausP4->Integral(0,2000);
		float FullSigP4 = h_TTbarFitP4->Integral(0,2000);
		cout<<"Mass: "<<mass[m]<<" Gaus Integral: "<< SigP4/10/100000 << " " << sqrt(2*3.14)*TTbarGausP4->GetParameter(2)*TTbarGausP4->GetParameter(0)/10/100000 << endl;
		cout << "Full integral " << FullSigP4/100000 << endl;
		
		//RPV_223
		
		Mass.push_back(mass[m]);
		GausAmp.push_back(TTbarGausP4->GetParameter(0));
		GausMean.push_back(TTbarGausP4->GetParameter(1));
		GausWidth.push_back(TTbarGausP4->GetParameter(2));
		GausIntegral.push_back(SigP4/10/100000);
		FullIntegral.push_back(FullSigP4/100000);
		
		GausAmp_Err.push_back(TTbarGausP4->GetParError(0));
		GausMean_Err.push_back(TTbarGausP4->GetParError(1));
		GausWidth_Err.push_back(TTbarGausP4->GetParError(2));
		GausIntegral_Err.push_back(SigP4/10/100000*sqrt(pow(TTbarGausP4->GetParError(0)/TTbarGausP4->GetParameter(0),2)
														+pow(TTbarGausP4->GetParError(2)/TTbarGausP4->GetParameter(2),2)));
		double fullEffErr = (FullSigP4/100000.0) * sqrt((1.0/FullSigP4) +
			1.0/100000.0); // Statistical error only
		// double fullEffErr = (FullSigP4/100000.0) *
		// sqrt(0.0225 + (1.0/FullSigP4) + 1.0/100000.0);
		// cout << "Full integral error: " << fullEffErr << endl;
		FullIntegral_Err.push_back(fullEffErr);
		// FullIntegral_Err.push_back(FullSigP4/100000 *
			// sqrt(pow(P4GausFit->GetParError(0)/P4GausFit->GetParameter(0),2)
      // + pow(P4GausFit->GetParError(2)/P4GausFit->GetParameter(2),2)));
		}	
	
	}

	
	TGraph* g_GausMean = new TGraph((int)Mass.size(), &Mass[0],&GausMean[0]);
	g_GausMean->SetName(("GausMean_vs_Mass_"+flavor+"_"+to_string(pT6V)).c_str());
	g_GausMean->SetTitle(("GausMean_vs_Mass_"+flavor+"_"+to_string(pT6V)).c_str());
	
	TGraphErrors* g_GausAmp = new TGraphErrors((int)Mass.size(), &Mass[0],&GausAmp[0],0,&GausAmp_Err[0]);
	g_GausAmp->SetName(("GausAmp_vs_Mass_"+flavor+"_"+to_string(pT6V)).c_str());
	g_GausAmp->SetTitle(("GausAmp_vs_Mass_"+flavor+"_"+to_string(pT6V)).c_str());
	
	TGraphErrors* g_GausWidth = new TGraphErrors((int)Mass.size(),&Mass[0], &GausWidth[0],0,&GausWidth_Err[0]);
	g_GausWidth->SetName(("GausWidth_vs_Mass_"+flavor+"_"+to_string(pT6V)).c_str());
	g_GausWidth->SetTitle(("GausWidth_vs_Mass_"+flavor+"_"+to_string(pT6V)).c_str());
	
	TGraphErrors* g_GausIntegral = new TGraphErrors((int)Mass.size(),&Mass[0], &GausIntegral[0],0,&GausIntegral_Err[0]);
	g_GausIntegral->SetName(("GausAcceptance_vs_Mass_"+flavor+"_"+to_string(pT6V)).c_str());
	g_GausIntegral->SetTitle(("GausAcceptance_vs_Mass_"+flavor+"_"+to_string(pT6V)).c_str());
	
	TGraphErrors *g_FullIntegral = new TGraphErrors((int)Mass.size(), &Mass[0],
		&FullIntegral[0], 0, &FullIntegral_Err[0]);
	g_FullIntegral->SetName(("FullAcceptance_vs_Mass_"+flavor+"_"+to_string(pT6V)).c_str());
	g_FullIntegral->SetTitle(("FullAcceptance_vs_Mass_"+flavor+"_"+to_string(pT6V)).c_str());
	
	
	fnew1.cd();
	TF1 *f_GausAmp_seq500 = new TF1("GausAmp_seq500","[0]/x*exp([1]*x)", 170, 600);
	TF1 *f_GausAmp_geq500 = new TF1("GausAmp_geq500","[0]/x*exp([1]*x)", 670, 1600);
	
	g_GausAmp->Fit(f_GausAmp_seq500,"R0L");
	g_GausAmp->Fit(f_GausAmp_seq500,"RL");
	g_GausAmp->SetName(("GausAmp_vs_Mass_"+flavor+"_seq500_"+to_string(pT6V)).c_str());
	g_GausAmp->SetTitle(("GausAmp vs Mass flavor = "+flavor).c_str());
	
	g_GausAmp->Write();
	f_GausAmp_geq500->SetLineColor(kBlue);
	
	f_GausAmp_geq500->SetParameter(0, 1.58807e+02);
	f_GausAmp_geq500->SetParameter(1,-8.26712e-03);
	g_GausAmp->Fit(f_GausAmp_geq500,"R0");
	g_GausAmp->Fit(f_GausAmp_geq500,"RL");
	g_GausAmp->SetName(("GausAmp_vs_Mass_"+flavor+"_geq500_"+to_string(pT6V)).c_str());
	
	g_GausAmp->Write();
	
	int FitStart=195;
	int FitEnd=760;
	if(pT6V>60){
		FitStart=390;
		FitEnd=1520;
	}
	TF1 *f_GausWidth = new TF1("GausWidth","pol2", FitStart,FitEnd);
	g_GausWidth->Fit(f_GausWidth,"R");
	g_GausWidth->Write();
	
	TF1 *totalInt = new TF1("total","pol3",FitStart,FitEnd);
	
	g_GausIntegral->Fit(totalInt,"R");
	g_GausIntegral->Write();
	
	TF1 *totalInt2 = new TF1("total","pol3",FitStart,FitEnd);
	g_FullIntegral->Fit(totalInt2, "R");
	g_FullIntegral->Write();
	
	g_GausMean->Write();
	
}
	
	}

 



