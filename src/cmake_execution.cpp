#include "project_template/cmake_execution.hpp"

#include <fmt/format.h>
#include <boost/process.hpp>

namespace bp = boost::process;

void run_cmake(const fs::path& source_directory,
               const fs::path& build_directory,
               std::string_view build_type) {
  auto cmake = bp::search_path("cmake");

  auto cmake_source_directory =
      fmt::format(fmt("-H{}"), source_directory.string());
  auto cmake_build_directory =
      fmt::format(fmt("-B{}"), build_directory.string());

  constexpr auto export_compile_commands = "-DCMAKE_EXPORT_COMPILE_COMMANDS=1";
  constexpr auto generator = "-GNinja";
  auto cmake_build_type = fmt::format(fmt("-DCMAKE_BUILD_TYPE={}"), build_type);

  auto c_compiler = fmt::format(fmt("-DCMAKE_C_COMPILER={}"),
                                bp::search_path("clang").string());
  auto cpp_compiler = fmt::format(fmt("-DCMAKE_CXX_COMPILER={}"),
                                  bp::search_path("clang++").string());

  bp::spawn(cmake, cmake_source_directory, cmake_build_directory,
            export_compile_commands, generator, cmake_build_type, c_compiler,
            cpp_compiler, bp::std_out > bp::null);
}
