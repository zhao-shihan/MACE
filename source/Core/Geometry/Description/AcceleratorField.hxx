#pragma once

#include "Core/Geometry/IDescription.hxx"

#include "G4Transform3D.hh"

namespace MACE::Core::Geometry::Description {

class AcceleratorField final : public IDescription {
public:
    static AcceleratorField& Instance() noexcept;

private:
    AcceleratorField();
    ~AcceleratorField() noexcept = default;
    AcceleratorField(const AcceleratorField&) = delete;
    AcceleratorField& operator=(const AcceleratorField&) = delete;

public:
    const auto& GetRadius() const { return fRadius; }
    const auto& GetLength() const { return fLength; }
    const auto& GetDownStreamLength() const { return fDownStreamLength; }
    G4Transform3D GetTransform() const;

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetDownStreamLength(double val) { fDownStreamLength = val; }

private:
    void ReadImpl(const YAML::Node& thisNode) override;
    void WriteImpl(YAML::Node& thisNode) const override;

private:
    double fRadius;
    double fLength;
    double fDownStreamLength;
};

} // namespace MACE::Core::Geometry::Description
