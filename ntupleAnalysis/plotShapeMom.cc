#include <iostream>
using namespace std;
void plotShapeMom()
{
   TFile *f1 = new TFile("MC9.root");
   TTree *y4s;

   f1->GetObject("y4s",y4s);

   TH1F *h0=new TH1F("h0","signal mu p* [GeV]",100,2.2,3.1);
   TH1F *h1=new TH1F("h1","signal mu p* [GeV]",100,2.2,3.1);
   TH1F *h2=new TH1F("h2","signal mu p* [GeV]",100,2.2,3.1);
   TH1F *h3=new TH1F("h3","signal mu p* [GeV]",100,2.2,3.1);
   TH1F *h4=new TH1F("h4","signal mu p* [GeV]",100,2.2,3.1);
   TH1F *h5=new TH1F("h5","signal mu p* [GeV]",100,2.2,3.1);

   //apply cuts 
   y4s->Draw("useCMSFrameLPdaughterLP1COpRPRP>>h0","(Flag==0)*Scale*900");
   y4s->Draw("useCMSFrameLPdaughterLP1COpRPRP>>h1","(Flag==1)*Scale");
   y4s->Draw("useCMSFrameLPdaughterLP1COpRPRP>>h2","(Flag==2)*Scale");
   y4s->Draw("useCMSFrameLPdaughterLP1COpRPRP>>h3","(Flag==3)*Scale");
   y4s->Draw("useCMSFrameLPdaughterLP1COpRPRP>>h4","(Flag==4)*Scale");
   y4s->Draw("useCMSFrameLPdaughterLP1COpRPRP>>h5","(Flag>=6)*Scale","B");

   h2->Add(h1);
   h3->Add(h2);
   h4->Add(h3);
   h5->Add(h4);


   //plot
   TCanvas *c1 = new TCanvas("c1","",1);


   c1->SetFillColor(0);
   c1->SetFrameFillColor(0);
   c1->SetFrameLineWidth(2);
   c1->SetFillStyle(4000);
   c1->SetFrameFillStyle(4000);
   //gStyle->SetOptTitle(0);
   gStyle->SetOptStat(kFALSE);
   //gPad->SetLogy();

   h5->SetMinimum(0);

   h5->SetFillColor(1);
   h5->SetLineColor(1);
   h5->Draw("HIST B");

   h4->SetFillColor(7);
   h4->SetLineColor(7);
   h4->Draw("B same");

   h3->SetFillColor(8);
   h3->SetLineColor(8);
   h3->Draw("B same");

   h2->SetFillColor(9);
   h2->SetLineColor(9);
   h2->Draw("B same");

   h1->SetFillColor(46);
   h1->SetLineColor(46);
   h1->Draw("B same");

   h0->SetLineColor(1);
   h0->SetLineWidth(2);
   h0->Draw("HIST same");

   //h3->Add(h2);


   //h2->GetXaxis()->SetTitle("P [GeV]");
   //h2->GetYaxis()->SetTitle("Entries/1 MeV");
   //h2->GetYaxis()->SetTitleOffset(1.4);
   //h2->GetXaxis()->SetTitleSize(0.045);

   //gStyle->SetOptTitle(0);
   //gStyle->SetOptStat(kFALSE);

   TLegend *leg = new TLegend(0.75,0.7,1,0.87);//legend
   leg->SetHeader("p* [GeV]");
   leg->SetTextSize(0.025);
   leg->AddEntry(h0,"signal*2000","l");
   leg->AddEntry(h1,"bb","f");
   leg->AddEntry(h2,"uu+dd+ss","f");
   leg->AddEntry(h3,"cc","f");
   leg->AddEntry(h4,"taupair","f");
   leg->AddEntry(h5,"QED+two photon","f");
   leg->Draw("same");

   c1->SaveAs("~/Ntuples/Mom.eps");


}
