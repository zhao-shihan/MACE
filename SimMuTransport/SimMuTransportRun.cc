#include "RunManager.hh"

using namespace MACE::SimMuTransport;

int main(int argc, char** argv) {
    auto runManager = RunManager::Instance();
    runManager->Initialize(&argc, &argv);
    runManager->Run();
    runManager->Finalize();
    delete runManager;
    return EXIT_SUCCESS;
}

