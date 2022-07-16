#include "MACE/Environment/Resource/SingletonFactory.hxx"

namespace MACE::Environment::Resource {

SingletonFactory::SingletonFactory() :
    fSingletonInstanceList(),
    fSingletonTypeCollection() {
    static ObserverPtr<SingletonFactory> gInstance = nullptr;
    if (gInstance == nullptr) {
        gInstance = this;
    } else {
        throw std::logic_error("MACE::Environment::Resource::SingletonFactory constructed twice");
    }
}

SingletonFactory::~SingletonFactory() {
    for (auto&& instance : std::as_const(fSingletonInstanceList)) {
        delete instance.first;
    }
}

} // namespace MACE::Environment::Resource
