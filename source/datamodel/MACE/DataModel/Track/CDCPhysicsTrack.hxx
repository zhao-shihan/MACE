#pragma once

#include "MACE/DataModel/Field/FundamentalField.hxx"
#include "MACE/DataModel/Field/VectorField.hxx"
#include "MACE/DataModel/Track/CDCTrackBase.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace Track {

using namespace std::string_view_literals;

class CDCPhysicsTrack : public CDCTrackBase {
public:
    struct Field : CDCTrackBase::Field {
        using VertexPosition = Vector3FField<CDCPhysicsTrack, 0, stdx::array3d>;
        using VertexKineticEnergy = FloatField<CDCPhysicsTrack, 1, double>;
        using VertexMomentum = Vector3FField<CDCPhysicsTrack, 2, stdx::array3d>;
    };

public:
    virtual ~CDCPhysicsTrack() = default;

    [[nodiscard]] const auto& VertexPosition() const& { return fVertexPosition; }
    [[nodiscard]] const auto& VertexKineticEnergy() const& { return fVertexKineticEnergy; }
    [[nodiscard]] const auto& VertexMomentum() const& { return fVertexMomentum; }

    [[nodiscard]] auto& VertexPosition() & { return fVertexPosition; }
    [[nodiscard]] auto& VertexKineticEnergy() & { return fVertexKineticEnergy; }
    [[nodiscard]] auto& VertexMomentum() & { return fVertexMomentum; }

    static constexpr auto BasicTreeName() { return "CDCPhysicsTrack"sv; }

    inline void FillAllBranchSocket() const&;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);

private:
    Field::VertexPosition fVertexPosition;
    Field::VertexKineticEnergy fVertexKineticEnergy;
    Field::VertexMomentum fVertexMomentum;
};
static_assert(TransientData<CDCPhysicsTrack>);

} // namespace Track

template<>
CDCPhysicsTrack::Field::VertexPosition::BranchSocket CDCPhysicsTrack::Field::VertexPosition::Base::fgBranchSocket;
template<>
CDCPhysicsTrack::Field::VertexKineticEnergy::BranchSocket CDCPhysicsTrack::Field::VertexKineticEnergy::Base::fgBranchSocket;
template<>
CDCPhysicsTrack::Field::VertexMomentum::BranchSocket CDCPhysicsTrack::Field::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Track/CDCPhysicsTrack.inl"
