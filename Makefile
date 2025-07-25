CXX_COMPILER := clang++
BUILD_DIR := build
BIN := $(BUILD_DIR)/stress_testing

NAIVE ?= src/cxx-builder/naive-solution.cpp
SMART ?= src/cxx-builder/smart-solution.cpp
GENERATOR ?= src/cxx-builder/generator.cpp
CHECKER ?= src/cxx-builder/advanced-checker.cpp

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
.PHONY: start-stress
start-stress: build
	@echo "=== Running stress_test_runner ==="
	$(BIN) $(NAIVE) $(SMART) $(GENERATOR)

# adv run (with custom checker)
.PHONY: start-adv-stress
start-adv-stress: build
	@echo "=== Running advanced stress_test_runner ==="
	$(BIN) -a $(NAIVE) $(SMART) $(GENERATOR) $(CHECKER)

.PHONY: clean
clean:
	@echo "=== Cleaning build directory ==="
	@rm -rf $(BUILD_DIR)
	@rm -rf tests
