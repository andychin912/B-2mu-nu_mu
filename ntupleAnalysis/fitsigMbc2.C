using namespace RooFit;
using namespace RooStats;
void fitsigMbc2(){
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   TFile* f1 = new TFile("MC9.root");
   TTree* tr = (TTree*)f1->Get("y4s");
   RooRealVar Mbc("Mbc","Mbc",5.1,5.29);
   RooRealVar m0("m0","m0",5.27836,5.2,5.29);
   RooRealVar sigma("sigma","sigma",0.00703166,0.,0.015);
   RooRealVar cut("cut","cut",0.121369,-1.1,1.1);
   RooRealVar power("power","power",9.94254,2,500);
   RooRealVar mean("mean","mean",5.28852,5.1,5.29);
   RooRealVar sigma2("sigma2","sigma2",0.005,0,0.03);
   RooRealVar sigma3("sigma3","sigma3",0.000596297,0,0.05);
   RooRealVar Flag("Flag","Flag",0,0,13);
   RooRealVar TrainOut("TrainOut","TrainOut",0.5,0.,1.);
   RooCBShape sig1("sig1","sig1",Mbc,m0,sigma,cut,power);
   RooPoisson sig2("sig2","sig2",Mbc,mean);
   RooRealVar m1("m1","m1",0.881041,0.,1.);
   RooAddPdf sig("sig","sig",RooArgList(sig1,sig2),RooArgList(m1));
   RooDataSet data("data","data",RooArgSet(Mbc,Flag,TrainOut),Import(*tr),Cut("Flag==0&&TrainOut>0.5"));
   RooFitResult *r = sig.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame = Mbc.frame(Title("sig"));
   data.plotOn(frame);
   sig.plotOn(frame);
   frame->Draw();

   //TH1F* h1 = new TH1F("h1","h1",1000,4.9,5.9);
   //nt->Draw("mass>>h1");
   //TF1* fu1 = new TF1("fu1","gaus(0)+[3]*TMath::BreitWigner(x,[4],[5])");
   //fu1->SetParameters(250,5.2,0.04,25,5.5,0.5);
   //h1->Fit("fu1");

}
