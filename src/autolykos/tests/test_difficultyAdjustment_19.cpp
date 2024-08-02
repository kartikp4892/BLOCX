#include "test.h"

void printResult(int height, uint64_t timestamp) {
    // Print the results
    std::cout << "Updated Height " << height << " with updated timestamp " << timestamp << ":" << std::endl;
}

//Create a Header for prove test 
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

void test(int height, uint64_t timestamp, uint32_t nBits, int epoch, int useLastEpochs, FiniteDuration interval) {

    ChainSettings chainSettings(interval, useLastEpochs, epoch);
    DifficultyAdjustment difficultyAdjustment(chainSettings);

    std::vector<Height> heights = difficultyAdjustment.previousHeightsRequiredForRecalculation(epoch * useLastEpochs + 1, epoch);

    // Create a vector of Headers with necessary values
    std::vector<Header> headers = createHeaders(timestamp, nBits, heights, interval);

    difficulty step = 1000;
    difficulty expectedDifficulty = headers.back().requiredDifficulty + step;

    try {
        difficulty temp = difficultyAdjustment.eip37Calculate(headers, epoch);
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

    // Create ChainSettings object with appropriate test values
    int height = 1035188871;
    uint64_t timestamp = 87217016901025661;
    uint32_t nBits = 151027712;
    FiniteDuration interval = std::chrono::milliseconds(3568818);
    int epoch = 3;
    int useLastEpochs = 5;
    test(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    height = 1546778532;
    timestamp = 4574837419740619842;
    nBits = 16908288;
    interval = std::chrono::milliseconds(574800);
    epoch = 4;
    useLastEpochs = 5;
    test(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    height = 229489830;
    timestamp = 4377264488213701522;
    nBits = 545248385;
    interval = std::chrono::milliseconds(1664810);
    epoch = 2;
    useLastEpochs = 4;
    test(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    height = 266051468;
    timestamp = 603841513478765641;
    nBits = 545259519;
    interval = std::chrono::milliseconds(1180211);
    epoch = 4;
    useLastEpochs = 5;
    test(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    height = 1510628059;
    timestamp = 1820295372759134594;
    nBits = 528226476;
    interval = std::chrono::milliseconds(1243561);
    epoch = 1;
    useLastEpochs = 3;
    test(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    return 0;
}
