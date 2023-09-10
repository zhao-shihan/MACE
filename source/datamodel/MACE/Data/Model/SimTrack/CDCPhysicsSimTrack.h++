#pragma once

#include "MACE/Data/Model/Field.h++"
#include "MACE/Data/Model/FieldSet.h++"
#include "MACE/Data/Model/Modelled.h++"
#include "MACE/Data/Model/SimTrack/CDCSimTrackBasis.h++"
#include "MACE/Data/Model/Track/CDCPhysicsTrack.h++"
#include "MACE/Extension/stdx/arraynx.h++"

#include <string_view>

namespace MACE::Data::inline Model::inline SimTrack {

class CDCPhysicsSimTrack : public Modelled<CDCPhysicsSimTrack,
                                           std::tuple<CDCPhysicsTrack,
                                                      CDCSimTrackBasis>,
                                           std::tuple<FieldSet<CDCPhysicsSimTrack,
                                                               Field<stdx::array3f>,
                                                               Field<float>,
                                                               Field<stdx::array3f>>>> {
public:
    using VertexPositionTruth = LocalField<0>;
    using VertexKineticEnergyTruth = LocalField<1>;
    using VertexMomentumTruth = LocalField<2>;

    static constexpr auto BasicName() -> std::string_view { return "CDCPhysicsSimTrack"; }

public:
    class Entry : public Modelled::Entry {
    public:
        virtual ~Entry() override = default;

        auto VertexPositionTruth() const -> decltype(auto) { return Get<CDCPhysicsSimTrack::VertexPositionTruth>(); }
        auto VertexKineticEnergyTruth() const -> decltype(auto) { return Get<CDCPhysicsSimTrack::VertexKineticEnergyTruth>(); }
        auto VertexMomentumTruth() const -> decltype(auto) { return Get<CDCPhysicsSimTrack::VertexMomentumTruth>(); }

        auto VertexPositionTruth() -> decltype(auto) { return Get<CDCPhysicsSimTrack::VertexPositionTruth>(); }
        auto VertexKineticEnergyTruth() -> decltype(auto) { return Get<CDCPhysicsSimTrack::VertexKineticEnergyTruth>(); }
        auto VertexMomentumTruth() -> decltype(auto) { return Get<CDCPhysicsSimTrack::VertexMomentumTruth>(); }
    };
};

} // namespace MACE::Data::inline Model::inline SimTrack

MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCPhysicsSimTrack::VertexPositionTruth, "x0T", "Vertex Position (MC Truth)")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCPhysicsSimTrack::VertexKineticEnergyTruth, "Ek0T", "Vertex Kinetic Energy (MC Truth)")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCPhysicsSimTrack::VertexMomentumTruth, "p0T", "Vertex Momentum (MC Truth)")
