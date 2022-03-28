#pragma once

#include "Core/DataModel/IBranchSocket.hxx"

namespace MACE::Core::DataModel::BranchSocket {

template<typename Class_t>
concept IsClass = std::is_class_v<Class_t>;

template<IsClass Class_t>
class ClassBranchSocket final : public IBranchSocket<Class_t> {
public:
    template<typename... Args>
    ClassBranchSocket(const char* branchName, Args&&... args);
    ~ClassBranchSocket() noexcept;
    ClassBranchSocket(const ClassBranchSocket&) = delete;
    ClassBranchSocket& operator=(const ClassBranchSocket&) = delete;

    [[nodiscard]] const Class_t& GetValue() const override { return *fObject; }
    void SetValue(const Class_t& object) override { *fObject = object; }

    void CreateBranch(TTree& tree) override { tree.Branch(fBranchName, std::addressof(fObject), 256000, 0); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(fBranchName, std::addressof(fObject)); }

private:
    const TString fBranchName;
    Class_t* fObject;
};

} // namespace MACE::Core::DataModel::BranchSocket

#include "Core/DataModel/BranchSocket/ClassBranchSocket.ixx"
