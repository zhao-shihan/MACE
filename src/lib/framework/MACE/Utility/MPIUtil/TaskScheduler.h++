#pragma once

#include "MACE/Concept/MPIPredefined.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Utility/MPIUtil/DataType.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "mpi.h"

#include "fmt/format.h"

#include <cassert>
#include <concepts>
#include <cstdio>
#include <optional>
#include <stdexcept>

namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
class TaskScheduler : public NonMoveableBase {
public:
    TaskScheduler();
    explicit TaskScheduler(T size);
    TaskScheduler(T first, T last);
    ~TaskScheduler();

    auto AssignTask(T size) -> void { AssignTask(0, size); }
    auto AssignTask(T first, T last) -> void;
    auto Reset() -> void;

    auto Task() const -> const auto& { return fTask; }
    auto NTask() const -> T { return fTask.last - fTask.first; }

    auto Next() -> std::optional<T>;
    auto Processing() const -> T { return fProcessing; }
    auto NProcessed() const -> T { return Processing() - fTask.first + 1; }
    auto NLocalProcessed() const -> T { return fNLocalProcessed; }

private:
    struct {
        T first;
        T last;
    } fTask;
    T fProcessing;
    T fNLocalProcessed;

    T* fMemory;
    MPI_Win fWindow;
};

} // namespace MACE::inline Utility::MPIUtil

#include "MACE/Utility/MPIUtil/TaskScheduler.inl"
