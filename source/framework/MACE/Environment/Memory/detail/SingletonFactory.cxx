#include "MACE/Environment/Memory/detail/ISingletonBase.hxx"
#include "MACE/Environment/Memory/detail/SingletonFactory.hxx"

namespace MACE::Environment::Memory::Detail {

ObserverPtr<SingletonFactory> SingletonFactory::fgInstance = nullptr;

SingletonFactory::SingletonFactory() :
    fSingletonInstanceList(),
    fSingletonTypeCollection() {
    if (fgInstance != nullptr) {
        throw std::logic_error("MACE::Environment::Memory::SingletonFactory: Trying to construct twice");
    }
    fgInstance = this;
}

SingletonFactory::~SingletonFactory() {
    for (auto&& [_, singletonBase] : std::as_const(fSingletonInstanceList)) {
        delete singletonBase;
    }
}

} // namespace MACE::Environment::Memory::Detail
