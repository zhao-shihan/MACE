#include "fields/PSIMACESeparatorField.hh"

#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"


PSIMACESeparatorField::PSIMACESeparatorField()
    : G4ElectroMagneticField(),
    fMessenger(nullptr),
    fBy(0.1 * tesla),
    fEy(0.1804 * kilovolt / cm) {
    // define commands for this class
    DefineCommands();
}


PSIMACESeparatorField::~PSIMACESeparatorField() {
    delete fMessenger;
}

void PSIMACESeparatorField::GetFieldValue(const G4double[4], double* bField) const {
    bField[0] = 0.;
    bField[1] = fBy;
    bField[2] = 0.1 * tesla;
    bField[3] = -49.82583 * kilovolt / cm;
    bField[4] = 0.;
    bField[5] = 0.;
}


void PSIMACESeparatorField::DefineCommands() {
    // Define /PSIMACE/field command directory using generic messenger class
    fMessenger = new G4GenericMessenger(this,
        "/PSIMACESeparatorField/field/",
        "Field control");

    // fieldValue command 
    auto& valueCmd
        = fMessenger->DeclareMethodWithUnit("value", "tesla",
            &PSIMACESeparatorField::SetField,
            "Set field strength.");
    valueCmd.SetParameterName("field", true);
    valueCmd.SetDefaultValue("0.2");
}

