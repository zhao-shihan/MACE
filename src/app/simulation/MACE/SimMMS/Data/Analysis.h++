#pragma once

#include "MACE/Data/CDCTrack.h++"
#include "MACE/Data/Output.h++"
#include "MACE/Data/SimDecayVertex.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimMMS/Data/AnalysisMessenger.h++"

#include "G4Types.hh"

#include "gsl/gsl"

#include <filesystem>
#include <memory>
#include <utility>

class TFile;

namespace MACE::inline Simulation::inline Hit {
class CDCHit;
class STCHit;
} // namespace MACE::inline Simulation::inline Hit

namespace MACE::SimMMS::Data {

class Analysis final : public Env::Memory::PassiveSingleton<Analysis> {
public:
    Analysis();

    auto FilePath(std::filesystem::path path) -> void { fFilePath = std::move(path); }
    auto FileMode(std::string mode) -> void { fFileMode = std::move(mode); }
    auto CoincidenceWithCDC(bool val) -> void { fCoincidenceWithCDC = val; }
    auto CoincidenceWithSTC(bool val) -> void { fCoincidenceWithSTC = val; }
    auto SaveCDCHitData(bool val) -> void { fSaveCDCHitData = val; }

    auto RunBegin(G4int runID) -> void;

    auto SubmitDecayVertexData(const std::vector<std::unique_ptr<MACE::Data::Tuple<MACE::Data::SimDecayVertex>>>& data) -> void { fDecayVertex = &data; }
    auto SubmitCDCHC(gsl::not_null<const std::vector<gsl::owner<Simulation::CDCHit*>>*> hc) -> void { fCDCHit = hc; }
    auto SubmitCDCTrackData(const std::vector<std::unique_ptr<MACE::Data::Tuple<MACE::Data::CDCSimTrack>>>& data) -> void { fCDCTrack = &data; }
    auto SubmitSTCHC(gsl::not_null<const std::vector<gsl::owner<Simulation::STCHit*>>*> hc) -> void { fSTCHit = hc; }
    auto EventEnd() -> void;

    auto RunEnd(Option_t* option = {}) -> void;

private:
    std::filesystem::path fFilePath;
    std::string fFileMode;
    bool fCoincidenceWithCDC;
    bool fCoincidenceWithSTC;
    bool fSaveCDCHitData;

    std::filesystem::path fLastUsedFullFilePath;

    gsl::owner<TFile*> fFile;
    std::optional<MACE::Data::Output<MACE::Data::SimDecayVertex>> fDecayVertexOutput;
    std::optional<MACE::Data::Output<MACE::Data::CDCSimHit>> fCDCSimHitOutput;
    std::optional<MACE::Data::Output<MACE::Data::CDCSimTrack>> fCDCSimTrackOutput;
    std::optional<MACE::Data::Output<MACE::Data::STCSimHit>> fSTCSimHitOutput;

    const std::vector<std::unique_ptr<MACE::Data::Tuple<MACE::Data::SimDecayVertex>>>* fDecayVertex;
    const std::vector<gsl::owner<Simulation::CDCHit*>>* fCDCHit;
    const std::vector<std::unique_ptr<MACE::Data::Tuple<MACE::Data::CDCSimTrack>>>* fCDCTrack;
    const std::vector<gsl::owner<Simulation::STCHit*>>* fSTCHit;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimMMS::Data
