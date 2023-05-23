#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/Entry/VectorEntry.hxx"
#include "MACE/DataModel/Hit/CDCHit.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"
#include "MACE/Utility/VectorAssign.hxx"
#include "MACE/Utility/VectorCast.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace SimHit {

using namespace std::string_view_literals;

class CDCSimHit : public CDCHit {
public:
    struct Entry : CDCHit::Entry {
        using MCEventID = IntEntry<CDCSimHit, 0, int>;
        using MCTrackID = IntEntry<CDCSimHit, 1, int>;
        using PDGCode = IntEntry<CDCSimHit, 2, int>;
        using KineticEnergy = FloatEntry<CDCSimHit, 3, double>;
        using Momentum = Vector3FEntry<CDCSimHit, 4, stdx::array3d>;
        using VertexTime = DoubleEntry<CDCSimHit, 5, double>;
        using VertexPosition = Vector3FEntry<CDCSimHit, 6, stdx::array3d>;
        using VertexKineticEnergy = FloatEntry<CDCSimHit, 7, double>;
        using VertexMomentum = Vector3FEntry<CDCSimHit, 8, stdx::array3d>;
    };

public:
    virtual ~CDCSimHit() = default;

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

    static constexpr auto BasicTreeName() { return "CDCSimHit"sv; }

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
static_assert(TransientData<CDCSimHit>);

} // namespace SimHit

template<>
CDCSimHit::Entry::MCEventID::BranchSocket CDCSimHit::Entry::MCEventID::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::MCTrackID::BranchSocket CDCSimHit::Entry::MCTrackID::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::PDGCode::BranchSocket CDCSimHit::Entry::PDGCode::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::KineticEnergy::BranchSocket CDCSimHit::Entry::KineticEnergy::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::Momentum::BranchSocket CDCSimHit::Entry::Momentum::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::VertexTime::BranchSocket CDCSimHit::Entry::VertexTime::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::VertexPosition::BranchSocket CDCSimHit::Entry::VertexPosition::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::VertexKineticEnergy::BranchSocket CDCSimHit::Entry::VertexKineticEnergy::Base::fgBranchSocket;
template<>
CDCSimHit::Entry::VertexMomentum::BranchSocket CDCSimHit::Entry::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/CDCSimHit.inl"
