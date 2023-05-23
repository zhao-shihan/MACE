#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/Entry/VectorEntry.hxx"
#include "MACE/DataModel/Track/CDCTrackBase.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace Track {

using namespace std::string_view_literals;

class CDCPhysicsTrack : public CDCTrackBase {
public:
    struct Entry : CDCTrackBase::Entry {
        using VertexPosition = Vector3FEntry<CDCPhysicsTrack, 0, stdx::array3d>;
        using VertexKineticEnergy = FloatEntry<CDCPhysicsTrack, 1, double>;
        using VertexMomentum = Vector3FEntry<CDCPhysicsTrack, 2, stdx::array3d>;
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
    Entry::VertexPosition fVertexPosition;
    Entry::VertexKineticEnergy fVertexKineticEnergy;
    Entry::VertexMomentum fVertexMomentum;
};
static_assert(TransientData<CDCPhysicsTrack>);

} // namespace Track

template<>
CDCPhysicsTrack::Entry::VertexPosition::BranchSocket CDCPhysicsTrack::Entry::VertexPosition::Base::fgBranchSocket;
template<>
CDCPhysicsTrack::Entry::VertexKineticEnergy::BranchSocket CDCPhysicsTrack::Entry::VertexKineticEnergy::Base::fgBranchSocket;
template<>
CDCPhysicsTrack::Entry::VertexMomentum::BranchSocket CDCPhysicsTrack::Entry::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Track/CDCPhysicsTrack.inl"
