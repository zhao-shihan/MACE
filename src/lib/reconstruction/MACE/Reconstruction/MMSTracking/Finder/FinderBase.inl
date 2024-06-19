namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit,
         Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack>
FinderBase<AHit, ATrack>::~FinderBase() = default;

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit,
         Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack>
template<std::indirectly_readable AHitPointer>
    requires std::derived_from<std::decay_t<std::iter_value_t<AHitPointer>>, Mustard::Data::Tuple<AHit>>
auto FinderBase<AHit, ATrack>::GoodHitData(const std::vector<AHitPointer>& hitData) -> bool {
    if (hitData.empty()) [[unlikely]] {
        Mustard::Env::PrintLnWarning("Warning: Empty hit data");
        return false;
    }

    auto good{true};

    std::unordered_set<int> eventID;
    eventID.reserve(hitData.size());
    for (auto&& hit : hitData) {
        eventID.emplace(Get<"EvtID">(*hit));
    }
    if (eventID.size() != 1) [[unlikely]] {
        Mustard::Env::PrintLnWarning("Warning: Hit data include different event IDs {}, skipping", eventID);
        good = false;
    }

    return good;
}

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder
