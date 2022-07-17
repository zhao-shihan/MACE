#include "Eigen/LU"

#include <numbers>

namespace MACE::ReconTracks::Fitter {

template<class CDCHit_t, class Track_t>
bool DirectLeastSquare<CDCHit_t, Track_t>::Fit(std::vector<HitPtr>& hitData, Track_t& track) {
    Initialize(hitData);

    if (InitialCircleFit() == false) [[unlikely]] { return false; }
    if (CircleFit() == false) [[unlikely]] { return false; }
    RevolveFit();

    Finalize(track);

    return true;
}

template<class CDCHit_t, class Track_t>
void DirectLeastSquare<CDCHit_t, Track_t>::Initialize(std::vector<HitPtr>& hitData) {
    // sort data by layer ID
    std::ranges::sort(hitData,
                      [](const auto& hit1, const auto& hit2) -> bool {
                          return hit1->GetLayerID() < hit2->GetLayerID();
                      });

    // constuct valarrays
    fN = hitData.size();
    fT.resize(fN);
    fWireX.resize(fN);
    fWireY.resize(fN);
    fD.resize(fN);
    fZ.resize(fN);
    fPhi.resize(fN);
    fS.resize(fN);
    for (size_t i = 0; i < fN; ++i) {
        fT[i] = hitData[i]->GetHitTime();
        fWireX[i] = hitData[i]->GetWirePosition().x();
        fWireY[i] = hitData[i]->GetWirePosition().y();
        fD[i] = hitData[i]->GetDriftDistance();
        fZ[i] = hitData[i]->GetHitPositionZ();
    }
}

template<class CDCHit_t, class Track_t>
void DirectLeastSquare<CDCHit_t, Track_t>::InitialScaling() {
    fXcBound.first *= fScalingFactor;
    fXcBound.second *= fScalingFactor;
    fYcBound.first *= fScalingFactor;
    fYcBound.second *= fScalingFactor;
    fRBound *= fScalingFactor;
    fWireX *= fScalingFactor;
    fWireY *= fScalingFactor;
    fD *= fScalingFactor;
    fZ *= fScalingFactor;
}

template<class CDCHit_t, class Track_t>
bool DirectLeastSquare<CDCHit_t, Track_t>::InitialCircleFit() {
    auto& Xc = fCircleParameters[0];
    auto& Yc = fCircleParameters[1];
    auto& R = fCircleParameters[2];

    auto xMean = fWireX.sum() / fN;
    auto yMean = fWireY.sum() / fN;
    auto u = fWireX - xMean;
    auto v = fWireY - yMean;

    auto u2 = u * u;
    auto v2 = v * v;
    auto uv = u * v;
    auto w2 = u2 + v2;
    auto uw2 = u * w2;
    auto vw2 = v * w2;

    auto u2Sum = u2.sum();
    auto v2Sum = v2.sum();
    auto uvSum = uv.sum();
    auto uw2Sum = uw2.sum();
    auto vw2Sum = vw2.sum();
    auto cauchy = u2Sum * v2Sum - uvSum * uvSum;
    if (std::abs(cauchy) < std::numeric_limits<decltype(cauchy)>::min() / std::numeric_limits<decltype(cauchy)>::epsilon()) [[unlikely]] {
        if (this->fVerbose > 0) {
            std::cout << "Warning: denominator is effectively 0, aborted." << std::endl;
        }
        return false;
    }

    Xc = xMean + (v2Sum * uw2Sum - uvSum * vw2Sum) / (2 * cauchy);
    Yc = yMean + (u2Sum * vw2Sum - uvSum * uw2Sum) / (2 * cauchy);
    auto deltaX = fWireX - Xc;
    auto deltaY = fWireY - Yc;
    R = std::sqrt((deltaX * deltaX + deltaY * deltaY).sum() / fN);

    if (this->fVerbose > 1) {
        std::cout
            << "=============== 2D Fit Initialization ===============\n"
            << " Xc = " << fCircleParameters[0] / fScalingFactor << "\n"
            << " Yc = " << fCircleParameters[1] / fScalingFactor << "\n"
            << " R  = " << fCircleParameters[2] / fScalingFactor << std::endl;
    }

    if (CircleParametersIsOutOfBound()) [[unlikely]] { return false; }

    return true;
}

template<class CDCHit_t, class Track_t>
bool DirectLeastSquare<CDCHit_t, Track_t>::CircleFit() {
    auto initCircleParameters = fCircleParameters;
    if (CircleFitNewtonRaphson() != kSuccess) {
        if (this->fVerbose > 0) {
            std::cout << "Warning: Newton-Raphson method failed, switch to conjugate gradient method." << std::endl;
        }
        fCircleParameters = initCircleParameters;
        if (CircleFitConjugateGrad() != kSuccess) {
            return false;
        }
    }
    return true;
}

template<class CDCHit_t, class Track_t>
void DirectLeastSquare<CDCHit_t, Track_t>::RevolveFit() {
    const auto& Xc = fCircleParameters[0];
    const auto& Yc = fCircleParameters[1];
    const auto& R = fCircleParameters[2];
    auto& Z0 = fRevolveParameters[0];
    auto& Alpha = fRevolveParameters[1];

    auto deltaX = fWireX - Xc;
    auto deltaY = fWireY - Yc;
    fPhi[0] = std::asin((-Xc * deltaY[0] + deltaX[0] * Yc) / std::sqrt((deltaX[0] * deltaX[0] + deltaY[0] * deltaY[0]) * (Xc * Xc + Yc * Yc)));
    for (size_t i = 1; i < fN; ++i) {
        fPhi[i] = fPhi[i - 1] + std::asin((deltaX[i - 1] * deltaY[i] - deltaX[i] * deltaY[i - 1]) / std::sqrt((deltaX[i - 1] * deltaX[i - 1] + deltaY[i - 1] * deltaY[i - 1]) * (deltaX[i] * deltaX[i] + deltaY[i] * deltaY[i])));
    }
    fS = R * fPhi;

    auto sAvg = fS.sum() / fN;
    auto s2Avg = (fS * fS).sum() / fN;

    auto zAvg = fZ.sum() / fN;
    auto szAvg = (fS * fZ).sum() / fN;
    auto cotAlpha = (szAvg - sAvg * zAvg) / (s2Avg - sAvg * sAvg);
    Z0 = zAvg - sAvg * cotAlpha;
    Alpha = std::atan(1 / cotAlpha);
    if (sAvg > 0 and cotAlpha < 0) {
        Alpha += std::numbers::pi;
    } else if (sAvg < 0 and cotAlpha > 0) {
        Alpha -= std::numbers::pi;
    }

    auto tAvg = fT.sum() / fN;
    auto stAvg = (fS * fT).sum() / fN;
    auto reciV = (stAvg - sAvg * tAvg) / (s2Avg - sAvg * sAvg);
    fVertexTime = tAvg - sAvg * reciV;
}

template<class CDCHit_t, class Track_t>
void DirectLeastSquare<CDCHit_t, Track_t>::FinalScaling() {
    fXcBound.first /= fScalingFactor;
    fXcBound.second /= fScalingFactor;
    fYcBound.first /= fScalingFactor;
    fYcBound.second /= fScalingFactor;
    fRBound /= fScalingFactor;
    fCircleParameters /= fScalingFactor;
    fRevolveParameters[0] /= fScalingFactor;
}

template<class CDCHit_t, class Track_t>
void DirectLeastSquare<CDCHit_t, Track_t>::Finalize(Track_t& track) {
    track.SetVertexTime(fVertexTime);
    track.SetCenter(fCircleParameters[0], fCircleParameters[1]);
    track.SetRadius(fCircleParameters[2]);
    track.SetZ0(fRevolveParameters[0]);
    track.SetAlpha(fRevolveParameters[1]);
    track.SetNumHits(fN);
    track.SetChi2(CalculateReducedChi2());
}

template<class CDCHit_t, class Track_t>
inline bool DirectLeastSquare<CDCHit_t, Track_t>::CircleParametersIsOutOfBound() const {
    const auto& Xc = fCircleParameters[0];
    const auto& Yc = fCircleParameters[1];
    const auto& R = fCircleParameters[2];

    if (fXcBound.first < Xc and Xc < fXcBound.second and
        fYcBound.first < Yc and Yc < fYcBound.second and
        0.0 < R and R < fRBound) [[likely]] {
        return false;
    } else [[unlikely]] {
        if (this->fVerbose > 0) {
            std::cout << "Warning: parameter bound reached." << std::endl;
        }
        return true;
    }
}

template<class CDCHit_t, class Track_t>
inline double DirectLeastSquare<CDCHit_t, Track_t>::TargetFunction(const double& Xc, const double& Yc, const double& R) const {
    const auto rX = Xc - fWireX;
    const auto rY = Yc - fWireY;
    const auto dca = std::sqrt(rX * rX + rY * rY) - R;
    const auto deltaMinus = dca - fD;
    const auto varMinus = deltaMinus * deltaMinus;
    const auto deltaPlus = dca + fD;
    const auto varPlus = deltaPlus * deltaPlus;
    double variance = 0;
    for (size_t i = 0; i < fN; ++i) {
        variance += std::min(varMinus[i], varPlus[i]);
    }
    return variance / (R * R * fN);
}

template<class CDCHit_t, class Track_t>
inline std::pair<double, Eigen::Vector3d> DirectLeastSquare<CDCHit_t, Track_t>::TargetGrad() const {
    const auto& Xc = fCircleParameters[0];
    const auto& Yc = fCircleParameters[1];
    const auto& R = fCircleParameters[2];

    // central point
    const auto h000 = TargetFunction(Xc, Yc, R);

    // diag points
    const auto hP00 = TargetFunction(Xc + fH, Yc, R);
    const auto hM00 = TargetFunction(Xc - fH, Yc, R);
    const auto h0P0 = TargetFunction(Xc, Yc + fH, R);
    const auto h0M0 = TargetFunction(Xc, Yc - fH, R);
    const auto h00P = TargetFunction(Xc, Yc, R + fH);
    const auto h00M = TargetFunction(Xc, Yc, R - fH);
    // 1/(2*h)
    const auto divTwoH = 0.5 / fH;
    // gradient of variance
    const Eigen::Vector3d grad(
        (hP00 - hM00) * divTwoH,
        (h0P0 - h0M0) * divTwoH,
        (h00P - h00M) * divTwoH);

    return std::make_pair(h000, grad);
}

template<class CDCHit_t, class Track_t>
inline std::tuple<double, Eigen::Vector3d, Eigen::Matrix3d> DirectLeastSquare<CDCHit_t, Track_t>::TargetGradHessian() const {
    const auto& Xc = fCircleParameters[0];
    const auto& Yc = fCircleParameters[1];
    const auto& R = fCircleParameters[2];

    // central point
    const auto h000 = TargetFunction(Xc, Yc, R);

    // diag points
    const auto hP00 = TargetFunction(Xc + fH, Yc, R);
    const auto hM00 = TargetFunction(Xc - fH, Yc, R);
    const auto h0P0 = TargetFunction(Xc, Yc + fH, R);
    const auto h0M0 = TargetFunction(Xc, Yc - fH, R);
    const auto h00P = TargetFunction(Xc, Yc, R + fH);
    const auto h00M = TargetFunction(Xc, Yc, R - fH);
    // 1/(2*h)
    const auto divTwoH = 0.5 / fH;
    // gradient of variance
    const Eigen::Vector3d grad(
        (hP00 - hM00) * divTwoH,
        (h0P0 - h0M0) * divTwoH,
        (h00P - h00M) * divTwoH);

    // h/2
    const auto halfH = 0.5 * fH;
    // off-diag points
    const auto hPP0 = TargetFunction(Xc + halfH, Yc + halfH, R);
    const auto hPM0 = TargetFunction(Xc + halfH, Yc - halfH, R);
    const auto hMP0 = TargetFunction(Xc - halfH, Yc + halfH, R);
    const auto hMM0 = TargetFunction(Xc - halfH, Yc - halfH, R);
    const auto h0PP = TargetFunction(Xc, Yc + halfH, R + halfH);
    const auto h0PM = TargetFunction(Xc, Yc + halfH, R - halfH);
    const auto h0MP = TargetFunction(Xc, Yc - halfH, R + halfH);
    const auto h0MM = TargetFunction(Xc, Yc - halfH, R - halfH);
    const auto hP0P = TargetFunction(Xc + halfH, Yc, R + halfH);
    const auto hP0M = TargetFunction(Xc + halfH, Yc, R - halfH);
    const auto hM0P = TargetFunction(Xc - halfH, Yc, R + halfH);
    const auto hM0M = TargetFunction(Xc - halfH, Yc, R - halfH);
    // 1/h^2
    const auto divH2 = 1 / (fH * fH);
    // hessian matrix of varience
    Eigen::Matrix3d hessian;
    // diag term
    hessian(0, 0) = (hP00 - h000 - h000 + hM00) * divH2;
    hessian(1, 1) = (h0P0 - h000 - h000 + h0M0) * divH2;
    hessian(2, 2) = (h00P - h000 - h000 + h00M) * divH2;
    // off-diag term
    hessian(0, 1) = (hPP0 - hMP0 - hPM0 + hMM0) * divH2;
    hessian(0, 2) = (hP0P - hM0P - hP0M + hM0M) * divH2;
    hessian(1, 2) = (h0PP - h0MP - h0PM + h0MM) * divH2;
    hessian(1, 0) = hessian(0, 1);
    hessian(2, 0) = hessian(0, 2);
    hessian(2, 1) = hessian(1, 2);

    return std::make_tuple(h000, grad, hessian);
}

template<class CDCHit_t, class Track_t>
typename DirectLeastSquare<CDCHit_t, Track_t>::MinimizerState
DirectLeastSquare<CDCHit_t, Track_t>::CircleFitNewtonRaphson() {
    double lastFunc;
    auto [thisFunc, grad, hessian] = TargetGradHessian();
    if (this->fVerbose > 1) {
        std::cout << "=========== Newton-Raphson iteration 0\t ============\n"
                  << " Xc            = " << fCircleParameters[0] / fScalingFactor << "\n"
                  << " Yc            = " << fCircleParameters[1] / fScalingFactor << "\n"
                  << " R             = " << fCircleParameters[2] / fScalingFactor << "\n"
                  << " Square        = " << thisFunc << "\n"
                  << " GradDirection = \n"
                  << grad / grad.norm() << "\n"
                  << " Hessian       = \n"
                  << hessian << "\n"
                  << " StepDirection = \n"
                  << -hessian.inverse() * grad / (hessian.inverse() * grad).norm() << std::endl;
    }

    decltype(fMaxStepsNR) stepCount = 0;
    do {
        // update step count
        ++stepCount;

        // do stepping
        // Eigen::Vector3d step = -hessian.inverse() * grad;
        // double stepLength = 1;
        // fCircleParameters += stepLength * step;
        // while (stepLength > 0 and TargetFunction() > thisFunc + fSufficentCoeff * stepLength * step.dot(grad)) {
        //     stepLength -= fBackTrackingCoeff;
        //     fCircleParameters -= stepLength * step;
        // }
        fCircleParameters -= hessian.inverse() * grad;

        // bound check
        if (CircleParametersIsOutOfBound()) [[unlikely]] {
            return kParameterBoundsReached;
        }

        // update function value, gradient, and hessian
        lastFunc = thisFunc;
        std::tie(thisFunc, grad, hessian) = TargetGradHessian();
        if (this->fVerbose > 1) {
            std::cout << "=========== Newton-Raphson iteration " << stepCount << "\t ============\n"
                      << " Xc            = " << fCircleParameters[0] / fScalingFactor << "\n"
                      << " Yc            = " << fCircleParameters[1] / fScalingFactor << "\n"
                      << " R             = " << fCircleParameters[2] / fScalingFactor << "\n"
                      << " Square        = " << thisFunc << "\n"
                      << " GradDirection = \n"
                      << grad / grad.norm() << "\n"
                      << " Hessian       = \n"
                      << hessian << "\n"
                      << " StepDirection = \n"
                      << (-hessian.inverse() * grad) / (hessian.inverse() * grad).norm() << std::endl;
        }
    } while (std::abs(thisFunc - lastFunc) / thisFunc > fTolerance and stepCount < fMaxStepsNR);

    if (this->fVerbose > 1) {
        std::cout << "========== Newton-Raphson method Finalized ==========" << std::endl;
    }

    // check step count
    if (stepCount >= fMaxStepsNR) [[unlikely]] {
        if (this->fVerbose > 0) {
            std::cout << "Warning: max step " << fMaxStepsNR << " reached for Newton-Raphson method." << std::endl;
        }
        return kMaxStepsReached;
    }

    return kSuccess;
}

template<class CDCHit_t, class Track_t>
typename DirectLeastSquare<CDCHit_t, Track_t>::MinimizerState
DirectLeastSquare<CDCHit_t, Track_t>::CircleFitConjugateGrad() {
    double lastFunc;
    Eigen::Vector3d lastGrad;
    auto [thisFunc, thisGrad] = TargetGrad();
    Eigen::Vector3d step = -thisGrad;
    if (this->fVerbose > 1) {
        std::cout << "=========== conjugate grad iteration 0\t ============\n"
                  << " Xc            = " << fCircleParameters[0] / fScalingFactor << "\n"
                  << " Yc            = " << fCircleParameters[1] / fScalingFactor << "\n"
                  << " R             = " << fCircleParameters[2] / fScalingFactor << "\n"
                  << " Square        = " << thisFunc << "\n"
                  << " GradDirection = \n"
                  << thisGrad / thisGrad.norm() << "\n"
                  << " StepDirection = \n"
                  << step / step.norm() << std::endl;
    }

    decltype(fMaxStepsCG) stepCount = 0;
    do {
        // update step count
        ++stepCount;

        // do stepping
        double stepLength = 1;
        fCircleParameters += step;
        while (stepLength > 0 and TargetFunction() > thisFunc + fSufficentCoeff * stepLength * step.dot(thisGrad)) {
            stepLength -= fBackTrackingLength;
            fCircleParameters -= fBackTrackingLength * step;
        }

        // bound check
        if (CircleParametersIsOutOfBound()) [[unlikely]] {
            return kParameterBoundsReached;
        }

        // update function value and gradient
        lastFunc = thisFunc;
        lastGrad = thisGrad;
        std::tie(thisFunc, thisGrad) = TargetGrad();
        step = (-thisGrad + (thisGrad.dot(thisGrad)) / (lastGrad.dot(lastGrad)) * step) * fCircleParameters[2];
        if (this->fVerbose > 1) {
            std::cout << "=========== conjugate grad iteration " << stepCount << "\t ============\n"
                      << " Xc            = " << fCircleParameters[0] / fScalingFactor << "\n"
                      << " Yc            = " << fCircleParameters[1] / fScalingFactor << "\n"
                      << " R             = " << fCircleParameters[2] / fScalingFactor << "\n"
                      << " Square        = " << thisFunc << "\n"
                      << " GradDirection = \n"
                      << thisGrad / thisGrad.norm() << "\n"
                      << " StepDirection = \n"
                      << step / step.norm() << std::endl;
        }
    } while (std::abs(thisFunc - lastFunc) / thisFunc > fTolerance and stepCount < fMaxStepsCG);

    if (this->fVerbose > 1) {
        std::cout << "========== conjugate grad method Finalized ==========" << std::endl;
    }

    // check step count
    if (stepCount >= fMaxStepsCG) [[unlikely]] {
        if (this->fVerbose > 0) {
            std::cout << "Warning: max step " << fMaxStepsCG << " reached for conjugate gradient method." << std::endl;
        }
        return kMaxStepsReached;
    }

    return kSuccess;
}

template<class CDCHit_t, class Track_t>
double DirectLeastSquare<CDCHit_t, Track_t>::CalculateReducedChi2() {
    const auto& Xc = fCircleParameters[0];
    const auto& Yc = fCircleParameters[1];
    const auto& R = fCircleParameters[2];
    const auto& Z0 = fRevolveParameters[0];
    const auto& Alpha = fRevolveParameters[1];

    auto phi0 = std::atan2(-Yc, -Xc);
    auto xPred = Xc + R * std::cos(fPhi + phi0);
    auto yPred = Yc + R * std::sin(fPhi + phi0);
    auto zPred = Z0 + fS / std::tan(Alpha);

    auto dPredX = xPred - fWireX;
    auto dPredY = yPred - fWireY;
    auto deltaD = std::sqrt(dPredX * dPredX + dPredY * dPredY) - fD;
    auto reducedChi2D = (deltaD * deltaD).sum();

    auto deltaZ = zPred - fZ;
    auto reducedChi2Z = (deltaZ * deltaZ).sum();

    return (reducedChi2D + reducedChi2Z) / (fN - 5);
}

} // namespace MACE::ReconTracks::Fitter
