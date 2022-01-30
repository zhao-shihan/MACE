#pragma once

#include "DataModel/Global.hxx"

template<typename Value_t>
struct MACE::DataModel::Column {
    const char* const name;
    Value_t value;
};