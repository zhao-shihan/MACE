project(MACE)

add_executable(BenchMarkPowRZ BenchMarkPowRZ.cxx)
target_link_libraries(BenchMarkPowRZ MACE)

add_library(CheckPowRZASM OBJECT CheckPowRZASM.cxx)
target_link_libraries(CheckPowRZASM MACE)

add_library(CheckPowZNASM OBJECT CheckPowZNASM.cxx)
target_link_libraries(CheckPowZNASM MACE)

add_executable(TestPowRZ TestPowRZ.cxx)
target_link_libraries(TestPowRZ MACE)

add_executable(TestPowZN TestPowZN.cxx)
target_link_libraries(TestPowZN MACE)
