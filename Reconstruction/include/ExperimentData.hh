#pragma once

#include "ReconstructionGlobal.hh"
#include "digitized/SpectrometerHit.hh"
#include "digitized/CalorimeterHit.hh"
#include "digitized/OrbitalDetectorHit.hh"

namespace MACE::Reconstruction {
    enum {
        kCalorimeter,
        kOrbitalDetector,
        kSpectrometer
    };

    using PluseData = std::tuple<DataModel::SpectrometerHit, DataModel::OrbitalDetectorHit, DataModel::CalorimeterHit>;
    using ExperimentDataType = std::vector<PluseData>;
    using PluseDataPointerList = std::vector<const PluseData*>;
}

class MACE::Reconstruction::ExperimentData final  {
    MACE_RECONSTRUCTION_NOT_ALLOW_TO_COPY_BUT_ALLOW_TO_MOVE(ExperimentData);
public:
    ExperimentData(const char* rootFile);

private:
    void ReadCalorimeter();
    void ReadOrbitalDetector();
    void ReadSpectrometer();

private:
    std::vector<PluseData> fData;
};