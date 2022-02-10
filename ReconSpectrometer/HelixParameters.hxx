#pragma once

#include "ReconSpectrometer/Global.hxx"

struct MACE::ReconSpectrometer::HelixParameters {
    double xCenter;
    double yCenter;
    double radius;
    double z0;
    double alpha;
};

namespace MACE::ReconSpectrometer {
    constexpr auto defaultHelixParameters = HelixParameters{ 0.0, 0.0, 0.0, 0.0, 0.0 };
}