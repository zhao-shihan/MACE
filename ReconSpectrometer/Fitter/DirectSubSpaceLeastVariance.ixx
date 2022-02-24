#include <valarray>

template<class SpectromrterHit_t, class Track_t>
bool MACE::ReconSpectrometer::Fitter::DirectSubSpaceLeastVariance<SpectromrterHit_t, Track_t>::
Fit(std::vector<HitPtr>& hitData, TrackPtr& track) {
    std::ranges::sort(hitData,
        [](const auto& hit1, const auto& hit2)->bool {
            return hit1->GetLayerID() < hit2->GetLayerID();
        }
    );

    auto n = hitData.size();

    // constuct valarrays

    std::valarray<double_t> xWire(n);
    std::valarray<double_t> yWire(n);
    std::valarray<double_t> d(n);
    std::valarray<double_t> z(n);
    for (size_t i = 0; i < n; ++i) {
        xWire[i] = hitData[i]->GetWirePosition().fX;
        yWire[i] = hitData[i]->GetWirePosition().fY;
        d[i] = hitData[i]->GetDriftDistance();
        z[i] = hitData[i]->GetHitPositionZ();
    }

    // initialize with wire position

    double_t initXc;
    double_t initYc;
    double_t initR;
    {
        auto xMean = xWire.sum() / n;
        auto yMean = yWire.sum() / n;
        auto u = xWire - xMean;
        auto v = yWire - yMean;

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
        if (std::abs(cauchy) < std::numeric_limits<decltype(cauchy)>::min() / std::numeric_limits<decltype(cauchy)>::epsilon()) {
            std::cout << "Warning: denominator is effectively 0, aborted." << std::endl;
            return false;
        }

        initXc = xMean + 0.5 * (v2Sum * uw2Sum - uvSum * vw2Sum) / cauchy;
        initYc = yMean + 0.5 * (u2Sum * vw2Sum - uvSum * uw2Sum) / cauchy;
        auto deltaX = xWire - initXc;
        auto deltaY = yWire - initYc;
        initR = std::sqrt((deltaX * deltaX + deltaY * deltaY).sum() / n);

        if (initXc < fXcBound.first or initXc > fXcBound.second or
            initYc < fYcBound.first or initYc > fYcBound.second or
            initR < fRBound.first or initR > fRBound.second) {
            std::cout << "Warning: parameter bound reached, aborted." << std::endl;
            return false;
        }
    }

    auto Xc = initXc;
    auto Yc = initYc;
    auto R = initR;

    // then gradient descent to final result with drift

    if (fEnableGradientDescent) {

        auto Variance = [&n, &xWire, &yWire, &d, this](const auto& Xc, const auto& Yc, const auto& R)->auto {
            auto VarianceCore = [&n, &xWire, &yWire, &d](const auto& Xc, const auto& Yc, const auto& R)->auto {
                auto deltaX = Xc - xWire;
                auto deltaY = Yc - yWire;
                auto deltaRMinus = R - d;
                auto deltaMinus = std::sqrt(deltaX * deltaX + deltaY * deltaY) - deltaRMinus;
                auto varMinus = deltaMinus * deltaMinus;
                auto deltaRPlus = R + d;
                auto deltaPlus = std::sqrt(deltaX * deltaX + deltaY * deltaY) - deltaRPlus;
                auto varPlus = deltaPlus * deltaPlus;
                double_t var = 0;
                for (size_t i = 0; i < n; ++i) {
                    var += std::min(varMinus[i], varPlus[i]);
                }
                return var / (n - 3);
            };

            auto varXcP = VarianceCore(Xc + fH, Yc, R);
            auto varXcM = VarianceCore(Xc - fH, Yc, R);
            auto varYcP = VarianceCore(Xc, Yc + fH, R);
            auto varYcM = VarianceCore(Xc, Yc - fH, R);
            auto  varRP = VarianceCore(Xc, Yc, R + fH);
            auto  varRM = VarianceCore(Xc, Yc, R - fH);

            auto var = (varXcP + varXcM + varYcP + varYcM + varRP + varRM) / 6;
            auto gradXc = (varXcP - varXcM) / (2 * fH);
            auto gradYc = (varYcP - varYcM) / (2 * fH);
            auto  gradR = (varRP - varRM) / (2 * fH);

            return std::make_tuple(var, gradXc, gradYc, gradR);
        };

        double_t lastVar;
        auto [thisVar, gradXc, gradYc, gradR] = Variance(Xc, Yc, R);
        decltype(fMaxSteps) stepCount = 0;
        do {
            Xc -= fDescentRate * gradXc;
            Yc -= fDescentRate * gradYc;
            R -= fDescentRate * gradR;

            if (Xc < fXcBound.first or Xc > fXcBound.second or
                Yc < fYcBound.first or Yc > fYcBound.second or
                R < fRBound.first or R > fRBound.second) {
                std::cout << "Warning: parameter bound reached, aborted." << std::endl;
                return false;
            }

            lastVar = thisVar;
            std::tie(thisVar, gradXc, gradYc, gradR) = Variance(Xc, Yc, R);

            ++stepCount;
            if (stepCount >= fMaxSteps) {
                std::cout << "Warning: max step " << fMaxSteps << " reached." << std::endl;
                break;
            }
        } while (std::abs(thisVar - lastVar) > fTolerance);
    }

    // fit s-z space

    std::valarray<double_t> phi(n);
    double_t Z0;
    double_t cotAlpha;
    double_t Alpha;
    {
        auto deltaX = xWire - Xc;
        auto deltaY = yWire - Yc;
        phi[0] = std::asin((-Xc * deltaY[0] + deltaX[0] * Yc) / std::sqrt((deltaX[0] * deltaX[0] + deltaY[0] * deltaY[0]) * (Xc * Xc + Yc * Yc)));
        for (size_t i = 1; i < n; ++i) {
            phi[i] = phi[i - 1] + std::asin((deltaX[i - 1] * deltaY[i] - deltaX[i] * deltaY[i - 1]) / std::sqrt((deltaX[i - 1] * deltaX[i - 1] + deltaY[i - 1] * deltaY[i - 1]) * (deltaX[i] * deltaX[i] + deltaY[i] * deltaY[i])));
        }
        auto s = R * phi;

        auto sAvg = s.sum() / n;
        auto zAvg = z.sum() / n;
        auto szAvg = (s * z).sum() / n;
        auto s2Avg = (s * s).sum() / n;

        cotAlpha = (szAvg - sAvg * zAvg) / (s2Avg - sAvg * sAvg);
        Z0 = zAvg - sAvg * cotAlpha;
        Alpha = std::atan(1 / cotAlpha);
        if (sAvg > 0 and cotAlpha < 0) {
            Alpha += M_PI;
        } else if (sAvg < 0 and cotAlpha > 0) {
            Alpha -= M_PI;
        }
    }

    // caculate reduced chi2

    double_t reducedChi2;
    {
        auto phi0 = std::atan2(-Yc, -Xc);
        auto xPred = Xc + R * std::cos(phi + phi0);
        auto yPred = Yc + R * std::sin(phi + phi0);
        auto zPred = Z0 + cotAlpha * R * phi;

        auto dPredX = xPred - xWire;
        auto dPredY = yPred - yWire;
        auto deltaD = std::sqrt(dPredX * dPredX + dPredY * dPredY) - d;
        auto reducedChi2D = (deltaD * deltaD).sum();

        auto deltaZ = zPred - z;
        auto reducedChi2Z = (deltaZ * deltaZ).sum();

        reducedChi2 = (reducedChi2D + reducedChi2Z) / (n - 5);
    }

    if (reducedChi2 > fReducedChi2Bound) {
        std::cout << "Warning: reduced chi2 bound reached, aborted." << std::endl;
        return false;
    }

    track->SetCenter(Xc, Yc);
    track->SetRadius(R);
    track->SetZ0(Z0);
    track->SetAlpha(Alpha);
    track->SetChi2(reducedChi2);

    return true;
}
