#pragma once

#include <iostream>

#include "TVector3.h"
#include "TString.h"

#include "MACEGlobal.hh"

#define MACE_TRACK_RECONSTRUCTION_NOT_ALLOW_TO_COPY_BUT_ALLOW_TO_MOVE(ClassName) \
    public: \
        ClassName(const ClassName&) = delete; \
        ClassName& operator=(const ClassName&) = delete; \
        ClassName(ClassName&& value)

namespace MACE::Reconstruction {
    using PluseData = std::vector<Hit>;
    using HitPointerList = std::vector<const Hit*>;
}