#pragma once

#include "MACE/Data/Model/Field.h++"
#include "MACE/Data/Model/FieldSet.h++"
#include "MACE/Data/Model/Hit/HitBasis.h++"
#include "MACE/Data/Model/Modelled.h++"

#include <string_view>

namespace MACE::Data::inline Model::inline Hit {

class EMCalHit : public Modelled<EMCalHit,
                                 std::tuple<HitBasis>,
                                 std::tuple<FieldSet<EMCalHit,
                                                     Field<float>>>> {
public:
    using EnergyDeposition = LocalField<0>;

    static constexpr auto BasicName() -> std::string_view { return "EMCalHit"; }

public:
    class Entry : public Modelled::Entry {
    public:
        virtual ~Entry() override = default;

        [[nodiscard]] auto EnergyDeposition() const -> decltype(auto) { return Get<EMCalHit::EnergyDeposition>(); }

        [[nodiscard]] auto EnergyDeposition() -> decltype(auto) { return Get<EMCalHit::EnergyDeposition>(); }
    };
};

} // namespace MACE::Data::inline Model::inline Hit

MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(EMCalHit::EnergyDeposition, "E", "Energy Deposition")
