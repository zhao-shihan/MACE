#pragma once

#include "DataModel/Interface/BranchSocket.hxx"

template<typename Class_t>
class MACE::DataModel::ClassBranchSocket final :
    public MACE::DataModel::Interface::BranchSocket<Class_t, Class_t**> {
    static_assert(std::is_class_v<Class_t>,
        "Class_t should be a class type!");
public:
    template<typename... Args>
    ClassBranchSocket(const char* branchName, Args&&... args);
    ~ClassBranchSocket() noexcept;
    ClassBranchSocket(const ClassBranchSocket&) = delete;
    ClassBranchSocket& operator=(const ClassBranchSocket&) = delete;

    [[nodiscard]] Class_t& Value() override { return *fObject; }
    [[nodiscard]] Class_t** Address() override { return std::addressof(fObject); }

private:
    Class_t* fObject;
};

#include "DataModel/BranchSocket/ClassBranchSocket.ixx"

namespace MACE::DataModel {
    inline namespace BranchSocket {
        using Vector2FBranchSocket = ClassBranchSocket<TEveVector2F>;
        using Vector3FBranchSocket = ClassBranchSocket<TEveVectorF>;
    }
}
