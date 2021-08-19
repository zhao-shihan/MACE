#ifndef Global_hh
#define Global_hh 1

#include <iostream>
#include "mpi.h"
#include "Vector3.hh"
#include "Config.hh"

// Unit system:
//  us = 1.0;
//  um = 1.0;
//  MeV = 1.0;
//  kelvin = 1.0;
//  rad = 1.0;
constexpr double_t cLight = 299792458.0;
constexpr double_t kBoltzmann = 8.617333262145178152e-11;

#ifdef TO_STR
#error "Conflict of #define TO_STR."
#else
#define TO_STR(str) #str
#endif
#ifdef CFG_TO_STR
#error "Conflict of #define CFG_TO_STR."
#else
#define CFG_TO_STR(cfg) TO_STR(cfg)
#endif 

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

constexpr const char* gName = CFG_TO_STR(NAME);
constexpr const char* gTargetFormula = CFG_TO_STR(TARGET_REGION);
inline          bool  gTarget(double_t x, double_t y, double_t z) { return TARGET_REGION; }
constexpr   double_t  gStepOfPushing = STEP_OF_PUSHING;
#ifdef PERIODIC_BOUNDARY_X
constexpr   double_t  gPeriodicBoundaryX = PERIODIC_BOUNDARY_X;
static_assert(gPeriodicBoundaryX > 0, "Periodic boundary conditions require a number greater than zero. If you do not need to compile this periodic boundary condition, simply do not #define it.");
#endif
#ifdef PERIODIC_BOUNDARY_Y
constexpr   double_t  gPeriodicBoundaryY = PERIODIC_BOUNDARY_Y;
static_assert(gPeriodicBoundaryY > 0, "Periodic boundary conditions require a number greater than zero. If you do not need to compile this periodic boundary condition, simply do not #define it.");
#endif
#ifdef PERIODIC_BOUNDARY_Z
constexpr   double_t  gPeriodicBoundaryZ = PERIODIC_BOUNDARY_Z;
static_assert(gPeriodicBoundaryZ > 0, "Periodic boundary conditions require a number greater than zero. If you do not need to compile this periodic boundary condition, simply do not #define it.");
#endif
constexpr   double_t  gMuoniumLife = MUONIUM_LIFE;
constexpr   double_t  gMuoniumMass = MUONIUM_MASS;
constexpr const char* gMeanFreePathFormula = CFG_TO_STR(MEAN_FREE_PATH);
inline      double_t  gMeanFreePath(double_t x, double_t y, double_t z) { return MEAN_FREE_PATH; }
constexpr   double_t  gTemperature = TEMPERATURE;
constexpr const char* gSourceFormula = CFG_TO_STR(SOURCE);
inline      double_t  gSource(double_t x, double_t y, double_t z) { return SOURCE; }
constexpr   double_t  gSourceXMin = SOURCE_X_MIN;
constexpr   double_t  gSourceXMax = SOURCE_X_MAX;
constexpr   double_t  gSourceYMin = SOURCE_Y_MIN;
constexpr   double_t  gSourceYMax = SOURCE_Y_MAX;
constexpr   double_t  gSourceZMin = SOURCE_Z_MIN;
constexpr   double_t  gSourceZMax = SOURCE_Z_MAX;
constexpr     size_t  gMuoniumNum = MUONIUM_NUM;
constexpr   double_t  gBeginTime = BEGIN_TIME;
constexpr   double_t  gOutputStep = OUTPUT_STEP;
constexpr   double_t  gEndTime = END_TIME;
constexpr   uint64_t  gGlobSeed = SEED;
constexpr     size_t  gWorkerJobSize = WORKER_JOB_SIZE;

#pragma GCC diagnostic pop

class MPIGlobal {
public:
    const int fCommRank;
    const int fCommSize;
    const int fMasterRank;
    const int fWorkerNum;

    static void Initialize(int* argc, char*** argv);
    static void Finalize();

private:
    MPIGlobal(int commRank, int commSize);
    ~MPIGlobal();
    MPIGlobal(const MPIGlobal&) = delete;
    MPIGlobal& operator=(const MPIGlobal&) = delete;
};
extern const MPIGlobal* gMPIGlobal;
#define gCommRank gMPIGlobal->fCommRank
#define gCommSize gMPIGlobal->fCommSize
#define gMasterRank gMPIGlobal->fMasterRank // = gCommSize - 1.
#define gWorkerNum gMPIGlobal->fWorkerNum // = gCommSize - 1.

#undef NAME
#undef TARGET_REGION
#undef STEP_OF_PUSHING
#undef MUONIUM_LIFE
#undef MUONIUM_MASS
#undef MEAN_FREE_PATH
#undef TEMPERATURE
#undef SOURCE
#undef SOURCE_X_MIN
#undef SOURCE_X_MAX
#undef SOURCE_Y_MIN
#undef SOURCE_Y_MAX
#undef SOURCE_Z_MIN
#undef SOURCE_Z_MAX
#undef MUONIUM_NUM
#undef BEGIN_TIME
#undef OUTPUT_STEP
#undef END_TIME
#undef SEED
#undef WORKER_JOB_SIZE
#undef TO_STR
#undef CFG_TO_STR

#include "MACEGlobal.hh"

namespace MACE {
    namespace SimMuTransport {
        class Analysis;
        class Master;
        class MonteCarlo;
        struct Muonium;
        class RunManager;
        class Track;
        struct Vector3;
        class Worker;
    }
}

#endif

