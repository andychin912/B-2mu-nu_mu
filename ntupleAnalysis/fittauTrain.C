using namespace RooFit;
using namespace RooStats;
void fittauTrain(){
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   TFile* f1 = new TFile("MC9.root");
   TTree* tr = (TTree*)f1->Get("y4s");
   RooRealVar useCMSFrameLPdaughterLP1COpRPRP("useCMSFrameLPdaughterLP1COpRPRP","useCMSFrameLPdaughterLP1COpRPRP",2.2,3.1);
   RooRealVar mean1("a","a",-0.303386,-0.5,3);
   RooRealVar mean2("a1","a1",-0.386162,-0.5,0.5);
   RooRealVar mean3("a2","a2",1.,-5,100);
   RooRealVar sigma1("b","b",1.77225,0,5);
   RooRealVar sigma2("b1","b1",1.81385,0,3);
   RooRealVar sigma3("b2","b2",1.93855,-1,100);
   RooRealVar sigma4("b3","b3",1.02359,0,3);
   RooRealVar sigma5("b5","b5",0.1,0,0.5);
   RooRealVar power("p","p",1.53588,0,1000);
   RooRealVar Flag("Flag","Flag",0,0,13);
   RooRealVar TrainOut("TrainOut","TrainOut",0.5,0.5,1.);
   RooRealVar TrainTrans("TrainTrans","TrainTrans",-7,-7,12);
   RooBifurGauss tau1("tau1","tau1",TrainTrans,mean1,sigma1,sigma2);
   RooBreitWigner tau2("tau2","tau2",TrainTrans,mean1,sigma3);
   RooGaussian tau3("tau3","tau3",TrainTrans,mean3,sigma5);
   //RooGaussian tau2("tau2","tau2",TrainTrans,mean2,sigma2);
   RooRealVar m1("m1","m1",0.888939,0,1.);
   RooRealVar m2("m2","m2",0.515673,0,1.);
   RooAddPdf tau("tau","tau",RooArgList(tau1,tau2),RooArgList(m1));
   RooDataSet data("data","data",RooArgSet(TrainOut,TrainTrans,useCMSFrameLPdaughterLP1COpRPRP,Flag),Import(*tr),Cut("(Flag==4)&&TrainOut>0.5"));
   RooFitResult *r = tau.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame = TrainTrans.frame(Title("tau"));
   data.plotOn(frame);
   tau.plotOn(frame);
   frame->Draw();

   //TH1F* h1 = new TH1F("h1","h1",1000,4.9,5.9);
   //nt->Draw("mass>>h1");
   //TF1* fu1 = new TF1("fu1","gaus(0)+[3]*TMath::BreitWigner(x,[4],[5])");
   //fu1->SetParameters(250,5.2,0.04,25,5.5,0.5);
   //h1->Fit("fu1");

}
