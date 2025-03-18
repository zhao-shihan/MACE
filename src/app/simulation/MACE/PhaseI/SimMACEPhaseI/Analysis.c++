#include "MACE/PhaseI/SimMACEPhaseI/Action/PrimaryGeneratorAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/TrackingAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/Simulation/Hit/ECALHit.h++"
#include "MACE/Simulation/Hit/ECALPMHit.h++"
#include "MACE/Simulation/Hit/MRPCHit.h++"

#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/Geant4X/Utility/ConvertGeometry.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::PhaseI::SimMACEPhaseI {

Analysis::Analysis() :
    AnalysisBase{this},
    fCoincidenceWithMRPC{true},
    fCoincidenceWithECAL{true},
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
    fMessengerRegister{this} {}

auto Analysis::RunBeginUserAction(int runID) -> void {
    if (PrimaryGeneratorAction::Instance().SavePrimaryVertexData()) { fPrimaryVertexOutput.emplace(fmt::format("G4Run{}/SimPrimaryVertex", runID)); }
    if (TrackingAction::Instance().SaveDecayVertexData()) { fDecayVertexOutput.emplace(fmt::format("G4Run{}/SimDecayVertex", runID)); }
    fMRPCSimHitOutput.emplace(fmt::format("G4Run{}/MRPCSimHit", runID));
    fECALSimHitOutput.emplace(fmt::format("G4Run{}/ECALSimHit", runID));
    fECALPMHitOutput.emplace(fmt::format("G4Run{}/ECALPMHit", runID));
}

auto Analysis::EventEndUserAction() -> void {
    const auto mrpcPassed{not fCoincidenceWithMRPC or fMRPCHit == nullptr or fMRPCHit->size() > 0};
    const auto ecalPassed{not fCoincidenceWithECAL or fECALHit == nullptr or fECALHit->size() > 0};
    if (mrpcPassed and ecalPassed) {
        if (fPrimaryVertex and fPrimaryVertexOutput) { fPrimaryVertexOutput->Fill(*fPrimaryVertex); }
        if (fDecayVertex and fDecayVertexOutput) { fDecayVertexOutput->Fill(*fDecayVertex); }
        if (fMRPCHit) { fMRPCSimHitOutput->Fill(*fMRPCHit); }
        if (fECALHit) { fECALSimHitOutput->Fill(*fECALHit); }
        if (fECALPMHit) { fECALPMHitOutput->Fill(*fECALPMHit); }
    }
    fPrimaryVertex = {};
    fDecayVertex = {};
    fMRPCHit = {};
    fECALHit = {};
    fECALPMHit = {};
}

auto Analysis::RunEndUserAction(int) -> void {
    // write data
    if (fPrimaryVertexOutput) { fPrimaryVertexOutput->Write(); }
    if (fDecayVertexOutput) { fDecayVertexOutput->Write(); }
    fMRPCSimHitOutput->Write();
    fECALSimHitOutput->Write();
    fECALPMHitOutput->Write();
    // reset output
    fPrimaryVertexOutput.reset();
    fDecayVertexOutput.reset();
    fMRPCSimHitOutput.reset();
    fECALSimHitOutput.reset();
    fECALPMHitOutput.reset();
}

} // namespace MACE::PhaseI::SimMACEPhaseI
