#pragma once

#include "ReconSpectrometer/ReconTrack/Global.hxx"
#include "ReconSpectrometer/ReconTrack/Interface/Fitter.hxx"

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

    void SetCenterXBound(double low, double up) { fXcBound = { low, up }; }
    void SetCenterYBound(double low, double up) { fYcBound = { low, up }; }
    void SetRadiusBound(double low, double up) { fRBound = { low, up }; }

    void EnableGradientDescent(bool b) { fEnableGradientDescent = b; }
    void SetDerivativeStep(double h) { fH = h; }
    void SetDescentRate(double val) { fDescentRate = val; }
    void SetTolerance(double val) { fTolerance = val; }
    void SetMaxSteps(int32_t val) { fMaxSteps = val; }

    void SetReducedChi2Bound(double val) { fReducedChi2Bound = val; }

    bool Fit(std::vector<HitPtr>& hitData, TrackPtr& track) override;

private:
    std::pair<double, double> fXcBound = { -1e4, 1e4 };
    std::pair<double, double> fYcBound = { -1e4, 1e4 };
    std::pair<double, double> fRBound = { 0.0, 1e4 };

    bool fEnableGradientDescent = true;
    double fH = 1e-6;
    double fDescentRate = 0.36;
    double fTolerance = 1e-6;
    int fMaxSteps = 100000;

    double fReducedChi2Bound = 20;
};

#include "ReconSpectrometer/ReconTrack/Fitter/DirectSubSpaceLeastVariance.ixx"
