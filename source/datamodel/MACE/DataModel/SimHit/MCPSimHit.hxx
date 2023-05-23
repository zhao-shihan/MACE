#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/Entry/VectorEntry.hxx"
#include "MACE/DataModel/Hit/MCPHit.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace SimHit {

using namespace std::string_view_literals;

class MCPSimHit : public MCPHit {
public:
    struct Entry : MCPHit::Entry {
        using MCEventID = IntEntry<MCPSimHit, 0, int>;
        using MCTrackID = IntEntry<MCPSimHit, 1, int>;
        using PDGCode = IntEntry<MCPSimHit, 2, int>;
        using KineticEnergy = FloatEntry<MCPSimHit, 3, double>;
        using Momentum = Vector3FEntry<MCPSimHit, 4, stdx::array3d>;
        using VertexTime = DoubleEntry<MCPSimHit, 5, double>;
        using VertexPosition = Vector3FEntry<MCPSimHit, 6, stdx::array3d>;
        using VertexKineticEnergy = FloatEntry<MCPSimHit, 7, double>;
        using VertexMomentum = Vector3FEntry<MCPSimHit, 8, stdx::array3d>;
    };

public:
    virtual ~MCPSimHit() = default;

    [[nodiscard]] const auto& MCEventID() const& { return fMCEventID; }
    [[nodiscard]] const auto& MCTrackID() const& { return fMCTrackID; }
    [[nodiscard]] const auto& PDGCode() const& { return fPDGCode; }
    [[nodiscard]] const auto& KineticEnergy() const& { return fKineticEnergy; }
    [[nodiscard]] const auto& Momentum() const& { return fMomentum; }
    [[nodiscard]] const auto& VertexTime() const& { return fVertexTime; }
    [[nodiscard]] const auto& VertexPosition() const& { return fVertexPosition; }
    [[nodiscard]] const auto& VertexKineticEnergy() const& { return fVertexKineticEnergy; }
    [[nodiscard]] const auto& VertexMomentum() const& { return fVertexMomentum; }

    [[nodiscard]] auto& MCEventID() & { return fMCEventID; }
    [[nodiscard]] auto& MCTrackID() & { return fMCTrackID; }
    [[nodiscard]] auto& PDGCode() & { return fPDGCode; }
    [[nodiscard]] auto& KineticEnergy() & { return fKineticEnergy; }
    [[nodiscard]] auto& Momentum() & { return fMomentum; }
    [[nodiscard]] auto& VertexTime() & { return fVertexTime; }
    [[nodiscard]] auto& VertexPosition() & { return fVertexPosition; }
    [[nodiscard]] auto& VertexKineticEnergy() & { return fVertexKineticEnergy; }
    [[nodiscard]] auto& VertexMomentum() & { return fVertexMomentum; }

    static constexpr auto BasicTreeName() { return "MCPSimHit"sv; }

    inline void FillAllBranchSocket() const&;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);

private:
    Entry::MCEventID fMCEventID;
    Entry::MCTrackID fMCTrackID;
    Entry::PDGCode fPDGCode;
    Entry::KineticEnergy fKineticEnergy;
    Entry::Momentum fMomentum;
    Entry::VertexTime fVertexTime;
    Entry::VertexPosition fVertexPosition;
    Entry::VertexKineticEnergy fVertexKineticEnergy;
    Entry::VertexMomentum fVertexMomentum;
};
static_assert(TransientData<MCPSimHit>);

} // namespace SimHit

template<>
MCPSimHit::Entry::MCEventID::BranchSocket MCPSimHit::Entry::MCEventID::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::MCTrackID::BranchSocket MCPSimHit::Entry::MCTrackID::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::PDGCode::BranchSocket MCPSimHit::Entry::PDGCode::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::KineticEnergy::BranchSocket MCPSimHit::Entry::KineticEnergy::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::Momentum::BranchSocket MCPSimHit::Entry::Momentum::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::VertexTime::BranchSocket MCPSimHit::Entry::VertexTime::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::VertexPosition::BranchSocket MCPSimHit::Entry::VertexPosition::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::VertexKineticEnergy::BranchSocket MCPSimHit::Entry::VertexKineticEnergy::Base::fgBranchSocket;
template<>
MCPSimHit::Entry::VertexMomentum::BranchSocket MCPSimHit::Entry::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/MCPSimHit.inl"
