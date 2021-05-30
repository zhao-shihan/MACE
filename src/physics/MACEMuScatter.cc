// MACEMuScatter
//
// Author:	Yuzhe Mao
//
// Review and update: Shihan Zhao 05.2021
//

#include "physics/MACEMuScatter.hh"

MACEMuScatter::MACEMuScatter(const G4String& name, G4ProcessType  aType) :
    G4VDiscreteProcess(name, aType),
    fParticleChange(new G4ParticleChange()) {}

MACEMuScatter:: ~MACEMuScatter() {
    delete fParticleChange;
}

G4VParticleChange* MACEMuScatter::PostStepDoIt(const G4Track& track, const G4Step& step) {
    fParticleChange->Initialize(track);
    if (!step.IsLastStepInVolume()) {
        fParticleChange->ProposeTrackStatus(fStopButAlive);
    }
    return fParticleChange;
}

G4double MACEMuScatter::GetMeanFreePath(const G4Track& track, G4double, G4ForceCondition* condition) {
    *condition = Forced;
    if (track.GetMaterial()->GetState() == kStateSolid ||
        track.GetMaterial()->GetState() == kStateLiquid) {
        return 24 * CLHEP::um;
    } else {
        return std::numeric_limits<G4double>::max();
    }
}
