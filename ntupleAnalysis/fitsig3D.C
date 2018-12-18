using namespace RooFit;
using namespace RooStats;
void fitsig3D(){
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   TFile* f1 = new TFile("MC9.root");
   TTree* tr = (TTree*)f1->Get("y4s");
   RooRealVar Flag("Flag","Flag",0,0,13);
   RooRealVar Mbc("Mbc","Mbc",5.1,5.29);
   RooRealVar TrainOut("TrainOut","TrainOut",0.5,0.,1.);
   RooRealVar useCMSFrameLPdaughterLP1COpRPRP("useCMSFrameLPdaughterLP1COpRPRP","useCMSFrameLPdaughterLP1COpRPRP",2.2,3.1);
   RooRealVar TrainTrans("TrainTrans","TrainTrans",-7,-7,12);
   RooDataSet data("data","data",RooArgSet(Flag,useCMSFrameLPdaughterLP1COpRPRP,Mbc,TrainTrans,TrainOut),Import(*tr),Cut("Flag==0&&TrainOut>=0.5&&TrainTrans>-7&&TrainTrans<12"));
   RooDataSet sigbox("sigbox","sigbox",RooArgSet(Flag,useCMSFrameLPdaughterLP1COpRPRP,Mbc,TrainTrans,TrainOut),Import(*tr),Cut("Flag==0&&TrainOut>=0.5&&TrainTrans>-7&&TrainTrans<12&&useCMSFrameLPdaughterLP1COpRPRP>2.45&&useCMSFrameLPdaughterLP1COpRPRP<2.85"));

   //-----------fit for Mbc-----------
   //Argus1
   RooRealVar Mbcstop("Mbcstop","Mbcstop",5.29);
   RooRealVar Mbcc("Mbcc","Mbcc",-33.5165,-200.,0.);
   RooArgusBG Mbcsig1("Mbcsig1","Mbcsig1",Mbc,Mbcstop,Mbcc);
   
   //Argus2
   RooRealVar Mbcc2("Mbcc2","Mbcc2",-105.646,-200.,0.);
   RooArgusBG Mbcsig2("Mbcsig2","Mbcsig2",Mbc,Mbcstop,Mbcc2);

   //Breit Wigner
   RooRealVar Mbcmean("Mbcmean","Mbcmean",5.27363,5.1,5.29);
   RooRealVar Mbcgamma("Mbcgamma","Mbcgamma",0.00980522,0,20);   
   RooBreitWigner Mbcsig3("Mbcsig3","Mbcsig3",Mbc,Mbcmean,Mbcgamma);
   
   //Add Mbc Pdf
   RooRealVar Mbcm1("Mbcm1","Mbcm1",0.504986,0,1);
   RooRealVar Mbcm2("Mbcm2","Mbcm2",0.477504,0,1);
   RooAddPdf Mbcsig("Mbcsig","Mbcsig",RooArgList(Mbcsig1,Mbcsig2,Mbcsig3),RooArgList(Mbcm1,Mbcm2));
   
   /*RooFitResult *r1 = Mbcsig.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame1 = Mbc.frame(Title("Mbcsig"));
   data.plotOn(frame1);
   Mbcsig.plotOn(frame1);
   frame1->Draw();*/

   //----------fit for Mom------------
   //Left Bifurcated Gaussian
   RooRealVar Mommean1("Mommean1","Mommean1",2.50199,2.35,2.65);
   RooRealVar MomsigmaS1("MomsigmaS1","MomsigmaS1",0.0233402,0,0.1);
   RooRealVar MomsigmaL1("MomsigmaL1","MomsigmaL1",0.0672146,0,1);
   RooBifurGauss Momsig1("Momsig1","Momsig1",useCMSFrameLPdaughterLP1COpRPRP,Mommean1,MomsigmaS1,MomsigmaL1);
      
   //Right Bifurcated Gaussian
   RooRealVar Mommean2("Mommean2","Mommean2",2.77907,2.65,2.85);
   RooRealVar MomsigmaS2("MomsigmaS2","MomsigmaS2",0.0281937,0,0.1);
   RooRealVar MomsigmaL2("MomsigmaL2","MomsigmaL2",0.0808619,0,1);
   RooBifurGauss Momsig2("Momsig2","Momsig2",useCMSFrameLPdaughterLP1COpRPRP,Mommean2,MomsigmaL2,MomsigmaS2);

   //Left Gaussian
   RooRealVar Mommeans1("Mommeans1","Mommeans1",2.48235,2.1,2.65);
   RooRealVar Momsigmas1("Momsigmas1","Momsigmas1",0.155070,0,1);
   RooGaussian Momsig3("Momsig3","Momsig3",useCMSFrameLPdaughterLP1COpRPRP,Mommeans1,Momsigmas1);
   
   //Right Gaussian
   RooRealVar Mommeans2("Mommeans2","Mommeans2",2.62973,2.45,2.95);
   RooRealVar Momsigmas2("Momsigmas2","Momsigmas2",0.0699447,0,1);
   RooGaussian Momsig4("Momsig4","Momsig4",useCMSFrameLPdaughterLP1COpRPRP,Mommeans2,Momsigmas2);

   //Add Mom Pdf
   RooRealVar Momm1("Momm1","Momm1",0.294327,0,1);
   RooRealVar Momm2("Momm2","Momm2",0.372657,0,1);
   RooRealVar Momm3("Momm3","Momm3",0.0191646,0,1);
   RooAddPdf Momsig("Momsig","Momsig",RooArgList(Momsig1,Momsig2,Momsig3,Momsig4),RooArgList(Momm1,Momm2,Momm3));

   /*RooFitResult *r2 = Momsig.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame2 = useCMSFrameLPdaughterLP1COpRPRP.frame(Title("Momsig"));
   data.plotOn(frame2);
   Momsig.plotOn(frame2);
   frame2->Draw();*/
   
   //--------------fit for Train result---------------
   //Bifurcated Gaussian 1
   RooRealVar Trainmean1("Trainmean1","Trainmean1",3.30435,0.9,100);
   RooRealVar Trainsigma1("Trainsigma1","Trainsigma1",3.21718,0,5);
   RooRealVar Trainsigma2("Trainsigma2","Trainsigma2",2.81852,0,3);
   RooBifurGauss Trainsig1("Trainsig1","Trainsig1",TrainTrans,Trainmean1,Trainsigma1,Trainsigma2);

   //Bifurcated Gaussian 2
   RooRealVar Trainmean2("Trainmean2","Trainmean2",1.55204,1,100);
   RooRealVar Trainsigma3("Trainsigma3","Trainsigma3",1.73782,0,3);
   RooRealVar Trainsigma4("Trainsigma4","Trainsigma4",1.68524,0,3);
   RooBifurGauss Trainsig2("Trainsig2","Trainsig2",TrainTrans,Trainmean2,Trainsigma3,Trainsigma4);
   
   //Add Train result PDF
   RooRealVar Trainm1("Trainm1","Trainm1",0.338180,0,1.);
   RooAddPdf Trainsig("Trainsig","Trainsig",RooArgList(Trainsig1,Trainsig2),RooArgList(Trainm1));
   
   /*RooFitResult *r3 = Trainsig.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame3 = TrainTrans.frame(Title("sig"));
   data.plotOn(frame3);
   Trainsig.plotOn(frame3);
   frame3->Draw();*/

   //--------------3D PDF------------------
   RooProdPdf sig("sig","sig",RooArgSet(Mbcsig,Momsig,Trainsig));
   RooFitResult *result = sig.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame01 = Mbc.frame(Title("Mbcsig"));
   sigbox.plotOn(frame01);
   sig.plotOn(frame01);
   RooPlot* frame02 = TrainTrans.frame(Title("Trainsig"));
   sigbox.plotOn(frame02);
   sig.plotOn(frame02);
   RooPlot* frame03 = useCMSFrameLPdaughterLP1COpRPRP.frame(Title("Momsig"));
   data.plotOn(frame03);
   sig.plotOn(frame03);
   TCanvas *c1 = new TCanvas("c1","",1);
   frame01->Draw();
   c1->SaveAs("~/Ntuples_ROE/sigMbc.eps");
   TCanvas *c2 = new TCanvas("c2","",1);
   frame02->Draw();
   c2->SaveAs("~/Ntuples_ROE/sigTrain.eps");
   TCanvas *c3 = new TCanvas("c3","",1);
   frame03->Draw();
   c3->SaveAs("~/Ntuples_ROE/sigMom.eps");

}
