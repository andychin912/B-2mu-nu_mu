int issignal()
{  
   //get TTree
   TFile *myfile = new TFile("~/B+2mu+nu_mu/B+2mu+nu_mu2.root");
   TTree* mytree;
   myfile->GetObject("muon",mytree);
   mytree->SetBranchStatus("*",1);
   mytree->SetBranchStatus("B_mu_P",1);
   mytree->SetBranchStatus("B_mu_mcErrors",1);
   mytree->Draw("B_mu_P>>h1(100,0,10)");
   mytree->SetLineColor(38);
   mytree->Draw("B_mu_P>>h2(100,0,10)","(B_mu_mcErrors==0)","same");

   return 0;
}
