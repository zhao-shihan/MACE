#pragma once

#include "MACE/Data/Model/Hit/EMCalHit.h++"
#include "MACE/Data/Model/Modelled.h++"
#include "MACE/Data/Model/SimHit/SimHitBasis.h++"

#include <string_view>

namespace MACE::Data::inline Model::inline SimHit {

class EMCalSimHit : public Modelled<EMCalSimHit,
                                    std::tuple<EMCalHit,
                                               SimHitBasis>,
                                    std::tuple<>> {
public:
    static constexpr auto BasicName() -> std::string_view { return "EMCalSimHit"; }

public:
    class Entry : public Modelled::Entry {
    public:
        virtual ~Entry() override = default;
    };
};

} // namespace MACE::Data::inline Model::inline SimHit
