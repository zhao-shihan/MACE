#include "MACE/Env/BasicEnv.hxx"
#include "MACE/Env/Memory/FreeSingleton.hxx"

class NullFreeSingleton : public MACE::Env::Memory::FreeSingleton<NullFreeSingleton> {};

int main(int /* argc */, char* /* argv */[]) {
    // MACE::Env::BasicEnv environment(argc, argv, {});
    NullFreeSingleton::Instance();
    return EXIT_SUCCESS;
}
