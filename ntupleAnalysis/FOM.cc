#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;
TFile* f1 = new TFile("~/Ntuples_ROE/MC9.root");
TTree *t1 = (TTree*)f1->Get("y4s");
double fcn(double *par)
{
   ostringstream strs;
   string Flag = "Flag==";
   strs << Flag << 0;
   string id = "&&missP2>";
   strs << id << par[0] ;
   cout<<"par[0] = "<<par[0]<<endl;
   string str = strs.str();
   char sig[200];
   strcpy(sig,(str).c_str());
   double signal = t1->GetEntries(sig);
   char* bkg = sig;
   bkg[6] = 49;
   double BB = t1->GetEntries(bkg);
   bkg[6] = 50;
   double uds = t1->GetEntries(bkg);
   bkg[6] = 51;
   double c = t1->GetEntries(bkg);
   bkg[6] = 52;
   double tau = t1->GetEntries(bkg);
   bkg[6] = 54;
   double mumu = t1->GetEntries(bkg)*40;
   bkg[6] = 55;
   double eeee = t1->GetEntries(bkg)*8000;
   bkg[6] = 56;
   double eemumu = t1->GetEntries(bkg)*8000;
   bkg[6] = 57;
   bkg[4] = 62;
   double eeuu = t1->GetEntries(bkg)*0.8;
   double background = BB+uds+c+tau+mumu+eeee+eemumu+eeuu;
   double eff = t1->GetEntries("!Flag")/500000.*344.;
   //cout<<"time: "<<clock()<<endl;
   signal = signal/500000.*344.;
   cout<<signal<<" "<<background;
   cout<<"purity: "<<signal/(signal+background)<<endl;
   cout<<"efficiency: "<<signal/eff<<endl;
   return signal/sqrt(background+signal);
   //return signal/eff/(0.64  + sqrt(background));
}
void FOM(){
   double par[1] = {0};
   double max = 0;
   double maxpar[1] = {0};
   TH1F *h1 = new TH1F("h1","h1",20,1.,3.);
   gStyle->SetOptStat(kFALSE);
   int j=1;
   for(double i=1;i<3;i=i+0.1)
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
