#include "MACE/Detector/Geometry/GeometryBase.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.h++"

#include "G4SDManager.hh"

#include <stdexcept>
#include <utility>

#if MACE_USE_G4GDML
#    include "G4GDMLParser.hh"
#endif

namespace MACE::Detector::Geometry {

void GeometryBase::RegisterMaterial(gsl::index iLogicalVolume, gsl::not_null<G4Material*> material) const {
    LogicalVolume(iLogicalVolume)->SetMaterial(material);
}

void GeometryBase::RegisterMaterial(gsl::not_null<G4Material*> material) const {
    for (gsl::index i = 0; i < std::ssize(fLogicalVolumes); ++i) {
        RegisterMaterial(i, material);
    }
}

void GeometryBase::RegisterRegion(gsl::index iLogicalVolume, gsl::not_null<G4Region*> region) const {
    const auto& logicalVolume = LogicalVolume(iLogicalVolume);
    if (logicalVolume->GetRegion() != region) {
        logicalVolume->SetRegion(region);
        region->AddRootLogicalVolume(logicalVolume.get());
    }
}

void GeometryBase::RegisterRegion(gsl::not_null<G4Region*> region) const {
    for (gsl::index i = 0; i < std::ssize(fLogicalVolumes); ++i) {
        RegisterRegion(i, region);
    }
}

void GeometryBase::RegisterSD(gsl::index iLogicalVolume, gsl::not_null<G4VSensitiveDetector*> sd) const {
    const auto& logicalVolume = LogicalVolume(iLogicalVolume);
    if (logicalVolume->GetSensitiveDetector() == nullptr) {
        // Register to logicalVolume
        logicalVolume->SetSensitiveDetector(sd);
        // Register to G4SDManager
        auto sdManager = G4SDManager::GetSDMpointer();
        if (sdManager->FindSensitiveDetector(sd->GetFullPathName(), false) == nullptr) {
            sdManager->AddNewDetector(sd);
        }
    } else if (logicalVolume->GetSensitiveDetector() != sd) {
        G4ExceptionDescription msg;
        msg << "Attempting to register SD multiple times for \"" << logicalVolume->GetName() << "\" is currently not supported "
            << "(G4MultiSensitiveDetector not supported currently), skipping.";
        G4Exception("MACE::Detector::Geometry::GeometryBase::RegisterSD", "-1", JustWarning, msg);
    } else {
        G4ExceptionDescription msg;
        msg << "Attempting to register the same SD multiple times for \"" << logicalVolume->GetName() << "\", skipping.";
        G4Exception("MACE::Detector::Geometry::GeometryBase::RegisterSD", "-1", JustWarning, msg);
    }
}

void GeometryBase::RegisterSD(gsl::not_null<G4VSensitiveDetector*> sd) const {
    for (gsl::index i = 0; i < std::ssize(fLogicalVolumes); ++i) {
        RegisterSD(i, sd);
    }
}

void GeometryBase::Export(std::filesystem::path gdmlFile, gsl::index iPhysicalVolume) const {
#if MACE_USE_G4GDML
    if (Env::MPIEnv::Available()) { MPIUtil::MakeMPIFilePathInPlace(gdmlFile); }
    G4GDMLParser gdml;
    gdml.SetAddPointerToName(false);
    gdml.SetOutputFileOverwrite(true);
    gdml.Write(gdmlFile.generic_string(), PhysicalVolume(iPhysicalVolume).get());
#else
    std::clog << "Warning: this binary does not support GDML export (MACE_USE_G4GDML=OFF). "
                 "Try a binary compiles with MACE_USE_G4GDML=ON"
              << std::endl;
#endif
}

} // namespace MACE::Detector::Geometry
