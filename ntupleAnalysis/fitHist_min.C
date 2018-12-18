using namespace RooFit;
using namespace RooStats;
TFile *MCfile = new TFile("MC9.root");
TTree *tr = (TTree*)MCfile->Get("y4s");
int bin = 10;
TH3F* hbb = new TH3F("hbb","hbb",bin,0.5,1.,bin,5.1,5.29,bin,2.2,3.1);
TH3F* hqq = new TH3F("hqq","hqq",bin,0.5,1.,bin,5.1,5.29,bin,2.2,3.1);
TH3F* htau = new TH3F("htau","htau",bin,0.5,1.,bin,5.1,5.29,bin,2.2,3.1);
TH3F* hss = new TH3F("hs","hs",bin,0.5,1.,bin,5.1,5.29,bin,2.2,3.1);
TH3F* hs = new TH3F("hs","hs",bin,0.5,1.,bin,5.1,5.29,bin,2.2,3.1);
TH3F* mac = new TH3F("mac","mac",bin,0.5,1.,bin,5.1,5.29,bin,2.2,3.1);
int sig;
int bb;
int qq;
int tau;
void fcn(int &npar, double *gin, double &f, double *par, int iflag)
{
  f = 0;
  int d;
  int a;
  int x2,y2,z2;
  int i2=0;
  double cons;
  double A;
  double fi;
  for (int i=0;i<(bin+2)*(bin+2)*(bin+2);i++)
  { 
    hs->GetBinXYZ(i+1,x2,y2,z2);
    if (x2==0||x2==bin+1||y2==0||y2==bin+1||z2==0||z2==bin+1){continue;}
    d = mac->GetBinContent(i+1);
    cons = 0;
    fi = 0;
    for(int j=0;j<4;j++)
    {
       A = par[j*bin*bin*bin+i2];
       if (A<0) {
         A = -A;
       }
       if (j==0) {
         a = hs->GetBinContent(i+1);
	 fi = fi + par[bin*bin*bin*4]*(A/sig);
       }
       else if (j==1) {
         a = hbb->GetBinContent(i+1);
	 fi = fi + par[bin*bin*bin*4+1]*(A/bb);
       }
       else if (j==2) {
         a = hqq->GetBinContent(i+1);
	 fi = fi + par[bin*bin*bin*4+2]*(A/qq);
       }
       else if (j==3) {
         a = htau->GetBinContent(i+1);
	 fi = fi + par[bin*bin*bin*4+3]*(A/tau);
       }
       if (a==0&&A==0) {}
       else {
       cons = cons + (a*log(A)-A);
       }
    }
    f = f - (d*log(fi)-fi+cons);
    i2++;
  }
}
void fitHist_min()
{
  tr->Draw("useCMSFrameLPdaughterLP1COpRPRP:Mbc:TrainOut>>hbb","1.0*(Flag==1&&TrainOut>0.5)");
  tr->Draw("useCMSFrameLPdaughterLP1COpRPRP:Mbc:TrainOut>>hqq","1.0*((Flag==2||Flag==3)&&TrainOut>0.5)");
  tr->Draw("useCMSFrameLPdaughterLP1COpRPRP:Mbc:TrainOut>>htau","1.0*(Flag==4&&TrainOut>0.5)");
  tr->Draw("useCMSFrameLPdaughterLP1COpRPRP:Mbc:TrainOut>>hss","Scale*(Flag==0&&TrainOut>0.5)");
  tr->Draw("useCMSFrameLPdaughterLP1COpRPRP:Mbc:TrainOut>>hs","(Flag==0&&TrainOut>0.5)");
  TH3F* sum = new TH3F("sum","sum",bin,0.5,1.,bin,5.1,5.29,bin,2.2,3.1);
  tr->Draw("useCMSFrameLPdaughterLP1COpRPRP:Mbc:TrainOut>>sum","1.0*(Flag==1&&TrainOut>0.5)"); sum->Add(hqq); sum->Add(htau); sum->Add(hss);
  TMinuit *gMinuit = new TMinuit(bin*bin*bin*4+4);
  gMinuit->SetPrintLevel(0);
  gMinuit->SetFCN(fcn);
  double x; double y; double z;
  for (int i=0;i<65000;i++)
  {
    sum->GetRandom3(x,y,z);
    mac->Fill(x,y,z);
  }
  hs->Draw();
  sig = tr->GetEntries("Flag==0&&TrainOut>0.5");
  bb = tr->GetEntries("Flag==1&&TrainOut>0.5");
  qq = tr->GetEntries("(Flag==2||Flag==3)&&TrainOut>0.5");
  tau = tr->GetEntries("Flag==4&&TrainOut>0.5");
  double q=0;
  int x2,y2,z2;
  int i2=0;
  int a=0;
  for (int i=0;i<(bin+2)*(bin+2)*(bin+2);i++)
  {
     hs->GetBinXYZ(i+1,x2,y2,z2);
     if (x2==0||x2==bin+1||y2==0||y2==bin+1||z2==0||z2==bin+1){continue;}

     for (int j=0;j<4;j++)
     {
       if (j==0) {gMinuit->DefineParameter(i2+j*bin*bin*bin,"zom",hs->GetBinContent(i+1)+0.01,1,-1,20000);}
       else if (j==1){ gMinuit->DefineParameter(i2+j*bin*bin*bin,"zom",hbb->GetBinContent(i+1)+0.01,1,-1,20000);}
       else if (j==2){ gMinuit->DefineParameter(i2+j*bin*bin*bin,"zom",hqq->GetBinContent(i+1)+0.01,1,-1,20000);}
       else if (j==3){ gMinuit->DefineParameter(i2+j*bin*bin*bin,"zom",htau->GetBinContent(i+1)+0.01,1,-1,20000);}
     }
     i2++;
     //htau->GetBinXYZ(6716,x2,y2,z2);
     //cout<<x2<<" "<<y2<<" "<<z2;

  }
  gMinuit->DefineParameter(bin*bin*bin*4,"Nsig",sig/500000.*344,1,0,1000);
  gMinuit->DefineParameter(bin*bin*bin*4+1,"Nbb",bb,1,0,50000);
  gMinuit->DefineParameter(bin*bin*bin*4+2,"Nqq",qq,1,0,50000);
  gMinuit->DefineParameter(bin*bin*bin*4+3,"Ntau",tau,1,0,50000);
  gMinuit->Command("MIGRAD");
  gMinuit->Command("MIGRAD");
  gMinuit->Command("MINOS");
  double par[5],err[5];
  for(int i=0;i<4;i++) gMinuit->GetParameter(bin*bin*bin*4+i,par[i],err[i]);

 }
