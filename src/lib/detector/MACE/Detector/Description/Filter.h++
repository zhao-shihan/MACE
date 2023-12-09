#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class Filter final : public DescriptionSingletonBase<Filter> {
    friend Env::Memory::SingletonFactory;

private:
    Filter();
    ~Filter() = default;

public:
    auto Length() const -> const auto& { return fLength; }
    auto Radius() const -> const auto& { return fRadius; }
    auto Thickness() const -> const auto& { return fThickness; }
    auto Count() const -> const auto& { return fCount; }

    auto Length(auto v) -> void { fLength = v; }
    auto Radius(auto v) -> void { fRadius = v; }
    auto Thickness(auto v) -> void { fThickness = v; }
    auto Count(auto v) -> void { fCount = v; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    double fLength;
    double fRadius;
    double fThickness;
    int fCount;
};

} // namespace MACE::Detector::Description
