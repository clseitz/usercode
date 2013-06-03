#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TObject.h"
#include "THStack.h"
#include <sstream>
#include "TH1F.h"
#include "math.h"
#include "TF1.h"
#include "TLine.h"
#include "TLatex.h"
#include "TStyle.h"

void trigTurnOnVsPt()
{
 gStyle->SetOptStat(kFALSE);

	int whichFile=0;
	vector <string > plotlistBase;
	vector <string > plotlistBaseSel;
	vector <string > plotlistRun;
	vector <string > plotnames;
	vector <float > ymaxlist;
	vector <TFile* > filelist;
	vector <string > filenames;
	vector <string > titlename;
  //Initialize your TH1F's from your file....
  //Note that these next 6 lines are not road-tested.
/*
	 filelist.push_back(TFile::Open("data2012_MultiJet_BQuad50_SQuad60_Di20_TriggerMap_6jets20GeV_2p4pb_jun19.root"));
	 filenames.push_back("Quad50_Quad60_Di20_jun19");
	 titlename.push_back("Quad60_Di20 (base Quad50) efficiency");
	 ymaxlist.push_back(1.1);
	TFile fnew1("TriggerPlots_BQuad50_SQuad60_Di20.root", "recreate");
 
	 filelist.push_back(TFile::Open("data2012_MultiJet_BQuad70_SQuad80_TriggerMap_6jets20GeV_2p4pb_jun19.root"));
	 filenames.push_back("BQuad70_SQuad80_jun19");
	 ymaxlist.push_back(1.1);
	 titlename.push_back("Quad80 (base Quad70) efficiency");
		TFile fnew1("TriggerPlots_BQuad70_SQuad80.root", "recreate");
	*/
	/*filelist.push_back(TFile::Open("data2012_MultiJet_BSix35_SSix45_TriggerMap_6jets20GeV_2p4pb_jun19.root"));
	filenames.push_back("BSix35_SSix45_jun19");
	titlename.push_back("Six45 (base Six35) efficiency");
	ymaxlist.push_back(1.1);
	 	TFile fnew1("TriggerPlots_BSix35_SSix45.root", "recreate");
	*/
		
	filelist.push_back(TFile::Open("trigstudy/nobjetreq/jetht2base/runBCD.root"));
	// filelist.push_back(TFile::Open("trigstudy/runsABCD.root"));
	// filelist.push_back(TFile::Open("data2012_MultiJet_BMu40_SQuad60_Di20_TriggerMap_6jets20GeV_jun29.root"));
	// filenames.push_back("BMu40_SQuad60_Di20_2012ABCD");
	// filenames.push_back("BMu40_SQuad60_Di20_2012Dfulljethtnojec");
	// filenames.push_back("BHT200_SQuad60_Di20_2012Cjetht");
	// titlename.push_back("Quad60_Di20 (base HT200) efficiency");
	// filenames.push_back("BQuad4550_SQuad60_Di20_2012D");
	//titlename.push_back("Quad60_Di20 (base Quadjet45_50) efficiency");
	// filenames.push_back("BEle27_WP80_SQuad60_Di20_Electron2012Cv2");
	// titlename.push_back("Quad60_Di20 (base Ele27_WP80) efficiency");
	filenames.push_back("BMu40HT200_SQuad60_Di20_2012BCD");
	titlename.push_back("Quad60_Di20 (base Mu40HT200) efficiency");
	// titlename.push_back("Quad60_Di20 (base Mu40) efficiency");
	ymaxlist.push_back(1.1);
	TFile fnew1("TriggerPlots_BMu40_SQuad60_Di20.root", "recreate");
	
	/*	filelist.push_back(TFile::Open("data2012_MultiJet_BMu40_SQuad50_TriggerMap_6jets20GeV_jul3_RUNg194270_eq4jet.root"));
	filenames.push_back("BMu40_SQuad50_Jul3_RUNg194270_eq4jet");
	titlename.push_back("Quad50 (base Mu40) efficiency (4 jets > 20 Gev)");
	ymaxlist.push_back(1.1);
	TFile fnew1("TriggerPlots_BMu40_SQuad50_RUNg194270_eq4jet.root", "recreate");
	*/
	/*
	filelist.push_back(TFile::Open("data2012_MultiJet_BMu40_SSix45_TriggerMap_6jets20GeV_jul3.root"));
	filenames.push_back("BMu40_SSix45");
	titlename.push_back("Six45 (base Mu40) efficiency (6 jets > 20 Gev)");
	ymaxlist.push_back(1.1);
	TFile fnew1("TriggerPlots_BMu40_SSix45t.root", "recreate");
	*/
	/*	
	filelist.push_back(TFile::Open("data2012_MultiJet_BMu40_SQuad80_TriggerMap_6jets20GeV_jul3_eq4jet.root"));
	filenames.push_back("BMu40_SQuad80_new");
	titlename.push_back("SQuad80 (base Mu40) efficiency (4 jets > 20 Gev)");
	ymaxlist.push_back(1.1);
	TFile fnew1("TriggerPlots_BMu40_SQuad80.root", "recreate");
	*/
	/*
	filelist.push_back(TFile::Open("data2012_MultiJet_BMu40_SHT750_TriggerMap_6jets45GeV_jul8_geq6jet.root"));
	filenames.push_back("BMu40_SHT750");
	titlename.push_back("SHT750 (base Mu40) efficiency (6 jets > 45 Gev)");
	ymaxlist.push_back(1.1);
	TFile fnew1("TriggerPlots_BMu40_SHT750_jetpt45.root", "recreate");
*/
	/*filelist.push_back(TFile::Open("data2012_MultiJet_BHT650_SHT750_TriggerMap_6jets45GeV_jul8_geq6jet.root"));
	filenames.push_back("BHT650_SHT750");
	titlename.push_back("SHT750 (base HT650) efficiency (6 jets > 45 Gev)");
	ymaxlist.push_back(1.1);
	TFile fnew1("TriggerPlots_BHT650_SHT750_jetpt45.root", "recreate");
	*/

	/*        filelist.push_back(TFile::Open("data2012_MultiJet_BMu_Quad60_Di20_Run2012AC_TriggerMap_6jets45GeV_oct16_geq6jet.root"));
        filenames.push_back("Quad50_Quad60_Di20_5fb");
	titlename.push_back("Quad60_Di20 (base Mu) efficiency");
        ymaxlist.push_back(1.1);
	TFile fnew1("TriggerPlots_BMu_SQuad60_Di20jetpt45.root", "recreate");
	*/
        /*filelist.push_back(TFile::Open("data2012_MultiJet_BMu_Quad60_Di20_Run2012B_TriggerMap_Nov9_geq6jet.root"));
        filenames.push_back("Mu_Quad60_Di20_5fb");
	titlename.push_back("Quad60_Di20 (base Mu dataset) efficiency");
        ymaxlist.push_back(1.1);
	TFile fnew1("TriggerPlots_BMuData_SQuad60_Di20jetpt45.root", "recreate");
	*/
	plotlistBase.push_back("Jet0_Base");
	plotlistBase.push_back("Jet1_Base");
	plotlistBase.push_back("Jet2_Base");
	plotlistBase.push_back("Jet3_Base");
	plotlistBase.push_back("Jet4_Base");
	plotlistBase.push_back("Jet5_Base");
	plotlistBase.push_back("HT_Base");
	

	plotlistBaseSel.push_back("Jet0_BaseSel");
	plotlistBaseSel.push_back("Jet1_BaseSel");
	plotlistBaseSel.push_back("Jet2_BaseSel");
	plotlistBaseSel.push_back("Jet3_BaseSel");
	plotlistBaseSel.push_back("Jet4_BaseSel");
	plotlistBaseSel.push_back("Jet5_BaseSel");
	plotlistBaseSel.push_back("HT_BaseSel");
	
	plotlistRun.push_back("RunNumber_Base");
	plotlistRun.push_back("RunNumber_BaseSel");
	plotlistRun.push_back("RunNumber_Sel");

	
	plotnames.push_back("Jet1.pdf");
	plotnames.push_back("Jet2.pdf");
	plotnames.push_back("Jet3.pdf");
	plotnames.push_back("Jet4.pdf");
	plotnames.push_back("Jet5.pdf");
	plotnames.push_back("Jet6.pdf");
	plotnames.push_back("HTJetp45.pdf");
	
	//For the Lumi Studies make the reference histogram
	int Runs[200]={190645, 190704, 190705, 190738, 191043, 191046, 191056, 191057, 191062, 191090, 191201, 191202, 
				191226, 191247, 191248, 191264, 191271, 191276, 191277, 191367, 191411, 191695, 191697, 191718, 191720,
				191721, 191726, 191810, 191830, 191833, 191834, 191837, 191856, 191859, 193093, 193112, 193116, 193123, 
				193124, 193207, 193334, 193336, 193541, 193556, 193557, 193575, 193621, 193834, 193835, 193836, 
				193998, 193999, 194027, 194050, 194051, 194052, 194075, 194076, 194108, 194115, 194117, 194119, 194120,
				194150, 194151, 194153, 194199, 194210, 194223, 194224, 194225, 194270, 194303, 194304, 194305, 
				194314, 194315, 194317, 194424, 194428, 194429, 194439, 194455, 194464, 194479, 194480, 194533, 194619, 
				194643, 194644, 194691, 194699, 194702, 194704, 194711, 194712, 194735, 194778, 194789, 194790, 
				194825, 194896, 194897, 194912, 194914, 194915, 195014, 195015, 195016};
	
	float Lumis[200] ={0.550795, 0.028862, 14.888, 12.836, 0.061734, 13.822, 0.263979, 3.524, 26.684, 5.348, 3.345, 
					7.079, 93.555, 70.327, 4.404, 11.258, 9.518, 0.93759, 53.292, 0.132846, 0.001195, 0.013044, 
					0.0, 16.665, 12.535, 10.467, 0.512428, 7.698, 37.752, 9.526, 29.529, 
					4.432, 8.63, 7.373, 0.0738, 1.887, 4.655, 0.543375, 1.04, 6.768, 8.915, 43.131, 26.571, 
					3.218, 5.581, 40.018, 89.651, 0.98811, 0.648552, 0.053585, 19.187, 3.61, 5.497, 110.376, 
					0.48922, 6.582, 4.91, 54.111, 61.654, 58.992, 2.277, 14.693, 19.262,26.671, 40.786, 6.994, 
					27.228, 38.922, 6.16, 42.181, 12.739, 1.428, 5.054, 4.798, 8.577, 28.127, 41.671, 1.466, 
					66.671, 35.988, 56.205, 7.776, 27.076, 21.853, 36.72, 81.026, 76.611, 9.916, 27.441, 
					33.218, 28.158, 22.555, 15.525, 40.875, 34.173, 33.839, 9.926, 18.834, 52.079, 3.538, 
		18.742, 8.553, 12.299, 151.942, 2.438, 4.624, 15.377, 1.2, 48.556};
		
	TH1F* h_RunNumber_Lumi = new TH1F("RunNumber_Lumi","RunNumber_Lumi",6000,190000,196000);
	for (int a=0; a< sizeof(Runs) / sizeof(int); a++){
	
		// cout << "ind " << a << " run " << Runs[a] << " lumi " << Lumis[a] << endl;
		h_RunNumber_Lumi->SetBinContent(Runs[a]-190000+1,Lumis[a]);
	}

	
  //So I use 2D plots, but it's even easier when you just load the TH1Fs, just name them htop_data and hbot_data directly
  //Also, you'll need to fix some things at the bottom of the script (x axis, maybe y axis, but little things)
  //Otherwise, I think things work out of the box (I know, I've said this before)
	for(int file=0; file<filelist.size(); file++){
	TH1F* htop_RunN =(TH1F*) filelist[file]->Get(plotlistRun[1].c_str())->Clone();
		TH1F* hbot_RunN = (TH1F*) filelist[file]->Get(plotlistRun[0].c_str())->Clone();
		TH1F* hsel_RunN = (TH1F*) filelist[file]->Get(plotlistRun[2].c_str())->Clone();

		
				fnew1.cd();
		h_RunNumber_Lumi->Write();		
		htop_RunN->Write();
		hbot_RunN->Write();
		hsel_RunN->Write();
		htop_RunN->Divide(h_RunNumber_Lumi);
		hbot_RunN->Divide(h_RunNumber_Lumi);
		hsel_RunN->Divide(h_RunNumber_Lumi);

		htop_RunN->SetName("BaseSel_Div_LumiperRun");
		hbot_RunN->SetName("Base_Div_LumiperRun");
		hsel_RunN->SetName("Sel_Div_LumiperRun");	
		htop_RunN->Write();
		hbot_RunN->Write();
		hsel_RunN->Write();
		
		
		for(int i=0; i<(plotlistBase.size()); i++){
		//TH1F* htop_datat =(TH1F*) myEffNfile_Data->Get(plotlistBaseSel[i].c_str());
		//TH1F* hbot_datat = (TH1F*) myEffNfile_Data->Get(plotlistBase[i].c_str());
		
		TH1F* htop_data =(TH1F*) filelist[file]->Get(plotlistBaseSel[i].c_str())->Clone();
		TH1F* hbot_data = (TH1F*) filelist[file]->Get(plotlistBase[i].c_str())->Clone();
		
	//TH1F* htop_data =htop_datat->Clone();
	//TH1F* hbot_data =hbot_datat->Clone();
//  TH1D* htop_data = htop_2ddata->ProjectionY();
//  TH1D* hbot_data = hbot_2ddata->ProjectionY();
  //myEffNfile_Data->Close();
  std::cout << "Boom" << std::endl;
		if(i<2){
		htop_data->GetXaxis()->SetRangeUser(50,800);
			hbot_data->GetXaxis()->SetRangeUser(50,800);}
		if(i>=2){
			htop_data->GetXaxis()->SetRangeUser(50,200);
			hbot_data->GetXaxis()->SetRangeUser(50,200);}
//		htop_data->Rebin(2);
//		hbot_data->Rebin(2);

	htop_data->Draw();
  hbot_data->Draw("same");
		TH1F* ratio = (TH1F*) filelist[file]->Get(plotlistBaseSel[i].c_str())->Clone();

  ratio->Sumw2();
  ratio->Divide(hbot_data);
  //erf((m-m0)/sigma)+1)/2
/*  TF1 * f1 = new TF1("f1","(TMath::Erf((x*[0] -[1])/[2])+1.)/2.",20.,100.);
  f1->SetParameter(2,1.);
  //ratio->Fit(f1,"R");*/

  TCanvas *c1 = new TCanvas("c1","Canvas1",0,0,800,600);
  c1->SetLineColor(0);
  c1->SetFrameFillColor(0);
  c1->SetFillStyle(4000);
  c1->SetFillColor(0);   
  c1->SetBorderMode(0);
  //gStyle->SetOptStat(0);    
  c1->SetFillColor(0);
  c1->SetBorderSize(0);
  c1->SetBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetRightMargin(0.12);
  c1->SetTopMargin(0.12);
  c1->SetBottomMargin(0.15);
/*  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000); //This puts in stats box
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.5); // X position of the title box from left
  gStyle->SetTitleAlign(23);
  gStyle->SetTitleY(.975); // Y position of the title box from bottom
  gStyle->SetLabelSize(0.03,"y");
  gStyle->SetStatX(.9);
  gStyle->SetStatY(.9);
  gStyle->SetStatW(0.20);
  gStyle->SetStatFontSize(0.044);
  gStyle->SetStatColor(0);  */
  std::cout << "Boom2" << std::endl;
  TGraphAsymmErrors* eff0 = new TGraphAsymmErrors();
  std::cout << "Boom3" << std::endl;
	eff0->BayesDivide(htop_data,hbot_data);
		TF1 * f1 = new TF1("f1","(TMath::Erf((x*[0] -[1])/[2])+1.)/2.",0.,1700.);
		f1->SetParameter(2,1.);
		if (i==2) eff0->Fit(f1,"","",50,350);
		if (i==3) eff0->Fit(f1,"","",50,250);
		if (i==5) eff0->Fit(f1,"","",50,250);
		if (i==6) eff0->Fit(f1,"","",600,1400);
	//	eff0->Divide(htop_data,hbot_data);
		
  //  eff0->BayesDivide(htop_data,hbot_data,"w");
  //eff1 = new TGraphAsymmErrors();
  //eff1->BayesDivide(htop_mc,hbot_mc,"w");
			std::cout << "Boom4" << std::endl;
		float x=400.0;
		//float xmin=60;
		float xmin=30;
		if(i>=1) x = 300.0; 
		if(i>=3) x = 250.0; 
		if(i>=6)
		  { x = 1300.0; 
		    xmin = 550.0;
		  }
  TH1D *T_Empty = new TH1D("T_Empty", "", 1, xmin, x);
  T_Empty->SetMinimum(0.001);
  T_Empty->SetMaximum(ymaxlist[file]);
  T_Empty->SetStats(kTRUE);
  T_Empty->GetXaxis()->SetLabelOffset(0.01);
  T_Empty->GetYaxis()->SetLabelOffset(0.01);
  T_Empty->GetXaxis()->SetLabelSize(0.035);
 T_Empty->GetXaxis()->SetLabelFont(42);
 T_Empty->GetXaxis()->SetTitleSize(0.040);
 T_Empty->GetYaxis()->SetLabelSize(0.035);
 T_Empty->GetYaxis()->SetLabelFont(42);
 T_Empty->GetYaxis()->SetTitleSize(0.040);
T_Empty->GetXaxis()->SetTitleOffset(1.29);
 T_Empty->GetYaxis()->SetTitleOffset(1.39);
 T_Empty->GetXaxis()->SetTitleColor(1);
 T_Empty->GetYaxis()->SetTitleColor(1);
 T_Empty->GetXaxis()->SetNdivisions(10505);
 T_Empty->GetYaxis()->SetNdivisions(515);
 T_Empty->GetXaxis()->SetTitleFont(42);
 T_Empty->GetYaxis()->SetTitleFont(42);
	char hNAME[99];	
	sprintf(hNAME, "%ith Jet P_{T} (GeV)", i+1);	
			if (i==6) sprintf(hNAME, "HT");
			T_Empty->GetXaxis()->SetTitle(hNAME);	

			T_Empty->SetTitle(titlename[file].c_str());
 T_Empty->GetYaxis()->SetTitle(titlename[file].c_str());
 T_Empty->Draw("AXIS");
 
 if(i<2){
   T_Empty->GetXaxis()->SetRangeUser(50,800);}
 if(i>=2){
   T_Empty->GetXaxis()->SetRangeUser(50,200);
 }
 eff0->SetMarkerStyle(20);
 eff0->SetMarkerSize(1.0);
 eff0->SetMarkerColor(1);
 eff0->SetLineWidth(2);
 //eff1->SetMarkerStyle(21);
 //eff1->SetMarkerColor(2);
 //eff1->SetMarkerSize(0.75);
 //eff1->SetLineWidth(2);

 eff0->Draw("e1pZ");
		

 eff0->SetTitle(hNAME);
 eff0->SetName(hNAME);			

			eff0->Write();
//		ratio->Draw("E");
 //eff1->Draw("e1pZsame");
TLegend *leg = new TLegend(0.2560484,0.8877119,0.7560484,0.9872881,NULL,"brNDC");

 leg->SetTextFont(42);
 leg->SetTextSize(0.030);
 leg->SetLineColor(1);
 leg->SetLineStyle(1);
 leg->SetLineWidth(1);
 leg->SetFillStyle(1001);
 leg->AddEntry(eff0,titlename[file].c_str(),"");
 //leg->AddEntry(eff1,"Spring10 7 TeV MC","p");
 leg->SetBorderSize(0);
 leg->SetFillColor(0);
 leg->Draw();

TLatex* tex = new TLatex();
 tex->SetTextColor(1);
 tex->SetTextSize(0.030);
 tex->SetLineWidth(2);
 tex->SetTextFont(42);
// tex->DrawLatex(1000., 0.65, titlename[file].c_str());

 float Offset = 200.;

 float y_min = 0.99;
 float y_max = 0.99;
 float x_min = xmin;
 float x_max = x;
 TLine *line = new TLine(x_min, y_min, x_max, y_max);
 line->SetLineColor(kRed);
 line->SetLineWidth(2);
 line->SetLineStyle(3);
 line->Draw("same");
 TLine *line2 = new TLine(900., 0.5, 900., 1.0);
 line2->SetLineColor(kBlue);
 line2->SetLineWidth(3);
 line2->SetLineStyle(2);
 //line2->Draw("same");
 f1->SetLineColor(4);
 //f1->Draw("same");
string suffix="_histodiv.png";
			
		cout << "save file name " << filenames[file]+plotnames[i] << endl;
		string svfile = filenames[file]+plotnames[i];
		c1->SaveAs(svfile.c_str());
		htop_data->Delete();
		hbot_data->Delete();
			std::cout << "Boom4" << std::endl;


	}	
			}
}	
	
