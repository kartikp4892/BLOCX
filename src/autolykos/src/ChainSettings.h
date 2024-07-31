#ifndef CHAIN_SETTINGS_H
#define CHAIN_SETTINGS_H

#include "includes.h"

using namespace boost::multiprecision;
using FiniteDuration = std::chrono::duration<int64_t, std::milli>;

class ChainSettings {
public:
    ChainSettings(FiniteDuration blockInterval, int useLastEpochs, const std::string& initialDifficultyHex);

    FiniteDuration getBlockInterval() const { return blockInterval; }
    int getUseLastEpochs() const { return useLastEpochs; }
    cpp_int getInitialDifficulty() const { return initialDifficulty; }

    int getEpochLength() const { return epochLength; }

private:
    FiniteDuration blockInterval;
    int useLastEpochs;
    std::string initialDifficultyHex;
    cpp_int initialDifficulty;
    int epochLength; // Add this field if used in DifficultyAdjustment

    cpp_int decodeHexToBigInt(const std::string& hex) const;
};

#endif // CHAIN_SETTINGS_H

