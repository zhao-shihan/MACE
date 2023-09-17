#pragma once

#include "MACE/Data/Model/Field.h++"
#include "MACE/Data/Model/FieldSet.h++"
#include "MACE/Data/Model/ModelSegment.h++"

namespace MACE::Data::inline Model::inline Track {

class CDCTrackBasis : public ModelSegment<CDCTrackBasis,
                                          std::tuple<>,
                                          std::tuple<FieldSet<CDCTrackBasis,
                                                              Field<int>,
                                                              Field<int>,
                                                              Field<float>,
                                                              Field<double>>>> {
public:
    using PDGCode = Field<0>;
    using NHit = Field<1>;
    using Chi2 = Field<2>;
    using VertexTime = Field<3>;

public:
    class Entry : public FieldSet::Entry {
    public:
        auto PDGCode() const -> decltype(auto) { return Get<CDCTrackBasis::PDGCode>(); }
        auto NHit() const -> decltype(auto) { return Get<CDCTrackBasis::NHit>(); }
        auto Chi2() const -> decltype(auto) { return Get<CDCTrackBasis::Chi2>(); }
        auto VertexTime() const -> decltype(auto) { return Get<CDCTrackBasis::VertexTime>(); }

        auto PDGCode() -> decltype(auto) { return Get<CDCTrackBasis::PDGCode>(); }
        auto NHit() -> decltype(auto) { return Get<CDCTrackBasis::NHit>(); }
        auto Chi2() -> decltype(auto) { return Get<CDCTrackBasis::Chi2>(); }
        auto VertexTime() -> decltype(auto) { return Get<CDCTrackBasis::VertexTime>(); }
    };
};

} // namespace MACE::Data::inline Model::inline Track

MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCTrackBasis::PDGCode, "pdgCode", "Particle PDG Code")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCTrackBasis::NHit, "nHit", "Number of Hits Fitted")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCTrackBasis::Chi2, "chi2", "Fitting chi^{2}")
MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(CDCTrackBasis::VertexTime, "t0", "Vertex Time")
