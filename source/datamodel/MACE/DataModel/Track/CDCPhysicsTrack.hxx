#pragma once

#include "MACE/DataModel/Column/FundamentalColumn.hxx"
#include "MACE/DataModel/Column/VectorColumn.hxx"
#include "MACE/DataModel/Track/CDCTrackBase.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace Track {

using namespace std::string_view_literals;

class CDCPhysicsTrack : public CDCTrackBase {
public:
    struct Column : CDCTrackBase::Column {
        using VertexPosition = Vector3FColumn<CDCPhysicsTrack, 0, stdx::array3d>;
        using VertexKineticEnergy = FloatColumn<CDCPhysicsTrack, 1, double>;
        using VertexMomentum = Vector3FColumn<CDCPhysicsTrack, 2, stdx::array3d>;
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
    Column::VertexPosition fVertexPosition;
    Column::VertexKineticEnergy fVertexKineticEnergy;
    Column::VertexMomentum fVertexMomentum;
};
static_assert(TransientData<CDCPhysicsTrack>);

} // namespace Track

template<>
CDCPhysicsTrack::Column::VertexPosition::BranchSocket CDCPhysicsTrack::Column::VertexPosition::Base::fgBranchSocket;
template<>
CDCPhysicsTrack::Column::VertexKineticEnergy::BranchSocket CDCPhysicsTrack::Column::VertexKineticEnergy::Base::fgBranchSocket;
template<>
CDCPhysicsTrack::Column::VertexMomentum::BranchSocket CDCPhysicsTrack::Column::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Track/CDCPhysicsTrack.inl"
