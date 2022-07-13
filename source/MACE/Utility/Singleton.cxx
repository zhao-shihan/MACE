#include "MACE/Utility/Singleton.hxx"

namespace MACE::Utility::Detail {

std::vector<ObserverPtr<ISingletonBase*>> SingletonGC::fgInstancesCollection{};

SingletonGC::SingletonGC() {
    std::atexit(DoSingletonGC);
}

void SingletonGC::AddInstance(ObserverPtr<ISingletonBase*> ptrToStaticInstancePtr) {
    fgInstancesCollection.emplace_back(ptrToStaticInstancePtr);
}

void SingletonGC::DoSingletonGC() {
    const auto crbegin = fgInstancesCollection.crbegin();
    const auto crend = fgInstancesCollection.crend();
    for (auto instance = crbegin; instance != crend; ++instance) {
        delete **instance;
    }
}

ISingletonBase::ISingletonBase(ObserverPtr<ISingletonBase*> ptrToStaticInstancePtr) {
    static SingletonGC gSingletonGC;
    SingletonGC::AddInstance(ptrToStaticInstancePtr);
}

ISingletonBase::~ISingletonBase() = default;

} // namespace MACE::Utility::Detail
