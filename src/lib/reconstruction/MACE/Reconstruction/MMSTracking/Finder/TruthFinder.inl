namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<Data::SuperTupleModel<Data::CDCHit> AHit,
         Data::SuperTupleModel<Data::MMSTrack> ATrack>
TruthFinder<AHit, ATrack>::TruthFinder() :
    Base{},
    fNHitThreshold{} {
    const auto& cdc{Detector::Description::CDC::Instance()};
    fNHitThreshold = cdc.NSenseLayerPerSuper() * cdc.NSuperLayer();
}

template<Data::SuperTupleModel<Data::CDCHit> AHit,
         Data::SuperTupleModel<Data::MMSTrack> ATrack>
template<std::indirectly_readable AHitPointer>
    requires std::derived_from<std::decay_t<std::iter_value_t<AHitPointer>>, Data::Tuple<AHit>>
auto TruthFinder<AHit, ATrack>::operator()(const std::vector<AHitPointer>& hitData, int) -> Base::template Result<AHitPointer> {
    using Result = Base::template Result<AHitPointer>;

    if (not this->GoodHitData(hitData) or
        ssize(hitData) < fNHitThreshold) { return {}; }

    Result r;
    r.good.reserve(hitData.size() / fNHitThreshold);
    r.garbage.reserve(hitData.size());

    const auto magneticFluxDensity{Detector::Description::MMSField::Instance().FastField()};

    std::ranges::subrange track{hitData.cbegin(), hitData.cbegin()};
    const auto CollectGarbage{
        [&] { r.garbage.insert(r.garbage.end(), track.begin(), track.end()); }};

    std::unordered_set<short> cellHit;
    cellHit.reserve(fNHitThreshold);

    while (track.end() != hitData.end()) {
        track = {track.end(), std::ranges::upper_bound(track.end(), hitData.end(), *track.end(),
                                                       [](auto&& hit1, auto&& hit2) {
                                                           return Get<"TrkID">(*hit1) < Get<"TrkID">(*hit2);
                                                       })};

        if (std::ranges::ssize(track) < fNHitThreshold) {
            CollectGarbage();
            continue;
        }

        cellHit.clear();
        for (auto&& hit : track) {
            cellHit.emplace(Get<"CellID">(*hit));
        }
        if (ssize(cellHit) < fNHitThreshold) {
            CollectGarbage();
            continue;
        }

        auto outputTrackID{*Get<"TrkID">(**track.begin())};
        auto [iGoodTrack, inserted]{r.good.try_emplace(outputTrackID, typename Result::GoodTrack{})};
        while (not inserted) {
            Env::PrintLnWarning("Warning: Disordered dataset (track {} has appeared before), attempting to assign track ID {}", outputTrackID, outputTrackID + 1);
            std::tie(iGoodTrack, inserted) = r.good.try_emplace(++outputTrackID, typename Result::GoodTrack{});
        }
        auto& [trackHitData, seed]{iGoodTrack->second};

        trackHitData.reserve(track.size());
        for (auto&& hit : track) {
            trackHitData.emplace_back(hit);
        }

        seed = std::make_shared_for_overwrite<Data::Tuple<Data::MMSSimTrack>>();
        const auto& firstHit{**track.begin()};
        Get<"EvtID">(*seed) = Get<"EvtID">(firstHit);
        Get<"TrkID">(*seed) = outputTrackID;
        Get<"HitID">(*seed)->reserve(track.size());
        for (auto&& hit : track) { Get<"HitID">(*seed)->emplace_back(Get<"HitID">(*hit)); }
        Get<"chi2">(*seed) = 0;
        Get<"t0">(*seed) = Get<"t0">(firstHit);
        Get<"PDGID">(*seed) = Get<"PDGID">(firstHit);
        Get<"x0">(*seed) = Get<"x0">(firstHit);
        Get<"Ek0">(*seed) = Get<"Ek0">(firstHit);
        Get<"p0">(*seed) = Get<"p0">(firstHit);
        Data::CalculateHelix(*seed, magneticFluxDensity);
        Get<"CreatProc">(*seed) = Get<"CreatProc">(firstHit);
    }

    return r;
}

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder
