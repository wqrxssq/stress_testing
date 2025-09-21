cmake_minimum_required(VERSION 3.15)
project(stress_testing CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# install gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(${PROJECT_NAME}_objs OBJECT
  src/langs.hpp

  src/utils/parser.hpp
  src/utils/parser.cpp

  src/compiler-builder/language-compilers.hpp
  src/compiler-builder/py-compiler.cpp
  src/compiler-builder/cpp-compiler.cpp
  src/compiler-builder/c-compiler.cpp
  src/compiler-builder/go-compiler.cpp
  src/compiler-builder/java-compiler.cpp

  src/detector/compiler-factory.hpp
  src/detector/extension-map.cpp
  src/detector/language-detector.cpp
  src/detector/compiler-factory.cpp
)

# main program
add_executable(${PROJECT_NAME} src/stress-test-runner.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)

# unittests
add_executable(${PROJECT_NAME}_unittest
	unittests/test-compiler-factory.cpp
  unittests/test-language-mapper.cpp
  unittests/test-parser.cpp
)
target_link_libraries(${PROJECT_NAME}_unittest PRIVATE ${PROJECT_NAME}_objs GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_unittest)

# Прописать output в папку build/
set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
