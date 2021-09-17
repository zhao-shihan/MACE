#include "TH2I.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMarker.h"
#include "TDirectory.h"

#include "Recognizer.hh"
#include "Hit.hh"

using namespace MACE::TrackReconstruction;

Recognizer::Recognizer(Eigen::Index size) :
    fSize(size),
    fHoughStore(size, size),
    fHoughCount(size, size),
    fResult(0) {}

Recognizer::Recognizer(Recognizer&& rvalue) :
    fThreshold(std::move(rvalue.fThreshold)),
    fMaxRadius(std::move(rvalue.fMaxRadius)),
    fProtectedRadius(std::move(rvalue.fProtectedRadius)),
    fCoincidenceChamberID(std::move(rvalue.fCoincidenceChamberID)),
    fDataResultIsConsistent(std::move(rvalue.fDataResultIsConsistent)),
    fpPluseData(std::move(rvalue.fpPluseData)),
    fSize(std::move(rvalue.fSize)),
    fHoughStore(std::move(rvalue.fHoughStore)),
    fHoughCount(std::move(rvalue.fHoughCount)),
    fResult(std::move(rvalue.fResult)) {}

void Recognizer::Recognize() {
    if (fpPluseData->size() < fThreshold) { return; }
    Initialize();
    HoughTransform();
    GenerateResult();
    fDataResultIsConsistent = true;
}

void Recognizer::Initialize() {
    for (Eigen::Index i = 0; i < fSize; ++i) {
        for (Eigen::Index j = 0; j < fSize; ++j) {
            fHoughStore(i, j).clear();
            fHoughStore(i, j).reserve(0x40UL);
        }
    }
    fHoughCount.fill(0);
}

void Recognizer::HoughTransform() {
    const Double_t resolution = 2.0 * fMaxRadius / fSize;
    // do hough transform
    for (const auto& hit : *fpPluseData) {
        const Double_t R2 = hit.HitPosition().x() * hit.HitPosition().x() + hit.HitPosition().y() * hit.HitPosition().y();
        const Double_t X = 2.0 * hit.HitPosition().x() / R2;
        const Double_t Y = 2.0 * hit.HitPosition().y() / R2;
        if (fabs(X / Y) < 1.0) {
            for (Eigen::Index i = 0; i < fSize; ++i) {
                const Double_t xc = -fMaxRadius + (i + 0.5) * resolution;
                const Double_t yc = (1.0 - X * xc) / Y;
                if (xc * xc + yc * yc < fProtectedRadius * fProtectedRadius) { continue; }
                const Eigen::Index j = yc / resolution + (fMaxRadius / resolution);
                if (0 <= j && j < fSize) { fHoughStore(i, j).push_back(&hit); }
            }
        } else {
            for (Eigen::Index j = 0; j < fSize; ++j) {
                const Double_t yc = -fMaxRadius + (j + 0.5) * resolution;
                const Double_t xc = (1.0 - Y * yc) / X;
                if (xc * xc + yc * yc < fProtectedRadius * fProtectedRadius) { continue; }
                const Eigen::Index i = xc / resolution + (fMaxRadius / resolution);
                if (0 <= i && i < fSize) { fHoughStore(i, j).push_back(&hit); }
            }
        }
    }
    // counting
    for (Eigen::Index i = 0; i < fSize; ++i) {
        for (Eigen::Index j = 0; j < fSize; ++j) {
            fHoughCount(i, j) = fHoughStore(i, j).size();
        }
    }
}

void Recognizer::GenerateResult() {
    fResult.clear();
    Eigen::Index imax, jmax;
    while (fHoughCount.maxCoeff(&imax, &jmax) >= fThreshold) {
        fHoughCount(imax, jmax) = 0;
        const auto firstHit = std::find_if(fHoughStore(imax, jmax).cbegin(), fHoughStore(imax, jmax).cend(),
            [this](const Hit* const hit)->bool { return hit->ChamberID() == fCoincidenceChamberID; });
        if (firstHit == fHoughStore(imax, jmax).cend()) { continue; }
        if (std::find(fResult.cbegin(), fResult.cend(), *firstHit) == fResult.cend()) {
            fResult.push_back(*firstHit);
        }
    }
}

void Recognizer::PrintLastRecognition(const char* realSpaceGraphFileName, const char* houghSpaceGraphFileName, UInt_t graphWidth, UInt_t graphHeight) const {
    if (!fDataResultIsConsistent) {
        printf("Warning: Data and result are inconsistent. Try do Recognize() before printing the result. Nothing was done here.");
        return;
    }

    std::cout << fpPluseData->size() << '\t' << fResult.size() << std::endl;

    auto dir = new TDirectory();

    auto canvas = new TCanvas(); dir->Add(canvas);
    canvas->SetCanvasSize(graphWidth, graphHeight);
    canvas->SetGrid();

    auto realSpace = new TH2I("RealSpace", "real space", 1, -350, 350, 1, -350, 350); realSpace->SetDirectory(dir);
    realSpace->SetStats(false);
    realSpace->Draw("AXIS");
    for (const auto& hit : *fpPluseData) {
        auto hitMarker = new TMarker(hit.HitPosition().x(), hit.HitPosition().y(), kFullSquare); dir->Add(hitMarker);
        hitMarker->SetMarkerColor(kBlue);
        hitMarker->Draw();
        auto vertexMarker = new TMarker(hit.VertexPosition().x(), hit.VertexPosition().y(), kPlus); dir->Add(vertexMarker);
        vertexMarker->SetMarkerSize(2);
        vertexMarker->SetMarkerColor(kRed);
        vertexMarker->Draw();
    }
    canvas->Print(realSpaceGraphFileName);
    canvas->Clear();

    auto houghSpace = new TH2I("HoughSpace", "hough space", fSize, 0, fSize, fSize, 0, fSize); houghSpace->SetDirectory(dir);
    for (Eigen::Index i = 0; i < fSize; ++i) {
        for (Eigen::Index j = 0; j < fSize; ++j) {
            houghSpace->Fill(i, j, fHoughStore(i, j).size());
        }
    }
    houghSpace->SetStats(false);
    houghSpace->Draw("COLZ");
    canvas->Print(houghSpaceGraphFileName);
    canvas->Clear();

    delete dir;
}