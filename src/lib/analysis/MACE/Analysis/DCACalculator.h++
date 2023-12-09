/* #pragma once

#include "MACE/Compatibility/std2b/constexpr_cmath.h++"
#include "MACE/DataModel/Hit/MCPHit.h++"
#include "MACE/DataModel/Track/CDCHelixTrack.h++"
#include "MACE/DataModel/Track/CDCPhysicsTrack.h++"
#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Detector/Field/SpectrometerField.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Math/Norm.h++"
#include "MACE/Utility/VectorArithmeticOperator.h++"

#include <concepts>

namespace MACE::Analysis {

class DCACalculator final {
public:
    AFloat Compute(const DataModel::CDCPhysicsTrack& cdcTrack, const DataModel::MCPHit& mcpHit) const;
    AFloat Compute(const DataModel::CDCHelixTrack& cdcTrack, const DataModel::MCPHit& mcpHit) const;

private:
    AFloat ComputePointCircleDCA(const AFloat r, const stdx::array2<AFloat> center, const stdx::array2<AFloat> point) const;

private:
    Detector::Field::SpectrometerField fSpectrometerField;
};

} // namespace MACE::Analysis

#include "MACE/Analysis/DCACalculator.inl"
 */