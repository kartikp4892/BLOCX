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
        difficulty result = difficultyAdjustment.eip37Calculate(headers, epochLength);
        std::cout << "Normalized difficulty: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {

    int startEpoch = 20;
    uint64_t timestamp = 7291808090597898641;
    uint32_t nBits = 545220302;
    test(startEpoch, timestamp, nBits);

    std::cout << std::endl;

    startEpoch = 6;
    timestamp = 7963580042730700614;
    nBits = 390821980;
    test(startEpoch, timestamp, nBits);

    std::cout << std::endl;

    startEpoch = 15;
    timestamp = 1184189213881624080;
    nBits = 545259519;
    test(startEpoch, timestamp, nBits);

    std::cout << std::endl;

    startEpoch = 38;
    timestamp = 5972071899239559124;
    nBits = 403530125;
    test(startEpoch, timestamp, nBits);

    std::cout << std::endl;

    startEpoch = 21;
    timestamp = 2353108119185682386;
    nBits = 83918848;
    test(startEpoch, timestamp, nBits);

    std::cout << std::endl;

    startEpoch = 31;
    timestamp = 2798866432215961413;
    nBits = 269214503;
    test(startEpoch, timestamp, nBits);

    std::cout << std::endl;

    startEpoch = 5;
    timestamp = 8113113178369235657;
    nBits = 545017698;
    test(startEpoch, timestamp, nBits);

    std::cout << std::endl;

    startEpoch = 21;
    timestamp = 6154770003730990969;
    nBits = 545259519;
    test(startEpoch, timestamp, nBits);

    std::cout << std::endl;

    startEpoch = 5;
    timestamp = 4366890608541341982;
    nBits = 553680896;
    test(startEpoch, timestamp, nBits);

    std::cout << std::endl;

    startEpoch = 26;
    timestamp = 3788155675478137220;
    nBits = 545239322;
    test(startEpoch, timestamp, nBits);

    return 0;
}
