#pragma once

#include "DataModel/Hit/CDCHit.hxx"
#include "DataModel/Track/IsTrack.hxx"
#include "VerboseLevel.hxx"

namespace MACE::Reconstruction::ReconTracks {

using Core::DataModel::Hit::IsSpectormeterHit;
using Core::DataModel::Track::IsTrack;
using Utility::VerboseLevel;

template<IsSpectormeterHit Hit_t, IsTrack Track_t>
class ITrackFitter {
protected:
    using HitPtr = std::shared_ptr<Hit_t>;
    using HitVector = std::vector<HitPtr>;

public:
    struct FittingResult {
        bool success;
        HitVector omittedHits;
    };

public:
    ITrackFitter(VerboseLevel verbose = kWarning);
    ITrackFitter(const ITrackFitter&) = delete;
    ITrackFitter& operator=(const ITrackFitter&) = delete;
    virtual ~ITrackFitter() noexcept = default;

    void SetVerbose(VerboseLevel verbose) { fVerbose = verbose; }

    /// @brief Do track fitting.
    /// @param hits Hits that fitting to be manipulated on.
    /// @param seed Tracking parameters seed. Optional for some fitting algorithrm.
    /// @return [fit was successful, omitted hits], see struct FittingResult for detail.
    virtual FittingResult Fit(HitVector& hits, Track_t& seed) = 0;

protected:
    VerboseLevel fVerbose;
};

} // namespace MACE::Reconstruction::ReconTracks

#include "ReconTracks/Interface/ITrackFitter.ixx"
