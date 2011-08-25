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



void CountMjjj(TH1F *temp_diagcut,float diag, float i){
	 

}
void make_stack()
{
  float lumi=1000.;
  vector <string > namelist;
  
  vector <string > VarList;
  vector <TFile* > data;
  vector <TFile* > filelist;
  vector<float> nEvtTot;
  vector<float> McXsec;
  vector<float> DataLumi;

  //file 0-3 are the files to fit
   filelist.push_back(TFile::Open("../TTBar_plots_additionalCuts.root"));
  namelist.push_back("TTbarJEts_e");
  //nEvtTot.push_back(216095.0);
  nEvtTot.push_back(3.6838e+06);
  McXsec.push_back(157.5);
  DataLumi.push_back(lumi);

  /* filelist.push_back(TFile::Open("../TTBar_plots_St600.root"));
  namelist.push_back("TTbarJEts_e");
  //nEvtTot.push_back(216095.0);
  nEvtTot.push_back(3.6838e+06);
  McXsec.push_back(0);
  DataLumi.push_back(lumi);
  */
  
  filelist.push_back(TFile::Open("../Wp600_plots_additionalCuts.root"));
  namelist.push_back("Wp600_e");
  nEvtTot.push_back(99987.0);
  McXsec.push_back(8.0);
  DataLumi.push_back(lumi);
  filelist.push_back(TFile::Open("../Wp1000_plots_additionalCuts.root"));
  namelist.push_back("Wp1000_e");
  nEvtTot.push_back(99995.0);
  McXsec.push_back(0.72);
  DataLumi.push_back(lumi);

 
  filelist.push_back(TFile::Open("../Sbottom750_plots_additionalCuts.root"));
  namelist.push_back("Sbottom750_e");
  nEvtTot.push_back(57073.0);
  McXsec.push_back(8.0);
  DataLumi.push_back(lumi);
 filelist.push_back(TFile::Open("../Stop350_plots_additionalCuts.root"));
  namelist.push_back("Stop350_e");
  nEvtTot.push_back(10000.0);
  McXsec.push_back(1);
  DataLumi.push_back(lumi);
  

  //plotlist.push_back("Event/SumptSig4HighestPlus");
  //plotlist.push_back("Event/SumptSig4SecondHighestPlus");
  //plotlist.push_back("Event/TransMassLepMET4JetPlus");
  //plotlist.push_back("Event/TransMassLepMET4SecondJetPlus");
  //plotlist.push_back("Event/SumptSig4HighestMinus");
  //plotlist.push_back("Event/SumptSig4SecondHighestMinus");
  //plotlist.push_back("Event/TransMassLepMET4JetMinus");
  //plotlist.push_back("Event/TransMassLepMET4SecondJetMinus");

  // string plotname="Mass3Jet2B";
  //string plotname="LepB_Diag50_Upper160_3Jet1B";
  //string plotname="LepBJet_Diag50_Upper160_4Jet";

 VarList.push_back("SumptSig4Highest_");
 VarList.push_back("SumptSig4SecondHighest_");
 VarList.push_back("TransMassLepMET4Jet_");
 VarList.push_back("TransMassLepMET5Jet_");
 VarList.push_back("TransMassLepMET4JetB_");
 VarList.push_back("TransMassLepMET5JetB_");
 VarList.push_back("Mass3Jet2B_");
 VarList.push_back("MassLep1Jet_");
 VarList.push_back("MassLep1B_");
 //VarList.push_back("MassLepB_vs_SumPt_");
 VarList.push_back("DeltaPhiLepMET_");
 VarList.push_back("LepBJet_Diag50_Upper160_4Jet_");
 VarList.push_back("LepB_Diag50_Upper160_3Jet1B_");
 VarList.push_back("LeadingJetPt_");
 VarList.push_back("St_");
 VarList.push_back("TransMassLepMET1JetB_");
VarList.push_back("Mass3Jet1B_");
//VarList.push_back("TransMassLepMET4Jet_vs_Mass3Jet1B_");
  
  

  TFile fnew1("stack_plots_additionalCuts.root", "recreate");
  
  for(int m=0; m<VarList.size(); m++){
    vector <string > plotlist;
    //plotlist.push_back("MET");
    //plotlist.push_back("MET");
    plotlist.push_back("5Jet_1b_P/"+VarList[m]+"5Jet_1b_P");
  plotlist.push_back("5Jet_2b_P/"+VarList[m]+"5Jet_2b_P");
  plotlist.push_back("4Jet_1b_P/"+VarList[m]+"4Jet_1b_P");
  plotlist.push_back("4Jet_2b_P/"+VarList[m]+"4Jet_2b_P");
  plotlist.push_back("5Jet_1b_M/"+VarList[m]+"5Jet_1b_M");
  plotlist.push_back("5Jet_2b_M/"+VarList[m]+"5Jet_2b_M");
  plotlist.push_back("4Jet_1b_M/"+VarList[m]+"4Jet_1b_M");
  plotlist.push_back("4Jet_2b_M/"+VarList[m]+"4Jet_2b_M");

  for(int i=0; i<(plotlist.size()/2); i++){//loop for all the plots we wan to
   
    THStack Wp600Stack;
    THStack Wp1000Stack;
    vector <TH1F* > histos;
   
    
    
    for(int file=0; file<5; file++){
      std::stringstream dir;
      cout<<namelist[file]<<endl;
      dir<<namelist[file];
      TH1F* temp;
      TH1F* tempa;
      TH1F* tempb;
      
      tempa = (TH1F*) filelist[file]->Get(plotlist[i].c_str());
      temp =  (TH1F*) tempa->Rebin(6, "temp");
      TH1F* temp2;
      tempb = (TH1F*) filelist[file]->Get(plotlist[i+plotlist.size()/2].c_str());
      temp2 = (TH1F*) tempb->Rebin(6,"temp2");
      temp->Add(temp2);
      float scale = (1.0/nEvtTot[file])*DataLumi[file]*McXsec[file];
      
      temp->Scale(scale);
      
      //temp->Draw("SAME");
      temp->SetLineColor(file+1);
      //temp->SetFillColor(file+1);
      temp->SetLineWidth(2);
      //temp->GetXaxis()->SetRangeUser(0,300);
if(file==4) temp->SetLineColor(46);
      /* if(file==4){
	temp->Sumw2();
	temp->SetMarkerStyle(23);
	temp->SetLineColor(12);
	}*/
      histos.push_back(temp);
      //leg->AddEntry(temp, namelist[file].c_str(),"lep");
     

     
      
    }
   
    Wp600Stack.Add(histos[0]);  Wp600Stack.Add(histos[1]);
    std::stringstream cn1;
     cn1<<plotlist[i]<<"_Wprime600";
     TCanvas* c1= new TCanvas((cn1.str()).c_str(),(cn1.str()).c_str(),800,600);
    TLegend *leg = new TLegend(0.7060302,0.7692308,0.9761307,0.972028,NULL,"brNDC");
    leg->AddEntry(histos[0], namelist[0].c_str(),"lep");
    leg->AddEntry(histos[1], namelist[1].c_str(),"lep");
    leg->AddEntry(histos[2], namelist[2].c_str(),"lep");
    leg->AddEntry(histos[3], namelist[3].c_str(),"lep");
    leg->AddEntry(histos[4], namelist[4].c_str(),"lep");
    //comment next line in for seeing stacked plots
    Wp600Stack.Draw("hist");
     //Wp600Stack.GetXaxis()->SetRangeUser(0,300);
     Wp600Stack.SetTitle(plotlist[i].c_str());
     //comment these in to just make overlayed plots
     // histos[0]->Draw();
     //histos[1]->Draw("same");
     //histos[2]->Draw("same");
     //histos[3]->Draw("same");
     //histos[4]->Draw("same");

     leg->Draw();
     fnew1.cd();
     c1->Write();
     std::stringstream gif;
     gif<<plotlist[i]<<"_Wp600_e_delphi_120.gif";
     
     c1->SaveAs((gif.str()).c_str());
     
     
     std::stringstream cn2;
     cn2<<plotlist[i]<<"_Wprime1000";
     TCanvas* c2= new TCanvas(((cn2.str()).c_str()),((cn2.str()).c_str()),800,600);
     TLegend *leg2 = new TLegend(0.7060302,0.7692308,0.9761307,0.972028,NULL,"brNDC");
     leg2->AddEntry(histos[0], namelist[0].c_str(),"lep");
     
     leg2->AddEntry(histos[1], namelist[1].c_str(),"lep");
     leg2->AddEntry(histos[3], namelist[3].c_str(),"lep");
     Wp1000Stack.Add(histos[1]);  Wp1000Stack.Add(histos[0]); Wp1000Stack.Add(histos[3]);
     Wp1000Stack.Draw("hist");
     //Wp1000Stack.GetXaxis()->SetRangeUser(0,500);
     Wp1000Stack.SetTitle(plotlist[i].c_str());
     
    leg2->Draw();
    fnew1.cd();
     std::stringstream gif2;
    gif2<<plotlist[i]<<"_Wprime1000_e_delphi_120.gif";
    c2->Write();
    c2->SaveAs((gif2.str()).c_str());
    //      temp_Mjj->Wr
  }
} 
} 


