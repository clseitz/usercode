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
  
  filelist.push_back(TFile::Open("/uscms_data/d3/clseitz/TTBarJets/TTbarJets_LeptonANA_e_test.root"));
  namelist.push_back("TTbarJEts");
  //nEvtTot.push_back(216095.0);
  nEvtTot.push_back(3701936.0);
  McXsec.push_back(157);
  DataLumi.push_back(lumi);
 
  plotlist.push_back("Event/NumEvtCut");
  cutlist.push_back("All events         ");
  cutlist.push_back("exactly one lepton ");
  cutlist.push_back("Electron $>$ 25 GeV  "); 
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
  cout<<"\\begin{tabular}{|l|c|}"<<endl;
  cout<<"{\\bf Cut}&{\\bf Nevents normalized to 1 $fb^{-1}$}\\\\ \\hline"<<endl;
  for(int file=0; file<1; file++){
    TH1F* temp;
    temp = (TH1F*) filelist[file]->Get(plotlist[0].c_str());
    //make latex output 
   
    cout<<"Sample & "<<namelist[file]<<"\\\\ \\hline"<<endl;
    cout<<"Events unscaled & "<<temp->GetBinContent(1)<<"\\\\ \\hline"<<endl;

    for(int i=1; i<=cutlist.size();i++){
      cout<<cutlist[i-1]<<"& "<< round(temp->GetBinContent(i)*(1.0/temp->GetBinContent(1)*DataLumi[file]*McXsec[file]))<<"\\\\ \\hline"<<endl;
    }
    
  }
  cout<<"\\end{tabular}"<<endl;
  cout<<"\\end{table}  "<<endl;
  cout<<"\\end{document}"<<endl;
  
} 


