// #include "MACE/ReconCDCTrack/Finder/MCTruthFinder.h++"
// #include "MACE/ReconCDCTrack/Fitter/MCTruthFitter.h++"

#include "MACE/Compatibility/std2b/constexpr_abs.h++"
#include "MACE/DataModel/DataFactory.h++"
#include "MACE/DataModel/SimHit/CDCSimHit.h++"
#include "MACE/DataModel/SimHit/EMCalSimHit.h++"
#include "MACE/DataModel/SimHit/MCPSimHit.h++"
#include "MACE/DataModel/SimTrack/CDCPhysicsSimTrack.h++"
#include "MACE/DataModel/Track/CDCHelixTrack.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Detector/Geometry/Fast/AcceleratorField.h++"
#include "MACE/Detector/Geometry/Fast/BeamDegrader.h++"
#include "MACE/Detector/Geometry/Fast/BeamMonitor.h++"
#include "MACE/Detector/Geometry/Fast/CDCBody.h++"
#include "MACE/Detector/Geometry/Fast/CDCFieldWire.h++"
#include "MACE/Detector/Geometry/Fast/CDCGas.h++"
#include "MACE/Detector/Geometry/Fast/CDCSenseLayer.h++"
#include "MACE/Detector/Geometry/Fast/CDCSuperLayer.h++"
#include "MACE/Detector/Geometry/Fast/SpectrometerField.h++"
#include "MACE/Detector/Geometry/Fast/Target.h++"
#include "MACE/Detector/Geometry/Fast/World.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/Env/CLI/BasicCLI.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Extension/stdx/to_signed.h++"
#include "MACE/Math/Hypot.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Math/Norm.h++"
#include "MACE/Math/Random/Distribution/Gaussian.h++"
#include "MACE/Math/Random/Distribution/Gaussian3DDiagnoal.h++"
#include "MACE/Math/Random/Generator/Xoshiro512SS.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/PhysicalConstant.h++"
#include "MACE/Utility/VectorArithmeticOperator.h++"
#include "MACE/Utility/VectorCast.h++"

#include "ROOT/RDataFrame.hxx"
#include "TDatabasePDG.h"
#include "TEveManager.h"
#include "TGeoManager.h"
#include "TGeoMaterialInterface.h"
#include "TList.h"
#include "TMath.h"
#include "TVector3.h"

#include "G4NistManager.hh"

#include "Eigen/Core"

#include "gsl/gsl"
#include "TNtuple.h"

#include "fmt/format.h"

#include "ConstField.h"
#include "EventDisplay.h"
#include "Exception.h"
#include "FieldManager.h"
#include "KalmanFitStatus.h"
#include "KalmanFitterRefTrack.h"
#include "MaterialEffects.h"
#include "RKTrackRep.h"
#include "StateOnPlane.h"
#include "Track.h"
#include "TrackPoint.h"
#include "WireMeasurement.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <filesystem>
#include <memory>
#include <ranges>
#include <tuple>
#include <utility>
#include <vector>

using namespace MACE;
using namespace LiteralUnit;
using namespace PhysicalConstant;

// rng
Math::Random::Xoshiro512SS rng;
Math::Random::Gaussian Gaussian1D;
Math::Random::Gaussian3DDiagnoal Gaussian3D;

void MakeMACECDCGeometry() {
    using namespace Detector::Geometry::Fast;

    constexpr auto fCheckOverlap = false;

    //
    // Geometry
    //

    // 0

    const auto world = std::make_unique_for_overwrite<World>();

    // 1

    auto& spectrometerField = world->NewDaughter<SpectrometerField>(fCheckOverlap);

    // 2

    auto& cdcBody = spectrometerField.NewDaughter<CDCBody>(fCheckOverlap);
    auto& acceleratorField = spectrometerField.NewDaughter<AcceleratorField>(fCheckOverlap);

    // 3

    auto& cdcGas = cdcBody.NewDaughter<CDCGas>(fCheckOverlap);

    auto& beamDegrader = acceleratorField.NewDaughter<BeamDegrader>(fCheckOverlap);
    auto& beamMonitor = acceleratorField.NewDaughter<BeamMonitor>(fCheckOverlap);
    auto& target = acceleratorField.NewDaughter<Target>(fCheckOverlap);

    // 4

    auto& cdcSuperLayer = cdcGas.NewDaughter<CDCSuperLayer>(fCheckOverlap);

    // 5

    auto& cdcSenseLayer = cdcSuperLayer.NewDaughter<CDCSenseLayer>(fCheckOverlap);

    // 6

    auto& cdcFieldWire = cdcSenseLayer.NewDaughter<CDCFieldWire>(fCheckOverlap);

    //
    // Material
    //

    using namespace LiteralUnit::Density;

    const auto nist = G4NistManager::Instance();

    const auto aluminium = nist->FindOrBuildMaterial("G4_Al");
    beamDegrader.RegisterMaterial(aluminium);
    cdcFieldWire.RegisterMaterial(aluminium);

    const auto cdcHeBasedGas = [&nist] {
        constexpr auto heFraction = 0.85;
        constexpr auto butaneFraction = 1 - heFraction;
        const auto he = nist->FindOrBuildMaterial("G4_He");
        const auto butane = nist->FindOrBuildMaterial("G4_BUTANE");
        const auto gas = new G4Material("CDCGas",
                                        heFraction * he->GetDensity() +
                                            butaneFraction * butane->GetDensity(),
                                        2,
                                        kStateGas);
        gas->AddMaterial(he, heFraction);
        gas->AddMaterial(butane, butaneFraction);
        return gas;
    }();
    cdcGas.RegisterMaterial(cdcHeBasedGas);
    cdcSenseLayer.RegisterMaterial(cdcHeBasedGas);
    cdcSuperLayer.RegisterMaterial(cdcHeBasedGas);

    const auto cdcShell = nist->BuildMaterialWithNewDensity("CarbonFiber", "G4_C", 1.7_g_cm3);
    cdcBody.RegisterMaterial(cdcShell);

    const auto plasticScitillator = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    beamMonitor.RegisterMaterial(plasticScitillator);

    const auto silicaAerogel = nist->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", 30_mg_cm3);
    target.RegisterMaterial(silicaAerogel);

    const auto vacuum = nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3);
    acceleratorField.RegisterMaterial(vacuum);
    spectrometerField.RegisterMaterial(vacuum);
    world->RegisterMaterial(vacuum);

    const auto tempGDMLFile = (std::filesystem::temp_directory_path() / "MACECDCGeometry.gdml").generic_string();
    world->Export(tempGDMLFile);

    //
    // Export to root
    //

    using namespace LiteralUnit::MagneticFluxDensity;

    new TGeoManager("MACECDC", "MACE CDC Geometry");
    gGeoManager->Import(tempGDMLFile.c_str());
    gGeoManager->GetTopVolume()->SetInvisible();
    genfit::MaterialEffects::getInstance()->init(new genfit::TGeoMaterialInterface);
    genfit::FieldManager::getInstance()->init(new genfit::ConstField(0, 0, Detector::Description::SpectrometerField::Instance().MagneticFluxDensity() / 0.1_T));
}

auto FitTrack(std::vector<std::shared_ptr<DataModel::CDCSimHit>> hitData) -> std::pair<std::vector<std::shared_ptr<DataModel::CDCPhysicsSimTrack>>,
                                                                                       std::vector<std::shared_ptr<DataModel::CDCHelixTrack>>> {
    if (hitData.empty()) {
        return {};
    }

    // find track
    std::ranges::sort(hitData,
                      [](const auto& hit1, const auto& hit2) {
                          return std::tie(hit1->MCEventID().Value(), hit1->MCTrackID().Value(), hit1->CellID().Value()) <
                                 std::tie(hit2->MCEventID().Value(), hit2->MCTrackID().Value(), hit2->CellID().Value());
                      });

    std::vector<std::vector<std::shared_ptr<DataModel::CDCSimHit>>> rawTrackData;
    {
        std::vector<std::shared_ptr<DataModel::CDCSimHit>> rawTrack;
        for (std::tuple currentTrackID = {hitData.front()->MCEventID().Value(), hitData.front()->MCTrackID().Value()};
             auto&& hit : std::as_const(hitData)) {
            if (const auto newTrackID = std::tie(hit->MCEventID().Value(), hit->MCTrackID().Value());
                newTrackID != currentTrackID) {
                if (rawTrack.size() >= 7) {
                    rawTrackData.emplace_back(rawTrack);
                }
                rawTrack.clear();
                currentTrackID = newTrackID;
            }
            if (hit->VertexKineticEnergy().Value() > 5_MeV) {
                rawTrack.emplace_back(hit);
            }
        }
        if (rawTrack.size() >= 7) {
            rawTrackData.emplace_back(rawTrack);
        }
    }
    if (rawTrackData.empty()) {
        return {};
    }

    // // event display
    // const auto display = genfit::EventDisplay::getInstance();

    // fitter
    genfit::KalmanFitterRefTrack fitter;

    // generate momentum seed by smearing true value
    const auto MomentumSeed = [&](stdx::array3d p) {
        constexpr auto resolution = 0.2;
        const auto sigma = resolution * Math::Norm(p) / 2.355; // clang-format off
        p += Gaussian3D(rng, {{0., sigma}, {0., sigma}, {0., sigma}}); // clang-format on
        TVector3 pSeed(p[0], p[1], p[2]);
        return pSeed * 0.001;
    };

    // fit data
    std::vector<genfit::Track> genfitTrackData;
    std::vector<std::shared_ptr<DataModel::CDCPhysicsSimTrack>> fitTrackData;
    std::vector<std::shared_ptr<DataModel::CDCHelixTrack>> fitHelixTrackData;

    // do Kalman fit
    const auto cdcCellMap = Detector::Description::CDC::Instance().CellMap();
    for (auto&& rawTrack : rawTrackData) {
        const auto& firstHit = rawTrack.front();

        // do the fit
        const auto trackRep = new genfit::RKTrackRep(firstHit->PDGCode().Value());
        auto& genfitTrack = genfitTrackData.emplace_back(trackRep, TVector3(0, 0, 0), MomentumSeed(firstHit->VertexMomentum().Value()));
        for (auto hitID = 0;
             auto&& hit : rawTrack) {
            const auto cellID = hit->CellID().Value();
            const auto cellHit = cdcCellMap[cellID];
            const Eigen::Vector3d wirePosition3D = {cellHit.position.x(), cellHit.position.y(), 0};
            const Eigen::Vector3d endPoint1 = (wirePosition3D - 1000 * cellHit.direction) / 10;
            const Eigen::Vector3d endPoint2 = (wirePosition3D + 1000 * cellHit.direction) / 10;
            const auto driftInROOTUnit = std::abs(Gaussian1D(rng, {hit->DriftDistance().Value(), 100_um / 2.355})) / 10;

            TVectorD rawHitCoords(7);
            rawHitCoords[0] = endPoint1.x();
            rawHitCoords[1] = endPoint1.y();
            rawHitCoords[2] = endPoint1.z();
            rawHitCoords[3] = endPoint2.x();
            rawHitCoords[4] = endPoint2.y();
            rawHitCoords[5] = endPoint2.z();
            rawHitCoords[6] = driftInROOTUnit;

            TMatrixDSym rawHitCov(7);
            rawHitCov[0][0] = 0;
            rawHitCov[0][1] = 0;
            rawHitCov[0][2] = 0;
            rawHitCov[0][3] = 0;
            rawHitCov[0][4] = 0;
            rawHitCov[0][5] = 0;
            rawHitCov[0][6] = 0;
            rawHitCov[1][0] = 0;
            rawHitCov[1][1] = 0;
            rawHitCov[1][2] = 0;
            rawHitCov[1][3] = 0;
            rawHitCov[1][4] = 0;
            rawHitCov[1][5] = 0;
            rawHitCov[1][6] = 0;
            rawHitCov[2][0] = 0;
            rawHitCov[2][1] = 0;
            rawHitCov[2][2] = 0;
            rawHitCov[2][3] = 0;
            rawHitCov[2][4] = 0;
            rawHitCov[2][5] = 0;
            rawHitCov[2][6] = 0;
            rawHitCov[3][0] = 0;
            rawHitCov[3][1] = 0;
            rawHitCov[3][2] = 0;
            rawHitCov[3][3] = 0;
            rawHitCov[3][4] = 0;
            rawHitCov[3][5] = 0;
            rawHitCov[3][6] = 0;
            rawHitCov[4][0] = 0;
            rawHitCov[4][1] = 0;
            rawHitCov[4][2] = 0;
            rawHitCov[4][3] = 0;
            rawHitCov[4][4] = 0;
            rawHitCov[4][5] = 0;
            rawHitCov[4][6] = 0;
            rawHitCov[5][0] = 0;
            rawHitCov[5][1] = 0;
            rawHitCov[5][2] = 0;
            rawHitCov[5][3] = 0;
            rawHitCov[5][4] = 0;
            rawHitCov[5][5] = 0;
            rawHitCov[5][6] = 0;
            rawHitCov[6][0] = 0;
            rawHitCov[6][1] = 0;
            rawHitCov[6][2] = 0;
            rawHitCov[6][3] = 0;
            rawHitCov[6][4] = 0;
            rawHitCov[6][5] = 0;
            rawHitCov[6][6] = Math::Pow2(100_um / 2.355 / 10);

            const auto wireMeasurement = new genfit::WireMeasurement(rawHitCoords,
                                                                     rawHitCov,
                                                                     cellID,
                                                                     hitID++,
                                                                     nullptr);
            genfitTrack.insertPoint(new genfit::TrackPoint(wireMeasurement, &genfitTrack));
        }

        genfitTrack.checkConsistency();
        try {
            fitter.processTrack(&genfitTrack);
            genfitTrack.getFittedState() /* .Print() */;
        } catch (const genfit::Exception&) {
            continue;
        }
        genfitTrack.checkConsistency();
        // display->addEvent(&genfitTrack);

        // analysis

        static const auto cdcInnerRadius = Detector::Description::CDC::Instance().GasInnerRadius();
        const auto& state = genfitTrack.getFittedState();
        const auto& fitStatus = *genfitTrack.getKalmanFitStatus();
        const auto& fitTrack = fitTrackData.emplace_back(std::make_shared_for_overwrite<DataModel::CDCPhysicsSimTrack>());
        const auto& fitHelixTrack = fitHelixTrackData.emplace_back(std::make_shared_for_overwrite<DataModel::CDCHelixTrack>());
        const auto tVertex = firstHit->Time().Value() - cdcInnerRadius / c_light;
        const auto xFirst = state.getPos() * 10;
        const auto pFirst = state.getMom() * 1000;
        const auto mass = state.getMass() * 1000;
        const auto charge = state.getCharge();
        const auto kineticEnergy = std::sqrt(pFirst.Mag2() + Math::Pow2(mass)) - mass;

        static const auto bField = Detector::Description::SpectrometerField::Instance().MagneticFluxDensity();
        const auto pT = Math::Hypot(pFirst.x(), pFirst.y());
        const auto radius = pT / (/* charge * */ bField * c_light);
        const Eigen::Vector2d center = {xFirst.x() - radius * (pFirst.y() / pT), xFirst.y() - radius * (-pFirst.x() / pT)};
        const auto theta = std::atan2(pT, pFirst.z());
        const auto vertexZ = xFirst.z() - radius *
                                              [&center, x = xFirst.x(), y = xFirst.y()] {
                                                  const Eigen::Vector2d local = {x - center.x(), y - center.y()};
                                                  return std::acos((center.x() * local.y() - local.x() * center.y()) / std::sqrt(center.squaredNorm() * local.squaredNorm()));
                                              }() /
                                              std::tan(theta);

        // vertexing

        // state.getPos()

        // save fitted track

        fitTrack->Chi2().Value(fitStatus.getChi2());
        fitTrack->PDGCode().Value(state.getPDG());
        fitTrack->NHit().Value(genfitTrack.getNumPoints());
        fitTrack->VertexTime().Value(tVertex);
        fitTrack->VertexPosition().Value({});
        fitTrack->VertexKineticEnergy().Value(kineticEnergy);
        fitTrack->VertexMomentum().Value({pFirst.x(), pFirst.y(), pFirst.z()});

        fitTrack->PDGCodeTruth().Value(firstHit->PDGCode().Value());
        fitTrack->NHitTruth().Value(rawTrack.size());
        fitTrack->VertexTimeTruth().Value(firstHit->VertexTime().Value());
        fitTrack->VertexPositionTruth().Value(firstHit->VertexPosition().Value());
        fitTrack->VertexKineticEnergyTruth().Value(firstHit->VertexKineticEnergy().Value());
        fitTrack->VertexMomentumTruth().Value(firstHit->VertexMomentum().Value());

        fitHelixTrack->Chi2().Value(fitStatus.getChi2());
        fitHelixTrack->PDGCode().Value(state.getPDG());
        fitHelixTrack->NHit().Value(genfitTrack.getNumPoints());
        fitHelixTrack->VertexTime().Value(tVertex);
        fitHelixTrack->Center().Value(center);
        fitHelixTrack->Radius().Value(radius);
        fitHelixTrack->VertexZ().Value(vertexZ);
        fitHelixTrack->Theta().Value(theta);
    }

    // const auto outFile = std::make_unique<TFile>(argv[2], "RECREATE");
    // dataFactory.CreateAndFillTree<DataModel::CDCPhysicsSimTrack>(fitTrackData, 0)->Write();

    // // open event display
    // display->open();
    return {fitTrackData, fitHelixTrackData};
}

int main(int argc, char* argv[]) {
    Env::BasicEnv env(argc, argv, {});

    // init geometry and mag. field
    MakeMACECDCGeometry();

    // hit data
    MACE::DataModel::DataFactory dataFactory;
    dataFactory.TreeNamePrefixFormat("G4Run{}_");

    const auto sigFile = std::make_unique<TFile>(argv[1]);
    decltype(auto) cdcHitSigTree = *dataFactory.FindTree<DataModel::CDCSimHit>(*sigFile, 0);
    decltype(auto) mcpHitSigTree = *dataFactory.FindTree<DataModel::MCPSimHit>(*sigFile, 0);
    decltype(auto) emCalHitSigTree = *dataFactory.FindTree<DataModel::EMCalSimHit>(*sigFile, 0);

    const auto bkgFile = std::make_unique<TFile>(argv[2]);
    decltype(auto) cdcHitBkgTree = *dataFactory.FindTree<DataModel::CDCSimHit>(*bkgFile, 0);
    decltype(auto) mcpHitBkgTree = *dataFactory.FindTree<DataModel::MCPSimHit>(*bkgFile, 0);
    decltype(auto) emCalHitBkgTree = *dataFactory.FindTree<DataModel::EMCalSimHit>(*bkgFile, 0);

    auto cdcHitSigDataAll = dataFactory.CreateAndFillList<DataModel::CDCSimHit>(cdcHitSigTree);
    auto mcpHitSigDataAll = dataFactory.CreateAndFillList<DataModel::MCPSimHit>(mcpHitSigTree);
    auto emCalHitSigDataAll = dataFactory.CreateAndFillList<DataModel::EMCalSimHit>(emCalHitSigTree);
    auto cdcHitBkgDataAll = dataFactory.CreateAndFillList<DataModel::CDCSimHit>(cdcHitBkgTree);
    auto mcpHitBkgDataAll = dataFactory.CreateAndFillList<DataModel::MCPSimHit>(mcpHitBkgTree);
    auto emCalHitBkgDataAll = dataFactory.CreateAndFillList<DataModel::EMCalSimHit>(emCalHitBkgTree);

    constexpr auto EventIDCompare =
        [](const auto& hit1, const auto& hit2) {
            return hit1->MCEventID().Value() < hit2->MCEventID().Value();
        };
    std::ranges::sort(cdcHitSigDataAll, EventIDCompare);
    std::ranges::sort(mcpHitSigDataAll, EventIDCompare);
    std::ranges::sort(emCalHitSigDataAll, EventIDCompare);
    std::ranges::sort(cdcHitBkgDataAll, EventIDCompare);
    std::ranges::sort(mcpHitBkgDataAll, EventIDCompare);
    std::ranges::sort(emCalHitBkgDataAll, EventIDCompare);

    constexpr auto SplitByEventID =
        [](const auto& data, const auto maxID) {
            std::vector<std::decay_t<decltype(data)>> splitData(maxID + 1);
            auto hitBegin = data.cbegin();
            while (hitBegin != data.cend()) {
                const auto currentID = (*hitBegin)->MCEventID().Value();
                const auto hitEnd = std::ranges::find_if_not(hitBegin, data.cend(),
                                                             [&hitBegin, &currentID](const auto& hit) {
                                                                 return hit->MCEventID().Value() == currentID;
                                                             });
                splitData[currentID] = {hitBegin, hitEnd};
                hitBegin = hitEnd;
            }
            splitData.shrink_to_fit();
            return splitData;
        };
    const auto maxSigID = std::max({(*std::ranges::max_element(cdcHitSigDataAll, EventIDCompare))->MCEventID().Value(),
                                    (*std::ranges::max_element(mcpHitSigDataAll, EventIDCompare))->MCEventID().Value(),
                                    (*std::ranges::max_element(emCalHitSigDataAll, EventIDCompare))->MCEventID().Value()});
    const auto maxBkgID = std::max({(*std::ranges::max_element(cdcHitBkgDataAll, EventIDCompare))->MCEventID().Value(),
                                    (*std::ranges::max_element(mcpHitBkgDataAll, EventIDCompare))->MCEventID().Value(),
                                    (*std::ranges::max_element(emCalHitBkgDataAll, EventIDCompare))->MCEventID().Value()});
    const auto cdcHitSigData = SplitByEventID(cdcHitSigDataAll, maxSigID);
    const auto mcpHitSigData = SplitByEventID(mcpHitSigDataAll, maxSigID);
    const auto emCalHitSigData = SplitByEventID(emCalHitSigDataAll, maxSigID);
    const auto cdcHitBkgData = SplitByEventID(cdcHitBkgDataAll, maxBkgID);
    const auto mcpHitBkgData = SplitByEventID(mcpHitBkgDataAll, maxBkgID);
    const auto emCalHitBkgData = SplitByEventID(emCalHitBkgDataAll, maxBkgID);

    auto eventID = 0;
    TFile coincidentDataFile("coincident_data.root", "RECREATE");
    TNtuple dcaTOFData("dcatof", "DCA and TOF", "dca:tof");

    for (gsl::index sigID = 0; sigID < maxSigID; ++sigID) {
        const auto bkgID = sigID % maxBkgID;
        const auto& cdcHitSig = cdcHitSigData[sigID];
        const auto& mcpHitSig = mcpHitSigData[sigID];
        const auto& emCalHitSig = emCalHitSigData[sigID];
        const auto& cdcHitBkg = cdcHitBkgData[bkgID];
        const auto& mcpHitBkg = mcpHitBkgData[bkgID];
        const auto& emCalHitBkg = emCalHitBkgData[bkgID];

        for (auto&& mcpHit : mcpHitSig) {
            const auto& tMCP = mcpHit->Time().Value();
            const auto& xMCP = mcpHit->Position().Value();

            //
            // MCP <-> EMCal
            //

            auto nGamma = 0;
            const auto EMCalSmearFilter =
                [&](const auto& emCalHit) {
                    const auto tEMCal = Gaussian1D(rng, {emCalHit->Time().Value(), 4.5_ns / 2.355});
                    const auto energy = Gaussian1D(rng, {emCalHit->EnergyDeposition().Value(), 350_keV / 2.355});
                    if (tMCP + 0.5_ns - 6_ns < tEMCal and tEMCal < tMCP + 0.5_ns + 6_ns and
                        200_keV < energy and energy < 1000_keV) {
                        ++nGamma;
                    }
                };
            std::ranges::for_each(emCalHitSig, EMCalSmearFilter);
            // std::ranges::for_each(emCalHitBkg, EMCalSmearFilter);
            if (nGamma < 2) {
                continue;
            }

            //
            // MCP <-> CDC
            //

            const auto CDCHitSmearFilter =
                [&](const auto& cdcHitData) {
                    std::vector<typename std::decay_t<decltype(cdcHitData)>::value_type> coincidentHitList;
                    for (auto&& cdcHit : cdcHitData) {
                        const auto tCDC = Gaussian1D(rng, {cdcHit->Time().Value(), 2_ns / 2.355});
                        const auto deltaT = tMCP - tCDC;
                        if (118.6_ns + 0.5_ns < deltaT and deltaT < 124.9_ns + 3.5_ns) {
                            coincidentHitList.emplace_back(cdcHit);
                        }
                    }
                    return coincidentHitList;
                };
            const auto coincidentCDCHitSig = CDCHitSmearFilter(cdcHitSig);
            // const auto coincidentCDCHitBkg = CDCHitSmearFilter(cdcHitBkg);
            if (coincidentCDCHitSig.size() < 7 /* and coincidentCDCHitBkg.size() < 7 */) {
                continue;
            }

            auto [coincidentCDCTrackData, coincidentCDCHelixData] = FitTrack(coincidentCDCHitSig);
            // const auto [coincidentCDCTrackBkgData, coincidentCDCHelixBkgData] = FitTrack(coincidentCDCHitBkg);
            // coincidentCDCTrackData.insert(coincidentCDCTrackData.cend(), coincidentCDCTrackBkgData.cbegin(), coincidentCDCTrackBkgData.cend());
            // coincidentCDCHelixData.insert(coincidentCDCHelixData.cend(), coincidentCDCHelixBkgData.cbegin(), coincidentCDCHelixBkgData.cend());
            if (coincidentCDCTrackData.empty()) {
                continue;
            }

            /* dataFactory.TreeNamePrefixFormat("Eve{}_");
            dataFactory.CreateAndFillTree<DataModel::CDCPhysicsSimTrack>(coincidentCDCTrackData, eventID)->Write();
            dataFactory.CreateAndFillTree<DataModel::CDCHelixTrack>(coincidentCDCHelixData, eventID)->Write(); */

            std::vector<std::pair<double, double>> dcaTOF;
            for (auto&& helix : std::as_const(coincidentCDCHelixData)) {
                const auto dca = Math::Norm(helix->Center().Value() - xMCP) - helix->Radius().Value();
                const auto tof = tMCP - helix->VertexTime().Value();
                dcaTOFData.Fill(dca, tof);
            }

            ++eventID;
        }
    }

    dcaTOFData.Write();

    /* constexpr auto cdcCoincidentDataFileName = "cdc_coincident_data.root";
    std::make_unique<TFile>(cdcCoincidentDataFileName, "RECREATE");

    auto eventID = 0;
    const auto ProcessEvent =
        [&](const double tMCP, const ROOT::RVecF& xMCPRVec, const int sigEventID) {
            ROOT::RDataFrame cdcHitSigDFAll(cdcHitSigTree);
            ROOT::RDataFrame emCalHitSigDFAll(emCalHitSigTree);
            const auto SigFilter = [&sigEventID](const int id) { return id == sigEventID; };
            auto cdcHitSigDF = cdcHitSigDFAll.Filter(SigFilter, {DataModel::CDCSimHit::Column::MCEventID::Name()});
            auto emCalHitSigDF = emCalHitSigDFAll.Filter(SigFilter, {DataModel::EMCalSimHit::Column::MCEventID::Name()});

            ROOT::RDataFrame cdcHitBkgDFAll(cdcHitBkgTree);
            ROOT::RDataFrame emCalHitBkgDFAll(emCalHitBkgTree);
            const auto BkgFilter = [&eventID](const int id) { return id == eventID % 10; };
            auto cdcHitBkgDF = cdcHitBkgDFAll.Filter(BkgFilter, {DataModel::CDCSimHit::Column::MCEventID::Name()});
            auto emCalHitBkgDF = emCalHitBkgDFAll.Filter(BkgFilter, {DataModel::EMCalSimHit::Column::MCEventID::Name()});

            //
            // MCP <-> EMCal
            //

            const auto EMCalSmearFilter =
                [&](double tEMCal, float energy) {
                    tEMCal = Gaussian1D(rng, {tEMCal, 4.5_ns / 2.355});
                    energy = Gaussian1D(rng, {energy, 350_keV / 2.355});
                    return tMCP + 0.5_ns - 6_ns < tEMCal and tEMCal < tMCP + 0.5_ns + 6_ns and
                           200_keV < energy and energy < 1000_keV;
                };
            const auto nGamma = *emCalHitSigDF.Filter(EMCalSmearFilter,
                                                      {DataModel::EMCalHit::Column::Time::Name(),
                                                       DataModel::EMCalHit::Column::EnergyDeposition::Name()})
                                     .Count() +
                                *emCalHitBkgDF.Filter(EMCalSmearFilter,
                                                      {DataModel::EMCalHit::Column::Time::Name(),
                                                       DataModel::EMCalHit::Column::EnergyDeposition::Name()})
                                     .Count();
            if (nGamma < 2) {
                return;
            }

            //
            // MCP <-> CDC
            //

            const auto CDCHitSmearFilter =
                [&](double tCDC) {
                    tCDC = Gaussian1D(rng, {tCDC, 2_ns / 2.355});
                    const auto deltaT = tMCP - tCDC;
                    return 118.6_ns + 0.5_ns < deltaT and deltaT < 124.9_ns + 3.5_ns;
                };
            auto coincidentCDCHitSigDF = cdcHitSigDF.Filter(CDCHitSmearFilter, {DataModel::CDCHit::Column::Time::Name()});
            auto coincidentCDCHitBkgDF = cdcHitBkgDF.Filter(CDCHitSmearFilter, {DataModel::CDCHit::Column::Time::Name()});
            if (*coincidentCDCHitSigDF.Count() < 7 and *coincidentCDCHitBkgDF.Count() < 7) {
                return;
            }

            const auto coincidentCDCHitSigTreeName = fmt::format("Eve{}_Sig_CDCSimHit", eventID);
            const auto coincidentCDCHitBkgTreeName = fmt::format("Eve{}_Bkg_CDCSimHit", eventID);
            const auto tempCDCCoincidentDataFileName = (std::filesystem::temp_directory_path() / cdcCoincidentDataFileName).generic_string();

            ROOT::RDF::RSnapshotOptions cdcHitSnapshotOptions;
            cdcHitSnapshotOptions.fMode = "UPDATE";
            cdcHitSnapshotOptions.fCompressionAlgorithm = ROOT::ECompressionAlgorithm::kZSTD;
            cdcHitSnapshotOptions.fCompressionLevel = ROOT::RCompressionSetting::ELevel::kDefaultZSTD;
            cdcHitSnapshotOptions.fOverwriteIfExists = true;
            coincidentCDCHitSigDF.Snapshot(coincidentCDCHitSigTreeName, tempCDCCoincidentDataFileName, "", cdcHitSnapshotOptions);
            coincidentCDCHitBkgDF.Snapshot(coincidentCDCHitBkgTreeName, tempCDCCoincidentDataFileName, "", cdcHitSnapshotOptions);

            TFile tempCDCCoincidentDataFile(tempCDCCoincidentDataFileName.c_str());
            dataFactory.TreeNamePrefixFormat("Eve{}_Sig_");
            const auto coincidentCDCHitSigData = dataFactory.CreateAndFillList<DataModel::CDCSimHit>(*tempCDCCoincidentDataFile.Get<TTree>(coincidentCDCHitSigTreeName.c_str()), eventID);
            auto [coincidentCDCTrackData, coincidentCDCHelixData] = FitTrack(coincidentCDCHitSigData);
            dataFactory.TreeNamePrefixFormat("Eve{}_Bkg_");
            const auto coincidentCDCHitBkgData = dataFactory.CreateAndFillList<DataModel::CDCSimHit>(*tempCDCCoincidentDataFile.Get<TTree>(coincidentCDCHitBkgTreeName.c_str()), eventID);
            const auto [coincidentCDCTrackBkgData, coincidentCDCHelixBkgData] = FitTrack(coincidentCDCHitBkgData);
            coincidentCDCTrackData.insert(coincidentCDCTrackData.cend(), coincidentCDCTrackBkgData.cbegin(), coincidentCDCTrackBkgData.cend());
            if (coincidentCDCTrackData.empty()) {
                return;
            }
            coincidentCDCHelixData.insert(coincidentCDCHelixData.cend(), coincidentCDCHelixBkgData.cbegin(), coincidentCDCHelixBkgData.cend());

            dataFactory.TreeNamePrefixFormat("Eve{}_");
            TFile cdcCoincidentDataFile(cdcCoincidentDataFileName, "UPDATE");
            dataFactory.CreateAndFillTree<DataModel::CDCPhysicsSimTrack>(coincidentCDCTrackData, eventID)->Write();
            dataFactory.CreateAndFillTree<DataModel::CDCHelixTrack>(coincidentCDCHelixData, eventID)->Write();

            const auto xMCP = VectorCast<stdx::array2d>(xMCPRVec);
            std::vector<std::pair<double, double>> dcaTOF;
            for (auto&& helix : std::as_const(coincidentCDCHelixData)) {
                const auto dca = std2b::abs(Math::Norm(helix->Center().Value() - xMCP) - helix->Radius().Value());
                std::cout << dca << std::endl;
            }

            ++eventID;
        };

    ROOT::RDataFrame(mcpHitSigTree)
        .Foreach(ProcessEvent,
                 {DataModel::MCPSimHit::Column::Time::Name(),
                  DataModel::MCPSimHit::Column::Position::Name(),
                  DataModel::MCPSimHit::Column::MCEventID::Name()}); */

    return EXIT_SUCCESS;
}
