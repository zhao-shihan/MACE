namespace MACE::Detector::Description {

inline const std::vector<CDC::SuperLayerConfiguration>& CDC::LayerConfigurationManager::Get(const CDC* cdc) {
    if (fOutdated) {
        fLayerConfiguration = cdc->ComputeLayerConfiguration();
        fOutdated = false;
    }
    return fLayerConfiguration;
}

inline const std::vector<CDC::CellInformation>& CDC::CellMapManager::Get(const CDC* cdc) {
    if (fOutdated) {
        fCellMap = cdc->ComputeCellMap();
        fOutdated = false;
    }
    return fCellMap;
}

inline void CDC::SetGeometryOutdated() const {
    fLayerConfigurationManager.SetOutdated();
    fCellMapManager.SetOutdated();
}

} // namespace MACE::Detector::Description
