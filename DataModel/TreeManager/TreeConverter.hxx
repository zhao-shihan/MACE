#pragma once

#include "DataModel/Global.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::DataModel::TreeManager::TreeConverter final {
public:
    TreeConverter() = delete;

    template<class DataInTree_t, class DataInList_t = DataInTree_t>
    [[nodiscard]] static inline std::vector<std::shared_ptr<DataInList_t>> CreateList(const std::shared_ptr<TTree>& tree);
    template<class DataInTree_t, class DataInList_t = DataInTree_t>
    [[nodiscard]] static inline std::vector<std::shared_ptr<DataInList_t>> CreateList(TTree* tree);

private:
    template<class DataInTree_t, class DataInList_t, typename PointerOfTree_t>
    [[nodiscard]] static std::vector<std::shared_ptr<DataInList_t>> CreateList(PointerOfTree_t tree);
};

#include "DataModel/TreeManager/TreeConverter.ixx"
