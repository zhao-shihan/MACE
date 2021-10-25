#include <unordered_set>

#include "TKey.h"
#include "TH2I.h"
#include "TCanvas.h"
#include "TMarker.h"

#include "Recognizer.hh"

using namespace MACE::Reconstruction;
using namespace MACE::DataModel::Hit;

Recognizer::Recognizer(Double_t houghSpaceExtent, Double_t proposingHoughSpaceResolution) :
    fSize(round(2.0 * houghSpaceExtent / proposingHoughSpaceResolution)),
    fExtent(houghSpaceExtent),
    fResolution(2.0 * houghSpaceExtent / fSize),
    fHoughStore(fSize, fSize),
    fHoughSpace(fSize, fSize),
    fCenterCandidateList(0),
    fCenterClusterList(0),
    fRecognizedTrackList(0) {
    std::for_each_n(fHoughStore.data(), fSize * fSize, [](SpectrometerHitPointerList& elem) { elem.reserve(64UL); });
    fCenterClusterList.reserve(32UL);
    fRecognizedTrackList.reserve(32UL);
    Initialize();
}

Recognizer::~Recognizer() {
    if (fFile != nullptr) {
        if (fFile->IsOpen()) {
            fFile->Write();
            fFile->Close();
        }
        delete fFile;
    }
}

void Recognizer::Recognize() {
    Initialize();
    HoughTransform();
    VoteForCenter();
    CenterClusterizaion();
    GenerateResult();
}

void Recognizer::Initialize() {
    std::for_each_n(fHoughStore.data(), fSize * fSize, [](SpectrometerHitPointerList& elem) { elem.clear(); });
    fHoughSpace.fill(0);
    fCenterCandidateList.clear();
    fCenterClusterList.clear();
    fRecognizedTrackList.clear();
}

void Recognizer::HoughTransform() {
    // do hough transform
    for (const auto& hit : *fpHitList) {
        const Double_t R2 = hit.GetHitPosition().x() * hit.GetHitPosition().x() + hit.GetHitPosition().y() * hit.GetHitPosition().y();
        const Double_t X = 2.0 * hit.GetHitPosition().x() / R2;
        const Double_t Y = 2.0 * hit.GetHitPosition().y() / R2;
        if (fabs(X / Y) < 1.0) {
            for (Eigen::Index i = 0; i < fSize; ++i) {
                const Double_t xc = ToRealX(i);
                const Double_t yc = (1.0 - X * xc) / Y;
                if (xc * xc + yc * yc < fProtectedRadius * fProtectedRadius) { continue; }
                const Eigen::Index j = ToHoughY(yc);
                if (0 <= j && j < fSize) {
                    fHoughStore(i, j).emplace_back(&hit);
                }
            }
        } else {
            for (Eigen::Index j = 0; j < fSize; ++j) {
                const Double_t yc = ToRealY(j);
                const Double_t xc = (1.0 - Y * yc) / X;
                if (xc * xc + yc * yc < fProtectedRadius * fProtectedRadius) { continue; }
                const Eigen::Index i = ToHoughX(xc);
                if (0 <= i && i < fSize) {
                    fHoughStore(i, j).emplace_back(&hit);
                }
            }
        }
    }
    // fill count space
    for (Eigen::Index i = 0; i < fSize; ++i) {
        for (Eigen::Index j = 0; j < fSize; ++j) {
            fHoughSpace(i, j) = fHoughStore(i, j).size();
        }
    }
}

void Recognizer::VoteForCenter() {
    for (Eigen::Index i = 0; i < fSize; ++i) {
        for (Eigen::Index j = 0; j < fSize; ++j) {
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

void Recognizer::CenterClusterizaion() {
    while (!fCenterCandidateList.empty()) {
        // new cluster
        auto& cluster = fCenterClusterList.emplace_back(0);
        cluster.reserve(16UL);
        // Do clusterizaion. Find neighbour recursively, fill the cbegin(),
        // and cbegin()'s neighbour, sub-neighbour, sub-sub-neighbour, ...
        ClusterizationImpl(fCenterCandidateList.cbegin(), cluster);
    }
}

void Recognizer::ClusterizationImpl(std::list<std::pair<HoughPoint, RealPointPolar>>::const_iterator candidate, std::vector<HoughPoint>& cluster) {
    // find neighbour
    auto neighbour = std::find_if(std::next(candidate), fCenterCandidateList.cend(),
        [&](const std::pair<HoughPoint, RealPointPolar>& anotherCandidate) {
            const auto deltaR = candidate->second.first - anotherCandidate.second.first;
            const auto deltaPhi = candidate->second.second - anotherCandidate.second.second;
            return (-fScannerDR < deltaR) && (deltaR < fScannerDR) && (
                ((-fScannerDPhi < deltaPhi) && (deltaPhi < fScannerDPhi)) ||
                ((-fScannerDPhi < deltaPhi - (2.0 * M_PI)) && (deltaPhi - (2.0 * M_PI) < fScannerDPhi)) ||
                ((-fScannerDPhi < deltaPhi + (2.0 * M_PI)) && (deltaPhi + (2.0 * M_PI) < fScannerDPhi)));
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

void Recognizer::GenerateResult() {
    std::unordered_set<const DataModel::Hit::SpectrometerHit*> trackPointSet;
    for (const auto& cluster : fCenterClusterList) {
        // drop duplications
        for (const auto& candidate : cluster) {
            for (const auto* hitPointer : fHoughStore(candidate.first, candidate.second)) {
                trackPointSet.emplace(hitPointer);
            }
        }
        // dump point set to a track
        auto& newTrack = fRecognizedTrackList.emplace_back(0);
        newTrack.reserve(trackPointSet.size());
        for (const auto* trackPoint : trackPointSet) {
            newTrack.emplace_back(trackPoint);
        }
        // clear set for next use
        trackPointSet.clear();
    }
}

void Recognizer::SaveLastRecognition(const char* fileName) {
    if (fFile == nullptr) { fFile = new TFile(fileName, "RECREATE"); }
    if (strcmp(fileName, fFile->GetName()) != 0) {
        if (fFile->IsOpen()) {
            fFile->Write();
            fFile->Close();
        }
        delete fFile;
        fFile = new TFile(fileName, "RECREATE");
    }

    TH2I houghSpace("HoughSpace", "hough space", fSize, -fExtent, fExtent, fSize, -fExtent, fExtent);
    houghSpace.SetStats(false);
    houghSpace.SetXTitle("x[mm]");
    houghSpace.SetYTitle("y[mm]");
    houghSpace.SetDrawOption("COLZ");
    for (Eigen::Index i = 0; i < fSize; ++i) {
        for (Eigen::Index j = 0; j < fSize; ++j) {
            const Double_t xc = ToRealX(i);
            const Double_t yc = ToRealY(j);
            houghSpace.Fill(xc, yc, fHoughStore(i, j).size());
        }
    }
    houghSpace.Write();

    TH2I houghSpaceET("HoughSpaceExceedThreshold", "hough space exceed threshold", fSize, -fExtent, fExtent, fSize, -fExtent, fExtent);
    houghSpaceET.SetStats(false);
    houghSpaceET.SetXTitle("x[mm]");
    houghSpaceET.SetYTitle("y[mm]");
    houghSpaceET.SetDrawOption("COLZ");
    for (Eigen::Index i = 0; i < fSize; ++i) {
        for (Eigen::Index j = 0; j < fSize; ++j) {
            const Double_t xc = ToRealX(i);
            const Double_t yc = ToRealY(j);
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
    constexpr std::array<EMarkerStyle, 7> markerStyle = { kPlus, kMultiply, kOpenCircle, kOpenSquare, kOpenTriangleUp, kOpenDiamond, kOpenTriangleDown };
    for (size_t i = 0; i < std::min<size_t>(fRecognizedTrackList.size(), markerColor.size() * markerStyle.size()); ++i) {
        for (const auto& point : fRecognizedTrackList[i]) {
            auto colorStyleIndex = i % (markerColor.size() * markerStyle.size());
            auto styleIndex = colorStyleIndex / markerColor.size();
            auto colorIndex = colorStyleIndex % markerColor.size();
            auto hitMarker = new TMarker(point->GetHitPosition().x(), point->GetHitPosition().y(), markerStyle[styleIndex]);
            hitMarker->SetMarkerColor(markerColor[colorIndex]);
            hitMarker->Draw();
        }
    }
    realSpace.Write();
    // for (const auto& hit : *fpHitList) {
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
