#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/SimTarget/Action/DetectorConstruction.h++"
#include "MACE/SimTarget/Messenger/DetectorMessenger.h++"

#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimTarget::inline Messenger {

DetectorMessenger::DetectorMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fImportDescription{},
    fExportDescription{},
    fIxportDescription{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Detector/");

    fImportDescription = std::make_unique<G4UIcmdWithAString>("/MACE/Detector/Description/Import", this);
    fImportDescription->SetGuidance("Import geometry descriptions required by this program from a yaml file.");
    fImportDescription->SetParameterName("yaml", false);
    fImportDescription->AvailableForStates(G4State_PreInit);

    fExportDescription = std::make_unique<G4UIcmdWithAString>("/MACE/Detector/Description/Export", this);
    fExportDescription->SetGuidance("Export geometry descriptions used by this program to a yaml file.");
    fExportDescription->SetParameterName("yaml", false);
    fExportDescription->AvailableForStates(G4State_PreInit, G4State_Idle);

    fIxportDescription = std::make_unique<G4UIcmdWithAString>("/MACE/Detector/Description/Ixport", this);
    fIxportDescription->SetGuidance("Export, Import, then export geometry descriptions used by this program. "
                                    "Exported files have '.prev' (previous) or '.curr' (current) suffix, respectively.");
    fIxportDescription->SetParameterName("yaml", false);
    fIxportDescription->AvailableForStates(G4State_PreInit);
}

DetectorMessenger::~DetectorMessenger() = default;

auto DetectorMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    using DescriptionInUse = DetectorConstruction::DescriptionInUse;
    using Detector::Description::DescriptionIO;
    if (command == fImportDescription.get()) {
        DescriptionIO::Import<DescriptionInUse>(std::string_view(value));
    } else if (command == fExportDescription.get()) {
        DescriptionIO::Export<DescriptionInUse>(std::string_view(value), "SimTarget: geometry description");
    } else if (command == fIxportDescription.get()) {
        DescriptionIO::Ixport<DescriptionInUse>(std::string_view(value), "SimTarget: geometry description");
    }
}

} // namespace MACE::SimTarget::inline Messenger
