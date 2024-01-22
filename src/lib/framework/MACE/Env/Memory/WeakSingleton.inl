namespace MACE::Env::Memory {

template<typename ADerived>
void** WeakSingleton<ADerived>::fgInstance{};

template<typename ADerived>
WeakSingleton<ADerived>::WeakSingleton() :
    WeakSingletonBase{} {
    static_assert(WeakSingletonified<ADerived>);
    if (auto& weakSingletonPool = internal::WeakSingletonPool::Instance();
        not weakSingletonPool.Contains<ADerived>()) {
        fgInstance = &weakSingletonPool.Insert<ADerived>(static_cast<ADerived*>(this));
    } else {
        throw std::logic_error{fmt::format("MACE::Env::Memory::WeakSingleton::WeakSingleton(): "
                                           "Trying to construct {} (weak singleton in environment) twice",
                                           typeid(ADerived).name())};
    }
}

template<typename ADerived>
WeakSingleton<ADerived>::~WeakSingleton() {
    UpdateInstance();
    *fgInstance = nullptr;
}

template<typename ADerived>
MACE_ALWAYS_INLINE auto WeakSingleton<ADerived>::Instantiated() -> bool {
    const auto status{UpdateInstance()};
    return status == Status::Available or
           status == Status::Expired;
}

template<typename ADerived>
auto WeakSingleton<ADerived>::UpdateInstance() -> Status {
    if (fgInstance == nullptr) [[unlikely]] {
        if (const auto optionalNode{internal::WeakSingletonPool::Instance().Find<ADerived>()};
            optionalNode.has_value()) {
            fgInstance = &optionalNode->get();
        } else {
            return Status::NotInstantiated;
        }
    }
    if (*fgInstance == nullptr) {
        return Status::Expired;
    } else {
        return Status::Available;
    }
}

} // namespace MACE::Env::Memory
