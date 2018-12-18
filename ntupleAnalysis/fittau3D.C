using namespace RooFit;
using namespace RooStats;
void fittau3D(){
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   TFile* f1 = new TFile("MC9.root");
   TTree* tr = (TTree*)f1->Get("y4s");
   RooRealVar Flag("Flag","Flag",0,0,13);
   RooRealVar Mbc("Mbc","Mbc",5.1,5.29);
   RooRealVar TrainOut("TrainOut","TrainOut",0.5,0.,1.);
   RooRealVar useCMSFrameLPdaughterLP1COpRPRP("useCMSFrameLPdaughterLP1COpRPRP","useCMSFrameLPdaughterLP1COpRPRP",2.2,3.1);
   RooRealVar TrainTrans("TrainTrans","TrainTrans",-7,-7,12);
   RooDataSet data("data","data",RooArgSet(Flag,useCMSFrameLPdaughterLP1COpRPRP,Mbc,TrainTrans,TrainOut),Import(*tr),Cut("Flag==4&&TrainOut>=0.5&&TrainTrans>-7&&TrainTrans<12"));
   RooDataSet sigbox("sigbox","sigbox",RooArgSet(Flag,useCMSFrameLPdaughterLP1COpRPRP,Mbc,TrainTrans,TrainOut),Import(*tr),Cut("Flag==4&&TrainOut>=0.5&&TrainTrans>-7&&TrainTrans<12&&useCMSFrameLPdaughterLP1COpRPRP>2.45&&useCMSFrameLPdaughterLP1COpRPRP<2.85"));

   //-----------fit for Mbc-----------
   //Argus
   RooRealVar Mbcstop("Mbcstop","Mbcstop",5.28985,5.1,5.30);
   RooRealVar Mbcc("Mbcc","Mbcc",-19.3098,-50.0,0.);
   RooArgusBG Mbctau("Mbctau","Mbctau",Mbc,Mbcstop,Mbcc);
  
   /*RooFitResult *r1 = Mbctau.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame1 = Mbc.frame(Title("Mbctau"));
   data.plotOn(frame1);
   Mbctau.plotOn(frame1);
   frame1->Draw();*/

   //----------fit for Mom------------
   //Gaussian 1
   RooRealVar Mommean("Mommean","Mommean",3.28804,-100,3.5);
   RooRealVar Momsigma("Momsigma","Momsigma",0.681075,0,1);
   RooGaussian Momtau("Momtau","Momtau",useCMSFrameLPdaughterLP1COpRPRP,Mommean,Momsigma);

   /*RooFitResult *r2 = Momtau.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame2 = useCMSFrameLPdaughterLP1COpRPRP.frame(Title("Momtau"));
   data.plotOn(frame2);
   Momtau.plotOn(frame2);
   frame2->Draw();*/
   
   //--------------fit for Train result---------------
   //Bifurcated Gaussian
   RooRealVar Trainmean("Trainmean","Trainmean",-0.303386,-0.5,3);
   RooRealVar Trainsigma1("Trainsigma1","Trainsigma1",1.77225,0,5);
   RooRealVar Trainsigma2("Trainsigma2","Trainsigma2",1.81385,0,3);
   RooBifurGauss Traintau1("Traintau1","Traintau1",TrainTrans,Trainmean,Trainsigma1,Trainsigma2);

   //Breit Wigner
   RooRealVar Traingamma("Traingamma","Traingamma",1.93855,-1,100);
   RooBreitWigner Traintau2("Traintau2","Traintau2",TrainTrans,Trainmean,Traingamma);
   
   //Add Train result PDF
   RooRealVar Trainm1("Trainm1","Trainm1",0.888939,0,1.);
   RooAddPdf Traintau("Traintau","Traintau",RooArgList(Traintau1,Traintau2),RooArgList(Trainm1));
   
   /*RooFitResult *r3 = Traintau.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame3 = TrainTrans.frame(Title("tau"));
   data.plotOn(frame3);
   Traintau.plotOn(frame3);
   frame3->Draw()/;*/

   //--------------3D PDF------------------
   RooProdPdf tau("tau","tau",RooArgSet(Mbctau,Momtau,Traintau));
   RooFitResult *result = tau.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame01 = Mbc.frame(Title("Mbctau"));
   data.plotOn(frame01);
   tau.plotOn(frame01);
   RooPlot* frame02 = TrainTrans.frame(Title("Traintau"));
   data.plotOn(frame02);
   tau.plotOn(frame02);
   RooPlot* frame03 = useCMSFrameLPdaughterLP1COpRPRP.frame(Title("Momtau"));
   data.plotOn(frame03);
   tau.plotOn(frame03);
   TCanvas *c1 = new TCanvas("c1","",1);
   frame01->Draw();
   c1->SaveAs("~/Ntuples_ROE/tauMbc.eps");
   TCanvas *c2 = new TCanvas("c2","",1);
   frame02->Draw();
   c2->SaveAs("~/Ntuples_ROE/tauTrain.eps");
   TCanvas *c3 = new TCanvas("c3","",1);
   frame03->Draw();
   c3->SaveAs("~/Ntuples_ROE/tauMom.eps");

}
