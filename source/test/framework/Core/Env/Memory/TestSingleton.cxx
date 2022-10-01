#include "MACE/Env/BasicEnv.hxx"
#include "MACE/Env/Memory/Singleton.hxx"

class NullSingleton final : public MACE::Env::Memory::Singleton<NullSingleton> {
    friend MACE::Env::Memory::SingletonFactory;

private:
    NullSingleton() = default;
};

int main(int /* argc */, char* /* argv */[]) {
    // MACE::Env::BasicEnv environment(argc, argv, {});
    NullSingleton::Instance();
    return EXIT_SUCCESS;
}
