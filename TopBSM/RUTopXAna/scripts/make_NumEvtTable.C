#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TObject.h"
#include <sstream>



void CountMjjj(TH1F *temp_diagcut,float diag, float i){
	 

}
void make_NumEvtTable()
{
  float lumi=1000.;
  vector <string > namelist;
  vector <string > plotlist;
  vector <string > cutlist;
  vector <TFile* > data;
  vector <TFile* > filelist;
  vector<float> nEvtTot;
  vector<float> McXsec;
  vector<float> DataLumi;
  //file 0-3 are the files to fit
  
  filelist.push_back(TFile::Open("/uscms_data/d3/clseitz/TTBarJets/TTbarJets_LeptonANA_mu.root"));
  namelist.push_back("TTbarJEts");
   McXsec.push_back(157.5);
  DataLumi.push_back(lumi);

   filelist.push_back(TFile::Open("/uscms_data/d3/clseitz/WJets/WJets_LeptonANA_mu.root"));
  namelist.push_back("WJets");
   McXsec.push_back(31314.0);
  DataLumi.push_back(lumi);


  filelist.push_back(TFile::Open("/uscms_data/d3/clseitz/WprimeHexcms/Wp600_CMS_LeptonANA_mu25_met30_b12.root"));
  namelist.push_back("Wprim600");
  McXsec.push_back(8.0);
  DataLumi.push_back(lumi);
  
 filelist.push_back(TFile::Open("/uscms_data/d3/clseitz/WprimeHexcms/Wp1000_CMS_LeptonANA_mu25_met30_b12.root"));
  namelist.push_back("Wprime1000");
  McXsec.push_back(0.72);
  DataLumi.push_back(lumi);

  plotlist.push_back("Event/NumEvtCut");
  cutlist.push_back("All events         ");
  cutlist.push_back("exactly one lepton ");
  cutlist.push_back("Muon $>$ 25 GeV  "); 
  cutlist.push_back("MET $>$ 30  GeV            ");   
  cutlist.push_back("$>=$ 1 jet           "); 
  cutlist.push_back("$>=$ 2 jet            ");
  cutlist.push_back("$>=$ 1 jet and $>=$ 1b    ");
  cutlist.push_back("$>=$ 3 jet            ");
  cutlist.push_back("$>=$ 4 jet            ");    
  cutlist.push_back("$>=$ 5 jet            ");



  cout<<"--------------LATEX-------------"<<endl;
  cout<<"\\documentclass[12pt,twoside,letterpaper]{article}"<<endl;
  cout<<"\\usepackage{amsmath}"<<endl;
  cout<<"\\begin{document}"<<endl;
  cout<<"\\begin{table}[htdp]"<<endl; 
  cout<<"\\begin{tabular}{|l|c|c|c|c}"<<endl;
  cout<<"{\\bf Cut}&{\\bf scaled to 1 $fb^{-1}$}\\\\ \\hline"<<endl;
    TH1F* TTbar;
    TTbar = (TH1F*) filelist[0]->Get(plotlist[0].c_str());
    TH1F* WJets;
    WJets = (TH1F*) filelist[1]->Get(plotlist[0].c_str());
    TH1F* Wp600;
    Wp600 = (TH1F*) filelist[2]->Get(plotlist[0].c_str());
    TH1F* Wp1000;
    Wp1000 = (TH1F*) filelist[3]->Get(plotlist[0].c_str());

    //make latex output 
   
    cout<<"Sample & "<<namelist[0]<< "& "<<namelist[1]<< " & "<<namelist[2]<< " & "<<namelist[3]<<"\\\\ \\hline"<<endl;
    cout<<"Events unscaled & "<<TTbar->GetBinContent(1)<<" & "<<WJets->GetBinContent(1)<<" & "<<Wp600->GetBinContent(1)<<" & "<<Wp1000->GetBinContent(1)<<"\\\\ \\hline"<<endl;

    for(int i=1; i<=cutlist.size();i++){
      cout<<cutlist[i-1]<<" & "<< round(TTbar->GetBinContent(i)*(1.0/TTbar->GetBinContent(1)*DataLumi[0]*McXsec[0]))<<" & "<< round(WJets->GetBinContent(i)*(1.0/WJets->GetBinContent(1)*DataLumi[1]*McXsec[1]))<<" & "<< round(Wp600->GetBinContent(i)*(1.0/Wp600->GetBinContent(1)*DataLumi[2]*McXsec[2]))<<" & "<< round(Wp1000->GetBinContent(i)*(1.0/Wp1000->GetBinContent(1)*DataLumi[3]*McXsec[3]))<<"\\\\ \\hline"<<endl;
    }
    
 
  cout<<"\\end{tabular}"<<endl;
  cout<<"\\end{table}  "<<endl;
  cout<<"\\end{document}"<<endl;
  
} 


