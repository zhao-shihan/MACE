#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include <algorithm>
#include <string>
#include <utility>

namespace MACE::Detector::Description {

class Filter final : public DescriptionSingletonBase<Filter> {
    friend Env::Memory::SingletonInstantiator;

private:
    Filter();
    ~Filter() = default;

public:
    // Geometry

    auto Enabled() const -> auto { return fEnabled; }
    auto Length() const -> auto { return fLength; }
    auto Radius() const -> auto { return fRadius; }
    auto Thickness() const -> auto { return fThickness; }
    auto Count() const -> auto { return fCount; }
    auto Interval() const -> auto { return 2 * fRadius / fCount; }

    auto Enabled(bool val) -> void { fEnabled = val; }
    auto Length(auto val) -> void { fLength = val; }
    auto Radius(auto val) -> void { fRadius = val; }
    auto Thickness(auto val) -> void { fThickness = val; }
    auto Count(auto val) -> void { fCount = std::max(2, val); }

    // Material

    auto MaterialName() const -> const auto& { return fMaterialName; }

    auto MaterialName(std::string val) { fMaterialName = std::move(val); }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    // Geometry

    bool fEnabled;
    double fLength;
    double fRadius;
    double fThickness;
    int fCount;

    // Material

    std::string fMaterialName;
};

} // namespace MACE::Detector::Description
