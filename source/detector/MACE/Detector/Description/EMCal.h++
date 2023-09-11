#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class EMC final : public DescriptionSingletonBase<EMC> {
    friend Env::Memory::SingletonFactory;

private:
    EMC();

public:
    const auto& InnerRadius() const { return fInnerRadius; }
    const auto& InnerLength() const { return fInnerLength; }
    const auto& WindowRadius() const { return fWindowRadius; }
    const auto& CrystalLength() const { return fCrystalLength; }

    void InnerRadius(double val) { fInnerRadius = val; }
    void InnerLength(double val) { fInnerLength = val; }
    void WindowRadius(double val) { fWindowRadius = val; }
    void CrystalLength(double val) { fCrystalLength = val; }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fInnerRadius;
    double fInnerLength;
    double fWindowRadius;
    double fCrystalLength;
};

} // namespace MACE::Detector::Description
