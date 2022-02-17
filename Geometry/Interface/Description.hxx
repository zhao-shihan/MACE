#pragma once

#include <iostream>

#include "Geometry/Global.hxx"
#include "Geometry/UnitSystem.hxx"

class MACE::Geometry::Interface::Description {
protected:
    Description() noexcept = default;
    virtual ~Description() noexcept = default;
    Description(const Description&) = delete;
    Description& operator=(const Description&) = delete;

public:
    [[nodiscard]] virtual const char* GetName()                   const = 0;
    [[nodiscard]] virtual const char* GetOverallDescription()     const = 0;
    [[nodiscard]] virtual const char* GetMaterialDescription()    const = 0;
    [[nodiscard]] virtual const char* GetShapeDescription()       const = 0;
    [[nodiscard]] virtual const char* GetMotherDescription()      const = 0;
    [[nodiscard]] virtual const char* GetTranslationDescription() const = 0;
    [[nodiscard]] virtual const char* GetRotationDescription()    const = 0;
    [[nodiscard]] virtual const char* GetOtherDescription()       const { return "None."; }

    friend std::ostream& operator<<(std::ostream& out, const Description& geomDescp);
};
