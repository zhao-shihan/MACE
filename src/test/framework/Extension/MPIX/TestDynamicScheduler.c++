#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/Execution/DynamicScheduler.h++"
#include "MACE/Extension/MPIX/Execution/Executor.h++"

#include "fmt/format.h"

#include <string>
#include <thread>

using namespace MACE;
using namespace std::chrono_literals;

auto main(int argc, char* argv[]) -> int {
    MACE::Env::MPIEnv env{argc, argv, {}};

    MPIX::Executor executor{std::stoll(argv[1]), MPIX::ScheduleBy<MPIX::DynamicScheduler>{}};

    executor.PrintProgressModulo(-1);
    executor.Execute([&](auto i) {
        fmt::println("{},{}", i, env.CommWorldRank());
    });

    std::this_thread::sleep_for(3s);

    executor.PrintProgressModulo(0);
    executor.Execute([&](auto i) {
        std::this_thread::sleep_for(500ms);
        fmt::println("{},{}", i, env.CommWorldRank());
    });

    executor.Execute([&](auto i) {
        std::this_thread::sleep_for(500ms);
        fmt::println("{},{}", i, env.CommWorldRank());
    });

    executor.PrintProgressModulo(1);
    executor.Execute([&](auto) {
        std::this_thread::sleep_for(500ms);
    });

    return EXIT_SUCCESS;
}
