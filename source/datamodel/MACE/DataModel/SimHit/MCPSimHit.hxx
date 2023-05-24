#pragma once

#include "MACE/DataModel/Field/FundamentalField.hxx"
#include "MACE/DataModel/Field/VectorField.hxx"
#include "MACE/DataModel/Hit/MCPHit.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace SimHit {

using namespace std::string_view_literals;

class MCPSimHit : public MCPHit {
public:
    struct Field : MCPHit::Field {
        using MCEventID = IntField<MCPSimHit, 0, int>;
        using MCTrackID = IntField<MCPSimHit, 1, int>;
        using PDGCode = IntField<MCPSimHit, 2, int>;
        using KineticEnergy = FloatField<MCPSimHit, 3, double>;
        using Momentum = Vector3FField<MCPSimHit, 4, stdx::array3d>;
        using VertexTime = DoubleField<MCPSimHit, 5, double>;
        using VertexPosition = Vector3FField<MCPSimHit, 6, stdx::array3d>;
        using VertexKineticEnergy = FloatField<MCPSimHit, 7, double>;
        using VertexMomentum = Vector3FField<MCPSimHit, 8, stdx::array3d>;
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
    Field::MCEventID fMCEventID;
    Field::MCTrackID fMCTrackID;
    Field::PDGCode fPDGCode;
    Field::KineticEnergy fKineticEnergy;
    Field::Momentum fMomentum;
    Field::VertexTime fVertexTime;
    Field::VertexPosition fVertexPosition;
    Field::VertexKineticEnergy fVertexKineticEnergy;
    Field::VertexMomentum fVertexMomentum;
};
static_assert(TransientData<MCPSimHit>);

} // namespace SimHit

template<>
MCPSimHit::Field::MCEventID::BranchSocket MCPSimHit::Field::MCEventID::Base::fgBranchSocket;
template<>
MCPSimHit::Field::MCTrackID::BranchSocket MCPSimHit::Field::MCTrackID::Base::fgBranchSocket;
template<>
MCPSimHit::Field::PDGCode::BranchSocket MCPSimHit::Field::PDGCode::Base::fgBranchSocket;
template<>
MCPSimHit::Field::KineticEnergy::BranchSocket MCPSimHit::Field::KineticEnergy::Base::fgBranchSocket;
template<>
MCPSimHit::Field::Momentum::BranchSocket MCPSimHit::Field::Momentum::Base::fgBranchSocket;
template<>
MCPSimHit::Field::VertexTime::BranchSocket MCPSimHit::Field::VertexTime::Base::fgBranchSocket;
template<>
MCPSimHit::Field::VertexPosition::BranchSocket MCPSimHit::Field::VertexPosition::Base::fgBranchSocket;
template<>
MCPSimHit::Field::VertexKineticEnergy::BranchSocket MCPSimHit::Field::VertexKineticEnergy::Base::fgBranchSocket;
template<>
MCPSimHit::Field::VertexMomentum::BranchSocket MCPSimHit::Field::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/MCPSimHit.inl"
