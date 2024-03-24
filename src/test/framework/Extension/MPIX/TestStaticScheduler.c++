#include "MACE/Env/MPIEnv.h++"
#include "MACE/Env/Print.h++"
#include "MACE/Extension/MPIX/Execution/Executor.h++"
#include "MACE/Extension/MPIX/Execution/StaticScheduler.h++"

#include <string>
#include <thread>

using namespace MACE;
using namespace std::chrono_literals;

auto main(int argc, char* argv[]) -> int {
    MACE::Env::MPIEnv env{argc, argv, {}};

    MPIX::Executor<unsigned short> executor{MPIX::ScheduleBy<MPIX::StaticScheduler>{}};

    const auto n{std::stoll(argv[1])};

    executor.PrintProgressModulo(-1);
    executor.Execute(n,
                     [&](auto i) {
                         std::this_thread::sleep_for(500ms);
                         Env::PrintLn("{},{}", i, env.CommWorldRank());
                     });

    executor.Execute(n,
                     [&](auto i) {
                         std::this_thread::sleep_for(500ms);
                         Env::PrintLn("{},{}", i, env.CommWorldRank());
                     });

    executor.PrintProgressModulo(1);
    executor.Execute(n,
                     [&](auto) {
                         std::this_thread::sleep_for(500ms);
                     });

    return EXIT_SUCCESS;
}
