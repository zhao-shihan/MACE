#pragma once

namespace MACE {
    inline namespace Utility {
        // mainly for class member holding pointer reference to an exist object which is not owned by the class.
        template<typename T>
        using ObserverPtr = T*;
    }
}
