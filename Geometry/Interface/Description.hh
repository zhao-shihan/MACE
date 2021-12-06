#pragma once

#include <iostream>

#include "Geometry/Global.hh"

class MACE::Geometry::Interface::Description {
protected:
    Description() noexcept {}
    virtual ~Description() noexcept {}
    Description(const Description&) = delete;
    Description& operator=(const Description&) = delete;

public:
    virtual const char* GetName()                   const = 0;
    virtual const char* GetOverallDescription()     const = 0;
    virtual const char* GetMaterialDescription()    const = 0;
    virtual const char* GetShapeDescription()       const = 0;
    virtual const char* GetMotherDescription()      const = 0;
    virtual const char* GetTranslationDescription() const = 0;
    virtual const char* GetRotationDescription()    const = 0;
    virtual const char* GetOtherDescription()       const { return "None."; }

    friend std::ostream& operator<<(std::ostream& out, const Description& geomDescp);
};

#define MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(DerivedGeometryDescriptionClass) \
    public: \
        static DerivedGeometryDescriptionClass* Instance() { \
            static DerivedGeometryDescriptionClass instance; \
            return &instance; \
        } \
    private: \
        DerivedGeometryDescriptionClass() noexcept { \
            static_assert(std::is_base_of<MACE::Geometry::Interface::Description, DerivedGeometryDescriptionClass>::value, \
                "DerivedGeometryDescriptionClass here should be derived from MACE::Geometry::Interface::Description."); \
            static_assert(std::is_final<DerivedGeometryDescriptionClass>::value, \
                "DerivedGeometryDescriptionClass should be a final class."); \
        } \
        ~DerivedGeometryDescriptionClass() noexcept final {} \
        DerivedGeometryDescriptionClass(const DerivedGeometryDescriptionClass&) = delete; \
        DerivedGeometryDescriptionClass& operator=(const DerivedGeometryDescriptionClass&) = delete
