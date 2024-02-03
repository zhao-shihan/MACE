#include "MACE/Env/BasicEnv.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Utility/CreateTemporaryFile.h++"

#include <chrono>
#include <cstdio>
#include <random>
#include <stdexcept>

namespace MACE::inline Utility {

auto CreateTemporaryFile(std::string_view signature, std::filesystem::path extension) -> std::filesystem::path {
    std::minstd_rand random;
    if (std::random_device randomDevice;
        randomDevice.Entropy() > 0) {
        random.seed(randomDevice());
    } else {
        random.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    }

    std::filesystem::path path;
    std::FILE* file;
    for (int i{}; i < 1'000'000; ++i) {
        path = std::filesystem::temp_directory_path() /
               fmt::format("{}{}{:x}.", Env::BasicEnv::Instance().Argv()[0], signature, random());
        if (Env::MPIEnv::Available()) {
            path.concat(fmt::format("mpi{}.", Env::MPIEnv::Instance().CommWorldRank()));
        }
        path.replace_extension(extension);
        file = std::fopen(path.generic_string().c_str(), "wx");
        if (file) { break; }
    }
    if (file == nullptr) { throw std::runtime_error{"failed to create a temporary file"}; }
    std::fclose(file);

    return path;
}

} // namespace MACE::inline Utility
