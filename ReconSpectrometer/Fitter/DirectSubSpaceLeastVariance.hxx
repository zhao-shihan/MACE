#pragma once

#include "ReconSpectrometer/Global.hxx"
#include "ReconSpectrometer/Interface/Fitter.hxx"

template<class SpectromrterHit_t, class Track_t>
class MACE::ReconSpectrometer::Fitter::DirectSubSpaceLeastVariance final :
    public MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHit_t, Track_t> {
    MACE_RECONSPECTROMETER_HELIXTRACK_CONCEPT(Track_t);

    DirectSubSpaceLeastVariance(const DirectSubSpaceLeastVariance&) = delete;
    DirectSubSpaceLeastVariance& operator=(const DirectSubSpaceLeastVariance&) = delete;

protected:
    using Base = MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHit_t, Track_t>;
    using HitPtr = typename Base::HitPtr;
    using TrackPtr = typename Base::TrackPtr;

public:
    DirectSubSpaceLeastVariance() = default;
    ~DirectSubSpaceLeastVariance() noexcept = default;

    void SetCenterXBound(double_t low, double_t up) { fXcBound = { low, up }; }
    void SetCenterYBound(double_t low, double_t up) { fYcBound = { low, up }; }
    void SetRadiusBound(double_t low, double_t up) { fRBound = { low, up }; }

    void EnableGradientDescent(bool b) { fEnableGradientDescent = b; }
    void SetDerivativeStep(double_t h) { fH = h; }
    void SetDescentRate(double_t val) { fDescentRate = val; }
    void SetTolerance(double_t val) { fTolerance = val; }
    void SetMaxSteps(int32_t val) { fMaxSteps = val; }

    void SetReducedChi2Bound(double_t val) { fReducedChi2Bound = val; }

    bool Fit(std::vector<HitPtr>& hitData, TrackPtr& track) override;

private:
    std::pair<double_t, double_t> fXcBound = { -1e4, 1e4 };
    std::pair<double_t, double_t> fYcBound = { -1e4, 1e4 };
    std::pair<double_t, double_t> fRBound = { 0.0, 1e4 };

    bool fEnableGradientDescent = true;
    double_t fH = 1e-6;
    double_t fDescentRate = 0.1;
    double_t fTolerance = 0.001;
    int32_t fMaxSteps = 10000;

    double_t fReducedChi2Bound = 20;
};

#include "ReconSpectrometer/Fitter/DirectSubSpaceLeastVariance.ixx"
