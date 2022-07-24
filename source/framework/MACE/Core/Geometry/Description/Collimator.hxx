#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class Collimator final : public ISingletonDescription<Collimator> {
    friend Environment::Memory::SingletonFactory;

private:
    Collimator();
    ~Collimator() noexcept = default;
    Collimator(const Collimator&) = delete;
    Collimator& operator=(const Collimator&) = delete;

public:
    const auto& GetInnerRadius() const { return fInnerRadius; }
    const auto& GetOuterRadius() const { return fOuterRadius; }
    const auto& GetLength() const { return fLength; }
    const auto& GetThickness() const { return fThickness; }
    const auto& GetZPosition() const { return fZPosition; }
    const auto& GetCount() const { return fCount; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetOuterRadius(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetThickness(double val) { fThickness = val; }
    void SetZPosition(double val) { fZPosition = val; }
    void SetCount(int val) { fCount = val; }

private:
    void ReadDescriptionNode(const YAML::Node& node) override;
    void WriteDescriptionNode(YAML::Node& node) const override;

private:
    double fInnerRadius;
    double fOuterRadius;
    double fLength;
    double fZPosition;
    double fThickness;
    int fCount;
};

} // namespace MACE::Core::Geometry::Description
