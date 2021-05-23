#ifndef PSIMACEActionInitialization_h
#define PSIMACEActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

// Action initialization class.
class PSIMACEDetectorConstruction;

class PSIMACEActionInitialization : public G4VUserActionInitialization
{
  public:
    PSIMACEActionInitialization(); 
    virtual ~PSIMACEActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    PSIMACEDetectorConstruction* fDetConstruction;

};

#endif
