using namespace RooFit;
using namespace RooStats;
void fitsigMom(){
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   TFile* f1 = new TFile("MC9.root");
   TTree* tr = (TTree*)f1->Get("y4s");
   RooRealVar useCMSFrameLPdaughterLP1COpRPRP("useCMSFrameLPdaughterLP1COpRPRP","useCMSFrameLPdaughterLP1COpRPRP",2.2,3.1);
   RooRealVar mean1("mean1","mean1",2.50199,2.35,2.65);
   RooRealVar means1("means1","means1",2.48235,2.1,2.65);
   RooRealVar mean2("mean2","mean2",2.77907,2.65,2.85);
   RooRealVar means2("means2","means2",2.62973,2.45,2.95);
   RooRealVar sigmaS1("sigmaS1","sigmaS1",0.0233402,0,0.1);
   RooRealVar sigmaS2("sigmaS2","sigmaS2",0.0281937,0,0.1);
   RooRealVar sigmaL1("sigmaL1","sigmaL1",0.0672146,0,1);
   RooRealVar sigmaL2("sigmaL2","sigmaL2",0.0808619,0,1);
   RooRealVar sigmas1("sigmas1","sigmas1",0.155070,0,1);
   RooRealVar sigmas2("sigmas2","sigmas2",0.0699447,0,1);
   RooRealVar Flag("Flag","Flag",0,0,13);
   RooRealVar TrainOut("TrainOut","TrainOut",0.5,0.5,1.);
   RooBifurGauss sig1("sig1","sig1",useCMSFrameLPdaughterLP1COpRPRP,mean1,sigmaS1,sigmaL1);
   RooBifurGauss sig2("sig2","sig2",useCMSFrameLPdaughterLP1COpRPRP,mean2,sigmaL2,sigmaS2);
   RooGaussian sig3("sig3","sig3",useCMSFrameLPdaughterLP1COpRPRP,means1,sigmas1);
   RooGaussian sig4("sig4","sig4",useCMSFrameLPdaughterLP1COpRPRP,means2,sigmas2);
   RooRealVar m1("m1","m1",0.294327,0,1);
   RooRealVar m2("m2","m2",0.372657,0,1);
   RooRealVar m3("m3","m3",0.0191646,0,1);
   RooAddPdf sig("sig","sig",RooArgList(sig1,sig2,sig3,sig4),RooArgList(m1,m2,m3));
   RooDataSet data("data","data",RooArgSet(useCMSFrameLPdaughterLP1COpRPRP,Flag,TrainOut),Import(*tr),Cut("Flag==0&&TrainOut>0.5"));
   RooFitResult *r = sig.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame = useCMSFrameLPdaughterLP1COpRPRP.frame(Title("sig"));
   data.plotOn(frame);
   sig.plotOn(frame);
   frame->Draw();

   //TH1F* h1 = new TH1F("h1","h1",1000,4.9,5.9);
   //nt->Draw("mass>>h1");
   //TF1* fu1 = new TF1("fu1","gaus(0)+[3]*TMath::BreitWigner(x,[4],[5])");
   //fu1->SetParameters(250,5.2,0.04,25,5.5,0.5);
   //h1->Fit("fu1");

}
