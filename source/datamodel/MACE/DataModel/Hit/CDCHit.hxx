#pragma once

#include "MACE/DataModel/Column/FundamentalColumn.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Utility/NonConstructibleBase.hxx"
#include "MACE/DataModel/Entry.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace Hit {

using namespace std::string_view_literals;

class CDCHit {
public:
    struct Column : NonConstructibleBase {
        using CellID = IntColumn<CDCHit, 0, int>;
        using DriftDistance = FloatColumn<CDCHit, 1, double>;
        using Time = DoubleColumn<CDCHit, 2, double>;
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
    Column::CellID fCellID;
    Column::DriftDistance fDriftDistance;
    Column::Time fTime;
};
static_assert(TransientData<CDCHit>);

} // namespace Hit

template<>
CDCHit::Column::CellID::BranchSocket CDCHit::Column::CellID::Base::fgBranchSocket;
template<>
CDCHit::Column::DriftDistance::BranchSocket CDCHit::Column::DriftDistance::Base::fgBranchSocket;
template<>
CDCHit::Column::Time::BranchSocket CDCHit::Column::Time::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Hit/CDCHit.inl"
