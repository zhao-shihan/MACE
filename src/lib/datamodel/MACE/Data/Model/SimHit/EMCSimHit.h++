#pragma once

#include "MACE/Data/Model/Hit/EMCHit.h++"
#include "MACE/Data/Model/Modelize.h++"
#include "MACE/Data/Model/SimHit/SimHitBasis.h++"

#include <string_view>

namespace MACE::Data::inline Model::inline SimHit {

class EMCSimHit : public Modelize<EMCSimHit,
                                    std::tuple<EMCHit,
                                               SimHitBasis>,
                                    std::tuple<>> {
public:
    static constexpr auto BasicName() -> std::string_view { return "EMCSimHit"; }

public:
    class Entry : public Modelize::Entry {
    public:
        virtual ~Entry() override = default;
    };
};

} // namespace MACE::Data::inline Model::inline SimHit
