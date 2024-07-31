#include "test.h"

void testdifficultyAdjustment_10() {
    // Create ChainSettings object with appropriate test values
    std::chrono::milliseconds blockInterval(600000); // Example value
    int useLastEpochs = 4; // Example value
    int epochLength = 123; // Example epoch length

    ChainSettings chainSettings(blockInterval, useLastEpochs, epochLength);
    DifficultyAdjustment difficultyAdjustment(chainSettings);

    // Define test parameters and expected results
    BigInt diff("675204474840679645414180963439886534428");

    std::vector<std::pair<int, BigInt>> data1 = {{799167010, diff}, {799167133, diff}, {799167256, diff}, {799167379, diff}};
    BigInt result1 = difficultyAdjustment.interpolate(data1, epochLength);
    std::cout << "Result 1: " << result1 << " Expected: " << diff << std::endl;

    std::vector<std::pair<int, BigInt>> data2 = {{123, diff}, {246, diff}, {369, diff}, {492, diff}};
    BigInt result2 = difficultyAdjustment.interpolate(data2, epochLength);
    std::cout << "Result 2: " << result2 << " Expected: " << diff << std::endl;

    std::vector<std::pair<int, BigInt>> data3 = {{123, diff}, {246, diff * 2}, {369, diff * 2}, {492, diff}};
    BigInt result3 = difficultyAdjustment.interpolate(data3, epochLength);
    std::cout << "Result 3: " << result3 << " Expected: " << (diff * 3 / 2) << std::endl;

    std::vector<std::pair<int, BigInt>> data4 = {{123, diff}, {246, diff * 2}, {369, diff * 3}, {492, diff * 4}};
    BigInt result4 = difficultyAdjustment.interpolate(data4, epochLength);
    std::cout << "Result 4: " << result4 << " Expected: " << BigInt("3376022374203398227070904817199432672139") << std::endl;
}

int main() {
    testdifficultyAdjustment_10();
    return 0;
}
