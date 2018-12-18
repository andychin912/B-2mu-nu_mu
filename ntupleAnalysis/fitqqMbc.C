using namespace RooFit;
using namespace RooStats;
void fitqqMbc(){
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   TFile* f1 = new TFile("MC9.root");
   TTree* tr = (TTree*)f1->Get("y4s");
   RooRealVar Mbc("Mbc","Mbc",5.1,5.29);
   RooRealVar m0("m0","m0",5.28986,5.1,5.30);
   RooRealVar c("c","c",-28.2556,-50.0,0.0);
   //RooRealVar sigma("sigma","sigma",0.004056,0.,0.015);
   //RooRealVar mean("mean","mean",5.2657,5.1,5.29);
   RooRealVar Flag("Flag","Flag",1,0,13);
   RooRealVar TrainOut("TrainOut","TrainOut",0.5,0,1);
   RooArgusBG qq1("qq1","qq1",Mbc,m0,c);
   //RooGaussian qq2("qq2","qq2",Mbc,mean,sigma);
   //RooRealVar m1("m1","m1",0.8546,0,1);
   //RooRealVar m2("m2","m2",0.059584,0,1);
   RooDataSet data("data","data",RooArgSet(Mbc,Flag,TrainOut),Import(*tr),Cut("(Flag==2||Flag==3)&&TrainOut>0.5"));
   RooFitResult *r = qq1.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame = Mbc.frame(Title("bb"));
   data.plotOn(frame);
   qq1.plotOn(frame);
   frame->Draw();

   //TH1F* h1 = new TH1F("h1","h1",1000,4.9,5.9);
   //nt->Draw("mass>>h1");
   //TF1* fu1 = new TF1("fu1","gaus(0)+[3]*TMath::BreitWigner(x,[4],[5])");
   //fu1->SetParameters(250,5.2,0.04,25,5.5,0.5);
   //h1->Fit("fu1");

}
