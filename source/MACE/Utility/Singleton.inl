namespace MACE::Utility {

template<class DerivedT>
std::once_flag Singleton<DerivedT>::fgInstantiateOnceFlag;
template<class DerivedT>
DerivedT* Singleton<DerivedT>::fgInstance = nullptr;

template<class DerivedT>
Singleton<DerivedT>::Singleton() :
    Detail::ISingletonBase(reinterpret_cast<ObserverPtr<Detail::ISingletonBase*>>(&fgInstance)) {}

template<class DerivedT>
DerivedT& Singleton<DerivedT>::Instance() {
    if (not Instantiated()) [[unlikely]] {
        std::call_once(fgInstantiateOnceFlag, [] {
            fgInstance = new DerivedT();
        });
    }
    return *fgInstance;
}

} // namespace MACE::Utility
