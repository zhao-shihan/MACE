#pragma once

#include "DataModel/Global.hh"

template<typename ColumnType>
struct MACE::DataModel::Core::Column {
    const char* const name;
    ColumnType value;
};