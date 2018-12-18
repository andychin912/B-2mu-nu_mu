#include<iostream>
using namespace std;
void getTrainAndTest(string filename);
void merge1();
void merge2();
void seperate2_8();
void createFlag(string filename);
void merge3();

void createTrainAndTestDatasets()
{
   cout<<"merge step 1......"<<endl;
   //merge1();
   cout<<"merge step 2......"<<endl;
   merge2();
   cout<<"seperating training and testing datasets......"<<endl;
   //seperate2_8();
   cout<<"merge step 3......"<<endl;
   //merge3();

}
void merge1()
{
   TChain *chn = new TChain("y4s");
   chn->Add("MC9mixed00.root");
   chn->Add("MC9mixed01.root");
   chn->Add("MC9mixed02.root");
   chn->Add("MC9mixed03.root");
   chn->Merge("MC9mixed.root");
   delete chn;
   cout<<"mixed sample added"<<endl;

   chn = new TChain("y4s");
   chn->Add("MC9charged00.root");
   chn->Add("MC9charged01.root");
   chn->Add("MC9charged02.root");
   chn->Add("MC9charged03.root");
   chn->Merge("MC9charged.root");
   delete chn;
   cout<<"charged sample added"<<endl;

   chn = new TChain("y4s");
   chn->Add("MC9uubar00.root");
   chn->Add("MC9uubar01.root");
   chn->Add("MC9uubar02.root");
   chn->Add("MC9uubar03.root");
   chn->Add("MC9uubar04.root");
   chn->Add("MC9uubar05.root");
   chn->Add("MC9uubar06.root");
   chn->Merge("MC9uubar.root");
   delete chn;
   cout<<"uubar sample added"<<endl;

   chn = new TChain("y4s");
   chn->Add("MC9ddbar00.root");
   chn->Add("MC9ddbar01.root");
   chn->Merge("MC9ddbar.root");
   delete chn;
   cout<<"ddbar sample added"<<endl;
   
   chn = new TChain("y4s");
   chn->Add("MC9ssbar00.root");
   chn->Add("MC9ssbar01.root");
   chn->Merge("MC9ssbar.root");
   delete chn;
   cout<<"ssbar sample added"<<endl;

   chn = new TChain("y4s");
   chn->Add("MC9ccbar00.root");
   chn->Add("MC9ccbar01.root");
   chn->Add("MC9ccbar02.root");
   chn->Add("MC9ccbar03.root");
   chn->Add("MC9ccbar04.root");
   chn->Add("MC9ccbar05.root");
   chn->Add("MC9ccbar06.root");
   chn->Add("MC9ccbar07.root");
   chn->Merge("MC9ccbar.root");
   delete chn;
   cout<<"ccbar sample added"<<endl;

   chn = new TChain("y4s");
   chn->Add("MC9taupair00/ntuple*.root");
   chn->Add("MC9taupair01/ntuple*.root");
   chn->Add("MC9taupair02/ntuple*.root");
   chn->Add("MC9taupair03/ntuple*.root");
   chn->Merge("MC9taupair.root");
   delete chn;
   cout<<"taupair sample added"<<endl;

   chn = new TChain("y4s");
   chn->Add("MC9B0Xulnu00/ntuple*.root");
   chn->Merge("MC9B0Xulnu.root");
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9BplusXulnu00/ntuple*.root");
   chn->Merge("MC9BplusXulnu.root");
   delete chn;
   cout<<"semi-leptonic sample added"<<endl;

   //chn = new TChain("y4s");
   //chn->Add("MC9ee00/ntuple*.root");
   //chn->Merge("MC9ee.root");
   //delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9mumu00/ntuple*.root");
   chn->Merge("MC9mumu.root");
   delete chn;
   cout<<"QED sample added"<<endl;

   chn = new TChain("y4s");
   chn->Add("MC9eeee00.root");
   chn->Merge("MC9eeee.root");
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9eemumu00.root");
   chn->Merge("MC9eemumu.root");
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9eeuubar00.root");
   chn->Merge("MC9eeuubar.root");
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9eessbar00.root");
   chn->Merge("MC9eessbar.root");
   delete chn;

   chn = new TChain("y4s");
   chn->Add("MC9eeccbar00.root");
   chn->Merge("MC9eeccbar.root");
   delete chn;  
   cout<<"two-photon sample added"<<endl;

}
void merge2()
{
   /*createFlag("MC9uubar");
   createFlag("MC9ddbar");
   createFlag("MC9ssbar");
   createFlag("MC9ccbar");
   createFlag("MC9taupair");
   createFlag("MC9mixed");
   createFlag("MC9charged");
   //createFlag("MC9B0Xulnu");
   //createFlag("MC9BplusXulnu");
   createFlag("MC9mumu");
   createFlag("MC9eeee");
   createFlag("MC9eemumu");
   createFlag("MC9eeuubar");
   createFlag("MC9eessbar");
   createFlag("MC9eeccbar");
   createFlag("MC9signal");*/
   TChain *chn = new TChain("y4s");
   chn->Add("MC9uubar.root");
   chn->Add("MC9ddbar.root");
   chn->Add("MC9ssbar.root");
   chn->Add("MC9ccbar.root");
   chn->Add("MC9taupair.root");
   chn->Add("MC9mixed.root");
   chn->Add("MC9charged.root");
   //chn->Add("MC9B0Xulnu.root");
   //chn->Add("MC9BplusXulnu.root");
   chn->Add("MC9mumu.root");
   chn->Add("MC9eeee.root");
   chn->Add("MC9eemumu.root");
   chn->Add("MC9eeuubar.root");
   chn->Add("MC9eessbar.root");
   chn->Add("MC9eeccbar.root");
   chn->Add("MC9signal.root");

   Int_t B_mu_mcErrors;
   Int_t B_mcErrors;
   Float_t B_useCMSFrame__bop__bc;
   Float_t B_deltae;
   Float_t B_mbc;
   Float_t B_ThrustB;
   Float_t B_ThrustO;
   Float_t B_CosTBTO;
   Float_t B_CosTBz;
   Float_t B_R2;
   Float_t B_cc1_CcROE;
   Float_t B_cc2_CcROE;
   Float_t B_cc3_CcROE;
   Float_t B_cc4_CcROE;
   Float_t B_cc5_CcROE;
   Float_t B_cc6_CcROE;
   Float_t B_cc7_CcROE;
   Float_t B_cc8_CcROE;
   Float_t B_cc9_CcROE;
   Float_t B_cc1;
   Float_t B_cc2;
   Float_t B_cc3;
   Float_t B_cc4;
   Float_t B_cc5;
   Float_t B_cc6;
   Float_t B_cc7;
   Float_t B_cc8;
   Float_t B_cc9;
   Float_t B_mm2;
   Float_t B_et;
   Float_t B_hso00;
   Float_t B_hso01;
   Float_t B_hso02;
   Float_t B_hso03;
   Float_t B_hso04;
   Float_t B_hso10;
   Float_t B_hso12;
   Float_t B_hso14;
   Float_t B_hso20;
   Float_t B_hso22;
   Float_t B_hso24;
   Float_t B_hoo0;
   Float_t B_hoo1;
   Float_t B_hoo2;
   Float_t B_hoo3;
   Float_t B_hoo4;
   Float_t B_mu_kaonID;
   Float_t B_mu_electronID;
   Float_t B_NLep;
   Float_t B_nTracks;
   Float_t cosTheta;
   Float_t B_mu_chiProb; 
   Float_t B_nROEKLMClusters;
   Float_t B_ROE_eextra__bocleanMask__bc;
   Float_t px;
   Float_t py;
   Float_t pz;
   Float_t PX;
   Float_t PY;
   Float_t PZ;
   Float_t E;
   Float_t dP;
   Float_t LogLikelihood;
   Float_t isSignal;
   Float_t weight=0;
   Float_t scale;
   Float_t Nlep;
   Float_t NhighP;
   Float_t B_mu_charge;
   Float_t B_qrOutput__boFANN__bc;
   Float_t B_qrOutput__boFBDT__bc;
   Float_t missP0;
   Float_t missP1;
   Float_t missP2;
   Float_t missE0;
   Float_t missE1;
   Float_t missE2;
   Int_t flag;

   chn->SetBranchAddress("B_mu_mcErrors",&B_mu_mcErrors);
   chn->SetBranchAddress("B_mcErrors",&B_mcErrors);
   chn->SetBranchAddress("B_useCMSFrame__bop__bc",&B_useCMSFrame__bop__bc);
   chn->SetBranchAddress("B_useCMSFrame__bopx__bc",&px);
   chn->SetBranchAddress("B_useCMSFrame__bopy__bc",&py);
   chn->SetBranchAddress("B_useCMSFrame__bopz__bc",&pz);
   chn->SetBranchAddress("B_useCMSFrame__boROE_Px__bocleanMask__bc__bc",&PX);
   chn->SetBranchAddress("B_useCMSFrame__boROE_Py__bocleanMask__bc__bc",&PY);
   chn->SetBranchAddress("B_useCMSFrame__boROE_Pz__bocleanMask__bc__bc",&PZ);
   chn->SetBranchAddress("B_ROE_E__bocleanMask__bc",&E);
   chn->SetBranchAddress("B_ROE_deltae__bocleanMask__bc",&B_deltae);
   chn->SetBranchAddress("B_ROE_mbc__bocleanMask__bc",&B_mbc);
   chn->SetBranchAddress("B_ThrustB",&B_ThrustB);
   chn->SetBranchAddress("B_ThrustO",&B_ThrustO);
   chn->SetBranchAddress("B_CosTBTO",&B_CosTBTO);
   chn->SetBranchAddress("B_CosTBz",&B_CosTBz);
   chn->SetBranchAddress("B_R2",&B_R2);
   chn->SetBranchAddress("B_cc1_CcROE",&B_cc1_CcROE);
   chn->SetBranchAddress("B_cc2_CcROE",&B_cc2_CcROE);
   chn->SetBranchAddress("B_cc3_CcROE",&B_cc3_CcROE);
   chn->SetBranchAddress("B_cc4_CcROE",&B_cc4_CcROE);
   chn->SetBranchAddress("B_cc5_CcROE",&B_cc5_CcROE);
   chn->SetBranchAddress("B_cc6_CcROE",&B_cc6_CcROE);
   chn->SetBranchAddress("B_cc7_CcROE",&B_cc7_CcROE);
   chn->SetBranchAddress("B_cc8_CcROE",&B_cc8_CcROE);
   chn->SetBranchAddress("B_cc9_CcROE",&B_cc9_CcROE);
   chn->SetBranchAddress("B_cc1",&B_cc1);
   chn->SetBranchAddress("B_cc2",&B_cc2);
   chn->SetBranchAddress("B_cc3",&B_cc3);
   chn->SetBranchAddress("B_cc4",&B_cc4);
   chn->SetBranchAddress("B_cc5",&B_cc5);
   chn->SetBranchAddress("B_cc6",&B_cc6);
   chn->SetBranchAddress("B_cc7",&B_cc7);
   chn->SetBranchAddress("B_cc8",&B_cc8);
   chn->SetBranchAddress("B_cc9",&B_cc9);
   chn->SetBranchAddress("B_mm2",&B_mm2);
   chn->SetBranchAddress("B_et",&B_et);
   chn->SetBranchAddress("B_hso00",&B_hso00);
   chn->SetBranchAddress("B_hso01",&B_hso01);
   chn->SetBranchAddress("B_hso02",&B_hso02);
   chn->SetBranchAddress("B_hso03",&B_hso03);
   chn->SetBranchAddress("B_hso04",&B_hso04);
   chn->SetBranchAddress("B_hso10",&B_hso10);
   chn->SetBranchAddress("B_hso12",&B_hso12);
   chn->SetBranchAddress("B_hso14",&B_hso14);
   chn->SetBranchAddress("B_hso20",&B_hso20);
   chn->SetBranchAddress("B_hso22",&B_hso22);
   chn->SetBranchAddress("B_hso24",&B_hso24);
   chn->SetBranchAddress("B_hoo0",&B_hoo0);
   chn->SetBranchAddress("B_hoo1",&B_hoo1);
   chn->SetBranchAddress("B_hoo2",&B_hoo2);
   chn->SetBranchAddress("B_hoo3",&B_hoo3);
   chn->SetBranchAddress("B_hoo4",&B_hoo4);
   chn->SetBranchAddress("B_mu_kaonID",&B_mu_kaonID);
   chn->SetBranchAddress("B_mu_electronID",&B_mu_electronID);
   chn->SetBranchAddress("B_nTracks",&B_nTracks);
   chn->SetBranchAddress("B_mu_chiProb",&B_mu_chiProb);
   chn->SetBranchAddress("B_nROEKLMClusters",&B_nROEKLMClusters);
   chn->SetBranchAddress("B_ROE_eextra__bocleanMask__bc",&B_ROE_eextra__bocleanMask__bc);
   chn->SetBranchAddress("Flag",&flag);
   chn->SetBranchAddress("B_mu_pidDeltaLogLikelihoodValueExpert__bo13__cm211__cmALL__bc",&LogLikelihood);
   //chn->SetBranchAddress("B_Nlep",&Nlep);
   chn->SetBranchAddress("B_NhighP",&NhighP);
   chn->SetBranchAddress("B_mu_charge",&B_mu_charge);
   chn->SetBranchAddress("B_qrOutput__boFANN__bc",&B_qrOutput__boFANN__bc);
   chn->SetBranchAddress("B_qrOutput__boFBDT__bc",&B_qrOutput__boFBDT__bc);
   chn->SetBranchAddress("B_missP__bocleanMask__cm0__bc",&missP0);
   chn->SetBranchAddress("B_missP__bocleanMask__cm1__bc",&missP1);
   chn->SetBranchAddress("B_missP__bocleanMask__cm2__bc",&missP2);
   chn->SetBranchAddress("B_missE__bocleanMask__cm0__bc",&missE0);
   chn->SetBranchAddress("B_missE__bocleanMask__cm1__bc",&missE1);
   chn->SetBranchAddress("B_missE__bocleanMask__cm2__bc",&missE2);
   chn->SetBranchAddress("Scale",&scale);
   chn->Print();


   TFile *newfile = new TFile("MC9.root","recreate");
   TTree *chg = new TTree("y4s","y4s");
   chg->Branch("isSignal",&isSignal);
   chg->Branch("useCMSFrameLPdaughterLP1COpRPRP",&B_useCMSFrame__bop__bc);
   chg->Branch("deltaE",&B_deltae);
   chg->Branch("Mbc",&B_mbc);
   chg->Branch("ThrustB",&B_ThrustB);
   chg->Branch("ThrustO",&B_ThrustO);
   chg->Branch("CosTBTO",&B_CosTBTO);
   chg->Branch("CosTBz",&B_CosTBz);
   chg->Branch("R2",&B_R2);
   chg->Branch("CleoConeLP1COROERP",&B_cc1_CcROE);
   chg->Branch("CleoConeLP2COROERP",&B_cc2_CcROE);
   chg->Branch("CleoConeLP3COROERP",&B_cc3_CcROE);
   chg->Branch("CleoConeLP4COROERP",&B_cc4_CcROE);
   chg->Branch("CleoConeLP5COROERP",&B_cc5_CcROE);
   chg->Branch("CleoConeLP6COROERP",&B_cc6_CcROE);
   chg->Branch("CleoConeLP7COROERP",&B_cc7_CcROE);
   chg->Branch("CleoConeLP8COROERP",&B_cc8_CcROE);
   chg->Branch("CleoConeLP9COROERP",&B_cc9_CcROE);
   chg->Branch("CleoConeLP1RP",&B_cc1);
   chg->Branch("CleoConeLP2RP",&B_cc2);
   chg->Branch("CleoConeLP3RP",&B_cc3);
   chg->Branch("CleoConeLP4RP",&B_cc4);
   chg->Branch("CleoConeLP5RP",&B_cc5);
   chg->Branch("CleoConeLP6RP",&B_cc6);
   chg->Branch("CleoConeLP7RP",&B_cc7);
   chg->Branch("CleoConeLP8RP",&B_cc8);
   chg->Branch("CleoConeLP9RP",&B_cc9);
   chg->Branch("KSFWVariablesLPmm2RP",&B_mm2);
   chg->Branch("KSFWVariablesLPetRP",&B_et);
   chg->Branch("KSFWVariablesLPhso00RP",&B_hso00);
   chg->Branch("KSFWVariablesLPhso01RP",&B_hso01);
   chg->Branch("KSFWVariablesLPhso02RP",&B_hso02);
   chg->Branch("KSFWVariablesLPhso03RP",&B_hso03);
   chg->Branch("KSFWVariablesLPhso04RP",&B_hso04);
   chg->Branch("KSFWVariablesLPhso10RP",&B_hso10);
   chg->Branch("KSFWVariablesLPhso12RP",&B_hso12);
   chg->Branch("KSFWVariablesLPhso14RP",&B_hso14);
   chg->Branch("KSFWVariablesLPhso20RP",&B_hso20);
   chg->Branch("KSFWVariablesLPhso22RP",&B_hso22);
   chg->Branch("KSFWVariablesLPhso24RP",&B_hso24);
   chg->Branch("KSFWVariablesLPhoo0RP",&B_hoo0);
   chg->Branch("KSFWVariablesLPhoo1RP",&B_hoo1);
   chg->Branch("KSFWVariablesLPhoo2RP",&B_hoo2);
   chg->Branch("KSFWVariablesLPhoo3RP",&B_hoo3);
   chg->Branch("KSFWVariablesLPhoo4RP",&B_hoo4);
   chg->Branch("daughterLP0COkaonIDRP",&B_mu_kaonID);
   chg->Branch("daughterLP0COelectronIDRP",&B_mu_electronID);
   chg->Branch("nTracks",&B_nTracks);
   chg->Branch("chiProb",&B_mu_chiProb);
   chg->Branch("nROEKLMClusters",&B_nROEKLMClusters);
   chg->Branch("eextra",&B_ROE_eextra__bocleanMask__bc);
   chg->Branch("ROE_E",&E);
   chg->Branch("LogLikelihood",&LogLikelihood);
   //chg->Branch("Nlep",&Nlep);
   chg->Branch("NhighP",&NhighP);
   chg->Branch("qrOutputLPFANNRP",&B_qrOutput__boFANN__bc);
   chg->Branch("qrOutputLPFBDTRP",&B_qrOutput__boFBDT__bc);
   chg->Branch("missP0",&missP0);
   chg->Branch("missP1",&missP1);
   chg->Branch("missP2",&missP2);
   chg->Branch("missE0",&missE0);
   chg->Branch("missE1",&missE1);
   chg->Branch("missE2",&missE2);
   chg->Branch("dP",&dP);
   chg->Branch("weight",&weight);
   chg->Branch("Scale",&scale);
   chg->Branch("Flag",&flag);
   Int_t i=0;
   for (i=0;i<chn->GetEntries();i++) {
      chn->GetEntry(i);
      dP = sqrt((px-PX)*(px-PX)+(py-PY)*(py-PY)+(pz-PZ)*(pz-PZ));
      B_qrOutput__boFANN__bc = B_qrOutput__boFANN__bc*B_mu_charge;
      B_qrOutput__boFBDT__bc = B_qrOutput__boFBDT__bc*B_mu_charge;
      if(flag==0) isSignal=1;
      else isSignal=0;
      chg->Fill();
   }
   chg->Write();
   newfile->Close();

}
void createFlag(string filename)
{
   string str;
   ostringstream strs;
   strs << filename << ".root";
   str = strs.str();
   char orfile[200];
   strcpy(orfile,(str).c_str());
   TFile *file1 = new TFile(orfile,"update");
   TTree *t1 = (TTree*)file1->Get("y4s");
   Float_t scale;
   Int_t flag;
   TBranch *b1 = t1->Branch("Flag",&flag);
   TBranch *b2 = t1->Branch("Scale",&scale);
   Int_t i=0;
   for (i=0;i<t1->GetEntries();i++) {
      t1->GetEntry(i);      
      if(filename=="MC9signal") {scale = 344./500000.; flag = 0;}
      else if(filename=="MC9mumu") {scale = 40; flag = 6;}
      else if(filename=="MC9eeee") {scale = 8000; flag = 7;}
      else if(filename=="MC9eemumu") {scale = 8000; flag = 8;}
      else if(filename=="MC9eeuubar") {scale = 0.8; flag = 9;}
      else if(filename=="MC9eessbar") {scale = 0.8; flag = 10;}
      else if(filename=="MC9eeccbar") {scale = 0.8; flag = 11;}
      else if(filename=="MC9B0Xulnu") {scale = 0.04108; flag = 5;}//br 0.004803
      else if(filename=="MC9BplusXulnu") {scale = 0.04964; flag = 5;}//br 0.005487
      else if(filename=="MC9uubar" || filename=="MC9ddbar" || filename=="MC9ssbar") {scale = 1; flag = 2;}
      else if(filename=="MC9ccbar") {scale = 1; flag = 3;}
      else if(filename=="MC9taupair") {scale = 1; flag = 4;}
      else {scale = 1; flag = 1;}
      b1->Fill();
      b2->Fill();
   }
   t1->Write();
   delete file1;
}
void seperate2_8()
{
   getTrainAndTest("MC9uubar");
   getTrainAndTest("MC9ddbar");
   getTrainAndTest("MC9ssbar");
   getTrainAndTest("MC9ccbar");
   //getTrainAndTest("MC9taupair");
   //getTrainAndTest("MC9ee");
   //getTrainAndTest("MC9mixed");
   //getTrainAndTest("MC9charged");
   //getTrainAndTest("MC9B0Xulnu");
   //getTrainAndTest("MC9BplusXulnu");
   //getTrainAndTest("MC9mumu");
   //getTrainAndTest("MC9eeee");
   //getTrainAndTest("MC9eemumu");
   //getTrainAndTest("MC9eeuubar");
   //getTrainAndTest("MC9eessbar");
   //getTrainAndTest("MC9eeccbar");
   getTrainAndTest("MC9signal");
}
void getTrainAndTest(string filename)
{
   Int_t B_mu_mcErrors;
   Int_t B_mcErrors;
   Float_t B_useCMSFrame__bop__bc;
   Float_t B_deltae;
   Float_t B_mbc;
   Float_t B_ThrustB;
   Float_t B_ThrustO;
   Float_t B_CosTBTO;
   Float_t B_CosTBz;
   Float_t B_R2;
   Float_t B_cc1_CcROE;
   Float_t B_cc2_CcROE;
   Float_t B_cc3_CcROE;
   Float_t B_cc4_CcROE;
   Float_t B_cc5_CcROE;
   Float_t B_cc6_CcROE;
   Float_t B_cc7_CcROE;
   Float_t B_cc8_CcROE;
   Float_t B_cc9_CcROE;
   Float_t B_cc1;
   Float_t B_cc2;
   Float_t B_cc3;
   Float_t B_cc4;
   Float_t B_cc5;
   Float_t B_cc6;
   Float_t B_cc7;
   Float_t B_cc8;
   Float_t B_cc9;
   Float_t B_mm2;
   Float_t B_et;
   Float_t B_hso00;
   Float_t B_hso01;
   Float_t B_hso02;
   Float_t B_hso03;
   Float_t B_hso04;
   Float_t B_hso10;
   Float_t B_hso12;
   Float_t B_hso14;
   Float_t B_hso20;
   Float_t B_hso22;
   Float_t B_hso24;
   Float_t B_hoo0;
   Float_t B_hoo1;
   Float_t B_hoo2;
   Float_t B_hoo3;
   Float_t B_hoo4;
   Float_t B_mu_kaonID;
   Float_t B_NLep;
   Float_t B_nTracks;
   Float_t cosTheta;
   Float_t B_mu_charge;
   Float_t B_qrOutput__boFANN__bc;
   Float_t B_qrOutput__boFBDT__bc;
   Float_t isSignal;
   Float_t weight;
   Float_t scale;
   Int_t flag;

   string str;
   ostringstream strs;
   strs << filename << ".root";
   str = strs.str();
   char orfile[200];
   strcpy(orfile,(str).c_str());
   TFile *file1 = new TFile(orfile);
   TTree *t1 = (TTree*)file1->Get("y4s");
   t1->SetBranchAddress("B_mu_mcErrors",&B_mu_mcErrors);
   t1->SetBranchAddress("B_mcErrors",&B_mcErrors);
   t1->SetBranchAddress("B_useCMSFrame__bop__bc",&B_useCMSFrame__bop__bc);
   t1->SetBranchAddress("B_ROE_deltae__bocleanMask__bc",&B_deltae);
   t1->SetBranchAddress("B_ROE_mbc__bocleanMask__bc",&B_mbc);
   t1->SetBranchAddress("B_ThrustB",&B_ThrustB);
   t1->SetBranchAddress("B_ThrustO",&B_ThrustO);
   t1->SetBranchAddress("B_CosTBTO",&B_CosTBTO);
   t1->SetBranchAddress("B_CosTBz",&B_CosTBz);
   t1->SetBranchAddress("B_R2",&B_R2);
   t1->SetBranchAddress("B_cc1_CcROE",&B_cc1_CcROE);
   t1->SetBranchAddress("B_cc2_CcROE",&B_cc2_CcROE);
   t1->SetBranchAddress("B_cc3_CcROE",&B_cc3_CcROE);
   t1->SetBranchAddress("B_cc4_CcROE",&B_cc4_CcROE);
   t1->SetBranchAddress("B_cc5_CcROE",&B_cc5_CcROE);
   t1->SetBranchAddress("B_cc6_CcROE",&B_cc6_CcROE);
   t1->SetBranchAddress("B_cc7_CcROE",&B_cc7_CcROE);
   t1->SetBranchAddress("B_cc8_CcROE",&B_cc8_CcROE);
   t1->SetBranchAddress("B_cc9_CcROE",&B_cc9_CcROE);
   t1->SetBranchAddress("B_cc1",&B_cc1);
   t1->SetBranchAddress("B_cc2",&B_cc2);
   t1->SetBranchAddress("B_cc3",&B_cc3);
   t1->SetBranchAddress("B_cc4",&B_cc4);
   t1->SetBranchAddress("B_cc5",&B_cc5);
   t1->SetBranchAddress("B_cc6",&B_cc6);
   t1->SetBranchAddress("B_cc7",&B_cc7);
   t1->SetBranchAddress("B_cc8",&B_cc8);
   t1->SetBranchAddress("B_cc9",&B_cc9);
   t1->SetBranchAddress("B_mm2",&B_mm2);
   t1->SetBranchAddress("B_et",&B_et);
   t1->SetBranchAddress("B_hso00",&B_hso00);
   t1->SetBranchAddress("B_hso01",&B_hso01);
   t1->SetBranchAddress("B_hso02",&B_hso02);
   t1->SetBranchAddress("B_hso03",&B_hso03);
   t1->SetBranchAddress("B_hso04",&B_hso04);
   t1->SetBranchAddress("B_hso10",&B_hso10);
   t1->SetBranchAddress("B_hso12",&B_hso12);
   t1->SetBranchAddress("B_hso14",&B_hso14);
   t1->SetBranchAddress("B_hso20",&B_hso20);
   t1->SetBranchAddress("B_hso22",&B_hso22);
   t1->SetBranchAddress("B_hso24",&B_hso24);
   t1->SetBranchAddress("B_hoo0",&B_hoo0);
   t1->SetBranchAddress("B_hoo1",&B_hoo1);
   t1->SetBranchAddress("B_hoo2",&B_hoo2);
   t1->SetBranchAddress("B_hoo3",&B_hoo3);
   t1->SetBranchAddress("B_hoo4",&B_hoo4);
   t1->SetBranchAddress("B_mu_kaonID",&B_mu_kaonID);
   t1->SetBranchAddress("B_nTracks",&B_nTracks);
   //t1->SetBranchAddress("B_NLep",&B_NLep);
   t1->SetBranchAddress("B_mu_charge",&B_mu_charge);
   t1->SetBranchAddress("B_qrOutput__boFANN__bc",&B_qrOutput__boFANN__bc);
   t1->SetBranchAddress("B_qrOutput__boFBDT__bc",&B_qrOutput__boFBDT__bc);
   t1->SetBranchAddress("Flag",&flag);
   t1->SetBranchAddress("Scale",&scale);



   ostringstream strs1;
   strs1 << filename << "_train.root";
   str = strs1.str();
   char trainfile[200];
   strcpy(trainfile,(str).c_str());
   TFile *newfile = new TFile(trainfile,"recreate");
   TTree *tr = new TTree("y4s","y4s");
   tr->Branch("isSignal",&isSignal);
   tr->Branch("useCMSFrameLPdaughterLP1COpRPRP",&B_useCMSFrame__bop__bc);
   tr->Branch("deltaE",&B_deltae);
   tr->Branch("Mbc",&B_mbc);
   tr->Branch("ThrustB",&B_ThrustB);
   tr->Branch("ThrustO",&B_ThrustO);
   tr->Branch("CosTBTO",&B_CosTBTO);
   tr->Branch("CosTBz",&B_CosTBz);
   tr->Branch("R2",&B_R2);
   tr->Branch("CleoConeLP1COROERP",&B_cc1_CcROE);
   tr->Branch("CleoConeLP2COROERP",&B_cc2_CcROE);
   tr->Branch("CleoConeLP3COROERP",&B_cc3_CcROE);
   tr->Branch("CleoConeLP4COROERP",&B_cc4_CcROE);
   tr->Branch("CleoConeLP5COROERP",&B_cc5_CcROE);
   tr->Branch("CleoConeLP6COROERP",&B_cc6_CcROE);
   tr->Branch("CleoConeLP7COROERP",&B_cc7_CcROE);
   tr->Branch("CleoConeLP8COROERP",&B_cc8_CcROE);
   tr->Branch("CleoConeLP9COROERP",&B_cc9_CcROE);
   tr->Branch("CleoConeLP1RP",&B_cc1);
   tr->Branch("CleoConeLP2RP",&B_cc2);
   tr->Branch("CleoConeLP3RP",&B_cc3);
   tr->Branch("CleoConeLP4RP",&B_cc4);
   tr->Branch("CleoConeLP5RP",&B_cc5);
   tr->Branch("CleoConeLP6RP",&B_cc6);
   tr->Branch("CleoConeLP7RP",&B_cc7);
   tr->Branch("CleoConeLP8RP",&B_cc8);
   tr->Branch("CleoConeLP9RP",&B_cc9);
   tr->Branch("KSFWVariablesLPmm2RP",&B_mm2);
   tr->Branch("KSFWVariablesLPetRP",&B_et);
   tr->Branch("KSFWVariablesLPhso00RP",&B_hso00);
   tr->Branch("KSFWVariablesLPhso01RP",&B_hso01);
   tr->Branch("KSFWVariablesLPhso02RP",&B_hso02);
   tr->Branch("KSFWVariablesLPhso03RP",&B_hso03);
   tr->Branch("KSFWVariablesLPhso04RP",&B_hso04);
   tr->Branch("KSFWVariablesLPhso10RP",&B_hso10);
   tr->Branch("KSFWVariablesLPhso12RP",&B_hso12);
   tr->Branch("KSFWVariablesLPhso14RP",&B_hso14);
   tr->Branch("KSFWVariablesLPhso20RP",&B_hso20);
   tr->Branch("KSFWVariablesLPhso22RP",&B_hso22);
   tr->Branch("KSFWVariablesLPhso24RP",&B_hso24);
   tr->Branch("KSFWVariablesLPhoo0RP",&B_hoo0);
   tr->Branch("KSFWVariablesLPhoo1RP",&B_hoo1);
   tr->Branch("KSFWVariablesLPhoo2RP",&B_hoo2);
   tr->Branch("KSFWVariablesLPhoo3RP",&B_hoo3);
   tr->Branch("KSFWVariablesLPhoo4RP",&B_hoo4);
   tr->Branch("daughtersLP0COkaonIDRP",&B_mu_kaonID);
   tr->Branch("nTracks",&B_nTracks);
   tr->Branch("qrOutputLPFANNRP",&B_qrOutput__boFANN__bc);
   tr->Branch("qrOutputLPFBDTRP",&B_qrOutput__boFBDT__bc);
   tr->Branch("weight",&weight);
   tr->Branch("Flag",&flag);
   tr->Branch("Scale",&scale);

   Int_t trainsize;
   trainsize = Int_t(double(t1->GetEntries()*0.8));
   if(filename == "MC9signal") trainsize = Int_t(double(t1->GetEntries())*83934/143314*0.8);
   Int_t i=0;
   for (i=0;i<trainsize;i++) {
      t1->GetEntry(i);
      B_qrOutput__boFANN__bc = B_qrOutput__boFANN__bc*B_mu_charge;
      B_qrOutput__boFBDT__bc = B_qrOutput__boFBDT__bc*B_mu_charge;
      if(flag == 0) isSignal=1;
      else isSignal=0;
      if(isSignal==0) weight = 143314./83934;
      else weight = 1;
      tr->Fill();
   }
   tr->Write();
   newfile->Close();

   ostringstream strs2;
   strs2 << filename << "_test.root";
   str = strs2.str();
   char testfile[200];
   strcpy(testfile,(str).c_str());
   TFile *newfile2 = new TFile(testfile,"recreate");
   TTree *te = new TTree("y4s","y4s");
   te->Branch("isSignal",&isSignal);
   te->Branch("useCMSFrameLPdaughterLP1COpRPRP",&B_useCMSFrame__bop__bc);
   te->Branch("deltaE",&B_deltae);
   te->Branch("Mbc",&B_mbc);
   te->Branch("ThrustB",&B_ThrustB);
   te->Branch("ThrustO",&B_ThrustO);
   te->Branch("CosTBTO",&B_CosTBTO);
   te->Branch("CosTBz",&B_CosTBz);
   te->Branch("R2",&B_R2);
   te->Branch("CleoConeLP1COROERP",&B_cc1_CcROE);
   te->Branch("CleoConeLP2COROERP",&B_cc2_CcROE);
   te->Branch("CleoConeLP3COROERP",&B_cc3_CcROE);
   te->Branch("CleoConeLP4COROERP",&B_cc4_CcROE);
   te->Branch("CleoConeLP5COROERP",&B_cc5_CcROE);
   te->Branch("CleoConeLP6COROERP",&B_cc6_CcROE);
   te->Branch("CleoConeLP7COROERP",&B_cc7_CcROE);
   te->Branch("CleoConeLP8COROERP",&B_cc8_CcROE);
   te->Branch("CleoConeLP9COROERP",&B_cc9_CcROE);
   te->Branch("CleoConeLP1RP",&B_cc1);
   te->Branch("CleoConeLP2RP",&B_cc2);
   te->Branch("CleoConeLP3RP",&B_cc3);
   te->Branch("CleoConeLP4RP",&B_cc4);
   te->Branch("CleoConeLP5RP",&B_cc5);
   te->Branch("CleoConeLP6RP",&B_cc6);
   te->Branch("CleoConeLP7RP",&B_cc7);
   te->Branch("CleoConeLP8RP",&B_cc8);
   te->Branch("CleoConeLP9RP",&B_cc9);
   te->Branch("KSFWVariablesLPmm2RP",&B_mm2);
   te->Branch("KSFWVariablesLPetRP",&B_et);
   te->Branch("KSFWVariablesLPhso00RP",&B_hso00);
   te->Branch("KSFWVariablesLPhso01RP",&B_hso01);
   te->Branch("KSFWVariablesLPhso02RP",&B_hso02);
   te->Branch("KSFWVariablesLPhso03RP",&B_hso03);
   te->Branch("KSFWVariablesLPhso04RP",&B_hso04);
   te->Branch("KSFWVariablesLPhso10RP",&B_hso10);
   te->Branch("KSFWVariablesLPhso12RP",&B_hso12);
   te->Branch("KSFWVariablesLPhso14RP",&B_hso14);
   te->Branch("KSFWVariablesLPhso20RP",&B_hso20);
   te->Branch("KSFWVariablesLPhso22RP",&B_hso22);
   te->Branch("KSFWVariablesLPhso24RP",&B_hso24);
   te->Branch("KSFWVariablesLPhoo0RP",&B_hoo0);
   te->Branch("KSFWVariablesLPhoo1RP",&B_hoo1);
   te->Branch("KSFWVariablesLPhoo2RP",&B_hoo2);
   te->Branch("KSFWVariablesLPhoo3RP",&B_hoo3);
   te->Branch("KSFWVariablesLPhoo4RP",&B_hoo4);
   te->Branch("daughtersLP0COkaonIDRP",&B_mu_kaonID);
   te->Branch("nTracks",&B_nTracks);
   te->Branch("daughterLP0COchargeRP",&B_mu_charge);
   te->Branch("qrOutputLPFANNRP",&B_qrOutput__boFANN__bc);
   te->Branch("qrOutputLPFBDTRP",&B_qrOutput__boFBDT__bc);
   te->Branch("weight",&weight);
   te->Branch("Flag",&flag);
   te->Branch("Scale",&scale);
   float pick = 83934./143314;
   if (filename != "MC9signal") pick = 1;
   for (i=trainsize;i<t1->GetEntries()*pick;i++) {
      t1->GetEntry(i);
      B_qrOutput__boFANN__bc = B_qrOutput__boFANN__bc*B_mu_charge;
      B_qrOutput__boFBDT__bc = B_qrOutput__boFBDT__bc*B_mu_charge;
      if(flag == 0) isSignal=1;
      else isSignal=0;
      if(isSignal==0) weight = 143314./83934;
      else weight = 1;
      te->Fill();
   }
   te->Write();
   newfile2->Close();
}
void merge3()
{
   TChain *chn = new TChain("y4s");
   chn->Add("*_train.root");
   chn->Merge("train.root");
   cout<<"dataset for training added"<<endl;
   delete chn;
   chn = new TChain("y4s");
   chn->Add("*_test.root");
   chn->Merge("test.root");
   cout<<"dataset for testing added"<<endl;
   delete chn;

}
