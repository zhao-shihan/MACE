#include "MACE/DataModel/BranchSocket2/ShortStringBranchSocket2.hxx"

namespace MACE::DataModel::inline BranchSocket {

ShortStringBranchSocket2::ShortStringBranchSocket2(std::string name, ShortString defaultString) :
    BranchSocketBase2<ShortStringBranchSocket2, ShortString>(std::move(name)),
    fLeafName(Name() + "/C"),
    fString(std::move(defaultString)) {}

} // namespace MACE::DataModel::inline BranchSocket
