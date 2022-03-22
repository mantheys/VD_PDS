// Arapuca simulation
// Authors: L. Paulucci & F. Marinho
// Date: 20th September 2016
//
// Added modifications should be reported in arapuca.cc header comments

#include "G4UImanager.hh"
#include "Randomize.hh"

#include "RunAction.hh"
#include "g4root.hh"

RunAction::RunAction(DetectorConstruction* det, double x, double y, double z) 
:fDetector(det)
{   
  fSaveRndm = 0;
  x0 = x;
  y0 = y;
  z0 = z;   
}

RunAction::~RunAction()
{
}

std::string convertToString(const double & x, const int & precision = 1)
{
    static std::ostringstream ss;
    ss.str(""); // don't forget to empty the stream
    ss << std::fixed << std::setprecision(precision) << x;

    return ss.str();
}

void RunAction::BeginOfRunAction(const G4Run*)
{  
  
  // Get/create analysis manager
  G4cout << "##### Create analysis manager " << "  " << this << G4endl;
  
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  
  G4cout << "Using " << man->GetType() << " analysis manager" << G4endl;

  std::string s_x = convertToString(x0,4);
  std::string s_y = convertToString(y0,4);
  std::string s_z = convertToString(z0,4);

  G4String root_name = std::string("arapuca")+"_"+s_x+"_"+s_y+"_"+s_z+".root";
  
  // Open an output file
  man->OpenFile(root_name);
  man->SetFirstNtupleId(1);

  //Declare ntuples
  //
  // Create 1st ntuple (id = 1)
  //
  man->CreateNtuple("ntuple", "data");
  man->CreateNtupleIColumn("evt");
  man->CreateNtupleIColumn("pdg");
  man->CreateNtupleIColumn("id");
  man->CreateNtupleIColumn("mid");
  man->CreateNtupleDColumn("x");
  man->CreateNtupleDColumn("y");
  man->CreateNtupleDColumn("z");
  man->CreateNtupleDColumn("de");
  man->CreateNtupleDColumn("e");
  man->CreateNtupleIColumn("vol");
  man->CreateNtupleIColumn("volrep");
  man->CreateNtupleIColumn("mvol");
  man->CreateNtupleIColumn("mvolrep");
  man->CreateNtupleIColumn("inter");
  man->CreateNtupleDColumn("time");
  man->FinishNtuple();

  G4int nvols = 710;
  G4int hv_id = man->CreateH1("hv","",nvols+1,-0.5,nvols+0.5);

  // save Rndm status
  if (fSaveRndm > 0)
    { 
      CLHEP::HepRandom::showEngineStatus();
      CLHEP::HepRandom::saveEngineStatus("beginOfRun.rndm");
    }
 
  fNumEvent = 0;
  
}

void RunAction::EndOfRunAction(const G4Run* /*aRun*/)
{     
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  
  // save Rndm status
  if (fSaveRndm == 1)
  { 
    CLHEP::HepRandom::showEngineStatus();
    CLHEP::HepRandom::saveEngineStatus("endOfRun.rndm");
  }   
  
  G4cout << G4endl;    
        
  man->Write();
  man->CloseFile();
  
  delete G4AnalysisManager::Instance();

}
