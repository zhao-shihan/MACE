#include "TH2I.h"
#include "TCanvas.h"
#include "TMarker.h"

#include "Reconstruction/Recognizer/HoughPolar.hh"

using namespace MACE::Reconstruction::Recognizer;

HoughPolar::HoughPolar(Double_t innerRadius, Double_t outerRadius, Eigen::Index nPhis, Eigen::Index nRhos) :
    HoughBase(nPhis, nRhos),
    fRhoLow(1.0 / outerRadius),
    fRhoUp(1.0 / innerRadius),
    fPhiResolution(2.0 * M_PI / nPhis),
    fRhoResolution((fRhoUp - fRhoLow) / nRhos),
    fHoughSpaceVis(nPhis, nRhos) {}

HoughPolar::~HoughPolar() {
    if (fFile != nullptr) {
        if (fFile->IsOpen()) {
            fFile->Write();
            fFile->Close();
        }
        delete fFile;
    }
}

void HoughPolar::HoughTransform() {
    // for each hit
    for (auto&& hitMap : fHitStore) {
        const auto& hit = hitMap.first;
        auto& addressList = hitMap.second;
        addressList.reserve(std::max(fRows, fCols) * 5);

        const auto hitX = hit->GetHitPosition().fX;
        const auto hitY = hit->GetHitPosition().fY;
        const auto R2 = hitX * hitX + hitY * hitY;
        const auto X = 2.0 * hitX / R2;
        const auto Y = 2.0 * hitY / R2;

        // do hough transform
        auto DoFill = [&](Eigen::Index row, Eigen::Index col)->void {
            auto& theList = fHoughSpace(row, col);
            theList.emplace_front(&hitMap);
            addressList.emplace_back(&theList, theList.cbegin());
        };
        auto phi = ToReal1(0);
        auto jLast = ToHough2(X * cos(phi) + Y * sin(phi));
        if (0 <= jLast && jLast < fCols) {
            DoFill(0, jLast);
        }
        for (Eigen::Index i = 1; i < fRows; ++i) {
            phi = ToReal1(i);
            const auto j = ToHough2(X * cos(phi) + Y * sin(phi));
            const auto jDiff = j - jLast;
            if (jDiff > 1) {
                for (auto k = jLast + 1; k < jLast + jDiff / 2; ++k) {
                    if (0 <= k && k < fCols) {
                        DoFill(i - 1, k);
                    }
                }
                for (auto k = jLast + jDiff / 2; k < j; ++k) {
                    if (0 <= k && k < fCols) {
                        DoFill(i, k);
                    }
                }
            }
            if (jDiff < -1) {
                for (auto k = jLast - 1; k > jLast + jDiff / 2; --k) {
                    if (0 <= k && k < fCols) {
                        DoFill(i - 1, k);
                    }
                }
                for (auto k = jLast + jDiff / 2; k > j; --k) {
                    if (0 <= k && k < fCols) {
                        DoFill(i, k);
                    }
                }
            }
            if (0 <= j && j < fCols) {
                DoFill(i, j);
            }
            jLast = j;
        }
    }

    if (fEnableHoughSpaceVis) {
        // save for visualization
        for (Eigen::Index i = 0; i < fRows; ++i) {
            for (Eigen::Index j = 0; j < fCols; ++j) {
                fHoughSpaceVis(i, j) = fHoughSpace(i, j).size();
            }
        }
    }
}

Double_t HoughPolar::Cross(const TEveVectorD& hitPos, const RealCoordinate& center) const {
    auto centerX = cos(center.first) / center.second;
    auto centerY = sin(center.first) / center.second;
    return hitPos.fX * centerY - centerX * hitPos.fY;
}

void HoughPolar::SaveLastRecognition(const char* fileName) {
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

        TH2I houghSpace("HoughSpace", "hough space", fRows, -M_PI, M_PI, fCols, fRhoLow, fRhoUp);
        houghSpace.SetStats(false);
        houghSpace.SetXTitle("phi[rad]");
        houghSpace.SetYTitle("1/r[1/mm]");
        houghSpace.SetDrawOption("COLZ");
        for (Eigen::Index i = 0; i < fRows; ++i) {
            for (Eigen::Index j = 0; j < fCols; ++j) {
                const auto phi = ToReal1(i);
                const auto rho = ToReal2(j);
                houghSpace.Fill(phi, rho, fHoughSpaceVis(i, j));
            }
        }
        houghSpace.Write();

        TH2I houghSpaceET("HoughSpaceExceedThreshold", "hough space exceed threshold", fRows, -M_PI, M_PI, fCols, fRhoLow, fRhoUp);
        houghSpaceET.SetStats(false);
        houghSpaceET.SetXTitle("phi[rad]");
        houghSpaceET.SetYTitle("1/r[1/mm]");
        houghSpaceET.SetDrawOption("COLZ");
        for (Eigen::Index i = 0; i < fRows; ++i) {
            for (Eigen::Index j = 0; j < fCols; ++j) {
                const auto phi = ToReal1(i);
                const auto rho = ToReal2(j);
                if (fHoughSpaceVis(i, j) >= fThreshold) {
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
    for (size_t i = 0; i < std::min<size_t>(fRecognizedList.size(), markerColor.size() * markerStyle.size()); ++i) {
        for (auto&& point : fRecognizedList[i].first) {
            auto colorStyleIndex = i % (markerColor.size() * markerStyle.size());
            auto styleIndex = colorStyleIndex / markerColor.size();
            auto colorIndex = colorStyleIndex % markerColor.size();
            auto hitMarker = new TMarker(point->GetHitPosition().fX, point->GetHitPosition().fY, markerStyle[styleIndex]);
            hitMarker->SetMarkerColor(markerColor[colorIndex]);
            hitMarker->Draw();
        }
    }
    realSpace.Write();
}