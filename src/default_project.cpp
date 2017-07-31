#include "default_project.hpp"

File CMakeLists_src_file{"CMakeLists.txt", R"delim(add_executable(main main.cpp)
)delim"};

File make_CMakeLists_root(const std::string name) {
  return File{"CMakeLists.txt", R"delim(cmake_minimum_required(VERSION 3.8)

# Using c++17 for all personal projects
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Change project name here
set(PROJECT_NAME )delim" + name + R"delim()
# Where to build the files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(${PROJECT_NAME})

include_directories(include)

add_subdirectory(src)

)delim"};
}

File projectile_file{".projectile", R"delim(-/bin
-/build
)delim"};

File main_file{"main.cpp", R"delim(#include <iostream>

int main(int argc, char *argv[]) {

  return 0;
}
)delim"};

File clang_format_file{".clang-format", R"delim(BasedOnStyle: Google
ColumnLimit: 100
)delim"};

Folder default_project(const std::string& name) {
  Folder project{name};
  project.add(Folder{"bin"});
  project.add(Folder{"build"});
  project.add(Folder{"include"});
  project.add(projectile_file);
  project.add(make_CMakeLists_root(name));
  project.add(clang_format_file);

  Folder src{"src"};
  src.add(CMakeLists_src_file);
  src.add(main_file);

  project.add(src);

  return project;
}
