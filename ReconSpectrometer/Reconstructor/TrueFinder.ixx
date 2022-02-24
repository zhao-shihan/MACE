template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t>
MACE::ReconSpectrometer::Reconstructor::TrueFinder<FitterT_t, SpectromrterHit_t, Track_t>::
TrueFinder() :
    fClassifier(0) {}

template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t>
void MACE::ReconSpectrometer::Reconstructor::TrueFinder<FitterT_t, SpectromrterHit_t, Track_t>::
Reconstruct(const std::vector<HitPtr>& hitData) {
    Base::fTrackList.clear();
    Base::fReconstructedHitList.clear();
    Base::fOmittedHitList.clear();

    const auto& [minHitIter, maxHitIter] = std::ranges::minmax_element(std::as_const(hitData),
        [](const auto& hit1, const auto& hit2)->bool {
            return hit1->GetTrackID() < hit2->GetTrackID();
        }
    );
    auto minTrackID = (*minHitIter)->GetTrackID();
    auto maxTrackID = (*maxHitIter)->GetTrackID();

    fClassifier.clear();
    fClassifier.resize(maxTrackID - minTrackID + 1);
    for (auto&& hitData : fClassifier) {
        hitData.reserve(fThreshold + 10);
    }

    for (auto&& hitPtr : std::as_const(hitData)) {
        fClassifier[hitPtr->GetTrackID() - minTrackID].emplace_back(hitPtr);
    }

    for (auto&& hitData : fClassifier) {
        if (hitData.size() < fThreshold) {
            Base::fOmittedHitList.insert(Base::fOmittedHitList.cend(), hitData.cbegin(), hitData.cend());
            continue;
        }

        auto track = std::make_shared<Track_t>();
        bool good = Base::fFitter->Fit(hitData, track);
        const auto& omitted = Base::fFitter->GetOmitted();

        if (hitData.size() < fThreshold or !good) {
            Base::fOmittedHitList.insert(Base::fOmittedHitList.cend(), hitData.cbegin(), hitData.cend());
            Base::fOmittedHitList.insert(Base::fOmittedHitList.cend(), omitted.cbegin(), omitted.cend());
        } else {
            Base::fTrackList.emplace_back(track);
            Base::fReconstructedHitList.emplace_back(hitData);
            Base::fOmittedHitList.insert(Base::fOmittedHitList.cend(), omitted.cbegin(), omitted.cend());
        }
    }
}
