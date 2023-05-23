#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/Entry/VectorEntry.hxx"
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
    struct Entry : CDCSimTrackBase::Entry {
        using CenterTruth = Vector2FEntry<CDCHelixSimTrack, 0, stdx::array2d>;
        using RadiusTruth = FloatEntry<CDCHelixSimTrack, 1, double>;
        using VertexZTruth = FloatEntry<CDCHelixSimTrack, 2, double>;
        using ThetaTruth = FloatEntry<CDCHelixSimTrack, 3, double>;
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
    Entry::CenterTruth fCenterTruth;
    Entry::RadiusTruth fRadiusTruth;
    Entry::VertexZTruth fVertexZTruth;
    Entry::ThetaTruth fThetaTruth;
};
static_assert(TransientData<CDCHelixSimTrack>);

} // namespace SimTrack

template<>
CDCHelixSimTrack::Entry::CenterTruth::BranchSocket CDCHelixSimTrack::Entry::CenterTruth::Base::fgBranchSocket;
template<>
CDCHelixSimTrack::Entry::RadiusTruth::BranchSocket CDCHelixSimTrack::Entry::RadiusTruth::Base::fgBranchSocket;
template<>
CDCHelixSimTrack::Entry::VertexZTruth::BranchSocket CDCHelixSimTrack::Entry::VertexZTruth::Base::fgBranchSocket;
template<>
CDCHelixSimTrack::Entry::ThetaTruth::BranchSocket CDCHelixSimTrack::Entry::ThetaTruth::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimTrack/CDCHelixSimTrack.inl"
