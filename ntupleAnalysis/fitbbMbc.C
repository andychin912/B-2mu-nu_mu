using namespace RooFit;
using namespace RooStats;
void fitbbMbc(){
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   TFile* f1 = new TFile("MC9.root");
   TTree* tr = (TTree*)f1->Get("y4s");
   RooRealVar Mbc("Mbc","Mbc",5.1,5.29);
   RooRealVar m0("m0","m0",5.28982,5.1,5.29);
   RooRealVar m("m","m",5.28982,5.1,5.29);
   RooRealVar c("c","c",-23.4797,-50.0,0.0);
   RooRealVar c2("c2","c2",-103.914,-120.0,0.0);
   //RooRealVar sigma("sigma","sigma",0.004056,0.,0.015);
   //RooRealVar mean("mean","mean",5.2657,5.1,5.29);
   RooRealVar Flag("Flag","Flag",1,0,13);
   RooRealVar TrainOut("TrainOut","TrainOut",0.5,0,1);
   RooArgusBG bb1("bb1","bb1",Mbc,m0,c);
   RooArgusBG bb2("bb2","bb2",Mbc,m,c2);
   RooRealVar m1("m1","m1",0.820154,0,1);
   //RooRealVar m2("m2","m2",0.059584,0,1);
   RooAddPdf bb("bb","bb",RooArgList(bb1,bb2),RooArgList(m1));
   RooDataSet data("data","data",RooArgSet(Mbc,Flag,TrainOut),Import(*tr),Cut("Flag==1&&TrainOut>0.5"));
   RooFitResult *r = bb.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame = Mbc.frame(Title("bb"));
   data.plotOn(frame);
   bb.plotOn(frame);
   frame->Draw();

   //TH1F* h1 = new TH1F("h1","h1",1000,4.9,5.9);
   //nt->Draw("mass>>h1");
   //TF1* fu1 = new TF1("fu1","gaus(0)+[3]*TMath::BreitWigner(x,[4],[5])");
   //fu1->SetParameters(250,5.2,0.04,25,5.5,0.5);
   //h1->Fit("fu1");

}
