namespace MACE::Detector::Description {

inline auto ECAL::MeshManager::Get(const ECAL* ecal) -> const MeshInformation& {
    if (fOutdated) {
        fMesh = ecal->CalculateMeshInformation();
        fOutdated = false;
    }
    return fMesh;
}

inline void ECAL::SetGeometryOutdated() const {
    fMeshManager.SetOutdated();
}

} // namespace MACE::Detector::Description
