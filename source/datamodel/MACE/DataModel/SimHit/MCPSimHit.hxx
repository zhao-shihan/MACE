#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
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
        using G4EventID = IntEntry<MCPSimHit, 2, int>;
        using G4TrackID = IntEntry<MCPSimHit, 3, int>;
        using PDGCode = IntEntry<MCPSimHit, 4, int>;
        using Energy = FloatEntry<MCPSimHit, 5, double>;
        using Momentum = Vector3FEntry<MCPSimHit, 6, stdx::array3d>;
        using VertexTime = DoubleEntry<MCPSimHit, 7, double>;
        using VertexPosition = Vector3FEntry<MCPSimHit, 8, stdx::array3d>;
        using VertexEnergy = FloatEntry<MCPSimHit, 9, double>;
        using VertexMomentum = Vector3FEntry<MCPSimHit, 10, stdx::array3d>;
    };

public:
    virtual ~MCPSimHit() = default;

    [[nodiscard]] const auto& G4EventID() const { return fG4EventID; }
    [[nodiscard]] const auto& G4TrackID() const { return fG4TrackID; }
    [[nodiscard]] const auto& PDGCode() const { return fPDGCode; }
    [[nodiscard]] const auto& Energy() const { return fEnergy; }
    [[nodiscard]] const auto& Momentum() const { return fMomentum; }
    [[nodiscard]] const auto& VertexTime() const { return fVertexTime; }
    [[nodiscard]] const auto& VertexPosition() const { return fVertexPosition; }
    [[nodiscard]] const auto& VertexEnergy() const { return fVertexEnergy; }
    [[nodiscard]] const auto& VertexMomentum() const { return fVertexMomentum; }

    void G4EventID(auto&& v) { fG4EventID.Value(std::forward<decltype(v)>(v)); }
    void G4TrackID(auto&& v) { fG4TrackID.Value(std::forward<decltype(v)>(v)); }
    void PDGCode(auto&& v) { fPDGCode.Value(std::forward<decltype(v)>(v)); }
    void Energy(auto&& v) { fEnergy.Value(std::forward<decltype(v)>(v)); }
    void Momentum(auto&& v) { fMomentum.Value(std::forward<decltype(v)>(v)); }
    void VertexTime(auto&& v) { fVertexTime.Value(std::forward<decltype(v)>(v)); }
    void VertexPosition(auto&& v) { fVertexPosition.Value(std::forward<decltype(v)>(v)); }
    void VertexEnergy(auto&& v) { fVertexEnergy.Value(std::forward<decltype(v)>(v)); }
    void VertexMomentum(auto&& v) { fVertexMomentum.Value(std::forward<decltype(v)>(v)); }

    static constexpr auto BasicTreeName() { return "MCPSimHit"sv; }

    inline void FillBranchSockets() const;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);

private:
    Entry::G4EventID fG4EventID;
    Entry::G4TrackID fG4TrackID;
    Entry::PDGCode fPDGCode;
    Entry::Energy fEnergy;
    Entry::Momentum fMomentum;
    Entry::VertexTime fVertexTime;
    Entry::VertexPosition fVertexPosition;
    Entry::VertexEnergy fVertexEnergy;
    Entry::VertexMomentum fVertexMomentum;
};
static_assert(TransientData<MCPSimHit>);

} // namespace SimHit

template<>
MCPSimHit::Entry::G4EventID::BranchSocket MCPSimHit::Entry::G4EventID::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::G4TrackID::BranchSocket MCPSimHit::Entry::G4TrackID::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::PDGCode::BranchSocket MCPSimHit::Entry::PDGCode::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::Energy::BranchSocket MCPSimHit::Entry::Energy::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::Momentum::BranchSocket MCPSimHit::Entry::Momentum::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::VertexTime::BranchSocket MCPSimHit::Entry::VertexTime::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::VertexPosition::BranchSocket MCPSimHit::Entry::VertexPosition::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::VertexEnergy::BranchSocket MCPSimHit::Entry::VertexEnergy::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::VertexMomentum::BranchSocket MCPSimHit::Entry::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/MCPSimHit.inl"
