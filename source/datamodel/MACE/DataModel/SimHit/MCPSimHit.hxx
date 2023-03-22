#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/Entry/StringEntry.hxx"
#include "MACE/DataModel/Entry/VectorEntry.hxx"
#include "MACE/DataModel/Hit/MCPHit.hxx"
#include "MACE/Extension/stdx/array_alias.hxx"

#include <string_view>
#include <utility>

namespace MACE::DataModel {

inline namespace SimHit {

using namespace std::string_view_literals;

class MCPSimHit : public MCPHit {
public:
    struct Entry : MCPHit::Entry {
        using G4EventID = IntEntry<MCPHit, 2, int>;
        using G4TrackID = IntEntry<MCPHit, 3, int>;
        using VertexTime = DoubleEntry<MCPHit, 4, double>;
        using VertexPosition = Vector3FEntry<MCPHit, 5, stdx::array3d>;
        using Particle = ShortStringEntry<MCPHit, 6, ShortString>;
    };

public:
    virtual ~MCPSimHit() = default;

    const auto& G4EventID() const { return fG4EventID; }
    const auto& G4TrackID() const { return fG4TrackID; }
    const auto& VertexTime() const { return fVertexTime; }
    const auto& VertexPosition() const { return fVertexPosition; }
    const auto& Particle() const { return fParticle; }

    void G4EventID(auto&& v) { fG4EventID.Value(std::forward<decltype(v)>(v)); }
    void G4TrackID(auto&& v) { fG4TrackID.Value(std::forward<decltype(v)>(v)); }
    void VertexTime(auto&& v) { fVertexTime.Value(std::forward<decltype(v)>(v)); }
    void VertexPosition(auto&& v) { fVertexPosition.Value(std::forward<decltype(v)>(v)); }
    void Particle(auto&& v) { fParticle.Value(std::forward<decltype(v)>(v)); }

    static constexpr auto BasicTreeName() { return "MCPSimHit"sv; }

    inline void FillBranchSockets() const;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);

private:
    Entry::G4EventID fG4EventID;
    Entry::G4TrackID fG4TrackID;
    Entry::VertexTime fVertexTime;
    Entry::VertexPosition fVertexPosition;
    Entry::Particle fParticle;
};
static_assert(TransientData<MCPSimHit>);

} // namespace SimHit

template<>
MCPSimHit::Entry::G4EventID::BranchSocket MCPSimHit::Entry::G4EventID::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::G4TrackID::BranchSocket MCPSimHit::Entry::G4TrackID::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::VertexTime::BranchSocket MCPSimHit::Entry::VertexTime::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::VertexPosition::BranchSocket MCPSimHit::Entry::VertexPosition::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::Particle::BranchSocket MCPSimHit::Entry::Particle::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/MCPSimHit.inl"
