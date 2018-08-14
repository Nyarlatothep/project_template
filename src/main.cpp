#include <fmt/format.h>
#include <llvm/Support/CommandLine.h>
#include <filesystem>
#include <string>

#include "project_template/cmake_execution.hpp"
#include "project_template/default_project.hpp"
#include "project_template/portability_filesystem.hpp"

namespace fs = std::filesystem;

constexpr bool valid_project_name(std::string_view name,
                                  const fs::path& working_directory) {
  return portable_directory_name(name) and
         not fs::exists(working_directory / name);
}

int main(int argc, char* argv[]) {
  const auto cwd = fs::current_path();

  namespace cl = llvm::cl;

  // Command Line Parsing
  cl::opt<std::string> project_name{
      cl::Positional, cl::desc{"Specify output project name"},
      cl::value_desc{"project name"}, cl::Required};
  cl::opt<bool> test{"test", cl::desc{"Set as testing"}};
  cl::ParseCommandLineOptions(argc, argv);

  if (valid_project_name(project_name, cwd)) {
    if (test) {
      create_default_test_spacemacs_project(cwd, project_name);
    } else {
      create_default_spacemacs_project(cwd, project_name);
    }
  } else {
    fmt::print("Invalid project name\n");
  }

  return 0;
}
