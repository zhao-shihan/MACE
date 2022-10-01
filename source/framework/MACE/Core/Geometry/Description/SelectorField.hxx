#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class SelectorField final : public ISingletonDescription<SelectorField> {
    friend Env::Memory::SingletonFactory;

private:
    SelectorField();
    ~SelectorField() noexcept = default;
    SelectorField(const SelectorField&) = delete;
    SelectorField& operator=(const SelectorField&) = delete;

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

} // namespace MACE::Core::Geometry::Description
