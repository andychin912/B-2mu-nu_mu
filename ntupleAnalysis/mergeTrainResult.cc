void mergeTrainResult()
{
   Float_t TrainOut;
   Float_t TrainTrans;
   TFile *f1 = new TFile("CSexpert.root");
   TTree *t1 = (TTree*)f1->Get("variables");
   t1 -> SetBranchAddress("CSFastBDT_500__ptxml",&TrainOut);
   TFile *f2 = new TFile("MC9.root","update");
   TTree *t2 = (TTree*)f2->Get("y4s");
   TBranch *b1 = t2->Branch("TrainOut",&TrainOut);
   TBranch *b2 = t2->Branch("TrainTrans",&TrainTrans);
   for (int i=0;i<t2->GetEntries();i++)
   {
      t1->GetEntry(i);
      TrainTrans = log((TrainOut-0.5)/(1-TrainOut));
      b1->Fill();
      b2->Fill();
   }
   t2->Write();
   f1->Close();
   f2->Close();
}
