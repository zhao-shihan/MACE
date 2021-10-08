#pragma once

#include "TTree.h"

#include "MACEGlobal.hh"

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

#define MACE_DATA_MODEL_PERSISTIFIER(T, Name) \
    private: \
        static T persist##Name

#define MACE_DATA_MODEL_PERSISTIFIER_DEF(ClassName, Name, defaultVal) \
    decltype(ClassName::persist##Name) ClassName::persist##Name = defaultVal

#define MACE_DATA_MODEL_NAME(nameStr) \
    public: \
        static constexpr const char* name = nameStr

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
