#pragma once

#if defined _MSC_VER or defined __INTEL_COMPILER
#    define MACE_STRONG_INLINE __forceinline
#else
#    define MACE_STRONG_INLINE inline
#endif

#if defined __clang__
#    define MACE_ALWAYS_INLINE [[clang::always_inline]] inline
#elif defined __GNUC__
#    define MACE_ALWAYS_INLINE [[gnu::always_inline]] inline
#else
#    define MACE_ALWAYS_INLINE MACE_STRONG_INLINE
#endif
