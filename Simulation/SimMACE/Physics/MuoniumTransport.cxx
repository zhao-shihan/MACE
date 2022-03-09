#include "G4MPImanager.hh"
#include "G4SystemOfUnits.hh"

#include "SimMACE/Physics/MuoniumTransport.hxx"
#include "SimMACE/Physics/Muonium.hxx"
#include "SimMACE/Utility/Region.hxx"

using namespace MACE::SimMACE::Physics;

MuoniumTransport::MuoniumTransport() :
    G4VContinuousProcess("MuoniumTransport", fTransportation),
    SimMTransport::Track(),
    fParticleChange() {

    if (MPI::Is_initialized()) {
        SimMTransport::Track::global->SetCommRank(G4MPImanager::GetManager()->GetRank());
    } else {
        SimMTransport::Track::global->SetCommRank(0);
    }

    SimMTransport::Track::global->SetTarget(new TF3("Target", "(-30000<x&&x<30000 && -30000<y&&y<30000 && -23050<z&&z<-13050) && (((x-(round((x-0.577350269189626*y)/101)+0.5*round(1.154700538379251*y/101))*101)*(x-(round((x-0.577350269189626*y)/101)+0.5*round(1.154700538379251*y/101))*101)+(y-0.866025403784439*round(1.154700538379251*y/101)*101)*(y-0.866025403784439*round(1.154700538379251*y/101)*101)>0.25*86*86) || (z<-18050 || x<-20000||x>20000 || y<-20000||y>20000))"));
    SimMTransport::Track::global->SetStepOfPushing(1.5);
    SimMTransport::Track::global->SetMuoniumMass(Muonium::Definition()->GetPDGMass() / MeV);
    SimMTransport::Track::global->SetMeanFreePath(new TF3("MeanFreePath", "0.1"));
    SimMTransport::Track::global->SetTemperature(300);
}

G4double MuoniumTransport::GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double&) {
    if (static_cast<Region*>(track.GetVolume()->GetLogicalVolume()->GetRegion())->GetType() == Region::kTarget) {
        SimMTransport::Track::fLife = (track.GetDynamicParticle()->GetPreAssignedDecayProperTime() - track.GetProperTime()) / us;
        if (SimMTransport::Track::fLife > 0) {
            SimMTransport::Track::fVertexTime = track.GetProperTime() / us;
            SimMTransport::Track::fVertexPosition = TEveVectorD(track.GetPosition().x(), track.GetPosition().y(), track.GetPosition().z()) * (1.0 / um);
            SimMTransport::Track::fCurrentStep->postTime = fVertexTime;
            SimMTransport::Track::fCurrentStep->postPosition = fVertexPosition;
            SimMTransport::Track::fEscaping = false;
            SimMTransport::Track::fStatus = SimMTransport::kTrackInitialized;
            do {
                SimMTransport::Track::Stepping();
            } while (SimMTransport::Track::fStatus == SimMTransport::kTrackAlive);
            return 0.0;
        } else {
            return DBL_MAX;
        }
    } else {
        if (track.GetMaterial()->GetState() == kStateGas) {
            return DBL_MAX;
        } else {
            return 0.0;
        }
    }
}

G4VParticleChange* MuoniumTransport::AlongStepDoIt(const G4Track& track, const G4Step&) {
    fParticleChange.Initialize(track);
    if (static_cast<Region*>(track.GetVolume()->GetLogicalVolume()->GetRegion())->GetType() == Region::kTarget) {
        if (SimMTransport::Track::fLife > 0) {
            fParticleChange.ProposeProperTime(SimMTransport::Track::fCurrentStep->postTime * us);
            const auto& position = SimMTransport::Track::fCurrentStep->postPosition;
            fParticleChange.ProposePosition(G4ThreeVector(position.fX, position.fY, position.fZ) * um);
            const auto& velocity = SimMTransport::Track::fCurrentStep->velocity;
            auto speed = velocity.Mag();
            fParticleChange.ProposeMomentumDirection(G4ThreeVector(velocity.fX, velocity.fY, velocity.fZ) / speed);
            fParticleChange.ProposeVelocity(speed * (um / us));
        }
    } else if (track.GetMaterial()->GetState() != kStateGas) {
        fParticleChange.ProposeTrackStatus(fStopButAlive);
    }
    return std::addressof(fParticleChange);
}
