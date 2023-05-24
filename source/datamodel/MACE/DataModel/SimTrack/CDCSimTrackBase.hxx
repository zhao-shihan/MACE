#pragma once

#include "MACE/DataModel/Field/FundamentalField.hxx"
#include "MACE/Utility/NonConstructibleBase.hxx"

namespace MACE::DataModel {

inline namespace SimTrack {

class CDCSimTrackBase {
public:
    struct Field : NonConstructibleBase {
        using PDGCodeTruth = IntField<CDCSimTrackBase, 0, int>;
        using NHitTruth = IntField<CDCSimTrackBase, 1, int>;
        using VertexTimeTruth = DoubleField<CDCSimTrackBase, 2, double>;
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
    Field::PDGCodeTruth fPDGCodeTruth;
    Field::NHitTruth fNHitTruth;
    Field::VertexTimeTruth fVertexTimeTruth;
};

} // namespace SimTrack

template<>
CDCSimTrackBase::Field::PDGCodeTruth::BranchSocket CDCSimTrackBase::Field::PDGCodeTruth::Base::fgBranchSocket;
template<>
CDCSimTrackBase::Field::NHitTruth::BranchSocket CDCSimTrackBase::Field::NHitTruth::Base::fgBranchSocket;
template<>
CDCSimTrackBase::Field::VertexTimeTruth::BranchSocket CDCSimTrackBase::Field::VertexTimeTruth::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimTrack/CDCSimTrackBase.inl"
