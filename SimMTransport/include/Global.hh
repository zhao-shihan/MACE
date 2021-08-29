#pragma once

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
namespace MACE {
    namespace SimMTransport {
        constexpr double_t cLight = 299792458.0;
        constexpr double_t kBoltzmann = 8.617333262145178152e-11;
    }
}

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
