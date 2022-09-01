#include "MACE/Utility/Concept/MerelyMoveable.hxx"
#include "MACE/Utility/Concept/NonCopyable.hxx"
#include "MACE/Utility/Concept/NonMoveable.hxx"
#include "MACE/Utility/MerelyMoveableBase.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include <iostream>

using namespace MACE::Utility;

class TrivialClass {};

static_assert(not Concept::NonCopyable<TrivialClass>);
static_assert(not Concept::MerelyMoveable<TrivialClass>);
static_assert(not Concept::NonMoveable<TrivialClass>);

class MerelyMoveableClass : public MerelyMoveableBase {};

static_assert(Concept::NonCopyable<MerelyMoveableClass>);
static_assert(Concept::MerelyMoveable<MerelyMoveableClass>);
static_assert(not Concept::NonMoveable<MerelyMoveableClass>);

class NonMoveableClass : public NonMoveableBase {};

static_assert(Concept::NonCopyable<NonMoveableClass>);
static_assert(not Concept::MerelyMoveable<NonMoveableClass>);
static_assert(Concept::NonMoveable<NonMoveableClass>);

int main() {
    std::cout << "I'm compiled, I'm passed." << std::endl;
    return EXIT_SUCCESS;
}
