#pragma once

#include "MACE/DataModel/Column/FundamentalColumn.hxx"
#include "MACE/DataModel/Column/VectorColumn.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"
#include "MACE/Utility/NonConstructibleBase.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace Hit {

using namespace std::string_view_literals;

class MCPHit {
public:
    struct Column : NonConstructibleBase {
        using Time = DoubleColumn<MCPHit, 0, double>;
        using Position = Vector2FColumn<MCPHit, 1, stdx::array2d>;
    };

public:
    virtual ~MCPHit() = default;

    const auto& Time() const& { return fTime; }
    const auto& Position() const& { return fPosition; }

    auto& Time() & { return fTime; }
    auto& Position() & { return fPosition; }

    static constexpr auto BasicTreeName() { return "MCPHit"sv; }

    inline void FillAllBranchSocket() const&;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);

private:
    Column::Time fTime;
    Column::Position fPosition;
};
static_assert(TransientData<MCPHit>);

} // namespace Hit

template<>
MCPHit::Column::Time::BranchSocket MCPHit::Column::Time::Base::fgBranchSocket;
template<>
MCPHit::Column::Position::BranchSocket MCPHit::Column::Position::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Hit/MCPHit.inl"
