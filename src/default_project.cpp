#include "default_project.hpp"

const std::string CMakeListsSrcFile = R"delim(#add_library(project_library )
)delim";

std::string CMakeListsRootFile(const std::string name) {
  return R"delim(cmake_minimum_required(VERSION 3.8)

# Using c++17 for all personal projects
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Change project name here
set(PROJECT_NAME )delim" +
         name + R"delim()
# Where to build the files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(${PROJECT_NAME})

# Uncomment for most used Boost libraries
#find_package(Boost REQUIRED COMPONENTS system filesystem program_options)

include_directories(include)

# Assumes a library called project_library is defined there
add_subdirectory(src)

add_executable(main src/main.cpp)
#target_link_libraries(main project_library)
#target_link_libraries(main ${Boost_LIBRARIES})
)delim";
}

const std::string ProjectileFile = R"delim(-/bin
-/build
)delim";

const std::string MainFile = R"delim(#include <iostream>

int main(int argc, char *argv[]) {

  return 0;
}
)delim";

Folder default_project(const std::string& name) {
  Folder project{name};
  project.add(Folder{"bin"});
  project.add(Folder{"build"});
  project.add(Folder{"include"});
  project.add(File{".projectile", ProjectileFile});
  project.add(File{"CMakeLists.txt", CMakeListsRootFile(name)});

  Folder src{"src"};
  src.add(File{"CMakeLists.txt", CMakeListsSrcFile});
  src.add(File{"main.cpp", MainFile});

  project.add(src);

  return project;
}
