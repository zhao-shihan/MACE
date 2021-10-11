#pragma once

#include "TRandom3.h"
#include "TF3.h"

#include "CLHEP/Vector/ThreeVector.h"

#include "Global.hh"

constexpr size_t kB = 1024;
constexpr size_t MonteCarloInitStockTotalCapacity = 512 * kB;
constexpr size_t MonteCarloStockTotalCapacity = 4096 * kB;

constexpr size_t MonteCarloInitStockSize = MonteCarloInitStockTotalCapacity / (2 * sizeof(double_t) + sizeof(CLHEP::Hep3Vector));
constexpr size_t MonteCarloStockSize = MonteCarloStockTotalCapacity / (sizeof(CLHEP::Hep3Vector) + sizeof(double_t));

#define MONTE_CARLO_STOCK_DECL(type, name) \
    type* const name##Stock; \
    type* const name##StockEnd; \
    type*       name##Iter

class MACE::SimMTransport::MonteCarlo {
private:
    TRandom* const fEngine;
    MONTE_CARLO_STOCK_DECL(double_t, fVertexTime);
    MONTE_CARLO_STOCK_DECL(CLHEP::Hep3Vector, fVertexPosition);
    MONTE_CARLO_STOCK_DECL(double_t, fLife);
    MONTE_CARLO_STOCK_DECL(CLHEP::Hep3Vector, fMB);
    MONTE_CARLO_STOCK_DECL(double_t, fFreePath);

public:
    MonteCarlo();
    ~MonteCarlo();
    MonteCarlo(const MonteCarlo&) = delete;
    MonteCarlo& operator=(const MonteCarlo&) = delete;

    double_t                 VertexTime();
    const CLHEP::Hep3Vector& VertexPosition();
    double_t                 Life();
    const CLHEP::Hep3Vector& MaxwellBoltzmann();
    double_t                 FreePath(const CLHEP::Hep3Vector& pos);
};
