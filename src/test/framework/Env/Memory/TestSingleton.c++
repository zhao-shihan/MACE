#include "MACE/Env/BasicEnv.h++"
#include "MACE/Env/Memory/Singleton.h++"

class NullSingleton final : public MACE::Env::Memory::Singleton<NullSingleton> {
    friend MACE::Env::Memory::SingletonInstantiator;

private:
    NullSingleton() = default;
};

int main(int /* argc */, char* /* argv */[]) {
    // MACE::Env::BasicEnv environment(argc, argv, {});
    NullSingleton::Instance();
    return EXIT_SUCCESS;
}
