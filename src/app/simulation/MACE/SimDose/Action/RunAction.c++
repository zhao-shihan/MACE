#include "MACE/SimDose/Action/RunAction.h++"
#include "MACE/SimDose/Analysis.h++"

#include "G4RegionStore.hh"
#include "G4Run.hh"

#include <algorithm>

namespace MACE::SimDose::inline Action {

auto RunAction::BeginOfRunAction(const G4Run* run) -> void {
    // Apply/update step limit
    const auto& analysis{Analysis::Instance()};
    const auto stepMax{0.3 * std::min({analysis.MapDeltaX(), analysis.MapDeltaY(), analysis.MapDeltaZ()})};
    fStepLimit.SetMaxAllowedStep(stepMax);
    G4RegionStore::GetInstance()->GetRegion("DefaultRegionForTheWorld")->SetUserLimits(&fStepLimit);
    // Analysis action
    Analysis::Instance().RunBeginAction(run->GetRunID());
}

auto RunAction::EndOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunEndAction(run->GetRunID());
}

} // namespace MACE::SimDose::inline Action
