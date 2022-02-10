template<template<class T> class FitterT_t, class SpectromrterHit_t>
MACE::ReconSpectrometer::Reconstructor::TrueFinder<FitterT_t, SpectromrterHit_t>::
TrueFinder() :
    fClassifier(0) {}

template<template<class T> class FitterT_t, class SpectromrterHit_t>
void MACE::ReconSpectrometer::Reconstructor::TrueFinder<FitterT_t, SpectromrterHit_t>::
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
    for (auto&& trackContainer : fClassifier) {
        trackContainer.reserve(fThreshold + 10);
    }

    for (auto&& hitPtr : std::as_const(hitData)) {
        fClassifier[hitPtr->GetTrackID() - minTrackID].emplace_back(hitPtr);
    }

    for (auto&& track : fClassifier) {
        if (track.size() < fThreshold) {
            Base::fOmittedList.insert(Base::fOmittedList.cend(), track.cbegin(), track.cend());
            continue;
        }

        Base::fFitter->Fit(track);
        const auto& helixParameters = Base::fFitter->GetFittedParameters();
        const auto& fittedTrack = Base::fFitter->GetFittedTrack();
        const auto& fitOmitted = Base::fFitter->GetOmittedList();

        if (fittedTrack.size() < fThreshold) {
            Base::fOmittedList.insert(Base::fOmittedList.cend(), track.cbegin(), track.cend());
        } else {
            Base::fReconstructedList.emplace_back(helixParameters, fittedTrack);
            Base::fOmittedList.insert(Base::fOmittedList.cend(), fitOmitted.cbegin(), fitOmitted.cend());
        }
    }
}