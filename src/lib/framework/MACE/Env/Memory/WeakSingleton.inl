namespace MACE::Env::Memory {

template<typename ADerived>
internal::WeakSingletonPool::Node* WeakSingleton<ADerived>::fgInstanceNode = nullptr;

template<typename ADerived>
WeakSingleton<ADerived>::WeakSingleton() :
    WeakSingletonBase{} {
    static_assert(WeakSingletonified<ADerived>);
    if (auto& weakSingletonPool = internal::WeakSingletonPool::Instance();
        not weakSingletonPool.Contains<ADerived>()) {
        fgInstanceNode = &weakSingletonPool.Insert<ADerived>(static_cast<ADerived*>(this));
    } else {
        throw std::logic_error{fmt::format("MACE::Env::Memory::WeakSingleton::WeakSingleton(): "
                                           "Trying to construct {} (mute singleton in environment) twice",
                                           typeid(ADerived).name())};
    }
}

template<typename ADerived>
WeakSingleton<ADerived>::~WeakSingleton() {
    *fgInstanceNode = nullptr;
    fgInstanceNode = nullptr;
}

} // namespace MACE::Env::Memory
