#pragma once

#include "TTree.h"

#include "MACEGlobal.hh"

#define MACE_DATA_MODEL_NOT_ALLOW_TO_COPY(ClassName) \
    public: \
        ClassName(const ClassName&) = delete; \
        ClassName& operator=(const ClassName&) = delete
