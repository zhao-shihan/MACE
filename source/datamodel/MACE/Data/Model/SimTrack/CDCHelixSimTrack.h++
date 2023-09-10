#pragma once

#include "MACE/Data/Model/Field.h++"
#include "MACE/Data/Model/FieldSet.h++"
#include "MACE/Data/Model/Modelled.h++"
#include "MACE/Data/Model/SimTrack/CDCSimTrackBasis.h++"
#include "MACE/Data/Model/Track/CDCHelixTrack.h++"
#include "MACE/Extension/stdx/arraynx.h++"

#include <string_view>

namespace MACE::Data::inline Model::inline SimTrack {

class CDCHelixSimTrack : public Modelled<CDCHelixSimTrack,
                                         std::tuple<CDCHelixTrack,
                                                    CDCSimTrackBasis>,
                                         std::tuple<FieldSet<CDCHelixSimTrack,
                                                             Field<stdx::array2f>,
                                                             Field<float>,
                                                             Field<float>,
                                                             Field<float>>>> {
public:
    using CenterTruth = LocalField<0>;
    using RadiusTruth = LocalField<1>;
    using VertexZTruth = LocalField<2>;
    using ThetaTruth = LocalField<3>;

    static constexpr auto BasicName() -> std::string_view { return "CDCHelixSimTrack"; }

public:
    class Entry : public Modelled::Entry {
    public:
        virtual ~Entry() override = default;

        auto CenterTruth() const -> decltype(auto) { return Get<CDCHelixSimTrack::CenterTruth>(); }
        auto RadiusTruth() const -> decltype(auto) { return Get<CDCHelixSimTrack::RadiusTruth>(); }
        auto VertexZTruth() const -> decltype(auto) { return Get<CDCHelixSimTrack::VertexZTruth>(); }
        auto ThetaTruth() const -> decltype(auto) { return Get<CDCHelixSimTrack::ThetaTruth>(); }

        auto CenterTruth() -> decltype(auto) { return Get<CDCHelixSimTrack::CenterTruth>(); }
        auto RadiusTruth() -> decltype(auto) { return Get<CDCHelixSimTrack::RadiusTruth>(); }
        auto VertexZTruth() -> decltype(auto) { return Get<CDCHelixSimTrack::VertexZTruth>(); }
        auto ThetaTruth() -> decltype(auto) { return Get<CDCHelixSimTrack::ThetaTruth>(); }
    };
};

} // namespace MACE::Data::inline Model::inline SimTrack

MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCHelixSimTrack::CenterTruth, "centerT", "Transverse Center (MC Truth)")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCHelixSimTrack::RadiusTruth, "rT", "Transverse Radius (MC Truth)")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCHelixSimTrack::VertexZTruth, "z0T", "Vertex Z Coordinate (MC Truth)")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCHelixSimTrack::ThetaTruth, "thetaT", "Polar Angle (MC Truth)")
