
#include "TH1.h"
#include "TH2.h"
#include "THnSparse.h"
#include "TRandom.h"
#include "TCanvas.h" 
#include "TFile.h"
#include "TStyle.h"
#include "TTree.h"
#include "TSystem.h"
#include "TProfile.h"
#include "math.h"
void netchg_v_mul2d()
{
   
   TFile *f = new TFile("13TeV_CR0_RHoff.root");
   TTree *pytree = (TTree*)f->Get("pytree");

   Int_t ntrack, sum=0, no_of[200], netchgsq[200], netchg[200], pid[200];
   Double_t eta[200], pT[200];
   pytree->SetBranchAddress("ntrack",&ntrack);
   pytree->SetBranchAddress("pid",pid);
   pytree->SetBranchAddress("eta",eta);
   pytree->SetBranchAddress("pT",pT);

   TH2* h2 = new TH2D("h2", "netchg vs multiplicity; Multiplicity; Net-Charge; No.of events", 100, 0.0, 100.0, 30, -15.0, 15.0);
 
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
    h2->Fill(newmult, newnetchg);
    newmult=0; newnetchg=0;
    }
   
auto c2=new TCanvas("Canvas2","Canvas2",1000,1000);
c2->Divide(2,2);
c2->cd(1);h2->Draw("Lego2");
c2->cd(2);h2->Draw("Colz");
c2->cd(3);h2->Draw("Cont1");
c2->cd(4);h2->Draw("Surf3");
   if (gROOT->IsBatch()) return;
   new TBrowser ();
   pytree->StartViewer();
}