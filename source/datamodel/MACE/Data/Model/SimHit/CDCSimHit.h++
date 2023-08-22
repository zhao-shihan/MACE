#pragma once

#include "MACE/Data/Model/Hit/CDCHit.h++"
#include "MACE/Data/Model/Modelled.h++"
#include "MACE/Data/Model/SimHit/SimHitBasis.h++"

#include <string_view>

namespace MACE::Data::inline Model::inline SimHit {

class CDCSimHit : public Modelled<CDCSimHit,
                                  std::tuple<CDCHit,
                                             SimHitBasis>,
                                  std::tuple<>> {
public:
    static constexpr auto BasicName() -> std::string_view { return "CDCSimHit"; }
};

} // namespace MACE::Data::inline Model::inline SimHit
