CXX_COMPILER := clang++
BUILD_DIR := build
BIN := $(BUILD_DIR)/stress_test_runner

NAIVE ?= src/NaiveSolution.cpp
SMART ?= src/SmartSolution.cpp
GENERATOR ?= src/Generator.cpp
CHECKER ?= src/AdvancedChecker.cpp

.PHONY: all
all: build start-stress

# conf + build via CMake
.PHONY: build
build:
	@echo "=== Configuring project ==="
	cmake -S . -B $(BUILD_DIR) -DCMAKE_CXX_COMPILER=$(CXX_COMPILER)
	@echo "=== Building project ==="
	cmake --build $(BUILD_DIR)
	@mkdir -p tests

# basic run (with standart checker)
start-stress: build
	@echo "=== Running stress_test_runner ==="
	$(BIN) $(NAIVE) $(SMART) $(GENERATOR)

# adv run (with custom checker)
start-adv-stress: build
	@echo "=== Running advanced stress_test_runner ==="
	$(BIN) -a $(NAIVE) $(SMART) $(GENERATOR) $(CHECKER)

clean:
	@echo "=== Cleaning build directory ==="
	@rm -rf $(BUILD_DIR)
	@rm -rf tests
