void kurtosis(){
   
   TFile *f = new TFile("13TeV_CR0_RHoff.root");
   TTree *pytree = (TTree*)f->Get("pytree");
   
   Int_t ntrack;
   const Int_t n=7;
   Int_t pid[200];
   Double_t no_of[n],netchg[n],netchgsq[n],netchgmea[n],netchgcub[n],netchgfour[n],kurt[n],netchgvar[n],ntracktot[n],pT[200],eta[200],y[n];
   pytree->SetBranchAddress("ntrack",&ntrack);
   pytree->SetBranchAddress("pid",pid);
   pytree->SetBranchAddress("eta",eta);
   pytree->SetBranchAddress("pT",pT);
 
   Int_t nentries = (Int_t)pytree->GetEntries();
   for (Int_t b=0; b<n; b++)
    {
    y[b]=0.0;
    no_of[b]=0;
    netchg[b]=0.0;
    ntracktot[b]=0.0;
    netchgsq[b]=0.0;
    netchgvar[b]=0.0;
    netchgcub[b]=0.0;
    netchgfour[b]=0.0;
    kurt[b]=0.0;
    }
   
   Int_t a,newmult=0,newnetchg=0;
   for (Int_t i=0; i<nentries; i++) 
    {
    newnetchg=0;
    pytree->GetEntry(i);
     for(Int_t j=0; j<ntrack; j++)
      {
      if((pT[j]>0.5) && (abs(eta[j])<1.0))
       {
       if(pid[j]>0) {newnetchg += 1;}
       else {newnetchg -= 1;}
       }
      }
    if(ntrack<20*(n-1))
      {
      a=ntrack/20;
      no_of[a]+=1;
      ntracktot[a]+=ntrack;
      netchg[a]+=newnetchg;
      netchgsq[a]+=pow(newnetchg,2);
      netchgcub[a]+=pow(newnetchg,3);
      netchgfour[a]+=pow(newnetchg,4);
      }
    else
      {
      a=n-1;
      no_of[a]+=1;
      ntracktot[a]+=ntrack;
      netchg[a]+=newnetchg;
      netchgsq[a]+=pow(newnetchg,2);
      netchgcub[a]+=pow(newnetchg,3); 
      netchgfour[a]+=pow(newnetchg,4);
      }
    }
   
      
   for(Int_t k=0; k<n; k++)
    {
    if(no_of[k]>1)
      {
      y[k]=ntracktot[k]/no_of[k]; 
      netchgmea[k]=(double)(netchg[k]/no_of[k]);
      netchgvar[k]=(double)((netchgsq[k])/(no_of[k]-1)-(pow(netchg[k],2))/(no_of[k]*(no_of[k]-1))); 
      kurt[k]=(double)((netchgfour[k]/no_of[k])-(3*pow(netchgmea[k],4))-(4*netchgmea[k]*netchgcub[k]/no_of[k])+(6*pow(netchgmea[k],2)*netchgsq[k]/no_of[k]));
      kurt[k]=(double)(kurt[k]/pow(netchgvar[k],2));
      cout<<"("<<y[k]<<","<<kurt[k]<<")"<<endl;
      }
    }
   
  
   TGraph *gr3 = new TGraph(n,y,kurt); 
   TCanvas *c1 = new TCanvas("c1","Graph Draw Options",
                             200,10,600,400);
   c1->cd(4);
   gr3->SetTitle("Kurtosis vs Mean Multiplicity");
   gr3->GetXaxis()->SetTitle("Mean Multiplicity");
   gr3->GetYaxis()->SetTitle("Kurtosis");
   gr3->SetLineColor(0);
   gr3->Draw("ASL");

   // get the points in the graph and put them into an array
   Double_t *nx = gr3->GetX();
   Double_t *ny = gr3->GetY();

   // create markers of different colors
   for (Int_t j=0; j<n; j++) {
      TMarker *m = new TMarker(y[j], kurt[j], 22);
      m->SetMarkerSize(2);
      m->SetMarkerColor(2);
      m->Draw();
   }
}
