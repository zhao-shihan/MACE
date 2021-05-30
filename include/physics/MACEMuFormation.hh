#ifndef   MACEMuFormation_h
#define   MACEMuFormation_h 1

#include "G4VDiscreteProcess.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleChange.hh"
#include "G4PVPlacement.hh"

#include "physics/yields.hh"

/*! MACEMuFormation class defines the muonium formation process in the Carbon foil
 *  according to yields from Gonin's paper Sci. Rev. Instrum. 65(3), 648-652 (1994).
 * \image html yields3.gif The muonium formation yields.
 * The main parameters are the foil thickness and muon energy. For a given energy,
 * a corresponding proportion of the muons will be converted into Muonium.
 * Concretely, the muon is eliminated and replaced by a Muonium with identical
 * properties, including time, energy, momentum, position etc.
 *
 * The process is executed at the END of a step, i.e. the muon is converted into
 * Muonium AFTER flying through the Carbon foil (see also yields.hh). */

class MACEMuFormation : public G4VDiscreteProcess {
private:
    G4ParticleChange* const fParticleChange;

    const G4PVPlacement* const fPhysicalSiO2Target;

public:
    MACEMuFormation(const G4String& name = "MuFormation", G4ProcessType aType = fElectromagnetic);
    ~MACEMuFormation();

    virtual G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);
    virtual G4double GetMeanFreePath(const G4Track& track, G4double, G4ForceCondition* condition);
};

#endif
