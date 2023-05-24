#pragma once

#include "MACE/DataModel/Field/FundamentalField.hxx"
#include "MACE/DataModel/Field/VectorField.hxx"
#include "MACE/DataModel/Hit/EMCalHit.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace SimHit {

using namespace std::string_view_literals;

class EMCalSimHit : public EMCalHit {
public:
    struct Field : EMCalHit::Field {
        using MCEventID = IntField<EMCalSimHit, 2, int>;
        using MCTrackID = IntField<EMCalSimHit, 3, int>;
        using PDGCode = IntField<EMCalSimHit, 4, int>;
        using Position = Vector3FField<EMCalSimHit, 5, stdx::array3d>;
        using Momentum = Vector3FField<EMCalSimHit, 6, stdx::array3d>;
        using VertexTime = DoubleField<EMCalSimHit, 7, double>;
        using VertexPosition = Vector3FField<EMCalSimHit, 8, stdx::array3d>;
        using VertexKineticEnergy = FloatField<EMCalSimHit, 9, double>;
        using VertexMomentum = Vector3FField<EMCalSimHit, 10, stdx::array3d>;
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
    Field::MCEventID fMCEventID;
    Field::MCTrackID fMCTrackID;
    Field::PDGCode fPDGCode;
    Field::Position fPosition;
    Field::Momentum fMomentum;
    Field::VertexTime fVertexTime;
    Field::VertexPosition fVertexPosition;
    Field::VertexKineticEnergy fVertexKineticEnergy;
    Field::VertexMomentum fVertexMomentum;
};
static_assert(TransientData<EMCalSimHit>);

} // namespace SimHit

template<>
EMCalSimHit::Field::MCEventID::BranchSocket EMCalSimHit::Field::MCEventID::Base::fgBranchSocket;
template<>
EMCalSimHit::Field::MCTrackID::BranchSocket EMCalSimHit::Field::MCTrackID::Base::fgBranchSocket;
template<>
EMCalSimHit::Field::PDGCode::BranchSocket EMCalSimHit::Field::PDGCode::Base::fgBranchSocket;
template<>
EMCalSimHit::Field::Position::BranchSocket EMCalSimHit::Field::Position::Base::fgBranchSocket;
template<>
EMCalSimHit::Field::Momentum::BranchSocket EMCalSimHit::Field::Momentum::Base::fgBranchSocket;
template<>
EMCalSimHit::Field::VertexTime::BranchSocket EMCalSimHit::Field::VertexTime::Base::fgBranchSocket;
template<>
EMCalSimHit::Field::VertexPosition::BranchSocket EMCalSimHit::Field::VertexPosition::Base::fgBranchSocket;
template<>
EMCalSimHit::Field::VertexKineticEnergy::BranchSocket EMCalSimHit::Field::VertexKineticEnergy::Base::fgBranchSocket;
template<>
EMCalSimHit::Field::VertexMomentum::BranchSocket EMCalSimHit::Field::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/EMCalSimHit.inl"
