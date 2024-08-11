#pragma once

#include "MACE/Detector/Field/MMSField.h++"

#include "Mustard/Utility/ConvertG3G4Unit.h++"
#include "Mustard/Utility/InlineMacro.h++"

#include "AbsBField.h"

#include "TVector3.h"

#include "muc/array"

namespace MACE::inline Reconstruction::MMSTracking::inline Field {

class GenFitMMSField : public genfit::AbsBField {
public:
    MUSTARD_STRONG_INLINE virtual auto get(const TVector3& x) const -> TVector3 override;
    MUSTARD_STRONG_INLINE virtual auto get(const double& x, const double& y, const double& z, double& Bx, double& By, double& Bz) const -> void override;

private:
    Detector::Field::MMSField fMMSField;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Field

#include "MACE/Reconstruction/MMSTracking/Field/GenFitMMSField.inl"
