#include "MACE/SimDose/Analysis.h++"

#include "Mustard/Env/MPIEnv.h++"

#include "TH3F.h"

#include "G4ParticleDefinition.hh"
#include "G4StepPoint.hh"
#include "G4SystemOfUnits.hh"

#include "muc/math"

#include "fmt/core.h"

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>

namespace MACE::SimDose {

Analysis::Analysis() :
    AnalysisBase{},
    fMapModel{},
    fMap{},
    fMessengerRegister{this} {}

auto Analysis::AddMap(std::string name) -> void {
    fMapModel.emplace_back().name = std::move(name);
}

auto Analysis::MapNBinX(int val) -> void {
    CheckMapAdded();
    fMapModel.back().nBinX = val;
}

auto Analysis::MapXMin(double val) -> void {
    CheckMapAdded();
    fMapModel.back().xMin = val;
}

auto Analysis::MapXMax(double val) -> void {
    CheckMapAdded();
    fMapModel.back().xMax = val;
}

auto Analysis::MapNBinY(int val) -> void {
    CheckMapAdded();
    fMapModel.back().nBinY = val;
}

auto Analysis::MapYMin(double val) -> void {
    CheckMapAdded();
    fMapModel.back().yMin = val;
}

auto Analysis::MapYMax(double val) -> void {
    CheckMapAdded();
    fMapModel.back().yMax = val;
}

auto Analysis::MapNBinZ(int val) -> void {
    CheckMapAdded();
    fMapModel.back().nBinZ = val;
}

auto Analysis::MapZMin(double val) -> void {
    CheckMapAdded();
    fMapModel.back().zMin = val;
}

auto Analysis::MapZMax(double val) -> void {
    CheckMapAdded();
    fMapModel.back().zMax = val;
}

auto Analysis::FillMap(const G4Step& step) const -> void {
    if (step.GetTotalEnergyDeposit() == 0) { return; }

    const auto eDep{step.GetTotalEnergyDeposit()};
    const auto& pre{*step.GetPreStepPoint()};
    const auto& post{*step.GetPostStepPoint()};
    const auto x0{pre.GetPosition()};
    const auto x{post.GetPosition()};
    const auto neutral{step.GetTrack()->GetParticleDefinition()->GetPDGCharge() == 0};

    for (auto&& [eDepMap, doseMap, deltaV, minDelta] : std::as_const(fMap)) {
        const auto Fill{
            [&](G4ThreeVector x, double eDep, double dose) {
                eDepMap->Fill(x.x(), x.y(), x.z(), eDep / joule);
                doseMap->Fill(x.x(), x.y(), x.z(), dose / gray);
            }};

        const auto deltaM{pre.GetMaterial()->GetDensity() * deltaV};
        const auto dose{eDep / deltaM};

        if (neutral or step.GetStepLength() < minDelta) {
            Fill(x, eDep, dose);
        } else {
            const auto segment{x - x0};
            const auto nFill{muc::lltrunc(segment.mag() / minDelta) + 1};

            const auto eDepFill{eDep / nFill};
            const auto doseFill{dose / nFill};
            const auto deltaFill{segment / nFill};

            auto xFill{x0 + deltaFill / 2};
            for (int i{}; i < nFill; ++i) {
                Fill(xFill, eDepFill, doseFill);
                xFill += deltaFill;
            }
        }
    }
}

auto Analysis::RunBeginUserAction(int) -> void {
    fMap.reserve(fMapModel.size());
    for (auto&& [name, nBinX, xMin, xMax, nBinY, yMin, yMax, nBinZ, zMin, zMax] : std::as_const(fMapModel)) {
        if (nBinX == 0) { throw std::runtime_error{"Map nBinX == 0"}; }
        if (nBinY == 0) { throw std::runtime_error{"Map nBinY == 0"}; }
        if (nBinZ == 0) { throw std::runtime_error{"Map nBinZ == 0"}; }
        if (xMin >= xMax) { throw std::runtime_error{"Map xMin >= xMax"}; }
        if (yMin >= yMax) { throw std::runtime_error{"Map yMin >= yMax"}; }
        if (zMin >= zMax) { throw std::runtime_error{"Map zMin >= zMax"}; }

        auto& map{fMap.emplace_back()};

        map.eDepMap = new TH3F{fmt::format("{}EdepMap", name).c_str(),
                               "Energy deposition (J)",
                               nBinX, xMin, xMax,
                               nBinY, yMin, yMax,
                               nBinZ, zMin, zMax};
        map.doseMap = new TH3F{fmt::format("{}DoseMap", name).c_str(),
                               "Absorbed dose (Gy)",
                               nBinX, xMin, xMax,
                               nBinY, yMin, yMax,
                               nBinZ, zMin, zMax};

        const auto dx{(xMax - xMin) / nBinX};
        const auto dy{(yMax - yMin) / nBinY};
        const auto dz{(zMax - zMin) / nBinZ};
        map.deltaV = dx * dy * dz;
        map.minDelta = std::min({dx, dy, dz});
    }
}

auto Analysis::RunEndUserAction(int runID) -> void {
    gDirectory->mkdir(fmt::format("G4Run{}", runID).c_str(), "", true)->cd();
    for (auto&& [eDepMap, doseMap, _, __] : std::as_const(fMap)) {
        eDepMap->Write();
        doseMap->Write();
    }
    fMap.clear();
}

auto Analysis::CheckMapAdded() -> void {
    if (fMapModel.empty()) {
        throw std::runtime_error{"no map was added"};
    }
}

} // namespace MACE::SimDose
