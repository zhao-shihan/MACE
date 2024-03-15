#pragma once

#include "MACE/Data/CDCTrack.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Simulation/Hit/CDCHit.h++"
#include "MACE/Simulation/SD/CDCSDMessenger.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <algorithm>
#include <memory>
#include <unordered_map>
#include <vector>

namespace MACE::inline Simulation::inline SD {

class CDCSD : public NonMoveableBase,
              public G4VSensitiveDetector {
public:
    CDCSD(const G4String& sdName);

    auto MinIonizingEnergyDepositionForHit(double e) -> void { fMinIonizingEnergyDepositionForHit = std::max(0., e); }
    auto NMinFiredCellForQualifiedTrack(int n) -> void { fNMinFiredCellForQualifiedTrack = std::max(1, n); }

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

private:
    auto BuildHitData() -> void;
    auto BuildTrackData() -> void;

protected:
    double fMinIonizingEnergyDepositionForHit;
    int fNMinFiredCellForQualifiedTrack;

    double fMeanDriftVelocity;
    const std::vector<Detector::Description::CDC::CellInformation>* fCellMap;

    std::unordered_map<int, std::vector<std::unique_ptr<CDCHit>>> fSplitHit;
    CDCHitCollection* fHitsCollection;

    std::vector<std::unique_ptr<Data::Tuple<Data::CDCSimTrack>>> fTrackData;

    CDCSDMessenger::Register<CDCSD> fMessengerRegister;
};

} // namespace MACE::inline Simulation::inline SD
