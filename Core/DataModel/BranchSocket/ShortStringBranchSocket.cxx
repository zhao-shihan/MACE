#include "Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"

using MACE::Core::DataModel::BranchSocket::ShortStringBranchSocket;

ShortStringBranchSocket::ShortStringBranchSocket(const TString& branchName, const ShortString& defaultString) :
    IBranchSocket<ShortString>(branchName),
    fLeafName(branchName + "/C"),
    fString(defaultString) {}
