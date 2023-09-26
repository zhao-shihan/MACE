#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include "Eigen/Core"

namespace MACE::Detector::Description {

class EMC final : public DescriptionSingletonBase<EMC> {
    friend Env::Memory::SingletonFactory;

private:
    EMC();

public:
    auto NSubdivision() const -> const auto& { return fNSubdivision; }
    auto InnerRadius() const -> const auto& { return fInnerRadius; }
    auto CrystalLength() const -> const auto& { return fCrystalLength; }
    auto WindowRadius() const -> const auto& { return fWindowRadius; }

    auto NSubdivision(const auto& val) -> void { fNSubdivision = val; }
    auto InnerRadius(const auto& val) -> void { fInnerRadius = val; }
    auto CrystalLength(const auto& val) -> void { fCrystalLength = val; }
    auto WindowRadius(const auto& val) -> void { fWindowRadius = val; }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    int fNSubdivision;
    double fInnerRadius;
    double fCrystalLength;
    double fWindowRadius;
};

} // namespace MACE::Detector::Description
