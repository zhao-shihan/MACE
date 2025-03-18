#include "MACE/Detector/Definition/ECALCrystal.h++"
#include "MACE/Detector/Definition/ECALPhotoSensor.h++"
#include "MACE/Detector/Definition/Target.h++"
#include "MACE/Detector/Description/ECAL.h++"
#include "MACE/PhaseI/Detector/Definition/CentralBeamPipe.h++"
#include "MACE/PhaseI/Detector/Definition/MRPC.h++"
#include "MACE/PhaseI/Detector/Definition/World.h++"
#include "MACE/PhaseI/Detector/Description/UsePhaseIDefault.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/DetectorConstruction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Messenger/DetectorMessenger.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/ECALPMSD.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/ECALSD.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/MRPCSD.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Detector/Description/DescriptionIO.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4Region.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#include <array>

namespace MACE::PhaseI::SimMACEPhaseI::inline Action {

using namespace Mustard::LiteralUnit;

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{this},
    G4VUserDetectorConstruction{},
    fCheckOverlap{false},
    fWorld{},
    fDefaultGaseousRegion{},
    fDefaultSolidRegion{},
    fECALSensitiveRegion{},
    fShieldRegion{},
    fTargetRegion{},
    fVacuumRegion{},
    fECALSD{},
    fECALPMSD{} {
    DetectorMessenger::EnsureInstantiation();
    Detector::Description::UsePhaseIDefault();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    namespace PhaseI = PhaseI::Detector::Definition;
    using namespace MACE::Detector::Definition;

    fWorld = std::make_unique<PhaseI::World>();
    auto& ecalCrystal{fWorld->NewDaughter<ECALCrystal>(fCheckOverlap)};
    // auto& ecalPhotoSensor{fWorld->NewDaughter<ECALPhotoSensor>(fCheckOverlap)};
    auto& mrpc{fWorld->NewDaughter<PhaseI::MRPC>(fCheckOverlap)};
    auto& centralBeamPipe{fWorld->NewDaughter<PhaseI::CentralBeamPipe>(fCheckOverlap)};
    auto& target{centralBeamPipe.NewDaughter<Target>(fCheckOverlap)};

    const auto defaultCuts{G4ProductionCutsTable::GetProductionCutsTable()->GetDefaultProductionCuts()};

    fECALSensitiveRegion = new Region{"ECALSensitive", RegionType::ECALSensitive};
    fECALSensitiveRegion->SetProductionCuts(defaultCuts);
    ecalCrystal.RegisterRegion(fECALSensitiveRegion);

    fDefaultSolidRegion = new Region{"DefaultSolid", RegionType::DefaultSolid};
    fDefaultSolidRegion->SetProductionCuts(defaultCuts);
    centralBeamPipe.RegisterRegion(fDefaultSolidRegion);

    fTargetRegion = new Region{"Target", RegionType::Target};
    fTargetRegion->SetProductionCuts(defaultCuts);
    target.RegisterRegion(fTargetRegion);

    const auto& ecalName{MACE::Detector::Description::ECAL::Instance().Name()};

    fECALPMSD = new SD::ECALPMSD{ecalName + "PM"};
    // ecalPhotoSensor.RegisterSD("ECALPMCathode", fECALPMSD);

    fECALSD = new SD::ECALSD{ecalName, fECALPMSD};
    ecalCrystal.RegisterSD(fECALSD);

    const auto& mrpcName{MACE::PhaseI::Detector::Description::MRPC::Instance().Name()};

    fMRPCSD = new SD::MRPCSD{mrpcName};
    mrpc.RegisterSD("MRPCGas", fMRPCSD);

    return fWorld->PhysicalVolume();
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline Action
