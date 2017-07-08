#include "cmake_execution.hpp"

#include <boost/filesystem/operations.hpp>
#include <boost/process/child.hpp>
#include <boost/process/search_path.hpp>

#include <gsl/gsl_util>

namespace fs = boost::filesystem;
namespace bp = boost::process;

void run_cmake(fs::path build_directory) {
  const auto initial_path = fs::current_path();
  fs::current_path(build_directory);
  auto __reset_working_directory =
      gsl::finally([initial_path] { fs::current_path(initial_path); });

  fs::path cmake = bp::search_path("cmake");
  const auto parent_directory = "..";

  // Create child process with build_directory as working directory
  bp::child c(cmake, parent_directory);
  c.wait();
}
