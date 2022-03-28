#include "Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"

using MACE::Core::DataModel::BranchSocket::ShortStringBranchSocket;

ShortStringBranchSocket::ShortStringBranchSocket(const char* branchName, const char* defaultString) :
    IBranchSocket<const char*, false>(),
    fBranchName(branchName),
    fBranchNameWithType(fBranchName + "/C"),
    fString(defaultString) {}
