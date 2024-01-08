#include "MACE/Env/MPIEnv.h++"
#include "MACE/Utility/MPIUtil/Scheduler.h++"

#include "fmt/format.h"

#include <string>
#include <thread>

using namespace MACE;

auto main(int argc, char* argv[]) -> int {
    MACE::Env::MPIEnv env{argc, argv, {}};

    MPIUtil::Scheduler scheduler{std::stoll(argv[1])};
    // scheduler.PrintProgressModulo(0);
    for (auto i{scheduler.Next()}; i.has_value(); i = scheduler.Next()) {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1000ms);
        fmt::println("{} by {}", *i, env.CommWorldRank());
    }

    return EXIT_SUCCESS;
}
