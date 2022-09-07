#include "MACE/Utility/PrintStackTrace.hxx"

#include <version>

#ifdef __cpp_lib_stacktrace // C++2b
#    include <iostream>
#    include <stacktrace>
#else // fallback: ROOT stacktrace
#    include "TSystem.h"
#endif

namespace MACE::Utility {

void PrintStackTrace() {
#ifdef __cpp_lib_stacktrace // C++2b
    std::cout << std::stacktrace::current() << std::endl;
#else // fallback: ROOT stacktrace
    if (gSystem != nullptr) { // not destructed
        gSystem->StackTrace();
    }
#endif
}

} // namespace MACE::Utility
