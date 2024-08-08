#include "MACE/SimECal/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimECal/Action/TrackingAction.h++"
#include "MACE/SimECal/Analysis.h++"
#include "MACE/Simulation/Hit/ECalHit.h++"
#include "MACE/Simulation/Hit/ECalPMTHit.h++"
#include "MACE/Simulation/Hit/MCPHit.h++"

#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/Geant4X/Utility/ConvertGeometry.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::SimECal {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimECal_untitled"},
    fFileMode{"NEW"},
    fCoincidenceWithECal{true},
    fCoincidenceWithMCP{false},
    fLastUsedFullFilePath{},
    fFile{},
    fPrimaryVertexOutput{},
    fDecayVertexOutput{},
    fECalSimHitOutput{},
    fECalPMTHitOutput{},
    fMCPSimHitOutput{},
    fPrimaryVertex{},
    fDecayVertex{},
    fECalHit{},
    fECalPMTHit{},
    fMCPHit{},
    fMessengerRegister{this} {}

auto Analysis::RunBegin(G4int runID) -> void {
    // open ROOT file
    auto fullFilePath{Mustard::MPIX::ParallelizePath(fFilePath).replace_extension(".root").generic_string()};
    const auto filePathChanged{fullFilePath != fLastUsedFullFilePath};
    fFile = TFile::Open(fullFilePath.c_str(), filePathChanged ? fFileMode.c_str() : "UPDATE",
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimECal::Analysis::RunBegin: Cannot open file '{}' with mode '{}'",
                                             fullFilePath, fFileMode)};
    }
    fLastUsedFullFilePath = std::move(fullFilePath);
    // save geometry
    if (filePathChanged and Mustard::Env::MPIEnv::Instance().OnCommWorldMaster()) {
        Mustard::Geant4X::ConvertGeometryToTMacro("SimECal_gdml", "SimECal.gdml")->Write();
    }
    // initialize outputs
    if (PrimaryGeneratorAction::Instance().SavePrimaryVertexData()) { fPrimaryVertexOutput.emplace(fmt::format("G4Run{}/SimPrimaryVertex", runID)); }
    if (TrackingAction::Instance().SaveDecayVertexData()) { fDecayVertexOutput.emplace(fmt::format("G4Run{}/SimDecayVertex", runID)); }
    fECalSimHitOutput.emplace(fmt::format("G4Run{}/ECalSimHit", runID));
    fECalPMTHitOutput.emplace(fmt::format("G4Run{}/ECalPMTHit", runID));
    fMCPSimHitOutput.emplace(fmt::format("G4Run{}/MCPSimHit", runID));
}

auto Analysis::EventEnd() -> void {
    const auto eCalPassed{not fCoincidenceWithECal or fECalHit == nullptr or fECalHit->size() > 0};
    const auto mcpPassed{not fCoincidenceWithMCP or fMCPHit == nullptr or fMCPHit->size() > 0};
    if (eCalPassed and mcpPassed) {
        if (fPrimaryVertex and fPrimaryVertexOutput) { fPrimaryVertexOutput->Fill(*fPrimaryVertex); }
        if (fDecayVertex and fDecayVertexOutput) { fDecayVertexOutput->Fill(*fDecayVertex); }
        if (fECalHit) { fECalSimHitOutput->Fill(*fECalHit); }
        if (fECalPMTHit) { fECalPMTHitOutput->Fill(*fECalPMTHit); }
        if (fMCPHit) { fMCPSimHitOutput->Fill(*fMCPHit); }
    }
    fPrimaryVertex = {};
    fDecayVertex = {};
    fECalHit = {};
    fECalPMTHit = {};
    fMCPHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    // write data
    if (fPrimaryVertexOutput) { fPrimaryVertexOutput->Write(); }
    if (fDecayVertexOutput) { fDecayVertexOutput->Write(); }
    fECalSimHitOutput->Write();
    fECalPMTHitOutput->Write();
    fMCPSimHitOutput->Write();
    // close file
    fFile->Close(option);
    delete fFile;
    // reset output
    fPrimaryVertexOutput.reset();
    fDecayVertexOutput.reset();
    fECalSimHitOutput.reset();
    fECalPMTHitOutput.reset();
    fMCPSimHitOutput.reset();
}

} // namespace MACE::SimECal
