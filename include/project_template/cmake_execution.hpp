#ifndef PROJECT_TEMPLATE_CMAKE_EXECUTION_HPP
#define PROJECT_TEMPLATE_CMAKE_EXECUTION_HPP

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

#include <string_view>

void run_cmake(const fs::path& source_directory,
               const fs::path& build_directory,
               std::string_view build_type);

#endif /* PROJECT_TEMPLATE_CMAKE_EXECUTION_HPP */
