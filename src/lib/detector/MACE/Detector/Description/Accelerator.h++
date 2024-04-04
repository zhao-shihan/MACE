#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include <string>
#include <utility>

namespace MACE::Detector::Description {

class Accelerator final : public DescriptionSingletonBase<Accelerator> {
    friend Env::Memory::SingletonInstantiator;

private:
    Accelerator();
    ~Accelerator() = default;

public:
    // Geometry

    auto UpstreamLength() const -> auto { return fUpstreamLength; }
    auto AccelerateLength() const -> auto { return fAccelerateLength; }
    auto ElectrodePitch() const -> auto { return fElectrodePitch; }
    auto ElectrodeInnerRadius() const -> auto { return fElectrodeInnerRadius; }
    auto ElectrodeOuterRadius() const -> auto { return fElectrodeOuterRadius; }
    auto ElectrodeThickness() const -> auto { return fElectrodeThickness; }
    auto FieldRadius() const -> auto { return fFieldRadius; }

    auto UpstreamLength(double val) -> void { fUpstreamLength = val; }
    auto AccelerateLength(double val) -> void { fAccelerateLength = val; }
    auto ElectrodePitch(double val) -> void { fElectrodePitch = val; }
    auto ElectrodeInnerRadius(double val) -> void { fElectrodeInnerRadius = val; }
    auto ElectrodeOuterRadius(double val) -> void { fElectrodeOuterRadius = val; }
    auto ElectrodeThickness(double val) -> void { fElectrodeThickness = val; }
    auto FieldRadius(double val) -> void { fFieldRadius = val; }

    // Material

    auto AcceleratePotential() const -> auto { return fAcceleratePotential; }

    auto AcceleratePotential(double val) -> void { fAcceleratePotential = val; }

    // Field

    auto ElectrodeMaterialName() const -> const auto& { return fElectrodeMaterialName; }

    auto ElectrodeMaterialName(std::string val) -> void { fElectrodeMaterialName = std::move(val); }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    // Geometry

    double fUpstreamLength;
    double fAccelerateLength;
    double fElectrodePitch;
    double fElectrodeInnerRadius;
    double fElectrodeOuterRadius;
    double fElectrodeThickness;
    double fFieldRadius;

    // Material

    std::string fElectrodeMaterialName;

    // Field

    double fAcceleratePotential;
};

} // namespace MACE::Detector::Description
