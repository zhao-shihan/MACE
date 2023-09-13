#pragma once

#include "MACE/Data/Model/Field.h++"
#include "MACE/Data/Model/FieldSet.h++"
#include "MACE/Data/Model/Modelize.h++"
#include "MACE/Data/Model/Track/CDCTrackBasis.h++"
#include "MACE/Extension/stdx/arraynx.h++"

#include <string_view>

namespace MACE::Data::inline Model::inline Track {

class CDCPhysicsTrack : public Modelize<CDCPhysicsTrack,
                                        std::tuple<CDCTrackBasis>,
                                        std::tuple<FieldSet<CDCPhysicsTrack,
                                                            Field<stdx::array3f>,
                                                            Field<float>,
                                                            Field<stdx::array3f>>>> {
public:
    using VertexPosition = LocalField<0>;
    using VertexKineticEnergy = LocalField<1>;
    using VertexMomentum = LocalField<2>;

    static constexpr auto BasicName() -> std::string_view { return "CDCPhysicsTrack"; }

public:
    class Entry : public Modelize::Entry {
    public:
        virtual ~Entry() override = default;

        auto VertexPosition() const -> decltype(auto) { return Get<CDCPhysicsTrack::VertexPosition>(); }
        auto VertexKineticEnergy() const -> decltype(auto) { return Get<CDCPhysicsTrack::VertexKineticEnergy>(); }
        auto VertexMomentum() const -> decltype(auto) { return Get<CDCPhysicsTrack::VertexMomentum>(); }

        auto VertexPosition() -> decltype(auto) { return Get<CDCPhysicsTrack::VertexPosition>(); }
        auto VertexKineticEnergy() -> decltype(auto) { return Get<CDCPhysicsTrack::VertexKineticEnergy>(); }
        auto VertexMomentum() -> decltype(auto) { return Get<CDCPhysicsTrack::VertexMomentum>(); }
    };
};

} // namespace MACE::Data::inline Model::inline Track

MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCPhysicsTrack::VertexPosition, "x0", "Vertex Position")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCPhysicsTrack::VertexKineticEnergy, "Ek0", "Vertex Kinetic Energy")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCPhysicsTrack::VertexMomentum, "p0", "Vertex Momentum")
