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
    auto MapXRange(double xMin, double xMax) { fMapXRange = {xMin, xMax}; }
    auto MapNBinY(int n) { fMapNBinY = n; }
    auto MapYRange(double yMin, double yMax) { fMapYRange = {yMin, yMax}; }
    auto MapNBinZ(int n) { fMapNBinZ = n; }
    auto MapZRange(double zMin, double zMax) { fMapZRange = {zMin, zMax}; }

    auto FillMap(G4ThreeVector x, double eDep, double density) const -> void;

private:
    auto RunBeginUserAction(int) -> void override;
    auto EventEndUserAction() -> void override {}
    auto RunEndUserAction(int runID) -> void override;

private:
    int fMapNBinX;
    std::pair<double, double> fMapXRange;
    int fMapNBinY;
    std::pair<double, double> fMapYRange;
    int fMapNBinZ;
    std::pair<double, double> fMapZRange;

    TH3F* fEdepMap;
    TH3F* fDoseMap;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimDose
