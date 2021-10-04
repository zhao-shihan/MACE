#pragma once

#include <array>

#include "CLHEP/Vector/ThreeVector.h"

#include "MACEGlobal.hh"

namespace MACE::DataModel {

    static constexpr uint32_t detectorNum = 3;

    enum DetectorSubscript {
        kCalorimeter,
        kOrbitalDetector,
        kSpectrometer
    };

    static constexpr std::array<const char*, detectorNum> detectorName = {
        "Calorimeter",
        "OrbitalDetector",
        "Spectrometer"
    };

}

#define MACE_DATA_MODEL_NOT_ALLOW_TO_COPY(ClassName) \
    public: \
        ClassName(const ClassName&) = delete; \
        ClassName& operator=(const ClassName&) = delete

#define MACE_DATA_MODEL_NOT_ALLOW_TO_COPY_BUT_ALLOW_TO_MOVE(ClassName) \
    public: \
        ClassName(const ClassName&) = delete; \
        ClassName& operator=(const ClassName&) = delete; \
        ClassName(ClassName&& value)

#define MACE_DATA_MODEL_SMALL_MEMBER(T, Name) \
    public: \
        T Name() const { return f##Name; } \
        void Set##Name(T val) { f##Name = val; } \
    private: \
        T f##Name

#define MACE_DATA_MODEL_LARGE_MEMBER(T, Name) \
    public: \
        const T& Name() const { return f##Name; } \
        void Set##Name(const T& val) { f##Name = val; } \
        void Set##Name(T&& val) { f##Name = std::move(val); } \
    private: \
        T f##Name

#define MACE_DATA_MODEL_TRANSIENT_ESSENTIAL(ClassName) \
public: \
    virtual ~ClassName() {} \
    ClassName(); \
    ClassName(const ClassName& hit); \
    ClassName(ClassName&& hit); \
    ClassName& operator=(const ClassName& hit); \
    ClassName& operator=(ClassName&& hit); \
    ClassName(const MACE::DataModel::Hit::Persistency::ClassName& hit); \
    ClassName(MACE::DataModel::Hit::Persistency::ClassName&& hit); \
    ClassName& operator=(const MACE::DataModel::Hit::Persistency::ClassName& hit); \
    ClassName& operator=(MACE::DataModel::Hit::Persistency::ClassName&& hit); \
    MACE::DataModel::Hit::Persistency::ClassName ToPersistency()
