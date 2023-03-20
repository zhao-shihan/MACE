#pragma once

#include "MACE/DataModel/BranchSocketBase.hxx"

#include "gsl/gsl"

#include <concepts>
#include <string>
#include <tuple>

namespace MACE::DataModel::inline BranchSocket {

template<class AClass>
    requires std::assignable_from<AClass, AClass>
class ClassBranchSocket final : public BranchSocketBase<ClassBranchSocket<AClass>, AClass> {
public:
    template<typename... Args>
    ClassBranchSocket(const std::string& branchName, std::tuple<Args&&...> argTuple);
    ~ClassBranchSocket();

    const auto& Value() const { return *fObject; }
    void Value(const AClass& object) { *fObject = object; }

    void CreateBranch(TTree& tree) { tree.Branch(this->fBranchName.c_str(), &fObject, 256000, 0); }
    void ConnectToBranch(TTree& tree) { tree.SetBranchAddress(this->fBranchName.c_str(), &fObject); }

private:
    const gsl::owner<AClass*> fObject;
};

} // namespace MACE::DataModel::inline BranchSocket

#include "MACE/DataModel/BranchSocket/ClassBranchSocket.inl"
