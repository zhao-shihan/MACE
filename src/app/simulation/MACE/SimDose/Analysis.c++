#include "MACE/Detector/Description/World.h++"
#include "MACE/SimDose/Analysis.h++"

#include "Mustard/Env/MPIEnv.h++"

#include "G4SystemOfUnits.hh"

#include "fmt/core.h"

namespace MACE::SimDose {

Analysis::Analysis() :
    AnalysisBase{},
    fMapNBinX{300},
    fMapXMin{},
    fMapXMax{},
    fMapNBinY{100},
    fMapYMin{},
    fMapYMax{},
    fMapNBinZ{400},
    fMapZMin{},
    fMapZMax{},
    fCachedMapDeltaV{},
    fEdepMap{},
    fDoseMap{},
    fMessengerRegister{this} {
    const auto& world{Detector::Description::World::Instance()};
    fMapXMin = -world.HalfXExtent();
    fMapXMax = world.HalfXExtent();
    fMapYMin = -world.HalfYExtent();
    fMapYMax = world.HalfYExtent();
    fMapZMin = -world.HalfZExtent();
    fMapZMax = world.HalfZExtent();
}

auto Analysis::FillMap(G4ThreeVector x, double eDep, double density) const -> void {
    fEdepMap->Fill(x.x(), x.y(), x.z(), eDep / joule);
    fDoseMap->Fill(x.x(), x.y(), x.z(), eDep / (density * fCachedMapDeltaV) / gray);
}

auto Analysis::RunBeginUserAction(int) -> void {
    fCachedMapDeltaV = MapDeltaX() * MapDeltaY() * MapDeltaZ();
    fEdepMap = new TH3F{"EdepMap", "Energy deposition (J)",
                        fMapNBinX, fMapXMin, fMapXMax,
                        fMapNBinY, fMapYMin, fMapYMax,
                        fMapNBinZ, fMapZMin, fMapZMax};
    fDoseMap = new TH3F{"DoseMap", "Absorbed dose (Gy)",
                        fMapNBinX, fMapXMin, fMapXMax,
                        fMapNBinY, fMapYMin, fMapYMax,
                        fMapNBinZ, fMapZMin, fMapZMax};
}

auto Analysis::RunEndUserAction(int runID) -> void {
    gDirectory->mkdir(fmt::format("G4Run{}", runID).c_str(), "", true)->cd();
    fEdepMap->Write();
    fDoseMap->Write();
}

} // namespace MACE::SimDose
