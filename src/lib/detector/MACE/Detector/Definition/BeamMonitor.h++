#pragma once

#include "Mustard/Detector/Definition/DefinitionBase.h++"

namespace MACE::Detector::Definition {

class BeamMonitor final : public Mustard::Detector::Definition::DefinitionBase {
public:
    bool Enabled() const override;

private:
    auto Construct(bool checkOverlaps) -> void override;
};

} // namespace MACE::Detector::Definition
