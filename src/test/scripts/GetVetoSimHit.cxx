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

    auto df{df0.Define("xx", "x[0]")
                .Define("yy", "x[1]")
                .Define("zz", "x[2]")
                .Define("px", "p[0]")
                .Define("py", "p[1]")
                .Define("pz", "p[2]")
                .Define("x0x", "x0[0]")
                .Define("x0y", "x0[1]")
                .Define("x0z", "x0[2]")
                .Define("p0x", "p0[0]")
                .Define("p0y", "p0[1]")
                .Define("p0z", "p0[2]")};

    std::vector<std::tuple<std::string, std::any, std::any>> histParameterList{
        {"HitID",   0.,                                                                                   10.                                                                                 },
        {"StripID", 0.,                                                                                   200.                                                                                },
        // {"x0x",     -2100.,                                                                               2100.                                                                               },
        // {"x0y",     -2100.,                                                                               2100.                                                                               },
        // {"x0z",     -2100.,                                                                               2100.                                                                               },
        // {"Ek",      0.,                                                                                   std::function([&]() -> double { return *df.Mean("Ek") + 0.5 * *df.StdDev("Ek"); })    },
        // {"Ek0",     0.,                                                                                   std::function([&]() -> double { return *df.Mean("Ek0") + 0.5 * *df.StdDev("Ek0"); })  },
        {"Edep",    0.,                                                                                   std::function([&]() -> double { return *df.Mean("Edep") + 2 * *df.StdDev("Edep"); })},
        {"xx",      std::function([&]() -> double { return *df.Mean("xx") - 0.5 * *df.StdDev("xx"); }),   std::function([&]() -> double { return *df.Mean("xx") + 0.5 * *df.StdDev("xx"); })  },
        {"yy",      std::function([&]() -> double { return *df.Mean("yy") - 0.5 * *df.StdDev("yy"); }),   std::function([&]() -> double { return *df.Mean("yy") + 0.5 * *df.StdDev("yy"); })  },
        {"zz",      std::function([&]() -> double { return *df.Mean("zz") - 0.5 * *df.StdDev("zz"); }),   std::function([&]() -> double { return *df.Mean("zz") + 0.5 * *df.StdDev("zz"); })  },
        // {"px",      std::function([&]() -> double { return *df.Mean("px") - 0.5 * *df.StdDev("px"); }),   std::function([&]() -> double { return *df.Mean("px") + 0.5 * *df.StdDev("px"); })  },
        // {"py",      std::function([&]() -> double { return *df.Mean("py") - 0.5 * *df.StdDev("py"); }),   std::function([&]() -> double { return *df.Mean("py") + 0.5 * *df.StdDev("py"); })  },
        // {"pz",      std::function([&]() -> double { return *df.Mean("pz") - 0.5 * *df.StdDev("pz"); }),   std::function([&]() -> double { return *df.Mean("pz") + 0.5 * *df.StdDev("pz"); })  },
        // {"p0x",     std::function([&]() -> double { return *df.Mean("p0x") - 0.5 * *df.StdDev("p0x"); }), std::function([&]() -> double { return *df.Mean("p0x") + 0.5 * *df.StdDev("p0x"); })},
        // {"p0y",     std::function([&]() -> double { return *df.Mean("p0y") - 0.5 * *df.StdDev("p0y"); }), std::function([&]() -> double { return *df.Mean("p0y") + 0.5 * *df.StdDev("p0y"); })},
        // {"p0z",     std::function([&]() -> double { return *df.Mean("p0z") - 0.5 * *df.StdDev("p0z"); }), std::function([&]() -> double { return *df.Mean("p0z") + 0.5 * *df.StdDev("p0z"); })}
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