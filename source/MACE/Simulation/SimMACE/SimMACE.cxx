#include "MACE/Simulation/SimMACE/Action/DetectorConstruction.hxx"
#include "MACE/Simulation/SimMACE/Action/PhysicsList.hxx"
#include "MACE/Simulation/SimMACE/RunManager.hxx"
#include "MACE/Utility/G4Util/MPIExecutive.hxx"
#include "MACE/Utility/MPIUtil/MPIEnvironment.hxx"

#include "Randomize.hh"

using namespace MACE::Simulation;

// constexpr const char* InitVisMac;

int main(int argc, char* argv[]) {
    MACE::Utility::MPIUtil::MPIEnvironment mpiEnvironment(argc, argv);

    bool interactive = (argc == 1);

    const auto randEng = std::make_unique<CLHEP::MTwistEngine>(4357L);
    G4Random::setTheEngine(randEng.get());

    // DetectorConstruction, PhysicsList, ActionInitialization are instantiated in RunManager constructor.
    const auto runManager = std::make_unique<SimMACE::RunManager>();
    runManager->GetDetectorConstruction().SetCheckOverlaps(interactive ? true : false);
    runManager->GetPhysicsList().SetVerboseLevel(interactive ? 1 : 0);

    const auto mpiExecutive = std::make_unique<MACE::Utility::G4Util::MPIExecutive>();
    if (interactive) {
        mpiExecutive->StartInteractiveSession(argc, argv, "init_vis.mac");
    } else {
        mpiExecutive->StartBatchSession(argv[1]);
    }

    return EXIT_SUCCESS;
}

/* # macro file for the initialization of SimMACE in interactive session

# Set some default verbose
/control/verbose 2
/control/saveHistory
/run/verbose 2

# Initialize kernel
/run/initialize

# Customized properties
/MACE/Generator/SurfaceMuon/SetFlux                   1e7 s-1
/MACE/Generator/SurfaceMuon/SetRepetitionRate         50 Hz
/MACE/Generator/SurfaceMuon/SetTimeWidthRMS           100 us
/MACE/Generator/SurfaceMuon/SetMomentum               28 MeV
/MACE/Generator/SurfaceMuon/SetMomentumSpreadRMS      1.4 MeV
/MACE/Generator/SurfaceMuon/SetBeamProfileRMS         5 mm
/MACE/Generator/SurfaceMuon/SetVertexZ                -1.5 m
/MACE/Generator/SurfaceMuon/SetMuonsForEachG4Event    500

/MACE/Physics/MuoniumPhysics/Formation/SetFormationProbability     0.6
/MACE/Physics/MuoniumPhysics/Formation/SetConversionProbability    0.5    # very high :)
/MACE/Physics/MuoniumPhysics/Transport/SetMeanFreePath             0.2 um

/MACE/Field/SetTransportMagneticField     0.1 tesla
/MACE/Field/SetLinacPotential             7 kilovolt
/MACE/Field/SetSelectorElectricField      500 kilovolt/m

/MACE/Analysis/EnableCoincidenceOfEMCal   true
/MACE/Analysis/EnableCoincidenceOfMCP     true

# Name of output
/MACE/Analysis/SetResultName              SimMACE_result

# Visualization setting
/control/execute vis.mac */
