/* #pragma once

#include "MACE/Data/Model/Field/BasicField.h++"
#include "MACE/Data/Model/FieldSet.h++"
#include "MACE/Data/Model/ModelBase.h++"

#include <array>
#include <string_view>

namespace MACE::Data::inline Model {

inline namespace Hit {

using namespace std::string_view_literals;

class CDCHit final : public ModelBase<CDCHit,
                                      std::tuple<>,
                                      std::tuple<FieldSet<CDCHit,
                                                          BasicField<int>,
                                                          BasicField<float>,
                                                          BasicField<double>,
                                                          // !!!!!!
                                                          BasicField<std::array<float, 2>>,
                                                          BasicField<std::vector<int>>,
                                                          BasicField<FixedString<15>>>>> {
public:
    using CellID = Field<0, FieldIndexMode::Relative>;
    using DriftDistance = Field<1, FieldIndexMode::Relative>;
    using Time = Field<2, FieldIndexMode::Relative>;

    static constexpr auto BasicName() { return "CDCHit"sv; }

public:
    class Entry : public ModelBase::Entry {
    public:
        [[nodiscard]] auto CellID() const -> decltype(auto) { return Get<CDCHit::CellID>(); }
        [[nodiscard]] auto DriftDistance() const -> decltype(auto) { return Get<CDCHit::DriftDistance>(); }
        [[nodiscard]] auto Time() const -> decltype(auto) { return Get<CDCHit::Time>(); }

        [[nodiscard]] auto CellID() -> decltype(auto) { return Get<CDCHit::CellID>(); }
        [[nodiscard]] auto DriftDistance() -> decltype(auto) { return Get<CDCHit::DriftDistance>(); }
        [[nodiscard]] auto Time() -> decltype(auto) { return Get<CDCHit::Time>(); }
    };
};

} // namespace Hit

inline namespace Field {

MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCHit::CellID)
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCHit::DriftDistance)
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCHit::Time)

} // namespace Field

} // namespace MACE::Data::inline Model
 */