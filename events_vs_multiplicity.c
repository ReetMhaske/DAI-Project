void multiplicity()
{
     TFile *f = new TFile("13TeV_CR0_RHoff.root");
     TTree *pytree = (TTree*)f-> Get("pytree");
     Int_t ntrack, temp=0, no_of[200];
     Double_t  eta[200];
     pytree-> SetBranchAddress("ntrack",&ntrack);
     pytree-> SetBranchAddress("eta",eta);
     TH1*h1m = new TH1F("h1m","No. of Events v/s Multiplicity",200,0.0,200);
      Int_t nentries = (Int_t)pytree-> GetEntries();
      for (Int_t b=0;b<200;b++)
           { no_of[b] = 0;
             eta[b] = 0;
            }
      for(Int_t i=0; i<nentries; i++)
           { pytree->GetEntry(i);
          
             for(Int_t p=0; p<ntrack; p++)
                   { 
                   if(abs(eta[p])>1.5)
                     {temp+=1;}
                   }
           no_of[temp]+=1;
           temp=0;
           }
      for(Int_t k=0; k<200; k++)
            { if (no_of[k]!=0)
                  { h1m-> Fill(k+1 , no_of[k]);
                  }
            }
       h1m-> Draw();
          if(gROOT-> IsBatch()) return;
          new TBrowser();
          pytree->Startviewer();
}
       
      