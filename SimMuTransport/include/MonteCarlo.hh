#ifndef MonteCarlo_hh
#define MonteCarlo_hh 1

#include "TRandom3.h"
#include "TF3.h"

#include "Global.hh"

constexpr size_t kB = 1024;
constexpr size_t MonteCarloInitStockTotalCapacity = 512 * kB;
constexpr size_t MonteCarloStockTotalCapacity = 4096 * kB;

constexpr size_t MonteCarloInitStockSize = MonteCarloInitStockTotalCapacity / (2 * sizeof(double_t) + sizeof(MACE::SimMuTransport::Vector3));
constexpr size_t MonteCarloStockSize = MonteCarloStockTotalCapacity / (sizeof(MACE::SimMuTransport::Vector3) + sizeof(double_t));

#define MONTE_CARLO_STOCK_DECL(type, name) \
    type* const name##Stock; \
    type* const name##StockEnd; \
    type*       name##Iter

class MACE::SimMuTransport::MonteCarlo {
private:
    TRandom* const fEngine;
    TF3* const fSource;
    MONTE_CARLO_STOCK_DECL(double_t, fVertexTime);
    MONTE_CARLO_STOCK_DECL(Vector3, fVertexPosition);
    MONTE_CARLO_STOCK_DECL(double_t, fLife);
    MONTE_CARLO_STOCK_DECL(Vector3, fMB);
    MONTE_CARLO_STOCK_DECL(double_t, fFreePath);

public:
    MonteCarlo();
    ~MonteCarlo();
    MonteCarlo(const MonteCarlo&) = delete;
    MonteCarlo& operator=(const MonteCarlo&) = delete;

    double_t           VertexTime();
    const Vector3& VertexPosition();
    double_t           Life();
    const Vector3& MaxwellBoltzmann();
    double_t           FreePath(const Vector3& pos);
};

#endif

