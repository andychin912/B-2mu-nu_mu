#include <iostream>
using namespace std;
void CMSskimimpactpid_efficiency()
{
   TFile *f1 = new TFile("~/B+2mu+nu_mu/20171018_B+2mu+nu_mu_2_CMSframenoskim.root");
   TFile *f2 = new TFile("~/B+2mu+nu_mu/20171018_B+2mu+nu_mu_3_CMSframe.root");
   TTree *muon1;
   TTree *muon2;

   f1->GetObject("muon",muon1);
   f2->GetObject("muon",muon2);

   TH1F *h1=new TH1F("h1","",5000,0,5);
   TH1F *h2=new TH1F("h2","",5000,0,5);
   TH1F *h3=new TH1F("h3","",3000,2,3.5);
   TH1F *h4=new TH1F("h4","",3000,2,3.5);

   //apply cuts 
   muon1->Draw("B_mu_useCMSFrame__bop__bc>>h1","B_mu_mcErrors==0&&(B_mcErrors==8||B_mcErrors==1032)");
   muon1->Draw("B_mu_useCMSFrame__bop__bc>>h2");
   muon2->Draw("B_mu_useCMSFrame__bop__bc>>h3","B_mu_mcErrors==0&&(B_mcErrors==8||B_mcErrors==1032)");
   muon2->Draw("B_mu_useCMSFrame__bop__bc>>h4");


   //plot before skim
   TCanvas *c1 = new TCanvas("c1","",1);


   c1->SetFillColor(0);
   c1->SetFrameFillColor(0);
   c1->SetFrameLineWidth(2);
   c1->SetFillStyle(4000);
   c1->SetFrameFillStyle(4000);


   h2->SetLineColor(kBlack);
   h2->SetLineWidth(2.3);
   h2->Draw();

   h1->SetLineColor(kBlue);
   h1->SetLineWidth(2.3);
   h1->Draw("same");


   h2->GetXaxis()->SetTitle("P [GeV]");
   h2->GetYaxis()->SetTitle("Entries/1 MeV");
   h2->GetYaxis()->SetTitleOffset(1.4);
   h2->GetXaxis()->SetTitleSize(0.045);

   gStyle->SetOptTitle(0);
   gStyle->SetOptStat(kFALSE);

   leg = new TLegend(0.73,0.7,0.83,0.87);//legend
   leg->SetHeader("P distribution");
   leg->SetTextSize(0.025);
   leg->AddEntry(h1,"","l");
   leg->AddEntry(h2,"signal","l");
   leg->Draw("same");

   c1->SaveAs("~/B+2mu+nu_mu/plot/before_skimimpactpidCMS.eps");
   
   
   //plot after skim
   TCanvas *c2 = new TCanvas("c2","",1);


   c2->SetFillColor(0);
   c2->SetFrameFillColor(0);
   c2->SetFrameLineWidth(2);
   c2->SetFillStyle(4000);
   c2->SetFrameFillStyle(4000);


   h4->SetLineColor(kBlack);
   h4->SetLineWidth(2.3);
   h4->Draw();

   h3->SetLineColor(kBlue);
   h3->SetLineWidth(2.3);
   h3->Draw("same");


   h4->GetXaxis()->SetTitle("P [GeV]");
   h4->GetYaxis()->SetTitle("Entries/1 MeV");
   h4->GetYaxis()->SetTitleOffset(1.4);
   h4->GetXaxis()->SetTitleSize(0.045);

   gStyle->SetOptTitle(0);
   gStyle->SetOptStat(kFALSE);

   leg = new TLegend(0.73,0.7,0.83,0.87);//legend
   leg->SetHeader("P distribution");
   leg->SetTextSize(0.025);
   leg->AddEntry(h1,"","l");
   leg->AddEntry(h2,"signal","l");
   leg->Draw("same");

   c2->SaveAs("~/B+2mu+nu_mu/plot/after_skimimpactpidCMS.eps");
 
   //calculate the efficiency
   double bef_sig=muon1->GetEntries("B_mu_mcErrors==0&&(B_mcErrors==8||B_mcErrors==1032)");
   double aft_sig=muon2->GetEntries("B_mu_mcErrors==0&&(B_mcErrors==8||B_mcErrors==1032)");
   double bef_bk=muon1->GetEntries()-bef_sig;
   double aft_bk=muon2->GetEntries()-aft_sig;
   double sigeff=aft_sig/bef_sig;
   double bkeff=aft_bk/bef_bk;
   cout<<"Signal efficiency is: "<<sigeff<<endl;
   cout<<"Background efficiency is: "<<bkeff<<endl;

}
