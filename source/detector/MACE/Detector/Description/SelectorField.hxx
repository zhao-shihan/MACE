#pragma once

#include "MACE/Detector/Description/DescriptionBase.hxx"

namespace MACE::Detector::Description {

class SelectorField final : public DescriptionSingletonBase<SelectorField> {
    friend Env::Memory::SingletonFactory;

private:
    SelectorField();

public:
    const auto& Radius() const { return fRadius; }
    const auto& Length() const { return fLength; }
    const auto& AxialPosition() const { return fAxialPosition; }

    void Radius(double val) { fRadius = val; }
    void Length(double val) { fLength = val; }
    void AxialPosition(double val) { fAxialPosition = val; }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fRadius;
    double fLength;
    double fAxialPosition;
};

} // namespace MACE::Detector::Description
