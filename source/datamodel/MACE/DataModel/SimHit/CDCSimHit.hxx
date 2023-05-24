#pragma once

#include "MACE/DataModel/Field/FundamentalField.hxx"
#include "MACE/DataModel/Field/VectorField.hxx"
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
    struct Field : CDCHit::Field {
        using MCEventID = IntField<CDCSimHit, 0, int>;
        using MCTrackID = IntField<CDCSimHit, 1, int>;
        using PDGCode = IntField<CDCSimHit, 2, int>;
        using KineticEnergy = FloatField<CDCSimHit, 3, double>;
        using Momentum = Vector3FField<CDCSimHit, 4, stdx::array3d>;
        using VertexTime = DoubleField<CDCSimHit, 5, double>;
        using VertexPosition = Vector3FField<CDCSimHit, 6, stdx::array3d>;
        using VertexKineticEnergy = FloatField<CDCSimHit, 7, double>;
        using VertexMomentum = Vector3FField<CDCSimHit, 8, stdx::array3d>;
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
static_assert(TransientData<CDCSimHit>);

} // namespace SimHit

template<>
CDCSimHit::Field::MCEventID::BranchSocket CDCSimHit::Field::MCEventID::Base::fgBranchSocket;
template<>
CDCSimHit::Field::MCTrackID::BranchSocket CDCSimHit::Field::MCTrackID::Base::fgBranchSocket;
template<>
CDCSimHit::Field::PDGCode::BranchSocket CDCSimHit::Field::PDGCode::Base::fgBranchSocket;
template<>
CDCSimHit::Field::KineticEnergy::BranchSocket CDCSimHit::Field::KineticEnergy::Base::fgBranchSocket;
template<>
CDCSimHit::Field::Momentum::BranchSocket CDCSimHit::Field::Momentum::Base::fgBranchSocket;
template<>
CDCSimHit::Field::VertexTime::BranchSocket CDCSimHit::Field::VertexTime::Base::fgBranchSocket;
template<>
CDCSimHit::Field::VertexPosition::BranchSocket CDCSimHit::Field::VertexPosition::Base::fgBranchSocket;
template<>
CDCSimHit::Field::VertexKineticEnergy::BranchSocket CDCSimHit::Field::VertexKineticEnergy::Base::fgBranchSocket;
template<>
CDCSimHit::Field::VertexMomentum::BranchSocket CDCSimHit::Field::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/CDCSimHit.inl"
