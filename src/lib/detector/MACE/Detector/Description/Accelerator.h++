#pragma once

#include "Mustard/Detector/Description/DescriptionBase.h++"

#include "muc/math"

#include <string>
#include <utility>

namespace MACE::Detector::Description {

class Accelerator final : public Mustard::Detector::Description::DescriptionBase<Accelerator> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    Accelerator();
    ~Accelerator() = default;

public:
    // Geometry

    auto UpstreamLength() const -> auto { return fUpstreamLength; }
    auto DownstreamLength() const -> auto { return fDownstreamLength; }
    auto ElectrodePitch() const -> auto { return fElectrodePitch; }
    auto ElectrodeInnerRadius() const -> auto { return fElectrodeInnerRadius; }
    auto ElectrodeOuterRadius() const -> auto { return fElectrodeOuterRadius; }
    auto ElectrodeThickness() const -> auto { return fElectrodeThickness; }
    auto FieldRadius() const -> auto { return fFieldRadius; }
    auto FullLength() const -> auto { return fUpstreamLength + fDownstreamLength; }
    auto NElectrode() const -> auto { return muc::lltrunc((FullLength() - fElectrodeThickness) / fElectrodePitch) + 1; }

    auto UpstreamLength(double val) -> void { fUpstreamLength = val; }
    auto DownstreamLength(double val) -> void { fDownstreamLength = val; }
    auto ElectrodePitch(double val) -> void { fElectrodePitch = val; }
    auto ElectrodeInnerRadius(double val) -> void { fElectrodeInnerRadius = val; }
    auto ElectrodeOuterRadius(double val) -> void { fElectrodeOuterRadius = val; }
    auto ElectrodeThickness(double val) -> void { fElectrodeThickness = val; }
    auto FieldRadius(double val) -> void { fFieldRadius = val; }

    // Material

    auto ElectrodeMaterialName() const -> const auto& { return fElectrodeMaterialName; }

    auto ElectrodeMaterialName(std::string val) -> void { fElectrodeMaterialName = std::move(val); }

    // Field

    auto MaxPotential() const -> auto { return fMaxPotential; }
    auto MaxPotentialPosition() const -> auto { return fMaxPotentialPosition; }
    auto DecelerateLength() const -> auto { return fDecelerateLength; }
    auto AccelerateLength() const -> auto { return fAccelerateLength; }

    auto MaxPotential(double val) -> void { fMaxPotential = val; }
    auto MaxPotentialPosition(double val) -> void { fMaxPotentialPosition = val; }
    auto DecelerateLength(double val) -> void { fDecelerateLength = val; }
    auto AccelerateLength(double val) -> void { fAccelerateLength = val; }

private:
    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    // Geometry

    double fUpstreamLength;
    double fDownstreamLength;
    double fElectrodePitch;
    double fElectrodeInnerRadius;
    double fElectrodeOuterRadius;
    double fElectrodeThickness;
    double fFieldRadius;

    // Material

    std::string fElectrodeMaterialName;

    // Field

    double fMaxPotential;
    double fMaxPotentialPosition;
    double fDecelerateLength;
    double fAccelerateLength;
};

} // namespace MACE::Detector::Description
