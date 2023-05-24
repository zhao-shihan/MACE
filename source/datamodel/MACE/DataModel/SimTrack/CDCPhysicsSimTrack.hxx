#pragma once

#include "MACE/DataModel/Field/FundamentalField.hxx"
#include "MACE/DataModel/Field/VectorField.hxx"
#include "MACE/DataModel/SimTrack/CDCSimTrackBase.hxx"
#include "MACE/DataModel/Track/CDCPhysicsTrack.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace SimTrack {

using namespace std::string_view_literals;

class CDCPhysicsSimTrack : public CDCPhysicsTrack,
                           public CDCSimTrackBase {
public:
    struct Field : CDCPhysicsTrack::Field,
                   CDCSimTrackBase::Field {
        using VertexPositionTruth = Vector3FField<CDCPhysicsSimTrack, 0, stdx::array3d>;
        using VertexKineticEnergyTruth = FloatField<CDCPhysicsSimTrack, 1, double>;
        using VertexMomentumTruth = Vector3FField<CDCPhysicsSimTrack, 2, stdx::array3d>;
    };

public:
    virtual ~CDCPhysicsSimTrack() override = default;

    [[nodiscard]] const auto& VertexPositionTruth() const& { return fVertexPositionTruth; }
    [[nodiscard]] const auto& VertexKineticEnergyTruth() const& { return fVertexKineticEnergyTruth; }
    [[nodiscard]] const auto& VertexMomentumTruth() const& { return fVertexMomentumTruth; }

    [[nodiscard]] auto& VertexPositionTruth() & { return fVertexPositionTruth; }
    [[nodiscard]] auto& VertexKineticEnergyTruth() & { return fVertexKineticEnergyTruth; }
    [[nodiscard]] auto& VertexMomentumTruth() & { return fVertexMomentumTruth; }

    static constexpr auto BasicTreeName() { return "CDCPhysicsSimTrack"sv; }

    inline void FillAllBranchSocket() const&;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);

private:
    Field::VertexPositionTruth fVertexPositionTruth;
    Field::VertexKineticEnergyTruth fVertexKineticEnergyTruth;
    Field::VertexMomentumTruth fVertexMomentumTruth;
};
static_assert(TransientData<CDCPhysicsSimTrack>);

} // namespace SimTrack

template<>
CDCPhysicsSimTrack::Field::VertexPositionTruth::BranchSocket CDCPhysicsSimTrack::Field::VertexPositionTruth::Base::fgBranchSocket;
template<>
CDCPhysicsSimTrack::Field::VertexKineticEnergyTruth::BranchSocket CDCPhysicsSimTrack::Field::VertexKineticEnergyTruth::Base::fgBranchSocket;
template<>
CDCPhysicsSimTrack::Field::VertexMomentumTruth::BranchSocket CDCPhysicsSimTrack::Field::VertexMomentumTruth::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimTrack/CDCPhysicsSimTrack.inl"
