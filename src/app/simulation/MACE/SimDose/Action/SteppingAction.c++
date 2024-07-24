#include "MACE/SimDose/Action/SteppingAction.h++"
#include "MACE/SimDose/Analysis.h++"

#include "G4Step.hh"
#include "G4StepPoint.hh"

namespace MACE::SimDose::inline Action {

auto SteppingAction::UserSteppingAction(const G4Step* step) -> void {
    Analysis::Instance().FillMap(*step);
}

} // namespace MACE::SimDose::inline Action
