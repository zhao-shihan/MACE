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

// Linux/BSD implementation:
#if (defined linux or defined __linux__ or defined __linux) or \
    (defined __DragonFly__ or defined __FreeBSD__ or defined __NetBSD__ or defined __OpenBSD__)
#    include "MACE/Utility/internal/WallTimer/WallTimer4LinuxBSD.hxx"
// Mac OSX implementation:
#elif defined __MACH__
#    include "MACE/Utility/internal/WallTimer/WallTimer4MacOSX.hxx"
// Windows implementation:
#elif defined _WIN32
#    include "MACE/Utility/internal/WallTimer/WallTimer4Windows.hxx"
// Fallback implementation:
#else
#    include "MACE/Utility/internal/WallTimer/WallTimer4Fallback.hxx"
#endif

#include <concepts>
#include <limits>

namespace MACE::Utility {

/// @brief high-precision cross-platform (linux/bsd/mac/windows) simple timer class
template<std::floating_point ATime>
    requires(std::numeric_limits<ATime>::digits >= std::numeric_limits<double>::digits)
class WallTimer final : public internal::WallTimer<ATime> {};

} // namespace MACE::Utility
