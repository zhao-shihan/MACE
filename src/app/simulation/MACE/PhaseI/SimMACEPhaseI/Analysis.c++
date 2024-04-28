#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/Geant4X/ConvertGeometry.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/PrimaryGeneratorAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/TrackingAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/Simulation/Hit/EMCHit.h++"
#include "MACE/Simulation/Hit/EMCPMTHit.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::PhaseI::SimMACEPhaseI {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimMACEPhaseI_untitled"},
    fFileMode{"NEW"},
    fCoincidenceWithEMC{true},
    fLastUsedFullFilePath{},
    fFile{},
    fPrimaryVertexOutput{},
    fDecayVertexOutput{},
    fEMCSimHitOutput{},
    fEMCPMTHitOutput{},
    fPrimaryVertex{},
    fDecayVertex{},
    fEMCHit{},
    fEMCPMTHit{},
    fMessengerRegister{this} {}

auto Analysis::RunBegin(G4int runID) -> void {
    // open ROOT file
    auto fullFilePath{MPIX::ParallelizePath(fFilePath).replace_extension(".root").generic_string()};
    const auto filePathChanged{fullFilePath != fLastUsedFullFilePath};
    fFile = TFile::Open(fullFilePath.c_str(), filePathChanged ? fFileMode.c_str() : "UPDATE",
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimMACEPhaseI::Analysis::RunBegin: Cannot open file '{}' with mode '{}'",
                                             fullFilePath, fFileMode)};
    }
    fLastUsedFullFilePath = std::move(fullFilePath);
    // save geometry
    if (filePathChanged and Env::MPIEnv::Instance().OnCommWorldMaster()) {
        Geant4X::ConvertGeometryToTMacro("SimMACEPhaseI_gdml", "SimMACEPhaseI.gdml")->Write();
    }
    // initialize outputs
    if (PrimaryGeneratorAction::Instance().SavePrimaryVertexData()) { fPrimaryVertexOutput.emplace(fmt::format("G4Run{}/SimPrimaryVertex", runID)); }
    if (TrackingAction::Instance().SaveDecayVertexData()) { fDecayVertexOutput.emplace(fmt::format("G4Run{}/SimDecayVertex", runID)); }
    fEMCSimHitOutput.emplace(fmt::format("G4Run{}/EMCSimHit", runID));
    fEMCPMTHitOutput.emplace(fmt::format("G4Run{}/EMCPMTHit", runID));
}

auto Analysis::EventEnd() -> void {
    const auto emcPassed{not fCoincidenceWithEMC or fEMCHit == nullptr or fEMCHit->size() > 0};
    if (emcPassed) {
        if (fPrimaryVertex and fPrimaryVertexOutput) { fPrimaryVertexOutput->Fill(*fPrimaryVertex); }
        if (fDecayVertex and fDecayVertexOutput) { fDecayVertexOutput->Fill(*fDecayVertex); }
        if (fEMCHit) { fEMCSimHitOutput->Fill(*fEMCHit); }
        if (fEMCPMTHit) { fEMCPMTHitOutput->Fill(*fEMCPMTHit); }
    }
    fPrimaryVertex = {};
    fDecayVertex = {};
    fEMCHit = {};
    fEMCPMTHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    // write data
    if (fPrimaryVertexOutput) { fPrimaryVertexOutput->Write(); }
    if (fDecayVertexOutput) { fDecayVertexOutput->Write(); }
    fEMCSimHitOutput->Write();
    fEMCPMTHitOutput->Write();
    // close file
    fFile->Close(option);
    delete fFile;
    // reset output
    fPrimaryVertexOutput.reset();
    fDecayVertexOutput.reset();
    fEMCSimHitOutput.reset();
    fEMCPMTHitOutput.reset();
}

} // namespace MACE::PhaseI::SimMACEPhaseI
