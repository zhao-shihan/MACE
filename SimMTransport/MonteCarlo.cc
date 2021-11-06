#include "MonteCarlo.hh"

using namespace MACE::SimMTransport;

#define MONTE_CARLO_STOCK_INIT(name, type, stockSize) \
    name##Stock(new type[stockSize]), \
    name##StockEnd(name##Stock + stockSize), \
    name##Iter(name##StockEnd)

static Global* global = nullptr;

MonteCarlo::MonteCarlo() :
    fEngine(new TRandom3()),
    MONTE_CARLO_STOCK_INIT(fVertexTime, double_t, MonteCarloInitStockSize),
    MONTE_CARLO_STOCK_INIT(fVertexPosition, TEveVectorD, MonteCarloInitStockSize),
    MONTE_CARLO_STOCK_INIT(fLife, double_t, MonteCarloInitStockSize),
    MONTE_CARLO_STOCK_INIT(fMB, TEveVectorD, MonteCarloStockSize),
    MONTE_CARLO_STOCK_INIT(fFreePath, double_t, MonteCarloStockSize) {
    int rank = 0;
    if (MPI::Is_initialized()) { MPI_Comm_rank(MPI_COMM_WORLD, &rank); }
    fEngine->SetSeed(4357UL + rank);
    fEngine->SetSeed(fEngine->Integer(std::numeric_limits<int>::max() - 1));
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
        for (name##Iter = name##Stock; name##Iter < name##StockEnd; ++name##Iter) { \
            Set##name(name##Iter); \
        } \
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

const TEveVectorD& MonteCarlo::VertexPosition() {
    const auto SetfVertexPosition = [this](TEveVectorD* iter)->void {
        do {
            global->Source()->GetRandom3(iter->fX, iter->fY, iter->fZ, fEngine);
        } while (!Target(iter->fX, iter->fY, iter->fZ));
    };
    CHECK_FILL_RETURN(fVertexPosition);
}

double_t MonteCarlo::Life() {
    const auto SetfLife = [this](double_t* iter)->void {
        *iter = -global->MuoniumLife() * log(fEngine->Rndm());
    };
    CHECK_FILL_RETURN(fLife);
}

const TEveVectorD& MonteCarlo::MaxwellBoltzmann() {
    const double_t sigmaV = cLight * sqrt(kBoltzmann * global->Temperature() / global->MuoniumMass());
    const auto SetfMB = [this, &sigmaV](TEveVectorD* iter)->void {
        iter->fX = fEngine->Gaus(0.0, sigmaV);
        iter->fY = fEngine->Gaus(0.0, sigmaV);
        iter->fZ = fEngine->Gaus(0.0, sigmaV);
    };
    CHECK_FILL_RETURN(fMB);
}

double_t MonteCarlo::FreePath(const TEveVectorD& pos) {
    const auto SetfFreePath = [this, &pos](double_t* iter)->void {
        *iter = -MeanFreePath(pos.fX, pos.fY, pos.fZ) * log(fEngine->Rndm());
    };
    CHECK_FILL_RETURN(fFreePath);
}

