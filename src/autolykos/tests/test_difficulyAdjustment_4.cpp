#include "test.h"

void testPreviousHeightsRequiredForRecalculation() {
    // Create ChainSettings object with appropriate test values
    FiniteDuration blockInterval = std::chrono::milliseconds(60000); // Example value
    std::cout << "Block interval is: " << blockInterval.count() << " milliseconds" << std::endl;
    int useLastEpochs = 3; // Example value
    int epochLength = 1; // Example value

    // Using default initialDifficultyHex
    ChainSettings chainSettings(blockInterval, useLastEpochs, epochLength);
    DifficultyAdjustment difficultyAdjustment(chainSettings);

    // Define test parameters
    Height height = useLastEpochs +1; // Example height

    // Get the result from the method
    std::vector<Height> result = difficultyAdjustment.previousHeightsRequiredForRecalculation(height, epochLength);

    // Print the results
    std::cout << "Previous Heights Required for Recalculation at height " << height << " with epoch length " << epochLength << ":" << std::endl;
    for (Height h : result) {
        std::cout << h << std::endl;
    }
}

int main() {
    testPreviousHeightsRequiredForRecalculation();
    return 0;
}

