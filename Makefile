CXX_COMPILER := clang++
BUILD_DIR    := build
BIN          := $(BUILD_DIR)/stress_testing

RUN_LANG ?= cpp

ifeq ($(RUN_LANG),cpp)
	NAIVE     ?= src/cpp-runner/naive-solution.cpp
	SMART     ?= src/cpp-runner/smart-solution.cpp
	GENERATOR ?= src/cpp-runner/generator.cpp
	CHECKER   ?= src/cpp-runner/advanced-checker.cpp
else ifeq ($(RUN_LANG),py)
	NAIVE     ?= src/py-runner/naive-solution.py
	SMART     ?= src/py-runner/smart-solution.py
	GENERATOR ?= src/py-runner/generator.py
	CHECKER   ?= src/py-runner/advanced-checker.py
else ifeq ($(RUN_LANG),c)
	NAIVE     ?= src/c-runner/naive-solution.c
	SMART     ?= src/c-runner/smart-solution.c
	GENERATOR ?= src/c-runner/generator.c
	CHECKER   ?= src/c-runner/advanced-checker.c
else
$(error Unsupported value for RUN_LANG: '$(RUN_LANG)'. Supported: cpp, py, c)
endif

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

# run unittests
.PHONY: test
test:
	$(BUILD_DIR)/stress_testing_unittest

# basic run (with standard checker)
.PHONY: start-stress
start-stress:
	@mkdir -p tests
	@echo "=== Running stress_test_runner ==="
	$(BIN) $(NAIVE) $(SMART) $(GENERATOR)

# adv run (with custom checker)
.PHONY: start-adv-stress
start-adv-stress:
	@mkdir -p tests
	@echo "=== Running advanced stress_test_runner ==="
	$(BIN) -a $(NAIVE) $(SMART) $(GENERATOR) $(CHECKER)

.PHONY: clean
clean:
	@echo "=== Cleaning build directory ==="
	@rm -rf $(BUILD_DIR) tests
