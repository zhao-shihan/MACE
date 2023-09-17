#pragma once

#include "MACE/Data/Model/Field.h++"
#include "MACE/Data/Model/FieldSet.h++"
#include "MACE/Data/Model/Hit/HitBasis.h++"
#include "MACE/Data/Model/Modelize.h++"

#include <string_view>

namespace MACE::Data::inline Model::inline Hit {

class EMCHit : public Modelize<EMCHit,
                                 std::tuple<HitBasis>,
                                 std::tuple<FieldSet<EMCHit,
                                                     Field<float>>>> {
public:
    using EnergyDeposition = LocalField<0>;

    static constexpr auto BasicName() -> std::string_view { return "EMCHit"; }

public:
    class Entry : public Modelize::Entry {
    public:
        virtual ~Entry() override = default;

        auto EnergyDeposition() const -> decltype(auto) { return Get<EMCHit::EnergyDeposition>(); }

        auto EnergyDeposition() -> decltype(auto) { return Get<EMCHit::EnergyDeposition>(); }
    };
};

} // namespace MACE::Data::inline Model::inline Hit

MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(EMCHit::EnergyDeposition, "E", "Energy Deposition")
