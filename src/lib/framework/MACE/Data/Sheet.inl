namespace MACE::Data {

template<Modelizable... Ts>
Sheet<Ts...>::Row::Row(gsl::index index, const DataSource& data) :
    fIndex{index},
    fData{&data} {}

template<Modelizable... Ts>
auto Sheet<Ts...>::Row::Get() const {
    if (std::ranges::any_of(fData->Status(), [](auto s) { return s == false; })) {
        throw std::logic_error{"MACE::Data::Sheet<Ts...>::DataSource: "
                               "trying to access disabled field"};
    }
    return fData->Fetch(fIndex);
}

template<Modelizable... Ts>
template<gsl::index... Is>
auto Sheet<Ts...>::Row::Get() const {
    if ((... or (std::get<Is>(fData->Status()) == false))) {
        throw std::logic_error{"MACE::Data::Sheet<Ts...>::DataSource: "
                               "trying to access disabled field"};
    }
    return std::move(fData->Fetch(fIndex)).template Get<Is...>();
}

template<Modelizable... Ts>
Sheet<Ts...>::Sheet(const std::string& name, const std::string& file) :
    Sheet{name, {file}} {}

template<Modelizable... Ts>
Sheet<Ts...>::Sheet(const std::string& name, std::initializer_list<std::string> files) :
    Sheet{name, files} {}

template<Modelizable... Ts>
template<std::ranges::input_range R>
    requires std::same_as<std::decay_t<std::ranges::range_value_t<R>>, std::string>
Sheet<Ts...>::Sheet(const std::string& name, const R& files) :
    fRow{},
    fData{name, files} {
    fRow.reserve(fData.ChainEntries());
    for (gsl::index i{0}; i < stdx::to_signed(fData.ChainEntries()); ++i) {
        fRow.emplace_back(i, fData);
    }
    fRow.shrink_to_fit();
}

template<Modelizable... Ts>
Sheet<Ts...>::DataSource::DataSource(const std::string& name, std::initializer_list<std::string> files) :
    DataSource{name, files} {}

template<Modelizable... Ts>
template<std::ranges::input_range R>
    requires std::same_as<std::decay_t<std::ranges::range_value_t<R>>, std::string>
Sheet<Ts...>::DataSource::DataSource(const std::string& name, const R& files) :
    fChain{[&] {
        const auto chain = std::make_unique<TChain>(name.c_str(), "", TChain::kWithoutGlobalRegistration);
        chain->ResetBit(TObject::kMustCleanup);
        for (auto&& file : files) {
            chain->Add(file.c_str());
        }
        return chain;
    }()},
    fChainEntries{fChain->GetEntries()},
    fEntry4Chain{},
    fBranchAddressHelper{},
    fExtension{},
    fStatus{},
    fFetchedIndex{},
    fFetchedEntry{nullptr} {
    SetAllBranchAddress();
    fChain->EnableCache();
    fChain->AddBranchToCache("*", true);
}

template<Modelizable... Ts>
auto Sheet<Ts...>::DataSource::Fetch(gsl::index i) const {
    if (i == fFetchedIndex and fFetchedEntry != nullptr) {
        return *fFetchedEntry;
    }
    if (i >= 0) {
        if (fChain->GetEntry(i) == 0) {
            throw std::out_of_range{fmt::format("MACE::Data::Sheet::DataSource::Fetch: i={} is out of range", i)};
        }
        fFetchedEntry = std::addressof(fEntry4Chain);
    } else {
        fFetchedEntry = std::addressof(fExtension.at(~i));
    }
    fFetchedIndex = i;
    return *fFetchedEntry;
}

template<Modelizable... Ts>
template<gsl::index... Is>
auto Sheet<Ts...>::DataSource::Enable() const -> void {
    (..., fChain->SetBranchStatus(Model<Ts...>::template Name<Is>(), true));
    SetAllBranchAddress();
    (..., (std::get<Is>(fStatus) = true));
}

template<Modelizable... Ts>
template<gsl::index... Is>
auto Sheet<Ts...>::DataSource::Disable() const -> void {
    (..., fChain->SetBranchStatus(Model<Ts...>::template Name<Is>(), false));
    SetAllBranchAddress();
    (..., (std::get<Is>(fStatus) = false));
}

template<Modelizable... Ts>
auto Sheet<Ts...>::DataSource::EnableAll() const -> void {
    fChain->SetBranchStatus("*", true);
    SetAllBranchAddress();
    fStatus.fill(true);
}

template<Modelizable... Ts>
auto Sheet<Ts...>::DataSource::SetAllBranchAddress() const -> void {
    [this]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        (...,
         [this] {
             TBranch* branch;
             const auto& name = Model<Ts...>::template Name<Is>();
             switch (fChain->SetBranchAddress(name, fBranchAddressHelper->FieldPointer<Is>(fEntry4Chain), &branch)) {
             case TChain::kMissingBranch:
                 throw std::runtime_error{fmt::format("MACE::Data::Sheet<Ts...>::DataSource: "
                                                      "error occured when setting address for branch \"{}\" of tree \"{}\" "
                                                      "(TChain::SetBranchAddress returned kMissingBranch: Missing branch)",
                                                      name.StringView(), fChain->GetName())};
                 break;
             case TChain::kInternalError:
                 throw std::runtime_error{fmt::format("MACE::Data::Sheet<Ts...>::DataSource: "
                                                      "error occured when setting address for branch \"{}\" of tree \"{}\" "
                                                      "(TChain::SetBranchAddress returned kInternalError: Internal error (could not find the type corresponding to a data type number))",
                                                      name.StringView(), fChain->GetName())};
                 break;
             case TChain::kMissingCompiledCollectionProxy:
                 throw std::runtime_error{fmt::format("MACE::Data::Sheet<Ts...>::DataSource: "
                                                      "error occured when setting address for branch \"{}\" of tree \"{}\" "
                                                      "(TChain::SetBranchAddress returned kMissingCompiledCollectionProxy: Missing compiled collection proxy for a compiled collection)",
                                                      name.StringView(), fChain->GetName())};
                 break;
             case TChain::kMismatch:
                 throw std::runtime_error{fmt::format("MACE::Data::Sheet<Ts...>::DataSource: "
                                                      "error occured when setting address for branch \"{}\" of tree \"{}\" "
                                                      "(TChain::SetBranchAddress returned kMismatch: Non-Class Pointer type given does not match the type expected by the branch",
                                                      name.StringView(), fChain->GetName())};
                 break;
             case TChain::kClassMismatch:
                 throw std::runtime_error{fmt::format("MACE::Data::Sheet<Ts...>::DataSource: "
                                                      "error occured when setting address for branch \"{}\" of tree \"{}\" "
                                                      "(TChain::SetBranchAddress returned kClassMismatch: Class Pointer type given does not match the type expected by the branch",
                                                      name.StringView(), fChain->GetName())};
                 break;
             }
             branch->SetAutoDelete(false);
         }());
    }(gslx::make_index_sequence<Model<Ts...>::NField()>());
}

} // namespace MACE::Data
