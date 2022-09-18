#include "MACE/Concept/MerelyMoveable.hxx"
#include "MACE/Concept/NonCopyable.hxx"
#include "MACE/Concept/NonMoveable.hxx"
#include "MACE/Utility/MerelyMoveableBase.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include <iostream>

using namespace MACE;

class TrivialClass {};

static_assert(not Concept::NonCopyable<TrivialClass>);
static_assert(not Concept::MerelyMoveable<TrivialClass>);
static_assert(not Concept::NonMoveable<TrivialClass>);

class MerelyMoveableClass : public Utility::MerelyMoveableBase {};

static_assert(Concept::NonCopyable<MerelyMoveableClass>);
static_assert(Concept::MerelyMoveable<MerelyMoveableClass>);
static_assert(not Concept::NonMoveable<MerelyMoveableClass>);

class NonMoveableClass : public Utility::NonMoveableBase {};

static_assert(Concept::NonCopyable<NonMoveableClass>);
static_assert(not Concept::MerelyMoveable<NonMoveableClass>);
static_assert(Concept::NonMoveable<NonMoveableClass>);

int main() {
    std::cout << "I'm compiled, I'm passed." << std::endl;
    return EXIT_SUCCESS;
}
