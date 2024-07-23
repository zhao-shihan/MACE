#include "MACE/SimDose/Action/SteppingAction.h++"
#include "MACE/SimDose/Analysis.h++"

#include "G4Step.hh"
#include "G4StepPoint.hh"

namespace MACE::SimDose::inline Action {

auto SteppingAction::UserSteppingAction(const G4Step* step) -> void {
    const auto post{step->GetPostStepPoint()};
    if (step->GetTotalEnergyDeposit() > 0 and post->GetMaterial()) {
        Analysis::Instance().FillMap(post->GetPosition(),
                                     step->GetTotalEnergyDeposit(),
                                     post->GetMaterial()->GetDensity());
    }
}

} // namespace MACE::SimDose::inline Action
