#include "MACE/Detector/Description/World.h++"
#include "MACE/SimDose/Analysis.h++"

#include "Mustard/Env/MPIEnv.h++"

#include "G4SystemOfUnits.hh"

#include "fmt/core.h"

namespace MACE::SimDose {

Analysis::Analysis() :
    AnalysisBase{},
    fMapNBinX{300},
    fMapXRange{},
    fMapNBinY{100},
    fMapYRange{},
    fMapNBinZ{400},
    fMapZRange{},
    fEdepMap{},
    fDoseMap{},
    fMessengerRegister{this} {
    const auto& world{Detector::Description::World::Instance()};
    fMapXRange = {-world.HalfXExtent(), world.HalfXExtent()};
    fMapYRange = {-world.HalfYExtent(), world.HalfYExtent()};
    fMapZRange = {-world.HalfZExtent(), world.HalfZExtent()};
}

auto Analysis::FillMap(G4ThreeVector x, double eDep, double density) const -> void {
    const auto deltaV{((fMapXRange.second - fMapXRange.first) / fMapNBinX) *
                      ((fMapYRange.second - fMapYRange.first) / fMapNBinY) *
                      ((fMapZRange.second - fMapZRange.first) / fMapNBinZ)};
    fEdepMap->Fill(x.x(), x.y(), x.z(), eDep / joule);
    fDoseMap->Fill(x.x(), x.y(), x.z(), eDep / (density * deltaV) / gray);
}

auto Analysis::RunBeginUserAction(int) -> void {
    fEdepMap = new TH3F{"EdepMap", "Energy deposition (J)",
                        fMapNBinX, fMapXRange.first, fMapXRange.second,
                        fMapNBinY, fMapYRange.first, fMapYRange.second,
                        fMapNBinZ, fMapZRange.first, fMapZRange.second};
    fDoseMap = new TH3F{"DoseMap", "Absorbed dose (Gy)",
                        fMapNBinX, fMapXRange.first, fMapXRange.second,
                        fMapNBinY, fMapYRange.first, fMapYRange.second,
                        fMapNBinZ, fMapZRange.first, fMapZRange.second};
}

auto Analysis::RunEndUserAction(int runID) -> void {
    gDirectory->mkdir(fmt::format("G4Run{}", runID).c_str(), "", true)->cd();
    fEdepMap->Write();
    fDoseMap->Write();
}

} // namespace MACE::SimDose
