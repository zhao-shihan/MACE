#ifndef PSIMACETransportField2_hh
#define PSIMACETransportField2_hh 1

#include "globals.hh"
#include "G4MagneticField.hh"

class PSIMACETransportField2 : public G4MagneticField {
private:
    // const G4double fBy;
    const G4double fBz;

    const G4double fTransportField2Z;

public:
    PSIMACETransportField2(G4double transportField2Z);
    virtual ~PSIMACETransportField2();
    virtual void GetFieldValue(const G4double point[4], double* bField) const;
};

#endif

