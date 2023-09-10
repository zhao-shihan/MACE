#pragma once

#include "MACE/Data/Model/Field.h++"
#include "MACE/Data/Model/FieldSet.h++"

namespace MACE::Data::inline Model::inline Hit {

class HitBasis : public FieldSet<HitBasis,
                                 Field<double>> {
public:
    using Time = Field<0>;

public:
    class Entry : public FieldSet::Entry {
    public:
        auto Time() const -> decltype(auto) { return Get<HitBasis::Time>(); }

        auto Time() -> decltype(auto) { return Get<HitBasis::Time>(); }
    };
};

} // namespace MACE::Data::inline Model::inline Hit

MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(HitBasis::Time, "t", "Hitting Time")
