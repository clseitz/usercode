//////////////////////////////////////////////////////////////////////////
//
// 'SPECIAL PDFS' RooFit tutorial macro #706
// 
// Histogram based p.d.f.s and functions
//
//
//
// 07/2008 - Wouter Verkerke 
// 
/////////////////////////////////////////////////////////////////////////

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
//#include "RooRealVar.h"
//#include "RooDataSet.h"
//#include "RooGaussian.h"
//#include "RooConstVar.h"
//#include "RooPolynomial.h"
//#include "RooHistPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TFile.h"
#include "TVector.h"
//#include "RooPlot.h"
using namespace RooFit ;


void fit_CMS_top()
{
  // C r e a t e   p d f   f o r   s a m p l i n g 
  // ---------------------------------------------


RooRealVar pt("pt","pt",20,160) ;
 RooRealVar eta("eta","eta",-2.1,2.1) ;
 RooRealVar nsig("nsig","nsig",100,-2000,2000) ;
 RooRealVar nbgk("nbgk","nbgk",100,-2000,2000) ;
 RooRealVar nqcd("nqcd","nqcd",156,-1000,1000) ;

RooRealVar Mjjj("Mjjj","Mjjj",0,900) 

 TVectorT<Double_t > v_nsig;
 TVectorT<Double_t > v_nbg;
  TVectorT<Double_t > v_wj;

// Construct Gaussian constraint p.d.f on parameter f at 0.8 with resolution of 0.1
  RooGaussian fconstraint("fconstraint","fconstraint",nqcd,RooConst(156),RooConst(156)) ;

TFile *f1 = new TFile("ttbar_skim_plots.root");
TFile *f2 = new TFile("wjets_skim_plots.root");
 TFile *f3 = new TFile("mu_skim_plots.root");
 




 TH1F*  Diagcut100_tt = (TH1F*) f1->Get("Diagcut_100");
 Diagcut100_tt->Rebin(20);
 float int_tt=Diagcut100_tt->Integral(0,40);
 float scale_tt=157.5*36*int_tt/1306182;
 Diagcut100_tt->Scale(scale_tt/int_tt);
RooDataHist*  Diagcut100_tt_roo = new RooDataHist("Diagcut100_tt_roo","",Mjjj, Diagcut100_tt);
TH1F*  Diagcut100_wj = (TH1F*) f2->Get("Diagcut_100");
 Diagcut100_wj->Rebin(20);
float int_wj=Diagcut100_wj->Integral(0,40);
 float scale_wj=31314*36*int_wj/14805546;
 Diagcut100_wj->Scale(scale_wj/int_wj);
RooDataHist*  Diagcut100_wj_roo = new RooDataHist("Diagcut100_wj_roo","",Mjjj, Diagcut100_wj);

TH1F*  Diagcut100_mu = (TH1F*) f3->Get("Diagcut_100");
 Diagcut100_mu->Rebin(20);
RooDataHist*  Diagcut100_mu_roo = new RooDataHist("Diagcut100_mu_roo","",Mjjj, Diagcut100_mu);
 TCanvas* c1 = new TCanvas("c1","r1f706_histpdf",900,700) ;
 c1->cd() ;
Diagcut100_mu->Draw("ep");
 Diagcut100_tt->Draw("SAME");
 
 Diagcut100_tt->Add(Diagcut100_wj);
 Diagcut100_tt->SetFillColor(kRed);

 Diagcut100_wj->SetFillColor(kGreen-1);
Diagcut100_wj->Draw("same");

Diagcut100_mu->Draw("Sameep");

RooHistPdf Diagcut100_wj_roo_pdf("Diagcut100_wj_roo","Diagcut100_wj_roo",Mjjj,*Diagcut100_wj_roo,0) ;
RooHistPdf Diagcut100_tt_roo_pdf("Diagcut100_tt_roo","Diagcut100_tt_roo",Mjjj,*Diagcut100_tt_roo,0) ;
RooHistPdf Diagcut100_mu_roo_pdf("Diagcut100_mu_roo","Diagcut100_mu_roo",Mjjj,*Diagcut100_mu_roo,0) ;

  // C r e a t e   l o w   s t a t s   h i s t o g r a m
  // ---------------------------------------------------

  

  // Represent data in dh as pdf in x
// RooHistPdf histpdf1("histpdf1","histpdf1",x,*hist1,0) ;




 RooAddPdf*  pdf_Diagcut100 = new RooAddPdf("pdf_Diagcut100","pdf_Diagcut100", RooArgList(Diagcut100_tt_roo_pdf,Diagcut100_wj_roo_pdf), RooArgList(nsig,nbgk));
 //pdf_Diagcut100.fitTo(*Diagcut100_mu_roo);
 // v_nsig.push_back(nsig.getVal());
 RooPlot* framea = Mjjj.frame(Title("Diagcut100 muon dataset 35 fb^{-1}")) ;
 Diagcut100_mu_roo.plotOn(framea);
 

 pdf_Diagcut100.plotOn(framea,DrawOption("F"),RooFit::Name("wj_tt"),RooFit::FillColor(kRed),RooFit::LineColor(kRed),Components(RooArgSet(Diagcut100_wj_roo_pdf,Diagcut100_tt_roo_pdf)));
 pdf_Diagcut100.plotOn(framea,DrawOption("F"),RooFit::Name("wj"),RooFit::FillColor(kGreen-1),RooFit::LineColor(kGreen-1),Components(RooArgSet(Diagcut100_wj_roo_pdf)));

Diagcut100_mu_roo.plotOn(framea);
 //mPt3jets_tt_roo_pdf.plotOn(framea,RooFit::LineColor(kBlue));
 //mPt3jets_wj_roo_pdf.plotOn(framea,RooFit::LineColor(kOrange));
 //mPt3jets_qcd_roo_pdf.plotOn(framea,RooFit::LineColor(kBlack));



 

 TCanvas* c2 = new TCanvas("c2","rf706_histpdf",900,700) ;
 c2->cd() ; gPad->SetLeftMargin(0.15) ; framea->GetYaxis()->SetTitleOffset(1.4) ; framea->Draw() ;
 l = new TLegend(0.8,0.7,0.48,0.9);
 l.AddEntry(Diagcut100_mu_roo,"Data", "lep");
 l.AddEntry("tt","t\\bar{t}","f");
 l.AddEntry("wj_tt","W+Jets","f");
c2->cd() ;
 l.Draw();

 



}


