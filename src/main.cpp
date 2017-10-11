#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <llvm/Support/CommandLine.h>
#include <string>

#include "default_project.hpp"

namespace fs = boost::filesystem;

bool invalid_project_name(const std::string name, const fs::path working_directory) {
  return !fs::portable_directory_name(name) || fs::exists(working_directory / name);
}

template <class Container>
void remove_invalid_and_duplicates(Container &project_names, const fs::path &working_directory) {
  std::remove_if(std::begin(project_names), std::end(project_names),
                 [&working_directory](const auto &name) {
                   return invalid_project_name(name, working_directory);
                 });
  std::sort(std::begin(project_names), std::end(project_names));
  std::unique(std::begin(project_names), std::end(project_names));
}

template <class Container>
std::vector<Folder> to_project_folders(Container &project_names) {
  std::vector<Folder> projects;
  for (const auto &name : project_names) {
    projects.push_back(default_project(name));
  }
  return projects;
}

void write_to_disk(std::vector<Folder> &projects, const fs::path working_directory) {
  for (const auto &project : projects) {
    project.write_to(working_directory);
  }
}

int main(int argc, char *argv[]) {
  const auto cwd = fs::current_path();

  using namespace llvm;
  // Command Line Parsing
  cl::opt<bool> RunCMake("cmake", cl::desc("Run CMake from build directory"));
  cl::list<std::string> project_names(cl::Positional, cl::desc("<Project Names>"), cl::OneOrMore);
  cl::ParseCommandLineOptions(argc, argv);

  remove_invalid_and_duplicates(project_names, cwd);
  auto projects = to_project_folders(project_names);
  write_to_disk(projects, cwd);

  return 0;
}
