#include "test.h"

void printInt(const std::vector<uint8_t>& hash) {
    for (size_t i = 0; i < hash.size(); ++i) {
        int8_t signedByte = static_cast<int8_t>(hash[i]);
        std::cout << static_cast<int>(signedByte);
        if (i != hash.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void printHeader(const Header& header) {
    std::cout << "Version: " << static_cast<int>(header.version) << std::endl;

    std::cout << "Parent ID: ";
    printInt(header.parentId);

    std::cout << "ADProofsRoot: ";
    for (const auto& byte : header.ADProofsRoot) {
        std::cout << static_cast<int>(static_cast<int8_t>(byte)) << " ";
    }
    std::cout << std::endl;

    std::cout << "StateRoot: ";
    for (const auto& byte : header.stateRoot) {
        std::cout << static_cast<int>(static_cast<int8_t>(byte)) << " ";
    }
    std::cout << std::endl;

    std::cout << "TransactionsRoot: ";
    for (const auto& byte : header.transactionsRoot) {
        std::cout << static_cast<int>(static_cast<int8_t>(byte)) << " ";
    }
    std::cout << std::endl;

    std::cout << "Timestamp: " << header.timestamp << std::endl;
    std::cout << "nBits: " << header.nBits << std::endl;
    std::cout << "Height: " << header.height << std::endl;

    std::cout << "ExtensionRoot: ";
    for (const auto& byte : header.extensionRoot) {
        std::cout << static_cast<int>(static_cast<int8_t>(byte)) << " ";
    }
    std::cout << std::endl;

    std::cout << "Solution pk: ";
    for (const auto& byte : groupElemToBytes(header.powSolution.pk)) {
        std::cout << static_cast<int>(static_cast<int8_t>(byte)) << " ";
    }
    std::cout << std::endl;

    std::cout << "Solution w: ";
    for (const auto& byte : groupElemToBytes(header.powSolution.w)) {
        std::cout << static_cast<int>(static_cast<int8_t>(byte)) << " ";
    }
    std::cout << std::endl;

    std::cout << "Solution nonce: ";
    for (const auto& byte : header.powSolution.n) {
        std::cout << static_cast<int>(static_cast<int8_t>(byte)) << " ";
    }
    std::cout << std::endl;

    std::cout << "Solution d: " << header.powSolution.d << std::endl;
}

//Create a Header for prove test 
Header createHeader() {
    //We can pass the different Header for testing 
    Version version = 1;
    ModifierId parentId = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    Digest32 ADProofsRoot = { 0xF6, 0x3E, 0x21, 0xB6, 0x38, 0x10, 0x54, 0xF3, 0x4F, 0x7F, 0x2D, 0x16, 0xD5, 0x3C, 0x73, 0x03, 0xBA, 0xE4, 0x6D, 0x89, 0x04, 0xA8, 0x61, 0xFB, 0xCE, 0xAD, 0xF7, 0x18, 0xF9, 0x6A, 0x4D, 0x11 };

    ADDigest stateRoot = { 0x2D, 0x05, 0xD4, 0x4A, 0xC7, 0x11, 0x6E, 0x77, 0x9C, 0x6E, 0x6D, 0xAE, 0x03, 0xC7, 0x29, 0xD5, 0x54, 0xCB, 0xFA, 0x93, 0x05, 0x85, 0x94, 0x9F, 0xEA, 0x8E, 0xB4, 0x4E, 0x54, 0x60, 0xC7, 0x9A, 0x03 };

    Digest32 transactionsRoot = { 0xC8, 0xD4, 0x9A, 0x9F, 0xD0, 0x69, 0x78, 0x6D, 0x88, 0xB9, 0xEA, 0xA1, 0x2E, 0x6D, 0x14, 0xC9, 0x9C, 0x08, 0x12, 0x76, 0x84, 0x98, 0xDD, 0xEF, 0x31, 0x9B, 0x8C, 0x87, 0x98, 0xB2, 0x70, 0x86 };
    
    uint64_t timestamp = 1720155266452;
    uint32_t nBits = 16842752;
    int height = 1;
    Digest32 extensionRoot = { 0x0E, 0x57, 0x51, 0xC0, 0x26, 0xE5, 0x43, 0xB2, 0xE8, 0xAB, 0x2E, 0xB0, 0x60, 0x99, 0xDA, 0xA1, 0xD1, 0xE5, 0xDF, 0x47, 0x77, 0x8F, 0x77, 0x87, 0xFA, 0xAB, 0x45, 0xCD, 0xF1, 0x2F, 0xE3, 0xA8 };

    AutolykosSolution powSolution = {
      groupElemFromBytes({ 0x03, 0x8B, 0x0F, 0x29, 0xA6, 0x0F, 0xA8, 0xD7, 0xE1, 0xAE, 0xAF, 0xBE, 0x51, 0x22, 0x88, 0xA6, 0xC6, 0xBC, 0x69, 0x65, 0x47, 0xBB, 0xF8, 0x24, 0x7D, 0xB2, 0x3C, 0x95, 0xE8, 0x30, 0x14, 0x51, 0x3C }),
      
      groupElemFromBytes({ 0x03, 0xF2, 0xDC, 0xB3, 0x41, 0xB9, 0xD4, 0xE8, 0xD9, 0x9A, 0xDB, 0x63, 0xA0, 0x2B, 0x28, 0x0D, 0xF9, 0x8C, 0x91, 0x06, 0x89, 0x3F, 0xBC, 0xE6, 0x01, 0x0F, 0x42, 0x94, 0xAE, 0x43, 0xAE, 0x07, 0x68 }),
      { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
      boost::multiprecision::cpp_int("5869978476706957113714750869992170814051243884080221252804036525476346689252")
    };
    std::array<uint8_t, 3> votes = {0x00, 0x00, 0x00};

    return Header(version, parentId, ADProofsRoot, stateRoot, transactionsRoot, timestamp, nBits, height, extensionRoot, powSolution, votes);
}

int main() {
    int k = 32;
    int n = 26; // Example values, adjust as needed
                
    // Create an instance of AutolykosPowScheme
    AutolykosPowScheme powScheme(k, n);

    Version version = 1;
    uint32_t nBits = 16842752;

    ADDigest stateRoot = { 0x2C, 0x35, 0xB6, 0x23, 0xCE, 0x1C, 0x45, 0xDD, 0x87, 0xD2, 0xDD, 0x86, 0x32, 0xDB, 0xDC, 0x43, 0x53, 0x32, 0x4A, 0x37, 0xDA, 0x03, 0x77, 0x91, 0xAD, 0x98, 0x41, 0xC7, 0x42, 0xCB, 0xA9, 0x39, 0x03 };

    Digest32 adProofsRoot = {0xB9, 0x0D, 0x5C, 0x8A, 0xE7, 0xDB, 0xE5, 0xC2, 0x93, 0x87, 0x5D, 0x8B, 0x80, 0x17, 0xD4, 0x74, 0xC9, 0x2C, 0x81, 0xFD, 0xF3, 0xB1, 0x46, 0x9B, 0x91, 0xF7, 0x59, 0x7C, 0x91, 0x47, 0xE4, 0x1F };

    Digest32 transactionsRoot = { 0x20, 0xD1, 0xAE, 0xFD, 0x82, 0x44, 0xBF, 0xDE, 0xB8, 0xEA, 0x0B, 0x17, 0xE3, 0xCC, 0xC7, 0x6A, 0x74, 0xB7, 0x6A, 0xFA, 0x49, 0xFA, 0x66, 0xC3, 0x0A, 0x85, 0xB1, 0x23, 0xCE, 0x83, 0xB1, 0x5F };

    uint64_t timestamp = 1720155386452;

    Digest32 extensionHash = { 0xDC, 0x35, 0x20, 0x8F, 0xFC, 0x18, 0x32, 0x0E, 0x2D, 0x5A, 0x2F, 0x11, 0x12, 0xDD, 0x88, 0xA4, 0x11, 0xD8, 0x80, 0x03, 0x23, 0xEC, 0x13, 0xAC, 0x56, 0xCB, 0x3E, 0x87, 0x46, 0xF3, 0xFC, 0x15 };

    std::array<uint8_t, 3> votes = {0x00, 0x00, 0x00};
    boost::multiprecision::cpp_int sk("24553816203091137057580550062664121360927647230968026115906299297794645072730");
    long minNonce = LLONG_MIN;
    long maxNonce = LLONG_MAX;

    Header header = createHeader();
    printHeader(header);

    std::cout << std::endl;
    std::cout << "2nd version: " << static_cast<int>(version) << std::endl;
    std::cout << "2nd nBits: " << nBits << std::endl;

    std::cout << "2nd StateRoot: ";
    for (const auto& byte : stateRoot) {
        std::cout << static_cast<int>(static_cast<int8_t>(byte)) << " ";
    }
    std::cout << std::endl;

    std::cout << "2nd adProofsRoot: ";
    for (const auto& byte : adProofsRoot) {
        std::cout << static_cast<int>(static_cast<int8_t>(byte)) << " ";
    }
    std::cout << std::endl;


    std::cout << "2nd transactionsRoot: ";
    for (const auto& byte : transactionsRoot) {
        std::cout << static_cast<int>(static_cast<int8_t>(byte)) << " ";
    }
    std::cout << std::endl;

    std::cout << "2nd timestamp: " << timestamp << std::endl;

    std::cout << "2nd extensionHash: ";
    for (const auto& byte : extensionHash) {
        std::cout << static_cast<int>(static_cast<int8_t>(byte)) << " ";
    }
    std::cout << std::endl;

    std::optional<Header> out_header_opt = powScheme.prove(header, version, nBits, stateRoot, adProofsRoot, transactionsRoot, timestamp, extensionHash, votes, sk, minNonce, maxNonce);
    if (out_header_opt) {
        Header out_header = *out_header_opt;
        std::cout << std::endl;
        std::cout << "Output Header" << std::endl;
        printHeader(out_header);
    } else {
        std::cerr << "Failed to generate proof" << std::endl;
    }
        
    return 0;
}
