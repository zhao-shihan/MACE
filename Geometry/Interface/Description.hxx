#pragma once

#include <iostream>

#include "Geometry/Global.hxx"
#include "Utility/UnitSystem.hxx"

class MACE::Geometry::Interface::Description {
protected:
    Description() noexcept = default;
    virtual ~Description() noexcept = default;
    Description(const Description&) = delete;
    Description& operator=(const Description&) = delete;

public:
    [[nodiscard]] virtual std::string GetName()                   const = 0;
    [[nodiscard]] virtual std::string GetOverallDescription()     const = 0;
    [[nodiscard]] virtual std::string GetMaterialDescription()    const = 0;
    [[nodiscard]] virtual std::string GetShapeDescription()       const = 0;
    [[nodiscard]] virtual std::string GetMotherDescription()      const = 0;
    [[nodiscard]] virtual std::string GetTranslationDescription() const = 0;
    [[nodiscard]] virtual std::string GetRotationDescription()    const = 0;
    [[nodiscard]] virtual std::string GetOtherDescription()       const { return "None."; }

    friend std::ostream& operator<<(std::ostream& out, const Description& geomDescp);
};
