#pragma once

#include "MACE/Data/MMSTrack.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Simulation/Hit/CDCHit.h++"
#include "MACE/Simulation/SD/CDCSDMessenger.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <algorithm>
#include <cmath>
#include <memory>
#include <unordered_map>
#include <vector>

namespace MACE::inline Simulation::inline SD {

class CDCSD : public Mustard::NonMoveableBase,
              public G4VSensitiveDetector {
public:
    CDCSD(const G4String& sdName);

    auto IonizingEnergyDepositionThreshold(double e) -> void { fIonizingEnergyDepositionThreshold = std::max(0., e); }

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

protected:
    double fIonizingEnergyDepositionThreshold;

    double fMeanDriftVelocity;
    const std::vector<Detector::Description::CDC::CellInformation>* fCellMap;

    std::unordered_map<int, std::vector<std::unique_ptr<CDCHit>>> fSplitHit;
    CDCHitCollection* fHitsCollection;

    CDCSDMessenger::Register<CDCSD> fMessengerRegister;
};

} // namespace MACE::inline Simulation::inline SD
