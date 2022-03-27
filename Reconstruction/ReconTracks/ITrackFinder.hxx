#pragma once

#include "DataModel/Hit/SpectrometerHit.hxx"
#include "DataModel/Track/IsTrack.hxx"
#include "VerboseLevel.hxx"

namespace MACE::Reconstruction::ReconTracks {

using Core::DataModel::Hit::IsSpectormeterHit;
using Core::DataModel::Track::IsTrack;
using Utility::VerboseLevel;

template<IsSpectormeterHit Hit_t, IsTrack Track_t>
class ITrackFinder {
protected:
    using HitPtr = std::shared_ptr<Hit_t>;
    using HitVector = std::vector<HitPtr>;
    using TrackPtr = std::shared_ptr<Track_t>;
    using TrackVector = std::vector<TrackPtr>;

public:
    /// @brief Return type of Find().
    struct FindingResult {
        struct TrackFound {
            HitVector hits;
            TrackPtr seed;
        };
        std::vector<TrackFound> tracksFound;
        HitVector omittedHits;
    };

public:
    ITrackFinder(VerboseLevel verbose = kWarning);
    ITrackFinder(const ITrackFinder&) = delete;
    ITrackFinder& operator=(const ITrackFinder&) = delete;
    virtual ~ITrackFinder() noexcept = default;

    void SetVerbose(VerboseLevel verbose) { fVerbose = verbose; }

    /// @brief Do track finding.
    /// @param hitData Hits data that track finding to be manipulated on.
    /// @return [tracks found, omitted hits], in which <tracks found> contains elements of type TrackFound,
    /// which contains hits found in this track and tracking parameters seed. See struct FindingResult for detail.
    virtual FindingResult Find(const HitVector& hitData) = 0;

protected:
    VerboseLevel fVerbose;
};

} // namespace MACE::Reconstruction::ReconTracks

#include "ReconTracks/Interface/ITrackFinder.ixx"
