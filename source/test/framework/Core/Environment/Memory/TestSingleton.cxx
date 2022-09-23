#include "MACE/Environment/BasicEnvironment.hxx"
#include "MACE/Environment/Memory/Singleton.hxx"

class NullSingleton final : public MACE::Environment::Memory::Singleton<NullSingleton> {
    friend MACE::Environment::Memory::SingletonFactory;

private:
    NullSingleton() = default;
};

int main(int /* argc */, char* /* argv */[]) {
    // MACE::Environment::BasicEnvironment environment(argc, argv, {});
    NullSingleton::Instance();
    return EXIT_SUCCESS;
}
