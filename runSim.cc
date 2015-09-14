#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"
#include "SteppingVerbose.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc,char** argv) {

  //choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  long seeds[2];
  seeds[0] = (long) time(NULL);
  seeds[1] = (long) (seeds[0] * G4UniformRand());
  CLHEP::HepRandom::setTheSeeds(seeds);



  //my Verbose output class
  G4VSteppingVerbose::SetInstance(new SteppingVerbose);

  // Construct the default run manager
  unique_ptr<G4RunManager> runManager(new G4RunManager);
 
  //initialization classes
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(new ActionInitialization());

   
  // get the pointer to the User Interface manager 
  G4UImanager* UI = G4UImanager::GetUIpointer();  

  if (argc!=1)   // batch mode  
    {
     G4String command = "/control/execute ";
     G4String fileName = argv[1];
     UI->ApplyCommand(command+fileName);
    }
    
  else           //define visualization and UI terminal for interactive mode
    {       
      unique_ptr<G4VisManager> visManager(new G4VisExecutive);
      visManager->Initialize();
      cout << "vis initializing" << endl;
      
      
      unique_ptr<G4UIExecutive> ui(new G4UIExecutive(argc,argv));      
      ui->SessionStart();
    }   

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

