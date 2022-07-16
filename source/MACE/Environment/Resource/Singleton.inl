namespace MACE::Environment::Resource {

template<class ADerived>
ObserverPtr<ObserverPtr<void>> Singleton<ADerived>::fgInstanceObjectNodePtr = nullptr;

template<class ADerived>
Singleton<ADerived>::~Singleton() {
    if (fgInstanceObjectNodePtr != nullptr) {
        *fgInstanceObjectNodePtr = nullptr;
        fgInstanceObjectNodePtr = nullptr;
    }
}

template<class ADerived>
ADerived& Singleton<ADerived>::Instance() {
    if (fgInstanceObjectNodePtr == nullptr) [[unlikely]] {
        SingletonFactory::Instance().Instantiate<ADerived>();
    }
    return *static_cast<ObserverPtr<ADerived>>(*fgInstanceObjectNodePtr);
}

} // namespace MACE::Environment::Resource
