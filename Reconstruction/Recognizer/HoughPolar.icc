#include "TH2I.h"
#include "TCanvas.h"
#include "TMarker.h"

template<class SpectrometerHitType>
MACE::Reconstruction::Recognizer::HoughPolar<SpectrometerHitType>::HoughPolar(Double_t innerRadius, Double_t outerRadius, Eigen::Index nPhis, Eigen::Index nRhos) :
    Base(nPhis, nRhos),
    fRhoLow(1.0 / outerRadius),
    fRhoUp(1.0 / innerRadius),
    fPhiResolution(2.0 * M_PI / nPhis),
    fRhoResolution((fRhoUp - fRhoLow) / nRhos),
    fHoughSpaceVis(nPhis, nRhos) {}

template<class SpectrometerHitType>
MACE::Reconstruction::Recognizer::HoughPolar<SpectrometerHitType>::~HoughPolar() {
    if (fFile != nullptr) {
        if (fFile->IsOpen()) {
            fFile->Write();
            fFile->Close();
        }
        delete fFile;
    }
}

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::HoughPolar<SpectrometerHitType>::HoughTransform() {
    // for each hit
    for (auto&& hit : Base::fHitStore) {
        const auto hitX = hit->GetWirePosition().fX;
        const auto hitY = hit->GetWirePosition().fY;
        const auto R2 = hitX * hitX + hitY * hitY;
        const auto X = 2.0 * hitX / R2;
        const auto Y = 2.0 * hitY / R2;

        // do hough transform
        auto DoFill = [&](Eigen::Index row, Eigen::Index col)->void {
            Base::fHoughSpace(row, col).emplace_back(&hit);
        };
        auto phi = ToRealPhi(0);
        auto jLast = ToHoughRho(X * cos(phi) + Y * sin(phi));
        if (0 <= jLast && jLast < Base::fCols) {
            DoFill(0, jLast);
        }
        for (Eigen::Index i = 1; i < Base::fRows; ++i) {
            phi = ToRealPhi(i);
            const auto j = ToHoughRho(X * cos(phi) + Y * sin(phi));
            const auto jDiff = j - jLast;
            if (jDiff > 1) {
                for (auto k = jLast + 1; k < jLast + jDiff / 2; ++k) {
                    if (0 <= k && k < Base::fCols) {
                        DoFill(i - 1, k);
                    }
                }
                for (auto k = jLast + jDiff / 2; k < j; ++k) {
                    if (0 <= k && k < Base::fCols) {
                        DoFill(i, k);
                    }
                }
            }
            if (jDiff < -1) {
                for (auto k = jLast - 1; k > jLast + jDiff / 2; --k) {
                    if (0 <= k && k < Base::fCols) {
                        DoFill(i - 1, k);
                    }
                }
                for (auto k = jLast + jDiff / 2; k > j; --k) {
                    if (0 <= k && k < Base::fCols) {
                        DoFill(i, k);
                    }
                }
            }
            if (0 <= j && j < Base::fCols) {
                DoFill(i, j);
            }
            jLast = j;
        }
    }

    if (fEnableHoughSpaceVis) {
        // save for visualization
        for (Eigen::Index i = 0; i < Base::fRows; ++i) {
            for (Eigen::Index j = 0; j < Base::fCols; ++j) {
                fHoughSpaceVis(i, j) = Base::fHoughSpace(i, j).size();
            }
        }
    }
}

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::HoughPolar<SpectrometerHitType>::SaveLastRecognition(const char* fileName) {
    if (fFile == nullptr) { fFile = new TFile(fileName, "RECREATE"); }
    if (strcmp(fileName, fFile->GetName()) != 0) {
        if (fFile->IsOpen()) {
            fFile->Write();
            fFile->Close();
        }
        delete fFile;
        fFile = new TFile(fileName, "RECREATE");
    }

    if (fEnableHoughSpaceVis) {

        TH2I houghSpace("HoughSpace", "hough space", Base::fRows, -M_PI, M_PI, Base::fCols, fRhoLow, fRhoUp);
        houghSpace.SetStats(false);
        houghSpace.SetXTitle("phi[rad]");
        houghSpace.SetYTitle("1/r[1/mm]");
        houghSpace.SetDrawOption("COLZ");
        for (Eigen::Index i = 0; i < Base::fRows; ++i) {
            for (Eigen::Index j = 0; j < Base::fCols; ++j) {
                const auto phi = ToRealPhi(i);
                const auto rho = ToRealRho(j);
                houghSpace.Fill(phi, rho, fHoughSpaceVis(i, j));
            }
        }
        houghSpace.Write();

        TH2I houghSpaceET("HoughSpaceExceedThreshold", "hough space exceed threshold", Base::fRows, -M_PI, M_PI, Base::fCols, fRhoLow, fRhoUp);
        houghSpaceET.SetStats(false);
        houghSpaceET.SetXTitle("phi[rad]");
        houghSpaceET.SetYTitle("1/r[1/mm]");
        houghSpaceET.SetDrawOption("COLZ");
        for (Eigen::Index i = 0; i < Base::fRows; ++i) {
            for (Eigen::Index j = 0; j < Base::fCols; ++j) {
                const auto phi = ToRealPhi(i);
                const auto rho = ToRealRho(j);
                if (fHoughSpaceVis(i, j) >= Base::fThreshold) {
                    houghSpaceET.Fill(phi, rho, fHoughSpaceVis(i, j));
                }
            }
        }
        houghSpaceET.Write();

    }

    TCanvas realSpace("RealSpace", "real space");
    realSpace.SetGrid();
    TH2I realSpaceAxis("RealSpace", "real space", 1, -350, 350, 1, -350, 350);
    realSpaceAxis.SetStats(false);
    realSpaceAxis.SetXTitle("x[mm]");
    realSpaceAxis.SetYTitle("y[mm]");
    realSpaceAxis.Draw("AXIS");
    constexpr std::array<EColor, 14> markerColor = { kBlack, kGray, kRed, kGreen, kBlue, kYellow, kMagenta, kCyan, kOrange, kSpring, kTeal, kAzure, kViolet, kPink };
    constexpr std::array<EMarkerStyle, 5> markerStyle = { kPlus, kMultiply, kOpenTriangleUp, kOpenDiamond, kOpenTriangleDown };
    for (size_t i = 0; i < std::min<size_t>(Base::fRecognizedList.size(), markerColor.size() * markerStyle.size()); ++i) {
        for (auto&& point : Base::fRecognizedList[i].first) {
            auto colorStyleIndex = i % (markerColor.size() * markerStyle.size());
            auto styleIndex = colorStyleIndex / markerColor.size();
            auto colorIndex = colorStyleIndex % markerColor.size();
            auto hitMarker = new TMarker(point->GetWirePosition().fX, point->GetWirePosition().fY, markerStyle[styleIndex]);
            hitMarker->SetMarkerColor(markerColor[colorIndex]);
            hitMarker->Draw();
        }
    }
    realSpace.Write();
}