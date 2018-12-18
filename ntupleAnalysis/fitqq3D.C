using namespace RooFit;
using namespace RooStats;
void fitqq3D(){
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   TFile* f1 = new TFile("MC9.root");
   TTree* tr = (TTree*)f1->Get("y4s");
   RooRealVar Flag("Flag","Flag",0,0,13);
   RooRealVar Mbc("Mbc","Mbc",5.1,5.29);
   RooRealVar TrainOut("TrainOut","TrainOut",0.5,0.,1.);
   RooRealVar useCMSFrameLPdaughterLP1COpRPRP("useCMSFrameLPdaughterLP1COpRPRP","useCMSFrameLPdaughterLP1COpRPRP",2.2,3.1);
   RooRealVar TrainTrans("TrainTrans","TrainTrans",-7,-7,12);
   RooDataSet data("data","data",RooArgSet(Flag,useCMSFrameLPdaughterLP1COpRPRP,Mbc,TrainTrans,TrainOut),Import(*tr),Cut("(Flag==2||Flag==3)&&TrainOut>=0.5&&TrainTrans>-7&&TrainTrans<12"));
   RooDataSet sigbox("sigbox","sigbox",RooArgSet(Flag,useCMSFrameLPdaughterLP1COpRPRP,Mbc,TrainTrans,TrainOut),Import(*tr),Cut("(Flag==2||Flag==3)&&TrainOut>=0.5&&TrainTrans>-7&&TrainTrans<12&&useCMSFrameLPdaughterLP1COpRPRP>2.45&&useCMSFrameLPdaughterLP1COpRPRP<2.85"));

   //-----------fit for Mbc-----------
   //Argus
   RooRealVar Mbcstop("Mbcstop","Mbcstop",5.28986,5.1,5.3);
   RooRealVar Mbcc("Mbcc","Mbcc",-28.2556,-50.0,0.);   
   RooArgusBG Mbcqq("Mbcqq","Mbcqq",Mbc,Mbcstop,Mbcc);

   RooFitResult *r1 = Mbcqq.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame1 = Mbc.frame(Title("Mbcqq"));
   data.plotOn(frame1);
   Mbcqq.plotOn(frame1);
   frame1->Draw();

   //----------fit for Mom------------
   //Gaussian
   RooRealVar Mommean("Mommean","Mommean",2.52060,-100,3.1);
   RooRealVar Momsigma("Momsigma","Momsigma",0.599526,0,1);
   RooGaussian Momqq("Momqq","Momqq",useCMSFrameLPdaughterLP1COpRPRP,Mommean,Momsigma);
      
   RooFitResult *r2 = Momqq.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame2 = useCMSFrameLPdaughterLP1COpRPRP.frame(Title("Momqq"));
   data.plotOn(frame2);
   Momqq.plotOn(frame2);
   frame2->Draw();
   
   //--------------fit for Train result---------------
   //Bifurcated Gaussian
   RooRealVar Trainmean("Trainmean","Trainmean",-0.306833,-5,100);
   RooRealVar Trainsigma1("Trainsigma1","Trainsigma1",1.86046,0,5);
   RooRealVar Trainsigma2("Trainsigma2","Trainsigma2",1.44270,0,3);
   RooBifurGauss Trainqq1("Trainqq1","Trainqq1",TrainTrans,Trainmean,Trainsigma1,Trainsigma2);

   //Breit Wigner
   RooRealVar Traingamma("Traingamma","Traingamma",1.04693,0,3);
   RooBreitWigner Trainqq2("Trainqq2","Trainqq2",TrainTrans,Trainmean,Traingamma);
   
   //Add Train result PDF
   RooRealVar Trainm1("Trainm1","Trainm1",0.904033,0,1.);
   RooAddPdf Trainqq("Trainqq","Trainqq",RooArgList(Trainqq1,Trainqq2),RooArgList(Trainm1));
   
   /*RooFitResult *r3 = Trainqq.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame3 = TrainTrans.frame(Title("qq"));
   data.plotOn(frame3);
   Trainqq.plotOn(frame3);
   frame3->Draw();*/

   //--------------3D PDF------------------
   RooProdPdf qq("qq","qq",RooArgSet(Mbcqq,Momqq,Trainqq));
   RooFitResult *result = qq.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame01 = Mbc.frame(Title("Mbcqq"));
   data.plotOn(frame01);
   qq.plotOn(frame01);
   RooPlot* frame02 = TrainTrans.frame(Title("Trainqq"));
   data.plotOn(frame02);
   qq.plotOn(frame02);
   RooPlot* frame03 = useCMSFrameLPdaughterLP1COpRPRP.frame(Title("Momqq"));
   data.plotOn(frame03);
   qq.plotOn(frame03);
   TCanvas *c1 = new TCanvas("c1","",1);
   frame01->Draw();
   c1->SaveAs("~/Ntuples_ROE/qqMbc.eps");
   TCanvas *c2 = new TCanvas("c2","",1);
   frame02->Draw();
   c2->SaveAs("~/Ntuples_ROE/qqTrain.eps");
   TCanvas *c3 = new TCanvas("c3","",1);
   frame03->Draw();
   c3->SaveAs("~/Ntuples_ROE/qqMom.eps");

}
