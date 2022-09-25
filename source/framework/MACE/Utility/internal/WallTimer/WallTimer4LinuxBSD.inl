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

namespace MACE::Utility::internal {

template<typename ATime>
WallTimer<ATime>::WallTimer() noexcept :
    fT0() {
    Reset();
}

template<typename ATime>
ATime WallTimer<ATime>::NanosecondsElapsed() const noexcept {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return static_cast<ATime>(t.tv_sec - fT0.tv_sec) * 1'000'000'000 +
           static_cast<ATime>(t.tv_nsec - fT0.tv_nsec);
}

} // namespace MACE::Utility::internal
