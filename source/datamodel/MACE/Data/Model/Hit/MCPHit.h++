#pragma once

#include "MACE/Data/Model/Field.h++"
#include "MACE/Data/Model/FieldSet.h++"
#include "MACE/Data/Model/Hit/HitBasis.h++"
#include "MACE/Data/Model/Modelled.h++"
#include "MACE/Extension/stdx/arraynx.h++"

#include <string_view>

namespace MACE::Data::inline Model::inline Hit {

class MCPHit : public Modelled<MCPHit,
                               std::tuple<HitBasis>,
                               std::tuple<FieldSet<MCPHit,
                                                   Field<stdx::array2f>>>> {
public:
    using Position = LocalField<0>;

    static constexpr auto BasicName() -> std::string_view { return "MCPHit"; }

public:
    class Entry : public Modelled::Entry {
    public:
        virtual ~Entry() override = default;

        [[nodiscard]] auto Position() const -> decltype(auto) { return Get<MCPHit::Position>(); }

        [[nodiscard]] auto Position() -> decltype(auto) { return Get<MCPHit::Position>(); }
    };
};

} // namespace MACE::Data::inline Model::inline Hit

MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(MCPHit::Position, "x", "Hitting Position")
