#pragma once

#include "MACE/DataModel/Column/FundamentalColumn.hxx"
#include "MACE/DataModel/Column/VectorColumn.hxx"
#include "MACE/DataModel/SimTrack/CDCSimTrackBase.hxx"
#include "MACE/DataModel/Track/CDCHelixTrack.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace SimTrack {

using namespace std::string_view_literals;

class CDCHelixSimTrack : public CDCHelixTrack,
                         public CDCSimTrackBase {
public:
    struct Column : CDCSimTrackBase::Column {
        using CenterTruth = Vector2FColumn<CDCHelixSimTrack, 0, stdx::array2d>;
        using RadiusTruth = FloatColumn<CDCHelixSimTrack, 1, double>;
        using VertexZTruth = FloatColumn<CDCHelixSimTrack, 2, double>;
        using ThetaTruth = FloatColumn<CDCHelixSimTrack, 3, double>;
    };

public:
    virtual ~CDCHelixSimTrack() = default;

    [[nodiscard]] auto& CenterTruth() & { return fCenterTruth; }
    [[nodiscard]] auto& RadiusTruth() & { return fRadiusTruth; }
    [[nodiscard]] auto& VertexZTruth() & { return fVertexZTruth; }
    [[nodiscard]] auto& ThetaTruth() & { return fThetaTruth; }

    [[nodiscard]] const auto& CenterTruth() const& { return fCenterTruth; }
    [[nodiscard]] const auto& RadiusTruth() const& { return fRadiusTruth; }
    [[nodiscard]] const auto& VertexZTruth() const& { return fVertexZTruth; }
    [[nodiscard]] const auto& ThetaTruth() const& { return fThetaTruth; }

    static constexpr auto BasicTreeName() { return "CDCHelixSimTrack"sv; }

    inline void FillAllBranchSocket() const&;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);

private:
    Column::CenterTruth fCenterTruth;
    Column::RadiusTruth fRadiusTruth;
    Column::VertexZTruth fVertexZTruth;
    Column::ThetaTruth fThetaTruth;
};
static_assert(TransientData<CDCHelixSimTrack>);

} // namespace SimTrack

template<>
CDCHelixSimTrack::Column::CenterTruth::BranchSocket CDCHelixSimTrack::Column::CenterTruth::Base::fgBranchSocket;
template<>
CDCHelixSimTrack::Column::RadiusTruth::BranchSocket CDCHelixSimTrack::Column::RadiusTruth::Base::fgBranchSocket;
template<>
CDCHelixSimTrack::Column::VertexZTruth::BranchSocket CDCHelixSimTrack::Column::VertexZTruth::Base::fgBranchSocket;
template<>
CDCHelixSimTrack::Column::ThetaTruth::BranchSocket CDCHelixSimTrack::Column::ThetaTruth::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimTrack/CDCHelixSimTrack.inl"
