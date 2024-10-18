#include "MACE/SimECAL/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimECAL/Action/TrackingAction.h++"
#include "MACE/SimECAL/Analysis.h++"
#include "MACE/Simulation/Hit/ECALHit.h++"
#include "MACE/Simulation/Hit/ECALSensorHit.h++"
#include "MACE/Simulation/Hit/MCPHit.h++"

#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/Geant4X/Utility/ConvertGeometry.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"
#include "Mustard/Utility/PrettyLog.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/core.h"

#include <algorithm>
#include <stdexcept>

namespace MACE::SimECAL {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimECAL_untitled"},
    fFileMode{"NEW"},
    fCoincidenceWithECAL{true},
    fCoincidenceWithMCP{false},
    fLastUsedFullFilePath{},
    fFile{},
    fPrimaryVertexOutput{},
    fDecayVertexOutput{},
    fECALSimHitOutput{},
    fECALSensorHitOutput{},
    fMCPSimHitOutput{},
    fPrimaryVertex{},
    fDecayVertex{},
    fECALHit{},
    fECALSensorHit{},
    fMCPHit{},
    fMessengerRegister{this} {}

auto Analysis::RunBegin(G4int runID) -> void {
    // open ROOT file
    auto fullFilePath{Mustard::MPIX::ParallelizePath(fFilePath).replace_extension(".root").generic_string()};
    const auto filePathChanged{fullFilePath != fLastUsedFullFilePath};
    fFile = TFile::Open(fullFilePath.c_str(), filePathChanged ? fFileMode.c_str() : "UPDATE",
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{Mustard::PrettyException(fmt::format("Cannot open file '{}' with mode '{}'",
                                                                      fullFilePath, fFileMode))};
    }
    fLastUsedFullFilePath = std::move(fullFilePath);
    // save geometry
    if (filePathChanged and Mustard::Env::MPIEnv::Instance().OnCommWorldMaster()) {
        Mustard::Geant4X::ConvertGeometryToTMacro("SimECAL_gdml", "SimECAL.gdml")->Write();
    }
    // initialize outputs
    if (PrimaryGeneratorAction::Instance().SavePrimaryVertexData()) { fPrimaryVertexOutput.emplace(fmt::format("G4Run{}/SimPrimaryVertex", runID)); }
    if (TrackingAction::Instance().SaveDecayVertexData()) { fDecayVertexOutput.emplace(fmt::format("G4Run{}/SimDecayVertex", runID)); }
    fECALSimHitOutput.emplace(fmt::format("G4Run{}/ECALSimHit", runID));
    fECALSensorHitOutput.emplace(fmt::format("G4Run{}/ECALSensorHit", runID));
    fMCPSimHitOutput.emplace(fmt::format("G4Run{}/MCPSimHit", runID));
}

auto Analysis::EventEnd() -> void {
    const auto ecalPassed{not fCoincidenceWithECAL or fECALHit == nullptr or fECALHit->size() > 0};
    const auto mcpPassed{not fCoincidenceWithMCP or fMCPHit == nullptr or std::ranges::any_of(*fMCPHit, [](auto&& hit) { return Get<"Trig">(*hit); })};
    if (ecalPassed and mcpPassed) {
        if (fPrimaryVertex and fPrimaryVertexOutput) { fPrimaryVertexOutput->Fill(*fPrimaryVertex); }
        if (fDecayVertex and fDecayVertexOutput) { fDecayVertexOutput->Fill(*fDecayVertex); }
        if (fECALHit) { fECALSimHitOutput->Fill(*fECALHit); }
        if (fECALSensorHit) { fECALSensorHitOutput->Fill(*fECALSensorHit); }
        if (fMCPHit) { fMCPSimHitOutput->Fill(*fMCPHit); }
    }
    fPrimaryVertex = {};
    fDecayVertex = {};
    fECALHit = {};
    fECALSensorHit = {};
    fMCPHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    // write data
    if (fPrimaryVertexOutput) { fPrimaryVertexOutput->Write(); }
    if (fDecayVertexOutput) { fDecayVertexOutput->Write(); }
    fECALSimHitOutput->Write();
    fECALSensorHitOutput->Write();
    fMCPSimHitOutput->Write();
    // close file
    fFile->Close(option);
    delete fFile;
    // reset output
    fPrimaryVertexOutput.reset();
    fDecayVertexOutput.reset();
    fECALSimHitOutput.reset();
    fECALSensorHitOutput.reset();
    fMCPSimHitOutput.reset();
}

} // namespace MACE::SimECAL
