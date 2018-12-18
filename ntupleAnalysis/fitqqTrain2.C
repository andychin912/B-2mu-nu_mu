using namespace RooFit;
using namespace RooStats;
void fitqqTrain2(){
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   TFile* f1 = new TFile("MC9.root");
   TTree* tr = (TTree*)f1->Get("y4s");
   RooRealVar useCMSFrameLPdaughterLP1COpRPRP("useCMSFrameLPdaughterLP1COpRPRP","useCMSFrameLPdaughterLP1COpRPRP",2.2,3.1);
   RooRealVar TrainOut("TrainOut","TrainOut",0.5,0.5,1);
   RooRealVar a("a","a",0.497778,-3,3);
   RooRealVar b("b","b",-1.312,-5,5);
   RooPolynomial qq("qq","qq",TrainOut,RooArgSet(a,b));
   RooRealVar Flag("Flag","Flag",0,0,13);
   RooRealVar m1("m1","m1",0.731725,0,1);
   //RooAddPdf qq("qq","qq",RooArgList(qq1,qq2),RooArgList(m1));
   RooDataSet data("data","data",RooArgSet(useCMSFrameLPdaughterLP1COpRPRP,Flag,TrainOut),Import(*tr),Cut("(Flag==2||Flag==3)&&TrainOut>0.5"));
   RooFitResult *r = qq.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame = TrainOut.frame(Title("qq"));
   data.plotOn(frame);
   qq.plotOn(frame);
   frame->Draw();

   //TH1F* h1 = new TH1F("h1","h1",1000,4.9,5.9);
   //nt->Draw("mass>>h1");
   //TF1* fu1 = new TF1("fu1","gaus(0)+[3]*TMath::BreitWigner(x,[4],[5])");
   //fu1->SetParameters(250,5.2,0.04,25,5.5,0.5);
   //h1->Fit("fu1");

}
