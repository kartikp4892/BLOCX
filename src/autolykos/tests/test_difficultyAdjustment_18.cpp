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
        headers.emplace_back(version, parentId, ADProofsRoot, stateRoot, transactionsRoot, timeStamp, nBits, height, extensionRoot, powSolution, votes, sizeOpt);
    }

    return headers;
}

void test(int height, uint64_t timestamp, uint32_t nBits, int epoch, int useLastEpochs, FiniteDuration interval) {

    ChainSettings chainSettings(interval, useLastEpochs, epoch);
    DifficultyAdjustment difficultyAdjustment(chainSettings);

    std::vector<Height> heights = difficultyAdjustment.previousHeightsRequiredForRecalculation(epoch * useLastEpochs + 1, epoch);

    // Create a vector of Headers with necessary values
    std::vector<Header> headers = createHeaders(timestamp, nBits, heights, interval);

    try {
        difficulty result = difficultyAdjustment.eip37Calculate(headers, epoch);
        std::cout << "Normalized difficulty: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {

    // Create ChainSettings object with appropriate test values
    int height = 91885553;
    uint64_t timestamp = 2737377624763806302;
    uint32_t nBits = 402948031;
    FiniteDuration interval = std::chrono::milliseconds(2544768);
    int epoch = 2;
    int useLastEpochs = 2;
    test(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    height = 1271872209;
    timestamp = 2591720030994034093;
    nBits = 522526152;
    interval = std::chrono::milliseconds(594501);
    epoch = 4;
    useLastEpochs = 3;
    test(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    height = 1463402341;
    timestamp = 5501394737357541476;
    nBits = 545259519;
    interval = std::chrono::milliseconds(1801117);
    epoch = 2;
    useLastEpochs = 4;
    test(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    height = 386086312;
    timestamp = 4641218209392022306;
    nBits = 536943273;
    interval = std::chrono::milliseconds(2219216);
    epoch = 3;
    useLastEpochs = 5;
    test(height, timestamp, nBits, epoch, useLastEpochs, interval);

    std::cout << std::endl;

    height = 1041070260;
    timestamp = 2721677729803135392;
    nBits = 545259519;
    interval = std::chrono::milliseconds(177325);
    epoch = 2;
    useLastEpochs = 4;
    test(height, timestamp, nBits, epoch, useLastEpochs, interval);

    return 0;
}
