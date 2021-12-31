#pragma once

#include "DataModel/Global.hxx"

template<typename ColumnType>
struct MACE::DataModel::Column {
    const char* const name;
    ColumnType value;
};