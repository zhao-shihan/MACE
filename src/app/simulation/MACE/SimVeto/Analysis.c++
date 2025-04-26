#include "MACE/SimVeto/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimVeto/Analysis.h++"
#include "MACE/Simulation/Hit/VetoPMHit.h++"
#include "MACE/Simulation/Hit/VetoHit.h++"

#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/Geant4X/Utility/ConvertGeometry.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"
#include "Mustard/Utility/PrettyLog.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/core.h"

#include <algorithm>
#include <stdexcept>
namespace MACE::SimVeto{
Analysis::Analysis():
    PassiveSingleton{this},
    fFilePath{"SimVeto_untiled"},
    fFileMode{"NEW"},
    fCoincidenceWithVeto{true},
    fLastUsedFullFilePath{},
    fFile{},
    fPrimaryVertexOutput{},
    fDecayVertexOutput{},
    fVetoSimHitOutput{},
    fVetoPMHitOutput{},
    fPrimaryVertex{},
    fDecayVertex{},
    fVetoHit{},
    fVetoPMHit{},
    fMessengerRegister{this}
    {}

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
        Mustard::Geant4X::ConvertGeometryToTMacro("SimVeto_gdml", "SimVeto.gdml")->Write();
    }
    // initialize outputs
    if (PrimaryGeneratorAction::Instance().SavePrimaryVertexData()) { fPrimaryVertexOutput.emplace(fmt::format("G4Run{}/SimPrimaryVertex", runID)); }
    // if (TrackingAction::Instance().SaveDecayVertexData()) { fDecayVertexOutput.emplace(fmt::format("G4Run{}/SimDecayVertex", runID)); }
    fVetoSimHitOutput.emplace(fmt::format("G4Run{}/VetoSimHit", runID));
    fVetoPMHitOutput.emplace(fmt::format("G4Run{}/VetoPMHit", runID));
}

auto Analysis::EventEnd() -> void {
    const auto vetoPassed{not fCoincidenceWithVeto or fVetoHit == nullptr or fVetoHit->size() > 0};
    if(vetoPassed){
        if (fPrimaryVertex and fPrimaryVertexOutput) { fPrimaryVertexOutput->Fill(*fPrimaryVertex); }
        if (fDecayVertex and fDecayVertexOutput) { fDecayVertexOutput->Fill(*fDecayVertex); }
        if (fVetoHit) { fVetoSimHitOutput->Fill(*fVetoHit); }
        if (fVetoPMHit) { fVetoPMHitOutput->Fill(*fVetoPMHit); }
    }
    fPrimaryVertex = {};
    fDecayVertex = {};
    fVetoHit = {};
    fVetoPMHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    // write data
    if (fPrimaryVertexOutput) { fPrimaryVertexOutput->Write(); }
    if (fDecayVertexOutput) { fDecayVertexOutput->Write(); }
    fVetoSimHitOutput->Write();
    fVetoPMHitOutput->Write();
    // close file
    fFile->Close(option);
    delete fFile;
    // reset output
    fPrimaryVertexOutput.reset();
    fDecayVertexOutput.reset();
    fVetoSimHitOutput.reset();
    fVetoPMHitOutput.reset();
}

} // namespace MACE::SimVeto