#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/Entry/VectorEntry.hxx"
#include "MACE/DataModel/Hit/EMCalHit.hxx"
#include "MACE/Extension/stdx/array_alias.hxx"

#include <string_view>
#include <utility>

namespace MACE::DataModel {

inline namespace SimHit {

using namespace std::string_view_literals;

class EMCalSimHit : public EMCalHit {
public:
    struct Entry : EMCalHit::Entry {
        using G4EventID = IntEntry<EMCalSimHit, 2, int>;
        using G4TrackID = IntEntry<EMCalSimHit, 3, int>;
        using PDGCode = IntEntry<EMCalSimHit, 4, int>;
        using Momentum = Vector3FEntry<EMCalSimHit, 5, stdx::array3d>;
        using VertexTime = DoubleEntry<EMCalSimHit, 6, double>;
        using VertexPosition = Vector3FEntry<EMCalSimHit, 7, stdx::array3d>;
        using VertexEnergy = FloatEntry<EMCalSimHit, 8, double>;
        using VertexMomentum = Vector3FEntry<EMCalSimHit, 9, stdx::array3d>;
    };

public:
    virtual ~EMCalSimHit() = default;

    const auto& G4EventID() const { return fG4EventID; }
    const auto& G4TrackID() const { return fG4TrackID; }
    const auto& PDGCode() const { return fPDGCode; }
    const auto& Momentum() const { return fMomentum; }
    const auto& VertexTime() const { return fVertexTime; }
    const auto& VertexPosition() const { return fVertexPosition; }
    const auto& VertexEnergy() const { return fVertexEnergy; }
    const auto& VertexMomentum() const { return fVertexMomentum; }

    void G4EventID(auto&& v) { fG4EventID.Value(std::forward<decltype(v)>(v)); }
    void G4TrackID(auto&& v) { fG4TrackID.Value(std::forward<decltype(v)>(v)); }
    void PDGCode(auto&& v) { fPDGCode.Value(std::forward<decltype(v)>(v)); }
    void Momentum(auto&& v) { fMomentum.Value(std::forward<decltype(v)>(v)); }
    void VertexTime(auto&& v) { fVertexTime.Value(std::forward<decltype(v)>(v)); }
    void VertexPosition(auto&& v) { fVertexPosition.Value(std::forward<decltype(v)>(v)); }
    void VertexEnergy(auto&& v) { fVertexEnergy.Value(std::forward<decltype(v)>(v)); }
    void VertexMomentum(auto&& v) { fVertexMomentum.Value(std::forward<decltype(v)>(v)); }

    static constexpr auto BasicTreeName() { return "EMCalSimHit"sv; }

    inline void FillBranchSockets() const;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);

private:
    Entry::G4EventID fG4EventID;
    Entry::G4TrackID fG4TrackID;
    Entry::PDGCode fPDGCode;
    Entry::Momentum fMomentum;
    Entry::VertexTime fVertexTime;
    Entry::VertexPosition fVertexPosition;
    Entry::VertexEnergy fVertexEnergy;
    Entry::VertexMomentum fVertexMomentum;
};
static_assert(TransientData<EMCalSimHit>);

} // namespace SimHit

template<>
EMCalSimHit::Entry::G4EventID::BranchSocket EMCalSimHit::Entry::G4EventID::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::G4TrackID::BranchSocket EMCalSimHit::Entry::G4TrackID::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::PDGCode::BranchSocket EMCalSimHit::Entry::PDGCode::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::Momentum::BranchSocket EMCalSimHit::Entry::Momentum::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::VertexTime::BranchSocket EMCalSimHit::Entry::VertexTime::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::VertexPosition::BranchSocket EMCalSimHit::Entry::VertexPosition::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::VertexEnergy::BranchSocket EMCalSimHit::Entry::VertexEnergy::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::VertexMomentum::BranchSocket EMCalSimHit::Entry::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/EMCalSimHit.inl"
