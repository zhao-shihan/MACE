#pragma once

#include "TTree.h"

#include "MACEGlobal.hh"

#define MACE_DATA_MODEL_CONSTRUCTORS_AND_ASSIGNMENTS(ClassName) \
    public: \
        ClassName() noexcept; \
        virtual ~ClassName() noexcept {} \
        ClassName(const ClassName& hit) noexcept; \
        ClassName(ClassName&& hit) noexcept; \
        ClassName& operator=(const ClassName& hit) noexcept; \
        ClassName& operator=(ClassName&& hit) noexcept

#define MACE_DATA_MODEL_NOT_ALLOW_TO_COPY(ClassName) \
    public: \
        ClassName(const ClassName&) = delete; \
        ClassName& operator=(const ClassName&) = delete

#define MACE_DATA_MODEL_NOT_ALLOW_TO_COPY_BUT_ALLOW_TO_MOVE(ClassName) \
    public: \
        ClassName(const ClassName&) = delete; \
        ClassName& operator=(const ClassName&) = delete; \
        ClassName(ClassName&& value)
