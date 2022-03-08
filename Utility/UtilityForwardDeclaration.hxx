#pragma once

namespace MACE {

    // FIXME: using inline namespace at this level (just under MACE) confuses VSCode's C++ extension. Maybe conflicts with the C++ standard? 
    // inline namespace Utility {

    inline namespace MPITools {
        class G4MPIRunManager;
        class MPIFileTools;
        class MPIJobsAssigner;
    }

    // } // inline namespace Utility

} // namespace MACE
