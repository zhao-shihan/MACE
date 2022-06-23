project(Test)

add_executable(BenchMarkPowZ BenchMarkPowZ.cxx)
add_library(CheckPowZASM STATIC CheckPowZASM.cxx)
add_executable(TestPowZ TestPowZ.cxx)
add_library(CheckPowIASM STATIC CheckPowIASM.cxx)
add_executable(TestPowI TestPowI.cxx)
