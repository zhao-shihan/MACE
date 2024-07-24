#pragma once

#include "MACE/SimDose/Messenger/AnalysisMessenger.h++"

#include "Mustard/Simulation/AnalysisBase.h++"

#include "TH3F.h"

#include "G4Step.hh"
#include "G4ThreeVector.hh"

namespace MACE::SimDose {

class Analysis final : public Mustard::Simulation::AnalysisBase<Analysis, "SimDose"> {
public:
    Analysis();

    auto MapNBinX() const -> auto { return fMapNBinX; }
    auto MapXMin() const -> auto { return fMapXMin; }
    auto MapXMax() const -> auto { return fMapXMax; }
    auto MapNBinY() const -> auto { return fMapNBinY; }
    auto MapYMin() const -> auto { return fMapYMin; }
    auto MapYMax() const -> auto { return fMapYMax; }
    auto MapNBinZ() const -> auto { return fMapNBinZ; }
    auto MapZMin() const -> auto { return fMapZMin; }
    auto MapZMax() const -> auto { return fMapZMax; }
    auto MapDeltaX() const -> auto { return ((fMapXMax - fMapXMin) / fMapNBinX); }
    auto MapDeltaY() const -> auto { return ((fMapYMax - fMapYMin) / fMapNBinY); }
    auto MapDeltaZ() const -> auto { return ((fMapZMax - fMapZMin) / fMapNBinZ); }

    auto MapNBinX(int n) { fMapNBinX = n; }
    auto MapXMin(double val) { fMapXMin = val; }
    auto MapXMax(double val) { fMapXMax = val; }
    auto MapNBinY(int n) { fMapNBinY = n; }
    auto MapYMin(double val) { fMapYMin = val; }
    auto MapYMax(double val) { fMapYMax = val; }
    auto MapNBinZ(int n) { fMapNBinZ = n; }
    auto MapZMin(double val) { fMapZMin = val; }
    auto MapZMax(double val) { fMapZMax = val; }

    auto FillMap(const G4Step& step) const -> void;

private:
    auto RunBeginUserAction(int) -> void override;
    auto EventEndUserAction() -> void override {}
    auto RunEndUserAction(int runID) -> void override;

    auto FillMapByPoint(G4ThreeVector x, double eDep, double dose) const -> void;
    auto FillMapBySegment(G4ThreeVector x0, G4ThreeVector x, double eDep, double dose) const -> void;

private:
    int fMapNBinX;
    double fMapXMin;
    double fMapXMax;
    int fMapNBinY;
    double fMapYMin;
    double fMapYMax;
    int fMapNBinZ;
    double fMapZMin;
    double fMapZMax;

    double fCachedMapDeltaV;
    double fCachedMapMinDeltaX;

    TH3F* fEdepMap;
    TH3F* fDoseMap;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimDose
