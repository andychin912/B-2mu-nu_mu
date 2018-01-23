#include <iostream>
using namespace std;
void KsIdentification()
{
   TFile *f1 = new TFile("~/B+2mu+nu_mu/temp/20171124_B+2mu+nu_mu_ccbar000_9.root");
   TTree *Ks;

   f1->GetObject("Ks",Ks);

   TH1F *h1=new TH1F("h1","",100,0,1);
   TH1F *h2=new TH1F("h2","",100,0,1);

   //save to Ntuple
   Ks->Draw("sqrt(pow((K_S0_P4[3]),2)-pow(K_S0_P,2))>>h1","K_S0_mcErrors==0");
   Ks->Draw("sqrt(pow((K_S0_P4[3]),2)-pow(K_S0_P,2))>>h2","K_S0_mcErrors!=0");


   //plot mcErrors and mcTruth
   TCanvas *c1 = new TCanvas("c1","",1);



   c1->SetFillColor(0);
   c1->SetFrameFillColor(0);
   c1->SetFrameLineWidth(2);
   c1->SetFillStyle(4000);
   c1->SetFrameFillStyle(4000);


   h2->SetLineColor(kBlack);
   h2->SetLineWidth(2);
   h2->Draw();
   TCanvas *c2 = new TCanvas("c2","",1);


   c2->SetFillColor(0);
   c2->SetFrameFillColor(0);
   c2->SetFrameLineWidth(2);
   c2->SetFillStyle(4000);
   c2->SetFrameFillStyle(4000);

   h1->SetLineColor(kBlue);
   h1->SetLineWidth(2);
   h1->Draw();


   h2->GetXaxis()->SetTitle("P [GeV]");
   h2->GetYaxis()->SetTitle("Entries/1 MeV");
   h2->GetYaxis()->SetTitleOffset(1.4);
   h2->GetXaxis()->SetTitleSize(0.045);

   gStyle->SetOptTitle(0);
   gStyle->SetOptStat(kFALSE);

   leg = new TLegend(0.65,0.7,0.83,0.87);//legend
   leg->SetHeader("P distribution");
   leg->SetTextSize(0.025);
   leg->AddEntry(h1,"signal","l");
   leg->AddEntry(h2,"all the other tracks","l");
   leg->Draw("same");

   
   

 

}
