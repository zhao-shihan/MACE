#include "RunManager.hxx"

using namespace MACE::Simulation::SimMTransport;

int main(int argc, char** argv) {
    auto runManager = RunManager::Instance();
    runManager->Initialize(argc, argv);
    runManager->Run();
    runManager->Finalize();
    delete runManager;
    return EXIT_SUCCESS;
}
