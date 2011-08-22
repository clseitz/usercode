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
#include "math.h"

void CountMjjj(TH1F *temp_diagcut,float diag, float i){
	 

}
void make_asym()
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
  
  filelist.push_back(TFile::Open("../TTBar_plots_St600.root"));
  namelist.push_back("TTbarJEts_e");
  //nEvtTot.push_back(216095.0);
  nEvtTot.push_back(3.6838e+06);
  McXsec.push_back(157.5);
  DataLumi.push_back(lumi);

  filelist.push_back(TFile::Open("../TTBar_plots_St600.root"));
  namelist.push_back("TTbarJEts_e");
  //nEvtTot.push_back(216095.0);
  nEvtTot.push_back(3.6838e+06);
  McXsec.push_back(0);
  DataLumi.push_back(lumi);
  /* filelist.push_back(TFile::Open("/uscms_data/d3/clseitz/WJets/WJets_LeptonANA_e_vec_delphi_120.root"));
  nEvtTot.push_back(4.5972e+07);
  namelist.push_back("WJets_e");
  McXsec.push_back(31314.0);
  DataLumi.push_back(lumi);
  */

  filelist.push_back(TFile::Open("../Wp600_plots_St600.root"));
  namelist.push_back("Wp600_e");
  nEvtTot.push_back(99987.0);
  McXsec.push_back(0.0);
  DataLumi.push_back(lumi);
  filelist.push_back(TFile::Open("../Wp600_plots_St600.root"));
  namelist.push_back("Wp1000_e");
  nEvtTot.push_back(99995.0);
  McXsec.push_back(0.0);
  DataLumi.push_back(lumi);
  
  //filelist.push_back(TFile::Open("/cms/data24/clseitz/MC_4_2_4/Sbottom/Sbottom750_neutralino150_LeptonAna_e25_met30_b12.root"));

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

 //VarList.push_back("TransMassLepMET4Jet_vs_LeadingJetPt_");

  


  TFile fnew1("ttbar_asym_plots.root", "recreate");
  
  for(int m=0; m<VarList.size(); m++){
    vector <string > plotlist;
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
   
    vector <TH1F* > histosP;
    vector <TH1F* > histosM;
    
    for(int file=0; file<4; file++){
      std::stringstream dir;
      cout<<namelist[file]<<endl;
      dir<<namelist[file];
      TH1F* temp;
      TH1F* tempa;
      TH1F* tempb;
      cout<<plotlist[i]<<endl;
      tempa = (TH1F*) filelist[file]->Get(plotlist[i].c_str());
      temp =  (TH1F*) tempa->Rebin(4, "temp");
      TH1F* temp2;
      tempb = (TH1F*) filelist[file]->Get(plotlist[i+plotlist.size()/2].c_str());
      temp2 = (TH1F*) tempb->Rebin(4,"temp2");
      //temp->Add(temp2);
      float scale = (1.0/nEvtTot[file])*DataLumi[file]*McXsec[file];
      temp->Scale(scale);
      temp2->Scale(scale);
      //TH1F* Asym;

      //temp->Draw("SAME");
      temp->SetLineColor(1);
      //temp->SetFillColor(file+1);
      temp->SetLineWidth(2);
      temp2->SetLineColor(2);
      //temp->SetFillColor(file+1);
      temp2->SetLineWidth(2);
      //temp->GetXaxis()->SetRangeUser(0,300);

      if(file==4){
	temp->Sumw2();
	temp->SetMarkerStyle(23);
	temp->SetLineColor(12);
      }
      histos.push_back(temp);
      histosP.push_back(temp);
      histosM.push_back(temp2);
      //leg->AddEntry(temp, namelist[file].c_str(),"lep");
     

     
      
    }
   
    Wp600Stack.Add(histos[1]);
    Wp600Stack.Add(histos[0]); 
    Wp600Stack.Add(histos[2]);
    std::stringstream cn1;
     cn1<<plotlist[i]<<"_Wprime600";
  
     //c1->SaveAs((gif.str()).c_str());

    
     //Make asymmetry plots
     THStack Wp600StackP; THStack Wp600StackM;

     Wp600StackP.Add(histosP[0]);
     Wp600StackP.Add(histosP[1]); 
     Wp600StackP.Add(histosP[2]);

     Wp600StackM.Add(histosM[0]);
     Wp600StackM.Add(histosM[1]); 
     Wp600StackM.Add(histosM[2]);
     TCanvas* c2= new TCanvas((cn1.str()).c_str(),(cn1.str()).c_str(),800,600);
     Wp600StackP.Draw("hist");
     Wp600StackM.Draw("histsame");
     TLegend *leg = new TLegend(0.7060302,0.7692308,0.9761307,0.972028,NULL,"brNDC");
     leg->AddEntry(histosP[1], "postive","lep");
     leg->AddEntry(histosM[1], "negative","lep");
    // leg->AddEntry(histos[2], namelist[2].c_str(),"lep");
    leg->Draw();
     fnew1.cd();
     c2->Write();
     TH1F* Asym;
     Asym = (TH1F*) histosP[2]->Clone();
     
     for (int k=1; k<histosP[2]->GetNbinsX()-1; k++){
       //cout<<"loop"<<endl;
       Float_t binP = ((TH1*)(Wp600StackP.GetStack()->Last()))->GetBinContent(k);
       Float_t binM = ((TH1*)(Wp600StackM.GetStack()->Last()))->GetBinContent(k);
       Float_t binE=0;
       float ratio=0;
       if(binP!=0 && binM!=0){
       ratio=(binP-binM)/(binP+binM);
       //binE=2*sqrt((binM*binP)/pow(binM + binP,3));
       binE=0.02;
       cout<<ratio<<" "<<binP<<" "<<binM<<endl;
       }
       else ratio=0;
       Asym->SetBinContent(k,ratio);
       Asym->SetBinError(k,binE);
			     
     }
     fnew1.cd();
     Asym->SetTitle(plotlist[i].c_str());
     Asym->SetName(plotlist[i].c_str());
     Asym->Write();
     
     
     /*
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
    */
  } 
} 
} 


