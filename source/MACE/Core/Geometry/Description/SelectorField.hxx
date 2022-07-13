#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class SelectorField final : public IDescriptionSingleton<SelectorField> {
    friend Singleton<SelectorField>;

private:
    SelectorField();
    ~SelectorField() noexcept = default;
    SelectorField(const SelectorField&) = delete;
    SelectorField& operator=(const SelectorField&) = delete;

public:
    const auto& GetRadius() const { return fRadius; }
    const auto& GetLength() const { return fLength; }
    const auto& GetZPosition() const { return fZPosition; }

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetZPosition(double val) { fZPosition = val; }

private:
    void ReadDescriptionNode(const YAML::Node& node) override;
    void WriteDescriptionNode(YAML::Node& node) const override;

private:
    double fRadius;
    double fLength;
    double fZPosition;
};

} // namespace MACE::Core::Geometry::Description
