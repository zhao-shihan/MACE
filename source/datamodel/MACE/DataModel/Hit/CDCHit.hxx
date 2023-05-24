#pragma once

#include "MACE/DataModel/Field/FundamentalField.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Utility/NonConstructibleBase.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace Hit {

using namespace std::string_view_literals;

class CDCHit {
public:
    struct Field : NonConstructibleBase {
        using CellID = IntField<CDCHit, 0, int>;
        using DriftDistance = FloatField<CDCHit, 1, double>;
        using Time = DoubleField<CDCHit, 2, double>;
    };

public:
    virtual ~CDCHit() = default;

    [[nodiscard]] const auto& CellID() const& { return fCellID; }
    [[nodiscard]] const auto& DriftDistance() const& { return fDriftDistance; }
    [[nodiscard]] const auto& Time() const& { return fTime; }

    [[nodiscard]] auto& CellID() & { return fCellID; }
    [[nodiscard]] auto& DriftDistance() & { return fDriftDistance; }
    [[nodiscard]] auto& Time() & { return fTime; }

    static constexpr auto BasicTreeName() { return "CDCHit"sv; }

    inline void FillAllBranchSocket() const&;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);

private:
    Field::CellID fCellID;
    Field::DriftDistance fDriftDistance;
    Field::Time fTime;
};
static_assert(TransientData<CDCHit>);

} // namespace Hit

template<>
CDCHit::Field::CellID::BranchSocket CDCHit::Field::CellID::Base::fgBranchSocket;
template<>
CDCHit::Field::DriftDistance::BranchSocket CDCHit::Field::DriftDistance::Base::fgBranchSocket;
template<>
CDCHit::Field::Time::BranchSocket CDCHit::Field::Time::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Hit/CDCHit.inl"
