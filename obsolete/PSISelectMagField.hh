#ifndef PSIMACESelectMagField_H
#define PSIMACESelectMagField_H 1

#include "globals.hh"
#include "G4MagneticField.hh"

class G4GenericMessenger;

// Magnetic field

class PSIMACESelectMagField : public G4MagneticField {
public:
    PSIMACESelectMagField();
    virtual ~PSIMACESelectMagField();

    virtual void GetFieldValue(const G4double point[4], double* bField) const;

    void SetField(G4double val) { fBy = val; }
    G4double GetField() const { return fBy; }

private:
    void DefineCommands();

    G4GenericMessenger* fMessenger;
    G4double fBy;
};


#endif
