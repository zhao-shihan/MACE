namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<std::indirectly_readable AHit,
         Data::TupleContain<Data::Tuple<Data::MMSTrack>> ATrack>
    requires Data::TupleContain<std::iter_value_t<AHit>, Data::Tuple<Data::CDCHit>>
FinderBase<AHit, ATrack>::~FinderBase() = default;

template<std::indirectly_readable AHit,
         Data::TupleContain<Data::Tuple<Data::MMSTrack>> ATrack>
    requires Data::TupleContain<std::iter_value_t<AHit>, Data::Tuple<Data::CDCHit>>
auto FinderBase<AHit, ATrack>::GoodHitData(const std::vector<AHit>& hitData) -> bool {
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
