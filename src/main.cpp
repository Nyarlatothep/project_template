#include <fmt/format.h>
#include <llvm/Support/CommandLine.h>
#include <experimental/filesystem>
#include <string>

#include "project_template/default_project.hpp"
#include "project_template/portability_filesystem.hpp"

namespace fs = std::experimental::filesystem;

bool valid_project_name(std::string_view name,
                        const fs::path& working_directory) {
  return portable_directory_name(name) and
         not fs::exists(working_directory / name);
}

int main(int argc, char* argv[]) {
  const auto cwd = fs::current_path();

  // Command Line Parsing
  llvm::cl::opt<std::string> project_name{
      llvm::cl::Positional, llvm::cl::desc("Specify output project name"),
      llvm::cl::value_desc("project name"), llvm::cl::Required};
  llvm::cl::ParseCommandLineOptions(argc, argv);

  if (valid_project_name(project_name, cwd)) {
    create_default_spacemacs_project(cwd, project_name);
  } else {
    fmt::print("Invalid project name\n");
  }

  return 0;
}
