#include "MACE/PhaseI/SimMACEPhaseI/Action/PrimaryGeneratorAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/TrackingAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/PhaseI/Simulation/Hit/MRPCHit.h++"
#include "MACE/PhaseI/Simulation/Hit/SciFiHit.h++"
#include "MACE/PhaseI/Simulation/Hit/SciFiSiPMRawHit.h++"
#include "MACE/Simulation/Hit/ECALHit.h++"
#include "MACE/Simulation/Hit/ECALPMHit.h++"
#include "MACE/Simulation/Hit/TTCHit.h++"
#include "MACE/Simulation/Hit/TTCSiPMHit.h++"

#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Geant4X/Utility/ConvertGeometry.h++"
#include "Mustard/Parallel/ProcessSpecificPath.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::PhaseI::SimMACEPhaseI {

Analysis::Analysis() :
    AnalysisBase{this},
    fCoincidenceWithMRPC{true},
    fCoincidenceWithECAL{true},
    fSaveTTCHitData{true},
    fSaveTTCSiPMHitData{true},
    fPrimaryVertexOutput{},
    fDecayVertexOutput{},
    fMRPCSimHitOutput{},
    fECALSimHitOutput{},
    fECALPMHitOutput{},
    fPrimaryVertex{},
    fDecayVertex{},
    fMRPCHit{},
    fECALHit{},
    fECALPMHit{},
    fSciFiHit{},
    fSciFiSiPMHit{},
    fTTCSimHitOutput{},
    fTTCSiPMHitOutput{},
    fTTCHit{},
    fTTCSiPMHit{},
    fMessengerRegister{this} {}

auto Analysis::RunBeginUserAction(int runID) -> void {
    if (PrimaryGeneratorAction::Instance().SavePrimaryVertexData()) {
        fPrimaryVertexOutput.emplace(fmt::format("G4Run{}/SimPrimaryVertex", runID));
    }
    if (TrackingAction::Instance().SaveDecayVertexData()) {
        fDecayVertexOutput.emplace(fmt::format("G4Run{}/SimDecayVertex", runID));
    }
    if (fSaveTTCHitData) {
        fTTCSimHitOutput.emplace(fmt::format("G4Run{}/TTCSimHit", runID));
    }
    if (fSaveTTCSiPMHitData) {
        fTTCSiPMHitOutput.emplace(fmt::format("G4Run{}/TTCSiPMHit", runID));
    }
    fMRPCSimHitOutput.emplace(fmt::format("G4Run{}/MRPCSimHit", runID));
    fECALSimHitOutput.emplace(fmt::format("G4Run{}/ECALSimHit", runID));
    fECALPMHitOutput.emplace(fmt::format("G4Run{}/ECALPMHit", runID));
    fSciFiHitOutput.emplace(fmt::format("G4Run{}/SciFiHit", runID));
    fSciFiSiPMHitOutput.emplace(fmt::format("G4Run{}/SciFiSiPMHit", runID));
}

auto Analysis::EventEndUserAction() -> void {
    const auto mrpcPassed{not fCoincidenceWithMRPC or fMRPCHit == nullptr or not fMRPCHit->empty()};
    const auto ecalPassed{not fCoincidenceWithECAL or fECALHit == nullptr or not fECALHit->empty()};
    if (mrpcPassed and ecalPassed) {
        if (fPrimaryVertex and fPrimaryVertexOutput) {
            fPrimaryVertexOutput->Fill(*fPrimaryVertex);
        }
        if (fDecayVertex and fDecayVertexOutput) {
            fDecayVertexOutput->Fill(*fDecayVertex);
        }
        if (fMRPCHit) {
            fMRPCSimHitOutput->Fill(*fMRPCHit);
        }
        if (fECALHit) {
            fECALSimHitOutput->Fill(*fECALHit);
        }
        if (fECALPMHit) {
            fECALPMHitOutput->Fill(*fECALPMHit);
        }
        if (fSciFiHit) {
            fSciFiHitOutput->Fill(*fSciFiHit);
        }
        if (fSciFiSiPMHit) {
            fSciFiSiPMHitOutput->Fill(*fSciFiSiPMHit);
        }
        if (fTTCSimHitOutput) {
            fTTCSimHitOutput->Fill(*fTTCHit);
        }
        if (fTTCSiPMHitOutput) {
            fTTCSiPMHitOutput->Fill(*fTTCSiPMHit);
        }
    }
    fPrimaryVertex = {};
    fDecayVertex = {};
    fMRPCHit = {};
    fECALHit = {};
    fECALPMHit = {};
    fSciFiHit = {};
    fSciFiSiPMHit = {};
    fTTCHit = {};
    fTTCSiPMHit = {};
}

auto Analysis::RunEndUserAction(int) -> void {
    // write data
    if (fPrimaryVertexOutput) {
        fPrimaryVertexOutput->Write();
    }
    if (fDecayVertexOutput) {
        fDecayVertexOutput->Write();
    }
    if (fTTCSimHitOutput) {
        fTTCSimHitOutput->Write();
    }
    if (fTTCSiPMHitOutput) {
        fTTCSiPMHitOutput->Write();
    }
    fMRPCSimHitOutput->Write();
    fECALSimHitOutput->Write();
    fECALPMHitOutput->Write();
    fSciFiHitOutput->Write();
    fSciFiSiPMHitOutput->Write();
    // reset output
    fPrimaryVertexOutput.reset();
    fDecayVertexOutput.reset();
    fMRPCSimHitOutput.reset();
    fECALSimHitOutput.reset();
    fECALPMHitOutput.reset();
    fSciFiHitOutput.reset();
    fSciFiSiPMHitOutput.reset();
    fTTCSimHitOutput.reset();
    fTTCSiPMHitOutput.reset();
}

} // namespace MACE::PhaseI::SimMACEPhaseI
