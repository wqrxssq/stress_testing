cmake_minimum_required(VERSION 3.15)
project(stress_testing CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME}_objs OBJECT
    src/utils/parser.hpp
    src/utils/parser.cpp
    src/compiler.hpp
    src/utils/compiler-factory.hpp
    src/utils/compiler-factory.cpp
    src/langs.hpp
)

# Цель для сборки
add_executable(${PROJECT_NAME} src/stress-test-runner.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)

# Прописать output в папку build/
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
