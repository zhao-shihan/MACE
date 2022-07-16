#pragma once

#include "MACE/Reconstruction/ReconTracks/Interface/Fitter.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "Eigen/Core"

#include <valarray>

namespace MACE::Reconstruction::ReconTracks::Fitter {

using namespace Utility::LiteralUnit::Length;

template<class CDCHit_t, class Track_t>
class DirectLeastSquare final : public Interface::Fitter<CDCHit_t, Track_t> {
    MACE_RECONSPECTROMETER_HELIXTRACK_CONCEPT(Track_t);

protected:
    using Base = Interface::Fitter<CDCHit_t, Track_t>;
    using HitPtr = typename Base::HitPtr;

public:
    DirectLeastSquare() = default;
    DirectLeastSquare(const DirectLeastSquare&) = delete;
    DirectLeastSquare& operator=(const DirectLeastSquare&) = delete;
    ~DirectLeastSquare() noexcept = default;

    void SetCenterXBound(double low, double up) { fXcBound = std::make_pair(low, up); }
    void SetCenterYBound(double low, double up) { fYcBound = std::make_pair(low, up); }
    void SetRadiusBound(double up) { fRBound = up; }

    // For calculating the gradient and hessian
    void SetDerivativeStep(double h) { fH = h; }

    void SetTolerance(double val) { fTolerance = val; }

    // Stop condition for Newton-Raphson method
    void SetMaxStepsForNewtonRaphson(size_t val) { fMaxStepsNR = val; }
    // Settings for conjugate gradient method
    void SetSufficientDecreaseCoefficient(double val) { fSufficentCoeff = val; }
    void SetBackTrackingLength(double val) { fBackTrackingLength = val; }
    void SetMaxStepsForConjugateGrad(size_t val) { fMaxStepsCG = val; }

    bool Fit(std::vector<HitPtr>& hitData, Track_t& track) override;

private:
    enum MinimizerState {
        kSuccess,
        kMaxStepsReached,
        kParameterBoundsReached
    };

private:
    void Initialize(std::vector<HitPtr>& hitData);
    void InitialScaling();
    bool InitialCircleFit();
    bool CircleFit();
    void RevolveFit();
    void FinalScaling();
    void Finalize(Track_t& track);

    inline bool CircleParametersIsOutOfBound() const;

    inline double TargetFunction(const double& Xc, const double& Yc, const double& R) const;
    inline double TargetFunction() const { return TargetFunction(fCircleParameters[0], fCircleParameters[1], fCircleParameters[2]); }
    inline std::pair<double, Eigen::Vector3d> TargetGrad() const;
    inline std::tuple<double, Eigen::Vector3d, Eigen::Matrix3d> TargetGradHessian() const;

    MinimizerState CircleFitNewtonRaphson();
    MinimizerState CircleFitConjugateGrad();

    double CalculateReducedChi2();

private:
    double fScalingFactor = 1 / 30_cm;

    std::pair<double, double> fXcBound = {-10_m, 10_m};
    std::pair<double, double> fYcBound = {-10_m, 10_m};
    double fRBound = 10_m;

    double fH = 1e-3;

    double fTolerance = 1e-6;
    size_t fMaxStepsNR = 100;
    double fSufficentCoeff = 1e-4;
    double fBackTrackingLength = 0.09;
    size_t fMaxStepsCG = 10000;

    size_t fN;
    std::valarray<double> fT;
    std::valarray<double> fWireX;
    std::valarray<double> fWireY;
    std::valarray<double> fD;
    std::valarray<double> fZ;
    std::valarray<double> fPhi;
    std::valarray<double> fS;

    Eigen::Vector3d fCircleParameters;
    Eigen::Vector2d fRevolveParameters;
    double fVertexTime;
};

} // namespace MACE::Reconstruction::ReconTracks::Fitter

#include "MACE/Reconstruction/ReconTracks/Fitter/DirectLeastSquare.inl"
