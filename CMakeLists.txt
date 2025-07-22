cmake_minimum_required(VERSION 3.15)
project(stress_testing CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Цель для сборки
add_executable(stress_test_runner src/StressTestRunner.cpp)

# Прописать output в папку build/
set_target_properties(stress_test_runner PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
