#pragma once

#include "CLHEP/Vector/ThreeVector.h"

#include "MACEGlobal.hh"

namespace MACE::Reconstruction {
    enum {
        kCalorimeter,
        kOrbitalDetector,
        kSpectrometer
    };
}

#define MACE_DATA_MODEL_SMALL_MEMBER(T, Name, defaultValue) \
    public: \
        T Name() const { return f##Name; } \
        void Set##Name(T val) { f##Name = val; } \
    private: \
        T f##Name = defaultValue

#define MACE_DATA_MODEL_LARGE_MEMBER(T, Name, defaultValue) \
    public: \
        const T& Name() const { return f##Name; } \
        void Set##Name(const T& val) { f##Name = val; } \
        void Set##Name(T&& val) { f##Name = std::move(val); } \
    private: \
        T f##Name = defaultValue
