#include "ROOT/RDataFrame.hxx"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

const auto nBinsValueType{100};
auto DataTupleName{"VetoSimHit"};

auto GetVetoSimHit(auto moduleName, auto srcFileName, auto dstFileName) -> int {
    ROOT::RDataFrame df0{Form("G4Run0/%s", DataTupleName), srcFileName};
    const auto dstFile{new TFile(dstFileName, "UPDATE")};
    auto moduleDir{static_cast<TDirectory*>(dstFile->Get(moduleName))};
    if (!moduleDir) {
        std::clog << "DST File: Directory named " << moduleName << " is a new dir, create it." << std::endl;
        moduleDir = dstFile->mkdir(moduleName);
    }
    auto dstDir{moduleDir->mkdir(DataTupleName)};
    if (!dstDir) {
        std::cout << "Make TDirectory " << DataTupleName << " Failed. ";
        if (moduleDir->Get(DataTupleName)) {
            std::cout << "Already exist." << std::endl;
            return 1;
        }
    }
    std::clog << "Getting " << DataTupleName << " from module: " << moduleName << std::endl;
    dstFile->cd();
    dstDir->cd();

    auto df{df0.Define("x[0]", "x[0]")
                .Define("x[1]", "x[1]")
                .Define("x[2]", "x[2]")
                .Define("p[0]", "p[0]")
                .Define("p[1]", "p[1]")
                .Define("p[2]", "p[2]")
                .Define("x0[0]", "x0[0]")
                .Define("x0[1]", "x0[1]")
                .Define("x0[2]", "x0[2]")
                .Define("p0[0]", "p0[0]")
                .Define("p0[1]", "p0[1]")
                .Define("p0[2]", "p0[2]")};

    std::vector<std::tuple<std::string, std::any, std::any>> histParameterList{
        {"HitID",   0.,                                                                                   10.                                                                                 },
        {"StripID", 0.,                                                                                   200.                                                                                },
        // {"x0[0]",     -2100.,                                                                               2100.                                                                               },
        // {"x0[1]",     -2100.,                                                                               2100.                                                                               },
        // {"x0[2]",     -2100.,                                                                               2100.                                                                               },
        // {"Ek",      0.,                                                                                   std::function([&]() -> double { return *df.Mean("Ek") + 0.5 * *df.StdDev("Ek"); })    },
        // {"Ek0",     0.,                                                                                   std::function([&]() -> double { return *df.Mean("Ek0") + 0.5 * *df.StdDev("Ek0"); })  },
        {"Edep",    0.,                                                                                   std::function([&]() -> double { return *df.Mean("Edep") + 2 * *df.StdDev("Edep"); })},
        {"x[0]",      std::function([&]() -> double { return *df.Mean("x[0]") - 0.5 * *df.StdDev("x[0]"); }),   std::function([&]() -> double { return *df.Mean("x[0]") + 0.5 * *df.StdDev("x[0]"); })  },
        {"x[1]",      std::function([&]() -> double { return *df.Mean("x[1]") - 0.5 * *df.StdDev("x[1]"); }),   std::function([&]() -> double { return *df.Mean("x[1]") + 0.5 * *df.StdDev("x[1]"); })  },
        {"x[2]",      std::function([&]() -> double { return *df.Mean("x[2]") - 0.5 * *df.StdDev("x[2]"); }),   std::function([&]() -> double { return *df.Mean("x[2]") + 0.5 * *df.StdDev("x[2]"); })  },
        // {"p[0]",      std::function([&]() -> double { return *df.Mean("p[0]") - 0.5 * *df.StdDev("p[0]"); }),   std::function([&]() -> double { return *df.Mean("p[0]") + 0.5 * *df.StdDev("p[0]"); })  },
        // {"p[1]",      std::function([&]() -> double { return *df.Mean("p[1]") - 0.5 * *df.StdDev("p[1]"); }),   std::function([&]() -> double { return *df.Mean("p[1]") + 0.5 * *df.StdDev("p[1]"); })  },
        // {"p[2]",      std::function([&]() -> double { return *df.Mean("p[2]") - 0.5 * *df.StdDev("p[2]"); }),   std::function([&]() -> double { return *df.Mean("p[2]") + 0.5 * *df.StdDev("p[2]"); })  },
        // {"p0[0]",     std::function([&]() -> double { return *df.Mean("p0[0]") - 0.5 * *df.StdDev("p0[0]"); }), std::function([&]() -> double { return *df.Mean("p0[0]") + 0.5 * *df.StdDev("p0[0]"); })},
        // {"p0[1]",     std::function([&]() -> double { return *df.Mean("p0[1]") - 0.5 * *df.StdDev("p0[1]"); }), std::function([&]() -> double { return *df.Mean("p0[1]") + 0.5 * *df.StdDev("p0[1]"); })},
        // {"p0[2]",     std::function([&]() -> double { return *df.Mean("p0[2]") - 0.5 * *df.StdDev("p0[2]"); }), std::function([&]() -> double { return *df.Mean("p0[2]") + 0.5 * *df.StdDev("p0[2]"); })}
    };

    std::vector<ROOT::RDF::RResultPtr<TH1>> histList;
    std::ranges::transform(histParameterList, std::back_inserter(histList),
                           [&](auto&& parameter) -> ROOT::RDF::RResultPtr<TH1> {
                               auto&& [expression, xLow, xUp]{parameter};
                               constexpr auto Cast{[](std::any& any) -> double {
                                   if (const auto x{std::any_cast<ROOT::RDF::RResultPtr<double>>(&any)}) {
                                       return **x;
                                   } else if (const auto x{std::any_cast<double>(&any)}) {
                                       return *x;
                                   } else if (const auto x{std::any_cast<std::function<double()>>(&any)}) {
                                       return (*x)();
                                   }
                                   return 0;
                               }};
                               std::clog << "Hist: " << expression << std::endl;
                               auto xMin{Cast(xLow)};
                               auto xMax{Cast(xUp)};
                               auto margin{(xMax - xMin) / nBinsValueType};
                               return df.Histo1D({expression.data(), expression.data(), nBinsValueType, xMin - margin, xMax + margin}, expression);
                           });

    for (auto aHist : histList) {
        aHist->Write();
    }
    dstDir->Write();
    dstFile->Close();

    return 0;
}