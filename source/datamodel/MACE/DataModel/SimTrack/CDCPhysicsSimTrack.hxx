#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/Entry/VectorEntry.hxx"
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
    struct Entry : CDCPhysicsTrack::Entry,
                   CDCSimTrackBase::Entry {
        using VertexPositionTruth = Vector3FEntry<CDCPhysicsSimTrack, 0, stdx::array3d>;
        using VertexKineticEnergyTruth = FloatEntry<CDCPhysicsSimTrack, 1, double>;
        using VertexMomentumTruth = Vector3FEntry<CDCPhysicsSimTrack, 2, stdx::array3d>;
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
    Entry::VertexPositionTruth fVertexPositionTruth;
    Entry::VertexKineticEnergyTruth fVertexKineticEnergyTruth;
    Entry::VertexMomentumTruth fVertexMomentumTruth;
};
static_assert(TransientData<CDCPhysicsSimTrack>);

} // namespace SimTrack

template<>
CDCPhysicsSimTrack::Entry::VertexPositionTruth::BranchSocket CDCPhysicsSimTrack::Entry::VertexPositionTruth::Base::fgBranchSocket;
template<>
CDCPhysicsSimTrack::Entry::VertexKineticEnergyTruth::BranchSocket CDCPhysicsSimTrack::Entry::VertexKineticEnergyTruth::Base::fgBranchSocket;
template<>
CDCPhysicsSimTrack::Entry::VertexMomentumTruth::BranchSocket CDCPhysicsSimTrack::Entry::VertexMomentumTruth::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimTrack/CDCPhysicsSimTrack.inl"
