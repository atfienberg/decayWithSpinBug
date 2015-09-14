#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include <cmath>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction ()
:G4VUserPrimaryGeneratorAction(), 
 fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  G4ParticleDefinition* particle
    = G4ParticleTable::GetParticleTable()->FindParticle("mu+");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticlePosition(G4ThreeVector(0, 7.112*m, 0));  

  G4double gammaMagic = 29.3;
  G4double p = particle->GetPDGMass()*gammaMagic*std::sqrt(1-1/(gammaMagic*gammaMagic));
  fParticleGun->SetParticleMomentum(G4ThreeVector(p, 0.,0.));
  
  fParticleGun->SetParticlePolarization(G4ThreeVector(1.0, 0.0, 0.0));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begin of event
  //
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

