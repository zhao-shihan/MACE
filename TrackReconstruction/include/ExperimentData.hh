#pragma once

#include "TrackReconstructionGlobal.hh"
#include "Hit.hh"

namespace MACE::TrackReconstruction {
    using ExperimentDataBase = std::vector<PluseData>;
}

class MACE::TrackReconstruction::ExperimentData final : public ExperimentDataBase {
    MACE_TRACK_RECONSTRUCTION_NOT_ALLOW_TO_COPY_BUT_ALLOW_TO_MOVE(ExperimentData);
public:
    ExperimentData(const char* rootFile);
};