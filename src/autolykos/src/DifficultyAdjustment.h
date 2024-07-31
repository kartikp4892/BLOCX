#ifndef DIFFICULTY_ADJUSTMENT_H
#define DIFFICULTY_ADJUSTMENT_H

#include "includes.h"

using Height = uint64_t;
using difficulty = uint64_t;
using Timestamp = uint64_t;
using BigInt = uint64_t; // Assuming BigInt is defined as uint64_t for simplicity

class DifficultyAdjustment {
public:
    DifficultyAdjustment(const ChainSettings& chainSettings);

    Height nextRecalculationHeight(Height height, int epochLength) const;

    std::vector<Height> previousHeightsRequiredForRecalculation(Height height, int epochLength) const;

    std::vector<Height> heightsForNextRecalculation(Height height, int epochLength) const;

    difficulty bitcoinCalculate(const std::vector<Header>& previousHeaders, int epochLength) const;

    difficulty eip37Calculate(const std::vector<Header>& previousHeaders, int epochLength) const;

private:
    const ChainSettings& chainSettings;
    const uint64_t desiredInterval;
    const int useLastEpochs;
    const cpp_int initialDifficulty;

    difficulty bitcoinCalculate(const Header& start, const Header& end, int epochLength) const;

    difficulty calculate(const std::vector<Header>& previousHeaders, int epochLength) const;

    BigInt interpolate(const std::vector<std::pair<int, difficulty>>& data, int epochLength) const;

    static const int PrecisionConstant = 1000000000;
};

#endif // DIFFICULTY_ADJUSTMENT_H

