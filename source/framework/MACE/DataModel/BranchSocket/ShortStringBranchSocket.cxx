#include "MACE/DataModel/BranchSocket/ShortStringBranchSocket.hxx"

namespace MACE::DataModel::BranchSocket {

ShortStringBranchSocket::ShortStringBranchSocket(const std::string& branchName, const ShortString& defaultString) :
    BranchSocketBase<ShortStringBranchSocket, ShortString>(branchName),
    fLeafName(branchName + "/C"),
    fString(defaultString) {}

} // namespace MACE::DataModel::BranchSocket
