#include "test.h"

void printResult(int height, uint64_t timestamp) {
    // Print the results
    std::cout << "Updated Height " << height << " with updated timestamp " << timestamp << ":" << std::endl;
}

//Create a Header for prove test 
std::vector<Header> createHeaders(uint64_t timestamp, uint32_t nBits, const std::vector<int>& heights) {
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
        printResult(height, (timestamp + height));
        headers.emplace_back(version, parentId, ADProofsRoot, stateRoot, transactionsRoot, (timestamp + height), nBits, height, extensionRoot, powSolution, votes, sizeOpt);
    }

    return headers;
}

void test(int height, uint64_t timestamp, uint32_t nBits) {
    // Create ChainSettings object with appropriate test values
    FiniteDuration blockInterval = std::chrono::milliseconds(60000); // Example value
    std::cout << "Block interval is: " << blockInterval.count() << " milliseconds" << std::endl;
    int useLastEpochs = 4; // Example value
    int epochLength = 123; // Example value

    // Using default initialDifficultyHex
    ChainSettings chainSettings(blockInterval, useLastEpochs, epochLength);
    DifficultyAdjustment difficultyAdjustment(chainSettings);

    std::vector<Height> heights = difficultyAdjustment.previousHeightsRequiredForRecalculation(height * epochLength + 1, epochLength);

    // Create a vector of Headers with necessary values
    std::vector<Header> headers = createHeaders(timestamp, nBits, heights);

    try {
        difficulty result = difficultyAdjustment.calculate(headers, epochLength);
        std::cout << "Normalized difficulty: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    //Update the height of the header
    for (size_t i = 0; i < headers.size(); ++i) {
        headers[i].height = headers[i].height * 2;
    }

    std::cout << "\nUpdate the height of the header" << std::endl;
    try {
        difficulty result = difficultyAdjustment.calculate(headers, epochLength);
        std::cout << "Normalized difficulty: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {

    int height = 4;
    uint64_t timestamp = 4679968235236910924;
    uint32_t nBits = 545258809;
    test(height, timestamp, nBits);

    std::cout << std::endl;

    height = 38;
    timestamp = 7299026446648792847;
    nBits = 151027712;
    test(height, timestamp, nBits);

    std::cout << std::endl;

    height = 35;
    timestamp = 835957171591476358;
    nBits = 136662632;
    test(height, timestamp, nBits);

    std::cout << std::endl;

    height = 30;
    timestamp = 1463750476079291394;
    nBits = 536924076;
    test(height, timestamp, nBits);

    std::cout << std::endl;

    height = 5;
    timestamp = 3186141160021957874;
    nBits = 403077202;
    test(height, timestamp, nBits);

    return 0;
}
