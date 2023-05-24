#pragma once

#include "MACE/DataModel/Field/FundamentalField.hxx"
#include "MACE/DataModel/Field/VectorField.hxx"
#include "MACE/DataModel/Track/CDCTrackBase.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace Track {

using namespace std::string_view_literals;

class CDCHelixTrack : public CDCTrackBase {
public:
    struct Field : CDCTrackBase::Field {
        using Center = Vector2FField<CDCHelixTrack, 0, stdx::array2d>;
        using Radius = FloatField<CDCHelixTrack, 1, double>;
        using VertexZ = FloatField<CDCHelixTrack, 2, double>;
        using Theta = FloatField<CDCHelixTrack, 3, double>;
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
    Field::Center fCenter;
    Field::Radius fRadius;
    Field::VertexZ fVertexZ;
    Field::Theta fTheta;
};
static_assert(TransientData<CDCHelixTrack>);

} // namespace Track

template<>
CDCHelixTrack::Field::Center::BranchSocket CDCHelixTrack::Field::Center::Base::fgBranchSocket;
template<>
CDCHelixTrack::Field::Radius::BranchSocket CDCHelixTrack::Field::Radius::Base::fgBranchSocket;
template<>
CDCHelixTrack::Field::VertexZ::BranchSocket CDCHelixTrack::Field::VertexZ::Base::fgBranchSocket;
template<>
CDCHelixTrack::Field::Theta::BranchSocket CDCHelixTrack::Field::Theta::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Track/CDCHelixTrack.inl"
