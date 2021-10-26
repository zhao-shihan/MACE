#include <unordered_set>

#include "TKey.h"
#include "TH2I.h"
#include "TCanvas.h"
#include "TMarker.h"

#include "Reconstruction/Recognizer/HoughPolar.hh"

using namespace MACE::Reconstruction::Recognizer;
using namespace MACE::DataModel::Hit;

HoughPolar::HoughPolar(Double_t protectedRadius, Eigen::Index nRhos, Eigen::Index nPhis) :
    HoughBase(nRhos, nPhis, protectedRadius),
    fRhoResolution((1.0 / protectedRadius) / nRhos),
    fPhiResolution(2.0 * M_PI / nPhis) {}

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
    for (auto&& hit : *fpHitList) {
        const auto hitX = hit.GetHitPosition().x();
        const auto hitY = hit.GetHitPosition().y();
        const auto R2 = hitX * hitX + hitY * hitY;
        const auto X = 2.0 * hitX / R2;
        const auto Y = 2.0 * hitY / R2;
        // do hough transform
        auto phi = ToRealPhi(0);
        auto iLast = ToHoughRho(X * cos(phi) + Y * sin(phi));
        if (0 <= iLast && iLast < fRows) {
            fHoughStore(iLast, 0).emplace_back(&hit);
        }
        for (Eigen::Index j = 1; j < fCols; ++j) {
            phi = ToRealPhi(j);
            const auto i = ToHoughRho(X * cos(phi) + Y * sin(phi));
            const auto iDiff = i - iLast;
            if (iDiff > 1) {
                for (auto k = iLast + 1; k < iLast + iDiff / 2; ++k) {
                    if (0 <= k && k < fRows) {
                        fHoughStore(k, j - 1).emplace_back(&hit);
                    }
                }
                for (auto k = iLast + iDiff / 2; k < i; ++k) {
                    if (0 <= k && k < fRows) {
                        fHoughStore(k, j).emplace_back(&hit);
                    }
                }
            }
            if (iDiff < -1) {
                for (auto k = iLast - 1; k > iLast + iDiff / 2; --k) {
                    if (0 <= k && k < fRows) {
                        fHoughStore(k, j - 1).emplace_back(&hit);
                    }
                }
                for (auto k = iLast + iDiff / 2; k > i; --k) {
                    if (0 <= k && k < fRows) {
                        fHoughStore(k, j).emplace_back(&hit);
                    }
                }
            }
            if (0 <= i && i < fRows) {
                fHoughStore(i, j).emplace_back(&hit);
            }
            iLast = i;
        }
    }
    // fill count space
    for (Eigen::Index i = 0; i < fRows; ++i) {
        for (Eigen::Index j = 0; j < fCols; ++j) {
            fHoughSpace(i, j) = fHoughStore(i, j).size();
        }
    }
}

void HoughPolar::VoteForCenter() {
    for (Eigen::Index i = 0; i < fRows; ++i) {
        for (Eigen::Index j = 0; j < fCols; ++j) {
            if (fHoughSpace(i, j) >= fThreshold) {
                // RealCoordinate is useless in HoughPolar, fill a random one
                fCenterCandidateList.emplace_back(std::make_pair(i, j), RealCoordinate());
            }
        }
    }
}

void HoughPolar::CenterClusterizaion() {
    while (!fCenterCandidateList.empty()) {
        // new cluster
        auto& cluster = fCenterClusterList.emplace_back(0);
        cluster.reserve(16UL);
        // Do clusterizaion. Find neighbour recursively, fill the cbegin(),
        // and cbegin()'s neighbour, sub-neighbour, sub-sub-neighbour, ...
        ClusterizationImpl(fCenterCandidateList.cbegin(), cluster);
    }
}

void HoughPolar::ClusterizationImpl(std::list<CoordinateSet>::const_iterator candidate, std::vector<HoughCoordinate>& cluster) {
    // find neighbour
    const auto thisI = candidate->first.first;
    const auto thisJ = candidate->first.second;
    auto neighbour = std::find_if(std::next(candidate), fCenterCandidateList.cend(),
        [&](const CoordinateSet& anotherCandidate) {
            const auto [anotherI, anotherJ] = anotherCandidate.first;
            const auto deltaI = abs(thisI - anotherI);
            const auto deltaJ = abs(thisJ - anotherJ);
            return (deltaI < fScannerDI) && (deltaJ < fScannerDJ);
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

void HoughPolar::GenerateResult() {
    std::unordered_set<const DataModel::Hit::SpectrometerHit*> trackHitSet;

    for (auto&& cluster : fCenterClusterList) {
        // drop duplications
        for (auto&& center : cluster) {
            for (auto&& hitPointer : fHoughStore(center.first, center.second)) {
                trackHitSet.emplace(hitPointer);
            }
        }

        Double_t centerRho = 0;
        Double_t centerPhi = 0;
        for (auto&& center : cluster) {
            centerRho += ToRealRho(center.first);
            centerPhi += ToRealPhi(center.second);
        }
        centerRho /= cluster.size();
        centerPhi /= cluster.size();
        const auto centerX = cos(centerPhi) / centerRho;
        const auto centerY = sin(centerPhi) / centerRho;

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

    TH2I houghSpace("HoughSpace", "hough space", fRows, 0.0, 1.0 / fProtectedRadius, fCols, -M_PI, M_PI);
    houghSpace.SetStats(false);
    houghSpace.SetXTitle("1/r[1/mm]");
    houghSpace.SetYTitle("phi[rad]");
    houghSpace.SetDrawOption("COLZ");
    for (Eigen::Index i = 0; i < fRows; ++i) {
        for (Eigen::Index j = 0; j < fCols; ++j) {
            const auto rho = ToRealRho(i);
            const auto phi = ToRealPhi(j);
            houghSpace.Fill(rho, phi, fHoughStore(i, j).size());
        }
    }
    houghSpace.Write();

    TH2I houghSpaceET("HoughSpaceExceedThreshold", "hough space exceed threshold", fRows, 0.0, 1.0 / fProtectedRadius, fCols, -M_PI, M_PI);
    houghSpaceET.SetStats(false);
    houghSpace.SetXTitle("1/r[1/mm]");
    houghSpace.SetYTitle("phi[rad]");
    houghSpaceET.SetDrawOption("COLZ");
    for (Eigen::Index i = 0; i < fRows; ++i) {
        for (Eigen::Index j = 0; j < fCols; ++j) {
            const auto rho = ToRealRho(i);
            const auto phi = ToRealPhi(j);
            if (fHoughStore(i, j).size() >= fThreshold) {
                houghSpace.Fill(rho, phi, fHoughStore(i, j).size());
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
}