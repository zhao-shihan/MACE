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
                .Define("p0x", "p0[0]")
                .Define("p0y", "p0[1]")
                .Define("p0z", "p0[2]")};

    std::vector<std::tuple<std::string, std::any, std::any>> histParameterList{
        {"ModID", 0.,                                                                               640.                                                                                  },
        {"xx",    df.Min("xx"),                                                                     df.Max("xx")                                                                          },
        {"yy",    df.Min("yy"),                                                                     df.Max("yy")                                                                          },
        {"zz",    df.Min("zz"),                                                                     df.Max("zz")                                                                          },
        {"px",    df.Min("px"),                                                                     df.Max("px")                                                                          }, // for SimECAL
        {"py",    df.Min("py"),                                                                     df.Max("py")                                                                          }, // for SimECAL
        {"pz",    df.Min("pz"),                                                                     df.Max("pz")                                                                          }, // for SimECAL
        {"p0x",   df.Min("p0x"),                                                                    df.Max("p0x")                                                                         }, // for SimECAL
        {"p0y",   df.Min("p0y"),                                                                    df.Max("p0y")                                                                         }, // for SimECAL
        {"p0z",   df.Min("p0z"),                                                                    df.Max("p0z")                                                                         }, // for SimECAL
        {"t",     0.,                                                                               std::function([&]() -> double { return *df.Mean("t") + 3 * *df.StdDev("t"); })        },
        {"t0",    0.,                                                                               std::function([&]() -> double { return *df.Mean("t0") + 3 * *df.StdDev("t0"); })      },
        {"TrkID", 0.,                                                                               std::function([&]() -> double { return *df.Mean("TrkID") + 2 * *df.StdDev("TrkID"); })},
        {"Edep",  std::function([&]() -> double { return *df.Mean("Edep") - *df.StdDev("Edep"); }), std::function([&]() -> double { return *df.Mean("Edep") + *df.StdDev("Edep"); })      }, // for SimECAL
        {"Ek0",   std::function([&]() -> double { return *df.Mean("Ek0") - *df.StdDev("Ek0"); }),   std::function([&]() -> double { return *df.Mean("Ek0") + *df.StdDev("Ek0"); })        }, // for SimECAL
        {"Ek",    std::function([&]() -> double { return *df.Mean("Ek") - *df.StdDev("Ek"); }),     std::function([&]() -> double { return *df.Mean("Ek") + *df.StdDev("Ek"); })          }  // for SimECAL
        // {"Edep",  0.,                                                                                 std::function([&]() -> double { return *df.Mean("Edep") + 0.5 * *df.StdDev("Edep"); })},// for SimPhaseI
        // {"Ek0",   0.,                                                                                 std::function([&]() -> double { return *df.Mean("Ek0") + 0.5 * *df.StdDev("Ek0"); })  },// for SimPhaseI
        // {"Ek",    0.,                                                                                 std::function([&]() -> double { return *df.Mean("Ek") + 0.5 * *df.StdDev("Ek"); })    },// for SimPhaseI
        // {"px",    std::function([&]() -> double { return *df.Mean("px") - 2 * *df.StdDev("px"); }),   std::function([&]() -> double { return *df.Mean("px") + 2 * *df.StdDev("px"); })      },// for SimPhaseI
        // {"py",    std::function([&]() -> double { return *df.Mean("py") - 2 * *df.StdDev("py"); }),   std::function([&]() -> double { return *df.Mean("py") + 2 * *df.StdDev("py"); })      },// for SimPhaseI
        // {"pz",    std::function([&]() -> double { return *df.Mean("pz") - 2 * *df.StdDev("pz"); }),   std::function([&]() -> double { return *df.Mean("pz") + 2 * *df.StdDev("pz"); })      },// for SimPhaseI
        // {"p0x",   std::function([&]() -> double { return *df.Mean("p0x") - 2 * *df.StdDev("p0x"); }), std::function([&]() -> double { return *df.Mean("p0x") + 2 * *df.StdDev("p0x"); })    },// for SimPhaseI
        // {"p0y",   std::function([&]() -> double { return *df.Mean("p0y") - 2 * *df.StdDev("p0y"); }), std::function([&]() -> double { return *df.Mean("p0y") + 2 * *df.StdDev("p0y"); })    },// for SimPhaseI
        // {"p0z",   std::function([&]() -> double { return *df.Mean("p0z") - 2 * *df.StdDev("p0z"); }), std::function([&]() -> double { return *df.Mean("p0z") + 2 * *df.StdDev("p0z"); })    },// for SimPhaseI
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