#pragma once

#include "TRandom3.h"
#include "TF3.h"

#include "TEveVector.h"

#include "Global.hxx"

constexpr size_t kB = 1024;
constexpr size_t MonteCarloInitStockTotalCapacity = 512 * kB;
constexpr size_t MonteCarloStockTotalCapacity = 4096 * kB;

constexpr size_t MonteCarloInitStockSize = MonteCarloInitStockTotalCapacity / (2 * sizeof(double) + sizeof(TEveVectorD));
constexpr size_t MonteCarloStockSize = MonteCarloStockTotalCapacity / (sizeof(TEveVectorD) + sizeof(double));

#define MONTE_CARLO_STOCK_DECL(type, name) \
    type* const name##Stock; \
    type* const name##StockEnd; \
    type*       name##Iter

class MACE::SimMTransport::MonteCarlo {
private:
    TRandom* const fEngine;
    MONTE_CARLO_STOCK_DECL(double, fVertexTime);
    MONTE_CARLO_STOCK_DECL(TEveVectorD, fVertexPosition);
    MONTE_CARLO_STOCK_DECL(double, fLife);
    MONTE_CARLO_STOCK_DECL(TEveVectorD, fMB);
    MONTE_CARLO_STOCK_DECL(double, fFreePath);

public:
    MonteCarlo();
    ~MonteCarlo();
    MonteCarlo(const MonteCarlo&) = delete;
    MonteCarlo& operator=(const MonteCarlo&) = delete;

    double                 VertexTime();
    const TEveVectorD& VertexPosition();
    double                 Life();
    const TEveVectorD& MaxwellBoltzmann();
    double                 FreePath(const TEveVectorD& pos);
};
