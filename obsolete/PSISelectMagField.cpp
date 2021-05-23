#include "PSIMACESelectMagField.hh"

#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"


PSIMACESelectMagField::PSIMACESelectMagField() :
    G4MagneticField(),
    fMessenger(nullptr),
    fBy(0.0008083 * tesla) {
    // define commands for this class
    DefineCommands();
}


PSIMACESelectMagField::~PSIMACESelectMagField() {
    delete fMessenger;
}

void PSIMACESelectMagField::GetFieldValue(const G4double point[4], double* bField) const {
    double sxy = sqrt((point[0] / CLHEP::cm - 35.0) * (point[0] / CLHEP::cm - 35.0) + (point[1] / CLHEP::cm - 48.0) * (point[1] / CLHEP::cm - 48.0));

    if (sxy > 38.0 || sxy < 32.0) {
        bField[0] = 0;
        bField[1] = 0;
    }

    else {
        bField[0] = (point[1] / CLHEP::cm - 48.0) / sxy * 0.1 * tesla;
        bField[1] = -(point[0] / CLHEP::cm - 35.0) / sxy * 0.1 * tesla;
    }

    bField[2] = fBy;
}

void PSIMACESelectMagField::DefineCommands() {
    // Define /PSIMACE/field command directory using generic messenger class
    fMessenger = new G4GenericMessenger(this,
        "/PSIMACESelectEMField/field/",
        "Field control");

    // fieldValue command 
    auto& valueCmd
        = fMessenger->DeclareMethodWithUnit("value", "tesla",
            &PSIMACESelectMagField::SetField,
            "Set field strength.");
    valueCmd.SetParameterName("field", true);
    valueCmd.SetDefaultValue("0.00080829");
}

