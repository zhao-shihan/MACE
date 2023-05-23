#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Utility/NonConstructibleBase.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace Hit {

using namespace std::string_view_literals;

class CDCHit {
public:
    struct Entry : NonConstructibleBase {
        using CellID = IntEntry<CDCHit, 0, int>;
        using DriftDistance = FloatEntry<CDCHit, 1, double>;
        using Time = DoubleEntry<CDCHit, 2, double>;
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
    Entry::CellID fCellID;
    Entry::DriftDistance fDriftDistance;
    Entry::Time fTime;
};
static_assert(TransientData<CDCHit>);

} // namespace Hit

template<>
CDCHit::Entry::CellID::BranchSocket CDCHit::Entry::CellID::Base::fgBranchSocket;
template<>
CDCHit::Entry::DriftDistance::BranchSocket CDCHit::Entry::DriftDistance::Base::fgBranchSocket;
template<>
CDCHit::Entry::Time::BranchSocket CDCHit::Entry::Time::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Hit/CDCHit.inl"
