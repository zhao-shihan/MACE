#include "MACE/Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"

namespace MACE::Core::DataModel::BranchSocket {

ShortStringBranchSocket::ShortStringBranchSocket(const std::string& branchName, const ShortString& defaultString) :
    BranchSocketBase<ShortStringBranchSocket, ShortString>(branchName),
    fLeafName(branchName + "/C"),
    fString(defaultString) {}

} // namespace MACE::Core::DataModel::BranchSocket
