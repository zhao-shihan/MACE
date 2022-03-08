template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t>
void MACE::ReconTracks::Tracker::TrueFinder<FitterT_t, SpectromrterHit_t, Track_t>::
Reconstruct(const std::vector<HitPtr>& hitData) {
    this->fTrackList.clear();
    this->fTrackedHitList.clear();
    this->fOmittedHitList.clear();

    for (auto&& candidate : Classify(hitData)) {
        if (candidate.size() < fThreshold) {
            this->fOmittedHitList.insert(this->fOmittedHitList.cend(), candidate.cbegin(), candidate.cend());
            continue;
        }

        auto track = std::make_shared<Track_t>();
        bool good = this->fFitter->Fit(candidate, *track);
        const auto& omitted = this->fFitter->GetOmitted();

        if (candidate.size() < fThreshold or !good) {
            this->fOmittedHitList.insert(this->fOmittedHitList.cend(), candidate.cbegin(), candidate.cend());
            this->fOmittedHitList.insert(this->fOmittedHitList.cend(), omitted.cbegin(), omitted.cend());
        } else {
            this->fTrackList.emplace_back(track);
            this->fTrackedHitList.emplace_back(candidate);
            this->fOmittedHitList.insert(this->fOmittedHitList.cend(), omitted.cbegin(), omitted.cend());
        }
    }
}

template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t>
std::vector<std::vector<typename MACE::ReconTracks::Tracker::TrueFinder<FitterT_t, SpectromrterHit_t, Track_t>::HitPtr>>
MACE::ReconTracks::Tracker::TrueFinder<FitterT_t, SpectromrterHit_t, Track_t>::
Classify(const std::vector<HitPtr>& hitData) {
    std::vector<HitPtr> sortedHitData(hitData);
    std::ranges::sort(sortedHitData,
        [](const auto& hit1, const auto& hit2) {
            return std::tie(hit1->GetEventID(), hit1->GetTrackID()) < std::tie(hit2->GetEventID(), hit2->GetTrackID());
        }
    );

    std::vector<std::vector<HitPtr>> candidates;
    int currentTrackID = -1;
    int currentEventID = -1;
    std::vector<HitPtr>* currentTrack = nullptr;
    for (auto&& hit : std::as_const(sortedHitData)) {
        if (hit->GetEventID() != currentEventID or hit->GetTrackID() != currentTrackID) {
            currentEventID = hit->GetEventID();
            currentTrackID = hit->GetTrackID();
            currentTrack = std::addressof(candidates.emplace_back());
            currentTrack->reserve(2 * fThreshold);
        }
        currentTrack->emplace_back(hit);
    }
    return candidates;
}
