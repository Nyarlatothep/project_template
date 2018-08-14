#ifndef DEFAULT_PROJECT_HPP
#define DEFAULT_PROJECT_HPP

#include <filesystem>
#include <string_view>

void create_default_project(const std::filesystem::path& target_directory,
                            std::string_view project_name);

void create_default_test_project(const std::filesystem::path& target_directory,
                                 std::string_view project_name);

void create_default_spacemacs_project(
    const std::filesystem::path& target_directory,
    std::string_view project_name);

void create_default_test_spacemacs_project(
    const std::filesystem::path& target_directory,
    std::string_view project_name);

#endif /* DEFAULT_PROJECT_HPP */
