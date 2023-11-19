#pragma once

#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/SimMACE/Hit/CDCHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VSensitiveDetector.hh"

#include <array>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace std {

template<>
struct hash<array<int32_t, 2>> {
    auto operator()(const array<int32_t, 2>& i) const noexcept -> size_t {
        return bit_cast<uint64_t>(i);
    }
};

} // namespace std

namespace MACE::SimMACE::inline SD {

class CDCSD final : public NonMoveableBase,
                    public G4VSensitiveDetector {
public:
    CDCSD(const G4String& sdName);

    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* theStep, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// @brief Inform this SD of event ID in EventAction
    void EventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    CDCHitCollection* fHitsCollection;

    G4double fMeanDriftVelocity;
    G4double fDeadTime;

    std::vector<std::pair<const G4TwoVector, const G4ThreeVector>> fCellMap;
    std::unordered_map<stdx::array2i32, const G4StepPoint> fCellEntryPoint;
    std::unordered_map<int, std::vector<std::pair<double, std::unique_ptr<CDCHit>>>> fCellSignalTimesAndHit;
};

} // namespace MACE::SimMACE::inline SD
