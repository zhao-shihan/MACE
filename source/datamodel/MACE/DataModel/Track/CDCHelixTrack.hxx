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

class CDCHelixTrack : public CDCTrackBase {
public:
    struct Entry : CDCTrackBase::Entry {
        using Center = Vector2FEntry<CDCHelixTrack, 0, stdx::array2d>;
        using Radius = FloatEntry<CDCHelixTrack, 1, double>;
        using VertexZ = FloatEntry<CDCHelixTrack, 2, double>;
        using Theta = FloatEntry<CDCHelixTrack, 3, double>;
    };

public:
    virtual ~CDCHelixTrack() = default;

    [[nodiscard]] auto& Center() & { return fCenter; }
    [[nodiscard]] auto& Radius() & { return fRadius; }
    [[nodiscard]] auto& VertexZ() & { return fVertexZ; }
    [[nodiscard]] auto& Theta() & { return fTheta; }

    [[nodiscard]] const auto& Center() const& { return fCenter; }
    [[nodiscard]] const auto& Radius() const& { return fRadius; }
    [[nodiscard]] const auto& VertexZ() const& { return fVertexZ; }
    [[nodiscard]] const auto& Theta() const& { return fTheta; }

    static constexpr auto BasicTreeName() { return "CDCHelixTrack"sv; }

    inline void FillAllBranchSocket() const&;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);

private:
    Entry::Center fCenter;
    Entry::Radius fRadius;
    Entry::VertexZ fVertexZ;
    Entry::Theta fTheta;
};
static_assert(TransientData<CDCHelixTrack>);

} // namespace Track

template<>
CDCHelixTrack::Entry::Center::BranchSocket CDCHelixTrack::Entry::Center::Base::fgBranchSocket;
template<>
CDCHelixTrack::Entry::Radius::BranchSocket CDCHelixTrack::Entry::Radius::Base::fgBranchSocket;
template<>
CDCHelixTrack::Entry::VertexZ::BranchSocket CDCHelixTrack::Entry::VertexZ::Base::fgBranchSocket;
template<>
CDCHelixTrack::Entry::Theta::BranchSocket CDCHelixTrack::Entry::Theta::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Track/CDCHelixTrack.inl"
