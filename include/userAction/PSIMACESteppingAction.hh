#ifndef PSIMACESteppingAction_h
#define PSIMACESteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4PVPlacement.hh"

class PSIMACESteppingAction : public G4UserSteppingAction {
private:
    const G4PVPlacement* const* fPhysicalMagneticSpectrometerShield;
    const size_t fPhysicalMagneticSpectrometerShieldCount;
    const G4PVPlacement* const* fPhysicalCsIShield;
    const size_t fPhysicalCsIShieldCount;

public:
    PSIMACESteppingAction();
    virtual ~PSIMACESteppingAction();

    virtual void UserSteppingAction(const G4Step* step);
};

#endif
