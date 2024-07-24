#include "MACE/Detector/Description/World.h++"
#include "MACE/SimDose/Analysis.h++"

#include "Mustard/Env/MPIEnv.h++"

#include "G4ParticleDefinition.hh"
#include "G4StepPoint.hh"
#include "G4SystemOfUnits.hh"

#include "muc/math"

#include "fmt/core.h"

#include <algorithm>
#include <vector>

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

auto Analysis::FillMap(const G4Step& step) const -> void {
    if (step.GetTotalEnergyDeposit() == 0) { return; }

    const auto& pre{*step.GetPreStepPoint()};
    const auto& post{*step.GetPostStepPoint()};

    const auto eDep{step.GetTotalEnergyDeposit()};
    const auto deltaM{pre.GetMaterial()->GetDensity() * fCachedMapDeltaV};
    const auto dose{eDep / deltaM};

    if (step.GetTrack()->GetParticleDefinition()->GetPDGCharge() == 0 or
        step.GetStepLength() < fCachedMapMinDeltaX) {
        FillMapByPoint(post.GetPosition(), eDep, dose);
    } else {
        FillMapBySegment(pre.GetPosition(), post.GetPosition(), eDep, dose);
    }
}

auto Analysis::RunBeginUserAction(int) -> void {
    const auto dx{MapDeltaX()};
    const auto dy{MapDeltaY()};
    const auto dz{MapDeltaZ()};
    fCachedMapDeltaV = dx * dy * dz;
    fCachedMapMinDeltaX = std::min({dx, dy, dz});

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

auto Analysis::FillMapByPoint(G4ThreeVector x, double eDep, double dose) const -> void {
    fEdepMap->Fill(x.x(), x.y(), x.z(), eDep / joule);
    fDoseMap->Fill(x.x(), x.y(), x.z(), dose / gray);
}

auto Analysis::FillMapBySegment(G4ThreeVector x0, G4ThreeVector x, double eDep, double dose) const -> void {
    const auto deltaX{x - x0};
    const auto nFill{muc::lltrunc(deltaX.mag() / fCachedMapMinDeltaX) + 1};

    eDep /= nFill;
    dose /= nFill;

    const auto deltaFill{deltaX / nFill};
    auto xFill{x0 + deltaFill / 2};
    for (int i{}; i < nFill; ++i) {
        FillMapByPoint(xFill, eDep, dose);
        xFill += deltaFill;
    }
}

} // namespace MACE::SimDose
