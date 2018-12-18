using namespace RooFit;
using namespace RooStats;
void fitHistTrain()
{
  TFile *MCfile = new TFile("MC9.root");
  TTree *tr = (TTree*)MCfile->Get("y4s");  
  TH1F* hs = new TH1F("hs","hs",20,0.5,1);
  TH1F* hbb = new TH1F("hbb","hbb",20,0.5,1);
  TH1F* hqq = new TH1F("hqq","hqq",20,0.5,1);
  TH1F* htau = new TH1F("htau","htau",20,0.5,1);
  tr->Draw("TrainOut>>hs","1.0*(Flag==0&&useCMSFrameLPdaughterLP1COpRPRP>2.45&&useCMSFrameLPdaughterLP1COpRPRP<2.85)*344./500000");
  tr->Draw("TrainOut>>hbb","1.0*(Flag==1&&useCMSFrameLPdaughterLP1COpRPRP>2.45&&useCMSFrameLPdaughterLP1COpRPRP<2.85)");
  tr->Draw("TrainOut>>hqq","1.0*((Flag==2||Flag==3)&&useCMSFrameLPdaughterLP1COpRPRP>2.45&&useCMSFrameLPdaughterLP1COpRPRP<2.85)");
  tr->Draw("TrainOut>>htau","1.0*(Flag==4&&useCMSFrameLPdaughterLP1COpRPRP>2.45&&useCMSFrameLPdaughterLP1COpRPRP<2.85)");
  RooWorkspace* w = new RooWorkspace("w",1) ;
  w->factory("train[0.5,1.]");
  w->var("train")->setBins(20);
  

  RooDataHist* dh_s = new RooDataHist("dh_s","dh_s",RooArgList(*(w->var("train"))),hs);
  RooDataHist* dh_bb =  new RooDataHist("dh_bb","dh_bb",RooArgList(*(w->var("train"))),hbb);
  RooDataHist* dh_qq =  new RooDataHist("dh_qq","dh_qq",RooArgList(*(w->var("train"))),hqq);
  RooDataHist* dh_tau =  new RooDataHist("dh_tau","dh_tau",RooArgList(*(w->var("train"))),htau);

  RooRealVar Bsig("Bsig","Bsig",1,0,50000) ;
  RooRealVar Bbb("Bbb","Bbb",1,0,50000) ;
  RooRealVar Bqq("Bqq","Bqq",1,0,50000) ;
  RooRealVar Btau("Btau","Btau",1,0,50000) ;
  RooRealVar Asig("Asig","Asig",20,0,100) ;
  RooRealVar Abb("Abb","Abb",0.5,0.3,100) ;
  RooRealVar Aqq("Aqq","Aqq",0.5,0.3,100) ;
  RooRealVar Atau("Atau","Atau",0.5,0.01,100) ;

  // ***** Case 0 - 'Rigid templates' *****

  // Construct histogram shapes for signal and background
  RooHistFunc p_h_s("p_h_s","p_h_s",RooArgList(*(w->var("train"))),*dh_s) ;
  RooHistFunc p_h_bb("p_h_bb","p_h_bb",RooArgList(*(w->var("train"))),*dh_bb) ;  
  RooHistFunc p_h_qq("p_h_qq","p_h_qq",RooArgList(*(w->var("train"))),*dh_qq) ;  
  RooHistFunc p_h_tau("p_h_tau","p_h_tau",RooArgList(*(w->var("train"))),*dh_tau) ;  

  // Construct the sum of these
  RooRealSumPdf model0("model0","model0",RooArgList(p_h_s,p_h_bb,p_h_qq,p_h_tau),RooArgList(Bsig,Bbb,Bqq,Btau),kTRUE) ;
  RooDataSet* toyData = model0.generate(RooArgList(*(w->var("train"))),AllBinned(),NumEvents(30683)) ;

  // ***** Case 1 - 'Beeston Barlow' *****

  // Construct parameterized histogram shapes for signal and background
  RooParamHistFunc p_ph_s("p_ph_s","p_ph_s",*dh_s) ;
  RooParamHistFunc p_ph_bb("p_ph_bb","p_ph_bb",*dh_bb) ;  
  RooParamHistFunc p_ph_qq("p_ph_qq","p_ph_qq",*dh_qq) ;  
  RooParamHistFunc p_ph_tau("p_ph_tau","p_ph_tau",*dh_tau) ;  

  // Construct the sum of these
  RooRealSumPdf model_tmp("sp_ph","sp_ph",RooArgList(p_ph_s,p_ph_bb,p_ph_qq,p_ph_tau),RooArgList(Bsig,Bbb,Bqq,Btau),kTRUE) ;

  // Construct the subsidiary poisson measurements constraining the histogram parameters
  RooHistConstraint hc_s("hc_sig","hc_sig",p_ph_s) ;
  RooHistConstraint hc_bb("hc_bb","hc_bb",p_ph_bb) ;
  RooHistConstraint hc_qq("hc_qq","hc_qq",p_ph_qq) ;
  RooHistConstraint hc_tau("hc_tau","hc_tau",p_ph_tau) ;

  // Construct the joint model
  RooProdPdf model1("model1","model1",RooArgSet(hc_s,hc_bb,hc_qq,hc_tau),Conditional(model_tmp,RooArgList(*(w->var("train"))))) ;

  //model0.fitTo(*toyData) ;
  //Double_t asig_val0 = Asig.getVal() ; Double_t asig_err0 = Asig.getError() ;
  RooPlot *frame = w->var("train")->frame();
  //model1.fitTo(*toyData) ;
  toyData->plotOn(frame);
  //model1.plotOn(frame);
  model0.plotOn(frame);
  Double_t asig_val = Bsig.getVal() ; Double_t asig_err = Bsig.getError() ;
  Double_t abb_val = Bbb.getVal() ; Double_t abb_err = Bbb.getError() ;
  Double_t aqq_val = Bqq.getVal() ; Double_t aqq_err = Bqq.getError() ;
  Double_t atau_val = Btau.getVal() ; Double_t atau_err = Btau.getError() ;
  frame->Draw();
  //cout << "Asig [normal ] = " << asig_val0 << " +/- " << asig_err0 << endl ;
  cout << "Asig [BB     ] = " << asig_val << " +/- " << asig_err << endl ;
  cout << "Abb [BB     ] = " << abb_val << " +/- " << abb_err << endl ;
  cout << "Aqq [qq     ] = " << aqq_val << " +/- " << aqq_err << endl ;
  cout << "Atau [tau     ] = " << atau_val << " +/- " << atau_err << endl ;
  w->Print();

}
