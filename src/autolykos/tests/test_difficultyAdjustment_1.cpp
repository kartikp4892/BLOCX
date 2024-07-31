#include "test.h"

void testdiffcultyAdjustment_1() {
    // Create ChainSettings object with appropriate test values
    FiniteDuration blockInterval = std::chrono::milliseconds(60000); // Example value
    int useLastEpochs = 5; // Example value
    int epochLength = 123; // Example epoch length

    ChainSettings chainSettings(blockInterval, useLastEpochs, epochLength);
    DifficultyAdjustment difficultyAdjustment(chainSettings);

    // Define test parameters
    Height height = 926976; // Example height

    epochLength = 128; // Example epoch length
    // Get the result from the method
    Height result = difficultyAdjustment.nextRecalculationHeight(height, epochLength);

    height = 926977; // Example height
    result = difficultyAdjustment.nextRecalculationHeight(height, epochLength);
    
    height = 926975; // Example height
    result = difficultyAdjustment.nextRecalculationHeight(height, epochLength);
    
    height = 926950; // Example height
    result = difficultyAdjustment.nextRecalculationHeight(height, epochLength);
    
    height = 1; // Example height
    result = difficultyAdjustment.nextRecalculationHeight(height, epochLength);
    
    height = 129; // Example height
    result = difficultyAdjustment.nextRecalculationHeight(height, epochLength);
    
    height = 256; // Example height
    result = difficultyAdjustment.nextRecalculationHeight(height, epochLength);
    

    // Print the results
    std::cout << "Previous Heights Required for Recalculation at height " << height << " with epoch length " << epochLength << ":" << std::endl;

    std::cout << result << std::endl;
}

int main() {
    testdiffcultyAdjustment_1();
    return 0;
}

