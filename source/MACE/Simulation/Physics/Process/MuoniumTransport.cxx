#include "MACE/Simulation/Physics/Messenger/MuoniumPhysicsMessenger.hxx"
#include "MACE/Simulation/Physics/Process/MuoniumTransport.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4TransportationManager.hh"
#include "Randomize.hh"

namespace MACE::Simulation::Physics::Process {

using namespace Utility::PhysicalConstant;
using namespace Utility::LiteralUnit;

MuoniumTransport::MuoniumTransport() :
    G4VContinuousProcess("MuoniumTransport", fTransportation),
    fTarget(std::addressof(Target::Instance())),
    fRandEng(nullptr),
    fMeanFreePath(0.2_um),
    fTolerance(fToleranceScale * fMeanFreePath),
    fParticleChange(),
    fCase(kUnknown),
    fIsExitingTargetVolume(false) {
    pParticleChange = std::addressof(fParticleChange);
    Messenger::MuoniumPhysicsMessenger::Instance().SetTo(this);
}

void MuoniumTransport::SetMeanFreePath(G4double val) {
    fMeanFreePath = val;
    // try to prevent bad tolerance
    fTolerance = std::max(fToleranceScale * fMeanFreePath, 1000 * DBL_EPSILON);
}

void MuoniumTransport::StartTracking(G4Track* track) {
    G4VContinuousProcess::StartTracking(track);
    // the random engine in use
    fRandEng = G4Random::getTheEngine();
}

G4VParticleChange* MuoniumTransport::AlongStepDoIt(const G4Track& track, const G4Step&) {
    fParticleChange.Initialize(track);
    switch (fCase) {
    case kUnknown:
        // Never
        break;
    case kDecaying:
        // Do nothing
        break;
    case kInsideTargetVolume:
        ProposeRandomFlight(track);
        break;
    case kExitingTargetVolume:
        // Don't do anything, wait for G4Navigator to update
        // just reset the flag
        fIsExitingTargetVolume = false;
        break;
    case kExitedTargetVolume:
        if (track.GetMaterial()->GetState() != kStateGas) {
            fParticleChange.ProposeTrackStatus(fStopButAlive);
        }
        break;
    }
    return std::addressof(fParticleChange);
}

G4double MuoniumTransport::GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double& safety) {
    if (track.GetProperTime() >= track.GetDynamicParticle()->GetPreAssignedDecayProperTime()) {
        fCase = kDecaying;
        SetGPILSelection(NotCandidateForSelection);
        return safety;
    } else if (fTarget->VolumeContains(track.GetPosition())) {
        fCase = kInsideTargetVolume;
        return DBL_MIN;
    } else if (fIsExitingTargetVolume) {
        fCase = kExitingTargetVolume;
        return DBL_MIN;
    } else {
        fCase = kExitedTargetVolume;
        // in other material, could be extracted to another process in future
        if (track.GetMaterial()->GetState() == kStateGas) {
            SetGPILSelection(NotCandidateForSelection);
            return safety;
        } else {
            return DBL_MIN;
        }
    }
}

void MuoniumTransport::ProposeRandomFlight(const G4Track& track) {
    // 'cause the momentum, position, etc. violates much in this process, no easy way of using G4 tracking mechanism to manage this process.
    // Thus we do that ourselves. The decay time is pre-assigned and used for limiting the flight time, and the "true safety" is ensured by bool expr.

    // pre step point position
    const auto& initialPosition = track.GetPosition();
    // get the pre-assigned decay time to determine when the flight stops and then let G4 decay it
    const auto timeLimit = track.GetDynamicParticle()->GetPreAssignedDecayProperTime();
    // std dev of velocity of single direction
    const auto sigmaV = std::sqrt((k_Boltzmann * c_squared / muon_mass_c2) * track.GetMaterial()->GetTemperature());

    // the total flight length in this G4Step
    G4double trueStepLength = 0;
    // velocity magnitude
    G4double velocity = track.GetVelocity();
    // momentum direction
    G4ThreeVector direction = track.GetMomentumDirection();
    // elapsed time of the flight
    G4double flightTime = 0;
    // displacement of the flight
    // using this displacement instead of track local position in flight for better accuracy
    G4ThreeVector displacement(0, 0, 0);
    // current position in flight
    G4ThreeVector position = initialPosition;
    // the free path of single flight step
    G4double freePath;
    // the free time of single flight step
    G4double freeTime;

    // do random flight

    do {
        if (fTarget->Contains(position)) {
            // sampling free path
            freePath = G4RandExponential::shoot(fRandEng, fMeanFreePath);
            // set a gauss vector of sigma=1
            direction.set(G4RandGauss::shoot(fRandEng),
                          G4RandGauss::shoot(fRandEng),
                          G4RandGauss::shoot(fRandEng));
            // get its length before multiply sigmaV
            velocity = direction.mag();
            // normalize direction vector
            direction /= velocity;
            // get the exact velocity
            velocity *= sigmaV;
        } else {
            // inside vacuum region of target fine structure,
            // stepping with mean free path at same velocity
            freePath = fMeanFreePath;
        }
        // the free time
        freeTime = freePath / velocity;
        // update flight length
        trueStepLength += freePath;
        // update time
        flightTime += freeTime;
        // update displacement
        displacement += freePath * direction;
        // update current position
        position = initialPosition + displacement;
        // do the flight until time up or out of target volume
    } while (flightTime < timeLimit and fTarget->VolumeContains(position));

    // flag indicate that the flight was stopped by decay
    const G4bool timeUp = flightTime > timeLimit;

    // then step back to fulfill the limit

    // the free time and free path correction of last step
    G4double finalStepFreePathCorrection;
    G4double finalStepFreeTimeCorrection;

    // do the back stepping
    if (timeUp) {
        // flight is break by decay
        // a tiny bit smaller correction ensuring the final value is little bit larger than decay time
        finalStepFreeTimeCorrection = std::nextafter(flightTime - timeLimit, -1.0);
        finalStepFreePathCorrection = velocity * finalStepFreeTimeCorrection;
    } else {
        // flight is break by target boundary
        const auto tolerance2 = fTolerance * fTolerance;
        auto moreDisplacement = displacement;
        auto lessDisplacement = displacement - freePath * direction;
        auto midDisplacement = (moreDisplacement + lessDisplacement) / 2;
        // prevent dead loop in case of really bad tolerance
        constexpr int maxLoop = 50;
        int nLoop = 0;
        do {
            if (fTarget->VolumeContains(initialPosition + midDisplacement)) {
                lessDisplacement = midDisplacement;
            } else {
                moreDisplacement = midDisplacement;
            }
            midDisplacement = (moreDisplacement + lessDisplacement) / 2;
            ++nLoop;
        } while ((moreDisplacement - lessDisplacement).mag2() > tolerance2 and nLoop < maxLoop);
        // a tiny bit smaller correction ensuring the final position is outside the volume
        finalStepFreePathCorrection = (displacement - moreDisplacement).mag();
        finalStepFreeTimeCorrection = finalStepFreePathCorrection / velocity;
        // remember to inform the next step that we are at the boundary of target
        fIsExitingTargetVolume = true;
    }

    // the final update

    // update flight length
    trueStepLength -= finalStepFreePathCorrection;
    // update time
    flightTime -= finalStepFreeTimeCorrection;
    // update displacement
    displacement -= finalStepFreePathCorrection * direction;
    // update current position
    position = initialPosition + displacement;

    // Propose particle change

    fParticleChange.ProposeTrueStepLength(trueStepLength);
    fParticleChange.ProposeMomentumDirection(direction);
    fParticleChange.ProposeEnergy(((muon_mass_c2 / c_squared) / 2) * velocity * velocity);
    fParticleChange.ProposeVelocity(velocity);
    fParticleChange.ProposeProperTime(track.GetProperTime() + flightTime);
    fParticleChange.ProposePosition(position);
    fParticleChange.ProposeLocalTime(track.GetLocalTime() + flightTime);
}

} // namespace MACE::Simulation::Physics::Process
