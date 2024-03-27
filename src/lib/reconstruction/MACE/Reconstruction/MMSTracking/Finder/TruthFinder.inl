namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<std::indirectly_readable AHit,
         Data::TupleContain<Data::Tuple<Data::MMSSimTrack>> ATrack>
    requires Data::TupleContain<std::iter_value_t<AHit>, Data::Tuple<Data::CDCSimHit>>
TruthFinder<AHit, ATrack>::TruthFinder() :
    Base{},
    fNHitThreshold{} {
    const auto& cdc{Detector::Description::CDC::Instance()};
    fNHitThreshold = cdc.NSenseLayerPerSuper() * cdc.NSuperLayer();
}

template<std::indirectly_readable AHit,
         Data::TupleContain<Data::Tuple<Data::MMSSimTrack>> ATrack>
    requires Data::TupleContain<std::iter_value_t<AHit>, Data::Tuple<Data::CDCSimHit>>
auto TruthFinder<AHit, ATrack>::operator()(const std::vector<AHit>& hitData, int) -> Result {
    if (not this->GoodHitData(hitData) or
        ssize(hitData) < fNHitThreshold) { return {}; }
    Result r;
    int trackID;
    auto trackBegin{hitData.cbegin()};
    auto trackEnd{trackBegin};
    const auto magneticFluxDensity{Detector::Description::MMSField::Instance().MagneticFluxDensity()};
    do {
        trackID = Get<"TrkID">(**trackBegin);
        trackEnd = std::ranges::find_if_not(trackBegin, hitData.cend(),
                                            [&trackID](auto&& hit) {
                                                return Get<"TrkID">(*hit) == trackID;
                                            });
        const auto nHit{std::ranges::distance(trackBegin, trackEnd)};
        if (nHit >= fNHitThreshold) {
            auto outputTrackID{trackID};
            auto [iGoodTrack, inserted]{r.good.try_emplace(outputTrackID, typename Result::GoodTrack{})};
            while (not inserted) {
                Env::PrintLnWarning("Warning: Disordered dataset (track {} has appeared before), attempting to assign track ID {}", outputTrackID, outputTrackID + 1);
                std::tie(iGoodTrack, inserted) = r.good.try_emplace(++outputTrackID, typename Result::GoodTrack{});
            }
            auto& [trackHitData, seed]{iGoodTrack->second};
            // hitData
            trackHitData.reserve(nHit);
            for (auto&& hit : std::ranges::subrange{trackBegin, trackEnd}) {
                trackHitData.emplace_back(hit);
            }
            // seed
            seed = std::make_shared_for_overwrite<Data::Tuple<Data::MMSSimTrack>>();
            const auto& firstHit{**trackBegin};
            Get<"EvtID">(*seed) = Get<"EvtID">(firstHit);
            Get<"TrkID">(*seed) = outputTrackID;
            Get<"HitID">(*seed)->resize(nHit);
            Get<"HitID">(*seed)->resize(nHit);
            std::ranges::transform(trackBegin, trackEnd, Get<"HitID">(*seed)->begin(),
                                   [](auto&& hit) { return Get<"HitID">(*hit); });
            Get<"chi2">(*seed) = 0;
            Get<"t0">(*seed) = Get<"t0">(firstHit);
            Get<"PDGID">(*seed) = Get<"PDGID">(firstHit);
            Get<"x0">(*seed) = Get<"x0">(firstHit);
            Get<"Ek0">(*seed) = Get<"Ek0">(firstHit);
            Get<"p0">(*seed) = Get<"p0">(firstHit);
            Data::CalculateHelix(*seed, magneticFluxDensity);
            Get<"CreatProc">(*seed) = Get<"CreatProc">(firstHit);
        } else {
            r.garbage.insert(r.garbage.end(), trackBegin, trackEnd);
        }
        trackBegin = trackEnd;
    } while (trackBegin != hitData.end());
    return r;
}

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder
