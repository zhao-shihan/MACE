#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/Utility/NonConstructibleBase.hxx"

namespace MACE::DataModel {

inline namespace Track {

class CDCTrackBase {
public:
    struct Entry : NonConstructibleBase {
        using PDGCode = IntEntry<CDCTrackBase, 0, int>;
        using NHit = IntEntry<CDCTrackBase, 1, int>;
        using Chi2 = FloatEntry<CDCTrackBase, 2, double>;
        using VertexTime = DoubleEntry<CDCTrackBase, 3, double>;
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
    Entry::PDGCode fPDGCode;
    Entry::NHit fNHit;
    Entry::Chi2 fChi2;
    Entry::VertexTime fVertexTime;
};

} // namespace Track

template<>
CDCTrackBase::Entry::PDGCode::BranchSocket CDCTrackBase::Entry::PDGCode::Base::fgBranchSocket;
template<>
CDCTrackBase::Entry::NHit::BranchSocket CDCTrackBase::Entry::NHit::Base::fgBranchSocket;
template<>
CDCTrackBase::Entry::Chi2::BranchSocket CDCTrackBase::Entry::Chi2::Base::fgBranchSocket;
template<>
CDCTrackBase::Entry::VertexTime::BranchSocket CDCTrackBase::Entry::VertexTime::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Track/CDCTrackBase.inl"
