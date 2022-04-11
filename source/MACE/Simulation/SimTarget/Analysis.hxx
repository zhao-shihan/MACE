#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Simulation/SimTarget/MuoniumTrack.hxx"
#include "MACE/Utility/MPITool/MPIFileTools.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "globals.hh"

#include "TFile.h"

namespace MACE::Simulation::SimTarget {

using Core::DataFactory;
using MACE::Utility::ObserverPtr;
using MACE::Utility::MPITool::MPIFileTools;

class Analysis final {
public:
    static Analysis& Instance();

private:
    Analysis();
    ~Analysis() noexcept = default;
    Analysis(const Analysis&) = delete;
    Analysis& operator=(const Analysis&) = delete;

public:
    void SetResultName(const G4String& resultName) { fResultName = resultName; }
    const G4String& GetResultName() const { return fResultName; }

    void Open(Option_t* option = "recreate");
    void SubmitMuoniumTrack(std::unique_ptr<MuoniumTrack>&& newTrack) { fMuoniumTrackList.emplace_back(std::move(newTrack)); }
    void Write(G4int runID);
    void Close(Option_t* option = nullptr);
    int Merge(G4bool forced = false);

private:
    G4String fResultName = "SimTarget_result";
    std::unique_ptr<TFile> fFile;
    std::unique_ptr<MPIFileTools> fMPIFileTools;
    std::vector<std::unique_ptr<MuoniumTrack>> fMuoniumTrackList;
    DataFactory fDataFactory;
};

} // namespace MACE::Simulation::SimTarget
