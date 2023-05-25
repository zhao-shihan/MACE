#pragma once

#include "MACE/DataModel/Column/FundamentalColumn.hxx"
#include "MACE/Utility/NonConstructibleBase.hxx"

namespace MACE::DataModel {

inline namespace Track {

class CDCTrackBase {
public:
    struct Column : NonConstructibleBase {
        using PDGCode = IntColumn<CDCTrackBase, 0, int>;
        using NHit = IntColumn<CDCTrackBase, 1, int>;
        using Chi2 = FloatColumn<CDCTrackBase, 2, double>;
        using VertexTime = DoubleColumn<CDCTrackBase, 3, double>;
    };

protected:
    CDCTrackBase() = default;
    ~CDCTrackBase() = default;

public:
    [[nodiscard]] const auto& PDGCode() const& { return fPDGCode; }
    [[nodiscard]] const auto& NHit() const& { return fNHit; }
    [[nodiscard]] const auto& Chi2() const& { return fChi2; }
    [[nodiscard]] const auto& VertexTime() const& { return fVertexTime; }

    [[nodiscard]] auto& PDGCode() & { return fPDGCode; }
    [[nodiscard]] auto& NHit() & { return fNHit; }
    [[nodiscard]] auto& Chi2() & { return fChi2; }
    [[nodiscard]] auto& VertexTime() & { return fVertexTime; }

protected:
    inline void FillAllBranchSocket() const&;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);

private:
    Column::PDGCode fPDGCode;
    Column::NHit fNHit;
    Column::Chi2 fChi2;
    Column::VertexTime fVertexTime;
};

} // namespace Track

template<>
CDCTrackBase::Column::PDGCode::BranchSocket CDCTrackBase::Column::PDGCode::Base::fgBranchSocket;
template<>
CDCTrackBase::Column::NHit::BranchSocket CDCTrackBase::Column::NHit::Base::fgBranchSocket;
template<>
CDCTrackBase::Column::Chi2::BranchSocket CDCTrackBase::Column::Chi2::Base::fgBranchSocket;
template<>
CDCTrackBase::Column::VertexTime::BranchSocket CDCTrackBase::Column::VertexTime::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Track/CDCTrackBase.inl"
