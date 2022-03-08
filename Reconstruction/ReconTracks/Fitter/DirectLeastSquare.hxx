#pragma once

#include <valarray>

#include "Eigen/Core"

#include "ReconTracks/Global.hxx"
#include "ReconTracks/Interface/Fitter.hxx"
#include "LiteralUnits.hxx"

template<class SpectromrterHit_t, class Track_t>
class MACE::ReconTracks::Fitter::DirectLeastSquare final :
    public MACE::ReconTracks::Interface::Fitter<SpectromrterHit_t, Track_t> {
    MACE_RECONSPECTROMETER_HELIXTRACK_CONCEPT(Track_t);

    DirectLeastSquare(const DirectLeastSquare&) = delete;
    DirectLeastSquare& operator=(const DirectLeastSquare&) = delete;

protected:
    using Base = MACE::ReconTracks::Interface::Fitter<SpectromrterHit_t, Track_t>;
    using HitPtr = typename Base::HitPtr;

public:
    DirectLeastSquare() = default;
    ~DirectLeastSquare() noexcept = default;

    void SetCenterXBound(double low, double up) { fXcBound = { low, up }; }
    void SetCenterYBound(double low, double up) { fYcBound = { low, up }; }
    void SetRadiusBound(double up) { fRBound = up; }

    void SetDerivativeStep(double h) { fH = h; }
    void SetTolerance(double val) { fTolerance = val; }
    void SetMaxSteps(size_t val) { fMaxSteps = val; }

    bool Fit(std::vector<HitPtr>& hitData, Track_t& track) override;

private:
    void Initialize(std::vector<HitPtr>& hitData);
    [[nodiscard]] bool InitialCircleFit();
    [[nodiscard]] bool CircleFit();
    void RevolveFit();
    void Finalize(Track_t& track);

    [[nodiscard]] inline bool CircleParametersBoundCheck() const;

    [[nodiscard]] inline double CircleVariance(const double& Xc, const double& Yc, const double& R) const;
    [[nodiscard]] inline double CircleVariance() const { return CircleVariance(fCircleParameters[0], fCircleParameters[1], fCircleParameters[2]); }
    [[nodiscard]] inline std::tuple<double, Eigen::Vector3d, Eigen::Matrix3d> CircleVarianceGradHessian() const;

    [[nodiscard]] double CalculateReducedChi2();

private:
    std::pair<double, double> fXcBound = { -10_m, 10_m };
    std::pair<double, double> fYcBound = { -10_m, 10_m };
    double fRBound = 10_m;

    double fH = 1e-3;
    double fTolerance = 1e-6;
    size_t fMaxSteps = 5000;

    size_t fN;
    std::valarray<double> fWireX;
    std::valarray<double> fWireY;
    std::valarray<double> fD;
    std::valarray<double> fZ;
    std::valarray<double> fPhi;
    std::valarray<double> fS;

    Eigen::Vector3d fCircleParameters;
    Eigen::Vector2d fRevolveParameters;
};

#include "ReconTracks/Fitter/DirectLeastSquare.ixx"
