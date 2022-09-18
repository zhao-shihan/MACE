#pragma once

#include "MACE/Utility/Math/Random/PCGXSHRR6432.hxx"

#include "CLHEP/Random/RandomEngine.h"

namespace MACE::CLHEPX::Random {

class PCGEngine final : public CLHEP::HepRandomEngine {
private:
    using PCG = MACE::Utility::Math::Random::PCGXSHRR6432;

public:
    PCGEngine();
    PCGEngine(long seed);

    double flat() override { return fgToDoubleFactor * NonZeroPCGRandom(); }
    void flatArray(const int size, double* vect) override;
    void discard(PCG::StateType n) { fPCG.Discard(n); }

    void setSeed(long seed, int = 0) override;
    void setSeeds(const long* seeds, int = 0) override;

    void saveStatus(const char filename[] = "pcg_xsh_rr_64_32.conf") const override;
    void restoreStatus(const char filename[] = "pcg_xsh_rr_64_32.conf") override;
    void showStatus() const override;

    static std::string engineName() { return "PCGEngine"; }
    std::string name() const override { return engineName(); }

    std::ostream& put(std::ostream& os) const override;
    std::istream& get(std::istream& is) override;

    static std::string beginTag() { return "PCGEngine-begin"; }
    std::istream& getState(std::istream& is) override;

    std::vector<unsigned long> put() const override;
    bool get(const std::vector<unsigned long>& v) override;
    bool getState(const std::vector<unsigned long>& v) override;

    operator double() override { return flat(); }
    operator float() override { return fgToFloatFactor * NonZeroPCGRandom(); }
    operator unsigned int() override { return fPCG(); }

private:
    inline PCG::ResultType NonZeroPCGRandom();

private:
    PCG fPCG;

    static constexpr double fgToDoubleFactor = 1.0 / (PCG::Max() + 1ULL);
    static inline const float fgToFloatFactor = std::nexttowardf(fgToDoubleFactor, 0); // Avoid end point
};

} // namespace CLHEPX

#include "MACE/CLHEPX/Random/PCGEngine.inl"
