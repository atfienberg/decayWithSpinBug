#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ActionInitialization : public G4VUserActionInitialization
{
public:
  ActionInitialization();

  virtual ~ActionInitialization();

  virtual void Build() const;

  virtual void BuildForMaster() const;

  virtual G4VSteppingVerbose* InitializeSteppingVerbose() const;
private:
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
