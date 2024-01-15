#include "MACE/Concept/MerelyMoveable.h++"
#include "MACE/Concept/NonCopyable.h++"
#include "MACE/Concept/NonMoveable.h++"
#include "MACE/Utility/MerelyMoveableBase.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include <iostream>

using namespace MACE;

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
