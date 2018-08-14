#ifndef PROJECT_TEMPLATE_CMAKE_EXECUTION_HPP
#define PROJECT_TEMPLATE_CMAKE_EXECUTION_HPP

#include <filesystem>
#include <string_view>

void run_cmake(const std::filesystem::path& source_directory,
               const std::filesystem::path& build_directory,
               std::string_view build_type);

#endif /* PROJECT_TEMPLATE_CMAKE_EXECUTION_HPP */
