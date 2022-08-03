#include "MACE/Utility/Math/RealVectorSpace.hxx"

#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/TwoVector.h"

#include "TEveVector.h"

#include "Eigen/Core"

#include <iostream>

using namespace MACE::Utility::Math::Concept;

static_assert(RealVectorSpace<Eigen::Vector2f, float, 2>);
static_assert(RealVectorSpace<Eigen::Vector3f, float, 3>);
static_assert(RealVectorSpace<Eigen::Vector4f, float, 4>);
static_assert(RealVectorSpace<Eigen::Vector2d, double, 2>);
static_assert(RealVectorSpace<Eigen::Vector3d, double, 3>);
static_assert(RealVectorSpace<Eigen::Vector4d, double, 4>);

static_assert(RealVectorSpace<CLHEP::Hep2Vector, double, 2>);
static_assert(RealVectorSpace<CLHEP::Hep3Vector, double, 3>);
static_assert(RealVectorSpace<CLHEP::HepLorentzVector, double, 4>);

static_assert(not RealVectorSpace<TEveVector2D, double, 2>);
static_assert(not RealVectorSpace<TEveVectorD, double, 3>);
static_assert(not RealVectorSpace<TEveVector4D, double, 4>);
static_assert(not RealVectorSpace<TEveVector2F, float, 2>);
static_assert(not RealVectorSpace<TEveVectorF, float, 3>);
static_assert(not RealVectorSpace<TEveVector4F, float, 4>);

int main() {
    std::cout << "I'm compiled, I'm passed." << std::endl;
    return EXIT_SUCCESS;
}
