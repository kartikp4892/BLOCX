#include "test.h"

void printHex(const std::vector<uint8_t>& msg) {
    for (const auto& byte : msg) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    std::cout << std::endl;
}

Header createHeader() {
    Version version = 2;
    ModifierId parentId = {0x0a, 0x0c, 0x02, 0x01, 0x00, 0x01, 0x08, 0x00, 0x07, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0a, 
                           0x00, 0x01, 0x0f, 0x0f, 0x00, 0x01, 0x01, 0x09, 0x0d, 0x0b, 0x02, 0x02, 0x07, 0x0f, 0x02, 0x00, 
                           0x02, 0x02, 0x00, 0x01, 0x00, 0x00, 0x07, 0x0f, 0x06, 0x02, 0x00, 0x00, 0x00, 0x01, 0x07, 0x07, 
                           0x0a, 0x00, 0x08, 0x00, 0x00, 0x00, 0x05, 0x0d, 0x04, 0x04, 0x00, 0x08, 0x09, 0x06, 0x0d, 0x00};
    Digest32 ADProofsRoot = {0x5d, 0x3f, 0x80, 0xdc, 0xff, 0x7f, 0x5e, 0x7f, 0x59, 0x00, 0x72, 0x94, 0xc1, 0x80, 0x80, 0x8d, 
                             0x01, 0x58, 0xd1, 0xff, 0x6b, 0xa1, 0x00, 0x00, 0xf9, 0x01, 0xc7, 0xf0, 0xef, 0x87, 0xdc, 0xff};
    ADDigest stateRoot = {0x5c, 0x8c, 0x00, 0xb8, 0x40, 0x3d, 0x37, 0x01, 0x55, 0x71, 0x81, 0xc8, 0xdf, 0x80, 0x00, 0x01, 
                          0xb6, 0xd5, 0x00, 0x9e, 0x22, 0x01, 0xc6, 0xff, 0x80, 0x7d, 0x71, 0x80, 0x8c, 0x00, 0x01, 0x97, 
                          0x80};
    Digest32 transactionsRoot = {0xf1, 0x7f, 0xff, 0xac, 0xb6, 0xff, 0x7f, 0x7f, 0x11, 0x80, 0xd2, 0xff, 0x7f, 0x1e, 0x24, 0xff, 
                                 0xff, 0xe1, 0xff, 0x93, 0x7f, 0x80, 0x7f, 0x07, 0x97, 0xb9, 0xff, 0x6e, 0xbd, 0xae, 0x00, 0x7e};
    uint64_t timestamp = 4928911477310178288;
    uint32_t nBits = 37748736 ;
    int height = 614400;
    Digest32 extensionRoot = {0x14, 0x80, 0x88, 0x7f, 0x80, 0x00, 0x7f, 0x4b, 0x01, 0xcf, 0x7f, 0x01, 0x3f, 0xf1, 0xff, 0xff,
                              0x56, 0x4a, 0x00, 0x00, 0xb9, 0xa5, 0x4f, 0x00, 0x77, 0x0e, 0x80, 0x7f, 0x41, 0xff, 0x88, 0xc0};
    AutolykosSolution powSolution = {
      groupElemFromBytes({0x03, 0xBE, 0xDA, 0xEE, 0x06, 0x9F, 0xF4, 0x82, 0x95, 0x00, 0xB3, 0xC0, 0x7C, 0x4D, 0x5F, 0xE6,
                          0xB3, 0xEA, 0x3D, 0x3B, 0xF7, 0x6C, 0x5C, 0x28, 0xC1, 0xD4, 0xDC, 0xDB, 0x1B, 0xED, 0x0A, 0xDE, 0x0C}),
       //The w,d field of the powSolution for these test is not provided in the scala test but it is generated by the jsonDecoder 
      // "pk", "w" and "d" values for Autolykos v2 solution, when they not passed from outside
      //val pkForV2: EcPointType = CryptoConstants.dlogGroup.identity
      //val wForV2: EcPointType = CryptoConstants.dlogGroup.generator
      groupElemFromBytes({0x02, 0x79, 0xbe, 0x66, 0x7e, 0xf9, 0xdc, 0xbb, 0xac, 0x55, 0xa0, 0x62, 0x95, 0xce, 0x87, 0x0b,
                          0x07, 0x02, 0x9b, 0xfc, 0xdb, 0x2d, 0xce, 0x28, 0xd9, 0x59, 0xf2, 0x81, 0x5b, 0x16, 0xf8, 0x17,
                          0x98}),
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x05},
      boost::multiprecision::cpp_int("0")
    };
    std::array<uint8_t, 3> votes = {0x00, 0x00, 0x00};

    return Header(version, parentId, ADProofsRoot, stateRoot, transactionsRoot, timestamp, nBits, height, extensionRoot, powSolution, votes);
}

//test vectors for first increase in N value (height 614,400)
void test_IncreaseinNvalue(AutolykosPowScheme& pow, const Header& header) {
    std::cout << "test_IncreaseinNvalue" << std::endl;

    assert(header.height == 614400); //Should be match

    HeaderWithoutPow headerWithoutPow = pow.toHeaderWithoutPow(header);
    //We need to pass headerWithoutPow as the input type for the msgByHeader and calcN method as it's input type is HeaderWithoutPow
    auto msg = pow.msgByHeader(headerWithoutPow); //msg Should be => 548c3e602a8f36f8f2738f5f643b02425038044d98543a51cabaa9785e7e864f
    std::cout << "msg: ";
    printHex(msg);

    assert(pow.calcN(headerWithoutPow) == 70464240); //Should be match

    // vector got from a miner dev
    //These is the expected output byte array for the Validate2(0002fcb113fe65e5754959872dfdbffea0489bf830beb4961ddc0e9e66a1412a)
    std::vector<uint8_t> byteArray = {0x00, 0x02, 0xfc, 0xb1, 0x13, 0xfe, 0x65, 0xe5, 0x75, 0x49, 0x59, 0x87, 0x2d, 0xfd, 0xbf, 0xfe, 0xa0, 0x48, 0x9b, 0xf8, 0x30, 0xbe, 
                                      0xb4, 0x96, 0x1d, 0xdc, 0x0e, 0x9e, 0x66, 0xa1, 0x41, 0x2a};
    //As per the scala convert these to bigInt
    boost::multiprecision::cpp_int exp_hit = toBigInt(byteArray);
 
    assert(pow.hitForVersion2(header) == exp_hit); //Result Should be =>2fcb113fe65e5754959872dfdbffea0489bf830beb4961ddc0e9e66a1412a
    std::cout << "exp_hit: " << exp_hit << std::endl ;

    boost::multiprecision::cpp_int getdata = pow.getB(header.nBits); //getB Should return => 7067388259113537318333190002971674063283542741642755394446115914399301849
    std::string getdata_decimal = getdata.str();
    std::cout << "getdata in decimal: " << getdata_decimal << std::endl;

    auto pk = groupElemToBytes(header.powSolution.pk); //pk should be => 03bedaee069ff4829500b3c07c4d5fe6b3ea3d3bf76c5c28c1d4dcdb1bed0ade0c
    std::cout << "pk: ";
    printHex(pk);
                                                       
    auto n = header.powSolution.n; //n Should be => 0000000000003105 
    std::cout << "n: ";
    printHex(n);
    
    pow.validate(header); //These result should be => hex(2fcb113fe65e5754959872dfdbffea0489bf830beb4961ddc0e9e66a1412a) dec(5277708225094898563951661870191721610292806029947618962935904682358423850)
}

int main() {
    int k = 32;
    int n = 26; // Example values, adjust as needed
                
    // Create an instance of AutolykosPowScheme
    AutolykosPowScheme powScheme(k, n);
    
    test_IncreaseinNvalue(powScheme, createHeader());

    return 0;
}

