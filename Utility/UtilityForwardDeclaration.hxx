#pragma once

namespace MACE {

// FIXME: using inline namespace at this level (just under MACE) confuses VSCode's C++ extension.
// inline namespace Utility {

inline namespace MPITools {
    class G4MPIRunManager;
    class MPIFileTools;
    class MPIJobsAssigner;
}

class ShortString;

// } // inline namespace Utility

}  // namespace MACE
