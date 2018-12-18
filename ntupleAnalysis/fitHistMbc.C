using namespace RooFit;
using namespace RooStats;
void fitHistMbc()
{
  TFile *MCfile = new TFile("MC9.root");
  TTree *tr = (TTree*)MCfile->Get("y4s");  
  TH1F* hs = new TH1F("hs","hs",100,5.1,5.3);
  //TH1F* hbb = new TH1F("hbb","hbb",100,5.1,5.3);
  TH1F* hqq = new TH1F("hqq","hqq",100,5.1,5.3);
  TH1F* htau = new TH1F("htau","htau",100,5.1,5.3);
  tr->Draw("Mbc>>hs","1.0*(Flag==0&&TrainOut>0.8&&useCMSFrameLPdaughterLP1COpRPRP>2.45&&useCMSFrameLPdaughterLP1COpRPRP<2.85)");
  //tr->Draw("Mbc>>hbb","1.0*(Flag==1&&TrainOut>0.8&&useCMSFrameLPdaughterLP1COpRPRP>2.45&&useCMSFrameLPdaughterLP1COpRPRP<2.85)");
  tr->Draw("Mbc>>hqq","1.0*((Flag==2||Flag==3)&&TrainOut>0.8&&useCMSFrameLPdaughterLP1COpRPRP>2.45&&useCMSFrameLPdaughterLP1COpRPRP<2.85)");
  tr->Draw("Mbc>>htau","1.0*(Flag==4&&TrainOut>0.8&&useCMSFrameLPdaughterLP1COpRPRP>2.45&&useCMSFrameLPdaughterLP1COpRPRP<2.85)");
  RooWorkspace* w = new RooWorkspace("w",1) ;
  w->factory("mbc[5.1,5.3]");
  w->var("mbc")->setBins(100);
  

  RooDataHist* dh_s = new RooDataHist("dh_s","dh_s",RooArgList(*(w->var("mbc"))),hs);
  //RooDataHist* dh_bb =  new RooDataHist("dh_bb","dh_bb",RooArgList(*(w->var("mbc"))),hbb);
  RooDataHist* dh_qq =  new RooDataHist("dh_qq","dh_qq",RooArgList(*(w->var("mbc"))),hqq);
  RooDataHist* dh_tau =  new RooDataHist("dh_tau","dh_tau",RooArgList(*(w->var("mbc"))),htau);

  RooRealVar Bsig("Bsig","Bsig",0.000688,0,50000) ;
  //RooRealVar Bbb("Bbb","Bbb",1,0,50000) ;
  RooRealVar Bqq("Bqq","Bqq",1,0,50000) ;
  RooRealVar Btau("Btau","Btau",1,0,50000) ;
  RooRealVar Asig("Asig","Asig",20,0,1000) ;
  //RooRealVar Abb("Abb","Abb",1,0.3,1000) ;
  RooRealVar Aqq("Aqq","Aqq",1,0.3,10000) ;
  RooRealVar Atau("Atau","Atau",1,0.01,10000) ;

  // ***** Case 0 - 'Rigid templates' *****

  // Construct histogram shapes for signal and background
  RooHistFunc p_h_s("p_h_s","p_h_s",RooArgList(*(w->var("mbc"))),*dh_s) ;
  //RooHistFunc p_h_bb("p_h_bb","p_h_bb",RooArgList(*(w->var("mbc"))),*dh_bb) ;  
  RooHistFunc p_h_qq("p_h_qq","p_h_qq",RooArgList(*(w->var("mbc"))),*dh_qq) ;  
  RooHistFunc p_h_tau("p_h_tau","p_h_tau",RooArgList(*(w->var("mbc"))),*dh_tau) ;  

  // Construct the sum of these
  RooRealSumPdf model0("model0","model0",RooArgList(p_h_s/*,p_h_bb*/,p_h_qq,p_h_tau),RooArgList(Bsig/*,Bbb*/,Bqq,Btau),kTRUE) ;
  RooDataSet* toyData = model0.generate(RooArgList(*(w->var("mbc"))),AllBinned(),NumEvents(20000)) ;

  // ***** Case 1 - 'Beeston Barlow' *****

  // Construct parameterized histogram shapes for signal and background
  RooParamHistFunc p_ph_s("p_ph_s","p_ph_s",*dh_s) ;
  //RooParamHistFunc p_ph_bb("p_ph_bb","p_ph_bb",*dh_bb) ;  
  RooParamHistFunc p_ph_qq("p_ph_qq","p_ph_qq",*dh_qq) ;  
  RooParamHistFunc p_ph_tau("p_ph_tau","p_ph_tau",*dh_tau) ;  

  // Construct the sum of these
  RooRealSumPdf model_tmp("sp_ph","sp_ph",RooArgList(p_ph_s/*,p_ph_bb*/,p_ph_qq,p_ph_tau),RooArgList(Asig/*,Abb*/,Aqq,Atau),kTRUE) ;

  // Construct the subsidiary poisson measurements constraining the histogram parameters
  RooHistConstraint hc_s("hc_sig","hc_sig",p_ph_s) ;
  //RooHistConstraint hc_bb("hc_bb","hc_bb",p_ph_bb) ;
  RooHistConstraint hc_qq("hc_qq","hc_qq",p_ph_qq) ;
  RooHistConstraint hc_tau("hc_tau","hc_tau",p_ph_tau) ;

  // Construct the joint model
  RooProdPdf model1("model1","model1",RooArgSet(hc_s/*,hc_bb*/,hc_qq,hc_tau),Conditional(model_tmp,RooArgList(*(w->var("mbc"))))) ;

  //model0.fitTo(*toyData) ;
  //Double_t asig_val0 = Asig.getVal() ; Double_t asig_err0 = Asig.getError() ;
  RooPlot *frame = w->var("mbc")->frame();
  model1.fitTo(*toyData) ;
  toyData->plotOn(frame);
  model1.plotOn(frame);
  //model_tmp.plotOn(frame);
  Double_t asig_val = Asig.getVal() ; Double_t asig_err = Asig.getError() ;
  //Double_t abb_val = Abb.getVal() ; Double_t abb_err = Abb.getError() ;
  Double_t aqq_val = Aqq.getVal() ; Double_t aqq_err = Aqq.getError() ;
  Double_t atau_val = Atau.getVal() ; Double_t atau_err = Atau.getError() ;
  frame->Draw();
  //cout << "Asig [normal ] = " << asig_val0 << " +/- " << asig_err0 << endl ;
  cout << "Asig [BB     ] = " << asig_val << " +/- " << asig_err << endl ;
  //cout << "Abb [BB     ] = " << abb_val << " +/- " << abb_err << endl ;
  cout << "Aqq [qq     ] = " << aqq_val << " +/- " << aqq_err << endl ;
  cout << "Atau [tau     ] = " << atau_val << " +/- " << atau_err << endl ;
  w->Print();

}
