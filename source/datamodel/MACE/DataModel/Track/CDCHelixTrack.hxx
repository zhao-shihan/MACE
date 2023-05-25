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

class CDCHelixTrack : public CDCTrackBase {
public:
    struct Column : CDCTrackBase::Column {
        using Center = Vector2FColumn<CDCHelixTrack, 0, stdx::array2d>;
        using Radius = FloatColumn<CDCHelixTrack, 1, double>;
        using VertexZ = FloatColumn<CDCHelixTrack, 2, double>;
        using Theta = FloatColumn<CDCHelixTrack, 3, double>;
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
    Column::Center fCenter;
    Column::Radius fRadius;
    Column::VertexZ fVertexZ;
    Column::Theta fTheta;
};
static_assert(TransientData<CDCHelixTrack>);

} // namespace Track

template<>
CDCHelixTrack::Column::Center::BranchSocket CDCHelixTrack::Column::Center::Base::fgBranchSocket;
template<>
CDCHelixTrack::Column::Radius::BranchSocket CDCHelixTrack::Column::Radius::Base::fgBranchSocket;
template<>
CDCHelixTrack::Column::VertexZ::BranchSocket CDCHelixTrack::Column::VertexZ::Base::fgBranchSocket;
template<>
CDCHelixTrack::Column::Theta::BranchSocket CDCHelixTrack::Column::Theta::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Track/CDCHelixTrack.inl"
