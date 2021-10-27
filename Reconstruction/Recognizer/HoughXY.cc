#include <unordered_set>

#include "TKey.h"
#include "TH2I.h"
#include "TCanvas.h"
#include "TMarker.h"

#include "Reconstruction/Recognizer/HoughXY.hh"

using namespace MACE::Reconstruction::Recognizer;
using namespace MACE::DataModel::Hit;

HoughXY::HoughXY(Double_t houghSpaceExtent, Eigen::Index size, Double_t protectedRadius) :
    HoughBase(size, size),
    fExtent(houghSpaceExtent),
    fResolution(2.0 * houghSpaceExtent / size),
    fProtectedRadius(protectedRadius) {}

HoughXY::~HoughXY() {
    if (fFile != nullptr) {
        if (fFile->IsOpen()) {
            fFile->Write();
            fFile->Close();
        }
        delete fFile;
    }
}

void HoughXY::HoughTransform() {
    // do hough transform
    for (auto&& hit : *fpHitList) {
        const auto hitX = hit.GetHitPosition().x();
        const auto hitY = hit.GetHitPosition().y();
        const auto R2 = hitX * hitX + hitY * hitY;
        const auto X = 2.0 * hitX / R2;
        const auto Y = 2.0 * hitY / R2;
        if (abs(X / Y) < 1.0) {
            for (Eigen::Index i = 0; i < fRows; ++i) {
                const auto xc = ToRealX(i);
                const auto yc = (1.0 - X * xc) / Y;
                if (xc * xc + yc * yc < fProtectedRadius * fProtectedRadius) { continue; }
                const Eigen::Index j = ToHoughY(yc);
                if (0 <= j && j < fRows) {
                    fHoughStore(i, j).emplace_back(&hit);
                }
            }
        } else {
            for (Eigen::Index j = 0; j < fRows; ++j) {
                const auto yc = ToRealY(j);
                const auto xc = (1.0 - Y * yc) / X;
                if (xc * xc + yc * yc < fProtectedRadius * fProtectedRadius) { continue; }
                const Eigen::Index i = ToHoughX(xc);
                if (0 <= i && i < fRows) {
                    fHoughStore(i, j).emplace_back(&hit);
                }
            }
        }
    }
    // fill count space
    for (Eigen::Index i = 0; i < fRows; ++i) {
        for (Eigen::Index j = 0; j < fRows; ++j) {
            fHoughSpace(i, j) = fHoughStore(i, j).size();
        }
    }
}

void HoughXY::VoteForCenter() {
    for (Eigen::Index i = 0; i < fRows; ++i) {
        for (Eigen::Index j = 0; j < fRows; ++j) {
            if (fHoughSpace(i, j) >= fThreshold) {
                const auto x = ToRealX(i);
                const auto y = ToRealY(j);
                const auto r = sqrt(x * x + y * y);
                const auto phi = atan2(y, x);
                fCenterCandidateList.emplace_back(std::make_pair(i, j), std::make_pair(r, phi));
            }
        }
    }
}

void HoughXY::CenterClusterizaion() {
    while (!fCenterCandidateList.empty()) {
        // new cluster
        auto& cluster = fCenterClusterList.emplace_back(0);
        cluster.reserve(16UL);
        // Do clusterizaion. Find neighbour recursively, fill the cbegin(),
        // and cbegin()'s neighbour, sub-neighbour, sub-sub-neighbour, ...
        ClusterizationImpl(fCenterCandidateList.cbegin(), cluster);
    }
}

void HoughXY::ClusterizationImpl(std::list<CoordinateSet>::const_iterator candidate, std::vector<HoughCoordinate>& cluster) {
    // find neighbour
    const auto thisR = candidate->second.first;
    const auto thisPhi = candidate->second.second;
    auto neighbour = std::find_if(std::next(candidate), fCenterCandidateList.cend(),
        [&](const CoordinateSet& anotherCandidate) {
            const auto [anotherR, anotherPhi] = anotherCandidate.second;
            const auto deltaR = abs(thisR - anotherR);
            const auto deltaPhi = abs(thisPhi - anotherPhi);
            return deltaR < fScannerDR &&
                (deltaPhi < fScannerDPhi || ((2.0 * M_PI) - deltaPhi) < fScannerDPhi);
        }
    );
    // fill candidate itself
    cluster.emplace_back(std::move(candidate->first));
    fCenterCandidateList.erase(candidate);
    // and find neighbour recursively
    // essential: stop condition
    if (neighbour == fCenterCandidateList.cend()) { return; }
    ClusterizationImpl(neighbour, cluster);
}

void HoughXY::GenerateResult() {
    std::unordered_set<const DataModel::Hit::SpectrometerHit*> trackHitSet;

    for (auto&& cluster : fCenterClusterList) {
        // drop duplications
        for (auto&& center : cluster) {
            for (auto&& hitPointer : fHoughStore(center.first, center.second)) {
                trackHitSet.emplace(hitPointer);
            }
        }

        Double_t centerX = 0;
        Double_t centerY = 0;
        for (auto&& center : cluster) {
            centerX += ToRealX(center.first);
            centerY += ToRealY(center.second);
        }
        centerX /= cluster.size();
        centerY /= cluster.size();

        SpectrometerHitPointerList leftHandHitList;
        SpectrometerHitPointerList rightHandHitList;
        leftHandHitList.reserve(trackHitSet.size());
        rightHandHitList.reserve(trackHitSet.size());
        for (auto&& trackPoint : trackHitSet) {
            const auto hitX = trackPoint->GetHitPosition().x();
            const auto hitY = trackPoint->GetHitPosition().y();
            const auto cross = hitX * centerY - centerX * hitY;
            if (cross > 0) {
                rightHandHitList.emplace_back(trackPoint);
            } else {
                leftHandHitList.emplace_back(trackPoint);
            }
        }
        trackHitSet.clear();

        // dump to track list
        if (leftHandHitList.size() >= fThreshold) {
            fRecognizedTrackList.emplace_back(std::move(leftHandHitList));
        }
        if (rightHandHitList.size() >= fThreshold) {
            fRecognizedTrackList.emplace_back(std::move(rightHandHitList));
        }
    }
}

void HoughXY::SaveLastRecognition(const char* fileName) {
    if (fFile == nullptr) { fFile = new TFile(fileName, "RECREATE"); }
    if (strcmp(fileName, fFile->GetName()) != 0) {
        if (fFile->IsOpen()) {
            fFile->Write();
            fFile->Close();
        }
        delete fFile;
        fFile = new TFile(fileName, "RECREATE");
    }

    TH2I houghSpace("HoughSpace", "hough space", fRows, -fExtent, fExtent, fRows, -fExtent, fExtent);
    houghSpace.SetStats(false);
    houghSpace.SetXTitle("x[mm]");
    houghSpace.SetYTitle("y[mm]");
    houghSpace.SetDrawOption("COLZ");
    for (Eigen::Index i = 0; i < fRows; ++i) {
        for (Eigen::Index j = 0; j < fRows; ++j) {
            const auto xc = ToRealX(i);
            const auto yc = ToRealY(j);
            houghSpace.Fill(xc, yc, fHoughStore(i, j).size());
        }
    }
    houghSpace.Write();

    TH2I houghSpaceET("HoughSpaceExceedThreshold", "hough space exceed threshold", fRows, -fExtent, fExtent, fRows, -fExtent, fExtent);
    houghSpaceET.SetStats(false);
    houghSpaceET.SetXTitle("x[mm]");
    houghSpaceET.SetYTitle("y[mm]");
    houghSpaceET.SetDrawOption("COLZ");
    for (Eigen::Index i = 0; i < fRows; ++i) {
        for (Eigen::Index j = 0; j < fRows; ++j) {
            const auto xc = ToRealX(i);
            const auto yc = ToRealY(j);
            if (fHoughStore(i, j).size() >= fThreshold) {
                houghSpaceET.Fill(xc, yc, fHoughStore(i, j).size());
            }
        }
    }
    houghSpaceET.Write();

    TCanvas realSpace("RealSpace", "real space");
    realSpace.SetGrid();
    TH2I realSpaceAxis("RealSpace", "real space", 1, -350, 350, 1, -350, 350);
    realSpaceAxis.SetStats(false);
    realSpaceAxis.SetXTitle("x[mm]");
    realSpaceAxis.SetYTitle("y[mm]");
    realSpaceAxis.Draw("AXIS");
    constexpr std::array<EColor, 14> markerColor = { kBlack, kGray, kRed, kGreen, kBlue, kYellow, kMagenta, kCyan, kOrange, kSpring, kTeal, kAzure, kViolet, kPink };
    constexpr std::array<EMarkerStyle, 5> markerStyle = { kPlus, kMultiply, kOpenTriangleUp, kOpenDiamond, kOpenTriangleDown };
    for (size_t i = 0; i < std::min<size_t>(fRecognizedTrackList.size(), markerColor.size() * markerStyle.size()); ++i) {
        for (auto&& point : fRecognizedTrackList[i]) {
            auto colorStyleIndex = i % (markerColor.size() * markerStyle.size());
            auto styleIndex = colorStyleIndex / markerColor.size();
            auto colorIndex = colorStyleIndex % markerColor.size();
            auto hitMarker = new TMarker(point->GetHitPosition().x(), point->GetHitPosition().y(), markerStyle[styleIndex]);
            hitMarker->SetMarkerColor(markerColor[colorIndex]);
            hitMarker->Draw();
        }
    }
    realSpace.Write();
    // for (auto&& hit : *fpHitList) {
    //     auto hitMarker = new TMarker(hit.GetHitPosition().x(), hit.GetHitPosition().y(), kFullCircle);
    //     hitMarker->SetMarkerColor(kBlue);
    //     if (std::find(fRecognizedTrackList.cbegin(), fRecognizedTrackList.cend(), &hit) != fRecognizedTrackList.cend()) {
    //         hitMarker->SetMarkerStyle(kFullSquare);
    //     }
    //     hitMarker->Draw();
    //     // auto vertexMarker = new TMarker(hit.GetVertexPosition().x(), hit.GetVertexPosition().y(), kPlus);
    //     // vertexMarker->SetMarkerSize(2);
    //     // vertexMarker->SetMarkerColor(kRed);
    //     // vertexMarker->Draw();
    // }
}
