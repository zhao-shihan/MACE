#pragma once

#include "MACE/Data/Model/Field.h++"
#include "MACE/Data/Model/FieldSet.h++"
#include "MACE/Data/Model/ModelSegment.h++"
#include "MACE/Data/Model/SimBasis.h++"
#include "MACE/Extension/stdx/arraynx.h++"

namespace MACE::Data::inline Model::inline SimHit {

class SimHitBasis : public ModelSegment<SimHitBasis,
                                        std::tuple<>,
                                        std::tuple<FieldSet<SimHitBasis,
                                                            Field<int>,
                                                            Field<int>,
                                                            Field<int>,
                                                            Field<float>,
                                                            Field<stdx::array3f>,
                                                            Field<double>,
                                                            Field<stdx::array3f>,
                                                            Field<float>,
                                                            Field<stdx::array3f>>>> {
public:
    using MCEventID = Field<0>;
    using MCTrackID = Field<1>;
    using PDGCode = Field<2>;
    using KineticEnergy = Field<3>;
    using Momentum = Field<4>;
    using VertexTime = Field<5>;
    using VertexPosition = Field<6>;
    using VertexKineticEnergy = Field<7>;
    using VertexMomentum = Field<8>;

public:
    class Entry : public ModelSegment::Entry {
    public:
        auto MCEventID() const -> decltype(auto) { return Get<SimHitBasis::MCEventID>(); }
        auto MCTrackID() const -> decltype(auto) { return Get<SimHitBasis::MCTrackID>(); }
        auto PDGCode() const -> decltype(auto) { return Get<SimHitBasis::PDGCode>(); }
        auto KineticEnergy() const -> decltype(auto) { return Get<SimHitBasis::KineticEnergy>(); }
        auto Momentum() const -> decltype(auto) { return Get<SimHitBasis::Momentum>(); }
        auto VertexTime() const -> decltype(auto) { return Get<SimHitBasis::VertexTime>(); }
        auto VertexPosition() const -> decltype(auto) { return Get<SimHitBasis::VertexPosition>(); }
        auto VertexKineticEnergy() const -> decltype(auto) { return Get<SimHitBasis::VertexKineticEnergy>(); }
        auto VertexMomentum() const -> decltype(auto) { return Get<SimHitBasis::VertexMomentum>(); }

        auto MCEventID() -> decltype(auto) { return Get<SimHitBasis::MCEventID>(); }
        auto MCTrackID() -> decltype(auto) { return Get<SimHitBasis::MCTrackID>(); }
        auto PDGCode() -> decltype(auto) { return Get<SimHitBasis::PDGCode>(); }
        auto KineticEnergy() -> decltype(auto) { return Get<SimHitBasis::KineticEnergy>(); }
        auto Momentum() -> decltype(auto) { return Get<SimHitBasis::Momentum>(); }
        auto VertexTime() -> decltype(auto) { return Get<SimHitBasis::VertexTime>(); }
        auto VertexPosition() -> decltype(auto) { return Get<SimHitBasis::VertexPosition>(); }
        auto VertexKineticEnergy() -> decltype(auto) { return Get<SimHitBasis::VertexKineticEnergy>(); }
        auto VertexMomentum() -> decltype(auto) { return Get<SimHitBasis::VertexMomentum>(); }
    };
};

} // namespace MACE::Data::inline Model::inline SimHit

MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(SimHitBasis::MCEventID, "mcEvtID", "MC Event ID")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(SimHitBasis::MCTrackID, "mcTrkID", "MC Track ID")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(SimHitBasis::PDGCode, "pdgCode", "Particle PDG Code (MC Truth)")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(SimHitBasis::KineticEnergy, "Ek", "Hitting Kinetic Energy (MC Truth)")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(SimHitBasis::Momentum, "p", "Hitting Momentum (MC Truth)")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(SimHitBasis::VertexTime, "t0", "Vertex Time (MC Truth)")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(SimHitBasis::VertexPosition, "x0", "Vertex Position (MC Truth)")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(SimHitBasis::VertexKineticEnergy, "Ek0", "Vertex Kinetic Energy (MC Truth)")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(SimHitBasis::VertexMomentum, "p0", "Vertex Momentum (MC Truth)")
