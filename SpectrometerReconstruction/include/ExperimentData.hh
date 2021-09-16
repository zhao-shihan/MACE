#pragma once

#include <list>

#include "SpectrometerReconstructionGlobal.hh"
#include "Hit.hh"

namespace MACE::SpectrometerReconstruction {
    using HitList = std::vector<Hit>;
    using ExperimentDataBase = std::vector<HitList>;
}

class MACE::SpectrometerReconstruction::ExperimentData final : public ExperimentDataBase {
    MACE_SPECTROMETER_RECONSTRUCTION_NOT_ALLOW_TO_COPY_BUT_ALLOW_TO_MOVE(ExperimentData);
public:
    ExperimentData(const char* rootFile);
};