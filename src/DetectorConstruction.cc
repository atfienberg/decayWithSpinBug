#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Torus.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UniformMagField.hh"
#include "G4Mag_SpinEqRhs.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4ClassicalRK4.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
  : 
  G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 8*m;
  G4double world_sizeZ  = 1*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       world_sizeXY, world_sizeXY, world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //turn counter object
  G4Torus* solidCounter = new G4Torus("torus", 
				 0, 0.5*m, 7.112*m, pi/2.0-pi/10.0, pi/5.0);
  G4LogicalVolume* logicCounter = new G4LogicalVolume(solidCounter, world_mat, "counter");
  new G4PVPlacement(0, G4ThreeVector(), logicCounter, "physCounter", logicWorld, false, 0, checkOverlaps);
  
  //make field
  G4double fieldValue = 1.5 * tesla;
  G4UniformMagField* theField = new G4UniformMagField(G4ThreeVector(0., 0., fieldValue));
  G4Mag_SpinEqRhs* eqn = new G4Mag_SpinEqRhs(theField);
  G4int nvar = 12;
  G4MagIntegratorStepper* stepper = new G4ClassicalRK4(eqn, nvar);

  G4FieldManager* manager = G4TransportationManager::GetTransportationManager()->GetFieldManager();
  manager->SetDetectorField(theField);
  G4double minStep = 0.01*mm;
  G4MagInt_Driver* driver = new G4MagInt_Driver(minStep, 
						stepper, 
						stepper->GetNumberOfVariables());
  G4ChordFinder* cFinder = new G4ChordFinder(driver);
  manager->SetChordFinder(cFinder);

  manager->SetMinimumEpsilonStep(1e-7);
  manager->SetMaximumEpsilonStep(1e-6);
  manager->SetDeltaOneStep(0.01*mm);
  manager->SetDeltaIntersection(0.01*mm);

  //
  //always return the physical World
  //
  return physWorld;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
