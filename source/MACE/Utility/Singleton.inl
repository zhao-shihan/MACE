namespace MACE::Utility {

template<class DerivedT>
typename Singleton<DerivedT>::Signature Singleton<DerivedT>::fgSignature;

template<class DerivedT>
void Singleton<DerivedT>::Signature::Instantiate() {
    std::call_once(fInstantiateOnceFlag, [this] {
        fInstance = new DerivedT();
    });
}

template<class DerivedT>
DerivedT& Singleton<DerivedT>::Instance() {
    if (fgSignature.NotInstantiated()) [[unlikely]] {
        fgSignature.Instantiate();
    }
    return fgSignature.GetInstance();
}

} // namespace MACE::Utility
