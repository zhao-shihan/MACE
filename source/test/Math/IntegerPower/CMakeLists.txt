project(MACE)

add_executable(BenchMarkPowZ BenchMarkPowZ.cxx)
target_link_libraries(BenchMarkPowZ MACE)

add_library(CheckPowZASM OBJECT CheckPowZASM.cxx)
target_link_libraries(CheckPowZASM MACE)

add_executable(TestPowZ TestPowZ.cxx)
target_link_libraries(TestPowZ MACE)

add_library(CheckPowIASM OBJECT CheckPowIASM.cxx)
target_link_libraries(CheckPowIASM MACE)

add_executable(TestPowI TestPowI.cxx)
target_link_libraries(TestPowI MACE)
