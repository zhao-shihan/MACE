// #include "MACE/ReconCDCTrack/Finder/MCTruthFinder.h++"
// #include "MACE/ReconCDCTrack/Fitter/MCTruthFitter.h++"

#include "MACE/DataModel/DataFactory.h++"
#include "MACE/DataModel/SimHit/CDCSimHit.h++"
#include "MACE/DataModel/SimTrack/CDCPhysicsSimTrack.h++"
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
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Math/Norm.h++"
#include "MACE/Math/Random/Distribution/Gaussian.h++"
#include "MACE/Math/Random/Distribution/Gaussian3DDiagnoal.h++"
#include "MACE/Math/Random/Generator/Xoshiro512SS.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/PhysicalConstant.h++"
#include "MACE/Utility/VectorArithmeticOperator.h++"
#include "MACE/Utility/VectorCast.h++"

#include "RKTrackRep.h"
#include "TDatabasePDG.h"
#include "TEveManager.h"
#include "TGeoManager.h"
#include "TGeoMaterialInterface.h"
#include "TMath.h"
#include "TVector3.h"
#include "Track.h"
#include "TrackPoint.h"

#include "G4NistManager.hh"

#include "gsl/gsl"

#include "ConstField.h"
#include "EventDisplay.h"
#include "Exception.h"
#include "FieldManager.h"
#include "KalmanFitStatus.h"
#include "KalmanFitterRefTrack.h"
#include "MaterialEffects.h"
#include "StateOnPlane.h"
#include "WireMeasurement.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <filesystem>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>

using namespace MACE;

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

std::vector<std::vector<std::shared_ptr<DataModel::CDCSimHit>>> FindTrackTruth(std::vector<std::shared_ptr<DataModel::CDCSimHit>> hitData) {
    std::ranges::sort(hitData,
                      [](const auto& hit1, const auto& hit2) {
                          return std::tie(hit1->MCEventID().Value(), hit1->MCTrackID().Value(), hit1->CellID().Value()) <
                                 std::tie(hit2->MCEventID().Value(), hit2->MCTrackID().Value(), hit2->CellID().Value());
                      });

    std::vector<std::vector<std::shared_ptr<DataModel::CDCSimHit>>> rawTrackData;
    std::tuple currentTrackID = {-1, -1};
    decltype(rawTrackData)::pointer rawTrack;
    for (auto&& hit : hitData) {
        if (const auto newTrackID = std::tie(hit->MCEventID().Value(), hit->MCTrackID().Value());
            newTrackID != currentTrackID) {
            if (rawTrack->size() >= 7) {
                rawTrack = &rawTrackData.emplace_back();
            }
            currentTrackID = newTrackID;
        }
        rawTrack->emplace_back(hit);
    }
    return rawTrackData;
}

int main(int argc, char* argv[]) {
    Env::BasicEnv env(argc, argv, {});

    // init geometry and mag. field
    MakeMACECDCGeometry();

    // import data
    const auto file = std::make_unique<TFile>(argv[1]);
    MACE::DataModel::DataFactory dataFactory;
    dataFactory.TreeNamePrefixFormat("G4Run{}_");
    const auto tree = dataFactory.FindTree<DataModel::CDCSimHit>(*file, 0);
    const auto hitData = dataFactory.CreateAndFillList<DataModel::CDCSimHit>(*tree);

    // find track
    const auto rawTrackData = FindTrackTruth(hitData);

    // event display
    const auto display = genfit::EventDisplay::getInstance();

    // fitter
    genfit::KalmanFitterRefTrack fitter;

    // rng
    Math::Random::Xoshiro512SS rng;

    // generate momentum seed by smearing true value
    const auto MomentumSeed = [&rng](stdx::array3d p) {
        constexpr auto resolution = 0.2;
        const auto sigma = resolution * Math::Norm(p);
        p += Math::Random::Gaussian3DDiagnoal({0., sigma}, {0., sigma}, {0., sigma})(rng);
        TVector3 pSeed(p[0], p[1], p[2]);
        return pSeed * 0.001;
    };

    // smearing drift
    using namespace LiteralUnit::Length;
    constexpr auto driftDistanceResolution = 100_um / 10;

    // fit data
    std::vector<genfit::Track> genfitTrackData;
    std::vector<std::shared_ptr<DataModel::CDCPhysicsSimTrack>> fitTrackData;

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
            const auto driftInROOTUnit = std::abs(Math::Random::Gaussian(hit->DriftDistance().Value(), driftDistanceResolution)(rng)) / 10;

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
            rawHitCov[6][6] = Math::Pow2(driftDistanceResolution);

            const auto wireMeasurement = new genfit::WireMeasurement(rawHitCoords,
                                                                     rawHitCov,
                                                                     cellID,
                                                                     hitID++,
                                                                     nullptr);
            genfitTrack.insertPoint(new genfit::TrackPoint(wireMeasurement, &genfitTrack));
        }
        genfitTrack.checkConsistency();
        fitter.processTrack(&genfitTrack);
        try {
            genfitTrack.getFittedState() /* .Print() */;
        } catch (const genfit::Exception&) {
            continue;
        }
        genfitTrack.checkConsistency();
        display->addEvent(&genfitTrack);
        // save fitted track
        const auto& state = genfitTrack.getFittedState();
        const auto& fitStatus = *genfitTrack.getKalmanFitStatus();
        const auto& fitTrack = fitTrackData.emplace_back(std::make_shared_for_overwrite<DataModel::CDCPhysicsSimTrack>());
        fitTrack->VertexKineticEnergyTruth().Value(firstHit->VertexKineticEnergy().Value());
        fitTrack->VertexMomentumTruth().Value(firstHit->VertexMomentum().Value());
        fitTrack->NHitTruth().Value(rawTrack.size());
        const auto momentum = state.getMom() * 1000;
        const auto mass = state.getMass() * 1000;
        const auto kineticEnergy = std::sqrt(momentum.Mag2() + Math::Pow2(mass)) - mass;
        fitTrack->VertexKineticEnergy().Value(kineticEnergy);
        fitTrack->VertexMomentum().Value({momentum[0], momentum[1], momentum[2]});
        fitTrack->NHit().Value(genfitTrack.getNumPoints());
        fitTrack->Chi2().Value(fitStatus.getChi2());
    }

    const auto outFile = std::make_unique<TFile>(argv[2], "RECREATE");
    dataFactory.CreateAndFillTree<DataModel::CDCPhysicsSimTrack>(fitTrackData, 0)->Write();

    // open event display
    display->open();

    return EXIT_SUCCESS;
}
