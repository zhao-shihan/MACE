#include "PSIMACETransSecondField.hh"

#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"


PSIMACETransSecondField::PSIMACETransSecondField()
: G4MagneticField(), 
  fMessenger(nullptr), fBy(0.1*tesla)
{
  // define commands for this class
  DefineCommands();
}


PSIMACETransSecondField::~PSIMACETransSecondField()
{ 
  delete fMessenger; 
}

void PSIMACETransSecondField::GetFieldValue(const G4double [4],double *bField) const
{
  bField[0] = fBy;
  bField[1] = 0.;
  bField[2] = 0.;
}


void PSIMACETransSecondField::DefineCommands()
{
  // Define /PSIMACE/field command directory using generic messenger class
  fMessenger = new G4GenericMessenger(this, 
                                      "/PSIMACETransSecondEMField/field/", 
                                      "Field control");

  // fieldValue command 
  auto& valueCmd
    = fMessenger->DeclareMethodWithUnit("value","tesla",
                                &PSIMACETransSecondField::SetField, 
                                "Set field strength.");
  valueCmd.SetParameterName("field", true);
  valueCmd.SetDefaultValue("0.002603187");
}

