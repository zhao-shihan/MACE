// Copyright (c) 2022, Matthew Bentley (mattreecebentley@gmail.com) www.plflib.org

// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgement in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#    include <windows.h>
#    undef WIN32_LEAN_AND_MEAN
#else
#    include <windows.h>
#endif

namespace MACE::Utility::internal {

template<typename ATime>
class WallTimer {
public:
    WallTimer() noexcept;

    void Reset() noexcept { QueryPerformanceCounter(&fT0); }
    ATime SecondsElapsed() noexcept;
    auto MillisecondsElapsed() noexcept { return SecondsElapsed() * 1'000; }
    auto MicrosecondsElapsed() noexcept { return SecondsElapsed() * 1'000'000; }
    auto NanosecondsElapsed() noexcept { return SecondsElapsed() * 1'000'000'000; }

private:
    LARGE_INTEGER fFrequency;
    LARGE_INTEGER fT0;
};

} // namespace MACE::Utility::internal

#include "MACE/Utility/internal/WallTimer/WallTimer4Windows.inl"
