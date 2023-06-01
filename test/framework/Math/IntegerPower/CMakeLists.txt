project(MACE)

add_executable(BenchMarkPowRZ BenchMarkPowRZ.c++)
target_link_libraries(BenchMarkPowRZ MACEFrameWork)

add_library(CheckPowRZASM OBJECT CheckPowRZASM.c++)
target_link_libraries(CheckPowRZASM MACEFrameWork)

add_library(CheckPowZNASM OBJECT CheckPowZNASM.c++)
target_link_libraries(CheckPowZNASM MACEFrameWork)

add_executable(TestPowRZ TestPowRZ.c++)
target_link_libraries(TestPowRZ MACEFrameWork)

add_executable(TestPowZN TestPowZN.c++)
target_link_libraries(TestPowZN MACEFrameWork)
