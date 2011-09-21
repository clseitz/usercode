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
void make_asym_MC()
{
  float lumi=2000.;
  vector <string > namelist;
  
  vector <string > VarList;
  vector <TFile* > data;
  vector <TFile* > filelist;
  vector<float> nEvtTot;
  vector<float> McXsec;
  vector<float> DataLumi;
vector <TH1F* > v_Asym;
  
  filelist.push_back(TFile::Open("../Wp600_plots_additionalCuts.root"));
  namelist.push_back("Wp600_e");
  nEvtTot.push_back(99987.0);
  McXsec.push_back(0.0);
  DataLumi.push_back(lumi);

  filelist.push_back(TFile::Open("../Wp600_plots_additionalCuts.root"));
  namelist.push_back("Wp600_e");
  nEvtTot.push_back(99987.0);
  McXsec.push_back(0.0);
  DataLumi.push_back(lumi);

  filelist.push_back(TFile::Open("../Wp600_plots_additionalCuts.root"));
  namelist.push_back("Wp600_e");
  nEvtTot.push_back(99987.0);
  McXsec.push_back(8.0);
  DataLumi.push_back(lumi);

  filelist.push_back(TFile::Open("../Wp600_plots_additionalCuts.root"));
  namelist.push_back("Wp600_e");
  nEvtTot.push_back(99987.0);
  McXsec.push_back(0.0);
  DataLumi.push_back(lumi);



  /*
  filelist.push_back(TFile::Open("../Sbottom750_plots.root"));
  namelist.push_back("Sbottom750_e");
  nEvtTot.push_back(78000.0);
  McXsec.push_back(8.0);
  DataLumi.push_back(lumi);
 filelist.push_back(TFile::Open("../Stop350_plots.root"));
  namelist.push_back("Stop350_e");
  nEvtTot.push_back(10000.0);
  McXsec.push_back(0.72);
  DataLumi.push_back(lumi);
  */

  


 VarList.push_back("MCwprimeMass");
 VarList.push_back("MCwprimeMETMass");
 VarList.push_back("MCPhidLepTop");
 VarList.push_back("minChi2");

 //VarList.push_back("TransMassLepMET4Jet_vs_LeadingJetPt_");

  


  TFile fnew1("wpMC_asym_plots.root", "recreate");
  
  for(int m=0; m<VarList.size(); m++){
    vector <string > plotlist;

    //COMMENT ALL IN if you want to look at other variables but then the added asymmetry doesn't work
  plotlist.push_back("MCwprime/"+VarList[m]+"Pos");
  plotlist.push_back("MCwprime/"+VarList[m]+"Neg");
  // plotlist.push_back("5Jet_2b_M/"+VarList[m]+"5Jet_2b_M");
  //plotlist.push_back("4Jet_1b_M/"+VarList[m]+"4Jet_1b_M");
  //plotlist.push_back("4Jet_2b_M/"+VarList[m]+"4Jet_2b_M");

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
      cout<<"got it"<<endl;
      temp =  (TH1F*) tempa->Rebin(2, "temp");
      TH1F* temp2;
      tempb = (TH1F*) filelist[file]->Get(plotlist[i+plotlist.size()/2].c_str());
      cout<<"got 2it"<<endl;
      temp2 = (TH1F*) tempb->Rebin(2,"temp2");
      //temp->Add(temp2);
      float scale = (1.0/nEvtTot[file])*DataLumi[file]*McXsec[file];
      //temp->Scale(scale);
      //temp2->Scale(scale);
	
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
     //TCanvas* c2= new TCanvas((cn1.str()).c_str(),(cn1.str()).c_str(),800,600);
     //Wp600StackM.Draw("hist");    
     //Wp600StackP.Draw("histsame");
    
     TLegend *leg = new TLegend(0.7060302,0.7692308,0.9761307,0.972028,NULL,"brNDC");
     leg->AddEntry(histosP[1], "postive","lep");
     leg->AddEntry(histosM[1], "negative","lep");
    // leg->AddEntry(histos[2], namelist[2].c_str(),"lep");
    leg->Draw();
     fnew1.cd();
     
     TH1F* Asym;
     Asym = (TH1F*) histosP[2]->Clone();
     TH1F* Pos;
     Pos = (TH1F*) histosP[2]->Clone();
     TH1F* Neg;
     Neg = (TH1F*) histosP[2]->Clone();
     /*for (int k=1; k<histosP[2]->GetNbinsX()-1; k++){
       //cout<<"loop"<<endl;
       Float_t binP = ((TH1*)(Wp600StackP.GetStack()->Last()))->GetBinContent(k);
       Float_t binM = ((TH1*)(Wp600StackM.GetStack()->Last()))->GetBinContent(k);
       Float_t binE=0;
       float ratio=0;
       if(binP!=0 && binM!=0){
       ratio=(binP-binM)/(binP+binM);
       binE=2*sqrt((binM*binP)/pow(binM + binP,3));
       //binE=0.02;
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
     */
     for (int k=1; k<histosP[2]->GetNbinsX()-1; k++){
       //cout<<"loop"<<endl;
       float scale_tt = (1.0/nEvtTot[0])*DataLumi[0]*McXsec[0];
       float scale_wp = (1.0/nEvtTot[2])*DataLumi[2]*McXsec[2];
       float EP_tt=sqrt(histosP[0]->GetBinContent(k));
       float EP_wp=sqrt(histosP[2]->GetBinContent(k));
       float EM_tt=sqrt(histosM[0]->GetBinContent(k));
       float EM_wp=sqrt(histosM[2]->GetBinContent(k));
       float BP_tt=histosP[0]->GetBinContent(k);
       float BP_wp=histosP[2]->GetBinContent(k);
       float BM_tt=histosM[0]->GetBinContent(k);
       float BM_wp=histosM[2]->GetBinContent(k);

      
       float binP = 0;
       float binM = 0;
       //cout<<scale_tt<<" "<<BP_tt<<" "<<EP_tt<<endl;
       // cout<<binP_E<<endl;
       float binE=0;
       float ratio=0;
       if(BP_tt!=0 && BP_wp!=0 && BM_tt!=0 && BM_wp!=0){
	 binP = scale_tt*BP_tt+scale_wp*BP_wp;
	 binM =  scale_tt*BM_tt+scale_wp*BM_wp;
	 cout<<scale_tt<<" "<<BP_tt<<" "<<EP_tt<<" "<<scale_wp<<" "<<BP_wp<<" "<<EP_wp<<endl;
	 float binP_E=sqrt(pow(scale_tt*BP_tt/EP_tt,2)+pow(scale_wp*BP_wp/EP_wp,2));
	 float binM_E=sqrt(pow(scale_tt*BM_tt/EM_tt,2)+pow(scale_wp*BM_wp/EM_wp,2));
	
	 //if(m==VarList.size()-1) ratio=(-binP+binM)/(binP+binM);
	 //else  ratio=(binP-binM)/(binP+binM);
	 //Real Errors from MC statistics
	 //binE=2*sqrt((pow(binM_E,2)*pow(binP,2) + pow(binM,2)*pow(binP_E,2))/pow(binM + binP,4));
	 //Error as would be seen in data just sqrt(binContent)
	 binE=2*sqrt((binM*binP)/pow(binM + binP,3));
	 ratio=(binP-binM)/(binP+binM);
	 //binE=0.02;
	 //cout<<ratio<<" "<<binE<<" "<<binP<<" "<<binM<<" "<<binM_E<<" "<<binP_E<<endl;
       }
       else ratio=0;

       Asym->SetBinContent(k,ratio);
       Asym->SetBinError(k,binE);
       Pos->SetBinContent(k,binP);
       Neg->SetBinContent(k,binM);
			     
     }
     fnew1.cd();
     Asym->SetTitle(plotlist[i].c_str());
     Asym->SetName(plotlist[i].c_str());
     Asym->Write();
     v_Asym.push_back(Asym);
      TCanvas* c2= new TCanvas((cn1.str()).c_str(),(cn1.str()).c_str(),800,600);
      Pos->SetLineColor(1); Neg->SetLineColor(2);
      Neg->Draw();
      Pos->Draw("same");
      
      c2->Write();
     
    
  } 
}
  /*TH1F* temp1;
 temp1 = (TH1F*) v_Asym[v_Asym.size()-2]->Clone(); 
TH1F* temp2;
 temp2 = (TH1F*) v_Asym[v_Asym.size()-1]->Clone(); 
TH1F* AddAsym;
 AddAsym = (TH1F*) v_Asym[v_Asym.size()-2]->Clone();
 for (int k=1; k< temp1->GetNbinsX()-1; k++){
   AddAsym->SetBinContent(k,temp1->GetBinContent(k)+temp2->GetBinContent(k));
   float error=sqrt(pow(temp1->GetBinError(k),2)+pow(temp2->GetBinError(k),2));
   AddAsym->SetBinError(k,error);
 }
     //AddAsym->Add(v_Asym[v_Asym.size()-1]);
 AddAsym->SetTitle("adding asymmetry");	 
 AddAsym->SetName("adding_asymmetry");	 
 AddAsym->Write();
  */    
} 


