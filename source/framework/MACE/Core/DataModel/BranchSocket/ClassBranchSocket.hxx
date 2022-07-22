#pragma once

#include "MACE/Core/DataModel/BranchSocket/IBranchSocket.hxx"

#include <concepts>
#include <tuple>

namespace MACE::Core::DataModel::BranchSocket {

template<class AClass> // clang-format off
    requires std::assignable_from<AClass, AClass>
class ClassBranchSocket final : public IBranchSocket<AClass> { // clang-format on
public:
    template<typename... Args>
    ClassBranchSocket(const TString& branchName, std::tuple<Args&&...> argTuple);
    ~ClassBranchSocket();
    ClassBranchSocket(const ClassBranchSocket&) = delete;
    ClassBranchSocket& operator=(const ClassBranchSocket&) = delete;

    const AClass& GetValue() const override { return *fObject; }
    void SetValue(const AClass& object) override { *fObject = object; }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, &fObject, 256000, 0); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, &fObject); }

private:
    AClass* fObject;
};

} // namespace MACE::Core::DataModel::BranchSocket

#include "MACE/Core/DataModel/BranchSocket/ClassBranchSocket.inl"
