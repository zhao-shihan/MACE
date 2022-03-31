#pragma once

#include "Core/Geometry/Description/SpectrometerField.hxx"

#include "G4Transform3D.hh"

namespace MACE::Core::Geometry::Description {

class FirstTransportField final : public IDescription {
public:
    static FirstTransportField& Instance() noexcept;

private:
    FirstTransportField();
    ~FirstTransportField() noexcept = default;
    FirstTransportField(const FirstTransportField&) = delete;
    FirstTransportField& operator=(const FirstTransportField&) = delete;

public:
    const auto& GetRadius() const { return fRadius; }
    const auto& GetLength() const { return fLength; }
    G4Transform3D GetTransform() const;

    void SetRaidus(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fRadius;
    double fLength;
};

} // namespace MACE::Core::Geometry::Description
