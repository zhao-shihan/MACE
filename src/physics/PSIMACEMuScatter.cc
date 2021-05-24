// PSIMACEMuScatter
//
// Author:	Yuzhe Mao
//
// Review and update: Shihan Zhao 05.2021
//

#include "physics/PSIMACEMuScatter.hh"

PSIMACEMuScatter::PSIMACEMuScatter(const G4String& name, G4ProcessType  aType) :
    G4VDiscreteProcess(name, aType),
    fParticleChange(new G4ParticleChange()) {}

PSIMACEMuScatter:: ~PSIMACEMuScatter() {
    delete fParticleChange;
}

G4VParticleChange* PSIMACEMuScatter::PostStepDoIt(const G4Track& track, const G4Step& step) {
    fParticleChange->Initialize(track);
    if (!step.IsLastStepInVolume()) {
        fParticleChange->ProposeTrackStatus(fStopButAlive);
    }
    return fParticleChange;
}

G4double PSIMACEMuScatter::GetMeanFreePath(const G4Track& track, G4double, G4ForceCondition* condition) {
    *condition = Forced;
    if (track.GetMaterial()->GetState() == kStateSolid ||
        track.GetMaterial()->GetState() == kStateLiquid) {
        return 24 * CLHEP::um;
    } else {
        return std::numeric_limits<G4double>::max();
    }
}
