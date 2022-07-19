#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class SpectrometerField final : public IDescriptionSingleton<SpectrometerField> {
    friend Environment::Resource::SingletonFactory;

private:
    SpectrometerField();
    ~SpectrometerField() noexcept = default;
    SpectrometerField(const SpectrometerField&) = delete;
    SpectrometerField& operator=(const SpectrometerField&) = delete;

public:
    const auto& GetRadius() const { return fRadius; }
    const auto& GetLength() const { return fLength; }

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    void ReadDescriptionNode(const YAML::Node& node) override;
    void WriteDescriptionNode(YAML::Node& node) const override;

private:
    double fRadius;
    double fLength;
};

} // namespace MACE::Core::Geometry::Description
