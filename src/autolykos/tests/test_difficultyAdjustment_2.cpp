#include "test.h"

void testdifficultyAdjustment_2() {
    // Create ChainSettings object with appropriate test values
    FiniteDuration blockInterval = std::chrono::milliseconds(600000); // Example value
    int useLastEpochs = 4; // Example value
    int epochLength = 123; // Example epoch length

    ChainSettings chainSettings(blockInterval, useLastEpochs, epochLength);
    DifficultyAdjustment difficultyAdjustment(chainSettings);

    // Define test parameters
    Height height = 926976; // Example height
    epochLength = 128; // Example epoch length

    // Get the result from the method
    std::vector<Height> result = difficultyAdjustment.heightsForNextRecalculation(height, epochLength);

    height = 926977;
    result = difficultyAdjustment.heightsForNextRecalculation(height, epochLength);

    height = 926975;
    result = difficultyAdjustment.heightsForNextRecalculation(height, epochLength);

    height = 926950;
    result = difficultyAdjustment.heightsForNextRecalculation(height, epochLength);

    height = 1;
    result = difficultyAdjustment.heightsForNextRecalculation(height, epochLength);

    height = 129;
    result = difficultyAdjustment.heightsForNextRecalculation(height, epochLength);

    height = 256;
    result = difficultyAdjustment.heightsForNextRecalculation(height, epochLength);

    // Print the results
    std::cout << "Previous Heights Required for Recalculation at height " << height << " with epoch length " << epochLength << ":" << std::endl;
    for (Height h : result) {
        std::cout << h << std::endl;
    }
}

int main() {
    testdifficultyAdjustment_2();
    return 0;
}

