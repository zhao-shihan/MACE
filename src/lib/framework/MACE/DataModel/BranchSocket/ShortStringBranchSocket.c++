#include "MACE/DataModel/BranchSocket/ShortStringBranchSocket.h++"

namespace MACE::DataModel::inline BranchSocket {

ShortStringBranchSocket::ShortStringBranchSocket(const std::string& branchName, const String15& defaultString) :
    BranchSocketBase<ShortStringBranchSocket, String15>(branchName),
    fLeafName(branchName + "/C"),
    fString(defaultString) {}

} // namespace MACE::DataModel::inline BranchSocket
