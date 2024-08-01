#include "test.h"

void testDifficultyAdjustment_11() {
    std::chrono::milliseconds blockInterval(600000); // Example value
    int useLastEpochs = 4; // Example value
    int epochLength = 123; // Example epoch length

    std::vector<std::pair<int, BigInt>> previousDifficulties = {
        {889548853, BigInt("5680815028959414095499577649612996581")},
        {889548976, BigInt("5680815028959414095499577649612996581")},
        {889549099, BigInt("5680815028959414095499577649612996581")},
        {889549222, BigInt("5680815028959414095499577649612996581")}
    };

    ChainSettings chainSettings(blockInterval, useLastEpochs, epochLength);
    DifficultyAdjustment difficultyAdjustment(chainSettings);

    // Precision value for comparison
    double precision = 0.01; // Example precision value

    BigInt diff = BigInt("5680815028959414095499577649612996581");

    BigInt newDiff = difficultyAdjustment.interpolate(previousDifficulties, epochLength);

    double relativeChange = static_cast<double>(newDiff - diff) / static_cast<double>(diff);

    assert(relativeChange < precision);

    previousDifficulties = {
        {172371690, BigInt("2343665489258948537")},
        {172371813, BigInt("2343665489258948537")},
        {172371936, BigInt("2343665489258948537")},
        {172372059, BigInt("2343665489258948537")}
    };

    diff = BigInt("2343665489258948537");

    newDiff = difficultyAdjustment.interpolate(previousDifficulties, epochLength);

    relativeChange = static_cast<double>(newDiff - diff) / static_cast<double>(diff);

    assert(relativeChange < precision);

    previousDifficulties = {
        {1748644761, BigInt("16382986027556206483596992296982613032")},
        {1748644884, BigInt("16382986027556206483596992296982613032")},
        {1748645007, BigInt("16382986027556206483596992296982613032")},
        {1748645130, BigInt("16382986027556206483596992296982613032")}
    };

    diff = BigInt("16382986027556206483596992296982613032");

    newDiff = difficultyAdjustment.interpolate(previousDifficulties, epochLength);

    relativeChange = static_cast<double>(newDiff - diff) / static_cast<double>(diff);

    assert(relativeChange < precision);
}

int main() {
    testDifficultyAdjustment_11();
    std::cout << "Tests Passed." << std::endl;
    return 0;
}
