#pragma once

#include "Core/Geometry/Description/FirstBendField.hxx"

#include "G4Transform3D.hh"

namespace MACE::Core::Geometry::Description {

class SecondTransportField final : public IDescription {
public:
    static SecondTransportField& Instance() noexcept;

private:
    SecondTransportField();
    ~SecondTransportField() noexcept = default;
    SecondTransportField(const SecondTransportField&) = delete;
    SecondTransportField& operator=(const SecondTransportField&) = delete;

public:
    const auto& GetLength() const { return fLength; }
    const auto& GetRadius() const { return FirstBendField::Instance().GetRadius(); }
    G4Transform3D GetTransform() const;

    void SetLength(double val) { fLength = val; }

private:
    double fLength;
};

} // namespace MACE::Core::Geometry::Description
