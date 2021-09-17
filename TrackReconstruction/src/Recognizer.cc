#include "TKey.h"
#include "TH2I.h"
#include "TCanvas.h"
#include "TMarker.h"
#include "TFolder.h"

#include "Recognizer.hh"
#include "Hit.hh"

using namespace MACE::TrackReconstruction;

Recognizer::Recognizer(Double_t houghSpaceExtent, Double_t proposingHoughSpaceResolution) :
    fSize(round(2.0 * houghSpaceExtent / proposingHoughSpaceResolution)),
    fExtent(houghSpaceExtent),
    fResolution(2.0 * houghSpaceExtent / fSize),
    fHoughStore(fSize, fSize),
    fHoughCount(fSize, fSize),
    fResult(0),
    fDataResultIsConsistent(false) {}

Recognizer::Recognizer(Recognizer&& rvalue) :
    fSize(std::move(rvalue.fSize)),
    fExtent(std::move(rvalue.fExtent)),
    fResolution(std::move(rvalue.fResolution)),
    fProtectedRadius(std::move(rvalue.fProtectedRadius)),
    fThreshold(std::move(rvalue.fThreshold)),
    fCoincidenceChamberID(std::move(rvalue.fCoincidenceChamberID)),
    fpPluseData(std::move(rvalue.fpPluseData)),
    fHoughStore(std::move(rvalue.fHoughStore)),
    fHoughCount(std::move(rvalue.fHoughCount)),
    fResult(std::move(rvalue.fResult)),
    fDataResultIsConsistent(std::move(rvalue.fDataResultIsConsistent)),
    fFile(std::move(rvalue.fFile)) {}

Recognizer::~Recognizer() {
    if (fFile != nullptr) {
        if (fFile->IsOpen()) {
            fFile->Write();
            fFile->Close();
        }
    }
    delete fFile;
}

void Recognizer::Recognize() {
    Initialize();
    if (fpPluseData->size() >= fThreshold) {
        HoughTransform();
    }
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
    // do hough transform
    for (const auto& hit : *fpPluseData) {
        const Double_t R2 = hit.HitPosition().x() * hit.HitPosition().x() + hit.HitPosition().y() * hit.HitPosition().y();
        const Double_t X = 2.0 * hit.HitPosition().x() / R2;
        const Double_t Y = 2.0 * hit.HitPosition().y() / R2;
        if (fabs(X / Y) < 1.0) {
            for (Eigen::Index i = 0; i < fSize; ++i) {
                const Double_t xc = -fExtent + (i + 0.5) * fResolution;
                const Double_t yc = (1.0 - X * xc) / Y;
                if (xc * xc + yc * yc < fProtectedRadius * fProtectedRadius) { continue; }
                const Eigen::Index j = (yc + fExtent) / fResolution;
                if (0 <= j && j < fSize) { fHoughStore(i, j).push_back(&hit); }
            }
        } else {
            for (Eigen::Index j = 0; j < fSize; ++j) {
                const Double_t yc = -fExtent + (j + 0.5) * fResolution;
                const Double_t xc = (1.0 - Y * yc) / X;
                if (xc * xc + yc * yc < fProtectedRadius * fProtectedRadius) { continue; }
                const Eigen::Index i = (xc + fExtent) / fResolution;
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

void Recognizer::SaveLastRecognition(const char* fileName) {
    if (!fDataResultIsConsistent) {
        std::cout << "Warning: Data and result are inconsistent. Try do Recognize() before printing the result. Nothing was done here." << std::endl;
        return;
    }
    if (fFile == nullptr) { fFile = new TFile(fileName, "RECREATE"); }

    TH2I houghSpace("HoughSpace", "hough space", fSize, -fExtent, fExtent, fSize, -fExtent, fExtent);
    houghSpace.SetStats(false);
    houghSpace.SetXTitle("x[mm]");
    houghSpace.SetYTitle("y[mm]");
    houghSpace.SetDrawOption("COLZ");
    for (Eigen::Index i = 0; i < fSize; ++i) {
        for (Eigen::Index j = 0; j < fSize; ++j) {
            const Double_t xc = -fExtent + (i + 0.5) * fResolution;
            const Double_t yc = -fExtent + (j + 0.5) * fResolution;
            houghSpace.Fill(xc, yc, fHoughStore(i, j).size());
        }
    }

    TCanvas realSpace("RealSpace", "real space");
    realSpace.SetGrid();
    TH2I realSpaceAxis("RealSpace", "real space", 1, -350, 350, 1, -350, 350);
    realSpaceAxis.SetStats(false);
    realSpaceAxis.SetXTitle("x[mm]");
    realSpaceAxis.SetYTitle("y[mm]");
    realSpaceAxis.Draw("AXIS");
    for (const auto& hit : *fpPluseData) {
        auto hitMarker = new TMarker(hit.HitPosition().x(), hit.HitPosition().y(), kFullCircle);
        hitMarker->SetMarkerColor(kBlue);
        if (std::find(fResult.cbegin(), fResult.cend(), &hit) != fResult.cend()) {
            hitMarker->SetMarkerStyle(kFullSquare);
        }
        hitMarker->Draw();
        auto vertexMarker = new TMarker(hit.VertexPosition().x(), hit.VertexPosition().y(), kPlus);
        vertexMarker->SetMarkerSize(2);
        vertexMarker->SetMarkerColor(kRed);
        vertexMarker->Draw();
    }

    TFolder folder("Recognition", "a recognition");
    folder.Add(&houghSpace);
    folder.Add(&realSpace);
    folder.Write();
}
