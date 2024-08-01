#include "test.h"

void equalsWithPrecision(const BigInt& i, const BigInt& j) {
    double relativeChange = static_cast<double>(i - j) / static_cast<double>(j);
    int precision = 0.0001;
    if (relativeChange < precision) {
        std::cerr << i << " and " << j << " are too different. Relative Change: " << relativeChange << std::endl;
    }
}

void testDifficultyAdjustment_12() {
    std::chrono::milliseconds blockInterval(600000); // Example value
    int useLastEpochs = 4; // Example value
    int epochLength = 123; // Example epoch length

    std::vector<std::pair<int, BigInt>> previousDifficulties = {
        {115143536, BigInt("907713703538597113779066912")},
        {115143538, BigInt("907713719305243424495060796")},
        {115143540, BigInt("907713735071889735211054680")},
        {115143542, BigInt("907713750838536045927048564")},
        {115143544, BigInt("907713766605182356643042448")}
    };

    ChainSettings chainSettings(blockInterval, useLastEpochs, epochLength);
    DifficultyAdjustment difficultyAdjustment(chainSettings);

    BigInt diff = BigInt("7883323155357996942");
    epochLength = 2;

    BigInt newDiff = difficultyAdjustment.interpolate(previousDifficulties, epochLength);

    BigInt maxPreviousDifficulty = std::max_element(previousDifficulties.begin(), previousDifficulties.end(),
        [](const std::pair<int, BigInt>& a, const std::pair<int, BigInt>& b) {
            return a.second < b.second;
        })->second;
    BigInt expected = maxPreviousDifficulty + diff;

    // Check precision
    equalsWithPrecision(expected, newDiff);

    previousDifficulties = {
        {717002421, BigInt("2810702898624348950055344651297047647483099760925423848778989335200142327401169085680")},
        {717002424, BigInt("2810702910384572415009372819307980980009661679534760431167281642426491296173238241920")}
    };

    diff = BigInt("3920074488318009389336977777508853972869778860796097435742116322924023052080");
    epochLength = 3;

    newDiff = difficultyAdjustment.interpolate(previousDifficulties, epochLength);

    maxPreviousDifficulty = std::max_element(previousDifficulties.begin(), previousDifficulties.end(),
        [](const std::pair<int, BigInt>& a, const std::pair<int, BigInt>& b) {
            return a.second < b.second;
        })->second;
    expected = maxPreviousDifficulty + diff;

    // Check precision
    equalsWithPrecision(expected, newDiff);

    previousDifficulties = {
        {1371206368, BigInt("362958892383153504236095622855984743129559488")},
        {1371206372, BigInt("362958893441955157593509156209982769066337352")},
        {1371206376, BigInt("362958894500756810950922689563980795003115216")}
    };

    diff = BigInt("264700413339353383338499506484194466");
    epochLength = 4;

    newDiff = difficultyAdjustment.interpolate(previousDifficulties, epochLength);

    maxPreviousDifficulty = std::max_element(previousDifficulties.begin(), previousDifficulties.end(),
        [](const std::pair<int, BigInt>& a, const std::pair<int, BigInt>& b) {
            return a.second < b.second;
        })->second;
    expected = maxPreviousDifficulty + diff;

    // Check precision
    equalsWithPrecision(expected, newDiff);

}

int main() {
    testDifficultyAdjustment_12();
    std::cout << "Tests Passed." << std::endl;
    return 0;
}
