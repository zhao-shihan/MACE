#include "MACE/Utility/CLHEPHep2VectorData.hxx"
#include "MACE/Utility/CLHEPHep3VectorData.hxx"
#include "MACE/Utility/CLHEPHepLorentzVectorData.hxx"

#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/TwoVector.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <utility>

int main() {
    using namespace CLHEP;
    using namespace MACE::Utility::CLHEPHep2VectorData;
    using namespace MACE::Utility::CLHEPHep3VectorData;
    using namespace MACE::Utility::CLHEPHepLorentzVectorData;

#define MACE_CLHEP_VECTOR_DATA_TEST_OUT(Arrange)                                                                                                                                                                                               \
                                                                                                                                                                                                                                               \
    double* vector2##Arrange##Data = &vector2##Arrange;                                                                                                                                                                                        \
    double* vector3##Arrange##Data = &vector3##Arrange;                                                                                                                                                                                        \
    double* vector4##Arrange##Data = &vector4##Arrange;                                                                                                                                                                                        \
    const double* vector2##Arrange##ConstData = &std::as_const(vector2##Arrange);                                                                                                                                                              \
    const double* vector3##Arrange##ConstData = &std::as_const(vector3##Arrange);                                                                                                                                                              \
    const double* vector4##Arrange##ConstData = &std::as_const(vector4##Arrange);                                                                                                                                                              \
                                                                                                                                                                                                                                               \
    std::cout << std::setprecision(19)                                                                                                                                                                                                         \
              << vector2##Arrange << '\n'                                                                                                                                                                                                      \
              << '(' << vector2##Arrange##Data[0] << ',' << vector2##Arrange##Data[1] << ')' << std::endl;                                                                                                                                     \
    if (vector2##Arrange[0] == vector2##Arrange##Data[0] and vector2##Arrange[1] == vector2##Arrange##Data[1]) {                                                                                                                               \
        std::cout << "PASS" << std::endl;                                                                                                                                                                                                      \
    } else {                                                                                                                                                                                                                                   \
        std::cout << "***FAIL***" << std::endl;                                                                                                                                                                                                \
    }                                                                                                                                                                                                                                          \
                                                                                                                                                                                                                                               \
    std::cout << '(' << vector2##Arrange##ConstData[0] << ',' << vector2##Arrange##ConstData[1] << ')' << std::endl;                                                                                                                           \
    if (vector2##Arrange[0] == vector2##Arrange##ConstData[0] and vector2##Arrange[1] == vector2##Arrange##ConstData[1]) {                                                                                                                     \
        std::cout << "PASS" << std::endl;                                                                                                                                                                                                      \
    } else {                                                                                                                                                                                                                                   \
        std::cout << "***FAIL***" << std::endl;                                                                                                                                                                                                \
    }                                                                                                                                                                                                                                          \
                                                                                                                                                                                                                                               \
    std::cout << vector3##Arrange << '\n'                                                                                                                                                                                                      \
              << '(' << vector3##Arrange##Data[0] << ',' << vector3##Arrange##Data[1] << ',' << vector3##Arrange##Data[2] << ')' << std::endl;                                                                                                 \
    if (vector3##Arrange[0] == vector3##Arrange##Data[0] and vector3##Arrange[1] == vector3##Arrange##Data[1] and vector3##Arrange[2] == vector3##Arrange##Data[2]) {                                                                          \
        std::cout << "PASS" << std::endl;                                                                                                                                                                                                      \
    } else {                                                                                                                                                                                                                                   \
        std::cout << "***FAIL***" << std::endl;                                                                                                                                                                                                \
    }                                                                                                                                                                                                                                          \
                                                                                                                                                                                                                                               \
    std::cout << '(' << vector3##Arrange##ConstData[0] << ',' << vector3##Arrange##ConstData[1] << ',' << vector3##Arrange##ConstData[2] << ')' << std::endl;                                                                                  \
    if (vector3##Arrange[0] == vector3##Arrange##ConstData[0] and vector3##Arrange[1] == vector3##Arrange##ConstData[1] and vector3##Arrange[2] == vector3##Arrange##ConstData[2]) {                                                           \
        std::cout << "PASS" << std::endl;                                                                                                                                                                                                      \
    } else {                                                                                                                                                                                                                                   \
        std::cout << "***FAIL***" << std::endl;                                                                                                                                                                                                \
    }                                                                                                                                                                                                                                          \
                                                                                                                                                                                                                                               \
    std::cout << vector4##Arrange << '\n'                                                                                                                                                                                                      \
              << '(' << vector4##Arrange##Data[0] << ',' << vector4##Arrange##Data[1] << ',' << vector4##Arrange##Data[2] << ',' << vector4##Arrange##Data[3] << ')' << std::endl;                                                             \
    if (vector4##Arrange[0] == vector4##Arrange##Data[0] and vector4##Arrange[1] == vector4##Arrange##Data[1] and vector4##Arrange[2] == vector4##Arrange##Data[2] and vector4##Arrange[3] == vector4##Arrange##Data[3]) {                     \
        std::cout << "PASS" << std::endl;                                                                                                                                                                                                      \
    } else {                                                                                                                                                                                                                                   \
        std::cout << "***FAIL***" << std::endl;                                                                                                                                                                                                \
    }                                                                                                                                                                                                                                          \
                                                                                                                                                                                                                                               \
    std::cout << '(' << vector4##Arrange##ConstData[0] << ',' << vector4##Arrange##ConstData[1] << ',' << vector4##Arrange##ConstData[2] << ',' << vector4##Arrange##ConstData[3] << ')' << std::endl;                                         \
    if (vector4##Arrange[0] == vector4##Arrange##ConstData[0] and vector4##Arrange[1] == vector4##Arrange##ConstData[1] and vector4##Arrange[2] == vector4##Arrange##ConstData[2] and vector4##Arrange[3] == vector4##Arrange##ConstData[3]) { \
        std::cout << "PASS" << std::endl;                                                                                                                                                                                                      \
    } else {                                                                                                                                                                                                                                   \
        std::cout << "***FAIL***" << std::endl;                                                                                                                                                                                                \
    }

    Hep2Vector vector21(3.1, 3.14);
    Hep3Vector vector31(3.142, 3.1416, 3.14156);
    HepLorentzVector vector41(3.141593, 3.1415927, 3.14159265, 3.141592653);
    MACE_CLHEP_VECTOR_DATA_TEST_OUT(1)

    Hep2Vector vector22(3.1, 3.14);
    HepLorentzVector vector42(3.141593, 3.1415927, 3.14159265, 3.141592653);
    Hep3Vector vector32(3.142, 3.1416, 3.14156);
    MACE_CLHEP_VECTOR_DATA_TEST_OUT(2)

    Hep3Vector vector33(3.142, 3.1416, 3.14156);
    Hep2Vector vector23(3.1, 3.14);
    HepLorentzVector vector43(3.141593, 3.1415927, 3.14159265, 3.141592653);
    MACE_CLHEP_VECTOR_DATA_TEST_OUT(3)

    Hep3Vector vector34(3.142, 3.1416, 3.14156);
    HepLorentzVector vector44(3.141593, 3.1415927, 3.14159265, 3.141592653);
    Hep2Vector vector24(3.1, 3.14);
    MACE_CLHEP_VECTOR_DATA_TEST_OUT(4)

    HepLorentzVector vector45(3.141593, 3.1415927, 3.14159265, 3.141592653);
    Hep2Vector vector25(3.1, 3.14);
    Hep3Vector vector35(3.142, 3.1416, 3.14156);
    MACE_CLHEP_VECTOR_DATA_TEST_OUT(5)

    HepLorentzVector vector46(3.141593, 3.1415927, 3.14159265, 3.141592653);
    Hep3Vector vector36(3.142, 3.1416, 3.14156);
    Hep2Vector vector26(3.1, 3.14);
    MACE_CLHEP_VECTOR_DATA_TEST_OUT(6)

    return EXIT_SUCCESS;
}
