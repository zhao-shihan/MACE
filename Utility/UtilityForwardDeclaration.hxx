#pragma once

namespace MACE {

    // FIXME: using inline namespace at this level (just under MACE) confuses VSCode's C++ extension. Maybe conflicts with the C++ standard? 
    // inline namespace Utility {

    inline namespace MPITools {
        class MPIFileTools;
        class G4MPIRunManager;
    }

    // } // inline namespace Utility

} // namespace MACE
