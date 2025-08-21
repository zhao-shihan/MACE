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
auto DataTupleName{"MCPSimHit"};

auto GetMCPSimHit(auto moduleName, auto srcFileName, auto dstFileName) -> int {
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
                .Define("x0x", "x0[0]")
                .Define("x0y", "x0[1]")
                .Define("x0z", "x0[2]")
                .Define("px", "p[0]")
                .Define("py", "p[1]")
                .Define("pz", "p[2]")
                .Define("p0x", "p0[0]")
                .Define("p0y", "p0[1]")
                .Define("p0z", "p0[2]")};

    std::vector<std::tuple<std::string, std::any, std::any>> histParameterList{
        {"TrkID", 0,                                                                                  20                                                                                  },
        {"xx",    df.Min("xx"),                                                                       df.Max("xx")                                                                        },
        {"yy",    df.Min("yy"),                                                                       df.Max("yy")                                                                        },
        // {"p0x",   df.Min("p0x"),                                                                      df.Max("p0x")                                                                       },
        // {"p0y",   df.Min("p0y"),                                                                      df.Max("p0y")                                                                       },
        // {"p0z",   df.Min("p0z"),                                                                      df.Max("p0z")                                                                       },
        // {"Ek0",   df.Min("Ek0"),                                                                      df.Max("Ek0")                                                                       },
        // {"Ek",    df.Min("Ek"),                                                                       df.Max("Ek")                                                                        },
        // {"Edep",  0.,                                                                                 std::function([&]() -> double { return *df.Mean("Edep") + 3 * *df.StdDev("Edep"); })},
        {"t",     0,                                                                                  std::function([&]() -> double { return *df.Mean("t") + 3 * *df.StdDev("t"); })      },
        {"t0",    0,                                                                                  std::function([&]() -> double { return *df.Mean("t0") + 3 * *df.StdDev("t0"); })    },
        {"px",    std::function([&]() -> double { return *df.Mean("px") - 3 * *df.StdDev("px"); }),   std::function([&]() -> double { return *df.Mean("px") + 3 * *df.StdDev("px"); })    },
        {"py",    std::function([&]() -> double { return *df.Mean("py") - 3 * *df.StdDev("py"); }),   std::function([&]() -> double { return *df.Mean("py") + 3 * *df.StdDev("py"); })    },
        {"pz",    std::function([&]() -> double { return *df.Mean("pz") - 3 * *df.StdDev("pz"); }),   std::function([&]() -> double { return *df.Mean("pz") + 3 * *df.StdDev("pz"); })    },
        {"p0x",   std::function([&]() -> double { return *df.Mean("p0x") - 3 * *df.StdDev("p0x"); }), std::function([&]() -> double { return *df.Mean("p0x") + 3 * *df.StdDev("p0x"); })  },
        {"p0y",   std::function([&]() -> double { return *df.Mean("p0y") - 3 * *df.StdDev("p0y"); }), std::function([&]() -> double { return *df.Mean("p0y") + 3 * *df.StdDev("p0y"); })  },
        {"p0z",   std::function([&]() -> double { return *df.Mean("p0z") - 3 * *df.StdDev("p0z"); }), std::function([&]() -> double { return *df.Mean("p0z") + 3 * *df.StdDev("p0z"); })  },
        {"x0x",   std::function([&]() -> double { return *df.Mean("x0x") - 2 * *df.StdDev("x0x"); }), std::function([&]() -> double { return *df.Mean("x0x") + 2 * *df.StdDev("x0x"); })  },
        {"x0y",   std::function([&]() -> double { return *df.Mean("x0y") - 2 * *df.StdDev("x0y"); }), std::function([&]() -> double { return *df.Mean("x0y") + 2 * *df.StdDev("x0y"); })  },
        {"x0z",   std::function([&]() -> double { return *df.Mean("x0z") - 2 * *df.StdDev("x0z"); }), std::function([&]() -> double { return *df.Mean("x0z") + 2 * *df.StdDev("x0z"); })  }
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