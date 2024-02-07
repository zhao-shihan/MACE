namespace MACE::Detector::Description {

inline auto CDC::Cache::Expire() -> void {
    fLayerConfiguration = {};
    fCellMap = {};
    fCellMapFromSenseLayerIDAndLocalCellID = {};
}

inline auto CDC::Cache::LayerConfiguration(const CDC* cdc) -> const std::vector<SuperLayerConfiguration>& {
    if (fLayerConfiguration) { return *fLayerConfiguration; }
    return *(fLayerConfiguration = cdc->ComputeLayerConfiguration());
}

inline auto CDC::Cache::CellMap(const CDC* cdc) -> const std::vector<CellInformation>& {
    if (fCellMap) { return *fCellMap; }
    return *(fCellMap = cdc->ComputeCellMap());
}

inline auto CDC::Cache::CellMapFromSenseLayerIDAndLocalCellID(const CDC* cdc) -> const CellMapFromSenseLayerIDAndLocalCellIDType& {
    if (fCellMapFromSenseLayerIDAndLocalCellID) { return *fCellMapFromSenseLayerIDAndLocalCellID; }
    return *(fCellMapFromSenseLayerIDAndLocalCellID = cdc->ComputeCellMapFromSenseLayerIDAndLocalCellID());
}

} // namespace MACE::Detector::Description
