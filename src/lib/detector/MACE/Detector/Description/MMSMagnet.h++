#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include <string>
#include <utility>

namespace MACE::Detector::Description {

class MMSMagnet final : public DescriptionSingletonBase<MMSMagnet> {
    friend Env::Memory::SingletonInstantiator;

private:
    MMSMagnet();
    ~MMSMagnet() = default;

public:
    // Geometry

    auto InnerRadius() const -> auto { return fInnerRadius; }
    auto OuterRadius() const -> auto { return fOuterRadius; }
    auto Length() const -> auto { return fLength; }

    auto InnerRadius(double val) -> void { fInnerRadius = val; }
    auto OuterRadius(double val) -> void { fOuterRadius = val; }
    auto Length(double val) -> void { fLength = val; }

    // Material

    auto MaterialName() const -> const auto& { return fMaterialName; }

    auto MaterialName(std::string val) { fMaterialName = std::move(val); }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    // Geometry

    double fInnerRadius;
    double fOuterRadius;
    double fLength;

    // Material

    std::string fMaterialName;
};

} // namespace MACE::Detector::Description
