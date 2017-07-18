cmake_minimum_required(VERSION 3.8)

# Using c++17 for all personal projects
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Change project name here
set(PROJECT_NAME project_template)
# Where to build the files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(${PROJECT_NAME})

include_directories(include)

add_subdirectory(src)
