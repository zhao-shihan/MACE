/* template<template<class T> class FitterT_t, class SpectrometerHit_t>
MACE::ReconTracks::Tracker::Hough<FitterT_t, SpectrometerHit_t>::
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

template<template<class T> class FitterT_t, class SpectrometerHit_t>
MACE::ReconTracks::Tracker::Hough<FitterT_t, SpectrometerHit_t>::
~Hough() noexcept = default;

template<template<class T> class FitterT_t, class SpectrometerHit_t>
void MACE::ReconTracks::Tracker::Hough<FitterT_t, SpectrometerHit_t>::
Reconstruct(const std::vector<HitPtr>& hitData) {
    fHitData = hitData;

    Base::fReconstructedList.clear();
    Base::fOmittedList.clear();

    HoughTransformXY();
    FindExceedThresholdXY();

    for (auto&& [center, piledTracks] : fPiledTrackList) {
        auto lastHitCountOfPiledTracks = std::numeric_limits<decltype(EffectiveSizeOf(*piledTracks))>::max();
        auto thisHitCountOfPiledTracks = EffectiveSizeOf(*piledTracks);
        while (thisHitCountOfPiledTracks > fThresholdXY and thisHitCountOfPiledTracks < lastHitCountOfPiledTracks) {
            HoughTransformSZ(center, piledTracks);
            FindExceedThresholdSZ(center);

            for (auto&& [parameters, track] : fTrackList) {
                auto lastHitCountOfTracks = std::numeric_limits<decltype(EffectiveSizeOf(*track))>::max();
                auto thisHitCountOfTracks = EffectiveSizeOf(*track);
                while (thisHitCountOfTracks > fThresholdSZ and thisHitCountOfTracks < lastHitCountOfTracks) {
                    FitAndDumpToResult(parameters, track);
                    lastHitCountOfTracks = thisHitCountOfTracks;
                    thisHitCountOfTracks = EffectiveSizeOf(*track);
                }
            }

            lastHitCountOfPiledTracks = thisHitCountOfPiledTracks;
            thisHitCountOfPiledTracks = EffectiveSizeOf(*piledTracks);
        }
    }

    GenerateOmitted();
}

template<template<class T> class FitterT_t, class SpectrometerHit_t>
void MACE::ReconTracks::Tracker::Hough<FitterT_t, SpectrometerHit_t>::
HoughTransformXY() {
    std::for_each_n(fHoughSpaceXY.data(), fHoughSpaceXY.rows() * fHoughSpaceXY.cols(), [](auto& elem) { elem.clear(); });
    // for each hit
    for (auto&& hit : fHitData) {
        const auto x = hit->GetWirePosition().fX;
        const auto y = hit->GetWirePosition().fY;
        const auto d = hit->GetDriftDistance();
        const auto r2 = x * x + y * y - d * d;
        const auto X = 2 * x / r2;
        const auto Y = 2 * y / r2;
        const auto D = 2 * d / r2;

        // do hough transform
        auto Hough = [&](double phi)->double { return X * cos(phi) + Y * sin(phi); };

        auto phi = ToPhiReal(0);
        auto jLast = ToRhoIndex(Hough(phi));
        auto jDrift = (Eigen::Index)std::lround(D / fRhoResolution);

        if (jDrift == 0) {

            auto DoFill = [&](Eigen::Index i, Eigen::Index j)->void {
                if (0 <= j and j < fHoughSpaceXY.cols()) {
                    fHoughSpaceXY(i, j).emplace_back(std::addressof(hit));
                }
            };
            DoFill(0, jLast);
            for (Eigen::Index i = 1; i < fHoughSpaceXY.rows(); ++i) {
                phi = ToPhiReal(i);
                const auto j = ToRhoIndex(Hough(phi));
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

        } else {

            auto FillPlus = [&](Eigen::Index i, Eigen::Index j)->void {
                const auto jPlus = jCenter + jDrift;
                if (0 <= jPlus and jPlus < fHoughSpaceXY.cols()) {
                    fHoughSpaceXY(i, jPlus).emplace_back(std::addressof(hit));
                }
            };
            auto FillMinus = [&](Eigen::Index i, Eigen::Index j)->void {
                const auto jMinus = jCenter - jDrift;
                if (0 <= jMinus and jMinus < fHoughSpaceXY.cols()) {
                    fHoughSpaceXY(i, jMinus).emplace_back(std::addressof(hit));
                }
            };
            FillPlus(0, jLast);
            FillMinus(0, jLast);
            for (Eigen::Index i = 1; i < fHoughSpaceXY.rows(); ++i) {
                phi = ToPhiReal(i);
                const auto j = ToRhoIndex(Hough(phi));
                const auto jDiff = j - jLast;
                if (jDiff > 1) {
                    for (auto k = jLast + 1; k < jLast + jDiff / 2; ++k) {
                        FillPlus(i - 1, k);
                        if (k < jLast + 2 * jDrift) {
                            FillMinus(i - 1, k);
                        }
                    }
                    for (auto k = jLast + jDiff / 2; k < j; ++k) {
                        FillPlus(i, k);
                        if (k < jLast + jDiff / 2 + 2 * jDrift) {
                            FillMinus(i, k);
                        }
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
}

template<template<class T> class FitterT_t, class SpectrometerHit_t>
void MACE::ReconTracks::Tracker::Hough<FitterT_t, SpectrometerHit_t>::
FindExceedThresholdXY() {
    fPiledTrackList.clear();
    for (Eigen::Index i = 0; i < fHoughSpaceXY.rows(); ++i) {
        auto phi = ToPhiReal(i);
        for (Eigen::Index j = 0; j < fHoughSpaceXY.cols(); ++j) {
            const auto& piledTracks = fHoughSpaceXY(i, j);
            if (piledTracks.size() >= fThresholdXY) {
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

template<template<class T> class FitterT_t, class SpectrometerHit_t>
void MACE::ReconTracks::Tracker::Hough<FitterT_t, SpectrometerHit_t>::
HoughTransformSZ(const std::pair<double, double>& center, const std::vector<HitPtr*>* piledTracks) {
    std::for_each_n(fHoughSpaceSZ.data(), fHoughSpaceSZ.rows() * fHoughSpaceSZ.cols(), [](auto& elem) { elem.clear(); });
    // for each hit exceed threshold in XY hough space
    for (auto&& hitPtrPtr : *piledTracks) {
        if (*hitPtrPtr == nullptr) { continue; }

        const auto* hit = hitPtrPtr->get();
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
            if (0 <= j and j < fHoughSpaceSZ.cols()) {
                fHoughSpaceSZ(i, j).emplace_back(hitPtrPtr);
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

template<template<class T> class FitterT_t, class SpectrometerHit_t>
void MACE::ReconTracks::Tracker::Hough<FitterT_t, SpectrometerHit_t>::
FindExceedThresholdSZ(const std::pair<double, double>& center) {
    fTrackList.clear();
    auto radius = std::hypot(center.first, center.second);
    for (Eigen::Index i = 0; i < fHoughSpaceSZ.rows(); ++i) {
        auto z0 = ToZ0Real(i);
        for (Eigen::Index j = 0; j < fHoughSpaceSZ.cols(); ++j) {
            const auto& track = fHoughSpaceSZ(i, j);
            if (track.size() >= fThresholdSZ) {
                auto alpha = ToAlphaReal(j);
                fTrackList.emplace_back(HelixParameters{ center.first, center.second, radius, z0, alpha }, std::addressof(track));
            }
        }
    }
    std::sort(fTrackList.begin(), fTrackList.end(),
        [](const auto& left, const auto& right)->bool {
            return left.second->size() > right.second->size();
        }
    );
}

template<template<class T> class FitterT_t, class SpectrometerHit_t>
void MACE::ReconTracks::Tracker::Hough<FitterT_t, SpectrometerHit_t>::
FitAndDumpToResult(const HelixParameters& parameters, const std::vector<HitPtr*>* track) {
    std::unordered_map<HitPtr, HitPtr*> hitPtrMap;
    hitPtrMap.reserve(track->size());
    std::vector<HitPtr> hitDataToBeFitted;
    hitDataToBeFitted.reserve(track->size());
    for (auto&& hitPtrPtr : *track) {
        if (*hitPtrPtr == nullptr) { continue; }
        hitPtrMap.emplace(*hitPtrPtr, hitPtrPtr);
        hitDataToBeFitted.emplace_back(*hitPtrPtr);
    }

    Base::fFitter->SetInitialParameters(parameters);
    Base::fFitter->SetHitDataToBeFitted(hitDataToBeFitted);
    Base::fFitter->Fit();
    const auto& fittedParameters = Base::fFitter->GetFittedParameters();
    const auto& fittedTrack = Base::fFitter->GetFittedTrack();

    // dump to result
    Base::fReconstructedList.emplace_back(fittedParameters, fittedTrack);
    // remove hough curve
    for (auto&& hitPtr : fittedTrack) {
        hitPtrMap[hitPtr]->reset(static_cast<SpectrometerHit_t*>(nullptr));
    }
}

template<template<class T> class FitterT_t, class SpectrometerHit_t>
void MACE::ReconTracks::Tracker::Hough<FitterT_t, SpectrometerHit_t>::
GenerateOmitted() {
    for (auto&& hitPtr : fHitData) {
        if (hitPtr) {
            Base::fOmittedList.emplace_back(hitPtr);
        }
    }
} */