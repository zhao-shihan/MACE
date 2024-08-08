#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/ECal.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/PhaseI/Detector/Description/UsePhaseIDefault.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::PhaseI::Detector::Description {

auto UsePhaseIDefault() -> void {
    using namespace Mustard::LiteralUnit::Length;
    namespace MACE = MACE::Detector::Description;
    { // set accelerator up/downstream length to a random equal value
        auto& accelerator{MACE::Accelerator::Instance()};
        accelerator.UpstreamLength(2);
        accelerator.DownstreamLength(2);
    }
    { // Use cylinder target
        auto& target{MACE::Target::Instance()};
        target.ShapeType(MACE::Target::TargetShapeType::Cylinder);
    }
    { // bigger windows for ECal
        auto& eCal{MACE::ECal::Instance()};
        eCal.UpstreamWindowRadius(100_mm);
        eCal.DownstreamWindowRadius(100_mm);
    }
}

} // namespace MACE::PhaseI::Detector::Description
