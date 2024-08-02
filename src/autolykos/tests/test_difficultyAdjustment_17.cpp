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

    std::vector<Height> heights = difficultyAdjustment.previousHeightsRequiredForRecalculation(height, epochLength);

    // Create a vector of Headers with necessary values
    std::vector<Header> headers = createHeaders(timestamp, nBits, heights);

    try {
        difficulty result = difficultyAdjustment.eip37Calculate(headers, epochLength);
        std::cout << "Normalized difficulty: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {

    int height = 1906076624;
    uint64_t timestamp = 8922006494203506772;
    uint32_t nBits = 545259519;
    test(height, timestamp, nBits);

    std::cout << std::endl;

    height = 620074945;
    timestamp = 4426747545559830463;
    nBits = 545259519;
    test(height, timestamp, nBits);

    std::cout << std::endl;

    height = 1176961142;
    timestamp = 7746157938731592608;
    nBits = 141245033;
    test(height, timestamp, nBits);

    std::cout << std::endl;

    height = 1567422158;
    timestamp = 2063042879598575213;
    nBits = 545259519;
    test(height, timestamp, nBits);

    std::cout << std::endl;

    height = 1676963357;
    timestamp = 1655794303025545727;
    nBits = 545259519;
    test(height, timestamp, nBits);

    std::cout << std::endl;

    height = 626500031;
    timestamp = 2035907288057740351;
    nBits = 268480005;
    test(height, timestamp, nBits);

    std::cout << std::endl;

    height = 987805700;
    timestamp = 315282339941536388;
    nBits = 135549186;
    test(height, timestamp, nBits);

    std::cout << std::endl;

    height = 157009230;
    timestamp = 2432812312734727082;
    nBits = 545259519;
    test(height, timestamp, nBits);

    std::cout << std::endl;

    height = 1444663291;
    timestamp = 6587073556086796511;
    nBits = 16908288;
    test(height, timestamp, nBits);

    std::cout << std::endl;

    height = 184666729;
    timestamp = 4775706557300038773;
    nBits = 545259519;
    test(height, timestamp, nBits);

    std::cout << std::endl;

    height = 626962305;
    timestamp = 5297340360002127193;
    nBits = 545259519;
    test(height, timestamp, nBits);

    return 0;
}
