template<template<class T> class FitterT_t, class SpectromrterHit_t>
MACE::ReconSpectrometer::Reconstructor::Hough<FitterT_t, SpectromrterHit_t>::
Hough(double r0Low, double r0Up, Eigen::Index nPhi, Eigen::Index nRho, double z0Low, double z0Up, Eigen::Index nZ0, Eigen::Index nAlpha) :
    Base(),
    fRhoLow(1 / r0Up),
    fRhoUp(1 / r0Low),
    fPhiResolution(2 * M_PI / nPhi),
    fRhoResolution((fRhoUp - fRhoLow) / nRho),
    fHoughSpaceXY(nPhi, nRho),
    fPiledTrackList(0),
    fZ0Low(z0Low),
    fZ0Up(z0Up),
    fZ0Resolution((fZ0Up - fZ0Low) / nZ0),
    fAlphaResolution(2 * M_PI / nAlpha),
    fHoughSpaceSZ(nZ0, nAlpha),
    fTrackList(0) {}

template<template<class T> class FitterT_t, class SpectromrterHit_t>
MACE::ReconSpectrometer::Reconstructor::Hough<FitterT_t, SpectromrterHit_t>::
~Hough() {}

template<template<class T> class FitterT_t, class SpectromrterHit_t>
void MACE::ReconSpectrometer::Reconstructor::Hough<FitterT_t, SpectromrterHit_t>::
Reconstruct() {
    Base::fReconstructedTrackList.clear();

    HoughTransformXY();
    FindExceedThresholdXY();

    for (auto&& [center, piledTracks] : fPiledTrackList) {
        while (EffectiveSizeOf(*piledTracks) > fThresholdXY) {
            HoughTransformSZ(center, piledTracks);
            FindExceedThresholdSZ(center);

            for (auto&& [parameters, track] : fTrackList) {
                while (EffectiveSizeOf(*track) > fThresholdSZ) {
                    FitAndDumpToResult(parameters, track);
                }
            }
        }
    }
}

template<template<class T> class FitterT_t, class SpectromrterHit_t>
void MACE::ReconSpectrometer::Reconstructor::Hough<FitterT_t, SpectromrterHit_t>::
HoughTransformXY() {
    std::for_each_n(fHoughSpaceXY.data(), fHoughSpaceXY.rows() * fHoughSpaceXY.cols(), [](auto& elem) { elem.clear(); });
    // for each hit
    for (auto&& hit : Base::fHitData) {
        const auto x = hit->GetWirePosition().fX;
        const auto y = hit->GetWirePosition().fY;
        const auto d = hit->GetDriftDistance();
        const auto r2 = x * x + y * y - d * d;
        const auto X = 2 * x / r2;
        const auto Y = 2 * y / r2;
        const auto D = 2 * d / r2;

        // do hough transform
        auto phi = ToPhiReal(0);
        auto jLast = ToRhoIndex(X * cos(phi) + Y * sin(phi));
        auto jDrift = (Eigen::Index)std::lround(D / fRhoResolution);
        auto DoFill = [&](Eigen::Index i, Eigen::Index jCenter)->void {
            if (jDrift == 0) {
                if (0 <= jCenter && jCenter < fHoughSpaceXY.cols()) {
                    fHoughSpaceXY(i, jCenter).emplace_back(std::addressof(hit));
                }
            } else {
                const auto jPlus = jCenter + jDrift;
                if (0 <= jPlus && jPlus < fHoughSpaceXY.cols()) {
                    fHoughSpaceXY(i, jPlus).emplace_back(std::addressof(hit));
                }
                const auto jMinus = jCenter - jDrift;
                if (0 <= jMinus && jMinus < fHoughSpaceXY.cols()) {
                    fHoughSpaceXY(i, jMinus).emplace_back(std::addressof(hit));
                }
            }
        };
        DoFill(0, jLast);
        for (Eigen::Index i = 1; i < fHoughSpaceXY.rows(); ++i) {
            phi = ToPhiReal(i);
            const auto j = ToRhoIndex(X * cos(phi) + Y * sin(phi));
            const auto jDiff = j - jLast;
            if (jDiff > 1) {
                for (auto k = jLast + 1; k < jLast + jDiff / 2; ++k) {
                    DoFill(i - 1, k);
                }
                for (auto k = jLast + jDiff / 2; k < j; ++k) {
                    DoFill(i, k);
                }
            }
            if (jDiff < -1) {
                for (auto k = jLast - 1; k > jLast + jDiff / 2; --k) {
                    DoFill(i - 1, k);
                }
                for (auto k = jLast + jDiff / 2; k > j; --k) {
                    DoFill(i, k);
                }
            }
            DoFill(i, j);
            jLast = j;
        }
    }
}

template<template<class T> class FitterT_t, class SpectromrterHit_t>
void MACE::ReconSpectrometer::Reconstructor::Hough<FitterT_t, SpectromrterHit_t>::
FindExceedThresholdXY() {
    fPiledTrackList.clear();
    for (Eigen::Index i = 0; i < fHoughSpaceXY.rows(); ++i) {
        for (Eigen::Index j = 0; j < fHoughSpaceXY.cols(); ++j) {
            const auto& piledTracks = fHoughSpaceXY(i, j);
            if (piledTracks.size() >= fThresholdXY) {
                auto phi = ToPhiReal(i);
                auto rho = ToRhoReal(j);
                auto x0 = cos(phi) / rho;
                auto y0 = sin(phi) / rho;
                fPiledTrackList.emplace_back(std::make_pair(x0, y0), std::addressof(piledTracks));
            }
        }
    }
    std::sort(fPiledTrackList.begin(), fPiledTrackList.end(),
        [](const auto& left, const auto& right)->bool {
            return left.second->size() > right.second->size();
        }
    );
}

template<template<class T> class FitterT_t, class SpectromrterHit_t>
void MACE::ReconSpectrometer::Reconstructor::Hough<FitterT_t, SpectromrterHit_t>::
HoughTransformSZ(const std::pair<double, double>& center, const std::vector<HitPtr*>* piledTracks) {
    std::for_each_n(fHoughSpaceSZ.data(), fHoughSpaceSZ.rows() * fHoughSpaceSZ.cols(), [](auto& elem) { elem.clear(); });
    // for each hit exceed threshold in XY hough space
    for (auto&& pHitPtr : *piledTracks) {
        if (*pHitPtr == nullptr) { continue; }

        const auto* hit = pHitPtr->get();
        const auto x = hit->GetWirePosition().fX;
        const auto y = hit->GetWirePosition().fY;
        const auto [x0, y0] = center;
        const auto r2 = (x - x0) * (x - x0) + (y - y0) * (y - y0);
        const auto r02 = x0 * x0 + y0 * y0;
        const auto s = std::sqrt(r02) * std::asin((x0 * y - y0 * x) / std::sqrt(r2 * r02));
        const auto z = hit->GetHitPositionZ();

        // do hough transform
        auto z0 = ToZ0Real(0);
        auto jLast = ToAlphaIndex(std::atan2(s, z - z0));
        auto DoFill = [&](Eigen::Index i, Eigen::Index j)->void {
            if (0 <= j && j < fHoughSpaceSZ.cols()) {
                fHoughSpaceSZ(i, j).emplace_back(pHitPtr);
            }
        };
        DoFill(0, jLast);
        for (Eigen::Index i = 1; i < fHoughSpaceSZ.rows(); ++i) {
            z0 = ToZ0Real(i);
            const auto j = ToAlphaIndex(std::atan2(s, z - z0));
            const auto jDiff = j - jLast;
            if (jDiff > 1) {
                for (auto k = jLast + 1; k < jLast + jDiff / 2; ++k) {
                    DoFill(i - 1, k);
                }
                for (auto k = jLast + jDiff / 2; k < j; ++k) {
                    DoFill(i, k);
                }
            }
            if (jDiff < -1) {
                for (auto k = jLast - 1; k > jLast + jDiff / 2; --k) {
                    DoFill(i - 1, k);
                }
                for (auto k = jLast + jDiff / 2; k > j; --k) {
                    DoFill(i, k);
                }
            }
            DoFill(i, j);
            jLast = j;
        }
    }
}

template<template<class T> class FitterT_t, class SpectromrterHit_t>
void MACE::ReconSpectrometer::Reconstructor::Hough<FitterT_t, SpectromrterHit_t>::
FindExceedThresholdSZ(const std::pair<double, double>& center) {
    fTrackList.clear();
    for (Eigen::Index i = 0; i < fHoughSpaceSZ.rows(); ++i) {
        for (Eigen::Index j = 0; j < fHoughSpaceSZ.cols(); ++j) {
            const auto& track = fHoughSpaceSZ(i, j);
            if (track.size() >= fThresholdSZ) {
                auto alpha = ToAlphaReal(i);
                auto z0 = ToZ0Real(j);
                fTrackList.emplace_back(HelixParameters{ center.first, center.second, z0, alpha }, std::addressof(track));
            }
        }
    }
    std::sort(fTrackList.begin(), fTrackList.end(),
        [](const auto& left, const auto& right)->bool {
            return left.second->size() > right.second->size();
        }
    );
}

template<template<class T> class FitterT_t, class SpectromrterHit_t>
void MACE::ReconSpectrometer::Reconstructor::Hough<FitterT_t, SpectromrterHit_t>::
FitAndDumpToResult(const HelixParameters& parameters, const std::vector<HitPtr*>* track) {
    std::unordered_map<HitPtr, HitPtr*> hitPtrMap;
    hitPtrMap.reserve(track->size());
    std::vector<HitPtr> hitDataToBeFitted;
    hitDataToBeFitted.reserve(tracks->size());
    for (auto&& pHitPtr : *track) {
        if (*pHitPtr == nullptr) { continue; }
        hitPtrMap.emplace(*pHitPtr, pHitPtr);
        hitDataToBeFitted.emplace_back(*pHitPtr);
    }

    Base::fFitter->SetHitDataToBeFitted(hitDataToBeFitted);
    Base::fFitter->Fit();
    const auto& fittedTrack = Base::fFitter->GetFittedTrack();
    const auto& fittedParameters = Base::fFitter->GetHelixParameter();

    // dump to result and remove hough curve, skip unfitted points
    auto& [parametersResult, trackResult] = Base::fReconstructedTrackList.emplace_back();
    for (auto&& hitPtr : fittedTrack) {
        trackResult.emplace_back(hitPtr);
        // remove hough curve
        hitPtrMap[hitPtr]->reset(static_cast<SpectromrterHit_t*>(nullptr));
    }
    parametersResult = std::move(parameters);
}