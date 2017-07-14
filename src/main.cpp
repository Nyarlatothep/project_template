#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/program_options.hpp>
#define BOOST_FILESYSTEM_NO_DEPRECATED

#include "range/v3/action.hpp"

#include <string>

#include "cmake_execution.hpp"
#include "default_project.hpp"

boost::program_options::variables_map setup_command_line(int argc, char* arv[]);
std::vector<std::string> get_project_names(
    boost::program_options::variables_map vm);

int main(int argc, char* argv[]) {
  namespace fs = boost::filesystem;
  using namespace ranges;

  auto variable_map = setup_command_line(argc, argv);
  auto project_names = get_project_names(variable_map);

  auto cwd = fs::current_path();

  auto invalid_project_name = [&cwd](const std::string name) {
    return !fs::portable_directory_name(name) || fs::exists(cwd / name);
  };

  project_names |=
      action::remove_if(invalid_project_name) | action::sort | action::unique;

  for (const auto& name : project_names) {
    auto project_path = cwd / name;

    Folder project = default_project(name);
    project.write_to(cwd);

    run_cmake(project_path / "build");
  }

  return 0;
}

boost::program_options::variables_map setup_command_line(int argc,
                                                         char* argv[]) {
  namespace po = boost::program_options;
  po::options_description desc{"Allowed options"};
  desc.add_options()("help", "produce help message")(
      "project-name", po::value<std::vector<std::string>>(), "project name");

  po::positional_options_description no_prefix_default;
  no_prefix_default.add("project-name", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
                .options(desc)
                .positional(no_prefix_default)
                .run(),
            vm);
  po::notify(vm);
  return vm;
}

std::vector<std::string> get_project_names(
    boost::program_options::variables_map vm) {
  if (vm.count("project-name")) {
    return vm["project-name"].as<std::vector<std::string>>();
  } else {
    return {};
  }
}
