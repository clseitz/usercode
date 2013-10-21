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

void tripletratioplot(int srch = 1)
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
  char hNAME[500], hNAME1[200], hNAME2[200];

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
	filelist.push_back(TFile::Open("histdir/combine.root"));
	cout << "opened input file\n";
	// filenames.push_back("BHT200_SQuad60_Di20_2012BCD.pdf");
	// titlename.push_back("Quad60_Di20 (base HT200) efficiency");
	// titlename.push_back("Quad60_Di20 (base Mu40) efficiency");
	//filenames.push_back("BQdjt4550_SQuad60_Di20_2012D.pdf");
	//titlename.push_back("Quad60_Di20 (base Quadjet45_50) efficiency");
	// filenames.push_back("MjjjvssumptDiagcut.root");
	titlename.push_back("Proportion of single-triplet events");
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
		for(int file=0; file < (int) filelist.size(); file++) {
		 int bjnum = 0, jPt = 110;
		 sprintf(hNAME2, "Mjjj_Sph4_bjet%i_pt%i_diag110_GE6jet",
		 	 bjnum, jPt);
		 if (srch == 2) {
		 	 bjnum = 1;
		 	 jPt = 60;
			 sprintf(hNAME2, "Mjjj_btag%i_bjet%i_pt%i_diag110_GE6jet",
				 bjnum, bjnum, jPt);
		 } else if (srch == 3) {
		 	 bjnum = 1;
			 sprintf(hNAME2, "Mjjj_Sph4_btag%i_bjet%i_pt%i_diag110_GE6jet",
				 bjnum, bjnum, jPt);
		 }
		 sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/", bjnum, jPt);
		 (void) strcat(hNAME, hNAME2);
		 (void) strcpy(hNAME1, hNAME2);
		 (void) strcat(hNAME1, ".root");
		 (void) strcat(hNAME2, ".pdf");
		 filenames.push_back(hNAME1);
		 // filenames.push_back(hNAME2);
		 cout << "fetching histogram " << hNAME << endl;
		 TCanvas* can= new TCanvas((filenames[file]).c_str(),(filenames[file]).c_str(),900,700);
		 TH1F* fullMjjj = (TH1F*) filelist[file]->Get(hNAME)->Clone();
		 // sprintf(hNAME, "Triplets/bjet_%i/jetpt_%i/Mjjj_btag%i_bjet%i_pt%i_diag110_GE6jet_1trp",
		 	 // bjnum, jPt, bjnum, bjnum, jPt);
		 strcat(hNAME, "_1trp");
		 cout << "fetching histogram " << hNAME << endl;
		 TH1F* singleTrips =(TH1F*) filelist[file]->Get(hNAME)->Clone();
		 // singleTrips->Sumw2();
				
 		can->cd();
		
		// singleTrips->SetMinimum(0.82);
		// singleTrips->SetMaximum(1.0);
		TLine *max = new TLine(0.1, 0.1, 0.9, 0.9);
		max->SetLineColor(kRed + 1);
		singleTrips->SetLineWidth(2);
		TH1F *trip1copy = (TH1F *) singleTrips->Clone();
		cout << "Doubling OK? " << singleTrips->Add(trip1copy) << endl;
		cout << "Subtracting OK? " << singleTrips->Add(fullMjjj, -1.0) << endl;
		cout << "Dividing OK? " << singleTrips->Divide(trip1copy) << endl;
		// singleTrips->GetYaxis()->SetRangeUser(0.70, 1.0);
		singleTrips->GetXaxis()->SetRangeUser(0, 2200);
		singleTrips->SetMarkerColor(kGreen + 1);
		singleTrips->Draw("hist");
		// singleTrips->Draw("cont3 same");
		singleTrips->GetXaxis()->SetTitle("Triplet invariant mass [GeV]");
		singleTrips->GetYaxis()->SetTitle("Purity of single triplets per event");
		float labsiz = 0.045;
		float axsize = 0.035;
		singleTrips->GetXaxis()->SetTitleSize(labsiz);
		singleTrips->GetYaxis()->SetTitleSize(labsiz);
		// singleTrips->GetXaxis()->SetLabelSize(axsize);
		// singleTrips->GetYaxis()->SetLabelSize(axsize);
		singleTrips->GetYaxis()->SetTitleOffset(1.4);
		singleTrips->GetXaxis()->SetTitleOffset(1.2);
		// fullMjjj->Draw("col same");
		// max->DrawLineNDC(0.22, 0.13, 0.98, 0.89);

		can->SaveAs(filenames[file].c_str());	
		can->SaveAs(hNAME2);	
	}
}		
	
