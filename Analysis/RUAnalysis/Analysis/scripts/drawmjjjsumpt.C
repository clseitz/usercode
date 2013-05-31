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
#include "TH2F.h"
#include "TLine.h"
#include "TLatex.h"
#include "TStyle.h"
#include "tdrstyle.C"

using namespace std;

void drawmjjjsumpt()
{
	setTDRStyle();
	vector <string > plotlistBase;
	vector <string > plotlistBaseSel;
	vector <string > plotnames;
	vector <float > ymaxlist;
	vector <TFile* > filelist;
	vector <string > filenames;
	vector <string > titlename;
  //Initialize your TH1F's from your file....
  //Note that these next 6 lines are not road-tested.
  char hNAME[500];

 // gStyle->SetPaintTextFormat("5.3f");
 gStyle->SetOptStat(kFALSE);
 gStyle->SetPalette(1, 0);

	/*filelist.push_back(TFile::Open("data2012_MultiJet_BQuad50_SQuad60_Di20_TriggerMap_6jets20GeV_2p4pb_jun19.root"));
	filenames.push_back("Quad50_Quad60_Di20_jun19.png");
	titlename.push_back("TriggerMap for Quad60_Di20 (base Quad50) efficiency");*/

/*	filelist.push_back(TFile::Open("data2012_MultiJet_BQuad70_SQuad80_TriggerMap_6jets20GeV_2p4pb_jun19.root"));
	filenames.push_back("TriggerMap_Quad70_Quad80_jun19.pdf");
titlename.push_back("Quad80 (base Quad70) efficiency");
*/
/*	
	filelist.push_back(TFile::Open("data2012_MultiJet_BSix35_SSix45_TriggerMap_6jets20GeV_2p4pb_jun19.root"));
	filenames.push_back("Six35_Six45_jun19.png");
	titlename.push_back("Six45 (base Six35) efficiency");
*/

		// filelist.push_back(TFile::Open("data2012_MultiJet_BMu40_SQuad60_Di20_TriggerMap_6jets20GeV_jun29.root"));
	// filelist.push_back(TFile::Open("trigstudy/runsABCD.root"));
	filelist.push_back(TFile::Open("samples/RUOfficial/jecdecsph/mc_RPV_M400_112_BtagMap_Officialpu206940twoDMC.root"));
	cout << "opened input file\n";
	// filenames.push_back("BMu40_SQuad60_Di20_2012ABCD.pdf");
	// filenames.push_back("BHT200_SQuad60_Di20_2012BCD.pdf");
	// titlename.push_back("Quad60_Di20 (base HT200) efficiency");
	// titlename.push_back("Quad60_Di20 (base Mu40) efficiency");
	//filenames.push_back("BQdjt4550_SQuad60_Di20_2012D.pdf");
	//titlename.push_back("Quad60_Di20 (base Quadjet45_50) efficiency");
	filenames.push_back("MjjjvssumptDiagcut.pdf");
	titlename.push_back("Mjjj vs. Sum PT and diagonal cut");
	// filenames.push_back("BEle27_WP80_SQuad60_Di20_Electron2012Cv2TwoD.pdf");
	// titlename.push_back("Quad60_Di20 (base Ele27_WP80) efficiency");

/*	filelist.push_back(TFile::Open("data2012_MultiJet_BMu40_SSix45_TriggerMap_6jets20GeV_jul3.root"));
	filenames.push_back("BMu40_SSix45.png");
	titlename.push_back("SSix45 (base Mu40) efficiency");
*/
/*	filelist.push_back(TFile::Open("data2012_MultiJet_BMu_Quad60_Di20_Run2012AC_TriggerMap_6jets45GeV_oct16_geq6jet.root"));
        filenames.push_back("Quad50_Quad60_Di20_5fb");
        titlename.push_back("Quad60_Di20 (base Mu) efficiency");
        ymaxlist.push_back(1.1);
*/
	/*
	filelist.push_back(TFile::Open("mc2012_TTJets_TriggerMap_jun7.root"));
	filenames.push_back("TTJets_TriggerMap_8TeV.png");
	titlename.push_back("TTJets selection efficiency");
	*/
		for(int file=0; file < (int) filelist.size(); file++){
		 TCanvas* can= new TCanvas((filenames[file]).c_str(),(filenames[file]).c_str(),900,700);
				
		 int bjnum = 0, jPt = 60;
		 sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_sumpt_bjet%i_pt%i_GE6jetMCmatch",
		 	 bjnum, jPt, bjnum, jPt);
		 cout << "fetching histogram " << hNAME << endl;
		 TH2F* signaltriplets = (TH2F*) filelist[file]->Get(hNAME)->Clone();
		 sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_sumpt_bjet%i_pt%i_GE6jetMCcomb",
		 	 bjnum, jPt, bjnum, jPt);
		 cout << "fetching histogram " << hNAME << endl;
		 TH2F* badtriplets =(TH2F*) filelist[file]->Get(hNAME)->Clone();
				
 		can->cd();
		
		// badtriplets->SetMinimum(0.82);
		// badtriplets->SetMaximum(1.0);
		TLine *max = new TLine(0.1, 0.1, 0.9, 0.9);
		max->SetLineColor(kGreen + 2);
		max->SetLineWidth(4);
		badtriplets->SetContour(80);
		badtriplets->GetYaxis()->SetRangeUser(0, 1800);
		badtriplets->GetXaxis()->SetRangeUser(0, 1500);
		badtriplets->Draw("scat");
		badtriplets->GetYaxis()->SetTitle("Invariant Mass [GeV]");
		badtriplets->GetXaxis()->SetTitle("#Sigma p_{T} [GeV]");
		float labsiz = 0.045;
		float axsize = 0.035;
		badtriplets->GetXaxis()->SetTitleSize(labsiz);
		badtriplets->GetYaxis()->SetTitleSize(labsiz);
		// badtriplets->GetXaxis()->SetLabelSize(axsize);
		// badtriplets->GetYaxis()->SetLabelSize(axsize);
		badtriplets->GetYaxis()->SetTitleOffset(1.4);
		badtriplets->GetXaxis()->SetTitleOffset(1.2);
		signaltriplets->Draw("col same");
		max->DrawLineNDC(0.22, 0.13, 0.98, 0.89);

		can->SaveAs(filenames[file].c_str());	
	}
}		
	
