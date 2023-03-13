project(MACE)

add_executable(BenchMarkPowRZ BenchMarkPowRZ.cxx)
target_link_libraries(BenchMarkPowRZ MACEFrameWork)

add_library(CheckPowRZASM OBJECT CheckPowRZASM.cxx)
target_link_libraries(CheckPowRZASM MACEFrameWork)

add_library(CheckPowZNASM OBJECT CheckPowZNASM.cxx)
target_link_libraries(CheckPowZNASM MACEFrameWork)

add_executable(TestPowRZ TestPowRZ.cxx)
target_link_libraries(TestPowRZ MACEFrameWork)

add_executable(TestPowZN TestPowZN.cxx)
target_link_libraries(TestPowZN MACEFrameWork)
