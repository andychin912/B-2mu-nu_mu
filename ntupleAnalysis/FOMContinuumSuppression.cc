#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;
TFile* f1 = new TFile("~/Ntuples_ROE/CSexpert.root");
TTree *t1 = (TTree*)f1->Get("variables");
double fcn(double *par)
{
   ostringstream strs;
   string isSignal = "CSFastBDT_500__ptxml_isSignal==";
   strs << isSignal << 1;
   string id = "&&CSFastBDT_500__ptxml>=";
   strs << id << par[0] ;
   cout<<"par[0] = "<<par[0]<<endl;
   string str = strs.str();
   char sig[200];
   strcpy(sig,(str).c_str());
   double signal = t1->GetEntries(sig);
   char* bkg = sig;
   bkg[31] = 48;
   double background = t1->GetEntries(bkg)/207081.*1527410;
   double eff = t1->GetEntries("CSFastBDT_500__ptxml_isSignal==1")/500000.*344.;
   //cout<<"time: "<<clock()<<endl;
   signal = signal/500000.*344.;
   cout<<signal<<" "<<background<<endl;
   cout<<"purity: "<<signal/(signal+background)<<endl;
   cout<<"efficiency: "<<signal/eff<<endl;
   return signal*5/sqrt(background+signal);
   //return (signal/eff)/(0.64  + sqrt(background*5));
}
void FOMContinuumSuppression(){
   double par[1] = {0};
   double max = 0;
   double maxpar[1] = {0};
   TH1F *h1 = new TH1F("h1","h1",100.,0,1);
   gStyle->SetOptStat(kFALSE);
   int j=1;
   for(double i=0;i<1;i=i+0.01)
   {
      par[0]=i;
      double f = fcn(par);
      //cout<<"time to return: "<<clock()<<endl;
      if(f>max)
      {
         max = f;
         maxpar[0] = par[0];
      }
      cout<<f<<endl;
      h1->SetBinContent(j,f);
      j++;
   }
   cout<<max<<endl;
   cout<<maxpar[0]<<endl;
   h1->Draw("L");

}
