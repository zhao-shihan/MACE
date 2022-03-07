#pragma once

namespace MACE {

    // FIXME: using inline namespace at this level (just under MACE) confuses VSCode's C++ extension. Maybe conflicts with the C++ standard? 
    // inline namespace Reconstruction {

    namespace ReconCalorimeter {}

    namespace ReconSpectrometer {
        namespace Fitter {
            template<class SpectromrterHit_t, class Track_t> class DirectLeastSquare;
            template<class SpectromrterHit_t, class Track_t> class Dummy;
        }
        namespace Interface {
            template<class SpectromrterHit_t, class Track_t> class Fitter;
            template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t> class Tracker;
        }
        namespace Tracker {
            template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t> class Hough;
            template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t> class TrueFinder;
        }
    }

    // } // inline namespace Reconstruction

} // namespace MACE
