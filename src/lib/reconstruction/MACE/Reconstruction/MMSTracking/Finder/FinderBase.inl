namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<Data::TupleModelContain<Data::CDCHit> AHit, Data::TupleModelContain<Data::MMSTrack> ATrack>
auto FinderBase<AHit, ATrack>::GoodHitData(const HitCollection& hitData) -> bool {
    auto good{true};

    if (hitData.empty()) [[unlikely]] {
        Env::PrintLnWarning("Warning: Empty hit data");
        good = false;
    }

    std::unordered_set<int> eventID;
    for (auto&& hit : hitData) {
        eventID.emplace(Get<"EvtID">(*hit));
    }
    if (eventID.size() != 1) [[unlikely]] {
        Env::PrintLnWarning("Warning: Hit data include different event IDs {}, skipping", eventID);
        good = false;
    }

    return good;
}

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder
