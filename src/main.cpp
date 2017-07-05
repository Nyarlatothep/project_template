#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <boost/program_options.hpp>

#include "gsl/gsl"
#include "range/v3/all.hpp"

#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <iostream>
#include <string>

#include "default_project.hpp"

namespace bp = boost::process;
namespace fs = boost::filesystem;
namespace po = boost::program_options;
using namespace ranges;

void run_cmake(fs::path build_directory);

int main(int argc, char* argv[]) {
  po::options_description desc{"Allowed options"};
  desc.add_options()
      ("help", "produce help message")
      ("project-name", po::value<std::vector<std::string>>(), "project name");

  po::positional_options_description no_prefix_default;
  no_prefix_default.add("project-name", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
                .options(desc)
                .positional(no_prefix_default)
                .run(),
            vm);
  po::notify(vm);

  if (vm.count("project-name")) {
    auto project_names = vm["project-name"].as<std::vector<std::string>>();
    auto cwd = fs::current_path();

    auto invalid_project_name = [&](std::string name) {
      return !fs::portable_file_name(name) || fs::exists(cwd / name);
    };

    project_names |=
        action::remove_if(invalid_project_name) | action::sort | action::unique;

    for (const auto& name : project_names) {
      auto project_path = cwd / name;

      Folder project = default_project(name);
      project.write_to(cwd);

      run_cmake(project_path / "build");
    }
  }

  return 0;
}

void run_cmake(fs::path build_directory) {
  const auto initial_path = fs::current_path();
  fs::current_path(build_directory);
  auto __reset_working_directory =
      gsl::finally([initial_path] { fs::current_path(initial_path); });

  fs::path cmake = bp::search_path("cmake");
  const auto parent_directory = "-G ninja ..";

  // Create child process with build_directory as working directory
  bp::child c(cmake, parent_directory);
  c.wait();
}
#include "range/v3/all.hpp"
