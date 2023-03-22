#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/Entry/StringEntry.hxx"
#include "MACE/DataModel/Entry/VectorEntry.hxx"
#include "MACE/DataModel/Hit/CDCHit.hxx"
#include "MACE/Extension/stdx/array_alias.hxx"
#include "MACE/Utility/VectorAssign.hxx"
#include "MACE/Utility/VectorCast.hxx"

#include <array>
#include <string_view>
#include <utility>

namespace MACE::DataModel {

inline namespace SimHit {

using namespace std::string_view_literals;

class CDCSimHit : public CDCHit {
public:
    struct Entry : CDCHit::Entry {
        using G4EventID = IntEntry<CDCSimHit, 3, int>;
        using G4TrackID = IntEntry<CDCSimHit, 4, int>;
        using Energy = FloatEntry<CDCSimHit, 5, double>;
        using Momentum = Vector3FEntry<CDCSimHit, 6, stdx::array3d>;
        using VertexTime = DoubleEntry<CDCSimHit, 7, double>;
        using VertexPosition = Vector3FEntry<CDCSimHit, 8, stdx::array3d>;
        using VertexEnergy = FloatEntry<CDCSimHit, 9, double>;
        using VertexMomentum = Vector3FEntry<CDCSimHit, 10, stdx::array3d>;
        using Particle = ShortStringEntry<CDCSimHit, 11, ShortString>;
    };

public:
    virtual ~CDCSimHit() = default;

    const auto& G4EventID() const { return fG4EventID; }
    const auto& G4TrackID() const { return fG4TrackID; }
    const auto& Energy() const { return fEnergy; }
    const auto& Momentum() const { return fMomentum; }
    const auto& VertexTime() const { return fVertexTime; }
    const auto& VertexPosition() const { return fVertexPosition; }
    const auto& VertexEnergy() const { return fVertexEnergy; }
    const auto& VertexMomentum() const { return fVertexMomentum; }
    const auto& Particle() const { return fParticle; }

    void G4EventID(auto&& v) { fG4EventID.Value(std::forward<decltype(v)>(v)); }
    void G4TrackID(auto&& v) { fG4TrackID.Value(std::forward<decltype(v)>(v)); }
    void Energy(auto&& v) { fEnergy.Value(std::forward<decltype(v)>(v)); }
    void Momentum(auto&& v) { fMomentum.Value(std::forward<decltype(v)>(v)); }
    void VertexTime(auto&& v) { fVertexTime.Value(std::forward<decltype(v)>(v)); }
    void VertexPosition(auto&& v) { fVertexPosition.Value(std::forward<decltype(v)>(v)); }
    void VertexEnergy(auto&& v) { fVertexEnergy.Value(std::forward<decltype(v)>(v)); }
    void VertexMomentum(auto&& v) { fVertexMomentum.Value(std::forward<decltype(v)>(v)); }
    void Particle(auto&& v) { fParticle.Value(std::forward<decltype(v)>(v)); }

    static constexpr auto BasicTreeName() { return "CDCSimHit"sv; }

    inline void FillBranchSockets() const;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);

private:
    Entry::G4EventID fG4EventID;
    Entry::G4TrackID fG4TrackID;
    Entry::Energy fEnergy;
    Entry::Momentum fMomentum;
    Entry::VertexTime fVertexTime;
    Entry::VertexPosition fVertexPosition;
    Entry::VertexEnergy fVertexEnergy;
    Entry::VertexMomentum fVertexMomentum;
    Entry::Particle fParticle;
};
static_assert(TransientData<CDCSimHit>);

} // namespace SimHit

template<>
CDCSimHit::Entry::G4EventID::BranchSocket CDCSimHit::Entry::G4EventID::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::G4TrackID::BranchSocket CDCSimHit::Entry::G4TrackID::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::Energy::BranchSocket CDCSimHit::Entry::Energy::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::Momentum::BranchSocket CDCSimHit::Entry::Momentum::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::VertexTime::BranchSocket CDCSimHit::Entry::VertexTime::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::VertexPosition::BranchSocket CDCSimHit::Entry::VertexPosition::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::VertexEnergy::BranchSocket CDCSimHit::Entry::VertexEnergy::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::VertexMomentum::BranchSocket CDCSimHit::Entry::VertexMomentum::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::Particle::BranchSocket CDCSimHit::Entry::Particle::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/CDCSimHit.inl"
