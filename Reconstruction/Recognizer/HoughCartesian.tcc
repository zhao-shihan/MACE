#include "TH2I.h"
#include "TCanvas.h"
#include "TMarker.h"

template<class SpectrometerHitType>
MACE::Reconstruction::Recognizer::HoughCartesian<SpectrometerHitType>::HoughCartesian(Double_t houghSpaceExtent, Eigen::Index size, Double_t protectedRadius) :
    Base(size, size),
    fExtent(houghSpaceExtent),
    fResolution(2.0 * houghSpaceExtent / size),
    fProtectedRadius(protectedRadius),
    fHoughSpaceVis(size, size) {}

template<class SpectrometerHitType>
MACE::Reconstruction::Recognizer::HoughCartesian<SpectrometerHitType>::~HoughCartesian() {
    if (fFile != nullptr) {
        if (fFile->IsOpen()) {
            fFile->Write();
            fFile->Close();
        }
        delete fFile;
    }
}

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::HoughCartesian<SpectrometerHitType>::HoughTransform() {
    // for each hit
    for (auto&& hitMap : Base::fHitStore) {
        const auto& hit = hitMap.first;
        auto& addressList = hitMap.second;
        addressList.reserve(Base::fRows * 2);

        const auto hitX = hit->GetHitPosition().fX;
        const auto hitY = hit->GetHitPosition().fY;
        const auto R2 = hitX * hitX + hitY * hitY;
        const auto X = 2.0 * hitX / R2;
        const auto Y = 2.0 * hitY / R2;

        // do hough transform
        auto DoFill = [&](Eigen::Index row, Eigen::Index col)->void {
            auto& theList = Base::fHoughSpace(row, col);
            theList.emplace_front(&hitMap);
            addressList.emplace_back(&theList, theList.cbegin());
        };
        if (abs(X / Y) < 1.0) {
            for (Eigen::Index i = 0; i < Base::fRows; ++i) {
                const auto xc = ToRealX(i);
                const auto yc = (1.0 - X * xc) / Y;
                if (xc * xc + yc * yc < fProtectedRadius * fProtectedRadius) { continue; }
                const auto j = ToHoughY(yc);
                if (0 <= j && j < Base::fRows) {
                    DoFill(i, j);
                }
            }
        } else {
            for (Eigen::Index j = 0; j < Base::fRows; ++j) {
                const auto yc = ToRealY(j);
                const auto xc = (1.0 - Y * yc) / X;
                if (xc * xc + yc * yc < fProtectedRadius * fProtectedRadius) { continue; }
                const auto i = ToHoughX(xc);
                if (0 <= i && i < Base::fRows) {
                    DoFill(i, j);
                }
            }
        }
    }

    if (fEnableHoughSpaceVis) {
        // save for visualization
        for (Eigen::Index i = 0; i < Base::fRows; ++i) {
            for (Eigen::Index j = 0; j < Base::fRows; ++j) {
                fHoughSpaceVis(i, j) = Base::fHoughSpace(i, j).size();
            }
        }
    }
}

template<class SpectrometerHitType>
void MACE::Reconstruction::Recognizer::HoughCartesian<SpectrometerHitType>::SaveLastRecognition(const char* fileName) {
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

        TH2I houghSpace("HoughSpace", "hough space", Base::fRows, -fExtent, fExtent, Base::fRows, -fExtent, fExtent);
        houghSpace.SetStats(false);
        houghSpace.SetXTitle("x[mm]");
        houghSpace.SetYTitle("y[mm]");
        houghSpace.SetDrawOption("COLZ");
        for (Eigen::Index i = 0; i < Base::fRows; ++i) {
            for (Eigen::Index j = 0; j < Base::fRows; ++j) {
                const auto xc = ToRealX(i);
                const auto yc = ToRealY(j);
                houghSpace.Fill(xc, yc, fHoughSpaceVis(i, j));
            }
        }
        houghSpace.Write();

        TH2I houghSpaceET("HoughSpaceExceedThreshold", "hough space exceed threshold", Base::fRows, -fExtent, fExtent, Base::fRows, -fExtent, fExtent);
        houghSpaceET.SetStats(false);
        houghSpaceET.SetXTitle("x[mm]");
        houghSpaceET.SetYTitle("y[mm]");
        houghSpaceET.SetDrawOption("COLZ");
        for (Eigen::Index i = 0; i < Base::fRows; ++i) {
            for (Eigen::Index j = 0; j < Base::fRows; ++j) {
                const auto xc = ToRealX(i);
                const auto yc = ToRealY(j);
                if (fHoughSpaceVis(i, j) >= Base::fThreshold) {
                    houghSpaceET.Fill(xc, yc, fHoughSpaceVis(i, j));
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
            auto hitMarker = new TMarker(point->GetHitPosition().fX, point->GetHitPosition().fY, markerStyle[styleIndex]);
            hitMarker->SetMarkerColor(markerColor[colorIndex]);
            hitMarker->Draw();
        }
    }
    realSpace.Write();
}
