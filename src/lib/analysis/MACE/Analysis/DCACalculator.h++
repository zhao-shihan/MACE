/* #pragma once

#include "MACE/Compatibility/std23/constexpr_cmath.h++"
#include "MACE/DataModel/Hit/MCPHit.h++"
#include "MACE/DataModel/Track/CDCHelixTrack.h++"
#include "MACE/DataModel/Track/CDCPhysicsTrack.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Field/MMSField.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Math/Norm.h++"
#include "MACE/Utility/VectorArithmeticOperator.h++"

#include <concepts>

namespace MACE::Analysis {

class DCACalculator final {
public:
    AFloat Compute(const DataModel::CDCPhysicsTrack& mmsTrack, const DataModel::MCPHit& mcpHit) const;
    AFloat Compute(const DataModel::CDCHelixTrack& mmsTrack, const DataModel::MCPHit& mcpHit) const;

private:
    AFloat ComputePointCircleDCA(const AFloat r, const stdx::array2<AFloat> center, const stdx::array2<AFloat> point) const;

private:
    Detector::Field::MMSField fMMSField;
};

} // namespace MACE::Analysis

#include "MACE/Analysis/DCACalculator.inl"
 */