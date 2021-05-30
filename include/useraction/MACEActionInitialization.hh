#ifndef MACEActionInitialization_h
#define MACEActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

// Action initialization class.
class MACEDetectorConstruction;

class MACEActionInitialization : public G4VUserActionInitialization
{
  public:
    MACEActionInitialization(); 
    virtual ~MACEActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    MACEDetectorConstruction* fDetConstruction;

};

#endif
