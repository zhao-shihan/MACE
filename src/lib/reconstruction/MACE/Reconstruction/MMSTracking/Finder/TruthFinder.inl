namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<Data::TupleModelContain<Data::CDCSimHit> AHit, Data::TupleModelContain<Data::MMSSimTrack> ATrack>
TruthFinder<AHit, ATrack>::TruthFinder() :
    Base{},
    fNHitThreshold{} {
    const auto& cdc{Detector::Description::CDC::Instance()};
    fNHitThreshold = cdc.NSenseLayerPerSuper() * cdc.NSuperLayer();
}

template<Data::TupleModelContain<Data::CDCSimHit> AHit, Data::TupleModelContain<Data::MMSSimTrack> ATrack>
auto TruthFinder<AHit, ATrack>::operator()(const HitCollection& hitData, int) -> Result {
    if (not GoodHitData(hitData)) { return {}; }
    Result r;
    auto trackID{Get<"TrkID">(*hitData.front())};
    auto trackBegin{hitData.begin()};
    auto trackEnd{trackBegin};
    const auto magneticFluxDensity{Detector::Description::MMSField::Instance().MagneticFluxDensity()};
    do {
        trackEnd = std::ranges::find_if_not(trackBegin, hitData.end(),
                                            [&trackID](auto&& hit) {
                                                return Get<"TrkID">(*hit) == trackID;
                                            });
        const auto nHit{std::ranges::distance(trackBegin, trackEnd)};
        if (nHit >= fNHitThreshold) {
            const auto& firstHit{**trackBegin};
            auto trackID{Get<"TrkID">(firstHit)};
            while (not r.goodies.try_emplace(trackID, HitCollection{trackBegin, trackEnd}).second) {
                Env::PrintLnWarning("Warning: Disordered dataset (track {} has appeared before), attempting to assign track ID {}", trackID, trackID + 1);
                ++trackID;
            }
            r.seed = std::make_shared_for_overwrite<Data::Tuple<Data::MMSSimTrack>>();
            Get<"EvtID">(r.seed) = Get<"EvtID">(firstHit);
            Get<"TrkID">(r.seed) = trackID;
            Get<"HitID">(r.seed)->resize(nHit); // to be determined
            Get<"chi2">(r.seed) = 0;
            Get<"t0">(r.seed) = Get<"t0">(firstHit);
            Get<"PDGID">(r.seed) = Get<"PDGID">(firstHit);
            Get<"x0">(r.seed) = Get<"x0">(firstHit);
            Get<"Ek0">(r.seed) = Get<"Ek0">(firstHit);
            Get<"p0">(r.seed) = Get<"p0">(firstHit);
            Data::CalculateHelix(r.seed, magneticFluxDensity);
            Get<"CreatProc">(r.seed) = Get<"CreatProc">(firstHit);
        } else {
            r.garbage.insert(r.garbage.end(), trackBegin, trackEnd);
        }
        trackBegin = trackEnd;
    } while (trackBegin != hitData.end());
}

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder
