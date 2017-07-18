#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <llvm/Support/CommandLine.h>
#include <range/v3/action.hpp>
#include <string>

#include "cmake_execution.hpp"
#include "default_project.hpp"

int main(int argc, char* argv[]) {
  namespace fs = boost::filesystem;
  using namespace llvm;
  using namespace ranges;

  auto cwd = fs::current_path();

  // Command Line Parsing
  cl::opt<bool> RunCMake("cmake", cl::desc("Run CMake from build directory"));
  cl::list<std::string> InputProjectNames(
      cl::Positional, cl::desc("<Project Names>"), cl::OneOrMore);
  cl::ParseCommandLineOptions(argc, argv);
  std::vector<std::string> project_names = InputProjectNames;

  auto invalid_project_name = [&cwd](const std::string name) {
    return !fs::portable_directory_name(name) || fs::exists(cwd / name);
  };

  project_names |=
      action::remove_if(invalid_project_name) | action::sort | action::unique;

  for (const auto& name : project_names) {
    auto project_path = cwd / name;

    Folder project = default_project(name);
    project.write_to(cwd);

    if (RunCMake) {
      run_cmake(project_path / "build");
    }
  }

  return 0;
}
