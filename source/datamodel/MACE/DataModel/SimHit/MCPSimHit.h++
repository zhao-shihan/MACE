#pragma once

#include "MACE/DataModel/Column/FundamentalColumn.h++"
#include "MACE/DataModel/Column/VectorColumn.h++"
#include "MACE/DataModel/Hit/MCPHit.h++"
#include "MACE/Extension/stdx/arraynx.h++"

#include <string_view>

namespace MACE::DataModel {

inline namespace SimHit {

using namespace std::string_view_literals;

class MCPSimHit : public MCPHit {
public:
    struct Column : MCPHit::Column {
        using MCEventID = IntColumn<MCPSimHit, 0, int>;
        using MCTrackID = IntColumn<MCPSimHit, 1, int>;
        using PDGCode = IntColumn<MCPSimHit, 2, int>;
        using KineticEnergy = FloatColumn<MCPSimHit, 3, double>;
        using Momentum = Vector3FColumn<MCPSimHit, 4, stdx::array3d>;
        using VertexTime = DoubleColumn<MCPSimHit, 5, double>;
        using VertexPosition = Vector3FColumn<MCPSimHit, 6, stdx::array3d>;
        using VertexKineticEnergy = FloatColumn<MCPSimHit, 7, double>;
        using VertexMomentum = Vector3FColumn<MCPSimHit, 8, stdx::array3d>;
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
static_assert(TransientData<MCPSimHit>);

} // namespace SimHit

template<>
MCPSimHit::Column::MCEventID::BranchSocket MCPSimHit::Column::MCEventID::Base::fgBranchSocket;
template<>
MCPSimHit::Column::MCTrackID::BranchSocket MCPSimHit::Column::MCTrackID::Base::fgBranchSocket;
template<>
MCPSimHit::Column::PDGCode::BranchSocket MCPSimHit::Column::PDGCode::Base::fgBranchSocket;
template<>
MCPSimHit::Column::KineticEnergy::BranchSocket MCPSimHit::Column::KineticEnergy::Base::fgBranchSocket;
template<>
MCPSimHit::Column::Momentum::BranchSocket MCPSimHit::Column::Momentum::Base::fgBranchSocket;
template<>
MCPSimHit::Column::VertexTime::BranchSocket MCPSimHit::Column::VertexTime::Base::fgBranchSocket;
template<>
MCPSimHit::Column::VertexPosition::BranchSocket MCPSimHit::Column::VertexPosition::Base::fgBranchSocket;
template<>
MCPSimHit::Column::VertexKineticEnergy::BranchSocket MCPSimHit::Column::VertexKineticEnergy::Base::fgBranchSocket;
template<>
MCPSimHit::Column::VertexMomentum::BranchSocket MCPSimHit::Column::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/MCPSimHit.inl"
