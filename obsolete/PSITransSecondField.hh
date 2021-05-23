#ifndef PSIMACETransSecondField_H
#define PSIMACETransSecondField_H 1

#include "globals.hh"
#include "G4MagneticField.hh"

class G4GenericMessenger;

// Magnetic field

class PSIMACETransSecondField : public G4MagneticField
{
  public:
    PSIMACETransSecondField();
    virtual ~PSIMACETransSecondField();
    
    virtual void GetFieldValue(const G4double point[4],double* bField ) const;
    
    void SetField(G4double val) { fBy = val; }
    G4double GetField() const { return fBy; }
    
  private:
    void DefineCommands();

    G4GenericMessenger* fMessenger;
    G4double fBy;
};


#endif
