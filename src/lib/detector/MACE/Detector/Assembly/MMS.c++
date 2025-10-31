#include "MACE/Detector/Assembly/MMS.h++"
#include "MACE/Detector/Definition/CDCBody.h++"
#include "MACE/Detector/Definition/CDCCell.h++"
#include "MACE/Detector/Definition/CDCGas.h++"
#include "MACE/Detector/Definition/CDCSenseLayer.h++"
#include "MACE/Detector/Definition/CDCSuperLayer.h++"
#include "MACE/Detector/Definition/MMSBeamPipe.h++"
#include "MACE/Detector/Definition/MMSField.h++"
#include "MACE/Detector/Definition/MMSMagnet.h++"
#include "MACE/Detector/Definition/MMSShield.h++"
#include "MACE/Detector/Definition/TTC.h++"

#include "Mustard/Detector/Assembly/AssemblyBase.h++"
#include "Mustard/Detector/Definition/DefinitionBase.h++"

namespace MACE::Detector::Assembly {

MMS::MMS(Mustard::Detector::Definition::DefinitionBase& mother, bool checkOverlap) :
    AssemblyBase{} {
    // 1

    auto& mmsField{mother.NewDaughter<Detector::Definition::MMSField>(checkOverlap)};
    auto& mmsShield{mother.NewDaughter<Detector::Definition::MMSShield>(checkOverlap)};

    // 2

    auto& cdcBody{mmsField.NewDaughter<Detector::Definition::CDCBody>(checkOverlap)};
    mmsField.NewDaughter<Detector::Definition::MMSBeamPipe>(checkOverlap);
    mmsField.NewDaughter<Detector::Definition::MMSMagnet>(checkOverlap);
    mmsField.NewDaughter<Detector::Definition::TTC>(checkOverlap);

    // 3

    auto& cdcGas{cdcBody.NewDaughter<Detector::Definition::CDCGas>(checkOverlap)};

    // 4

    auto& cdcSuperLayer{cdcGas.NewDaughter<Detector::Definition::CDCSuperLayer>(checkOverlap)};

    // 5

    auto& cdcSenseLayer{cdcSuperLayer.NewDaughter<Detector::Definition::CDCSenseLayer>(checkOverlap)};

    // 6

    cdcSenseLayer.NewDaughter<Detector::Definition::CDCCell>(checkOverlap);

    // initialize

    AddTop(mmsField);
    AddTop(mmsShield);
    TopComplete();
}

} // namespace MACE::Detector::Assembly
