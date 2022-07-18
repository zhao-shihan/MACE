#pragma once

#include "MACE/Core/DataModel/BranchSocket/IBranchSocket.hxx"

namespace MACE::Core::DataModel::BranchSocket {

template<class AClass>
requires std::is_class_v<AClass>
class ClassBranchSocket final : public IBranchSocket<AClass> {
public:
    template<typename... Args>
    ClassBranchSocket(const TString& branchName, Args&&... args);
    ~ClassBranchSocket() noexcept;
    ClassBranchSocket(const ClassBranchSocket&) = delete;
    ClassBranchSocket& operator=(const ClassBranchSocket&) = delete;

    const AClass& GetValue() const override { return *fObject; }
    void SetValue(const AClass& object) override { *fObject = object; }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, std::addressof(fObject), 256000, 0); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, std::addressof(fObject)); }

private:
    AClass* fObject;
};

} // namespace MACE::Core::DataModel::BranchSocket

#include "MACE/Core/DataModel/BranchSocket/ClassBranchSocket.inl"
