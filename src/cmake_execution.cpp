#include "project_template/cmake_execution.hpp"

#include <vector>

#include "fmt/format.h"
#include "reproc++/reproc.hpp"

namespace fs = std::filesystem;

void run_cmake(const fs::path& source_directory,
               const fs::path& build_directory,
               std::string_view build_type) {
  auto cmake_configure = reproc::process();
  auto args = std::vector<std::string>{
      "cmake",
      fmt::format(fmt("-H{}"), source_directory.string()),
      fmt::format(fmt("-B{}"), build_directory.string()),
      "-DCMAKE_EXPORT_COMPILE_COMMANDS=1",
      "-GNinja",
      fmt::format(fmt("-DCMAKE_BUILD_TYPE={}"), build_type),
      "-DCMAKE_C_COMPILER=clang",
      "-DCMAKE_CXX_COMPILER=clang++"};

  cmake_configure.start(args);
}
