#include "MACE/Environment/BasicEnvironment.hxx"
#include "MACE/Environment/Memory/FreeSingleton.hxx"

class NullFreeSingleton : public MACE::Environment::Memory::FreeSingleton<NullFreeSingleton> {};

int main(int /* argc */, char* /* argv */[]) {
    // MACE::Environment::BasicEnvironment environment(argc, argv, {});
    NullFreeSingleton::Instance();
    return EXIT_SUCCESS;
}
