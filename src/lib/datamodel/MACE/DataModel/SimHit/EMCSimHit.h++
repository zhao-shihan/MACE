#pragma once

#include "MACE/DataModel/Column/FundamentalColumn.h++"
#include "MACE/DataModel/Column/VectorColumn.h++"
#include "MACE/DataModel/Hit/EMCHit.h++"
#include "MACE/Extension/stdx/arraynx.h++"

#include <string_view>

namespace MACE::DataModel {

inline namespace SimHit {

using namespace std::string_view_literals;

class EMCSimHit : public EMCHit {
public:
    struct Column : EMCHit::Column {
        using MCEventID = IntColumn<EMCSimHit, 2, int>;
        using MCTrackID = IntColumn<EMCSimHit, 3, int>;
        using PDGCode = IntColumn<EMCSimHit, 4, int>;
        using Position = Vector3FColumn<EMCSimHit, 5, stdx::array3d>;
        using Momentum = Vector3FColumn<EMCSimHit, 6, stdx::array3d>;
        using VertexTime = DoubleColumn<EMCSimHit, 7, double>;
        using VertexPosition = Vector3FColumn<EMCSimHit, 8, stdx::array3d>;
        using VertexKineticEnergy = FloatColumn<EMCSimHit, 9, double>;
        using VertexMomentum = Vector3FColumn<EMCSimHit, 10, stdx::array3d>;
    };

public:
    virtual ~EMCSimHit() = default;

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


    static constexpr auto BasicTreeName() { return "EMCSimHit"sv; }

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
static_assert(TransientData<EMCSimHit>);

} // namespace SimHit

template<>
EMCSimHit::Column::MCEventID::BranchSocket EMCSimHit::Column::MCEventID::Base::fgBranchSocket;
template<>
EMCSimHit::Column::MCTrackID::BranchSocket EMCSimHit::Column::MCTrackID::Base::fgBranchSocket;
template<>
EMCSimHit::Column::PDGCode::BranchSocket EMCSimHit::Column::PDGCode::Base::fgBranchSocket;
template<>
EMCSimHit::Column::Position::BranchSocket EMCSimHit::Column::Position::Base::fgBranchSocket;
template<>
EMCSimHit::Column::Momentum::BranchSocket EMCSimHit::Column::Momentum::Base::fgBranchSocket;
template<>
EMCSimHit::Column::VertexTime::BranchSocket EMCSimHit::Column::VertexTime::Base::fgBranchSocket;
template<>
EMCSimHit::Column::VertexPosition::BranchSocket EMCSimHit::Column::VertexPosition::Base::fgBranchSocket;
template<>
EMCSimHit::Column::VertexKineticEnergy::BranchSocket EMCSimHit::Column::VertexKineticEnergy::Base::fgBranchSocket;
template<>
EMCSimHit::Column::VertexMomentum::BranchSocket EMCSimHit::Column::VertexMomentum::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/EMCSimHit.inl"
