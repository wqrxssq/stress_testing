cmake_minimum_required(VERSION 3.15)
project(stress_testing CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME}_objs OBJECT
    src/langs.hpp
	src/lib/parser.hpp
    src/lib/parser.cpp
    src/lib/cmd-builder.hpp
    src/lib/cmd-builder.cpp
)

# Цель для сборки
add_executable(${PROJECT_NAME} src/stress-test-runner.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)

# Прописать output в папку build/
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
