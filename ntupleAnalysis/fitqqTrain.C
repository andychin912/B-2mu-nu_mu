using namespace RooFit;
using namespace RooStats;
void fitqqTrain(){
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   TFile* f1 = new TFile("MC9.root");
   TTree* tr = (TTree*)f1->Get("y4s");
   RooRealVar useCMSFrameLPdaughterLP1COpRPRP("useCMSFrameLPdaughterLP1COpRPRP","useCMSFrameLPdaughterLP1COpRPRP",2.2,3.1);
   RooRealVar mean1("a","a",-0.306833,-5,100);
   RooRealVar mean2("a1","a1",1.,-5,100);
   RooRealVar sigma1("b","b",1.86046,0,5);
   RooRealVar sigma2("b1","b1",1.44270,0,3);
   RooRealVar sigma3("b2","b2",1.04693,0,3);
   RooRealVar sigma4("b3","b3",1.53588,-1,100);
   RooRealVar cut("cut","cut",1.53588,-10,5);
   RooRealVar power("p","p",1.53588,0,10);
   RooRealVar Flag("Flag","Flag",0,0,13);
   RooRealVar TrainOut("TrainOut","TrainOut",0.5,0.5,1.);
   RooRealVar TrainTrans("TrainTrans","TrainTrans",-7,-7,12);
   RooBifurGauss qq1("qq1","qq1",TrainTrans,mean1,sigma1,sigma2);
   RooBreitWigner qq2("qq2","qq2",TrainTrans,mean1,sigma3);
   //RooGaussian qq2("qq2","qq2",TrainTrans,mean2,sigma2);
   RooRealVar m1("m1","m1",0.904033,0,1.);
   //RooRealVar m2("m2","m2",0.632397,0.5,1);
   RooAddPdf qq("qq","qq",RooArgList(qq1,qq2),RooArgList(m1));
   RooDataSet data("data","data",RooArgSet(TrainOut,TrainTrans,useCMSFrameLPdaughterLP1COpRPRP,Flag),Import(*tr),Cut("(Flag==2||Flag==3)&&TrainOut>0.5"));
   RooFitResult *r = qq.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame = TrainTrans.frame(Title("qq"));
   data.plotOn(frame);
   qq.plotOn(frame);
   frame->Draw();

   //TH1F* h1 = new TH1F("h1","h1",1000,4.9,5.9);
   //nt->Draw("mass>>h1");
   //TF1* fu1 = new TF1("fu1","gaus(0)+[3]*TMath::BreitWigner(x,[4],[5])");
   //fu1->SetParameters(250,5.2,0.04,25,5.5,0.5);
   //h1->Fit("fu1");

}
