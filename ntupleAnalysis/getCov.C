{
  TFile *MCfile = new TFile("MC9.root");
  TTree *tr = (TTree*)MCfile->Get("y4s");
  int bin = 1000;

  TH2F* mpbb = new TH2F("mpbb","mpbb",bin,5.1,5.29,bin,2.2,3.1);
  TH2F* mpqq = new TH2F("mpqq","mpqq",bin,5.1,5.29,bin,2.2,3.1);
  TH2F* mptau = new TH2F("mptau","mptau",bin,5.1,5.29,bin,2.2,3.1);
  TH2F* mps = new TH2F("mps","mps",bin,5.1,5.29,bin,2.2,3.1);
  tr->Draw("useCMSFrameLPdaughterLP1COpRPRP:Mbc>>mpbb","1*(Flag==1)&&TrainOut>0.5");
  tr->Draw("useCMSFrameLPdaughterLP1COpRPRP:Mbc>>mpqq","1*(Flag==2||Flag==3)&&TrainOut>0.5");
  tr->Draw("useCMSFrameLPdaughterLP1COpRPRP:Mbc>>mptau","1*(Flag==4)&&TrainOut>0.5");
  tr->Draw("useCMSFrameLPdaughterLP1COpRPRP:Mbc>>mps","(Flag==0)&&TrainOut>0.5");
  cout<<"Mbc p correlation for bb : "<<mpbb->GetCorrelationFactor()<<endl;
  cout<<"Mbc p correlation for qq : "<<mpqq->GetCorrelationFactor()<<endl;
  cout<<"Mbc p correlation for tau: "<<mptau->GetCorrelationFactor()<<endl;
  cout<<"Mbc p correlation for sig: "<<mps->GetCorrelationFactor()<<endl;
  /*Float_t p;
  Float_t Mbc;
  Float_t TrainOut;
  double sump=0;
  double sumMbc=0;
  double avgp;
  double avgMbc;
  double j=0;
  tr->SetBranchAddress("Mbc",&Mbc);
  tr->SetBranchAddress("useCMSFrameLPdaughterLP1COpRPRP",&p);
  tr->SetBranchAddress("TrainOut",&TrainOut);
  for (int i=0;i<83934;i++)
  {
    tr->GetEntry(i);
    if(TrainOut>0.5){
      sump=sump+p;
      sumMbc=sumMbc+Mbc;
      j++;
    }    
  }
  avgp=sump/j;
  avgMbc=sumMbc/j;
  double numerator=0;
  double stdMbc=0;
  double stdp=0;
  for (int i=0;i<83934;i++)
  {
    tr->GetEntry(i);
    if(TrainOut>0.5){
      numerator=numerator+(Mbc-avgMbc)*(p-avgp);
      stdMbc=stdMbc+(Mbc-avgMbc)*(Mbc-avgMbc);
      stdp=stdp+(p-avgp)*(p-avgp);
    }    
  }
  cout<<numerator/sqrt(stdp*stdMbc);*/


  TH2F* mtbb = new TH2F("mtbb","mtbb",bin,5.1,5.29,bin,-7.,12.);
  TH2F* mtqq = new TH2F("mtqq","mtqq",bin,5.1,5.29,bin,-7.,12.);
  TH2F* mttau = new TH2F("mttau","mttau",bin,5.1,5.29,bin,-7.,12.);
  TH2F* mts = new TH2F("mts","mts",bin,5.1,5.29,bin,-7.,12.);
  tr->Draw("TrainTrans:Mbc>>mtbb","1*(Flag==1)&&TrainOut>0.5");
  tr->Draw("TrainTrans:Mbc>>mtqq","1*(Flag==2||Flag==3)&&TrainOut>0.5");
  tr->Draw("TrainTrans:Mbc>>mttau","1*(Flag==4)&&TrainOut>0.5");
  tr->Draw("TrainTrans:Mbc>>mts","(Flag==0)&&TrainOut>0.5");
  cout<<"Mbc TrainTrans correlation for bb : "<<mtbb->GetCorrelationFactor()<<endl;
  cout<<"Mbc TrainTrans correlation for qq : "<<mtqq->GetCorrelationFactor()<<endl;
  cout<<"Mbc TrainTrans correlation for tau: "<<mttau->GetCorrelationFactor()<<endl;
  cout<<"Mbc TrainTrans correlation for sig: "<<mts->GetCorrelationFactor()<<endl;
  TH2F* ptbb = new TH2F("ptbb","ptbb",bin,-7.,12.,bin,2.2,3.1);
  TH2F* ptqq = new TH2F("ptqq","ptqq",bin,-7.,12.,bin,2.2,3.1);
  TH2F* pttau = new TH2F("pttau","pttau",bin,-7.,12.,bin,2.2,3.1);
  TH2F* pts = new TH2F("pts","pts",bin,-7.,12.,bin,2.2,3.1);
  tr->Draw("useCMSFrameLPdaughterLP1COpRPRP:TrainTrans>>ptbb","1*(Flag==1)&&TrainOut>0.5");
  tr->Draw("useCMSFrameLPdaughterLP1COpRPRP:TrainTrans>>ptqq","1*(Flag==2||Flag==3)&&TrainOut>0.5");
  tr->Draw("useCMSFrameLPdaughterLP1COpRPRP:TrainTrans>>pttau","1*(Flag==4)&&TrainOut>0.5");
  tr->Draw("useCMSFrameLPdaughterLP1COpRPRP:TrainTrans>>pts","useCMSFrameLPdaughterLP1COpRPRP>2.45&&useCMSFrameLPdaughterLP1COpRPRP<2.85&&(Flag==0)&&TrainOut>0.5&&TrainTrans<7&&TrainTrans>-3");
  cout<<"p TrainTrans correlation for bb : "<<ptbb->GetCorrelationFactor()<<endl;
  cout<<"p TrainTrans correlation for qq : "<<ptqq->GetCorrelationFactor()<<endl;
  cout<<"p TrainTrans correlation for tau: "<<pttau->GetCorrelationFactor()<<endl;
  cout<<"p TrainTrans correlation for sig: "<<pts->GetCorrelationFactor()<<endl;

 }
