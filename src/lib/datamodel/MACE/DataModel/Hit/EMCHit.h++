#pragma once

#include "MACE/DataModel/Column/FundamentalColumn.h++"
#include "MACE/DataModel/TransientData.h++"
#include "MACE/Utility/NonConstructibleBase.h++"

#include <string_view>

namespace MACE::DataModel {

inline namespace Hit {

using namespace std::string_view_literals;

class EMCHit {
public:
    struct Column : NonConstructibleBase {
        using Time = DoubleColumn<EMCHit, 0, double>;
        using EnergyDeposition = FloatColumn<EMCHit, 1, double>;
    };

public:
    virtual ~EMCHit() = default;

    [[nodiscard]] const auto& Time() const& { return fTime; }
    [[nodiscard]] const auto& EnergyDeposition() const& { return fEnergyDeposition; }

    [[nodiscard]] auto& Time() & { return fTime; }
    [[nodiscard]] auto& EnergyDeposition() & { return fEnergyDeposition; }

    static constexpr auto BasicTreeName() { return "EMCHit"sv; }

    inline void FillAllBranchSocket() const&;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);

private:
    Column::Time fTime;
    Column::EnergyDeposition fEnergyDeposition;
};
static_assert(TransientData<EMCHit>);

} // namespace Hit

template<>
EMCHit::Column::Time::BranchSocket EMCHit::Column::Time::Base::fgBranchSocket;
template<>
EMCHit::Column::EnergyDeposition::BranchSocket EMCHit::Column::EnergyDeposition::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Hit/EMCHit.inl"
