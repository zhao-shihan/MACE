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
auto DataTupleName{"ECALSimHit"};

auto GetECALSimHit(auto moduleName, auto srcFileName, auto dstFileName) -> int {
    ROOT::RDataFrame df0{Form("G4Run0/%s", DataTupleName), srcFileName};
    const auto dstFile{new TFile(dstFileName, "UPDATE")};
    auto moduleDir{static_cast<TDirectory*>(dstFile->Get(moduleName))};
    if (!moduleDir) {
        std::clog << "DST File: Directory named " << moduleName << " is a new dir, create it." << std::endl;
        moduleDir = dstFile->mkdir(moduleName);
    }
    auto dstDir{moduleDir->mkdir(DataTupleName)};
    std::clog << "Getting " << DataTupleName << " from module: " << moduleName << std::endl;
    dstFile->cd();
    dstDir->cd();

    auto df{df0.Define("xx", "x[0]")
                .Define("yy", "x[1]")
                .Define("zz", "x[2]")
                .Define("px", "p[0]")
                .Define("py", "p[1]")
                .Define("pz", "p[2]")
                .Define("p0x", "p0[0]")
                .Define("p0y", "p0[1]")
                .Define("p0z", "p0[2]")};

    std::vector<std::tuple<std::string, std::any, std::any>> histParameterList{
        {"ModID", 0,                                                                                  540                                                                                   },
        {"xx",    df.Min("xx"),                                                                       df.Max("xx")                                                                          },
        {"yy",    df.Min("yy"),                                                                       df.Max("yy")                                                                          },
        {"zz",    df.Min("zz"),                                                                       df.Max("zz")                                                                          },
        {"t",     0,                                                                                  std::function([&]() -> double { return *df.Mean("t") + 3 * *df.StdDev("t"); })        },
        {"Edep",  0.,                                                                                 std::function([&]() -> double { return *df.Mean("Edep") + 0.5 * *df.StdDev("Edep"); })},
        {"Ek",    0.,                                                                                 std::function([&]() -> double { return *df.Mean("Ek") + 0.5 * *df.StdDev("Ek"); })    },
        {"TrkID", 0.,                                                                                 std::function([&]() -> double { return *df.Mean("TrkID") + 2 * *df.StdDev("TrkID"); })},
        {"t0",    0,                                                                                  std::function([&]() -> double { return *df.Mean("t0") + 3 * *df.StdDev("t0"); })      },
        {"Ek0",   0.,                                                                                 std::function([&]() -> double { return *df.Mean("Ek0") + 0.5 * *df.StdDev("Ek0"); })  },
        {"px",    std::function([&]() -> double { return *df.Mean("px") - 2 * *df.StdDev("px"); }),   std::function([&]() -> double { return *df.Mean("px") + 2 * *df.StdDev("px"); })      },
        {"py",    std::function([&]() -> double { return *df.Mean("py") - 2 * *df.StdDev("py"); }),   std::function([&]() -> double { return *df.Mean("py") + 2 * *df.StdDev("py"); })      },
        {"pz",    std::function([&]() -> double { return *df.Mean("pz") - 2 * *df.StdDev("pz"); }),   std::function([&]() -> double { return *df.Mean("pz") + 2 * *df.StdDev("pz"); })      },
        {"p0x",   std::function([&]() -> double { return *df.Mean("p0x") - 2 * *df.StdDev("p0x"); }), std::function([&]() -> double { return *df.Mean("p0x") + 2 * *df.StdDev("p0x"); })    },
        {"p0y",   std::function([&]() -> double { return *df.Mean("p0y") - 2 * *df.StdDev("p0y"); }), std::function([&]() -> double { return *df.Mean("p0y") + 2 * *df.StdDev("p0y"); })    },
        {"p0z",   std::function([&]() -> double { return *df.Mean("p0z") - 2 * *df.StdDev("p0z"); }), std::function([&]() -> double { return *df.Mean("p0z") + 2 * *df.StdDev("p0z"); })    },
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
                               return df.Histo1D({expression.data(), expression.data(), nBinsValueType, Cast(xLow), Cast(xUp)}, expression);
                           });

    for (auto aHist : histList) {
        aHist->Write();
    }
    dstDir->Write();
    dstFile->Close();

    return 0;
}