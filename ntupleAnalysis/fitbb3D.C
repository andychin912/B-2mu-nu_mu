using namespace RooFit;
using namespace RooStats;
void fitbb3D(){
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   TFile* f1 = new TFile("MC9.root");
   TTree* tr = (TTree*)f1->Get("y4s");
   RooRealVar Flag("Flag","Flag",0,0,13);
   RooRealVar Mbc("Mbc","Mbc",5.1,5.29);
   RooRealVar TrainOut("TrainOut","TrainOut",0.5,0.,1.);
   RooRealVar useCMSFrameLPdaughterLP1COpRPRP("useCMSFrameLPdaughterLP1COpRPRP","useCMSFrameLPdaughterLP1COpRPRP",2.2,3.1);
   RooRealVar TrainTrans("TrainTrans","TrainTrans",-7,-7,12);
   RooDataSet data("data","data",RooArgSet(Flag,useCMSFrameLPdaughterLP1COpRPRP,Mbc,TrainTrans,TrainOut),Import(*tr),Cut("Flag==1&&TrainOut>=0.5&&TrainTrans>-7&&TrainTrans<12"));
   RooDataSet sigbox("sigbox","sigbox",RooArgSet(Flag,useCMSFrameLPdaughterLP1COpRPRP,Mbc,TrainTrans,TrainOut),Import(*tr),Cut("Flag==1&&TrainOut>=0.5&&TrainTrans>-7&&TrainTrans<12&&useCMSFrameLPdaughterLP1COpRPRP>2.45&&useCMSFrameLPdaughterLP1COpRPRP<2.85"));

   //-----------fit for Mbc-----------
   //Argus1
   RooRealVar Mbcstop1("Mbcstop1","Mbcstop1",5.28982,5.1,5.29);
   RooRealVar Mbcc("Mbcc","Mbcc",-23.4797,-50.0,0.);
   RooArgusBG Mbcbb1("Mbcbb1","Mbcbb1",Mbc,Mbcstop1,Mbcc);
   
   //Argus2
   RooRealVar Mbcstop2("Mbcstop2","Mbcstop2",5.28982,5.1,5.29);
   RooRealVar Mbcc2("Mbcc2","Mbcc2",-103.914,-120.,0.);
   RooArgusBG Mbcbb2("Mbcbb2","Mbcbb2",Mbc,Mbcstop2,Mbcc2);

   //Add Mbc Pdf
   RooRealVar Mbcm1("Mbcm1","Mbcm1",0.820154,0,1);
   RooAddPdf Mbcbb("Mbcbb","Mbcbb",RooArgList(Mbcbb1,Mbcbb2),RooArgList(Mbcm1));
   
   /*RooFitResult *r1 = Mbcbb.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame1 = Mbc.frame(Title("Mbcbb"));
   data.plotOn(frame1);
   Mbcbb.plotOn(frame1);
   frame1->Draw();*/

   //----------fit for Mom------------
   //Gaussian 1
   RooRealVar Mommean1("Mommean1","Mommean1",1.93134,-100,2.2);
   RooRealVar Momsigma1("Momsigma1","Momsigma1",0.212495,0,2.2);
   RooGaussian Mombb1("Mombb1","Mombb1",useCMSFrameLPdaughterLP1COpRPRP,Mommean1,Momsigma1);
      
   //Gaussian 2
   RooRealVar Mommean2("Mommean2","Mommean2",2.45027,2.3,2.5);
   RooRealVar Momsigma2("Momsigma2","Momsigma2",0.103744,0,0.2);
   RooGaussian Mombb2("Mombb2","Mombb2",useCMSFrameLPdaughterLP1COpRPRP,Mommean2,Momsigma2);

   //Add Mom Pdf
   RooRealVar Momm1("Momm1","Momm1",0.748008,0,1);
   RooAddPdf Mombb("Mombb","Mombb",RooArgList(Mombb1,Mombb2),RooArgList(Momm1));

   /*RooFitResult *r2 = Mombb.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame2 = useCMSFrameLPdaughterLP1COpRPRP.frame(Title("Mombb"));
   data.plotOn(frame2);
   Mombb.plotOn(frame2);
   frame2->Draw();*/
   
   //--------------fit for Train result---------------
   //Bifurcated Gaussian 1
   RooRealVar Trainmean("Trainmean","Trainmean",0.568028,-1,100);
   RooRealVar Trainsigma1("Trainsigma1","Trainsigma1",2.27617,0,10);
   RooRealVar Trainsigma2("Trainsigma2","Trainsigma2",3.17328,0,5);
   RooBifurGauss Trainbb1("Trainbb1","Trainbb1",TrainTrans,Trainmean,Trainsigma1,Trainsigma2);

   //Bifurcated Gaussian 2
   RooRealVar Trainsigma3("Trainsigma3","Trainsigma3",1.41742,0,3);
   RooRealVar Trainsigma4("Trainsigma4","Trainsigma4",1.58287,0,3);
   RooBifurGauss Trainbb2("Trainbb2","Trainbb2",TrainTrans,Trainmean,Trainsigma3,Trainsigma4);
   
   //Add Train result PDF
   RooRealVar Trainm1("Trainm1","Trainm1",0.508471,0,1.);
   RooAddPdf Trainbb("Trainbb","Trainbb",RooArgList(Trainbb1,Trainbb2),RooArgList(Trainm1));
   
   /*RooFitResult *r3 = Trainbb.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame3 = TrainTrans.frame(Title("bb"));
   data.plotOn(frame3);
   Trainbb.plotOn(frame3);
   frame3->Draw();*/

   //--------------3D PDF------------------
   RooProdPdf bb("bb","bb",RooArgSet(Mbcbb,Mombb,Trainbb));
   RooFitResult *result = bb.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame01 = Mbc.frame(Title("Mbcbb"));
   data.plotOn(frame01);
   bb.plotOn(frame01);
   RooPlot* frame02 = TrainTrans.frame(Title("Trainbb"));
   data.plotOn(frame02);
   bb.plotOn(frame02);
   RooPlot* frame03 = useCMSFrameLPdaughterLP1COpRPRP.frame(Title("Mombb"));
   data.plotOn(frame03);
   bb.plotOn(frame03);
   TCanvas *c1 = new TCanvas("c1","",1);
   frame01->Draw();
   c1->SaveAs("~/Ntuples_ROE/bbMbc.eps");
   TCanvas *c2 = new TCanvas("c2","",1);
   frame02->Draw();
   c2->SaveAs("~/Ntuples_ROE/bbTrain.eps");
   TCanvas *c3 = new TCanvas("c3","",1);
   frame03->Draw();
   c3->SaveAs("~/Ntuples_ROE/bbMom.eps");

}
