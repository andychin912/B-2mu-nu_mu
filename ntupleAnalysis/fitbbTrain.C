using namespace RooFit;
using namespace RooStats;
void fitbbTrain(){
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   TFile* f1 = new TFile("MC9.root");
   TTree* tr = (TTree*)f1->Get("y4s");
   RooRealVar useCMSFrameLPdaughterLP1COpRPRP("useCMSFrameLPdaughterLP1COpRPRP","useCMSFrameLPdaughterLP1COpRPRP",2.2,3.1);
   RooRealVar mean1("a","a",0.568028,-1,100);
   RooRealVar mean2("a1","a1",2.27617,-5,5);
   RooRealVar sigma1("b","b",2.27617,0,10);
   RooRealVar sigma2("b1","b1",3.17328,0,5);
   RooRealVar sigma3("b2","b2",1.41742,0,3);
   RooRealVar sigma4("b3","b3",1.58287,0,3);
   RooRealVar Flag("Flag","Flag",0,0,13);
   RooRealVar TrainOut("TrainOut","TrainOut",0.5,0.5,1.);
   RooRealVar TrainTrans("TrainTrans","TrainTrans",-7,-7,12);
   RooBifurGauss bb1("bb1","bb1",TrainTrans,mean1,sigma1,sigma2);
   RooBifurGauss bb2("bb2","bb2",TrainTrans,mean1,sigma3,sigma4);
   //RooGaussian bb2("bb2","bb2",TrainTrans,mean2,bbma2);
   RooRealVar m1("m1","m1",0.508471,0,1.);
   //RooRealVar m2("m2","m2",0.632397,0.5,1);
   RooAddPdf bb("bb","bb",RooArgList(bb1,bb2),RooArgList(m1));
   RooDataSet data("data","data",RooArgSet(TrainOut,TrainTrans,useCMSFrameLPdaughterLP1COpRPRP,Flag),Import(*tr),Cut("Flag==1&&TrainOut>0.5"));
   RooFitResult *r = bb.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame = TrainTrans.frame(Title("bb"));
   data.plotOn(frame);
   bb.plotOn(frame);
   frame->Draw();

   //TH1F* h1 = new TH1F("h1","h1",1000,4.9,5.9);
   //nt->Draw("mass>>h1");
   //TF1* fu1 = new TF1("fu1","gaus(0)+[3]*TMath::BreitWigner(x,[4],[5])");
   //fu1->SetParameters(250,5.2,0.04,25,5.5,0.5);
   //h1->Fit("fu1");

}
