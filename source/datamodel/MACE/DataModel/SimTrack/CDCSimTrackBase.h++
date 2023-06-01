#pragma once

#include "MACE/DataModel/Column/FundamentalColumn.h++"
#include "MACE/Utility/NonConstructibleBase.h++"

namespace MACE::DataModel {

inline namespace SimTrack {

class CDCSimTrackBase {
public:
    struct Column : NonConstructibleBase {
        using PDGCodeTruth = IntColumn<CDCSimTrackBase, 0, int>;
        using NHitTruth = IntColumn<CDCSimTrackBase, 1, int>;
        using VertexTimeTruth = DoubleColumn<CDCSimTrackBase, 2, double>;
    };

protected:
    CDCSimTrackBase() = default;
    ~CDCSimTrackBase() = default;

public:
    [[nodiscard]] const auto& PDGCodeTruth() const& { return fPDGCodeTruth; }
    [[nodiscard]] const auto& NHitTruth() const& { return fNHitTruth; }
    [[nodiscard]] const auto& VertexTimeTruth() const& { return fVertexTimeTruth; }

    [[nodiscard]] auto& PDGCodeTruth() & { return fPDGCodeTruth; }
    [[nodiscard]] auto& NHitTruth() & { return fNHitTruth; }
    [[nodiscard]] auto& VertexTimeTruth() & { return fVertexTimeTruth; }

protected:
    inline void FillAllBranchSocket() const&;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);

private:
    Column::PDGCodeTruth fPDGCodeTruth;
    Column::NHitTruth fNHitTruth;
    Column::VertexTimeTruth fVertexTimeTruth;
};

} // namespace SimTrack

template<>
CDCSimTrackBase::Column::PDGCodeTruth::BranchSocket CDCSimTrackBase::Column::PDGCodeTruth::Base::fgBranchSocket;
template<>
CDCSimTrackBase::Column::NHitTruth::BranchSocket CDCSimTrackBase::Column::NHitTruth::Base::fgBranchSocket;
template<>
CDCSimTrackBase::Column::VertexTimeTruth::BranchSocket CDCSimTrackBase::Column::VertexTimeTruth::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimTrack/CDCSimTrackBase.inl"
