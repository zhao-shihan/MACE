#pragma once

#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Reconstruction/MMSTracking/Finder/FinderBase.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Env/Print.h++"

#include "CLHEP/Vector/ThreeVector.h"

#include "muc/algorithm"

#include <algorithm>
#include <iterator>
#include <ranges>
#include <unordered_set>

namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<Mustard::Data::SuperTupleModel<Data::CDCSimHit> AHit = Data::CDCSimHit,
         Mustard::Data::SuperTupleModel<Data::MMSSimTrack> ATrack = Data::MMSSimTrack>
class TruthFinder : public FinderBase<AHit, ATrack> {
protected:
    using Base = FinderBase<AHit, ATrack>;

public:
    virtual ~TruthFinder() override = default;

    template<std::indirectly_readable AHitPointer>
        requires Mustard::Data::SuperTupleModel<typename std::iter_value_t<AHitPointer>::Model, AHit>
    auto operator()(const std::vector<AHitPointer>& hitData, int = {}) const -> Base::template Result<AHitPointer>;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder

#include "MACE/Reconstruction/MMSTracking/Finder/TruthFinder.inl"
