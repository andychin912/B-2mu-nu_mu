using namespace RooFit;
using namespace RooStats;
void fitqqMom(){
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   TFile* f1 = new TFile("MC9.root");
   TTree* tr = (TTree*)f1->Get("y4s");
   RooRealVar useCMSFrameLPdaughterLP1COpRPRP("useCMSFrameLPdaughterLP1COpRPRP","useCMSFrameLPdaughterLP1COpRPRP",2.2,3.1);
   RooRealVar mean1("a","a",2.52060,-100,3.1);
   //RooRealVar mean2("a1","a1",2.445048,2.2,3.1);
   RooRealVar sigma1("b","b",0.599526,0,1);
   //RooRealVar sigma2("b1","b1",0.103440,0,1);
   RooRealVar Flag("Flag","Flag",0,0,13);
   RooRealVar TrainOut("TrainOut","TrainOut",0.5,0,1);
   RooGaussian qq1("qq1","qq1",useCMSFrameLPdaughterLP1COpRPRP,mean1,sigma1);
   //RooGaussian 2("qq2","qq2",useCMSFrameLPdaughterLP1COpRPRP,mean2,sigma2);
   RooRealVar m1("m1","m1",0.599526,0,1);
   //RooAddPdf ("qq","qq",RooArgList(qq1,qq2),RooArgList(m1));
   RooDataSet data("data","data",RooArgSet(useCMSFrameLPdaughterLP1COpRPRP,Flag,TrainOut),Import(*tr),Cut("(Flag==2||Flag==3)&&TrainOut>0.5"));
   RooFitResult *r = qq1.fitTo(data,Minos(true),PrintEvalErrors(10));
   RooPlot* frame = useCMSFrameLPdaughterLP1COpRPRP.frame(Title(""));
   data.plotOn(frame);
   qq1.plotOn(frame);
   frame->Draw();

   //TH1F* h1 = new TH1F("h1","h1",1000,4.9,5.9);
   //nt->Draw("mass>>h1");
   //TF1* fu1 = new TF1("fu1","gaus(0)+[3]*TMath::BreitWigner(x,[4],[5])");
   //fu1->SetParameters(250,5.2,0.04,25,5.5,0.5);
   //h1->Fit("fu1");

}
