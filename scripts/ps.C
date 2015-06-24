#include "TGenPhaseSpace.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TString.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TRandom3.h"
#include "TLorentzVector.h"

#include <iostream>
using namespace std;

void
ps(TString outfilename, int seed, unsigned int N=10000){

  gStyle->SetOptStat(0);

  gRandom->SetSeed(seed);
  
  // initial state
  double mXib = 5794.9; // Xi_b
  double mXib0 = 5793.1;
  double mLb = 5619.5;

  // Xi_b decay products
  const double mJPsi = 3096.916;  // J/Psi
  const double mXi0 = 1314.86;   // Xi0
  const double mXi = 1321.71;    // Xi-
  const double mXi1530 =  1531.8;
  const double mXi1690 = 1690;
  const double wXi1690 = 20;
  const double mXi1820 = 1823;
  const double wXi1820 = 24;
  Double_t masses[2]={mJPsi,mXi1690};
  Double_t wXi=wXi1690;

  TString label1("MC #Xi_{b}^{-}#rightarrow J/#psi #Xi^{-}(1690)");
  TString label2("#Xi^{-}(1690) #rightarrow #Lambda K");
  TString label3("#Lambda #rightarrow p (#pi)_{missing}");

  // Xi decay products
  const double mL = 1115.683;//1519.5;
  const double mpi0 = 134.9766;
   const double mP=938.272;
  const double mK=493.67;
  const double mpi=139.57;

  Double_t massesXi[2]={mL,mK}; // Xi(1690,1820) 
  //Double_t massesXi[2]={mL,mpi0};  
  //Double_t massesXi[2]={mL,mpi};  
 
  Double_t massesL[2]={mP,mpi};

  // setup first decay
  TLorentzVector p1(0,0,0,mXib);
  TGenPhaseSpace event;
  

  TGenPhaseSpace xi;
  TGenPhaseSpace Lambda;
   
  TH1D* hm=new TH1D("hm","(J/#psi P K) Mass",200,5300,5800);
  hm->GetXaxis()->SetTitle("m(J/#psi p K)[MeV]");
  TH1D* hmX=new TH1D("hmX","(J/#psi P) Mass",200,4000,6000);
  hmX->GetXaxis()->SetTitle("m(J/#psi p)[MeV]");
  TH1D* hmKp=new TH1D("hmKp","(K P) Mass",200,mK+mP,2000);
  hmKp->GetXaxis()->SetTitle("m(p K)[MeV]");
  TH1D* hmJK=new TH1D("hmJK","(J/#psi K) Mass",200,mK+mJPsi,4500);
  hmJK->GetXaxis()->SetTitle("m(J/#psi K)[MeV]");
  TH1D* hmXi = new TH1D("hmXi","Xi Mass",200,1300,2000);

  TFile* outfile=TFile::Open(outfilename,"RECREATE");
  TTree* outtree=new TTree("ps","PS");
  double m, mX, mKP, w;
  outtree->Branch("mJPK",&m);
  outtree->Branch("mJP",&mX);
  outtree->Branch("mKP",&mKP);
  outtree->Branch("weight",&w);

  // main loop
  for(unsigned int i=0; i<N; ++i){
    // give the Xi a width:
    double d=gRandom->Gaus(0,wXi/2);
    masses[1]+=d;
    if(!event.SetDecay(p1,2,masses))return;
    
    double w1=event.Generate();
    hmXi->Fill(masses[1],w1);
   
    masses[1]-=d; 
    TLorentzVector* pJPsi=event.GetDecay(0);
    TLorentzVector* pXi=event.GetDecay(1);
    
    //pXi->Print();
    
      
    if(!xi.SetDecay(*pXi,2,massesXi)){cout<< "Xi decay kinematically not possible" << endl; return;}
    // loop until we generate a fitting decay
    TLorentzVector* pL;
    TLorentzVector* ppi0;

    while(true){
      double w2=xi.Generate();
      // sample and reject
      if(gRandom->Uniform() < w2){
	pL=xi.GetDecay(0);
	ppi0=xi.GetDecay(1);
	break;
      }
    }

    // make Lambda decay
    if(!Lambda.SetDecay(*pL,2,massesL)){cout<< "Lambda decay kinematically not possible" << endl;return;}
    TLorentzVector* pP;
    TLorentzVector* ppi;
    
    while(true){
      double w3=Lambda.Generate();
      if(gRandom->Uniform() < w3){
	pP=Lambda.GetDecay(0);
	ppi=Lambda.GetDecay(1);
	break;
      }
    }
    

    //cout << (*pL+*ppi0).M() << endl;
    TLorentzVector pK;
    pK.SetVectM(ppi0->Vect(),mK); //(ppi0->Vect(),mK);

    TLorentzVector ppartial=*pJPsi+*pP+ pK;
    hm->Fill(ppartial.M(),w1);

    m=ppartial.M();
    w=w1;

    if(fabs(ppartial.M()-mLb)<15){
      TLorentzVector JpsiP=*pJPsi + *pP;
      hmX->Fill(JpsiP.M(),w1);
      mX=JpsiP.M();
      TLorentzVector JpsiK=*pJPsi + pK;
      hmJK->Fill(JpsiK.M(),w1);

      TLorentzVector KP=*pP + pK;
      hmKp->Fill(KP.M(),w1);
      mKP=KP.M();

    }
    
    outtree->Fill();
  }
  
  //TCanvas* con=new TCanvas("con","control");
  //hmXi->Draw();

  //TCanvas* c=new TCanvas("c","c",10,10,1000,1000);
  //c->Divide(2,2);
  //c->cd(1);
  //hm->Draw();
  
  
  //c->cd(2);
  //hmX->Draw();
  //c->cd(3);
  //hmKp->Draw();
  //TLatex* l= new TLatex(0,0,label1);l->SetTextSize(0.04);
  //l->DrawLatex(1600,4000,label1);
  //l->DrawLatex(1720,3200,label2);
  //l->DrawLatex(1720,2400,label3);
  //c->cd(4);
  //hmJK->Draw();
  outtree->Write();
  outfile->Close();

}// end of main 
