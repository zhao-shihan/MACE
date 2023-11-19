namespace MACE::Detector::Description {

inline auto EMC::MeshManager::Get(const EMC* emc) -> const MeshInformation& {
    if (fOutdated) {
        fMesh = emc->ComputeMesh();
        fOutdated = false;
    }
    return fMesh;
}

inline void EMC::SetGeometryOutdated() const {
    fMeshManager.SetOutdated();
}

} // namespace MACE::Detector::Description