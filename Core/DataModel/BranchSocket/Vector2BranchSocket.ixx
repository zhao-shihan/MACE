namespace MACE::Core::DataModel::BranchSocket {

template<typename Fund_t>
Vector2BranchSocket<Fund_t>::Vector2BranchSocket(const char* branchName, std::array<const char*, 2> leafList, std::array<Fund_t, 2> defaultValues) :
    IBranchSocket<TEveVector2T<Fund_t>>(),
    fBranchName(branchName),
    fLeafList(leafList.front()),
    fVector2(defaultValues.data()) {
    if constexpr (std::is_same_v<Fund_t, Char_t>) {
        fLeafList += "/B";
    } else if constexpr (std::is_same_v<Fund_t, UChar_t>) {
        fLeafList += "/b";
    } else if constexpr (std::is_same_v<Fund_t, Short_t>) {
        fLeafList += "/S";
    } else if constexpr (std::is_same_v<Fund_t, UShort_t>) {
        fLeafList += "/s";
    } else if constexpr (std::is_same_v<Fund_t, Int_t>) {
        fLeafList += "/I";
    } else if constexpr (std::is_same_v<Fund_t, UInt_t>) {
        fLeafList += "/i";
    } else if constexpr (std::is_same_v<Fund_t, Float_t>) {
        fLeafList += "/F";
    } else if constexpr (std::is_same_v<Fund_t, Double_t>) {
        fLeafList += "/D";
    } else if constexpr (std::is_same_v<Fund_t, Long64_t>) {
        fLeafList += "/L";
    } else if constexpr (std::is_same_v<Fund_t, ULong64_t>) {
        fLeafList += "/l";
    } else if constexpr (std::is_same_v<Fund_t, Long_t>) {
        fLeafList += "/G";
    } else if constexpr (std::is_same_v<Fund_t, ULong_t>) {
        fLeafList += "/g";
    } else if constexpr (std::is_same_v<Fund_t, Bool_t>) {
        fLeafList += "/O";
    }
    fLeafList += ':';
    fLeafList += leafList[1];
}

} // namespace MACE::Core::DataModel::BranchSocket
