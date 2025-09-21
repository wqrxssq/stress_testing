CXX_COMPILER := clang++
BUILD_DIR    := build
BIN          := $(BUILD_DIR)/stress_testing

RUN_LANG ?= cpp

ifeq ($(RUN_LANG),cpp)
	NAIVE     ?= src/runners/cpp-runner/naive-solution.cpp
	SMART     ?= src/runners/cpp-runner/smart-solution.cpp
	GENERATOR ?= src/runners/cpp-runner/generator.cpp
	CHECKER   ?= src/runners/cpp-runner/advanced-checker.cpp
else ifeq ($(RUN_LANG),py)
	NAIVE     ?= src/runners/py-runner/naive-solution.py
	SMART     ?= src/runners/py-runner/smart-solution.py
	GENERATOR ?= src/runners/py-runner/generator.py
	CHECKER   ?= src/runners/py-runner/advanced-checker.py
else ifeq ($(RUN_LANG),c)
	NAIVE     ?= src/runners/c-runner/naive-solution.c
	SMART     ?= src/runners/c-runner/smart-solution.c
	GENERATOR ?= src/runners/c-runner/generator.c
	CHECKER   ?= src/runners/c-runner/advanced-checker.c
else ifeq ($(RUN_LANG),go)
	NAIVE     ?= src/runners/go-runner/naive-solution.go
	SMART     ?= src/runners/go-runner/smart-solution.go
	GENERATOR ?= src/runners/go-runner/generator.go
	CHECKER   ?= src/runners/go-runner/advanced-checker.go
else ifeq ($(RUN_LANG),java)
	NAIVE	 ?= src/runners/java-runner/naive-solution.java
	SMART	 ?= src/runners/java-runner/smart-solution.java
	GENERATOR ?= src/runners/java-runner/generator.java
	CHECKER   ?= src/runners/java-runner/advanced-checker.java
else
$(error Unsupported value for RUN_LANG: '$(RUN_LANG)'. Supported: cpp, py, c, go)
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
