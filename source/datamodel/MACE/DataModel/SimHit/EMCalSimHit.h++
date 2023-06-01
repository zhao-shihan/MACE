#pragma once

#include "MACE/DataModel/Column/FundamentalColumn.h++"
#include "MACE/DataModel/Column/VectorColumn.h++"
#include "MACE/DataModel/Hit/EMCalHit.h++"
#include "MACE/Extension/stdx/arraynx.h++"

#include <string_view>

namespace MACE::DataModel {

inline namespace SimHit {

using namespace std::string_view_literals;

class EMCalSimHit : public EMCalHit {
public:
    struct Column : EMCalHit::Column {
        using MCEventID = IntColumn<EMCalSimHit, 2, int>;
        using MCTrackID = IntColumn<EMCalSimHit, 3, int>;
        using PDGCode = IntColumn<EMCalSimHit, 4, int>;
        using Position = Vector3FColumn<EMCalSimHit, 5, stdx::array3d>;
        using Momentum = Vector3FColumn<EMCalSimHit, 6, stdx::array3d>;
        using VertexTime = DoubleColumn<EMCalSimHit, 7, double>;
        using VertexPosition = Vector3FColumn<EMCalSimHit, 8, stdx::array3d>;
        using VertexKineticEnergy = FloatColumn<EMCalSimHit, 9, double>;
        using VertexMomentum = Vector3FColumn<EMCalSimHit, 10, stdx::array3d>;
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
    Column::MCEventID fMCEventID;
    Column::MCTrackID fMCTrackID;
    Column::PDGCode fPDGCode;
    Column::Position fPosition;
    Column::Momentum fMomentum;
    Column::VertexTime fVertexTime;
    Column::VertexPosition fVertexPosition;
    Column::VertexKineticEnergy fVertexKineticEnergy;
    Column::VertexMomentum fVertexMomentum;
};
static_assert(TransientData<EMCalSimHit>);

} // namespace SimHit

template<>
EMCalSimHit::Column::MCEventID::BranchSocket EMCalSimHit::Column::MCEventID::Base::fgBranchSocket;
template<>
EMCalSimHit::Column::MCTrackID::BranchSocket EMCalSimHit::Column::MCTrackID::Base::fgBranchSocket;
template<>
EMCalSimHit::Column::PDGCode::BranchSocket EMCalSimHit::Column::PDGCode::Base::fgBranchSocket;
template<>
EMCalSimHit::Column::Position::BranchSocket EMCalSimHit::Column::Position::Base::fgBranchSocket;
template<>
EMCalSimHit::Column::Momentum::BranchSocket EMCalSimHit::Column::Momentum::Base::fgBranchSocket;
template<>
EMCalSimHit::Column::VertexTime::BranchSocket EMCalSimHit::Column::VertexTime::Base::fgBranchSocket;
template<>
EMCalSimHit::Column::VertexPosition::BranchSocket EMCalSimHit::Column::VertexPosition::Base::fgBranchSocket;
template<>
EMCalSimHit::Column::VertexKineticEnergy::BranchSocket EMCalSimHit::Column::VertexKineticEnergy::Base::fgBranchSocket;
template<>
EMCalSimHit::Column::VertexMomentum::BranchSocket EMCalSimHit::Column::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/EMCalSimHit.inl"
