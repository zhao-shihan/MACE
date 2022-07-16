#include "MACE/Environment/Resource/SingletonFactory.hxx"

namespace MACE::Environment::Resource {

ObserverPtr<SingletonFactory> SingletonFactory::fgInstance = nullptr;

SingletonFactory::SingletonFactory() :
    fSingletonInstanceList(),
    fSingletonTypeCollection() {
    if (fgInstance == nullptr) {
        fgInstance = this;
    } else {
        throw std::logic_error("MACE::Environment::Resource::SingletonFactory: Trying to construct twice");
    }
}

SingletonFactory::~SingletonFactory() {
    for (auto&& instance : std::as_const(fSingletonInstanceList)) {
        delete instance.first;
    }
}

} // namespace MACE::Environment::Resource
