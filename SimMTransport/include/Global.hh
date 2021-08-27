#ifndef Global_hh
#define Global_hh 1

#include <iostream>

#include "TF3.h"

#include "mpi.h"

#include "MACEGlobal.hh"
#include "Vector3.hh"

// Unit system:
//  us = 1.0;
//  um = 1.0;
//  MeV = 1.0;
//  kelvin = 1.0;
//  rad = 1.0;
constexpr double_t cLight = 299792458.0;
constexpr double_t kBoltzmann = 8.617333262145178152e-11;
/*
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

constexpr const char* Global::Instance()->Name() = CFG_TO_STR(NAME);
constexpr const char* Global::Instance()->Target()Formula = CFG_TO_STR(TARGET_REGION);
inline          bool  Global::Instance()->Target()(double_t x, double_t y, double_t z) { return TARGET_REGION; }
constexpr   double_t  Global::Instance()->StepOfPushing() = STEP_OF_PUSHING;
#ifdef PERIODIC_BOUNDARY_X
constexpr   double_t  Global::Instance()->PeriodicBoundaryX() = PERIODIC_BOUNDARY_X;
static_assert(Global::Instance()->PeriodicBoundaryX() > 0, "Periodic boundary conditions require a number greater than zero. If you do not need to compile this periodic boundary condition, simply do not #define it.");
#endif
#ifdef PERIODIC_BOUNDARY_Y
constexpr   double_t  Global::Instance()->PeriodicBoundaryY() = PERIODIC_BOUNDARY_Y;
static_assert(Global::Instance()->PeriodicBoundaryY() > 0, "Periodic boundary conditions require a number greater than zero. If you do not need to compile this periodic boundary condition, simply do not #define it.");
#endif
#ifdef PERIODIC_BOUNDARY_Z
constexpr   double_t  Global::Instance()->PeriodicBoundaryZ() = PERIODIC_BOUNDARY_Z;
static_assert(Global::Instance()->PeriodicBoundaryZ() > 0, "Periodic boundary conditions require a number greater than zero. If you do not need to compile this periodic boundary condition, simply do not #define it.");
#endif
constexpr   double_t  Global::Instance()->MuoniumLife() = MUONIUM_LIFE;
constexpr   double_t  Global::Instance()->MuoniumMass() = MUONIUM_MASS;
constexpr const char* Global::Instance()->MeanFreePath()Formula = CFG_TO_STR(MEAN_FREE_PATH);
inline      double_t  Global::Instance()->MeanFreePath()(double_t x, double_t y, double_t z) { return MEAN_FREE_PATH; }
constexpr   double_t  Global::Instance()->Temperature() = TEMPERATURE;
constexpr const char* gSourceFormula = CFG_TO_STR(SOURCE);
inline      double_t  gSource(double_t x, double_t y, double_t z) { return SOURCE; }
constexpr   double_t  gSourceXMin = SOURCE_X_MIN;
constexpr   double_t  gSourceXMax = SOURCE_X_MAX;
constexpr   double_t  gSourceYMin = SOURCE_Y_MIN;
constexpr   double_t  gSourceYMax = SOURCE_Y_MAX;
constexpr   double_t  gSourceZMin = SOURCE_Z_MIN;
constexpr   double_t  gSourceZMax = SOURCE_Z_MAX;
constexpr     size_t  Global::Instance()->MuoniumNum() = MUONIUM_NUM;
constexpr   double_t  Global::Instance()->BeginTime() = BEGIN_TIME;
constexpr   double_t  Global::Instance()->OutputStep() = OUTPUT_STEP;
constexpr   double_t  Global::Instance()->EndTime() = END_TIME;
constexpr   uint64_t  Global::Instance()->SeedForWorker0() = SEED;
constexpr     size_t  Global::Instance()->WorkerJobSize() = WORKER_JOB_SIZE;

#pragma GCC diagnostic pop */

#define MACE_SIMMTRANSPORT_GLOBAL_MEMBER(T, Name, defaultVal) \
public: \
    T const& Name() const { return f##Name; } \
    void Set##Name(T const& val) { f##Name = val; } \
private: \
    T f##Name = defaultVal

#define MACE_SIMMTRANSPORT_GLOBAL_MEMBER_POINT_TO_OBJ(T, Name, defaultVal) \
public: \
    T* Name() const { return f##Name; } \
    void Set##Name(T* val) { \
        delete f##Name; \
        f##Name = val; \
    } \
private: \
    T* f##Name = defaultVal

class MACE::SimMTransport::Global {
private:
    Global() {}
    ~Global();
    Global(const Global&) = delete;
    Global& operator=(const Global&) = delete;

public:
    static Global* Instance();
    static void Initialize(int& argc, char**& argv);
    static void Finalize();

    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(int, CommRank, -1);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(int, CommSize, -1);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(int, MasterRank, -1);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(int, WorkerNum, -1);
    
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(std::string, Name, "");
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER_POINT_TO_OBJ(TF3, Target, nullptr);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(double_t, StepOfPushing, -1);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(double_t, PeriodicBoundaryX, -1);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(double_t, PeriodicBoundaryY, -1);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(double_t, PeriodicBoundaryZ, -1);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(double_t, MuoniumLife, -1);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(double_t, MuoniumMass, -1);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER_POINT_TO_OBJ(TF3, MeanFreePath, nullptr);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(double_t, Temperature, -1);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER_POINT_TO_OBJ(TF3, Source, nullptr);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(size_t, MuoniumNum, 0);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(double_t, BeginTime, -1);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(double_t, OutputStep, -1);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(double_t, EndTime, -1);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(uint64_t, SeedForWorker0, 4357);
    MACE_SIMMTRANSPORT_GLOBAL_MEMBER(size_t, WorkerJobSize, 1000);
};

#undef MACE_SIMMTRANSPORT_GLOBAL_MEMBER
#undef MACE_SIMMTRANSPORT_GLOBAL_MEMBER_POINT_TO_OBJ

#endif

