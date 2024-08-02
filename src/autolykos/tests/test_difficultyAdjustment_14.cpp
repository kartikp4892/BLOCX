#include "test.h"

void printResult(int height, uint64_t timestamp) {
    // Print the results
    std::cout << "Updated Height " << height << " with updated timestamp " << timestamp << ":" << std::endl;
}

//Create a Header for prove testDifficultyAdjustment_14 
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
        headers.emplace_back(version, parentId, ADProofsRoot, stateRoot, transactionsRoot, timeStamp, encodeCompactBits(decodeCompactBits(nBits) + 1000), height, extensionRoot, powSolution, votes, sizeOpt);
    }

    return headers;
}

void testDifficultyAdjustment_14(int height, uint64_t timestamp, uint32_t nBits, int epoch, int useLastEpochs, FiniteDuration interval) {

    ChainSettings chainSettings(interval, useLastEpochs, epoch);
    DifficultyAdjustment difficultyAdjustment(chainSettings);

    std::vector<Height> heights = difficultyAdjustment.previousHeightsRequiredForRecalculation(epoch * useLastEpochs + 1, epoch);

    // Create a vector of Headers with necessary values
    std::vector<Header> headers = createHeaders(timestamp, nBits, heights, interval);

    difficulty step = 1000;
    difficulty expectedDifficulty = headers.back().requiredDifficulty + step;

    try {
        difficulty temp = difficultyAdjustment.calculate(headers, epoch);
        difficulty result = (temp - expectedDifficulty);
        long double result_double = static_cast<long double>(result);
        long double expectedDifficulty_double = static_cast<long double>(expectedDifficulty);
        // Perform floating-point division
        long double result2 = result_double / expectedDifficulty_double;

        std::cout << "Result2: " << result2 << std::endl; 

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {

    // Create ChainSettings object with appropriate testDifficultyAdjustment_14 values
    int height = 489928414;
    uint64_t timestamp = 5625479226582401005;
    uint32_t nBits = 138626145;
    FiniteDuration interval = std::chrono::milliseconds(2576682);
    int epoch = 4;
    int useLastEpochs = 2;
    testDifficultyAdjustment_14(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    height = 151376483;
    timestamp = 4393656939993612566;
    nBits = 16908288;
    interval = std::chrono::milliseconds(250481);
    epoch = 2;
    useLastEpochs = 4;
    testDifficultyAdjustment_14(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    int height = 1343735766;
    uint64_t timestamp = 7565676346816020450;
    uint32_t nBits = 16842752;
    FiniteDuration interval = std::chrono::milliseconds(2216861);
    int epoch = 4;
    int useLastEpochs = 4;
    testDifficultyAdjustment_14(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    int height = 242121424;
    uint64_t timestamp = 829700541907539228;
    uint32_t nBits = 553680896;
    FiniteDuration interval = std::chrono::milliseconds(2837945);
    int epoch = 2;
    int useLastEpochs = 4;
    testDifficultyAdjustment_14(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    return 0;
}
