#pragma once

#include "MACE/Data/Model/Field.h++"
#include "MACE/Data/Model/FieldSet.h++"

namespace MACE::Data::inline Model::inline SimTrack {

class CDCSimTrackBasis : public FieldSet<CDCSimTrackBasis,
                                         Field<int>,
                                         Field<int>,
                                         Field<double>> {
public:
    using PDGCodeTruth = Field<0>;
    using NHitTruth = Field<1>;
    using VertexTimeTruth = Field<2>;

public:
    class Entry : public FieldSet::Entry {
    public:
        auto PDGCodeTruth() const -> decltype(auto) { return Get<CDCSimTrackBasis::PDGCodeTruth>(); }
        auto NHitTruth() const -> decltype(auto) { return Get<CDCSimTrackBasis::NHitTruth>(); }
        auto VertexTimeTruth() const -> decltype(auto) { return Get<CDCSimTrackBasis::VertexTimeTruth>(); }

        auto PDGCodeTruth() -> decltype(auto) { return Get<CDCSimTrackBasis::PDGCodeTruth>(); }
        auto NHitTruth() -> decltype(auto) { return Get<CDCSimTrackBasis::NHitTruth>(); }
        auto VertexTimeTruth() -> decltype(auto) { return Get<CDCSimTrackBasis::VertexTimeTruth>(); }
    };
};

} // namespace MACE::Data::inline Model::inline SimTrack

MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCSimTrackBasis::PDGCodeTruth, "pdgCodeT", "Particle PDG Code (MC Truth)")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCSimTrackBasis::NHitTruth, "nHitT", "Number of Hits (MC Truth)")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCSimTrackBasis::VertexTimeTruth, "t0T", "Vertex Time (MC Truth)")
