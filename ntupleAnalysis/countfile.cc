#include<iostream>
using namespace std;
int countfile() {

   TChain *chn = new TChain("y4s");
  /* chn->Add("MC9mixed00/ntuple_*.root");
   chn->Add("MC9mixed01/ntuple_*.root");
   chn->Add("MC9mixed02/ntuple_*.root");
   chn->Add("MC9mixed03/ntuple_*.root");
   cout<<"mixed: "<<chn->GetEntries()<<endl;
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9charged00/ntuple_*.root");
   chn->Add("MC9charged01/ntuple_*.root");
   chn->Add("MC9charged02/ntuple_*.root");
   chn->Add("MC9charged03/ntuple_*.root");
   cout<<"charged: "<<chn->GetEntries()<<endl;
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9uubar00/ntuple_*.root");
   chn->Add("MC9uubar01/ntuple_*.root");
   chn->Add("MC9uubar02/ntuple_*.root");
   chn->Add("MC9uubar03/ntuple_*.root");
   chn->Add("MC9uubar04/ntuple_*.root");
   chn->Add("MC9uubar05/ntuple_*.root");
   chn->Add("MC9uubar06/ntuple_*.root");
   chn->Add("MC9uubar07/ntuple_*.root");
   cout<<"uubar: "<<chn->GetEntries()<<endl;
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9ddbar00/ntuple_*.root");
   chn->Add("MC9ddbar01/ntuple_*.root");
   cout<<"ddbar: "<<chn->GetEntries()<<endl;
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9ssbar00/ntuple_*.root");
   chn->Add("MC9ssbar01/ntuple_*.root");
   cout<<"ssbar: "<<chn->GetEntries()<<endl;
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9ccbar00/ntuple_*.root");
   chn->Add("MC9ccbar01/ntuple_*.root");
   chn->Add("MC9ccbar02/ntuple_*.root");
   chn->Add("MC9ccbar03/ntuple_*.root");
   chn->Add("MC9ccbar04/ntuple_*.root");
   chn->Add("MC9ccbar05/ntuple_*.root");
   chn->Add("MC9ccbar06/ntuple_*.root");
   chn->Add("MC9ccbar07/ntuple_*.root");
   cout<<"ccbar: "<<chn->GetEntries()<<endl;
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9taupair00/ntuple_*.root");
   chn->Add("MC9taupair01/ntuple_*.root");
   chn->Add("MC9taupair02/ntuple_*.root");
   chn->Add("MC9taupair03/ntuple_*.root");
   cout<<"taupair: "<<chn->GetEntries()<<endl;
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9B0Xulnu00/ntuple_*.root");
   cout<<"B0Xulnu: "<<chn->GetEntries()<<endl;
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9BplusXulnu00/ntuple_*.root");
   cout<<"BplusXulnu: "<<chn->GetEntries()<<endl;
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9ee00/ntuple_*.root");
   cout<<"ee: "<<chn->GetEntries()<<endl;
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9mumu00/ntuple_*.root");
   cout<<"mumu: "<<chn->GetEntries()<<endl;
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9eeee00/ntuple_*.root");
   cout<<"eeee: "<<chn->GetEntries()<<endl;
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9eemumu00/ntuple_*.root");
   cout<<"eemumu: "<<chn->GetEntries()<<endl;
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9eeuubar00/ntuple_*.root");
   cout<<"eeuu: "<<chn->GetEntries()<<endl;
   delete chn;*/

   chn = new TChain("y4s");
   chn->Add("MC9eessbar00/ntuple_*.root");
   cout<<"eess: "<<chn->GetEntries()<<endl;
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9eeccbar00/ntuple_*.root");
   cout<<"eecc: "<<chn->GetEntries()<<endl;
   delete chn;
   return 0;
}
