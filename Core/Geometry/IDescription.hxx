#pragma once

#include "Utility/LiteralUnit.hxx"

#include <ostream>

namespace MACE::Geometry {

using namespace Utility::LiteralUnit;

class IDescription {
protected:
    IDescription() noexcept = default;
    virtual ~IDescription() noexcept = default;
    IDescription(const IDescription&) = delete;
    IDescription& operator=(const IDescription&) = delete;

public:
    virtual std::string GetName() const = 0;
    virtual std::string GetOverallDescription() const = 0;
    virtual std::string GetMaterialDescription() const = 0;
    virtual std::string GetShapeDescription() const = 0;
    virtual std::string GetMotherDescription() const = 0;
    virtual std::string GetTranslationDescription() const = 0;
    virtual std::string GetRotationDescription() const = 0;
    virtual std::string GetOtherDescription() const { return "None."; }

    friend std::ostream& operator<<(std::ostream& out, const IDescription& geomDescp);
};

} // namespace MACE::Geometry::Description
