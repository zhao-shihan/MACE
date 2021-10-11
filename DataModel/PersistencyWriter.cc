#include <iostream>

#include "DataModel/PersistencyWriter.hh"

using namespace MACE::DataModel;

PersistencyWriter::PersistencyWriter() :
    fFile(nullptr),
    fTrees(0),
    fPrefix(""),
    fSuffix("") {}

PersistencyWriter::~PersistencyWriter() {
    if (!fTrees.empty()) {
        std::cerr << "Warning from MACE::DataModel::PersistencyWriter::~PersistencyWriter : "
            "Some trees are not written to disk, they are lost." << std::endl;
    }
    if (fFile != nullptr) {
        if (fFile->IsOpen()) {
            std::cerr << "Warning from MACE::DataModel::PersistencyWriter::~PersistencyWriter : "
                "We think you forgot to close the file! Although we will close it for you, "
                "it is recommended for you to explicitly call the Close(...) function somewhere "
                "to close the file, in order to control the behaviour fully." << std::endl;
            fFile->Close();
        } else {
            std::cerr << "Warning from MACE::DataModel::PersistencyWriter::~PersistencyWriter : "
                "... How could you close the file without deleting it and setting it to nullptr "
                "(this is the behavior of the Close(...) function)? If you did not intend to do this, "
                "please contact the developer. " << std::endl;
        }
        delete fFile;
    }
}

void PersistencyWriter::Open(const char* fileName) {
    if (fFile != nullptr) {
        if (fFile->IsOpen()) {
            std::cerr << "Warning from MACE::DataModel::PersistencyWriter::Open : "
                "Current file is not closed. Nothing was done." << std::endl;
            return;
        } else {
            std::cerr << "Warning from MACE::DataModel::PersistencyWriter::Open : "
                "... How could you close the file without deleting it and setting it to nullptr "
                "(this is the behavior of the Close(...) function)? If you did not intend to do this, "
                "please contact the developer. " << std::endl;
        }
        delete fFile;
    }
    fFile = new TFile(fileName, "RECREATE");
}

void PersistencyWriter::Close(Option_t* option) {
    if (fFile == nullptr) {
        std::cerr << "Warning from MACE::DataModel::PersistencyWriter::Close : "
            "Current file does not exist. Nothing was done." << std::endl;
        return;
    }
    if (fFile->IsOpen()) {
        fFile->Close(option);
    } else {
        std::cerr << "Warning from MACE::DataModel::PersistencyWriter::Close : "
            "... How could you close the file without deleting it and setting it to nullptr "
            "(this is the behavior of the Close(...) function)? If you did not intend to do this, "
            "please contact the developer. " << std::endl;
    }
    if (!fTrees.empty()) {
        std::cerr << "Warning from MACE::DataModel::PersistencyWriter::Close : "
            "Some trees are not written to disk, they are lost." << std::endl;
    }
    delete fFile;
    fFile = nullptr;
}

void PersistencyWriter::WriteTrees(Int_t option, Int_t bufsize) {
    if (fFile == nullptr) {
        std::cerr << "Warning from MACE::DataModel::PersistencyWriter::WriteTrees : "
            "Current file does not exist. Nothing was done." << std::endl;
        return;
    }
    if (fFile->IsOpen()) {
        for (auto tree : fTrees) {
            tree->Write(nullptr, option, bufsize);
            delete tree;
        }
        fTrees.clear();
    } else {
        std::cerr << "Warning from MACE::DataModel::PersistencyWriter::WriteTrees : "
            "... How could you close the file without deleting it and setting it to nullptr "
            "(this is the behavior of the Close(...) function)? If you did not intend to do this, "
            "please contact the developer. " << std::endl;
    }
}