#include "MonteCarlo.hh"

using namespace MACE::SimMTransport;

#define MONTE_CARLO_STOCK_INIT(name, type, stockSize) \
    name##Stock(new type[stockSize]), \
    name##StockEnd(name##Stock + stockSize), \
    name##Iter(name##StockEnd)

static inline double_t Source(const double_t* pos, const double_t*) {
    return gSource(pos[0], pos[1], pos[2]);
}

MonteCarlo::MonteCarlo() :
    fEngine(new TRandom3(gGlobSeed + gCommRank)),
    fSource(new TF3("Source", Source, gSourceXMin, gSourceXMax, gSourceYMin, gSourceYMax, gSourceZMin, gSourceZMax)),
    MONTE_CARLO_STOCK_INIT(fVertexTime, double_t, MonteCarloInitStockSize),
    MONTE_CARLO_STOCK_INIT(fVertexPosition, Vector3, MonteCarloInitStockSize),
    MONTE_CARLO_STOCK_INIT(fLife, double_t, MonteCarloInitStockSize),
    MONTE_CARLO_STOCK_INIT(fMB, Vector3, MonteCarloStockSize),
    MONTE_CARLO_STOCK_INIT(fFreePath, double_t, MonteCarloStockSize) {
    fSource->SetNpx(100);
    fSource->SetNpy(100);
    fSource->SetNpz(100);
}

MonteCarlo::~MonteCarlo() {
    delete fEngine;
    delete fSource;
    delete[] fVertexTimeStock;
    delete[] fVertexPositionStock;
    delete[] fLifeStock;
    delete[] fMBStock;
    delete[] fFreePathStock;
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
        *iter = fEngine->Uniform(gBeginTime, gEndTime);
    };
    CHECK_FILL_RETURN(fVertexTime);
}

const Vector3& MonteCarlo::VertexPosition() {
    const auto SetfVertexPosition = [this](Vector3* iter)->void {
        do {
            fSource->GetRandom3(iter->x, iter->y, iter->z, fEngine);
        } while (!gTarget(iter->x, iter->y, iter->z));
    };
    CHECK_FILL_RETURN(fVertexPosition);
}

double_t MonteCarlo::Life() {
    const auto SetfLife = [this](double_t* iter)->void {
        *iter = -gMuoniumLife * log(fEngine->Rndm());
    };
    CHECK_FILL_RETURN(fLife);
}

const Vector3& MonteCarlo::MaxwellBoltzmann() {
    const auto SetfMB = [this](Vector3* iter)->void {
        const double_t sigmaVx = cLight * sqrt(kBoltzmann * gTemperature / gMuoniumMass);
        iter->x = fEngine->Gaus(0.0, sigmaVx);
        iter->y = fEngine->Gaus(0.0, sigmaVx);
        iter->z = fEngine->Gaus(0.0, sigmaVx);
    };
    CHECK_FILL_RETURN(fMB);
}

double_t MonteCarlo::FreePath(const Vector3& pos) {
    const auto SetfFreePath = [this, &pos](double_t* iter)->void {
        *iter = -gMeanFreePath(pos.x, pos.y, pos.z) * log(fEngine->Rndm());
    };
    CHECK_FILL_RETURN(fFreePath);
}

