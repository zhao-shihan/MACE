#include "MACE/Environment/Memory/detail/ISingletonBase.hxx"
#include "MACE/Environment/Memory/detail/SingletonFactory.hxx"

namespace MACE::Environment::Memory::Detail {

ObserverPtr<SingletonFactory> SingletonFactory::fgInstance = nullptr;

SingletonFactory::SingletonFactory() :
    NonCopyableBase(),
    fInstancePool() {
    if (fgInstance != nullptr) {
        throw std::logic_error("MACE::Environment::Memory::SingletonFactory: Trying to construct twice");
    }
    fgInstance = this;
}

SingletonFactory::~SingletonFactory() {
    for (auto&& [_, singletonBase] : fInstancePool) {
        delete singletonBase;
    }
}

} // namespace MACE::Environment::Memory::Detail
