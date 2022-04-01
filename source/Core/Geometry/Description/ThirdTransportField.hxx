#pragma once

#include "Core/Geometry/Description/SecondBendField.hxx"

#include "G4Transform3D.hh"

namespace MACE::Core::Geometry::Description {

class ThirdTransportField final : public IDescription {
public:
    static ThirdTransportField& Instance() noexcept;

private:
    ThirdTransportField();
    ~ThirdTransportField() noexcept = default;
    ThirdTransportField(const ThirdTransportField&) = delete;
    ThirdTransportField& operator=(const ThirdTransportField&) = delete;

public:
    const auto& GetLength() const { return fLength; }
    const auto& GetRadius() const { return SecondBendField::Instance().GetRadius(); }
    G4Transform3D GetTransform() const;

    void SetLength(double val) { fLength = val; }

private:
    double fLength;
};

} // namespace MACE::Core::Geometry::Description
