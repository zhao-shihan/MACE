#include "MACE/Env/BasicEnv.hxx"
#include "MACE/Env/Memory/PassiveSingleton.hxx"

class NullPassiveSingleton : public MACE::Env::Memory::PassiveSingleton<NullPassiveSingleton> {};

int main(int /* argc */, char* /* argv */[]) {
    // MACE::Env::BasicEnv environment(argc, argv, {});
    NullPassiveSingleton::Instance();
    return EXIT_SUCCESS;
}
