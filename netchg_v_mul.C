void netchg_v_mul()
{
   TFile *f = new TFile("13TeV_CR0_RHoff.root");
   TTree *pytree = (TTree*)f->Get("pytree");
   Int_t ntrack, sum=0, no_of[200], netchgsq[200], netchg[200], pid[200];
   Double_t eta[200], pT[200];
   pytree->SetBranchAddress("ntrack",&ntrack);
   pytree->SetBranchAddress("pid",pid);
   pytree->SetBranchAddress("eta",eta);
   pytree->SetBranchAddress("pT",pT);

   TH1* h1 = new TH1D("h1", "netchg vs multiplicity", 200, 0.0, 200.0);
 
   Int_t nentries = (Int_t)pytree->GetEntries();

   for (Int_t b=0; b<200; b++)
    {
    no_of[b]=0; // no_of[q] will store the no. of events that have effective multiplicity q.
    netchg[b]=0; // netchg[q] will store the overall total charge of events that have effective multiplicity q.
    }  

   Int_t newmult=0, newnetchg=0;
   for (Int_t i=0; i<nentries; i++) 
    {
    pytree->GetEntry(i);
        for (Int_t j=0; j<ntrack; j++)
        {
          if((pT[j]>0.05) && (eta[j]<1) && (eta[j]>-1))
          {
           newmult++;
           //cout<<newmult;
           if(pid[j]>0) {newnetchg += 1;}
           else if(pid[j]<0) {newnetchg -= 1;}
          }
        }
    no_of[newmult]+=1;
    netchg[newmult]+=newnetchg;
    newmult=0; newnetchg=0;
    }
   Double_t y;
   for(Int_t x=0; x<200; x++)
    {
    if(no_of[x]!=0)
     {
      y = (double)netchg[x]/no_of[x];
      h1->Fill(x,y);
      cout<<netchg[x]<<" "<<no_of[x]<<" "<<x<<" "<<y<<" "<<endl;
     }
    else continue;
    }

   h1->Draw();
   if (gROOT->IsBatch()) return;
   new TBrowser ();
   pytree->StartViewer();
}