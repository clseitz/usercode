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

void makeTriggerMap()
{

	vector <string > plotlistBase;
	vector <string > plotlistBaseSel;
	vector <string > plotnames;
	vector <float > ymaxlist;
	vector <TFile* > filelist;
	vector <string > filenames;
	vector <string > titlename;
  //Initialize your TH1F's from your file....
  //Note that these next 6 lines are not road-tested.
char hNAME[99];


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

		filelist.push_back(TFile::Open("data2012_MultiJet_BMu40_SQuad60_Di20_TriggerMap_6jets20GeV_jun29.root"));
	filenames.push_back("BMu40_SQuad60_Di20_Nov20.pdf");
	titlename.push_back("Quad60_Di20 (base Mu40) efficiency");

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
		for(int file=0; file<filelist.size(); file++){
		 TCanvas* can= new TCanvas((filenames[file]).c_str(),(filenames[file]).c_str(),900,700);
			TH2F* hTriggerMap = new TH2F((filenames[file]).c_str(), (titlename[file]).c_str(),16,20,100,16,20,100);  
		for(int i=0; i<15; i++){
			for (int j=i; j<15; j++){
				int iPt=20+i*5;
				int jPt=20+j*5;
				
				sprintf(hNAME, "h_Jet0_BaseSel_FourPt%i_SixPt%i", jPt, iPt);
				TH1F* htop_data =(TH1F*) filelist[file]->Get(hNAME)->Clone();
				
				sprintf(hNAME, "h_Jet0_Base_FourPt%i_SixPt%i", jPt, iPt);
				TH1F* hbot_data = (TH1F*) filelist[file]->Get(hNAME)->Clone();
				
	
		//TH1F* htop_datat =(TH1F*) myEffNfile_Data->Get(plotlistBaseSel[i].c_str());
		//TH1F* hbot_datat = (TH1F*) myEffNfile_Data->Get(plotlistBase[i].c_str());
				
		
		float ftop = htop_data->GetEntries();
		float fbot = hbot_data->GetEntries();
		//eff for example ttbar
		//float ratio = 100*ftop/1203373;///fbot;
		//trigger eff
		float ratio = ftop/fbot;
				hTriggerMap->SetBinContent(i+1,j+1,ratio);
				
		cout<<"4thjet pt: "<<jPt<<" 6thjet pt: "<<iPt<<" top: "<<ftop<<" bottom: "<<fbot<<" Eff: "<<ratio<<endl;
				
				
			}
		}
				can->cd();
		
		hTriggerMap->Draw("colzTEXT");
		hTriggerMap->GetYaxis()->SetTitle("4th P_{T} [GeV]");
		hTriggerMap->GetXaxis()->SetTitle("6th P_{T} [GeV]");
		hTriggerMap->GetYaxis()->SetTitleOffset(1.2);
		hTriggerMap->GetXaxis()->SetTitleOffset(1.2);

		can->SaveAs(filenames[file].c_str());	
				}
}		
	
