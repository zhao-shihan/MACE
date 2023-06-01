#include "MACE/Env/BasicEnv.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"

class NullPassiveSingleton : public MACE::Env::Memory::PassiveSingleton<NullPassiveSingleton> {};

int main(int /* argc */, char* /* argv */[]) {
    // MACE::Env::BasicEnv environment(argc, argv, {});
    NullPassiveSingleton::Instance();
    return EXIT_SUCCESS;
}
