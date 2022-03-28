namespace MACE::Reconstruction::ReconTracks::Tracker {

template<template<class H, class T> class FitterT_t, class SpectrometerHit_t, class Track_t>
void PerfectFinder<FitterT_t, SpectrometerHit_t, Track_t>::Reconstruct(const std::vector<HitPtr>& hitData) {
    this->fTrackList.clear();
    this->fTrackedHitList.clear();
    this->fOmittedHitList.clear();

    auto sortedHitData = LexicographicalSort(hitData);

    for (auto&& candidate : ClassifyToG4Tracks(sortedHitData)) {
        if (candidate.size() < fThreshold) {
            this->fOmittedHitList.insert(this->fOmittedHitList.cend(), candidate.cbegin(), candidate.cend());
            continue;
        }
        CutByLayerID(candidate);
        if (candidate.size() < fThreshold) {
            this->fOmittedHitList.insert(this->fOmittedHitList.cend(), candidate.cbegin(), candidate.cend());
            continue;
        }
        FitAndDumpToResult(candidate);
    }
}

template<template<class H, class T> class FitterT_t, class SpectrometerHit_t, class Track_t>
std::vector<typename PerfectFinder<FitterT_t, SpectrometerHit_t, Track_t>::HitPtr>
PerfectFinder<FitterT_t, SpectrometerHit_t, Track_t>::LexicographicalSort(std::vector<HitPtr> hitData) {
    std::ranges::sort(hitData,
                      [](const auto& hit1, const auto& hit2) {
                          return std::tie(hit1->GetG4EventID(), hit1->GetG4TrackID(), hit1->GetHitTime()) <
                                 std::tie(hit2->GetG4EventID(), hit2->GetG4TrackID(), hit2->GetHitTime());
                      });
    hitData.shrink_to_fit();
    return hitData;
}

template<template<class H, class T> class FitterT_t, class SpectrometerHit_t, class Track_t>
std::vector<std::vector<typename PerfectFinder<FitterT_t, SpectrometerHit_t, Track_t>::HitPtr>>
PerfectFinder<FitterT_t, SpectrometerHit_t, Track_t>::ClassifyToG4Tracks(const std::vector<HitPtr>& sortedHitData) const {
    std::vector<std::vector<HitPtr>> g4Tracks;
    g4Tracks.reserve(sortedHitData.size() / fThreshold);
    int currentEventID = -1;
    int currentTrackID = -1;
    std::vector<HitPtr>* currentTrack = nullptr;
    for (auto&& hit : sortedHitData) {
        if (hit->GetG4TrackID() > currentTrackID or hit->GetG4EventID() > currentEventID) {
            currentEventID = hit->GetG4EventID();
            currentTrackID = hit->GetG4TrackID();
            if (currentTrack != nullptr) [[likely]] { currentTrack->shrink_to_fit(); }
            currentTrack = std::addressof(g4Tracks.emplace_back());
            currentTrack->reserve(2 * fThreshold);
        }
        currentTrack->emplace_back(hit);
    }
    g4Tracks.shrink_to_fit();
    return g4Tracks;
}

template<template<class H, class T> class FitterT_t, class SpectrometerHit_t, class Track_t>
void PerfectFinder<FitterT_t, SpectrometerHit_t, Track_t>::CutByLayerID(std::vector<HitPtr>& g4Track) {
    const auto lastHitIter = std::prev(g4Track.cend());
    for (auto hitIter = g4Track.cbegin(); hitIter != lastHitIter; ++hitIter) {
        const auto& hit = *hitIter;
        const auto& nextHit = *std::next(hitIter);
        if (nextHit->GetLayerID() < hit->GetLayerID()) {
            this->fOmittedHitList.insert(this->fOmittedHitList.cend(), hitIter, g4Track.cend());
            g4Track.erase(hitIter, g4Track.cend());
            return;
        }
    }
}

template<template<class H, class T> class FitterT_t, class SpectrometerHit_t, class Track_t>
void PerfectFinder<FitterT_t, SpectrometerHit_t, Track_t>::FitAndDumpToResult(std::vector<HitPtr>& candidate) {
    auto track = std::make_shared<Track_t>();
    bool good = this->fFitter->Fit(candidate, *track);
    const auto& omitted = this->fFitter->GetOmitted();

    if (candidate.size() < fThreshold or not good) {
        this->fOmittedHitList.insert(this->fOmittedHitList.cend(), candidate.cbegin(), candidate.cend());
        this->fOmittedHitList.insert(this->fOmittedHitList.cend(), omitted.cbegin(), omitted.cend());
    } else {
        this->fTrackList.emplace_back(track);
        this->fTrackedHitList.emplace_back(candidate);
        this->fOmittedHitList.insert(this->fOmittedHitList.cend(), omitted.cbegin(), omitted.cend());
    }
}

} // namespace MACE::Reconstruction::ReconTracks::Tracker
