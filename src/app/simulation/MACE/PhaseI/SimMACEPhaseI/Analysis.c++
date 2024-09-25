#include "MACE/PhaseI/SimMACEPhaseI/Action/PrimaryGeneratorAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/TrackingAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/Simulation/Hit/ECALHit.h++"
#include "MACE/Simulation/Hit/ECALPMTHit.h++"

#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/Geant4X/Utility/ConvertGeometry.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"
#include "Mustard/Utility/PrettyLog.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::PhaseI::SimMACEPhaseI {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimMACEPhaseI_untitled"},
    fFileMode{"NEW"},
    fCoincidenceWithECAL{true},
    fLastUsedFullFilePath{},
    fFile{},
    fPrimaryVertexOutput{},
    fDecayVertexOutput{},
    fECALSimHitOutput{},
    fECALPMTHitOutput{},
    fPrimaryVertex{},
    fDecayVertex{},
    fECALHit{},
    fECALPMTHit{},
    fMessengerRegister{this} {}

auto Analysis::RunBegin(G4int runID) -> void {
    // open ROOT file
    auto fullFilePath{Mustard::MPIX::ParallelizePath(fFilePath).replace_extension(".root").generic_string()};
    const auto filePathChanged{fullFilePath != fLastUsedFullFilePath};
    fFile = TFile::Open(fullFilePath.c_str(), filePathChanged ? fFileMode.c_str() : "UPDATE",
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{Mustard::PrettyException(fmt::format("Cannot open file '{}' with mode '{}'", fullFilePath, fFileMode))};
    }
    fLastUsedFullFilePath = std::move(fullFilePath);
    // save geometry
    if (filePathChanged and Mustard::Env::MPIEnv::Instance().OnCommWorldMaster()) {
        Mustard::Geant4X::ConvertGeometryToTMacro("SimMACEPhaseI_gdml", "SimMACEPhaseI.gdml")->Write();
    }
    // initialize outputs
    if (PrimaryGeneratorAction::Instance().SavePrimaryVertexData()) { fPrimaryVertexOutput.emplace(fmt::format("G4Run{}/SimPrimaryVertex", runID)); }
    if (TrackingAction::Instance().SaveDecayVertexData()) { fDecayVertexOutput.emplace(fmt::format("G4Run{}/SimDecayVertex", runID)); }
    fECALSimHitOutput.emplace(fmt::format("G4Run{}/ECALSimHit", runID));
    fECALPMTHitOutput.emplace(fmt::format("G4Run{}/ECALPMTHit", runID));
}

auto Analysis::EventEnd() -> void {
    const auto ecalPassed{not fCoincidenceWithECAL or fECALHit == nullptr or fECALHit->size() > 0};
    if (ecalPassed) {
        if (fPrimaryVertex and fPrimaryVertexOutput) { fPrimaryVertexOutput->Fill(*fPrimaryVertex); }
        if (fDecayVertex and fDecayVertexOutput) { fDecayVertexOutput->Fill(*fDecayVertex); }
        if (fECALHit) { fECALSimHitOutput->Fill(*fECALHit); }
        if (fECALPMTHit) { fECALPMTHitOutput->Fill(*fECALPMTHit); }
    }
    fPrimaryVertex = {};
    fDecayVertex = {};
    fECALHit = {};
    fECALPMTHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    // write data
    if (fPrimaryVertexOutput) { fPrimaryVertexOutput->Write(); }
    if (fDecayVertexOutput) { fDecayVertexOutput->Write(); }
    fECALSimHitOutput->Write();
    fECALPMTHitOutput->Write();
    // close file
    fFile->Close(option);
    delete fFile;
    // reset output
    fPrimaryVertexOutput.reset();
    fDecayVertexOutput.reset();
    fECALSimHitOutput.reset();
    fECALPMTHitOutput.reset();
}

} // namespace MACE::PhaseI::SimMACEPhaseI
