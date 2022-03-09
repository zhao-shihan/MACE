#pragma once

namespace MACE {

    // FIXME: using inline namespace at this level (just under MACE) confuses VSCode's C++ extension. Maybe conflicts with the C++ standard? 
    // inline namespace Reconstruction {

    namespace ReconCalorimeter {}

    namespace ReconMuonium {}

    namespace ReconTracks {
        namespace Fitter {
            template<class SpectrometerHit_t, class Track_t> class DirectLeastSquare;
            template<class SpectrometerHit_t, class Track_t> class Dummy;
            template<class SpectrometerHit_t, class Track_t> class PerfectFitter;
        }
        namespace Interface {
            template<class SpectrometerHit_t, class Track_t> class Fitter;
            template<template<class H, class T> class FitterT_t, class SpectrometerHit_t, class Track_t> class Tracker;
        }
        namespace Tracker {
            template<template<class H, class T> class FitterT_t, class SpectrometerHit_t, class Track_t> class Hough;
            template<template<class H, class T> class FitterT_t, class SpectrometerHit_t, class Track_t> class PerfectFinder;
        }
    }

    // } // inline namespace Reconstruction

} // namespace MACE
