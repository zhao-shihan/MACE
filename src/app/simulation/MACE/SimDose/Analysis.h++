#pragma once

#include "MACE/SimDose/Messenger/AnalysisMessenger.h++"

#include "Mustard/Simulation/AnalysisBase.h++"

#include "TH3F.h"

#include "G4ThreeVector.hh"

#include <utility>

namespace MACE::SimDose {

class Analysis final : public Mustard::Simulation::AnalysisBase<Analysis, "SimDose"> {
public:
    Analysis();

    auto MapNBinX(int n) { fMapNBinX = n; }
    auto MapXMin(double val) { fMapXMin = val; }
    auto MapXMax(double val) { fMapXMax = val; }
    auto MapNBinY(int n) { fMapNBinY = n; }
    auto MapYMin(double val) { fMapYMin = val; }
    auto MapYMax(double val) { fMapYMax = val; }
    auto MapNBinZ(int n) { fMapNBinZ = n; }
    auto MapZMin(double val) { fMapZMin = val; }
    auto MapZMax(double val) { fMapZMax = val; }

    auto FillMap(G4ThreeVector x, double eDep, double density) const -> void;

private:
    auto RunBeginUserAction(int) -> void override;
    auto EventEndUserAction() -> void override {}
    auto RunEndUserAction(int runID) -> void override;

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

    TH3F* fEdepMap;
    TH3F* fDoseMap;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimDose
