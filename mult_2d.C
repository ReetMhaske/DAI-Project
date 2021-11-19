void mult_2d()
{
  TFile *f=new TFile("13TeV_CR0_RHoff.root");
  TTree *tree = (TTree*)f->Get("pytree"); // use the required tree here
   Int_t entries = tree->GetEntries();

 const Int_t maxTrack=10000;
   
 Int_t ntrack = 0;
   Double_t pT[maxTrack];
  Double_t eta[maxTrack];
  Double_t rap[maxTrack];
  Double_t phi[maxTrack];


  tree->SetBranchAddress("ntrack",&ntrack);
  tree->SetBranchAddress("phi",&phi);
  tree->SetBranchAddress("pT",&pT);
  tree->SetBranchAddress("eta",&eta);
 
   gStyle->SetPalette(52);
    gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
  TH1D *hmult_acc = new TH1D("hmul_acc","No. of events vs accepted multiplicity;Multiplicity in accepted region; N_{events}",50,0,50);
  TH1D *hmult_notacc = new TH1D("hmul_notacc","No. of events vs non-accepted multiplicity;Multiplicity in accepted region; N_{events}",50,0,50);
  TH1D *heta = new TH1D("heta","Rapidity",100,-10.0,10.0);
  TH2D *mult_2=new TH2D("mult_2","2D Histogram; Accepted Multiplicity; Non-Accepted Multiplicity; No. of Events",
                         50,0,50,
                         50,0,50); 

  for(Int_t ii=0; ii<entries; ii++)  {  //  A Collison Event loop starts here
    tree->GetEntry(ii);

      Int_t ntrks = ntrack;


     
   Int_t new_mult=0;
      for(int i=0; i<ntrks; i++) { //track loop is here loop on no. of particels released in the particular event

     if( (eta[i]>1.5) || (eta[i]<-1.5)  ){
       new_mult++;};
    // Double_t eta1 = eta[i];
    // heta->Fill(eta1);


   }
 hmult_acc->Fill(new_mult);
 hmult_notacc->Fill(ntrks-new_mult);
 mult_2->Fill(new_mult,ntrks-new_mult); 
if (ii%500000==0){cout<< ii<<"\n";}
 }
 auto c1=new TCanvas("Canvas1","Canvas1",1000,1000);
 c1->Divide(1,2);
 
  //heta->Draw();
c1->cd(1);   hmult_acc->Draw();
c1->cd(2); hmult_notacc->Draw();
    
auto c2=new TCanvas("Canvas2","Canvas2",1000,1000);
c2->Divide(2,2);
c2->cd(1);mult_2->Draw("Lego2");
c2->cd(2);mult_2->Draw("Colz");
c2->cd(3);mult_2->Draw("Cont1");
c2->cd(4);mult_2->Draw("Surf3");
cout << "Moments of Distribution:\n"
         << " - Mean     = " << hmult_acc->GetMean() << " +- "
                             << hmult_acc->GetMeanError() << "\n"
         << " - Std Dev  = " << hmult_acc->GetStdDev() << " +- "
                             <<hmult_acc->GetStdDevError() << "\n"
         << " - Skewness = " << hmult_acc->GetSkewness() << "\n"
         << " - Kurtosis = " << hmult_acc->GetKurtosis() << "\n";
}