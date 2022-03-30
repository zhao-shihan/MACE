#pragma once

#include "Core/DataModel/BranchSocket/IBranchSocket.hxx"

namespace MACE::Core::DataModel::BranchSocket {

template<class Class_t>
requires std::is_class_v<Class_t>
class ClassBranchSocket final : public IBranchSocket<Class_t> {
public:
    template<typename... Args>
    ClassBranchSocket(const TString& branchName, Args&&... args);
    ~ClassBranchSocket() noexcept;
    ClassBranchSocket(const ClassBranchSocket&) = delete;
    ClassBranchSocket& operator=(const ClassBranchSocket&) = delete;

    const Class_t& GetValue() const override { return *fObject; }
    void SetValue(const Class_t& object) override { *fObject = object; }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, std::addressof(fObject), 256000, 0); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, std::addressof(fObject)); }

private:
    Class_t* fObject;
};

} // namespace MACE::Core::DataModel::BranchSocket

#include "Core/DataModel/BranchSocket/ClassBranchSocket.ixx"
