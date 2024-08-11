namespace MACE::Detector::Description {

inline auto ECal::MeshManager::Get(const ECal* eCal) -> const MeshInformation& {
    if (fOutdated) {
        fMesh = eCal->ComputeMesh();
        fOutdated = false;
    }
    return fMesh;
}

inline void ECal::SetGeometryOutdated() const {
    fMeshManager.SetOutdated();
}

} // namespace MACE::Detector::Description
