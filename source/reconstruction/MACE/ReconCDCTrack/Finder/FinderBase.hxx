#pragma once

#include "MACE/DataModel/Hit/CDCHit.hxx"
#include "MACE/DataModel/Track/CDCPhysicsTrack.hxx"
#include "MACE/Env/VerboseLevel.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include <concepts>
#include <memory>
#include <vector>

namespace MACE::ReconCDCTrack::inline Finder {

template<std::derived_from<DataModel::CDCHit> AHit,
         std::derived_from<DataModel::CDCPhysicsTrack> ATrack>
class FinderBase : public NonMoveableBase {
public:
    constexpr FinderBase(Env::VerboseLevel verboseLevel = Env::VerboseLevel::Warning);

protected:
    constexpr ~FinderBase() = default;

public:
    constexpr void VerboseLevel(Env::VerboseLevel v) { fVerboseLevel = v; }
    constexpr auto VerboseLevel() { return fVerboseLevel; }

public:
    /// @brief Return type of Find().
    template<std::derived_from<AHit> AReturnedHit,
             std::derived_from<ATrack> AReturnedTrack>
    struct FinderResult {
        struct TrackFound {
            std::vector<std::shared_ptr<AReturnedHit>> hits;
            std::shared_ptr<AReturnedTrack> seed;
        };
        std::vector<TrackFound> tracks;
        std::vector<std::shared_ptr<AReturnedHit>> omittedHits;
    };

    template<std::derived_from<AHit> AReturnedHit,
             std::derived_from<ATrack> AReturnedTrack>
    constexpr FinderResult<AReturnedHit, AReturnedTrack> Find();

private:
    constexpr virtual FinderResult<AHit, ATrack> FindImpl() = 0;

private:
    Env::VerboseLevel fVerboseLevel;
};

} // namespace MACE::ReconCDCTrack::inline Finder

#include "MACE/ReconCDCTrack/Finder/FinderBase.inl"
