namespace MACE::Env::Memory {

template<class ADerived>
internal::WeakSingletonPool::Node* WeakSingleton<ADerived>::fgInstanceNode = nullptr;

template<class ADerived>
WeakSingleton<ADerived>::WeakSingleton() :
    WeakSingletonBase() {
    static_assert(WeakSingletonified<ADerived>);
    if (auto& weakSingletonPool = internal::WeakSingletonPool::Instance();
        not weakSingletonPool.Contains<ADerived>()) {
        fgInstanceNode = &weakSingletonPool.Insert<ADerived>(static_cast<ADerived*>(this));
    } else {
        throw std::logic_error(
            std::string("MACE::Env::Memory::WeakSingleton::WeakSingleton(): "
                        "Trying to construct ")
                .append(typeid(ADerived).name())
                .append(" (mute singleton in environment) twice"));
    }
}

template<class ADerived>
WeakSingleton<ADerived>::~WeakSingleton() {
    *fgInstanceNode = nullptr;
    fgInstanceNode = nullptr;
}

} // namespace MACE::Env::Memory
