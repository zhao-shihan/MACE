#include "PSIMACETransMagField.hh"

#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

#include "PSIMACEConfigs.hh"

PSIMACETransMagField::PSIMACETransMagField()
    : G4ElectroMagneticField(),
    fMessenger(nullptr),
    fBy(0.1 * tesla),
    fEy(0.1804 * kilovolt / cm) {
    // define commands for this class
    DefineCommands();
}

PSIMACETransMagField::~PSIMACETransMagField() {
    delete fMessenger;
}

void PSIMACETransMagField::GetFieldValue(const G4double[4], double* bField) const {
    bField[0] = 0.;
    bField[1] = fBy;
    bField[2] = 0.;
    bField[3] = 0.;
#if PSIMACE_EXPERIMENT_TYPE == 1
    bField[4] = -fEy;
#elif PSIMACE_EXPERIMENT_TYPE == -1
    bField[4] = fEy;
#else
#error "unknown experiment."
#endif
    bField[5] = 0.;
}


void PSIMACETransMagField::DefineCommands() {
    // Define /PSIMACE/field command directory using generic messenger class
    fMessenger = new G4GenericMessenger(this,
        "/PSIMACETransEMField/field/",
        "Field control");

    // fieldValue command 
    auto& valueCmd
        = fMessenger->DeclareMethodWithUnit("value", "tesla",
            &PSIMACETransMagField::SetField,
            "Set field strength.");
    valueCmd.SetParameterName("field", true);
    valueCmd.SetDefaultValue("0.2");
}

