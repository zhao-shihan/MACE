#pragma once

#include "MACE/DataModel/Column/FundamentalColumn.h++"
#include "MACE/DataModel/Column/VectorColumn.h++"
#include "MACE/DataModel/Hit/CDCHit.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Utility/VectorAssign.h++"
#include "MACE/Utility/VectorCast.h++"

#include <string_view>

namespace MACE::DataModel {

inline namespace SimHit {

using namespace std::string_view_literals;

class CDCSimHit : public CDCHit {
public:
    struct Column : CDCHit::Column {
        using MCEventID = IntColumn<CDCSimHit, 0, int>;
        using MCTrackID = IntColumn<CDCSimHit, 1, int>;
        using PDGCode = IntColumn<CDCSimHit, 2, int>;
        using KineticEnergy = FloatColumn<CDCSimHit, 3, double>;
        using Momentum = Vector3FColumn<CDCSimHit, 4, stdx::array3d>;
        using VertexTime = DoubleColumn<CDCSimHit, 5, double>;
        using VertexPosition = Vector3FColumn<CDCSimHit, 6, stdx::array3d>;
        using VertexKineticEnergy = FloatColumn<CDCSimHit, 7, double>;
        using VertexMomentum = Vector3FColumn<CDCSimHit, 8, stdx::array3d>;
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
    Column::MCEventID fMCEventID;
    Column::MCTrackID fMCTrackID;
    Column::PDGCode fPDGCode;
    Column::KineticEnergy fKineticEnergy;
    Column::Momentum fMomentum;
    Column::VertexTime fVertexTime;
    Column::VertexPosition fVertexPosition;
    Column::VertexKineticEnergy fVertexKineticEnergy;
    Column::VertexMomentum fVertexMomentum;
};
static_assert(TransientData<CDCSimHit>);

} // namespace SimHit

template<>
CDCSimHit::Column::MCEventID::BranchSocket CDCSimHit::Column::MCEventID::Base::fgBranchSocket;
template<>
CDCSimHit::Column::MCTrackID::BranchSocket CDCSimHit::Column::MCTrackID::Base::fgBranchSocket;
template<>
CDCSimHit::Column::PDGCode::BranchSocket CDCSimHit::Column::PDGCode::Base::fgBranchSocket;
template<>
CDCSimHit::Column::KineticEnergy::BranchSocket CDCSimHit::Column::KineticEnergy::Base::fgBranchSocket;
template<>
CDCSimHit::Column::Momentum::BranchSocket CDCSimHit::Column::Momentum::Base::fgBranchSocket;
template<>
CDCSimHit::Column::VertexTime::BranchSocket CDCSimHit::Column::VertexTime::Base::fgBranchSocket;
template<>
CDCSimHit::Column::VertexPosition::BranchSocket CDCSimHit::Column::VertexPosition::Base::fgBranchSocket;
template<>
CDCSimHit::Column::VertexKineticEnergy::BranchSocket CDCSimHit::Column::VertexKineticEnergy::Base::fgBranchSocket;
template<>
CDCSimHit::Column::VertexMomentum::BranchSocket CDCSimHit::Column::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/CDCSimHit.inl"
