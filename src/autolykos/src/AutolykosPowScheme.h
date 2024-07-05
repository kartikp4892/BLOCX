#ifndef AUTOLYKOS_POW_SCHEME_H
#define AUTOLYKOS_POW_SCHEME_H

#include "includes.h"
/**
  * Autolykos PoW puzzle scheme reference implementation.
  *
  * Based on k-sum problem, so general idea is to find k numbers in a table of size N, such that
  * sum of numbers (or a hash of the sum) is less than target value.
  *
  * See https://docs.ergoplatform.com/ErgoPow.pdf for details
  *
  * CPU Mining process is implemented in inefficient way and should not be used in real environment.
  *
  * @see papers/yellow/pow/ErgoPow.tex for full description
  * @param k - number of elements in one solution
  * @param n - initially, N = 2^^n
  */
class AutolykosPowScheme {
public:
    AutolykosPowScheme(int k, int n);
    int calcN(int version, int headerHeight) const;
    int calcN(const HeaderWithoutPow& header) const;
    boost::multiprecision::cpp_int getB(uint32_t nBits);
    std::vector<int> genIndexes(const std::vector<uint8_t>& seed, int N);
    boost::multiprecision::cpp_int genElement(int version,
                                          const std::vector<uint8_t>& m,
                                          const std::vector<uint8_t>& pk,
                                          const std::vector<uint8_t>& w,
                                          const std::vector<uint8_t>& indexBytes,
                                          const std::vector<uint8_t>& heightBytes);

    std::optional<AutolykosSolution> checkNonces(int version,
                                                 const std::vector<uint8_t>& h,
                                                 const std::vector<uint8_t>& m,
                                                 const boost::multiprecision::cpp_int& sk,
                                                 const boost::multiprecision::cpp_int& x,
                                                 const boost::multiprecision::cpp_int& b,
                                                 int N,
                                                 long startNonce,
                                                 long endNonce);

    std::vector<uint8_t> msgByHeader(const HeaderWithoutPow& h);

    bool checkPoWForVersion1(const Header& header, const boost::multiprecision::cpp_int& b);
    boost::multiprecision::cpp_int hitForVersion2(const Header& header);
    void validate(const Header& header);
    
    std::tuple<ModifierId, int> derivedHeaderFields(const std::optional<Header>& parentOpt);

    std::optional<Header> prove(const std::optional<Header>& parentOpt,
                                Version version,
                                uint32_t nBits,
                                const ADDigest stateRoot,
                                const Digest32 adProofsRoot,
                                const Digest32 transactionsRoot,
                                Timestamp timestamp,
                                const Digest32 extensionHash,
                                const std::array<uint8_t, 3>& votes,
                                const boost::multiprecision::cpp_int& sk,
                                long minNonce = LLONG_MIN,
                                long maxNonce = LLONG_MAX);

    static int k;
    static int n;
    int NBase;

    //The toHeaderWithoutPow is not used in scala code it is added here because in c we can't able to pass the Header type to different type HeaderWithoutPow
    HeaderWithoutPow toHeaderWithoutPow(const Header& header) const {
        return HeaderWithoutPow(header.version, header.parentId, header.ADProofsRoot, header.stateRoot, header.transactionsRoot, header.timestamp, header.nBits, header.height, header.extensionRoot, header.votes);
    }

private:
    int HeaderInitialVersion = 1;
    int IncreaseStart;
    int IncreasePeriodForN;
    int NIncreasementHeightMax;
};

#endif // AUTOLYKOS_POW_SCHEME_H

