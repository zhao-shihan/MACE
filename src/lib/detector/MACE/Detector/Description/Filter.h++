#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class Filter final : public DescriptionSingletonBase<Filter> {
    friend Env::Memory::SingletonFactory;

private:
    Filter();

public:
    const auto& Length() const { return fLength; }
    const auto& Width() const { return fWidth; }
    const auto& Thickness() const { return fThickness; }
    const auto& Count() const { return fCount; }

    void Length(auto v) { fLength = v; }
    void Width(auto v) { fWidth = v; }
    void Thickness(auto v) { fThickness = v; }
    void Count(auto v) { fCount = v; }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fLength;
    double fWidth;
    double fThickness;
    int fCount;
};

} // namespace MACE::Detector::Description
