#include "MACE/PhaseI/SimMACEPhaseI/Action/PrimaryGeneratorAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/TrackingAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/Simulation/Hit/ECalHit.h++"
#include "MACE/Simulation/Hit/ECalPMTHit.h++"

#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/Geant4X/Utility/ConvertGeometry.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::PhaseI::SimMACEPhaseI {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimMACEPhaseI_untitled"},
    fFileMode{"NEW"},
    fCoincidenceWithECal{true},
    fLastUsedFullFilePath{},
    fFile{},
    fPrimaryVertexOutput{},
    fDecayVertexOutput{},
    fECalSimHitOutput{},
    fECalPMTHitOutput{},
    fPrimaryVertex{},
    fDecayVertex{},
    fECalHit{},
    fECalPMTHit{},
    fMessengerRegister{this} {}

auto Analysis::RunBegin(G4int runID) -> void {
    // open ROOT file
    auto fullFilePath{Mustard::MPIX::ParallelizePath(fFilePath).replace_extension(".root").generic_string()};
    const auto filePathChanged{fullFilePath != fLastUsedFullFilePath};
    fFile = TFile::Open(fullFilePath.c_str(), filePathChanged ? fFileMode.c_str() : "UPDATE",
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimMACEPhaseI::Analysis::RunBegin: Cannot open file '{}' with mode '{}'",
                                             fullFilePath, fFileMode)};
    }
    fLastUsedFullFilePath = std::move(fullFilePath);
    // save geometry
    if (filePathChanged and Mustard::Env::MPIEnv::Instance().OnCommWorldMaster()) {
        Mustard::Geant4X::ConvertGeometryToTMacro("SimMACEPhaseI_gdml", "SimMACEPhaseI.gdml")->Write();
    }
    // initialize outputs
    if (PrimaryGeneratorAction::Instance().SavePrimaryVertexData()) { fPrimaryVertexOutput.emplace(fmt::format("G4Run{}/SimPrimaryVertex", runID)); }
    if (TrackingAction::Instance().SaveDecayVertexData()) { fDecayVertexOutput.emplace(fmt::format("G4Run{}/SimDecayVertex", runID)); }
    fECalSimHitOutput.emplace(fmt::format("G4Run{}/ECalSimHit", runID));
    fECalPMTHitOutput.emplace(fmt::format("G4Run{}/ECalPMTHit", runID));
}

auto Analysis::EventEnd() -> void {
    const auto eCalPassed{not fCoincidenceWithECal or fECalHit == nullptr or fECalHit->size() > 0};
    if (eCalPassed) {
        if (fPrimaryVertex and fPrimaryVertexOutput) { fPrimaryVertexOutput->Fill(*fPrimaryVertex); }
        if (fDecayVertex and fDecayVertexOutput) { fDecayVertexOutput->Fill(*fDecayVertex); }
        if (fECalHit) { fECalSimHitOutput->Fill(*fECalHit); }
        if (fECalPMTHit) { fECalPMTHitOutput->Fill(*fECalPMTHit); }
    }
    fPrimaryVertex = {};
    fDecayVertex = {};
    fECalHit = {};
    fECalPMTHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    // write data
    if (fPrimaryVertexOutput) { fPrimaryVertexOutput->Write(); }
    if (fDecayVertexOutput) { fDecayVertexOutput->Write(); }
    fECalSimHitOutput->Write();
    fECalPMTHitOutput->Write();
    // close file
    fFile->Close(option);
    delete fFile;
    // reset output
    fPrimaryVertexOutput.reset();
    fDecayVertexOutput.reset();
    fECalSimHitOutput.reset();
    fECalPMTHitOutput.reset();
}

} // namespace MACE::PhaseI::SimMACEPhaseI
