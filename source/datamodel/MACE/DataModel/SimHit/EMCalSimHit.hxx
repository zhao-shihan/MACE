#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/Entry/VectorEntry.hxx"
#include "MACE/DataModel/Hit/EMCalHit.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace SimHit {

using namespace std::string_view_literals;

class EMCalSimHit : public EMCalHit {
public:
    struct Entry : EMCalHit::Entry {
        using MCEventID = IntEntry<EMCalSimHit, 2, int>;
        using MCTrackID = IntEntry<EMCalSimHit, 3, int>;
        using PDGCode = IntEntry<EMCalSimHit, 4, int>;
        using Position = Vector3FEntry<EMCalSimHit, 5, stdx::array3d>;
        using Momentum = Vector3FEntry<EMCalSimHit, 6, stdx::array3d>;
        using VertexTime = DoubleEntry<EMCalSimHit, 7, double>;
        using VertexPosition = Vector3FEntry<EMCalSimHit, 8, stdx::array3d>;
        using VertexKineticEnergy = FloatEntry<EMCalSimHit, 9, double>;
        using VertexMomentum = Vector3FEntry<EMCalSimHit, 10, stdx::array3d>;
    };

public:
    virtual ~EMCalSimHit() = default;

    [[nodiscard]] const auto& MCEventID() const& { return fMCEventID; }
    [[nodiscard]] const auto& MCTrackID() const& { return fMCTrackID; }
    [[nodiscard]] const auto& PDGCode() const& { return fPDGCode; }
    [[nodiscard]] const auto& Position() const& { return fPosition; }
    [[nodiscard]] const auto& Momentum() const& { return fMomentum; }
    [[nodiscard]] const auto& VertexTime() const& { return fVertexTime; }
    [[nodiscard]] const auto& VertexPosition() const& { return fVertexPosition; }
    [[nodiscard]] const auto& VertexKineticEnergy() const& { return fVertexKineticEnergy; }
    [[nodiscard]] const auto& VertexMomentum() const& { return fVertexMomentum; }

    [[nodiscard]] auto& MCEventID() & { return fMCEventID; }
    [[nodiscard]] auto& MCTrackID() & { return fMCTrackID; }
    [[nodiscard]] auto& PDGCode() & { return fPDGCode; }
    [[nodiscard]] auto& Position() & { return fPosition; }
    [[nodiscard]] auto& Momentum() & { return fMomentum; }
    [[nodiscard]] auto& VertexTime() & { return fVertexTime; }
    [[nodiscard]] auto& VertexPosition() & { return fVertexPosition; }
    [[nodiscard]] auto& VertexKineticEnergy() & { return fVertexKineticEnergy; }
    [[nodiscard]] auto& VertexMomentum() & { return fVertexMomentum; }


    static constexpr auto BasicTreeName() { return "EMCalSimHit"sv; }

    inline void FillAllBranchSocket() const&;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);

private:
    Entry::MCEventID fMCEventID;
    Entry::MCTrackID fMCTrackID;
    Entry::PDGCode fPDGCode;
    Entry::Position fPosition;
    Entry::Momentum fMomentum;
    Entry::VertexTime fVertexTime;
    Entry::VertexPosition fVertexPosition;
    Entry::VertexKineticEnergy fVertexKineticEnergy;
    Entry::VertexMomentum fVertexMomentum;
};
static_assert(TransientData<EMCalSimHit>);

} // namespace SimHit

template<>
EMCalSimHit::Entry::MCEventID::BranchSocket EMCalSimHit::Entry::MCEventID::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::MCTrackID::BranchSocket EMCalSimHit::Entry::MCTrackID::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::PDGCode::BranchSocket EMCalSimHit::Entry::PDGCode::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::Position::BranchSocket EMCalSimHit::Entry::Position::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::Momentum::BranchSocket EMCalSimHit::Entry::Momentum::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::VertexTime::BranchSocket EMCalSimHit::Entry::VertexTime::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::VertexPosition::BranchSocket EMCalSimHit::Entry::VertexPosition::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::VertexKineticEnergy::BranchSocket EMCalSimHit::Entry::VertexKineticEnergy::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::VertexMomentum::BranchSocket EMCalSimHit::Entry::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/EMCalSimHit.inl"
