#pragma once

#include "MACE/Data/Model/Field.h++"
#include "MACE/Data/Model/FieldSet.h++"
#include "MACE/Data/Model/Hit/HitBasis.h++"
#include "MACE/Data/Model/Modelled.h++"

#include <string_view>

namespace MACE::Data::inline Model::inline Hit {

class CDCHit : public Modelled<CDCHit,
                               std::tuple<HitBasis>,
                               std::tuple<FieldSet<CDCHit,
                                                   Field<int>,
                                                   Field<float>>>> {
public:
    using CellID = LocalField<0>;
    using DriftDistance = LocalField<1>;

    static constexpr auto BasicName() -> std::string_view { return "CDCHit"; }

public:
    class Entry : public Modelled::Entry {
    public:
        [[nodiscard]] auto CellID() const -> decltype(auto) { return Get<CDCHit::CellID>(); }
        [[nodiscard]] auto DriftDistance() const -> decltype(auto) { return Get<CDCHit::DriftDistance>(); }

        [[nodiscard]] auto CellID() -> decltype(auto) { return Get<CDCHit::CellID>(); }
        [[nodiscard]] auto DriftDistance() -> decltype(auto) { return Get<CDCHit::DriftDistance>(); }
    };
};

} // namespace MACE::Data::inline Model::inline Hit

MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCHit::CellID, "cellID", "Hitting Cell ID")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCHit::DriftDistance, "d", "Drift Distance")
