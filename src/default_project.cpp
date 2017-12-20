#include "default_project.hpp"

#include <fmt/format.h>
#include <fmt/ostream.h>

const File CMakeLists_src_file{"CMakeLists.txt", R"delim(find_package(FMT REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main fmt::fmt)
)delim"};

File make_CMakeLists_root(const std::string& project_name) {
  return File{"CMakeLists.txt", R"delim(cmake_minimum_required(VERSION 3.8)

# Using c++17 for all personal projects
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Change project name here
set(PROJECT_NAME )delim" + project_name +
                                    R"delim()
# Where to build the files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(${PROJECT_NAME})

include_directories(include)

add_subdirectory(src)
add_subdirectory(include)

)delim"};
}

const File projectile_file{".projectile", R"delim(-/bin
-/build
)delim"};

File dir_locals_file(const boost::filesystem::path& path_to_project_root) {
  constexpr auto cmake_generator = "Ninja";
  constexpr auto cmake_build_type = "Debug";
  constexpr auto cmake_cpp_compiler = "clang++";
  constexpr auto cmake_c_compiler = "clang";
  const auto cmake_options = fmt::format(
      "(cmake-ide-cmake-opts . \"-G{} -DCMAKE_BUILD_TYPE={} -DCMAKE_CXX_COMPILER={} "
      "-DCMAKE_C_COMPILER={}\")",
      cmake_generator, cmake_build_type, cmake_cpp_compiler, cmake_c_compiler);

  const auto project_dir = fmt::format("(cmake-ide-project-dir . {})", path_to_project_root);
  const auto build_dir =
      fmt::format("(cmake-ide-build-dir . {})", path_to_project_root / "build" / cmake_build_type);

  const auto dir_locals = fmt::format(R"foo((((nil .
       ({}
        {}
        {})))))foo",
                                      project_dir, build_dir, cmake_options);
  return File{".dir-locals.el", dir_locals};
}

const File main_file{"main.cpp", R"delim(#include <fmt/format.h>

int main(int argc, char *argv[]) {

  return 0;
}
)delim"};

const File clang_format_file{".clang-format", "BasedOnStyle: Google\n"};

Folder default_build_folder() {
  Folder build{"build"};
  build.add(Folder{"Debug"});
  build.add(Folder{"Release"});
  return build;
}

Folder default_include_folder() {
  const boost::filesystem::path home = getenv("HOME");
  const auto default_user_include = home / "in_progress/nyarlat";
  Folder include("include");
  include.add(SymLink{default_user_include});
  include.add(File("CMakeLists.txt", "add_subdirectory(nyarlat)"));
  return include;
}

Folder default_src_folder() {
  Folder src{"src"};
  src.add(CMakeLists_src_file);
  src.add(main_file);

  return src;
}

Folder default_project(const std::string& project_name) {
  Folder project{project_name};
  project.add(Folder{"bin"});
  project.add(default_build_folder());
  project.add(default_include_folder());
  project.add(default_src_folder());
  project.add(make_CMakeLists_root(project_name));
  project.add(clang_format_file);

  return project;
}

Folder default_spacemacs_project(const std::string& project_name,
                                 const boost::filesystem::path& working_directory) {
  auto project = default_project(project_name);

  project.add(projectile_file);
  project.add(dir_locals_file(working_directory / project_name));

  return project;
}
