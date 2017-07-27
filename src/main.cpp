#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <llvm/Support/CommandLine.h>
#include <string>

#include "cmake_execution.hpp"
#include "default_project.hpp"

namespace fs = boost::filesystem;

bool invalid_project_name(const std::string name, const fs::path working_directory) {
  return !fs::portable_directory_name(name) || fs::exists(working_directory / name);
}

template <class Container>
void remove_invalid_and_duplicate(Container &project_names, const fs::path &working_directory) {
  std::remove_if(std::begin(project_names), std::end(project_names),
                 [&working_directory](const auto &name) {
                   return invalid_project_name(name, working_directory);
                 });
  std::sort(std::begin(project_names), std::end(project_names));
  std::unique(std::begin(project_names), std::end(project_names));
}

template <class Container>
void write_to_disk(Container &project_names, const fs::path working_directory) {
  for (const auto &name : project_names) {
    Folder project = default_project(name);
    project.write_to(working_directory);
  }
}

template <class Container>
void run_cmake_in_build_folders(Container &project_names, const fs::path working_directory) {
  for (const std::string &name : project_names) {
    auto project_path = working_directory / name;
    run_cmake(project_path / "build");
  }
}

int main(int argc, char *argv[]) {
  const auto cwd = fs::current_path();

  using namespace llvm;
  // Command Line Parsing
  cl::opt<bool> RunCMake("cmake", cl::desc("Run CMake from build directory"));
  cl::list<std::string> project_names(cl::Positional, cl::desc("<Project Names>"), cl::OneOrMore);
  cl::ParseCommandLineOptions(argc, argv);

  remove_invalid_and_duplicate(project_names, cwd);
  write_to_disk(project_names, cwd);
  if (RunCMake) {
    run_cmake_in_build_folders(project_names, cwd);
  }

  return 0;
}
