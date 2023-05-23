#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/Utility/NonConstructibleBase.hxx"

namespace MACE::DataModel {

inline namespace SimTrack {

class CDCSimTrackBase {
public:
    struct Entry : NonConstructibleBase {
        using PDGCodeTruth = IntEntry<CDCSimTrackBase, 0, int>;
        using NHitTruth = IntEntry<CDCSimTrackBase, 1, int>;
        using VertexTimeTruth = DoubleEntry<CDCSimTrackBase, 2, double>;
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
    Entry::PDGCodeTruth fPDGCodeTruth;
    Entry::NHitTruth fNHitTruth;
    Entry::VertexTimeTruth fVertexTimeTruth;
};

} // namespace SimTrack

template<>
CDCSimTrackBase::Entry::PDGCodeTruth::BranchSocket CDCSimTrackBase::Entry::PDGCodeTruth::Base::fgBranchSocket;
template<>
CDCSimTrackBase::Entry::NHitTruth::BranchSocket CDCSimTrackBase::Entry::NHitTruth::Base::fgBranchSocket;
template<>
CDCSimTrackBase::Entry::VertexTimeTruth::BranchSocket CDCSimTrackBase::Entry::VertexTimeTruth::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimTrack/CDCSimTrackBase.inl"
