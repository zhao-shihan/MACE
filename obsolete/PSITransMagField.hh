#ifndef PSIMACETransMagField_H
#define PSIMACETransMagField_H 1

#include "globals.hh"
#include "G4ElectroMagneticField.hh"

class G4GenericMessenger;

// Magnetic field

class PSIMACETransMagField : public G4ElectroMagneticField
{
  public:
    PSIMACETransMagField();
    virtual ~PSIMACETransMagField();
    
    virtual void GetFieldValue(const G4double point[4],double* bField ) const;
    
    void SetField(G4double val) { fBy = val; }
    G4double GetField() const { return fBy; }
    
   G4bool   DoesFieldChangeEnergy() const { return true; }

  private:
    void DefineCommands();

    G4GenericMessenger* fMessenger;
    G4double fBy;
	G4double fEy;
};


#endif
