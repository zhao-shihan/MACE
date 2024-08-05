#pragma once

#include "MACE/Data/MMSTrack.h++"
#include "MACE/Reconstruction/MMSTracking/Finder/TruthFinder.h++"
#include "MACE/Simulation/Analysis/MMSTruthTrackerMessenger.h++"
#include "MACE/Simulation/Hit/CDCHit.h++"
#include "MACE/Simulation/Hit/TTCHit.h++"

#include "Mustard/Data/Tuple.h++"

#include "G4ThreeVector.hh"

#include "muc/math"

#include "gsl/gsl"

#include <algorithm>
#include <iterator>
#include <memory>
#include <ranges>
#include <vector>

namespace MACE::inline Simulation::Analysis {

class MMSTruthTracker {
public:
    MMSTruthTracker();

    auto MinNCDCHitForQualifiedTrack(int n) -> void { fTrackFinder.NHitThreshold(std::max(1, n)); }
    auto MinNTTCHitForQualifiedTrack(int n) -> void { fMinNTTCHitForQualifiedTrack = std::max(1, n); }

    auto operator()(const std::vector<gsl::owner<CDCHit*>>& cdcHitHC,
                    const std::vector<gsl::owner<TTCHit*>>& ttcHitHC) -> std::vector<std::shared_ptr<Mustard::Data::Tuple<Data::MMSSimTrack>>>;

private:
    int fMinNTTCHitForQualifiedTrack;

    MMSTracking::TruthFinder<> fTrackFinder;

    MMSTruthTrackerMessenger::Register<MMSTruthTracker> fMessengerRegister;
};

} // namespace MACE::inline Simulation::Analysis
