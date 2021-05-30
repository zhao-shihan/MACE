#ifndef MACETransportField2_hh
#define MACETransportField2_hh 1

#include "globals.hh"
#include "G4MagneticField.hh"

class MACETransportField2 : public G4MagneticField {
private:
    // const G4double fBy;
    const G4double fBz;

    const G4double fTransportField2Z;

public:
    MACETransportField2(G4double transportField2Z);
    virtual ~MACETransportField2();
    virtual void GetFieldValue(const G4double point[4], double* bField) const;
};

#endif

