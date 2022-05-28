#include "MACE/Utility/DivideIndices.hxx"

#include <iostream>

using namespace MACE::Utility;

template<std::integral Integral_t>
void DoTest(Integral_t begin, Integral_t end, Integral_t nTakers) {
    const auto dividedIndexNum = DivideIndexNum(end - begin, nTakers);
    std::cout << "DivideIndexNum(...):\n";
    for (size_t i = 0; i < dividedIndexNum.size(); ++i) {
        std::cout << i << ": " << dividedIndexNum[i] << '\n';
    }

    auto PrintResult = [](const auto& result) {
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << i << ": [" << result[i].begin << ", " << result[i].end << ", " << result[i].step << ", " << result[i].count << "]\n";
        }
    };

    const auto dividedIndexRangeIndexWise = DivideIndexRangeIndexWise(begin, end, nTakers);
    std::cout << "DivideIndexRangeIndexWise(...):\n";
    PrintResult(dividedIndexRangeIndexWise);

    const auto dividedIndexRangeIndexWisePair = DivideIndexRangeIndexWise(std::make_pair(begin, end), nTakers);
    std::cout << "DivideIndexRangeIndexWise(...):\n";
    PrintResult(dividedIndexRangeIndexWisePair);

    const auto dividedIndexRangeTakerWise = DivideIndexRangeTakerWise(begin, end, nTakers);
    std::cout << "DivideIndexRangeTakerWise(...):\n";
    PrintResult(dividedIndexRangeTakerWise);

    const auto dividedIndexRangeTakerWisePair = DivideIndexRangeTakerWise(std::make_pair(begin, end), nTakers);
    std::cout << "DivideIndexRangeTakerWise(...):\n";
    PrintResult(dividedIndexRangeTakerWisePair);
}

int main(int, char*[]) {
    std::cout << "<int>(0, 74, 7):\n";
    DoTest<int>(0, 74, 7);
    std::cout << "<unsigned int>(0, 74, 7):\n";
    DoTest<unsigned int>(0, 74, 7);
    std::cout << "<long>(0, 74, 7):\n";
    DoTest<long>(0, 74, 7);
    std::cout << "<unsigned long>(0, 74, 7):\n";
    DoTest<unsigned long>(0, 74, 7);
    std::cout << "<long long>(0, 74, 7):\n";
    DoTest<long long>(0, 74, 7);
    std::cout << "<unsigned long long>(0, 74, 7):\n";
    DoTest<unsigned long long>(0, 74, 7);

    std::cout << "<int>(0, 3, 7):\n";
    DoTest<int>(0, 3, 7);
    std::cout << "<unsigned int>(0, 3, 7):\n";
    DoTest<unsigned int>(0, 3, 7);
    std::cout << "<long>(0, 3, 7):\n";
    DoTest<long>(0, 3, 7);
    std::cout << "<unsigned long>(0, 3, 7):\n";
    DoTest<unsigned long>(0, 3, 7);
    std::cout << "<long long>(0, 3, 7):\n";
    DoTest<long long>(0, 3, 7);
    std::cout << "<unsigned long long>(0, 3, 7):\n";
    DoTest<unsigned long long>(0, 3, 7);

    std::cout << "<int>(45, 6452, 5):\n";
    DoTest<int>(45, 6452, 5);
    std::cout << "<unsigned int>(45, 6452, 5):\n";
    DoTest<unsigned int>(45, 6452, 5);
    std::cout << "<long>(45, 6452, 5):\n";
    DoTest<long>(45, 6452, 5);
    std::cout << "<unsigned long>(45, 6452, 5):\n";
    DoTest<unsigned long>(45, 6452, 5);
    std::cout << "<long long>(45, 6452, 5):\n";
    DoTest<long long>(45, 6452, 5);
    std::cout << "<unsigned long long>(45, 6452, 5):\n";
    DoTest<unsigned long long>(45, 6452, 5);

    std::cout << "<int>(7, 7, 5):\n";
    DoTest<int>(7, 7, 5);
    std::cout << "<unsigned int>(7, 7, 5):\n";
    DoTest<unsigned int>(7, 7, 5);
    std::cout << "<long>(7, 7, 5):\n";
    DoTest<long>(7, 7, 5);
    std::cout << "<unsigned long>(7, 7, 5):\n";
    DoTest<unsigned long>(7, 7, 5);
    std::cout << "<long long>(7, 7, 5):\n";
    DoTest<long long>(7, 7, 5);
    std::cout << "<unsigned long long>(7, 7, 5):\n";
    DoTest<unsigned long long>(7, 7, 5);

    std::cout << std::endl;

    return EXIT_SUCCESS;
}