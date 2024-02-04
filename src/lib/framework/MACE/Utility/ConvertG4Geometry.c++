#include "MACE/Utility/ConvertG4Geometry.h++"
#include "MACE/Utility/CreateTemporaryFile.h++"

#include "TMacro.h"

#include "G4GDMLParser.hh"
#include "G4LogicalVolume.hh"

#include "fmt/format.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace MACE::inline Utility {

auto ConvertG4GeometryToGDMLText(const G4LogicalVolume* g4Geom) -> std::string {
    const auto tempGDMLPath{CreateTemporaryFile("g4geom", ".gdml")};
    {
        G4GDMLParser gdml;
        gdml.SetAddPointerToName(true);
        gdml.SetOutputFileOverwrite(true);
        const auto g4coutBuf{G4cout.rdbuf(nullptr)};
        gdml.Write(tempGDMLPath.generic_string(), g4Geom);
        G4cout.rdbuf(g4coutBuf);
    }
    std::ostringstream tempText;
    {
        std::ifstream tempGDML{tempGDMLPath};
        if (tempGDML.fail()) { throw std::runtime_error{"error opening temp gdml file"}; }
        tempText << tempGDML.rdbuf();
    }
    std::error_code muteRemoveError;
    std::filesystem::remove(tempGDMLPath, muteRemoveError);
    return tempText.str();
}

auto ConvertG4GeometryToTMacro(const std::string& name, const std::filesystem::path& output, const G4LogicalVolume* g4Geom) -> std::unique_ptr<TMacro> {
    const auto tempMacroPath{CreateTemporaryFile(name, ".C")};
    {
        const auto tempMacroFile{std::fopen(tempMacroPath.generic_string().c_str(), "w")};
        if (tempMacroFile == nullptr) { throw std::runtime_error{"error opening temp macro file"}; }
        fmt::println(tempMacroFile, R"macro(
#include <fstream>
#include <iostream>
#include <stdexcept>

auto {0}() -> void {{
    std::ofstream gdmlFile{{"{1}"}};
    if (gdmlFile.fail()) {{ throw std::runtime_error{{"error opening {1}"}}; }}
    gdmlFile << R"{0}({2}){0}""\n";
    std::cout << "\nGDML has been saved to {1}" << std::endl;
}}
)macro",
                     name, output.generic_string(), ConvertG4GeometryToGDMLText(g4Geom));
        std::fclose(tempMacroFile);
    }
    auto macro{std::make_unique<TMacro>(name.c_str(), "Generate GDML file")};
    {
        const auto lines{macro->ReadFile(tempMacroPath.generic_string().c_str())};
        if (lines == 0) { throw std::runtime_error{"error opening temp macro file"}; }
    }
    std::error_code muteRemoveError;
    std::filesystem::remove(tempMacroPath, muteRemoveError);
    return macro;
}

} // namespace MACE::inline Utility
