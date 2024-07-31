#include "test.h"

void printResult(int height, int epochLength, std::vector<Height> result) {
    // Print the results
    std::cout << "Previous Heights Required for Recalculation at height " << height << " with epoch length " << epochLength << ":" << std::endl;
    for (Height h : result) {
        std::cout << h << std::endl;
    }
}

void testPreviousHeightsRequiredForRecalculation() {
    // Create ChainSettings object with appropriate test values
    FiniteDuration blockInterval = std::chrono::milliseconds(60000); // Example value
    std::cout << "Block interval is: " << blockInterval.count() << " milliseconds" << std::endl;
    int useLastEpochs = 4; // Example value
    int epochLength = 123; // Example value

    // Using default initialDifficultyHex
    ChainSettings chainSettings(blockInterval, useLastEpochs, epochLength);
    DifficultyAdjustment difficultyAdjustment(chainSettings);

    //1 Get the result from the method
    std::vector<Height> result = difficultyAdjustment.previousHeightsRequiredForRecalculation(epochLength +1, epochLength);
    printResult(epochLength +1, epochLength, result);
    
    //2 Get the result from the method
    result = difficultyAdjustment.previousHeightsRequiredForRecalculation(2 * epochLength +1, epochLength);
    printResult(2 * epochLength +1 , epochLength, result);
    
    //3 Get the result from the method
    result = difficultyAdjustment.previousHeightsRequiredForRecalculation(3 * epochLength +1, epochLength);
    printResult(3 * epochLength +1, epochLength, result);
    
    //4 Get the result from the method
    result = difficultyAdjustment.previousHeightsRequiredForRecalculation(4 * epochLength +1, epochLength);
    printResult(4 * epochLength +1, epochLength, result);
    
    //5 Get the result from the method
    result = difficultyAdjustment.previousHeightsRequiredForRecalculation(5 * epochLength +1, epochLength);
    printResult(5 * epochLength +1, epochLength, result);
}

int main() {
    testPreviousHeightsRequiredForRecalculation();
    return 0;
}

