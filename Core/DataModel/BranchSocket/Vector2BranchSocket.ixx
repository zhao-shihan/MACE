namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental Fund_t>
Vector2BranchSocket<Fund_t>::Vector2BranchSocket(const TString& branchName, const std::array<TString, 2>& leafList, const std::array<Fund_t, 2>& defaultValues) :
    IBranchSocket<TEveVector2T<Fund_t>>(branchName),
    fLeafList(leafList[0] + '/' + GetBranchTypeName<Fund_t>() + ':' + leafList[1]),
    fVector2(defaultValues.data()) {}

} // namespace MACE::Core::DataModel::BranchSocket
