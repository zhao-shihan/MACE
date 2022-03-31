#pragma once

#include "Core/Geometry/Description/FirstTransportField.hxx"

#include "G4Transform3D.hh"

namespace MACE::Core::Geometry::Description {

class FirstBendField final : public IDescription {
public:
    static FirstBendField& Instance() noexcept;

private:
    FirstBendField();
    ~FirstBendField() noexcept = default;
    FirstBendField(const FirstBendField&) = delete;
    FirstBendField& operator=(const FirstBendField&) = delete;

public:
    const auto& GetRadius() const { return FirstTransportField::Instance().GetRadius(); }
    const auto& GetBendRadius() const { return fBendRadius; }
    G4Transform3D GetTransform() const;

    void SetBendRadius(double val) { fBendRadius = val; }

private:
    double fBendRadius;
};

} // namespace MACE::Core::Geometry::Description
