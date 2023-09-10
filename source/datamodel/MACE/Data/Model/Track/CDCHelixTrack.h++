#pragma once

#include "MACE/Data/Model/Field.h++"
#include "MACE/Data/Model/FieldSet.h++"
#include "MACE/Data/Model/Modelled.h++"
#include "MACE/Data/Model/Track/CDCTrackBasis.h++"
#include "MACE/Extension/stdx/arraynx.h++"

#include <string_view>

namespace MACE::Data::inline Model::inline Track {

class CDCHelixTrack : public Modelled<CDCHelixTrack,
                                      std::tuple<CDCTrackBasis>,
                                      std::tuple<FieldSet<CDCHelixTrack,
                                                          Field<stdx::array2f>,
                                                          Field<float>,
                                                          Field<float>,
                                                          Field<float>>>> {
public:
    using Center = LocalField<0>;
    using Radius = LocalField<1>;
    using VertexZ = LocalField<2>;
    using Theta = LocalField<3>;

    static constexpr auto BasicName() -> std::string_view { return "CDCHelixTrack"; }

public:
    class Entry : public Modelled::Entry {
    public:
        virtual ~Entry() override = default;

        auto Center() const -> decltype(auto) { return Get<CDCHelixTrack::Center>(); }
        auto Radius() const -> decltype(auto) { return Get<CDCHelixTrack::Radius>(); }
        auto VertexZ() const -> decltype(auto) { return Get<CDCHelixTrack::VertexZ>(); }
        auto Theta() const -> decltype(auto) { return Get<CDCHelixTrack::Theta>(); }

        auto Center() -> decltype(auto) { return Get<CDCHelixTrack::Center>(); }
        auto Radius() -> decltype(auto) { return Get<CDCHelixTrack::Radius>(); }
        auto VertexZ() -> decltype(auto) { return Get<CDCHelixTrack::VertexZ>(); }
        auto Theta() -> decltype(auto) { return Get<CDCHelixTrack::Theta>(); }
    };
};

} // namespace MACE::Data::inline Model::inline Track

MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCHelixTrack::Center, "center", "Transverse Center")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCHelixTrack::Radius, "r", "Transverse Radius")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCHelixTrack::VertexZ, "z0", "Vertex Z Coordinate")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCHelixTrack::Theta, "theta", "Polar Angle")
