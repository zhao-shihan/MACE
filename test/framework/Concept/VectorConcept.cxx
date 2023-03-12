#include "MACE/Concept/MathVector.hxx"
#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Extension/stdx/array_alias.hxx"

#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/TwoVector.h"

#include "TEveVector.h"

#include "Eigen/Core"

#include <array>
#include <iostream>
#include <vector>

namespace stdx = MACE::stdx;
using namespace MACE::Compatibility::CLHEPDefectFix::Hep2VectorDivisionAssignment;
using namespace MACE::Concept;

static_assert(InputNumericVector<float*, float, 3>);
static_assert(InputNumericVector<double*, double, 3>);
static_assert(InputNumericVector<long double*, long double, 3>);
static_assert(not NumericVector<float*, float, 3>);
static_assert(not NumericVector<double*, double, 3>);
static_assert(not NumericVector<long double*, long double, 3>);

static_assert(InputNumericVector<const float*, float, 3>);
static_assert(InputNumericVector<const double*, double, 3>);
static_assert(InputNumericVector<const long double*, long double, 3>);
static_assert(not NumericVector<const float*, float, 3>);
static_assert(not NumericVector<const double*, double, 3>);
static_assert(not NumericVector<const long double*, long double, 3>);

static_assert(InputNumericVector<float[3], float, 3>);
static_assert(InputNumericVector<double[3], double, 3>);
static_assert(InputNumericVector<long double[3], long double, 3>);
static_assert(not NumericVector<float[3], float, 3>);
static_assert(not NumericVector<double[3], double, 3>);
static_assert(not NumericVector<long double[3], long double, 3>);

static_assert(InputNumericVector<const float[3], float, 3>);
static_assert(InputNumericVector<const double[3], double, 3>);
static_assert(InputNumericVector<const long double[3], long double, 3>);
static_assert(not NumericVector<const float[3], float, 3>);
static_assert(not NumericVector<const double[3], double, 3>);
static_assert(not NumericVector<const long double[3], long double, 3>);

static_assert(NumericVector<stdx::array2f, float, 2>);
static_assert(NumericVector<stdx::array3f, float, 3>);
static_assert(NumericVector<stdx::array4f, float, 4>);
static_assert(NumericVector<stdx::array2d, double, 2>);
static_assert(NumericVector<stdx::array3d, double, 3>);
static_assert(NumericVector<stdx::array4d, double, 4>);

// static_assert(not NumericVector<std::vector<float>, float, 2>);
// static_assert(not NumericVector<std::vector<float>, float, 3>);
// static_assert(not NumericVector<std::vector<float>, float, 4>);
// static_assert(not NumericVector<std::vector<double>, double, 2>);
// static_assert(not NumericVector<std::vector<double>, double, 3>);
// static_assert(not NumericVector<std::vector<double>, double, 4>);

static_assert(MathVector<Eigen::Vector2f, float, 2>);
static_assert(MathVector<Eigen::Vector3f, float, 3>);
static_assert(MathVector<Eigen::Vector4f, float, 4>);
static_assert(MathVector<Eigen::Vector2d, double, 2>);
static_assert(MathVector<Eigen::Vector3d, double, 3>);
static_assert(MathVector<Eigen::Vector4d, double, 4>);

static_assert(MathVector<CLHEP::Hep2Vector, double, 2>);
static_assert(MathVector<CLHEP::Hep3Vector, double, 3>);
static_assert(MathVector<CLHEP::HepLorentzVector, double, 4>);

static_assert(not MathVector<TEveVector2D, double, 2>);
static_assert(not MathVector<TEveVectorD, double, 3>);
static_assert(not MathVector<TEveVector4D, double, 4>);
static_assert(not MathVector<TEveVector2F, float, 2>);
static_assert(not MathVector<TEveVectorF, float, 3>);
static_assert(not MathVector<TEveVector4F, float, 4>);

int main() {
    std::cout << "I'm compiled, I'm passed." << std::endl;
    return EXIT_SUCCESS;
}
