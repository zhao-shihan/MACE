#pragma once

#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/SimMACE/Hit/CDCHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include "gsl/gsl"

#include <array>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace MACE::SimMACE::inline SD {

class CDCSD final : public NonMoveableBase,
                    public G4VSensitiveDetector {
public:
    CDCSD(const G4String& sdName);

    auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    auto EndOfEvent(G4HCofThisEvent*) -> void override;

    /// @brief Inform this SD of event ID in EventAction
    auto EventID(G4int eventID) -> void { fEventID = eventID; }

private:
    struct HashArray2I32 {
        auto operator()(const stdx::array2i32& i) const noexcept -> std::size_t { return std::bit_cast<std::uint64_t>(i); }
    };

private:
    G4int fEventID;
    CDCHitCollection* fHitsCollection;

    G4double fMeanDriftVelocity;
    G4double fDeadTime;
    const std::vector<Detector::Description::CDC::CellInformation>* fCellMap;

    std::unordered_map<stdx::array2i32, const G4StepPoint, HashArray2I32> fCellEntryPoint;
    std::unordered_map<int, std::vector<std::pair<double, std::unique_ptr<CDCHit>>>> fCellSignalTimesAndHit;
};

} // namespace MACE::SimMACE::inline SD
