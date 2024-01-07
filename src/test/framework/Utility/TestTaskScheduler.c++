#include "MACE/Env/MPIEnv.h++"
#include "MACE/Utility/MPIUtil/TaskScheduler.h++"

#include "fmt/format.h"

#include <string>
#include <thread>

using namespace MACE;

auto main(int argc, char* argv[]) -> int {
    MACE::Env::MPIEnv env{argc, argv, {}};

    MPIUtil::TaskScheduler task{std::stoll(argv[1])};
    // task.PrintProgressModulo(0);
    for (auto i{task.Next()}; i.has_value(); i = task.Next()) {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1000ms);
        fmt::println("{} by {}", *i, env.CommWorldRank());
    }

    return EXIT_SUCCESS;
}
