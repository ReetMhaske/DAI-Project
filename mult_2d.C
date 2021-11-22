void mult_2d()
{
  TFile *f=new TFile("13TeV_CR0_RHoff.root");
  TTree *tree = (TTree*)f->Get("pytree80100;6"); // use the required tree here
   Int_t entries = tree->GetEntries();

 const Int_t maxTrack=10000;
   
 Int_t ntrack = 0;
   Double_t pT[maxTrack];
 Int_t pid[maxTrack];
  Double_t rap[maxTrack];
  Double_t eta[maxTrack];


  tree->SetBranchAddress("ntrack",&ntrack);
  tree->SetBranchAddress("eta",&eta);
  tree->SetBranchAddress("pT",&pT);
  tree->SetBranchAddress("pid",&pid);
 
   gStyle->SetPalette(1);
    gStyle->SetOptStat("emr");
   gStyle->SetOptTitle(2);
 char title[]= "Multiplicity Distribution for bin beyond 100";
max_mult= tree->GetMaximum("ntrack");
  auto TH1D *hmult_acc = new TH1D("hmul_acc",title,100,0,100);
 TAxis *X1=hmult_acc->GetXaxis();
   X1->SetTitle("Multiplicity w.r.t |eta|>1.5");  X1->SetTitleOffset(1);

 TAxis *Y1=hmult_acc->GetYaxis();
   Y1->SetTitle("Number of events");
  Y1->SetTitleOffset(1);


 auto TH1D *hmult_notacc = new TH1D("hmul_notacc",title,100,0,100);
  TAxis *X2=hmult_notacc->GetXaxis();
 X2->SetTitle("Multiplicity w.r.t paticles with |eta|<1 and pT >0.05");
X2->SetTitleOffset(1);  


 TAxis *Y2=hmult_notacc->GetYaxis();
   Y2->SetTitle("Number of events");
  Y2->SetTitleOffset(1);
  
  
auto TH2D *mult_2=new TH2D("mult_2",title,
                         100,0,100,
                         100,0,100); 

TAxis *X=mult_2->GetXaxis();
 X->SetTitle("Multiplicity w.r.t particles with |eta|> 1.5");
X->SetTitleOffset(1.4);


 TAxis *Y=mult_2->GetYaxis();
   Y->SetTitle("Multiplicity w.r.t particles with |eta|<1 and pT>0.05");
  Y->SetTitleOffset(1.4);
   
TAxis *Z=mult_2->GetZaxis();
   Z->SetTitle("Number of Events");
  Z->SetTitleOffset(1.4);
 
 for(Int_t ii=0; ii<entries; ii++)  {  //  A Collison Event loop starts here
    tree->GetEntry(ii);

      Int_t ntrks = ntrack;
      Int_t new_mult=0,analysis=0;
      for(Int_t i=0;i<ntrks;i++){  
       	if(abs(eta[i])<1 && pT[i]>0.05){analysis++;} 
       	if(abs(eta[i])>1.5){new_mult++;}
                                  }
 hmult_acc->Fill(new_mult);
 hmult_notacc->Fill(analysis);
  mult_2->Fill(new_mult,analysis); 
if (ii%500000==0){cout<< ii<<"\n";}
 }

TF1*poisson=new TF1("Poisson","[0]*(TMath::Poisson(x,[1]))",0,100);
poisson->SetParNames("normalization constnt","lamda");
Double_t mean=hmult_acc->GetMean();
poisson->SetParameters(entries,hmult_acc->GetMean());
 auto c1=new TCanvas("Canvas1","Canvas1",1000,1000);
hmult_acc->Fit("Poisson") ;
gStyle->SetOptFit(0000);
hmult_acc->Draw("BOX ");
//hmult_acc->Draw("SAME C ");

auto c2= new TCanvas("canvas2","canvas2",1000,1000);
poisson->SetParameters(entries,hmult_acc->GetMean());
hmult_notacc->Fit("Poisson");
gStyle->SetOptFit(0000);
hmult_notacc->Draw(" BOX ");
//hmult_notacc->Draw("SAME C");   
auto c3=new TCanvas("Canvas3","Canvas3",1000,1000);
mult_2->Draw("Lego2");
auto c4=new TCanvas("Canvas4","Canvas4",1000,1000);
mult_2->Draw("ContZ");


 
cout << "Moments of Distribution:\n"
         << " - Mean     = " << hmult_acc->GetMean() << " +- "
                             << hmult_acc->GetMeanError() << "\n"
         << " - Std Dev  = " << hmult_acc->GetStdDev() << " +- "
                             <<hmult_acc->GetStdDevError() << "\n"
         << " - Skewness = " << hmult_acc->GetSkewness() << "\n"
         << " - Kurtosis = " << hmult_acc->GetKurtosis() << "\n";




}