#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <fmt/format.h>
#include <llvm/Support/CommandLine.h>
#include <string>

#include "project_template/default_project.hpp"

bool valid_project_name(const std::string& name,
                        const boost::filesystem::path& working_directory) {
  return boost::filesystem::portable_directory_name(name) and
         not boost::filesystem::exists(working_directory / name);
}

int main(int argc, char* argv[]) {
  const auto cwd = boost::filesystem::current_path();

  // Command Line Parsing
  llvm::cl::opt<std::string> project_name(
      llvm::cl::Positional, llvm::cl::desc("Specify output project name"),
      llvm::cl::value_desc("project name"), llvm::cl::Required);
  llvm::cl::ParseCommandLineOptions(argc, argv);

  if (valid_project_name(project_name, cwd)) {
    create_default_spacemacs_project(cwd, project_name);
  } else {
    fmt::print("Invalid project name\n");
  }

  return 0;
}
