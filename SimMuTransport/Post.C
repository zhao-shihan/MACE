#include <iostream>
#include <vector>
#include <sstream>
#include "TFile.h"
#include "TKey.h"
#include "TNtuple.h"
#include "TH3F.h"
#include "TH2F.h"

int POST(
    // I/O file name.
    const TString& input, const TString& output,

    // Analysis range.
    const Double32_t targetXMin,
    const Double32_t targetXMax,
    const Double32_t targetYMin,
    const Double32_t targetYMax,
    const Double32_t targetZMin,
    const Double32_t targetZMax,

    const Double32_t worldXMin,
    const Double32_t worldXMax,
    const Double32_t worldYMin,
    const Double32_t worldYMax,
    const Double32_t worldZMin,
    const Double32_t worldZMax,

    // Position H3F configs.
    const Int_t nPosBinsX,
    const Int_t nPosBinsY,
    const Int_t nPosBinsZ,

    // Position H2F configs.
    const size_t     nPosXYSlices,
    const Double32_t posXYSliceDz,
    const Int_t  nPosXYSliceBinsX,
    const Int_t  nPosXYSliceBinsY,

    const size_t     nPosYZSlices,
    const Double32_t posYZSliceDx,
    const Int_t  nPosYZSliceBinsY,
    const Int_t  nPosYZSliceBinsZ,

    const size_t     nPosXZSlices,
    const Double32_t posXZSliceDy,
    const Int_t  nPosXZSliceBinsX,
    const Int_t  nPosXZSliceBinsZ,

    // Vertex H3F configs.
    const Int_t  nVtxBinsX,
    const Int_t  nVtxBinsY,
    const Int_t  nVtxBinsZ,

    // Vertex H2F configs.
    const size_t     nVtxXYSlices,
    const Double32_t vtxXYSliceDz,
    const Int_t  nVtxXYSliceBinsX,
    const Int_t  nVtxXYSliceBinsY,

    const size_t     nVtxYZSlices,
    const Double32_t vtxYZSliceDx,
    const Int_t  nVtxYZSliceBinsY,
    const Int_t  nVtxYZSliceBinsZ,

    const size_t     nVtxXZSlices,
    const Double32_t vtxXZSliceDy,
    const Int_t  nVtxXZSliceBinsX,
    const Int_t  nVtxXZSliceBinsZ,

    // Decay H3F configs.
    const Int_t  nDecBinsX,
    const Int_t  nDecBinsY,
    const Int_t  nDecBinsZ,

    // Decay H2F configs.
    const size_t     nDecXYSlices,
    const Double32_t decXYSliceDz,
    const Int_t  nDecXYSliceBinsX,
    const Int_t  nDecXYSliceBinsY,

    const size_t     nDecYZSlices,
    const Double32_t decYZSliceDx,
    const Int_t  nDecYZSliceBinsY,
    const Int_t  nDecYZSliceBinsZ,

    const size_t     nDecXZSlices,
    const Double32_t decXZSliceDy,
    const Int_t  nDecXZSliceBinsX,
    const Int_t  nDecXZSliceBinsZ
) {

    auto Slicer = [](Double32_t min, Double32_t max, size_t n)->std::vector<Double32_t> {
        std::vector<Double32_t> slices(n);
        auto sliceGap = (max - min) / (n + 1);
        for (size_t i = 0; i < n; ++i) {
            slices[i] = min + (i + 1) * sliceGap;
        }
        return slices;
    };
    // Initialize slice parameters.
    auto posXYSlices = Slicer(targetZMin, targetZMax, nPosXYSlices);
    auto posYZSlices = Slicer(targetXMin, targetXMax, nPosYZSlices);
    auto posXZSlices = Slicer(targetYMin, targetYMax, nPosXZSlices);

    auto vtxXYSlices = Slicer(targetZMin, targetZMax, nVtxXYSlices);
    auto vtxYZSlices = Slicer(targetXMin, targetXMax, nVtxYZSlices);
    auto vtxXZSlices = Slicer(targetYMin, targetYMax, nVtxXZSlices);

    auto decXYSlices = Slicer(worldZMin, worldZMax, nDecXYSlices);
    auto decYZSlices = Slicer(worldXMin, worldXMax, nDecYZSlices);
    auto decXZSlices = Slicer(worldYMin, worldYMax, nDecXZSlices);

    // Input file.
    auto inputFile = TFile::Open(input, "READ");
    if (inputFile == nullptr) {
        std::cout << "Cannot open <" << input << ">. Aborted." << std::endl;
        return EXIT_FAILURE;
    }
    // Output file.
    auto outputFile = TFile::Open(output, "RECREATE");
    if (outputFile == nullptr) {
        std::cout << "Cannot open <" << output << ">. Aborted." << std::endl;
        if (inputFile->IsOpen()) { inputFile->Close(); }
        return EXIT_FAILURE;
    }

    // Traverse all input Ntuples.
    for (auto keyAsObj : *inputFile->GetListOfKeys()) {
        auto key = dynamic_cast<TKey*>(keyAsObj);
        TString keyName(key->GetName());
        std::cout << "Processing " << input << '/' << keyName << " ... " << std::endl;
        auto Ntuple = inputFile->Get<TNtuple>(keyName);

        if (keyName != "Escaped") {

            // Position TH3F corresponding to this Ntuple. 
            auto xyz = static_cast<TH3F*>(outputFile->FindObject("XYZ," + keyName));
            if (xyz == nullptr) {
                xyz = new TH3F(
                    "XYZ," + keyName, keyName,
                    nPosBinsX, targetXMin, targetXMax,
                    nPosBinsY, targetYMin, targetYMax,
                    nPosBinsZ, targetZMin, targetZMax
                );
            }
            // Position TH2F, XY slices corresponding to this Ntuple. 
            std::vector<TH2F*> xy(nPosXYSlices);
            for (size_t i = 0; i < nPosXYSlices; ++i) {
                std::stringstream ss;
                TString titleName;
                ss << keyName << ",z=" << posXYSlices[i] << "um,dz=" << posXYSliceDz << "um";
                ss >> titleName;
                xy[i] = static_cast<TH2F*>(outputFile->FindObject("XY," + titleName));
                if (xy[i] == nullptr) {
                    xy[i] = new TH2F(
                        "XY," + titleName, titleName,
                        nPosXYSliceBinsX, targetXMin, targetXMax,
                        nPosXYSliceBinsY, targetYMin, targetYMax
                    );
                }
            }
            // Position TH2F, YZ slices corresponding to this Ntuple. 
            std::vector<TH2F*> yz(nPosYZSlices);
            for (size_t i = 0; i < nPosYZSlices; ++i) {
                std::stringstream ss;
                TString titleName;
                ss << keyName << ",x=" << posYZSlices[i] << "um,dx=" << posYZSliceDx << "um";
                ss >> titleName;
                yz[i] = static_cast<TH2F*>(outputFile->FindObject("YZ," + titleName));
                if (yz[i] == nullptr) {
                    yz[i] = new TH2F(
                        "YZ," + titleName, titleName,
                        nPosYZSliceBinsY, targetYMin, targetYMax,
                        nPosYZSliceBinsZ, targetZMin, targetZMax
                    );
                }
            }
            // Position TH2F, XZ slices corresponding to this Ntuple. 
            std::vector<TH2F*> xz(nPosXZSlices);
            for (size_t i = 0; i < nPosXZSlices; ++i) {
                std::stringstream ss;
                TString titleName;
                ss << keyName << ",y=" << posXZSlices[i] << "um,dy=" << posXZSliceDy << "um";
                ss >> titleName;
                xz[i] = static_cast<TH2F*>(outputFile->FindObject("XZ," + titleName));
                if (xz[i] == nullptr) {
                    xz[i] = new TH2F(
                        "XZ," + titleName, titleName,
                        nPosXZSliceBinsX, targetXMin, targetXMax,
                        nPosXZSliceBinsZ, targetZMin, targetZMax
                    );
                }
            }

            // Traverse each muonium. 
            for (int rowId = 0; rowId < Ntuple->GetEntries(); ++rowId) {
                Ntuple->GetEntry(rowId);
                auto args = Ntuple->GetArgs();
                Double32_t x = args[0];
                Double32_t y = args[1];
                Double32_t z = args[2];
                xyz->Fill(x, y, z);
                for (size_t i = 0; i < nPosXYSlices; ++i) {
                    if (z > posXYSlices[i] - 0.5 * posXYSliceDz &&
                        z < posXYSlices[i] + 0.5 * posXYSliceDz) {
                        xy[i]->Fill(x, y);
                        break;
                    }
                }
                for (size_t i = 0; i < nPosYZSlices; ++i) {
                    if (x > posYZSlices[i] - 0.5 * posYZSliceDx &&
                        x < posYZSlices[i] + 0.5 * posYZSliceDx) {
                        yz[i]->Fill(y, z);
                        break;
                    }
                }
                for (size_t i = 0; i < nPosXZSlices; ++i) {
                    if (y > posXZSlices[i] - 0.5 * posXZSliceDy &&
                        y < posXZSlices[i] + 0.5 * posXZSliceDy) {
                        xz[i]->Fill(x, z);
                        break;
                    }
                }
            }

        } else { // keyName == "Escaped"

            // Escape, vertex TH3F corresponding to this Ntuple. 

            auto xvyvzv = static_cast<TH3F*>(outputFile->FindObject("XYZ_vertex," + keyName));
            if (xvyvzv == nullptr) {
                xvyvzv = new TH3F(
                    "XYZ_vertex," + keyName, keyName,
                    nVtxBinsX, targetXMin, targetXMax,
                    nVtxBinsY, targetYMin, targetYMax,
                    nVtxBinsZ, targetZMin, targetZMax
                );
            }
            // Escape, vertex TH2F, XY slices corresponding to this Ntuple. 
            std::vector<TH2F*> xvyv(nVtxXYSlices);
            for (size_t i = 0; i < nVtxXYSlices; ++i) {
                std::stringstream ss;
                TString titleName;
                ss << keyName << ",z=" << vtxXYSlices[i] << "um,dz=" << vtxXYSliceDz << "um";
                ss >> titleName;
                xvyv[i] = static_cast<TH2F*>(outputFile->FindObject("XY_vertex," + titleName));
                if (xvyv[i] == nullptr) {
                    xvyv[i] = new TH2F(
                        "XY_vertex," + titleName, titleName,
                        nVtxXYSliceBinsX, targetXMin, targetXMax,
                        nVtxXYSliceBinsY, targetYMin, targetYMax
                    );
                }
            }
            // Escape, vertex TH2F, YZ slices corresponding to this Ntuple. 
            std::vector<TH2F*> yvzv(nVtxYZSlices);
            for (size_t i = 0; i < nVtxYZSlices; ++i) {
                std::stringstream ss;
                TString titleName;
                ss << keyName << ",x=" << vtxYZSlices[i] << "um,dx=" << vtxYZSliceDx << "um";
                ss >> titleName;
                yvzv[i] = static_cast<TH2F*>(outputFile->FindObject("YZ_vertex," + titleName));
                if (yvzv[i] == nullptr) {
                    yvzv[i] = new TH2F(
                        "YZ_vertex," + titleName, titleName,
                        nVtxYZSliceBinsY, targetYMin, targetYMax,
                        nVtxYZSliceBinsZ, targetZMin, targetZMax
                    );
                }
            }
            // Escape, vertex TH2F, XZ slices corresponding to this Ntuple. 
            std::vector<TH2F*> xvzv(nVtxXZSlices);
            for (size_t i = 0; i < nVtxXZSlices; ++i) {
                std::stringstream ss;
                TString titleName;
                ss << keyName << ",y=" << vtxXZSlices[i] << "um,dy=" << vtxXZSliceDy << "um";
                ss >> titleName;
                xvzv[i] = static_cast<TH2F*>(outputFile->FindObject("XZ_vertex," + titleName));
                if (xvzv[i] == nullptr) {
                    xvzv[i] = new TH2F(
                        "XZ_vertex," + titleName, titleName,
                        nVtxXZSliceBinsX, targetXMin, targetXMax,
                        nVtxXZSliceBinsZ, targetZMin, targetZMax
                    );
                }
            }

            // Decay TH3F corresponding to this Ntuple. 

            auto xdydzd = static_cast<TH3F*>(outputFile->FindObject("XYZ_decay," + keyName));
            if (xdydzd == nullptr) {
                xdydzd = new TH3F(
                    "XYZ_decay," + keyName, keyName,
                    nDecBinsX, targetXMin, targetXMax,
                    nDecBinsY, targetYMin, targetYMax,
                    nDecBinsZ, targetZMin, targetZMax
                );
            }
            // Decay TH2F, XY slices corresponding to this Ntuple. 
            std::vector<TH2F*> xdyd(nDecXYSlices);
            for (size_t i = 0; i < nDecXYSlices; ++i) {
                std::stringstream ss;
                TString titleName;
                ss << keyName << ",z=" << decXYSlices[i] << "um,dz=" << decXYSliceDz << "um";
                ss >> titleName;
                xdyd[i] = static_cast<TH2F*>(outputFile->FindObject("XY_decay," + titleName));
                if (xdyd[i] == nullptr) {
                    xdyd[i] = new TH2F(
                        "XY_decay," + titleName, titleName,
                        nDecXYSliceBinsX, targetXMin, targetXMax,
                        nDecXYSliceBinsY, targetYMin, targetYMax
                    );
                }
            }
            // Decay TH2F, YZ slices corresponding to this Ntuple. 
            std::vector<TH2F*> ydzd(nDecYZSlices);
            for (size_t i = 0; i < nDecYZSlices; ++i) {
                std::stringstream ss;
                TString titleName;
                ss << keyName << ",x=" << decYZSlices[i] << "um,dx=" << decYZSliceDx << "um";
                ss >> titleName;
                ydzd[i] = static_cast<TH2F*>(outputFile->FindObject("YZ_decay," + titleName));
                if (ydzd[i] == nullptr) {
                    ydzd[i] = new TH2F(
                        "YZ_decay," + titleName, titleName,
                        nDecYZSliceBinsY, targetYMin, targetYMax,
                        nDecYZSliceBinsZ, targetZMin, targetZMax
                    );
                }
            }
            // Decay TH2F, XZ slices corresponding to this Ntuple. 
            std::vector<TH2F*> xdzd(nDecXZSlices);
            for (size_t i = 0; i < nDecXZSlices; ++i) {
                std::stringstream ss;
                TString titleName;
                ss << keyName << ",y=" << decXZSlices[i] << "um,dy=" << decXZSliceDy << "um";
                ss >> titleName;
                xdzd[i] = static_cast<TH2F*>(outputFile->FindObject("XZ_decay," + titleName));
                if (xdzd[i] == nullptr) {
                    xdzd[i] = new TH2F(
                        "XZ_decay," + titleName, titleName,
                        nDecXZSliceBinsX, targetXMin, targetXMax,
                        nDecXZSliceBinsZ, targetZMin, targetZMax
                    );
                }
            }

            // Decay angular distribution TH2F corresponding to this Ntuple. 
            auto angulard = static_cast<TH2F*>(outputFile->FindObject("AngularDistribution," + keyName));
            if (angulard == nullptr) {
                angulard = new TH2F(
                    "AngularDistribution," + keyName, keyName,
                    360, -M_PI, M_PI,
                    180, 0.0, M_PI
                );
            }

            // Traverse each muonium. 
            for (int rowId = 0; rowId < Ntuple->GetEntries(); ++rowId) {
                Ntuple->GetEntry(rowId);
                auto args = Ntuple->GetArgs();
                
                Double32_t xv = args[0];
                Double32_t yv = args[1];
                Double32_t zv = args[2];
                xvyvzv->Fill(xv, yv, zv);
                for (size_t i = 0; i < nVtxXYSlices; ++i) {
                    if (zv > vtxXYSlices[i] - 0.5 * vtxXYSliceDz &&
                        zv < vtxXYSlices[i] + 0.5 * vtxXYSliceDz) {
                        xvyv[i]->Fill(xv, yv);
                        break;
                    }
                }
                for (size_t i = 0; i < nVtxYZSlices; ++i) {
                    if (xv > vtxYZSlices[i] - 0.5 * vtxYZSliceDx &&
                        xv < vtxYZSlices[i] + 0.5 * vtxYZSliceDx) {
                        yvzv[i]->Fill(yv, zv);
                        break;
                    }
                }
                for (size_t i = 0; i < nVtxXZSlices; ++i) {
                    if (yv > vtxXZSlices[i] - 0.5 * vtxXZSliceDy &&
                        yv < vtxXZSlices[i] + 0.5 * vtxXZSliceDy) {
                        xvzv[i]->Fill(xv, zv);
                        break;
                    }
                }
                
                Double32_t xd = args[4];
                Double32_t yd = args[5];
                Double32_t zd = args[6];
                Double32_t phid = atan2(yd, xd);
                Double32_t thetad = atan2(sqrt(xd * xd + yd * yd), zd);
                xdydzd->Fill(xd, yd, zd);
                angulard->Fill(phid, thetad, 1.0 / sin(thetad));
                for (size_t i = 0; i < nDecXYSlices; ++i) {
                    if (zd > decXYSlices[i] - 0.5 * decXYSliceDz &&
                        zd < decXYSlices[i] + 0.5 * decXYSliceDz) {
                        xdyd[i]->Fill(xd, yd);
                        break;
                    }
                }
                for (size_t i = 0; i < nDecYZSlices; ++i) {
                    if (xd > decYZSlices[i] - 0.5 * decYZSliceDx &&
                        xd < decYZSlices[i] + 0.5 * decYZSliceDx) {
                        ydzd[i]->Fill(yd, zd);
                        break;
                    }
                }
                for (size_t i = 0; i < nDecXZSlices; ++i) {
                    if (yd > decXZSlices[i] - 0.5 * decXZSliceDy &&
                        yd < decXZSlices[i] + 0.5 * decXZSliceDy) {
                        xdzd[i]->Fill(xd, zd);
                        break;
                    }
                }
            }
        }
    }

    outputFile->Write();
    outputFile->Close();
    inputFile->Close();

    return EXIT_SUCCESS;
}

