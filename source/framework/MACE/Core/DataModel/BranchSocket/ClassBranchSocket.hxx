#pragma once

#include "MACE/Core/DataModel/BranchSocket/IBranchSocket.hxx"

namespace MACE::Core::DataModel::BranchSocket {

template<class ClassT>
requires std::is_class_v<ClassT>
class ClassBranchSocket final : public IBranchSocket<ClassT> {
public:
    template<typename... Args>
    ClassBranchSocket(const TString& branchName, Args&&... args);
    ~ClassBranchSocket() noexcept;
    ClassBranchSocket(const ClassBranchSocket&) = delete;
    ClassBranchSocket& operator=(const ClassBranchSocket&) = delete;

    const ClassT& GetValue() const override { return *fObject; }
    void SetValue(const ClassT& object) override { *fObject = object; }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, std::addressof(fObject), 256000, 0); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, std::addressof(fObject)); }

private:
    ClassT* fObject;
};

} // namespace MACE::Core::DataModel::BranchSocket

#include "MACE/Core/DataModel/BranchSocket/ClassBranchSocket.inl"
