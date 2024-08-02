#include "test.h"

void printResult(int height, uint64_t timestamp) {
    // Print the results
    std::cout << "Updated Height " << height << " with updated timestamp " << timestamp << ":" << std::endl;
}

//Create a Header for prove testDifficultyAdjustment_13 
std::vector<Header> createHeaders(uint64_t timestamp, uint32_t nBits, const std::vector<int>& heights, FiniteDuration interval) {
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
        auto intervalInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(interval).count();
        printResult(height, (timestamp + height * intervalInMillis));
        Timestamp timeStamp = (timestamp + height * intervalInMillis);
        headers.emplace_back(version, parentId, ADProofsRoot, stateRoot, transactionsRoot, timeStamp, nBits, height, extensionRoot, powSolution, votes, sizeOpt);
    }

    return headers;
}

void testDifficultyAdjustment_13(int height, uint64_t timestamp, uint32_t nBits, int epoch, int useLastEpochs, FiniteDuration interval) {

    ChainSettings chainSettings(interval, useLastEpochs, epoch);
    DifficultyAdjustment difficultyAdjustment(chainSettings);

    std::vector<Height> heights = difficultyAdjustment.previousHeightsRequiredForRecalculation(epoch * useLastEpochs + 1, epoch);

    // Create a vector of Headers with necessary values
    std::vector<Header> headers = createHeaders(timestamp, nBits, heights, interval);

    try {
        difficulty result = difficultyAdjustment.calculate(headers, epoch);
        std::cout << "Normalized difficulty: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {

    // Create ChainSettings object with appropriate testDifficultyAdjustment_13 values
    int height = 1254952717;
    uint64_t timestamp = 491216063000731684;
    uint32_t nBits = 404039593;
    FiniteDuration interval = std::chrono::milliseconds(430150);
    int epoch = 4;
    int useLastEpochs = 3;
    testDifficultyAdjustment_13(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    height = 378834763;
    timestamp = 9024358681566682043;
    nBits = 135543491;
    interval = std::chrono::milliseconds(1666367);
    epoch = 1;
    useLastEpochs = 3;
    testDifficultyAdjustment_13(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    height = 1549017780;
    timestamp = 8200469155296626966;
    nBits = 553680896;
    interval = std::chrono::milliseconds(2896373);
    epoch = 3;
    useLastEpochs = 4;
    testDifficultyAdjustment_13(height, timestamp, nBits, epoch, useLastEpochs, interval);

    return 0;
}
