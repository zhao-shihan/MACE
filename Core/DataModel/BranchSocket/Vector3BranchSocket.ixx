namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental Fund_t>
Vector3BranchSocket<Fund_t>::Vector3BranchSocket(const TString& branchName, const std::array<TString, 3>& leafList, const std::array<Fund_t, 3>& defaultValues) :
    IBranchSocket<TEveVectorT<Fund_t>>(branchName),
    fLeafList(leafList[0] + '/' + GetBranchTypeName<Fund_t>() + ':' + leafList[1] + ':' + leafList[2]),
    fVector3(defaultValues.data()) {}

} // namespace MACE::Core::DataModel::BranchSocket
