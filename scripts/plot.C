#include "TTree.h"
#include "TFile.h"
#include "TString.h"


void
plot(TString infilename, TString plotfilename){
  TFile* infile=TFile::Open(infilename,"READ");
  TTree* intree=(TTree*)infile->Get("ps");

  TFile* plotfile=TFile::Open(plotfilename,"RECREATE");
  intree->Draw("mJPK>>hmJPK(200,5300,6000)");


  // get all the created histos and write them to file
  TList* objlist = gDirectory->GetList();
  for(int io=0;io<objlist->GetEntries();io++){
    if(dynamic_cast<TTree*>(objlist->At(io))!=NULL)continue;
    objlist->At(io)->Write();
  }

  
  plotfile->Close();
  infile->Close();
}
 
