template<class SpectrometerHitType>
MACE::Reconstruction::Recognizer::HoughBase<SpectrometerHitType>::HoughBase(Eigen::Index rows, Eigen::Index cols) :
    fRows(rows),
    fCols(cols),
    fHitStore(0),
    fHoughSpace(rows, cols),
    fRecognizedList(0),
    fExceedThreshold(0),
    fLeftHandCandidateTrackList(0),
    fRightHandCandidateTrackList(0) {
    fRecognizedList.reserve(128UL);
    fExceedThreshold.reserve(rows * cols / 5);
}

template<class SpectrometerHitType>
MACE::Reconstruction::Recognizer::HoughBase<SpectrometerHitType>::~HoughBase() {}

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::HoughBase<SpectrometerHitType>::SetEventToBeRecognized(const std::vector<Hit>& hitVector) {
    fHitStore.clear();
    fHitStore.reserve(hitVector.size());
    for (auto&& hit : hitVector) {
        fHitStore.emplace_back(hit, 0);
    }
}

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::HoughBase<SpectrometerHitType>::Recognize() {
    Initialize();
    HoughTransform();
    FindExceedThreshold();
    GenerateResult();
}

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::HoughBase<SpectrometerHitType>::Initialize() {
    std::for_each_n(fHoughSpace.data(), fRows * fCols, [](auto& elem) { elem.clear(); });
    fRecognizedList.clear();
    fExceedThreshold.clear();
    fLeftHandCandidateTrackList.clear();
    fRightHandCandidateTrackList.clear();
}

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::HoughBase<SpectrometerHitType>::FindExceedThreshold() {
    for (Eigen::Index i = 0; i < fRows; ++i) {
        for (Eigen::Index j = 0; j < fCols; ++j) {
            const auto& hitMapList = fHoughSpace(i, j);
            if (hitMapList.size() >= fThreshold) {
                fExceedThreshold.emplace_back(&hitMapList, ToRealCartesian(std::make_pair(i, j)));
            }
        }
    }
    std::sort(fExceedThreshold.begin(), fExceedThreshold.end(),
        [](const auto& left, const auto& right)->bool {
            return left.first->size() > right.first->size();
        }
    );
}

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::HoughBase<SpectrometerHitType>::GenerateResult() {
    for (auto&& rawListAndCenter : fExceedThreshold) {
        const auto& rawList = rawListAndCenter.first;
        const auto& center = rawListAndCenter.second;
        if (rawList->size() < fThreshold) { continue; }

        fLeftHandCandidateTrackList.reserve(rawList->size());
        fRightHandCandidateTrackList.reserve(rawList->size());

        for (auto&& hitMapVoid : *rawList) {
            const auto& hit = static_cast<HitMap*>(hitMapVoid)->first;

            auto cross = hit->GetHitPosition().fX * center.second - center.first * hit->GetHitPosition().fY;
            auto& candidateTrackList = (cross > 0) ? fRightHandCandidateTrackList : fLeftHandCandidateTrackList;

            auto candidateTrackToBeJoin = std::find_if(candidateTrackList.begin(), candidateTrackList.end(),
                [&](const auto& candidate)->bool {
                    const auto timeDiff = abs(candidate.first - hit->GetHitTime());
                    return timeDiff < fTrackTimeWindow;
                }
            );
            if (candidateTrackToBeJoin == candidateTrackList.end()) {
                auto& candidateTrackOfTheTime = candidateTrackList.emplace_back(hit->GetHitTime(), 0).second;
                candidateTrackOfTheTime.reserve(64UL);
                candidateTrackToBeJoin = std::prev(candidateTrackList.end());
            }
            candidateTrackToBeJoin->second.emplace_back(static_cast<HitMap*>(hitMapVoid));
        }

        auto DumpToResultAndEraseHoughCurve =
            [&](const decltype(fLeftHandCandidateTrackList)& candidateTrackList) {
            for (auto&& candidateTrack : candidateTrackList) {
                const auto& hitMapVector = candidateTrack.second;
                if (hitMapVector.size() < fThreshold) { continue; }

                auto& track = fRecognizedList.emplace_back(0, center).first;
                track.reserve(hitMapVector.size());
                for (auto&& hitMap : hitMapVector) {
                    track.emplace_back(std::move(hitMap->first));
                    for (auto&& [hitMapList, hitMapListIter] : hitMap->second) {
                        hitMapList->erase(hitMapListIter);
                    }
                    hitMap->second.clear();
                }
            }
        };
        DumpToResultAndEraseHoughCurve(fLeftHandCandidateTrackList);
        fLeftHandCandidateTrackList.clear();
        DumpToResultAndEraseHoughCurve(fRightHandCandidateTrackList);
        fRightHandCandidateTrackList.clear();
    }
}