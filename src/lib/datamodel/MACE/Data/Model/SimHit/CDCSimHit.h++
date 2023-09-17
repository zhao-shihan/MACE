#pragma once

#include "MACE/Data/Model/Hit/CDCHit.h++"
#include "MACE/Data/Model/Modelize.h++"
#include "MACE/Data/Model/SimHit/SimHitBasis.h++"

#include <string_view>

namespace MACE::Data::inline Model::inline SimHit {

class CDCSimHit : public Modelize<CDCSimHit,
                                  std::tuple<CDCHit,
                                             SimHitBasis>,
                                  std::tuple<>> {
public:
    static constexpr auto BasicName() -> std::string_view { return "CDCSimHit"; }

public:
    class Entry : public Modelize::Entry {
    public:
        virtual ~Entry() override = default;
    };
};

} // namespace MACE::Data::inline Model::inline SimHit
