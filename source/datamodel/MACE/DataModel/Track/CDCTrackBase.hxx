#pragma once

#include "MACE/DataModel/Field/FundamentalField.hxx"
#include "MACE/Utility/NonConstructibleBase.hxx"

namespace MACE::DataModel {

inline namespace Track {

class CDCTrackBase {
public:
    struct Field : NonConstructibleBase {
        using PDGCode = IntField<CDCTrackBase, 0, int>;
        using NHit = IntField<CDCTrackBase, 1, int>;
        using Chi2 = FloatField<CDCTrackBase, 2, double>;
        using VertexTime = DoubleField<CDCTrackBase, 3, double>;
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
    Field::PDGCode fPDGCode;
    Field::NHit fNHit;
    Field::Chi2 fChi2;
    Field::VertexTime fVertexTime;
};

} // namespace Track

template<>
CDCTrackBase::Field::PDGCode::BranchSocket CDCTrackBase::Field::PDGCode::Base::fgBranchSocket;
template<>
CDCTrackBase::Field::NHit::BranchSocket CDCTrackBase::Field::NHit::Base::fgBranchSocket;
template<>
CDCTrackBase::Field::Chi2::BranchSocket CDCTrackBase::Field::Chi2::Base::fgBranchSocket;
template<>
CDCTrackBase::Field::VertexTime::BranchSocket CDCTrackBase::Field::VertexTime::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Track/CDCTrackBase.inl"
