#include "MACE/Utility/Concept/MathVector.hxx"
#include "MACE/Utility/Concept/NumericVector.hxx"

#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/TwoVector.h"

#include "TEveVector.h"

#include "Eigen/Core"

#include <array>
#include <iostream>
#include <vector>

using namespace MACE::Utility::Concept;

static_assert(NumericVector<float*, float, 3>);
static_assert(NumericVector<double*, double, 3>);
static_assert(NumericVector<long double*, long double, 3>);

static_assert(NumericVector<const float*, float, 3>);
static_assert(NumericVector<const double*, double, 3>);
static_assert(NumericVector<const long double*, long double, 3>);

static_assert(NumericVector<float[3], float, 3>);
static_assert(NumericVector<double[3], double, 3>);
static_assert(NumericVector<long double[3], long double, 3>);

static_assert(NumericVector<const float[3], float, 3>);
static_assert(NumericVector<const double[3], double, 3>);
static_assert(NumericVector<const long double[3], long double, 3>);

static_assert(NumericVector<std::array<float, 2>, float, 2>);
static_assert(NumericVector<std::array<float, 3>, float, 3>);
static_assert(NumericVector<std::array<float, 4>, float, 4>);
static_assert(NumericVector<std::array<double, 2>, double, 2>);
static_assert(NumericVector<std::array<double, 3>, double, 3>);
static_assert(NumericVector<std::array<double, 4>, double, 4>);

static_assert(NumericVector<std::vector<float>, float, 2>);
static_assert(NumericVector<std::vector<float>, float, 3>);
static_assert(NumericVector<std::vector<float>, float, 4>);
static_assert(NumericVector<std::vector<double>, double, 2>);
static_assert(NumericVector<std::vector<double>, double, 3>);
static_assert(NumericVector<std::vector<double>, double, 4>);

static_assert(NumericVector<const std::array<double, 3>, double, 3>);
static_assert(NumericVector<const std::vector<double>, double, 3>);

static_assert(MathVector<Eigen::Vector2f, float, 2>);
static_assert(MathVector<Eigen::Vector3f, float, 3>);
static_assert(MathVector<Eigen::Vector4f, float, 4>);
static_assert(MathVector<Eigen::Vector2d, double, 2>);
static_assert(MathVector<Eigen::Vector3d, double, 3>);
static_assert(MathVector<Eigen::Vector4d, double, 4>);

static_assert(MathVector<CLHEP::Hep2Vector, double, 2>);
static_assert(MathVector<CLHEP::Hep3Vector, double, 3>);
static_assert(MathVector<CLHEP::HepLorentzVector, double, 4>);

static_assert(MathVector<const Eigen::Vector3d, double, 3>);
static_assert(MathVector<const CLHEP::Hep3Vector, double, 3>);

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
