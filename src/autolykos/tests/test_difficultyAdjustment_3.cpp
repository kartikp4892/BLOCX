#include "test.h"

void testdifficultyAdjustment_3() {
    // Create ChainSettings object with appropriate test values
    FiniteDuration blockInterval = std::chrono::milliseconds(600000); // Example value
    int useLastEpochs = 4; // Example value
    int epochLength = 123; // Example epoch length

    ChainSettings chainSettings(blockInterval, useLastEpochs, epochLength);
    DifficultyAdjustment difficultyAdjustment(chainSettings);

    // Define test parameters
    Height height = epochLength * (useLastEpochs + 1) + 1; // Example height

    // Get the result from the method
    std::vector<Height> result = difficultyAdjustment.previousHeightsRequiredForRecalculation(height, epochLength);

    // Print the results
    std::cout << "Previous Heights Required for Recalculation at height " << height << " with epoch length " << epochLength << ":" << std::endl;
    for (Height h : result) {
        std::cout << h << std::endl;
    }
}

int main() {
    testdifficultyAdjustment_3();
    return 0;
}

