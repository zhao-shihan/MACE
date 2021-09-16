#pragma once

#include <iostream>

#include "TVector3.h"
#include "TString.h"

#include "MACEGlobal.hh"

#define MACE_SPECTROMETER_RECONSTRUCTION_NOT_ALLOW_TO_COPY_BUT_ALLOW_TO_MOVE(ClassName) \
    public: \
        Bool_t operator==(const ClassName& instance) { return this == &instance; } \
        ClassName(const ClassName&) = delete; \
        ClassName& operator=(const ClassName&) = delete; \
        ClassName(ClassName&& value)
