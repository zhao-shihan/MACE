#pragma once

#include "MACE/DataModel/Column/FundamentalColumn.hxx"
#include "MACE/DataModel/Column/VectorColumn.hxx"
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
    struct Column : CDCPhysicsTrack::Column,
                   CDCSimTrackBase::Column {
        using VertexPositionTruth = Vector3FColumn<CDCPhysicsSimTrack, 0, stdx::array3d>;
        using VertexKineticEnergyTruth = FloatColumn<CDCPhysicsSimTrack, 1, double>;
        using VertexMomentumTruth = Vector3FColumn<CDCPhysicsSimTrack, 2, stdx::array3d>;
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
    Column::VertexPositionTruth fVertexPositionTruth;
    Column::VertexKineticEnergyTruth fVertexKineticEnergyTruth;
    Column::VertexMomentumTruth fVertexMomentumTruth;
};
static_assert(TransientData<CDCPhysicsSimTrack>);

} // namespace SimTrack

template<>
CDCPhysicsSimTrack::Column::VertexPositionTruth::BranchSocket CDCPhysicsSimTrack::Column::VertexPositionTruth::Base::fgBranchSocket;
template<>
CDCPhysicsSimTrack::Column::VertexKineticEnergyTruth::BranchSocket CDCPhysicsSimTrack::Column::VertexKineticEnergyTruth::Base::fgBranchSocket;
template<>
CDCPhysicsSimTrack::Column::VertexMomentumTruth::BranchSocket CDCPhysicsSimTrack::Column::VertexMomentumTruth::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimTrack/CDCPhysicsSimTrack.inl"
