#include "MACE/SimDose/Action/SteppingAction.h++"
#include "MACE/SimDose/Analysis.h++"

#include "G4Step.hh"
#include "G4StepPoint.hh"

namespace MACE::SimDose::inline Action {

auto SteppingAction::UserSteppingAction(const G4Step* step) -> void {
    if (step->GetTotalEnergyDeposit() > 0) {
        Analysis::Instance().FillMap(step->GetPostStepPoint()->GetPosition(),
                                     step->GetTotalEnergyDeposit(),
                                     step->GetPreStepPoint()->GetMaterial()->GetDensity());
    }
}

} // namespace MACE::SimDose::inline Action
