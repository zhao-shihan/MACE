#include "MACE/SimVeto/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimVeto/Analysis.h++"
#include "MACE/Simulation/Hit/VetoHit.h++"
#include "MACE/Simulation/Hit/VetoPMHit.h++"

#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Geant4X/Utility/ConvertGeometry.h++"
#include "Mustard/Parallel/ProcessSpecificPath.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/core.h"

#include <algorithm>
#include <optional>
#include <stdexcept>
namespace MACE::SimVeto {
Analysis::Analysis() :
    AnalysisBase{this},
    // fFilePath{"SimVeto_untiled"},
    // fFileMode{"NEW"},
    fCoincidenceWithVeto{true},
    // fLastUsedFullFilePath{},
    // fFile{},
    fPrimaryVertexOutput{},
    // fDecayVertexOutput{},
    fVetoSimHitOutput{},
    fVetoPMHitOutput{},
    fPrimaryVertex{},
    // fDecayVertex{},
    fVetoHit{},
    fVetoPMHit{},
    fMessengerRegister{this} {}

auto Analysis::RunBeginUserAction(int runID) -> void {
    if (PrimaryGeneratorAction::Instance().SavePrimaryVertexData()) {
        fPrimaryVertexOutput.emplace(fmt::format("G4Run{}/SimPrimaryVertex", runID));
    }
    // if (TrackingAction::Instance().SaveDecayVertexData()) { fDecayVertexOutput.emplace(fmt::format("G4Run{}/SimDecayVertex", runID)); }
    fVetoSimHitOutput.emplace(fmt::format("G4Run{}/VetoSimHit", runID));
    fVetoPMHitOutput.emplace(fmt::format("G4Run{}/VetoPMHit", runID));
}

auto Analysis::EventEndUserAction() -> void {
    const auto vetoPassed{not fCoincidenceWithVeto or fVetoHit == nullptr or fVetoHit->size() > 0};
    if (vetoPassed) {
        if (fPrimaryVertex and fPrimaryVertexOutput) {
            fPrimaryVertexOutput->Fill(*fPrimaryVertex);
        }
        // if (fDecayVertex and fDecayVertexOutput) {
        //     fDecayVertexOutput->Fill(*fDecayVertex);
        // }
        if (fVetoHit) {
            fVetoSimHitOutput->Fill(*fVetoHit);
        }
        if (fVetoPMHit) {
            fVetoPMHitOutput->Fill(*fVetoPMHit);
        }
    }
    fPrimaryVertex = {};
    // fDecayVertex = {};
    fVetoHit = {};
    fVetoPMHit = {};
}

auto Analysis::RunEndUserAction(int) -> void {
    // write data
    if (fPrimaryVertexOutput) {
        fPrimaryVertexOutput->Write();
    }
    // if (fDecayVertexOutput) {
    //     fDecayVertexOutput->Write();
    // }
    if (fVetoSimHitOutput) {
        fVetoSimHitOutput->Write();
    }
    if (fVetoPMHitOutput) {
        fVetoPMHitOutput->Write();
    }
    // reset output
    fPrimaryVertexOutput.reset();
    // fDecayVertexOutput.reset();
    fVetoSimHitOutput.reset();
    fVetoPMHitOutput.reset();
}

} // namespace MACE::SimVeto