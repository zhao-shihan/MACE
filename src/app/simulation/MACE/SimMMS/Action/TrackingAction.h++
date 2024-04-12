#pragma once

#include "MACE/Data/SimVertex.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimMMS/Messenger/AnalysisMessenger.h++"

#include "G4UserTrackingAction.hh"

#include <memory>
#include <vector>

namespace MACE::SimMMS::inline Action {

class TrackingAction final : public Env::Memory::PassiveSingleton<TrackingAction>,
                             public G4UserTrackingAction {
public:
    TrackingAction();

    auto PostUserTrackingAction(const G4Track* track) -> void override;

    auto SaveDecayVertexData() const -> auto { return fSaveDecayVertexData; }
    auto SaveDecayVertexData(bool val) -> void { fSaveDecayVertexData = val; }

    auto ClearDecayVertexData() -> void { return fDecayVertexData.clear(); }
    auto DecayVertexData() const -> const auto& { return fDecayVertexData; }

private:
    auto UpdateDecayVertexData(const G4Track& track) -> void;

private:
    bool fSaveDecayVertexData;

    std::vector<std::unique_ptr<Data::Tuple<Data::SimDecayVertex>>> fDecayVertexData;

    AnalysisMessenger::Register<TrackingAction> fMessengerRegister;
};

} // namespace MACE::SimMMS::inline Action
