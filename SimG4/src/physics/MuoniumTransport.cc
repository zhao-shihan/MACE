#include "G4Track.hh"
#include "G4RunManager.hh"

#include "detector/geometry/Target.hh"
#include "physics/Muonium.hh"
#include "physics/MuoniumTransport.hh"

using namespace MACE::SimG4::Physics;

MuoniumTransport::MuoniumTransport(const G4String& name, G4ProcessType aType) :
    G4VContinuousProcess(name, aType),
    SimMTransport::Track(),
    fParticleChange(new G4ParticleChange()),
    fpTarget(static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction())->GetTarget()->GetPhysicalVolume()) {

    if (MPI::Is_initialized()) {
        int commRank; MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
        int commSize; MPI_Comm_size(MPI_COMM_WORLD, &commSize);
        SimMTransport::Track::global->SetCommRank(commRank);
        SimMTransport::Track::global->SetCommSize(commSize);
        SimMTransport::Track::global->SetMasterRank(-1);
        SimMTransport::Track::global->SetWorkerNum(commSize);
    } else {
        SimMTransport::Track::global->SetCommRank(0);
        SimMTransport::Track::global->SetCommSize(1);
        SimMTransport::Track::global->SetMasterRank(-1);
        SimMTransport::Track::global->SetWorkerNum(1);
    }

    SimMTransport::Track::global->SetTarget(new TF3("Target", "(-25000<x&&x<25000 && -25000<y&&y<25000 && -10000<z&&z<0) && (((x-(round((x-0.577350269189626*y)/101)+0.5*round(1.154700538379251*y/101))*101)*(x-(round((x-0.577350269189626*y)/101)+0.5*round(1.154700538379251*y/101))*101)+(y-0.866025403784439*round(1.154700538379251*y/101)*101)*(y-0.866025403784439*round(1.154700538379251*y/101)*101)>0.25*86*86) || (z<-5000 || x<-15000||x>15000 || y<-15000||y>15000))"));
    SimMTransport::Track::global->SetStepOfPushing(1.5);
    SimMTransport::Track::global->SetMuoniumMass(Muonium::Definition()->GetPDGMass() / MeV);
    SimMTransport::Track::global->SetMeanFreePath(new TF3("MeanFreePath", "0.1"));
    SimMTransport::Track::global->SetTemperature(300);
    SimMTransport::Track::global->SetSeedForWorker0(G4Random::getTheSeed());
}

MuoniumTransport::~MuoniumTransport() {
    delete fParticleChange;
}

G4double MuoniumTransport::GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double&) {
    if (track.GetVolume() == fpTarget) {
        SimMTransport::Track::fLife = (track.GetDynamicParticle()->GetPreAssignedDecayProperTime() - track.GetProperTime()) / us;
        if (SimMTransport::Track::fLife > 0) {
            SimMTransport::Track::fVertexTime = track.GetProperTime() / us;
            const auto& prePos = track.GetPosition();
            SimMTransport::Track::fVertexPosition = SimMTransport::Vector3(prePos.x(), prePos.y(), prePos.z()) / um;
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
    fParticleChange->Initialize(track);
    if (track.GetVolume() == fpTarget) {
        if (SimMTransport::Track::fLife > 0) {
            fParticleChange->ProposeProperTime(SimMTransport::Track::fCurrentStep->postTime * us);
            const auto& postPos = SimMTransport::Track::fCurrentStep->postPosition;
            fParticleChange->ProposePosition(G4ThreeVector(postPos.x, postPos.y, postPos.z) * um);
            const auto& velocity = SimMTransport::Track::fCurrentStep->velocity;
            auto speed = velocity.Norm();
            fParticleChange->ProposeMomentumDirection(G4ThreeVector(velocity.x, velocity.y, velocity.z) / speed);
            fParticleChange->ProposeVelocity(speed * um / us);
        }
    } else if (track.GetMaterial()->GetState() != kStateGas) {
        fParticleChange->ProposeTrackStatus(fStopButAlive);
    }
    return fParticleChange;
}
