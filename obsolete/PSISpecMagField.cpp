#include "PSIMACESpecMagField.hh"

#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"


PSIMACESpecMagField::PSIMACESpecMagField()
: G4MagneticField(), 
  fMessenger(nullptr), fBy(0.1*tesla)
//  fBy(0.002637187*tesla)
//  fBy(0.1*tesla)
{
  // define commands for this class
  DefineCommands();
}


PSIMACESpecMagField::~PSIMACESpecMagField()
{ 
  delete fMessenger; 
}

void PSIMACESpecMagField::GetFieldValue(const G4double [4],double *bField) const
{
  bField[0] = 0.;
  bField[1] = fBy;
  bField[2] = 0.;
}


void PSIMACESpecMagField::DefineCommands()
{
  // Define /PSIMACE/field command directory using generic messenger class
  fMessenger = new G4GenericMessenger(this, 
                                      "/PSIMACESpecEMField/field/", 
                                      "Field control");

  // fieldValue command 
  auto& valueCmd
    = fMessenger->DeclareMethodWithUnit("value","tesla",
                                &PSIMACESpecMagField::SetField, 
                                "Set field strength.");
  valueCmd.SetParameterName("field", true);
  valueCmd.SetDefaultValue("0.1");
}

