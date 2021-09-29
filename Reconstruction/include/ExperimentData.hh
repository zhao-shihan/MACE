#pragma once

#include "ReconstructionGlobal.hh"
#include "datamodel/SpectrometerHit.hh"

namespace MACE::Reconstruction {
    using ExperimentDataBase = std::vector<PluseData>;
}

class MACE::Reconstruction::ExperimentData final : public ExperimentDataBase {
    MACE_TRACK_RECONSTRUCTION_NOT_ALLOW_TO_COPY_BUT_ALLOW_TO_MOVE(ExperimentData);
public:
    ExperimentData(const char* rootFile);
};