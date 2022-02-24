// A simple TTreeReader use: read data from hsimple.root (written by hsimple.C)
#include <TFile.h>
#include <TH1F.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

void hsimpleReader()
{
   TFile* hist = new TFile("hist.root", "RECREATE");
   
   // Create a histogram for the values we read.
   TH1D* myHist = new TH1D("h1", "ntuple", 636, 0, 636);
   
   // Open the file containing the tree.
   TFile *myFile = TFile::Open("arapuca.root");
   
   // Create a TTreeReader for the tree, for instance by passing the
   // TTree's name and the TDirectory / TFile it is in.
   TTreeReader myReader("ntuple", myFile);
   
   // The branch "px" contains floats; access them as myPx.
   TTreeReaderValue<Int_t> myVol(myReader, "vol");
   
   // Loop over all entries of the TTree or TChain.
   while (myReader.Next())
   {
      // Just access the data as if myPx and myPy were iterators (note the '*' in front of them):
      myHist->Fill(*myVol);
   }
   myHist->Draw();
   hist->Write();
   hist->Close();
}