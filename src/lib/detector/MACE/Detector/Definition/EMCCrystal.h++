#pragma once

#include "Mustard/Detector/Definition/DefinitionBase.h++"

namespace MACE::Detector::Definition {

class EMCCrystal final : public Mustard::Detector::Definition::DefinitionBase {
private:
    auto Construct(bool checkOverlaps) -> void override;

private:
    std::map<std::size_t, std::size_t> fCopyNo2TypeID;
};

} // namespace MACE::Detector::Definition
