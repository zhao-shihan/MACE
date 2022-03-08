template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t>
void MACE::ReconTracks::Tracker::TrueFinder<FitterT_t, SpectromrterHit_t, Track_t>::
Reconstruct(const std::vector<HitPtr>& hitData) {
    Base::fTrackList.clear();
    Base::fTrackedHitList.clear();
    Base::fOmittedHitList.clear();

    for (auto&& candidate : Classify(hitData)) {
        if (candidate.size() < fThreshold) {
            Base::fOmittedHitList.insert(Base::fOmittedHitList.cend(), candidate.cbegin(), candidate.cend());
            continue;
        }

        auto track = std::make_shared<Track_t>();
        bool good = Base::fFitter->Fit(candidate, *track);
        const auto& omitted = Base::fFitter->GetOmitted();

        if (candidate.size() < fThreshold or !good) {
            Base::fOmittedHitList.insert(Base::fOmittedHitList.cend(), candidate.cbegin(), candidate.cend());
            Base::fOmittedHitList.insert(Base::fOmittedHitList.cend(), omitted.cbegin(), omitted.cend());
        } else {
            Base::fTrackList.emplace_back(track);
            Base::fTrackedHitList.emplace_back(candidate);
            Base::fOmittedHitList.insert(Base::fOmittedHitList.cend(), omitted.cbegin(), omitted.cend());
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
