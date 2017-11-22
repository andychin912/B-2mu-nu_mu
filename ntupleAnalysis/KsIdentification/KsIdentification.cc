#include <iostream>
using namespace std;
void KsIdentification()
{
   TFile *f1 = new TFile("~/B+2mu+nu_mu/temp/20171117_B+2mu+nu_mu_1.root");
   TTree *Ks;

   f1->GetObject("Ks",Ks);

   TH1F *h1=new TH1F("h1","",1000,0,0.1);
   TH1F *h2=new TH1F("h2","",1000,0,0.1);

   //save to Ntuple
   Ks->Draw("pow(K_S0_VertexZDist,0.25)>>h1","K_S0_mcErrors==0");
   Ks->Draw("pow(K_S0_VertexZDist,0.25)>>h2","K_S0_mcErrors!=0");


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

   h1->SetLineColor(kBlue);
   h1->SetLineWidth(2);
   h1->Draw("same");


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
