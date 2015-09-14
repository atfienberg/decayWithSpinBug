#include "PhysicsList.hh"
#include "G4LeptonConstructor.hh"
#include "G4MuonPlus.hh"
#include "G4DecayWithSpin.hh"
#include "G4DecayTable.hh"
#include "G4MuonDecayChannelWithSpin.hh"
#include "G4MuonRadiativeDecayChannelWithSpin.hh"
#include "G4Gamma.hh"

#include "G4LossTableManager.hh"
#include "G4ProcessManager.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList() 
  : G4VModularPhysicsList()
{
  SetVerboseLevel(1);

  G4LossTableManager::Instance();
  SetDefaultCutValue(1*mm);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::~PhysicsList()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructParticle()
{
  G4LeptonConstructor lepCon;
  lepCon.ConstructParticle();

  G4Gamma::Gamma();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructProcess()
{
  // transportation
  //
  AddTransportation();
  
  G4DecayWithSpin* decayWithSpin = new G4DecayWithSpin();

  G4ProcessManager* pmanager = G4MuonPlus::MuonPlus()->GetProcessManager();
  pmanager->AddProcess(decayWithSpin);
  pmanager->SetProcessOrdering(decayWithSpin, idxPostStep);
  pmanager->SetProcessOrdering(decayWithSpin, idxAtRest);

  G4DecayTable* muonPlusDecayTable = new G4DecayTable();
  muonPlusDecayTable->Insert(new
			     G4MuonDecayChannelWithSpin("mu+",0.986));
  muonPlusDecayTable->Insert(new
			     G4MuonRadiativeDecayChannelWithSpin("mu+",0.014));
  G4MuonPlus::MuonPlus()->SetDecayTable(muonPlusDecayTable);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
