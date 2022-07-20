#include "MACE/Environment/Resource/detail/SingletonFactory.hxx"

namespace MACE::Environment::Resource::Detail {

ObserverPtr<SingletonFactory> SingletonFactory::fgInstance = nullptr;

SingletonFactory::SingletonFactory() :
    fSingletonInstanceList(),
    fSingletonTypeCollection() {
    if (fgInstance != nullptr) {
        throw std::logic_error("MACE::Environment::Resource::SingletonFactory: Trying to construct twice");
    }
    fgInstance = this;
}

SingletonFactory::~SingletonFactory() {
    for (auto&& instance : std::as_const(fSingletonInstanceList)) {
        delete instance.first;
    }
}

} // namespace MACE::Environment::Resource::Detail
