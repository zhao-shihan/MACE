#include "MonteCarlo.hh"

using namespace MACE::SimMTransport;

#define MONTE_CARLO_STOCK_INIT(name, type, stockSize) \
    name##Stock(new type[stockSize]), \
    name##StockEnd(name##Stock + stockSize), \
    name##Iter(name##StockEnd)

static Global* global = nullptr;

MonteCarlo::MonteCarlo() :
    fEngine(new TRandom3(Global::Instance()->SeedForWorker0() + Global::Instance()->CommRank())),
    MONTE_CARLO_STOCK_INIT(fVertexTime, double_t, MonteCarloInitStockSize),
    MONTE_CARLO_STOCK_INIT(fVertexPosition, Vector3, MonteCarloInitStockSize),
    MONTE_CARLO_STOCK_INIT(fLife, double_t, MonteCarloInitStockSize),
    MONTE_CARLO_STOCK_INIT(fMB, Vector3, MonteCarloStockSize),
    MONTE_CARLO_STOCK_INIT(fFreePath, double_t, MonteCarloStockSize) {
    global = Global::Instance();
}

MonteCarlo::~MonteCarlo() {
    delete fEngine;
    delete[] fVertexTimeStock;
    delete[] fVertexPositionStock;
    delete[] fLifeStock;
    delete[] fMBStock;
    delete[] fFreePathStock;
}

inline bool Target(double_t x, double_t y, double_t z) {
    return (*global->Target())(x, y, z) > 0.5;
}

inline double_t MeanFreePath(double_t x, double_t y, double_t z) {
    return (*global->MeanFreePath())(x, y, z);
}

#define CHECK_FILL_RETURN(name) \
    if (name##Iter == name##StockEnd) { \
        for (name##Iter = name##Stock; name##Iter < name##StockEnd; ++name##Iter) \
            Set##name(name##Iter); \
        name##Iter = name##Stock; \
    } \
    ++name##Iter; \
    return *(name##Iter - 1)

double_t MonteCarlo::VertexTime() {
    const auto SetfVertexTime = [this](double_t* iter)->void {
        *iter = fEngine->Uniform(global->BeginTime(), global->EndTime());
    };
    CHECK_FILL_RETURN(fVertexTime);
}

const Vector3& MonteCarlo::VertexPosition() {
    const auto SetfVertexPosition = [this](Vector3* iter)->void {
        do {
            global->Source()->GetRandom3(iter->x, iter->y, iter->z, fEngine);
        } while (!Target(iter->x, iter->y, iter->z));
    };
    CHECK_FILL_RETURN(fVertexPosition);
}

double_t MonteCarlo::Life() {
    const auto SetfLife = [this](double_t* iter)->void {
        *iter = -global->MuoniumLife() * log(fEngine->Rndm());
    };
    CHECK_FILL_RETURN(fLife);
}

const Vector3& MonteCarlo::MaxwellBoltzmann() {
    const double_t sigmaV = cLight * sqrt(kBoltzmann * global->Temperature() / global->MuoniumMass());
    const auto SetfMB = [this, &sigmaV](Vector3* iter)->void {
        iter->x = fEngine->Gaus(0.0, sigmaV);
        iter->y = fEngine->Gaus(0.0, sigmaV);
        iter->z = fEngine->Gaus(0.0, sigmaV);
    };
    CHECK_FILL_RETURN(fMB);
}

double_t MonteCarlo::FreePath(const Vector3& pos) {
    const auto SetfFreePath = [this, &pos](double_t* iter)->void {
        *iter = -MeanFreePath(pos.x, pos.y, pos.z) * log(fEngine->Rndm());
    };
    CHECK_FILL_RETURN(fFreePath);
}

