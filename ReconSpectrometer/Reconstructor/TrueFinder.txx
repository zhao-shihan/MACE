template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t>
MACE::ReconSpectrometer::Reconstructor::TrueFinder<FitterT_t, SpectromrterHit_t, Track_t>::
TrueFinder() :
    fClassifier(0) {}

template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t>
void MACE::ReconSpectrometer::Reconstructor::TrueFinder<FitterT_t, SpectromrterHit_t, Track_t>::
Reconstruct(const std::vector<HitPtr>& hitData) {
    const auto& [minHitIter, maxHitIter] = std::minmax_element(hitData.cbegin(), hitData.cend(),
        [](const auto& hit1, const auto& hit2)->bool {
            return hit1->GetTrackID() < hit2->GetTrackID();
        }
    );
    auto minTrackID = (*minHitIter)->GetTrackID();
    auto maxTrackID = (*maxHitIter)->GetTrackID();

    fClassifier.clear();
    fClassifier.resize(maxTrackID - minTrackID + 1);
    for (auto&& candidateContainer : fClassifier) {
        candidateContainer.reserve(fThreshold + 10);
    }

    for (auto&& hitPtr : std::as_const(hitData)) {
        fClassifier[hitPtr->GetTrackID() - minTrackID].emplace_back(hitPtr);
    }

    for (auto&& candidate : fClassifier) {
        if (candidate.size() < fThreshold) {
            Base::fOmittedHitList.insert(Base::fOmittedHitList.cend(), candidate.cbegin(), candidate.cend());
            continue;
        }

        Base::fFitter->Fit(candidate, Track_t());
        const auto& track = Base::fFitter->GetFittedTrack();
        const auto& fitted = Base::fFitter->GetFittedList();
        const auto& omitted = Base::fFitter->GetOmittedList();

        if (fitted.size() < fThreshold) {
            Base::fOmittedHitList.insert(Base::fOmittedHitList.cend(), candidate.cbegin(), candidate.cend());
        } else {
            Base::fTrackList.emplace_back(track);
            Base::fReconstructedHitList.emplace_back(fitted);
            Base::fOmittedHitList.insert(Base::fOmittedHitList.cend(), omitted.cbegin(), omitted.cend());
        }
    }
}