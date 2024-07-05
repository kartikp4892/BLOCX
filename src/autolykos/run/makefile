# Makefile for compiling AutolykosPowScheme and DifficultySerializer

TEST=test_validate_pow_1

# Define the C++ source files and output executable
SOURCES=../src/AutolykosPowScheme.cpp ../src/DifficultySerializer.cpp ../src/HeaderSerializer.cpp ../src/NumericHash.cpp ../src/Writer.cpp ../src/core.cpp ../src/mining.cpp ../src/CryptoFacade.cpp ../src/AutolykosSolution.cpp ../src/ErgoNodeViewModifier.cpp ../src/blake2/blake2b.c ../tests/$(TEST).cpp
EXECUTABLE=main

# Define Boost and secp256k1 installation directories
BOOST_DIR=/usr/local
SECP256K1_DIR=/usr/local

# Define C++ compiler and flags
CXX=g++
CXXFLAGS=-std=c++17 -I$(BOOST_DIR)/include -I$(SECP256K1_DIR)/include
LDFLAGS=-L$(BOOST_DIR)/lib -lboost_system -L$(SECP256K1_DIR)/lib -lsecp256k1 -lssl -lcrypto -Wl,-rpath,$(SECP256K1_DIR)/lib

# Target to clean and run the executable
.PHONY: clean_run
clean_run: clean run

# Target to install Boost
.PHONY: install_boost
install_boost:
	@echo "Installing Boost..."
	cd /tmp && wget https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.gz
	cd /tmp && tar -xzf boost_1_81_0.tar.gz
	cd /tmp/boost_1_81_0 && ./bootstrap.sh --prefix=$(BOOST_DIR)
	cd /tmp/boost_1_81_0 && ./b2 install
	@echo "Boost installed"

# Target to install secp256k1
.PHONY: install_secp256k1
install_secp256k1:
	@echo "Installing secp256k1..."
	cd /tmp && git clone https://github.com/bitcoin-core/secp256k1.git
	cd /tmp/secp256k1 && ./autogen.sh
	cd /tmp/secp256k1 && ./configure --prefix=$(SECP256K1_DIR)
	cd /tmp/secp256k1 && make
	cd /tmp/secp256k1 && sudo make install
	@echo "secp256k1 installed"

# Target to compile the C++ code
$(EXECUTABLE): $(SOURCES)
	@$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE) $(LDFLAGS)
	@echo "Compiled $(EXECUTABLE)"

# Target to run the executable
.PHONY: run
run: $(EXECUTABLE)
	@./$(EXECUTABLE)

# Clean up compiled files
.PHONY: clean
clean:
	@rm -f $(EXECUTABLE)
	@echo "Cleaned up $(EXECUTABLE)"

