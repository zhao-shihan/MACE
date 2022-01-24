template<class SpectrometerHitType>
MACE::Reconstruction::Recognizer::Hough<SpectrometerHitType>::
Hough(double r0Low, double r0Up, Eigen::Index nPhi, Eigen::Index nRho, double z0Low, double z0Up, Eigen::Index nZ0, Eigen::Index nAlpha) :
    MACE::Reconstruction::Interface::Recognizer<SpectrometerHitType>(),
    fEvent(0),
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
    fTrackList(0),
    fRecognizedParameterList(0) {}

template<class SpectrometerHitType>
MACE::Reconstruction::Recognizer::Hough<SpectrometerHitType>::
~Hough() {}

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::Hough<SpectrometerHitType>::
Recognize(const std::vector<Hit>& hitList) {
    fEvent.clear();
    fEvent.reserve(hitList.size());
    for (auto&& hit : hitList) {
        fEvent.emplace_back(hit);
    }

    Base::fRecognizedList.clear();
    fRecognizedParameterList.clear();

    HoughTransformXY();
    FindExceedThresholdXY();
    for (auto&& [piledTracks, center] : fPiledTrackList) {
        if (EffectiveSizeOf(*piledTracks) < fThresholdXY) { continue; }
        HoughTransformSZ(piledTracks, center);
        FindExceedThresholdSZ(center);
        DumpToResult();
    }
}

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::Hough<SpectrometerHitType>::
HoughTransformXY() {
    std::for_each_n(fHoughSpaceXY.data(), fHoughSpaceXY.rows() * fHoughSpaceXY.cols(), [](auto& elem) { elem.clear(); });
    // for each hit
    for (auto&& hit : fEvent) {
        const auto x = hit->GetWirePosition().fX;
        const auto y = hit->GetWirePosition().fY;
        const auto d = hit->GetDriftDistance();
        const auto r2 = x * x + y * y - d * d;
        const auto X = 2 * x / r2;
        const auto Y = 2 * y / r2;
        const auto D = 2 * d / r2;

        // do hough transform
        auto phi = ToPhiReal(0);
        auto jLast = ToRhoIndex(X * cos(phi) + Y * sin(phi) + D);
        auto DoFill = [&](Eigen::Index i, Eigen::Index j)->void {
            if (0 <= j && j < fHoughSpaceXY.cols()) {
                fHoughSpaceXY(i, j).emplace_back(&hit);
            }
        };
        DoFill(0, jLast);
        for (Eigen::Index i = 1; i < fHoughSpaceXY.rows(); ++i) {
            phi = ToPhiReal(i);
            const auto j = ToRhoIndex(X * cos(phi) + Y * sin(phi) + D);
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

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::Hough<SpectrometerHitType>::
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
                fPiledTrackList.emplace_back(&piledTracks, std::make_pair(x0, y0));
            }
        }
    }
    std::sort(fPiledTrackList.begin(), fPiledTrackList.end(),
        [](const auto& left, const auto& right)->bool {
            return left.first->size() > right.first->size();
        }
    );
}

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::Hough<SpectrometerHitType>::
HoughTransformSZ(const std::vector<Hit*>* piledTracks, const std::pair<double, double>& center) {
    std::for_each_n(fHoughSpaceSZ.data(), fHoughSpaceSZ.rows() * fHoughSpaceSZ.cols(), [](auto& elem) { elem.clear(); });
    // for each hit exceed threshold in XY hough space
    for (auto&& hitPtr : *piledTracks) {
        if (*hitPtr == nullptr) { continue; }

        const auto* hit = hitPtr->get();
        const auto x = hit->GetWirePosition().fX;
        const auto y = hit->GetWirePosition().fY;
        const auto [x0, y0] = center;
        const auto r2 = (x - x0) * (x - x0) + (y - y0) * (y - y0);
        const auto r02 = x0 * x0 + y0 * y0;
        const auto s = std::sqrt(r02) * std::asin((x0 * y - y0 * x) / std::sqrt(r2 * r02));
        const auto z = hit->GetHitPositionZ();

        // do hough transform
        auto z0 = ToZ0Real(0);
        auto jLast = ToAlphaIndex(std::atan2(z - z0, s));
        auto DoFill = [&](Eigen::Index i, Eigen::Index j)->void {
            if (0 <= j && j < fHoughSpaceSZ.cols()) {
                fHoughSpaceSZ(i, j).emplace_back(hitPtr);
            }
        };
        DoFill(0, jLast);
        for (Eigen::Index i = 1; i < fHoughSpaceSZ.rows(); ++i) {
            z0 = ToZ0Real(i);
            const auto j = ToAlphaIndex(std::atan2(z - z0, s));
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

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::Hough<SpectrometerHitType>::
FindExceedThresholdSZ(const std::pair<double, double>& center) {
    fTrackList.clear();
    for (Eigen::Index i = 0; i < fHoughSpaceSZ.rows(); ++i) {
        for (Eigen::Index j = 0; j < fHoughSpaceSZ.cols(); ++j) {
            const auto& track = fHoughSpaceSZ(i, j);
            if (track.size() >= fThresholdSZ) {
                auto alpha = ToAlphaReal(i);
                auto z0 = ToZ0Real(j);
                fTrackList.emplace_back(&track, std::make_tuple(center.first, center.second, z0, alpha));
            }
        }
    }
    std::sort(fTrackList.begin(), fTrackList.end(),
        [](const auto& left, const auto& right)->bool {
            return left.first->size() > right.first->size();
        }
    );
}

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::Hough<SpectrometerHitType>::DumpToResult() {
    for (auto&& [track, parameters] : fTrackList) {
        if (EffectiveSizeOf(*track) < fThresholdSZ) { continue; }
        // dump to result
        auto& trackResult = Base::fRecognizedList.emplace_back();
        for (auto&& hitPtr : *track) {
            if (*hitPtr == nullptr) { continue; }
            trackResult.emplace_back(*hitPtr);
            // remove hough curve
            hitPtr->reset(static_cast<SpectrometerHitType*>(nullptr));
        }
        fRecognizedParameterList.emplace_back(std::move(parameters));
    }
}