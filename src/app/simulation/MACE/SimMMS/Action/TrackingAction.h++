#pragma once

#include "MACE/Data/SimDecayVertex.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4UserTrackingAction.hh"

#include <memory>
#include <vector>

namespace MACE::SimMMS::inline Action {

class TrackingAction final : public Env::Memory::PassiveSingleton<TrackingAction>,
                             public G4UserTrackingAction {
public:
    auto PostUserTrackingAction(const G4Track* track) -> void override;

    auto ClearDecayVertexData() -> void { return fDecayVertexData.clear(); }
    auto DecayVertexData() const -> const auto& { return fDecayVertexData; }

private:
    std::vector<std::unique_ptr<Data::Tuple<Data::SimDecayVertex>>> fDecayVertexData;
};

} // namespace MACE::SimMMS::inline Action
