void net_mea(){
   
   TFile *f = new TFile("13TeV_CR0_RHoff.root");
   TTree *tree = (TTree*)f->Get("pytree");

   Int_t ntrack;
   Int_t pid[200];
   Double_t no_of[200],netchg[200],netchgmean[200],pT[200],eta[200];
   pytree->SetBranchAddress("ntrack",&ntrack);
   pytree->SetBranchAddress("pid",pid);
   pytree->SetBranchAddress("eta",eta);
   pytree->SetBranchAddress("pT",pT);

   TH1* h1 = new TH1D("h1", "net charge_mean vs multiplicity", 100, 0.0, 100.0);
 
   Int_t nentries = (Int_t)pytree->GetEntries();
   for (Int_t b=0; b<200; b++)
    {
    no_of[b]=0;
    netchg[b]=0.0;
    netchgmean[b]=0.0;
    }
   
   Int_t a,newmult=0,newnetchg=0;
   for (Int_t i=0; i<nentries; i++) 
    {
    newmult=0, newnetchg=0;
    pytree->GetEntry(i);
     for(Int_t j=0; j<ntrack; j++)
      {
      if((pT[j]>0.05) && (abs(eta[j])<1.0))
       {
       newmult+=1;
       if(pid[j]>0) {newnetchg += 1;}
       else if(pid[j]<0) {newnetchg -= 1;}
       }
      }
    a=newmult; // a is kind of useless.
    no_of[a]+=1;
    netchg[a]+=newnetchg;
    }

   for(Int_t k=0; k<100; k++)
    {
    if(no_of[k]!=0)
      {
      netchgmean[k]=netchg[k]/no_of[k]+0.0;
      h1->Fill(k ,netchgmean[k]);
      cout<<netchgmean[k]<<" "<<netchg[k]<<" "<<no_of[k]<<" "<<endl;
      }
    }
   
   h1->Draw();
}