#include <TFile.h>
#include <TMath.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

void lightYield(){
  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.15);

  // FULL SIMULATION GRID PARAMETERS
  // double xmin = -6.5;double xmax = 6.5;double dx = 0.1625;int nbinsx = 40;
  // double ymin = -3.5;double ymax = 3.5;double dy = 0.1625;int nbinsy = 40;
  // double zmin = 0.0 ;double zmax = 3.0;double dy = 0.25  ;int nbinsz = 14;

  // FAST SIMULATION GRID PARAMETERS
  double xmin = -6.5 ;double xmax = 6.5;double dx = 0.325;int nbinsx = 40;
  double ymin = -6.5;double ymax = 6.5;double dy = 0.325;int nbinsy = 40;
  // double zmin = 0.0 ;double zmax = 3.0;double dz = 1.0  ;int nbinsz = 4;
  double zmin = 0.0 ;double zmax = 0.0;double dz = 0.0  ;int nbinsz = 1; 

  double pde = 3.e-2;       // photon detection efficiency [1]
  double ly_prod = 25.e3;   // produced photons per MeV [1/MeV]
  double ngen = 1.e6;       // number of generated photons per point [1]
  int nvols = 710;          // number of volumes in arapuca files

  TH1D* htXe = new TH1D("htXe","",nvols+1,-0.5,nvols+0.5); //Xe histogram for collecting data from files
  TH1D* htAr = new TH1D("htAr","",nvols+1,-0.5,nvols+0.5); //Ar histogram for collecting data from files
  TFile* fXe; TFile* fAr; 
  
  double x0, y0, z0, sumXe=0, sumtotXe=0, sumAr=0, sumtotAr=0;
  double err_sumtotXe, err_sumtotAr;
  
  TString fnameXe, fnameAr;
  TH1D* haXe; TH1D* haAr; //auxiliar histogram
  TH2F *Xeaux = new TH2F("Xeaux",    "PE per MeV ",nbinsx,xmin,xmax,nbinsy,ymin,ymax);  //Auxiliar LY map (Xe only)
  TH2F *Araux = new TH2F("Araux",    "PE per MeV ",nbinsx,xmin,xmax,nbinsy,ymin,ymax);  //Auxiliar LY map (Ar only)
  TH2F *Phtot = new TH2F("PhtotXeAr","PE per MeV ",nbinsx,xmin,xmax,nbinsy,ymin,ymax);  //LY map for Ar+Xe

  int bin_global;
  for(int i=0;i<nbinsx/2;i++){ //loop over x position
    for(int j=0;j<nbinsy/2;j++){//loop over y position
      for(int k=0;k<nbinsz;k++){
        x0 = dx/2+i*dx; y0 = -3.5+dy/2+j*dy; z0 = zmin+dz*k;

        fnameXe.Form("../RUN_Xe/arapuca_%.5f_%.5f_%.5f.root",x0,y0,z0);fnameAr.Form("../RUN_Ar/arapuca_%.5f_%.5f_%.5f.root",x0,y0,z0);
        fXe = TFile::Open(fnameXe);                              fAr = TFile::Open(fnameAr);
        haXe = (TH1D*)fXe->Get("hv");                            haAr = (TH1D*)fAr->Get("hv");
        htXe->Add(haXe);                                         htAr->Add(haAr); //summing to get average at center, but can be made per plane (k value)
        fXe->Close();                                            fAr->Close();
        
        // ACCOUNTING FOR CATHODE TRANSMISSION (CHANGE FROM 0.8 -> 0.9)
        float cathode_trans = 0.9;
        sumXe=htXe->Integral(5,164) + cathode_trans*(htXe->Integral(165,484));//summing all landing photons over the two laterals (index from 5 to 164) and cathode (from 165 to 484) with 80% light transmission
        sumAr=htAr->Integral(5,164) + cathode_trans*(htAr->Integral(165,484));

        sumtotXe+=sumXe;sumtotAr+=sumAr;
        htXe->Reset();htAr->Reset();
        } // for in k

      err_sumtotXe = (sqrt(sumtotXe)/ngen)*pde*ly_prod; //3% detection efficiency and 25,000 photons per MeV
      sumtotXe=(sumtotXe/ngen)*pde*ly_prod;             //3% detection efficiency and 25,000 photons per MeV
      err_sumtotAr = (sqrt(sumtotAr)/ngen)*pde*ly_prod;
      sumtotAr=(sumtotAr/ngen)*pde*ly_prod;

      y0 = dy/2+j*dy;

      bin_global = Xeaux->FindBin(x0,y0);
      Xeaux->SetBinContent(bin_global,sumtotXe/nbinsz);
      Xeaux->SetBinError(bin_global,err_sumtotXe/nbinsz);
      Araux->SetBinContent(bin_global,sumtotAr/nbinsz);
      Araux->SetBinError(bin_global,err_sumtotAr/nbinsz);

      sumtotXe=0.0;
      sumtotAr=0.0;  
    }   //for in j
  }     //for in i

  // mirror over x
  int aux  = nbinsx;
  for(int i=1;i<=nbinsx/2;i++){
    for(int j=nbinsy/2+1;j<=nbinsy;j++){
      Xeaux->SetBinContent(i,j,Xeaux->GetBinContent(aux,j));
      Xeaux->SetBinError(i,j,Xeaux->GetBinError(aux,j));
      Araux->SetBinContent(i,j,Araux->GetBinContent(aux,j));
      Araux->SetBinError(i,j,Araux->GetBinError(aux,j));
    }
    aux--;
  }

  // mirror over y
  aux  = nbinsy;
  for(int j=1;j<=nbinsy/2;j++){
    for(int i=1;i<=nbinsx;i++){
      Xeaux->SetBinContent(i,j,Xeaux->GetBinContent(i,aux));
      Xeaux->SetBinError(i,j,Xeaux->GetBinError(i,aux));
      Araux->SetBinContent(i,j,Araux->GetBinContent(i,aux));
      Araux->SetBinError(i,j,Araux->GetBinError(i,aux));
    }
    aux--;
  }

  //TFile* f = TFile::Open("lyR0.root");
  //PhtotAr->Add((TH2F*)f->Get("Phztot"));
  double avg; //auxiliar variable for getting the weighted histo
  double err;
  
  double ly_avg = 0.;
  double err_ly_avg = 0.;
  double ly_min = 1.e7;
  double err_ly_min = 0.;
  
  //ACCOUNT FOR XE AND AR FRACTIONS
  float Xe_contnet = 0.635;float Ar_content = 0.365;

  for(int i=1;i<=nbinsx;i++){
    for(int j=1;j<=nbinsy;j++){
      avg=(Araux->GetBinContent(i,j))*Ar_content;
      err = TMath::Power(Araux->GetBinError(i,j)*Ar_content,2); // for error, sum in quadrature Ar and Xe contributions. 
      avg+=(Xeaux->GetBinContent(i,j))*Xe_contnet;
      err += TMath::Power(Xeaux->GetBinError(i,j)*Xe_contnet,2);
      err = sqrt(err);  
      Phtot->SetBinContent(i,j,avg);
      Phtot->SetBinError(i,j,err);
      ly_avg += avg;
      err_ly_avg += TMath::Power(err,2);
      if (avg < ly_min) {
        ly_min = avg;
        err_ly_min = err;
        //std::cout << avg << ", " << err << std::endl;
      }
    }
  }

  ly_avg = ly_avg / (nbinsx*nbinsy);
  err_ly_avg = sqrt(err_ly_avg) / (nbinsx*nbinsy);
  
  std::cout << "ly_avg (PEs/MeV):" << Form("%.2f",ly_avg) << " +/- " << Form("%.2f",err_ly_avg) << std::endl;
  std::cout << "ly_min (PEs/MeV):" << Form("%.2f",ly_min) << " +/- " << Form("%.2f",err_ly_min) << std::endl;
    
  gStyle->SetPalette(1);
  TFile* total = new TFile(Form("LY_Xe%.2f_Ar%.2f.root",Xe_contnet,Ar_content), "RECREATE");
  Phtot->GetXaxis()->SetTitle("x (m)");
  Phtot->GetYaxis()->SetTitle("y (m)");
  Phtot->GetZaxis()->SetTitle("LY (PEs/MeV)");
  
  // Phtot->GetZaxis()->SetRangeUser(0,125);
  Phtot->Draw("COLZ");
  Phtot->Write();

  total->Close();
}
