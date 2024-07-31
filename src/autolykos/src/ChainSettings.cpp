#include "includes.h"

ChainSettings::ChainSettings(FiniteDuration blockInterval, int useLastEpochs, int epochLength, const std::string& initialDifficultyHex)
    : blockInterval(blockInterval), useLastEpochs(useLastEpochs), epochLength(epochLength), initialDifficultyHex(initialDifficultyHex) {
    initialDifficulty = decodeHexToBigInt(initialDifficultyHex);
}

cpp_int ChainSettings::decodeHexToBigInt(const std::string& hex) const {
    try {
        std::string decodedHex;
        boost::algorithm::unhex(hex.begin(), hex.end(), std::back_inserter(decodedHex));
        cpp_int value;
        std::istringstream iss(decodedHex);
        iss >> value;
        return value;
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to parse initialDifficultyHex: " + hex);
    }
}

