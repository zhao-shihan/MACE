#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Utility/NonConstructibleBase.hxx"

#include <string_view>
#include <utility>

namespace MACE::DataModel {

inline namespace Hit {

using namespace std::string_view_literals;

class EMCalHit {
public:
    struct Entry : NonConstructibleBase {
        using HitTime = DoubleEntry<EMCalHit, 0, double>;
        using Energy = FloatEntry<EMCalHit, 1, double>;
    };

public:
    virtual ~EMCalHit() = default;

    const auto& HitTime() const { return fHitTime; }
    const auto& Energy() const { return fEnergy; }

    void HitTime(auto&& v) { fHitTime.Value(std::forward<decltype(v)>(v)); }
    void Energy(auto&& v) { fEnergy.Value(std::forward<decltype(v)>(v)); }

    static constexpr auto BasicTreeName() { return "EMCalHit"sv; }

    inline void FillBranchSockets() const;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);

private:
    Entry::HitTime fHitTime;
    Entry::Energy fEnergy;
};
static_assert(TransientData<EMCalHit>);

} // namespace Hit

template<>
EMCalHit::Entry::HitTime::BranchSocket EMCalHit::Entry::HitTime::Base::fgBranchSocket;
template<>
EMCalHit::Entry::Energy::BranchSocket EMCalHit::Entry::Energy::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Hit/EMCalHit.inl"
