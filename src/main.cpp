#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <llvm/Support/CommandLine.h>
#include <string>

#include "default_project.hpp"

namespace fs = boost::filesystem;

bool valid_project_name(const std::string &name, const fs::path &working_directory) {
  return fs::portable_directory_name(name) and not fs::exists(working_directory / name);
}

template <class Container>
std::vector<std::string> get_valid_project_names(const Container &project_names,
                                                 const fs::path &working_directory) {
  auto valid_name = [&working_directory](const auto &name) {
    return valid_project_name(name, working_directory);
  };

  std::vector<std::string> valid_project_names;
  std::copy_if(std::begin(project_names), std::end(project_names),
               std::back_inserter(valid_project_names), valid_name);

  std::sort(std::begin(valid_project_names), std::end(valid_project_names));

  // remove duplicates
  valid_project_names.erase(
      std::unique(std::begin(valid_project_names), std::end(valid_project_names)),
      std::end(valid_project_names));

  return valid_project_names;
}

template <class Container>
std::vector<Folder> container_of_default_projects(Container &project_names,
                                                  const fs::path &working_directory) {
  std::vector<Folder> projects;
  for (const auto &name : project_names) {
    projects.push_back(default_spacemacs_project(name, working_directory));
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
  cl::list<std::string> project_names(cl::Positional, cl::desc("<Project Names>"), cl::OneOrMore);
  cl::ParseCommandLineOptions(argc, argv);

  auto valid_project_names = get_valid_project_names(project_names, cwd);
  auto projects = container_of_default_projects(valid_project_names, cwd);
  write_to_disk(projects, cwd);

  return 0;
}
