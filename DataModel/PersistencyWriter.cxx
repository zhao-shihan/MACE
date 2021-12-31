#include <iostream>

#include "DataModel/PersistencyWriter.hxx"

using namespace MACE::DataModel;

PersistencyWriter::PersistencyWriter() :
    PersistencyHandler(),
    fTreeAndBehaviours(0) {}

PersistencyWriter::PersistencyWriter(const char* fileName) :
    PersistencyHandler(),
    fTreeAndBehaviours(0) {
    PersistencyWriter::Open(fileName);
}

PersistencyWriter::~PersistencyWriter() {
    if (!fTreeAndBehaviours.empty()) {
        std::cerr << "Warning from MACE::DataModel::PersistencyWriter::~PersistencyWriter : "
            "Some trees are not written to disk, they are lost." << std::endl;
    }
}

void PersistencyWriter::Close(Option_t* option) {
    if (!fTreeAndBehaviours.empty()) {
        std::cerr << "Warning from MACE::DataModel::PersistencyWriter::Close : "
            "Some trees are not written to disk, they are lost." << std::endl;
    }
    PersistencyHandler::Close(option);
}

void PersistencyWriter::WriteTrees(Int_t option, Int_t bufsize) {
    if (fFile == nullptr) {
        std::cerr << "Warning from MACE::DataModel::PersistencyWriter::WriteTrees : "
            "Current file does not exist. Nothing was done." << std::endl;
        return;
    }
    if (fFile->IsOpen()) {
        for (auto&& tree : fTreeAndBehaviours) {
            tree.first->Write(nullptr, option, bufsize);
            if (tree.second == kDeleteAfterWrite) {
                delete tree.first;
            }
        }
        fTreeAndBehaviours.clear();
    } else {
        std::cerr << "Warning from MACE::DataModel::PersistencyWriter::WriteTrees : "
            "... How could you close the file without deleting it and setting it to nullptr "
            "(this is the behavior of the Close(...) function)? If you did not intend to do this, "
            "please contact the developer. " << std::endl;
    }
}