void tagsideB() {


	TFile *myfile = new TFile("~/B+2mu+nu_mu/20180718_B+2mu+nu_mu_1.root");
        TTree *data = (TTree*) myfile->Get("Btag");

	TH2F *m1 = new TH2F("m1","m1",400,4.,5.3,400,-4.9,4.9);

	data->Draw("B_deltae:B_mbc>>m1");//put x into m1

        TCanvas *zone = new TCanvas("zone","zone",1);//graphic space
        zone->SetFillColor(0);
        zone->SetFrameFillColor(0);
        zone->SetFrameLineWidth(2);
        zone->SetFillStyle(4000);
        zone->SetFrameFillStyle(4000);


	m1->Draw("COLZ");



	m1->GetXaxis()->SetTitle("Mbc [GeV]");
	m1->GetYaxis()->SetTitle("deltaE [GeV]");
	m1->GetYaxis()->SetTitleOffset(1.4);
	m1->GetXaxis()->SetTitleSize(0.045);

	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(kFALSE);


	zone->SaveAs("./y.eps");

}
