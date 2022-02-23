
void lightYieldXe()
{
  
  gROOT->SetStyle("Plain");
 
  TH1D* ht = new TH1D("ht","",641,-0.5,640.5); //histogram for collecting data from files
  TFile* f0;
  
  double dx = 0.675/2;
  double dy = 0.65/2;
  double dz = 0.25;
  double x0, y0, z0, sum=0, sumtot=0;
  TString fname;
  TH1D* ha;//auxiliar histogram
  TH2F *Xeaux = new TH2F("Xeaux","Pe per MeV ",40,-6.75,6.75,20,-3.25,3.25);//Auxiliar LY map (Xe only)
  TH2F *Phtot = new TH2F("Phztotxe","Pe per MeV ",40,-6.75,6.75,20,-3.25,3.25); //LY map for Ar+Xe
  TH2F *PhtotAr = new TH2F("PhztotAr","Pe per MeV ",40,-6.75,6.75,20,-3.25,3.25);  //LY map Ar only (was created before, just reading in this macro)
  
  for(int i=0;i<20;i++)
  { //loop over x position
    for(int j=0;j<20;j++)
    {//loop over y position
      for(int k=0;k<7;k++)
      {//loop over z position -- to get average on center
   	    x0 = i*dx;
   	    y0 = j*dy-3.25+dy/2.0;
   	    z0 = k*dz;
	
        for(int m=1;m<11;m++)
        {//loop over files (1 million photons per file)
          fname.Form("vdoutXe/histo_%d_%d_%d_%d.root",i,j,k,m);
          f0 = TFile::Open(fname);
          ha = (TH1D*)f0->Get("hv");
          //summing to get average at center, but can be made per plane (k value)
          ht->Add(ha);
          f0->Close();
        }
	
        sum=ht->Integral(5,164) + 0.8*(ht->Integral(165,484));//summing all landing photons over the two laterals (index from 5 to 164) and cathode (from 165 to 484) with 80% light transmission

	      sumtot+=sum;

   	    ht->Reset();
      } //for in k
      //3% detection efficiency and 25,000 photons per MeV
      sumtot=sumtot*0.03*25/10000; 
      //Divide by 7 because there are 7 different values of z (k)
      Xeaux->Fill(x0,y0,sumtot/7); 
      sumtot=0.0;

    } //for in j
  }//for in i

  int aux=40;
  for(int i=1;i<=20;i++)
  { //mirror over x
    for(int j=1;j<=20;j++)
    {
      Xeaux->SetBinContent(i,j,Xeaux->GetBinContent(aux,j));
    }
    aux--;
  }

  TFile* f = TFile::Open("lyR0.root");
  PhtotAr->Add((TH2F*)f->Get("Phztot"));
  double avg; //auxiliar variable for getting the weighted histo
  
  for(int i=1;i<=40;i++)
  {
    for(int j=1;j<=20;j++)
    {
      avg=(PhtotAr->GetBinContent(i,j))*0.25;
      avg+=(Xeaux->GetBinContent(i,j))*0.75;
      Phtot->SetBinContent(i,j,avg);
    }
  }
    
  gStyle->SetPalette(1);
  TFile* total = new TFile("lyR0XeR20.root", "RECREATE");
  Phtot->GetXaxis()->SetTitle("x (m)");
  Phtot->GetYaxis()->SetTitle("y (m)");
  Phtot->Draw("COLZ");
  Phtot->Write();

  f->Close();
  total->Close();
}
