#include "Eigen/LU"

template<class SpectromrterHit_t, class Track_t>
bool MACE::ReconSpectrometer::Fitter::DirectLeastSquare<SpectromrterHit_t, Track_t>::
Fit(std::vector<HitPtr>& hitData, Track_t& track) {
    Initialize(hitData);

    if (InitialCircleFit() == false) [[unlikely]] { return false; }
    if (CircleFit() == false) [[unlikely]] { return false; }
    RevolveFit();

    Finalize(track);

    track.SetVertexTime(hitData.front()->GetHitTime());

    return true;
}

template<class SpectromrterHit_t, class Track_t>
void MACE::ReconSpectrometer::Fitter::DirectLeastSquare<SpectromrterHit_t, Track_t>::
Initialize(std::vector<HitPtr>& hitData) {
    // sort data by layer ID
    std::ranges::sort(hitData,
        [](const auto& hit1, const auto& hit2)->bool {
            return hit1->GetLayerID() < hit2->GetLayerID();
        }
    );

    // constuct valarrays
    fN = hitData.size();
    fWireX.resize(fN);
    fWireY.resize(fN);
    fD.resize(fN);
    fZ.resize(fN);
    fPhi.resize(fN);
    for (size_t i = 0; i < fN; ++i) {
        fWireX[i] = hitData[i]->GetWirePosition().fX;
        fWireY[i] = hitData[i]->GetWirePosition().fY;
        fD[i] = hitData[i]->GetDriftDistance();
        fZ[i] = hitData[i]->GetHitPositionZ();
    }
}

template<class SpectromrterHit_t, class Track_t>
bool MACE::ReconSpectrometer::Fitter::DirectLeastSquare<SpectromrterHit_t, Track_t>::
InitialCircleFit() {
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
        if (Base::fVerbose > 0) {
            std::cout << "Warning: denominator is effectively 0, aborted." << std::endl;
        }
        return false;
    }

    Xc = xMean + (v2Sum * uw2Sum - uvSum * vw2Sum) / (2 * cauchy);
    Yc = yMean + (u2Sum * vw2Sum - uvSum * uw2Sum) / (2 * cauchy);
    auto deltaX = fWireX - Xc;
    auto deltaY = fWireY - Yc;
    R = std::sqrt((deltaX * deltaX + deltaY * deltaY).sum() / fN);

    if (CircleParametersBoundCheck() == false) [[unlikely]] { return false; }

    return true;
}

template<class SpectromrterHit_t, class Track_t>
bool MACE::ReconSpectrometer::Fitter::DirectLeastSquare<SpectromrterHit_t, Track_t>::
CircleFit() {
    double lastVar;
    auto [thisVar, grad, hessian] = CircleVarianceGradHessian();

    decltype(fMaxSteps) stepCount = 0;
    do {
        // update last variance
        lastVar = thisVar;

        // do stepping
        fCircleParameters -= hessian.inverse() * grad;

        // bound check
        if (CircleParametersBoundCheck() == false) [[unlikely]] { return false; }
            //
        // update variance, gradient, and hessian
        std::tie(thisVar, grad, hessian) = CircleVarianceGradHessian();

        // update step count
        ++stepCount;
    } while (std::abs(thisVar - lastVar) / thisVar > fTolerance and stepCount < fMaxSteps);

    // check step count
    if (stepCount >= fMaxSteps) [[unlikely]] {
        if (Base::fVerbose > 0) { std::cout << "Warning: max step " << fMaxSteps << " reached." << std::endl; }
    }

    return true;
}

template<class SpectromrterHit_t, class Track_t>
void MACE::ReconSpectrometer::Fitter::DirectLeastSquare<SpectromrterHit_t, Track_t>::
RevolveFit() {
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
    auto zAvg = fZ.sum() / fN;
    auto szAvg = (fS * fZ).sum() / fN;
    auto s2Avg = (fS * fS).sum() / fN;

    auto cotAlpha = (szAvg - sAvg * zAvg) / (s2Avg - sAvg * sAvg);
    Z0 = zAvg - sAvg * cotAlpha;
    Alpha = std::atan(1 / cotAlpha);
    if (sAvg > 0 and cotAlpha < 0) {
        Alpha += M_PI;
    } else if (sAvg < 0 and cotAlpha > 0) {
        Alpha -= M_PI;
    }
}

template<class SpectromrterHit_t, class Track_t>
void MACE::ReconSpectrometer::Fitter::DirectLeastSquare<SpectromrterHit_t, Track_t>::
Finalize(Track_t& track) {
    track.SetCenter(fCircleParameters[0], fCircleParameters[1]);
    track.SetRadius(fCircleParameters[2]);
    track.SetZ0(fRevolveParameters[0]);
    track.SetAlpha(fRevolveParameters[1]);
    track.SetChi2(CalculateReducedChi2());
}

template<class SpectromrterHit_t, class Track_t>
inline bool MACE::ReconSpectrometer::Fitter::DirectLeastSquare<SpectromrterHit_t, Track_t>::
CircleParametersBoundCheck() const {
    const auto& Xc = fCircleParameters[0];
    const auto& Yc = fCircleParameters[1];
    const auto& R = fCircleParameters[2];

    if (fXcBound.first < Xc and Xc < fXcBound.second and
        fYcBound.first < Yc and Yc < fYcBound.second and
        0.0 < R and R < fRBound) [[likely]] {
        return true;
    } else {
        if (Base::fVerbose > 0) {
            std::cout << "Warning: parameter bound reached, aborted." << std::endl;
        }
        return false;
    }
}

template<class SpectromrterHit_t, class Track_t>
inline double MACE::ReconSpectrometer::Fitter::DirectLeastSquare<SpectromrterHit_t, Track_t>::
CircleVariance(const double& Xc, const double& Yc, const double& R) const {
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

template<class SpectromrterHit_t, class Track_t>
inline std::tuple<double, Eigen::Vector3d, Eigen::Matrix3d> MACE::ReconSpectrometer::Fitter::DirectLeastSquare<SpectromrterHit_t, Track_t>::
CircleVarianceGradHessian() const {
    const auto& Xc = fCircleParameters[0];
    const auto& Yc = fCircleParameters[1];
    const auto& R = fCircleParameters[2];

    // central point
    const auto v000 = CircleVariance(Xc, Yc, R);

    // diag points
    const auto vP00 = CircleVariance(Xc + fH, Yc, R);
    const auto vM00 = CircleVariance(Xc - fH, Yc, R);
    const auto v0P0 = CircleVariance(Xc, Yc + fH, R);
    const auto v0M0 = CircleVariance(Xc, Yc - fH, R);
    const auto v00P = CircleVariance(Xc, Yc, R + fH);
    const auto v00M = CircleVariance(Xc, Yc, R - fH);
    // 1/(2*h)
    const auto divTwoH = 0.5 / fH;
    // gradient of variance
    const Eigen::Vector3d grad(
        (vP00 - vM00) * divTwoH,
        (v0P0 - v0M0) * divTwoH,
        (v00P - v00M) * divTwoH);

    // h/2
    const auto halfH = 0.5 * fH;
    // off-diag points
    const auto vPP0 = CircleVariance(Xc + halfH, Yc + halfH, R);
    const auto vPM0 = CircleVariance(Xc + halfH, Yc - halfH, R);
    const auto vMP0 = CircleVariance(Xc - halfH, Yc + halfH, R);
    const auto vMM0 = CircleVariance(Xc - halfH, Yc - halfH, R);
    const auto v0PP = CircleVariance(Xc, Yc + halfH, R + halfH);
    const auto v0PM = CircleVariance(Xc, Yc + halfH, R - halfH);
    const auto v0MP = CircleVariance(Xc, Yc - halfH, R + halfH);
    const auto v0MM = CircleVariance(Xc, Yc - halfH, R - halfH);
    const auto vP0P = CircleVariance(Xc + halfH, Yc, R + halfH);
    const auto vP0M = CircleVariance(Xc + halfH, Yc, R - halfH);
    const auto vM0P = CircleVariance(Xc - halfH, Yc, R + halfH);
    const auto vM0M = CircleVariance(Xc - halfH, Yc, R - halfH);
    // 1/h^2
    const auto divH2 = 1 / (fH * fH);
    // hessian matrix of varience
    Eigen::Matrix3d hessian;
    // diag term
    hessian(0, 0) = (vP00 - v000 - v000 + vM00) * divH2;
    hessian(1, 1) = (v0P0 - v000 - v000 + v0M0) * divH2;
    hessian(2, 2) = (v00P - v000 - v000 + v00M) * divH2;
    // off-diag term
    hessian(0, 1) = (vPP0 - vMP0 - vPM0 + vMM0) * divH2;
    hessian(0, 2) = (vP0P - vM0P - vP0M + vM0M) * divH2;
    hessian(1, 2) = (v0PP - v0MP - v0PM + v0MM) * divH2;
    hessian(1, 0) = hessian(0, 1);
    hessian(2, 0) = hessian(0, 2);
    hessian(2, 1) = hessian(1, 2);

    return std::make_tuple(v000, grad, hessian);
}

template<class SpectromrterHit_t, class Track_t>
double MACE::ReconSpectrometer::Fitter::DirectLeastSquare<SpectromrterHit_t, Track_t>::
CalculateReducedChi2() {
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
