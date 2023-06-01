#pragma once

#include "MACE/DataModel/Column/FundamentalColumn.h++"
#include "MACE/DataModel/TransientData.h++"
#include "MACE/Utility/NonConstructibleBase.h++"

#include <string_view>

namespace MACE::DataModel {

inline namespace Hit {

using namespace std::string_view_literals;

class EMCalHit {
public:
    struct Column : NonConstructibleBase {
        using Time = DoubleColumn<EMCalHit, 0, double>;
        using EnergyDeposition = FloatColumn<EMCalHit, 1, double>;
    };

public:
    virtual ~EMCalHit() = default;

    [[nodiscard]] const auto& Time() const& { return fTime; }
    [[nodiscard]] const auto& EnergyDeposition() const& { return fEnergyDeposition; }

    [[nodiscard]] auto& Time() & { return fTime; }
    [[nodiscard]] auto& EnergyDeposition() & { return fEnergyDeposition; }

    static constexpr auto BasicTreeName() { return "EMCalHit"sv; }

    inline void FillAllBranchSocket() const&;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);

private:
    Column::Time fTime;
    Column::EnergyDeposition fEnergyDeposition;
};
static_assert(TransientData<EMCalHit>);

} // namespace Hit

template<>
EMCalHit::Column::Time::BranchSocket EMCalHit::Column::Time::Base::fgBranchSocket;
template<>
EMCalHit::Column::EnergyDeposition::BranchSocket EMCalHit::Column::EnergyDeposition::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Hit/EMCalHit.inl"
