#include "test.h"

void printResult(int height, uint64_t timestamp) {
    // Print the results
    std::cout << "Updated Height " << height << " with updated timestamp " << timestamp << ":" << std::endl;
}

//Create a Header for prove test 
std::vector<Header> createHeaders(uint64_t timestamp, uint32_t nBits, const std::vector<int>& heights, FiniteDuration DesiredInterval) {
    // Initialize the common parts of the Header
    Version version = 1;
    ModifierId parentId = {};
    Digest32 ADProofsRoot = {};
    ADDigest stateRoot = {};
    Digest32 transactionsRoot = {};
    Digest32 extensionRoot = {};
    AutolykosSolution powSolution = { {}, {}, {}, boost::multiprecision::cpp_int("") };
    std::array<uint8_t, 3> votes = {};
    std::optional<int> sizeOpt = std::nullopt;

    std::vector<Header> headers;

    // Create a Header object for each height in the vector and add it to the headers vector
    for (int height : heights) {
        auto intervalInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(DesiredInterval).count();
        printResult(height, (timestamp + intervalInMillis *2 * height));
        Timestamp timeStamp = (timestamp + intervalInMillis *2 * height);
        headers.emplace_back(version, parentId, ADProofsRoot, stateRoot, transactionsRoot, timeStamp, nBits, height, extensionRoot, powSolution, votes, sizeOpt);
    }

    return headers;
}

void test(int startEpoch, uint64_t timestamp, uint32_t nBits) {
    // Create ChainSettings object with appropriate test values
    FiniteDuration blockInterval = std::chrono::milliseconds(60000); // Example value
    std::cout << "Block interval is: " << blockInterval.count() << " milliseconds" << std::endl;
    int useLastEpochs = 4; // Example value
    int epochLength = 123; // Example value

    // Using default initialDifficultyHex
    ChainSettings chainSettings(blockInterval, useLastEpochs, epochLength);
    DifficultyAdjustment difficultyAdjustment(chainSettings);

    std::vector<Height> heights = difficultyAdjustment.previousHeightsRequiredForRecalculation(startEpoch * epochLength + 1, epochLength);

    // Create a vector of Headers with necessary values
    std::vector<Header> headers = createHeaders(timestamp, nBits, heights, blockInterval);

    try {
        difficulty result = difficultyAdjustment.calculate(headers, epochLength);
        std::cout << "Normalized difficulty: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {

    int startEpoch = 18;
    uint64_t timestamp = 5138131638541841395;
    uint32_t nBits = 137322694;
    test(startEpoch, timestamp, nBits);

    std::cout << std::endl;

    startEpoch = 25;
    timestamp = 7497154043665243135;
    nBits = 151027712;
    test(startEpoch, timestamp, nBits);

    std::cout << std::endl;

    startEpoch = 14;
    timestamp = 6116976175077542838;
    nBits = 545259519;
    test(startEpoch, timestamp, nBits);

    std::cout << std::endl;

    startEpoch = 25;
    timestamp = 5525741474235997458;
    nBits = 83918848;
    test(startEpoch, timestamp, nBits);

    std::cout << std::endl;

    startEpoch = 13;
    timestamp = 988580056388466198;
    nBits = 536927460;
    test(startEpoch, timestamp, nBits);

    return 0;
}
