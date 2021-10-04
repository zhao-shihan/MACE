#include "hit/Manager.hh"

using namespace MACE::DataModel::Hit;

Manager* Manager::Instance() {
    static Manager instance;
    return &instance;
}