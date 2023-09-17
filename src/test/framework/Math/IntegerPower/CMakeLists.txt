project(MACE)

add_executable(BenchMarkPowRZ BenchMarkPowRZ.c++)
target_link_libraries(BenchMarkPowRZ MACEFramework)

add_library(CheckPowRZASM OBJECT CheckPowRZASM.c++)
target_link_libraries(CheckPowRZASM MACEFramework)

add_library(CheckPowZNASM OBJECT CheckPowZNASM.c++)
target_link_libraries(CheckPowZNASM MACEFramework)

add_executable(TestPowRZ TestPowRZ.c++)
target_link_libraries(TestPowRZ MACEFramework)

add_executable(TestPowZN TestPowZN.c++)
target_link_libraries(TestPowZN MACEFramework)
