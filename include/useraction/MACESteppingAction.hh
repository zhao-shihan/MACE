#ifndef MACESteppingAction_h
#define MACESteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4PVPlacement.hh"

class MACESteppingAction : public G4UserSteppingAction {
private:
    const G4PVPlacement* const* fPhysicalMagneticSpectrometerShield;
    const size_t fPhysicalMagneticSpectrometerShieldCount;
    const G4PVPlacement* const* fPhysicalCsIShield;
    const size_t fPhysicalCsIShieldCount;

public:
    MACESteppingAction();
    virtual ~MACESteppingAction();

    virtual void UserSteppingAction(const G4Step* step);
};

#endif
