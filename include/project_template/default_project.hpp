#ifndef DEFAULT_PROJECT_HPP
#define DEFAULT_PROJECT_HPP

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

#include <string_view>

void create_default_project(const fs::path& target_directory,
                            std::string_view project_name);

void create_default_test_project(const fs::path& target_directory,
                                 std::string_view project_name);

void create_default_spacemacs_project(const fs::path& target_directory,
                                      std::string_view project_name);

void create_default_test_spacemacs_project(const fs::path& target_directory,
                                           std::string_view project_name);

#endif /* DEFAULT_PROJECT_HPP */
