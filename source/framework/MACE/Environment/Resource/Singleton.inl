namespace MACE::Environment::Memory {

template<class ADerived>
ObserverPtr<Detail::SingletonFactory::InstanceNode> Singleton<ADerived>::fgInstanceNode = nullptr;

template<class ADerived>
ADerived& Singleton<ADerived>::Instance() {
    if (fgInstanceNode == nullptr) [[unlikely]] {
        Detail::SingletonFactory::Instance().Instantiate<ADerived>();
    }
    return *static_cast<ObserverPtr<ADerived>>(fgInstanceNode->first);
}

template<class ADerived>
Singleton<ADerived>::Singleton() {
    if (fgInstanceNode != nullptr) {
        throw std::logic_error(std::string("MACE::Environment::Memory::Singleton: Trying to construct ")
                                   .append(typeid(ADerived).name())
                                   .append(" (environmental singleton) twice"));
    }
}

template<class ADerived>
Singleton<ADerived>::~Singleton() {
    if (fgInstanceNode != nullptr) {
        *fgInstanceNode = {nullptr, nullptr};
        fgInstanceNode = nullptr;
    }
}

} // namespace MACE::Environment::Memory
