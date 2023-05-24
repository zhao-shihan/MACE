#pragma once

#include "MACE/DataModel/Field/FundamentalField.hxx"
#include "MACE/DataModel/Field/VectorField.hxx"
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
    struct Field : CDCSimTrackBase::Field {
        using CenterTruth = Vector2FField<CDCHelixSimTrack, 0, stdx::array2d>;
        using RadiusTruth = FloatField<CDCHelixSimTrack, 1, double>;
        using VertexZTruth = FloatField<CDCHelixSimTrack, 2, double>;
        using ThetaTruth = FloatField<CDCHelixSimTrack, 3, double>;
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
    Field::CenterTruth fCenterTruth;
    Field::RadiusTruth fRadiusTruth;
    Field::VertexZTruth fVertexZTruth;
    Field::ThetaTruth fThetaTruth;
};
static_assert(TransientData<CDCHelixSimTrack>);

} // namespace SimTrack

template<>
CDCHelixSimTrack::Field::CenterTruth::BranchSocket CDCHelixSimTrack::Field::CenterTruth::Base::fgBranchSocket;
template<>
CDCHelixSimTrack::Field::RadiusTruth::BranchSocket CDCHelixSimTrack::Field::RadiusTruth::Base::fgBranchSocket;
template<>
CDCHelixSimTrack::Field::VertexZTruth::BranchSocket CDCHelixSimTrack::Field::VertexZTruth::Base::fgBranchSocket;
template<>
CDCHelixSimTrack::Field::ThetaTruth::BranchSocket CDCHelixSimTrack::Field::ThetaTruth::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimTrack/CDCHelixSimTrack.inl"
