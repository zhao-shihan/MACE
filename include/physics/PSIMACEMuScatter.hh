// PSIMACEMuScatter
//
// Author:	Yuzhe Mao
//
// Review and update: Shihan Zhao 05.2021
// 

/* PSIMACEMuScatter class defines the Muonium scattering process. It implements a very
 * basic model which assumes Muonium looses its electron as soon as it enters any
 * material (except for vacuum and CFoil). The class has only a PostStepDoIt method.
 * The in-flight Muonium spin precession has been supressed. */

#ifndef PSIMACEMuScatter_h
#define PSIMACEMuScatter_h 1

#include "G4VDiscreteProcess.hh"

class PSIMACEMuScatter : public G4VDiscreteProcess {
private:
    G4ParticleChange* const fParticleChange;

public:
    PSIMACEMuScatter(const G4String& name = "MuScatter", G4ProcessType aType = fGeneral);
    ~PSIMACEMuScatter();

    //! \mm The actions are taken at the end of the step.
    virtual G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);
    virtual G4double GetMeanFreePath(const G4Track& aTrack, G4double, G4ForceCondition* condition);
};

#endif
