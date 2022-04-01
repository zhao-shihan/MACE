#pragma once

#include "Core/Geometry/Description/ThirdTransportField.hxx"

namespace MACE::Core::Geometry::Description {

class CalorimeterField final : public IDescription {
public:
    static CalorimeterField& Instance() noexcept;

private:
    CalorimeterField();
    ~CalorimeterField() noexcept = default;
    CalorimeterField(const CalorimeterField&) = delete;
    CalorimeterField& operator=(const CalorimeterField&) = delete;

public:
    const auto& GetRadius() const { return fRadius; }
    const auto& GetLength() const { return fLength; }
    G4Transform3D GetTransform() const;

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fRadius;
    double fLength;
};

} // namespace MACE::Core::Geometry::Description
