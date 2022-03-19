#include "DataModel/BranchSocket/ShortStringBranchSocket.hxx"

using namespace MACE::DataModel;

ShortStringBranchSocket::ShortStringBranchSocket(const char* branchName, const char* defaultString) :
    MACE::DataModel::Interface::BranchSocket<const char*, false>(),
    fBranchName(branchName),
    fBranchNameWithType(fBranchName + "/C"),
    fString(defaultString) {}
